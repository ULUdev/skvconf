/// @file
#ifndef SKVCONF_TYPES_H
#define SKVCONF_TYPES_H
#include <stdbool.h>
/// a type a value from a config may have
typedef enum {
  SKVCONF_TYPE_NUM,     ///< a number (integer)
  SKVCONF_TYPE_STR,     ///< a string
  SKVCONF_TYPE_BOOLEAN, ///< a boolean
  SKVCONF_TYPE_GROUP,   ///< a group with other values inside of it
} skvconf_type_t;

/// an element of a configuration
typedef struct skvconf_elm {
  skvconf_type_t type; ///< the type of the value
  union {
    int num;
    char *str;
    bool boolean;
  } val;                     ///< a union to where the value is stored
  char *id;                  ///< the identifier/key for the value
  struct skvconf_elm *next;  ///< the next value
  struct skvconf_elm *child; ///< the first child
} skvconf_elm_t;

/// destroy an element
/// @param elm the element to destroy
/// @remark this function destroys `elm` recursively. This means that all linked
/// elements (next pointers and children) are also cleared until the entire tree
/// pointed to by `elm` is free'd. This means you can call this function on the
/// root element to destroy everything in that config
void skvconf_elm_destroy(skvconf_elm_t *elm);
#endif
