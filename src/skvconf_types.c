#include "skvconf_types.h"
#include <stdlib.h>

void skvconf_elm_destroy(skvconf_elm_t *elm) {
    if (!elm) return;
    if (elm->type == SKVCONF_TYPE_STR) free(elm->val.str);
    free(elm->id);
    skvconf_elm_destroy(elm->child);
    skvconf_elm_destroy(elm->next);
    free(elm);
}
