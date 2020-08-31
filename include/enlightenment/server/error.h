#ifndef ENLIGHTENMENT_SERVER_ERROR_H
#define ENLIGHTENMENT_SERVER_ERROR_H

#include <glib.h>

G_BEGIN_DECLS

typedef enum {

    /**
     * Error while opening/initializing the module.
     */
    E_SERVER_ERROR_MODULE_INIT,

    /**
     * Could not find the initialize function symbol.
     *     (make sure you've dllexported it or visibility is public.)
     */
    E_SERVER_ERROR_MODULE_FUNC,

} EnlightenmentServerError;

#define ENLIGHTENMENT_SERVER_ERROR (enlightenment_server_error_quark())

extern GQuark
enlightenment_server_error_quark(void);

G_END_DECLS

#endif //ENLIGHTENMENT_SERVER_ERROR_H
