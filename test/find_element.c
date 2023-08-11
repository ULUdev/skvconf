#include "skvconf.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define streq(s1, s2)                                                          \
  (strlen(s1) == strlen(s2) && strncmp(s1, s2, strlen(s1)) == 0)

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;
  skvconf_elm_t *elm;
  int res = skvconf_parse_file(argv[1], &elm);
  if (res != 0)
    return res;

  skvconf_elm_t *a = skvconf_find_element(elm, "a", NULL);
  assert(a);
  assert(a->type == SKVCONF_TYPE_NUM);
  assert(a->val.num == 3);

  skvconf_elm_t *b = skvconf_find_element(elm, "b", NULL);
  assert(b);
  assert(b->type == SKVCONF_TYPE_STR);
  assert(streq(b->val.str, "abc"));

  skvconf_elm_t *c = skvconf_find_element(elm, "c", NULL);
  assert(c);
  assert(c->type == SKVCONF_TYPE_BOOLEAN);
  assert(c->val.boolean == true);

  skvconf_elm_destroy(elm);
  return 0;
}
