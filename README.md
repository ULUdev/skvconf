# `skvconf`
## Simple key-value configuration language written in C

## Compiling from source
### Dependencies
- `meson`
- A C compiler (e.g. `gcc`)
- `flex`
- `bison`

### Build Instructions
1. `meson setup build .`
2. `meson compile -C build`
3. `meson install -C build` (optional)

If you use meson in your project you can also use `skvconf` through a
subproject.

### Tests
If you wish to contribute (for whatever reason) or just check wether the API
behaves correctly use `meson test -C build`. When contributing add test cases
that check your expected behavior.

## Basic Usage
`skvconf` is simple. Both in it's language and API. A basic example looks like this:

```c
#include <skvconf.h>
#include <stdio.h>

int main(void) {
    skvconf_elm_t *conf;
    skvconf_parse_file("test.conf", &conf);
    skvconf_elm_t *elm = skvconf_find_element(conf, "test.value", NULL);
    if (!elm) {
        printf("undefined\n");
        return 1;
    }
    if (elm->type != SKVCONF_TYPE_STR) {
        printf("wrong type!\n");
        return 1;
    }
    printf("test.value: %s\n", elm->val.str);
    skvconf_elm_destroy(conf);
    return 0;
}
```

Your main interactions are going to be with three functions:
- `skvconf_parse_file`
- `skvconf_find_element`
- `skvconf_elm_destroy`
All of them are made available through the `skvconf.h` header, which also
includes a few other headers automatically.

The definition for an `skvconf_elm_t` can be found in `skvconf_types.h`:
```c
typedef struct skvconf_elm {
    skvconf_type_t type;
    union {
        int num;
        char *str;
        bool boolean;
    } val;
    char *id;
    struct skvconf_elm *next;
    struct skvconf_elm *child;
} skvconf_elm_t;
```

the `type` is simply an enum specifying the type of the object:
```c
typedef enum {
    SKVCONF_TYPE_NUM,
    SKVCONF_TYPE_STR,
    SKVCONF_TYPE_BOOLEAN,
    SKVCONF_TYPE_GROUP,
} skvconf_type_t;
```
Depending on the type of the object you can access the corresponding member of
the union `val` in an element.

## Notes
- You can't use `skvconf_find_element` to find a group element
- If a single key has been defined with multiple values, the last one is used,
  regardless of type (this is due to the find function exiting after finding
  the first element that matches and the parser returning the elements in reverse order).

## Configuration file syntax
A configuration file has a very basic syntax:
```
a = 3
b = "abc"
c = true
d {
    e = false
}
```

It is made up of key-value pairs as well as groups, which are basically namespaces.
In this example, `a`, `b` and `c` are simply key-value pairs accessible by
their respective names. `d` is a group which means it cannot be found by the
`skvconf_find_element` function and `e` is another key-value pair which is
accessible as `d.e`. You can also have nested groups.
