#ifndef ENLIGHTENMENT_DATA_COLUMN_H
#define ENLIGHTENMENT_DATA_COLUMN_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_DATA_COLUMN(ptr) ((EDataColumn *) ptr)

typedef struct _DataColumn EDataColumn;

/**
 *
 */
struct _DataColumn {
    const gchar *name;

    /**
     * Size in bytes.
     */
    gulong size;
    gpointer data;
};

E_EXPORT void
e_data_column_free(EDataColumn *data_column);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EDataColumn, e_data_column_free)

G_END_DECLS

#endif //ENLIGHTENMENT_DATA_COLUMN_H
