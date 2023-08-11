#include "skvconf.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;
  skvconf_elm_t *elm;
  int res = skvconf_parse_file(argv[1], &elm);
  if (res != 0)
    return res;

  skvconf_elm_t *d = skvconf_find_element(elm, "d", NULL);
  assert(!d);

  skvconf_elm_destroy(elm);
  return 0;
}
