#ifndef ENLIGHTENMENT_PRIMARY_COLUMN_H
#define ENLIGHTENMENT_PRIMARY_COLUMN_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_PRIMARY_COLUMN(ptr) ((EPrimaryColumn *) ptr)

typedef gint64
(* EPrimaryColumnIntValueFunc) (gpointer key_data);

typedef struct _PrimaryColumn EPrimaryColumn;

/**
 * A primary column is a special column which is used as a primary key.
 *
 * The data stored in this column can always be converted to an integer in some way, shape or form.
 */
struct _PrimaryColumn {
    const gchar *name;

    gpointer key_data;
    EPrimaryColumnIntValueFunc convert_func;
};

E_EXPORT void
e_primary_column_free(EPrimaryColumn *primary_column);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EPrimaryColumn, e_primary_column_free)

G_END_DECLS

#endif //ENLIGHTENMENT_PRIMARY_COLUMN_H
