#include "skvconf.h"
#include <assert.h>

int main(int argc, char **argv) {
  assert(argc > 1);
  skvconf_elm_t *elm;
  assert(skvconf_parse_file(argv[1], &elm) != 0);
  return 0;
}
