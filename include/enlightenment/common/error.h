#ifndef ENLIGHTENMENT_ERROR_H
#define ENLIGHTENMENT_ERROR_H

#include <glib.h>

typedef enum {
    E_ERROR_INVALID_PTR,
} EnlightenmentError;

#define ENLIGHTENMENT_ERROR (enlightenment_error_quark())

#define e_return_error_if_null(ptr) \
        G_STMT_START { \
            if (G_LIKELY (ptr)) \
                { } \
            else \
                { \
                    g_set_error(error, ENLIGHTENMENT_ERROR, E_ERROR_INVALID_PTR, \
                                "Invalid %s pointer passed to %s", #ptr, __func__); \
                    return FALSE; \
                } \
        } G_STMT_END \

#define e_return_error_if_null_msg(ptr, msg) \
        G_STMT_START { \
            if (G_LIKELY (ptr)) \
                { } \
            else \
                { \
                    g_set_error(error, ENLIGHTENMENT_ERROR, E_ERROR_INVALID_PTR, \
                                "%s was null in func %s, message: %s", #ptr, __func__, msg); \
                    return FALSE; \
                } \
        } G_STMT_END \

extern GQuark
enlightenment_error_quark(void);

#endif //ENLIGHTENMENT_ERROR_H
