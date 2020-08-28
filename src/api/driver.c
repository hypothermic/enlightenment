#include "enlightenment/api/driver.h"

struct _Driver {
    /* TODO*/
    const gchar *id;

    EDriverGetOptionsFunc get_options_func;
    EDriverFreeFunc free_func;
};

E_EXPORT const gchar *
e_driver_get_id(EDriver *driver) {
    return driver->id;
}

E_EXPORT EDriverGetOptionsFunc
e_driver_get_options_func(EDriver *driver) {
    return driver->get_options_func;
}

E_EXPORT EDriverFreeFunc
e_driver_get_free_func(EDriver *driver) {
    return driver->free_func;
}
