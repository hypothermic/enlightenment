#ifndef ENLIGHTENMENT_ENGINE_IMH_ERROR_H
#define ENLIGHTENMENT_ENGINE_IMH_ERROR_H

#include <glib.h>

G_BEGIN_DECLS

typedef enum {

    /**
     * Table format is unsupported by IMH.
     */
    E_IMH_ERROR_TABLE_UNSUPPORTED,

    /**
     * Table does not have any primary columns.
     */
    E_IMH_ERROR_TABLE_NO_PRIMARY_COLUMNS,

    /**
     * User provided an invalid destination for storing the function result.
     */
    E_IMH_ERROR_FUNCTION_RESULT_PTR,

    /**
     * No more heap memory available.
     */
    E_IMH_ERROR_OUT_OF_MEMORY,

} EnlightenmentImhError;

#define ENLIGHTENMENT_IMH_ERROR (enlightenment_imh_error_quark())

extern GQuark
enlightenment_imh_error_quark(void);

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_IMH_ERROR_H
