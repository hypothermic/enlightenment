#include "enlightenment/api/driver.h"

struct _Driver {
    /**
     * An identifier describing the manufacturer and name of the driver.<br />
     * <br />
     * Preferably, the Java package naming standard should be used.
     * See https://en.wikipedia.org/wiki/Java_package#Package_naming_conventions
     * or https://docs.oracle.com/javase/tutorial/java/package/namingpkgs.html
     * if the Oracle hasn't gone bankrupt yet and their website is still online.
     */
    const gchar *id;

    EDriverGetOptionsFunc get_options_func;
    EDriverFreeFunc free_func;
};

E_EXPORT EDriver *
e_driver_new(const gchar *id,
             EDriverGetOptionsFunc get_options_func,
             EDriverFreeFunc free_func) {
    EDriver *driver = g_new0(EDriver, 1);

    driver->id = id;
    driver->get_options_func = get_options_func;
    driver->free_func = free_func;

    return driver;
}

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
