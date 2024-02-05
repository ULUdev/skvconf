#include "skvconf.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define streq(s1, s2)                                                          \
  (strlen(s1) == strlen(s2) && strncmp(s1, s2, strlen(s1)) == 0)

#define EXPECTED_STRING "a_b-c.d:e f; g"

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;
  skvconf_elm_t *elm;
  if (skvconf_parse_file(argv[1], &elm) != 0)
    return 1;

  skvconf_elm_t *string = skvconf_find_element(elm, "d.f.h", NULL);
  assert(string);
  assert(string->type == SKVCONF_TYPE_STR);
  assert(streq(string->val.str, EXPECTED_STRING));

  skvconf_elm_destroy(elm);
  return 0;
}
