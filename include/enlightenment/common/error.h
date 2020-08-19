#ifndef ENLIGHTENMENT_ERROR_H
#define ENLIGHTENMENT_ERROR_H

typedef enum {
    E_ERROR_INVALID_PTR,
} EnlightenmentError;

G_DEFINE_QUARK(enlightenment-error-quark, enlightenment_error)

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

#endif //ENLIGHTENMENT_ERROR_H
