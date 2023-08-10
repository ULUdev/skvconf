#include "parser.tab.h"
#include "skvconf.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define streq(s1, s2) (strlen(s1) == strlen(s2) && strncmp(s1, s2, strlen(s1)) == 0)

int main(int argc, char **argv) {
  if (argc < 2) return 1;
  skvconf_elm_t *e;
  int res = skvconf_parse_file(argv[1], &e);
  if (res != 0) return res;

  skvconf_elm_t *a = skvconf_find_element(e, "a", NULL);
  assert(a);
  assert(a->type == SKVCONF_TYPE_NUM);
  assert(a->val.num == 3);

  skvconf_elm_t *b = skvconf_find_element(e, "b", NULL);
  assert(b);
  assert(b->type == SKVCONF_TYPE_STR);
  assert(streq(b->val.str, "abc"));

  skvconf_elm_t *c = skvconf_find_element(e, "c", NULL);
  assert(c);
  assert(c->type == SKVCONF_TYPE_BOOLEAN);
  assert(c->val.boolean == true);

  /* skvconf_elm_t *d = skvconf_find_element(e, "d", NULL);
  assert(d);
  assert(d->type = SKVCONF_TYPE_GROUP); */

  skvconf_elm_t *_e = skvconf_find_element(e, "d.e", NULL);
  assert(_e);
  assert(_e->type == SKVCONF_TYPE_BOOLEAN);
  assert(_e->val.boolean == false);

  skvconf_elm_destroy(e);
  return 0;
}
