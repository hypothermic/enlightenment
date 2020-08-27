#include "enlightenment/api/driver.h"

struct _Driver {
    /* TODO*/
    const gchar *id;

    EDriverGetOptionsFunc get_options_func;
    EDriverFreeFunc free_func;
};
