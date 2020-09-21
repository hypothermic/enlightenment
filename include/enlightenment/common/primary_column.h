#ifndef ENLIGHTENMENT_PRIMARY_COLUMN_H
#define ENLIGHTENMENT_PRIMARY_COLUMN_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_PRIMARY_COLUMN(ptr) ((EPrimaryColumn *) ptr)

typedef gint64
(* EPrimaryColumnIntValueFunc) (gpointer key_data, gpointer convert_func_data);

typedef struct _PrimaryColumn EPrimaryColumn;

/**
 * A primary column is a special column which is used as a primary key.<br />
 * <br />
 * The data stored in this column can always be converted to an integer in some way, shape or form.
 */
struct _PrimaryColumn {
    const gchar *name;

    EPrimaryColumnIntValueFunc convert_func;
    gpointer convert_func_data;
};

/**
 * Convenience function for creating a new Primary Column with 64-bit signed integer data type.<br />
 * <br />
 * Under the hood, this function calls <i>e_primary_column_new</i> with the appropriate conversion methods.
 *
 * @return An allocated EPrimaryColumn or NULL if error
 */
E_EXPORT EPrimaryColumn *
e_primary_column_new_s64(const gchar *name);

/**
 * Allocates a new EPrimaryColumn and sets it's attributes to the ones provided in the arguments.<br />
 * <br />
 * May return NULL if not enough memory was available (depends on your libc's malloc implementation)
 *
 * @return An allocated EPrimaryColumn or NULL if error
 */
E_EXPORT EPrimaryColumn *
e_primary_column_new(const gchar *name,
                     EPrimaryColumnIntValueFunc convert_func,
                     gpointer convert_func_data);

E_EXPORT void
e_primary_column_free(EPrimaryColumn *primary_column);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EPrimaryColumn, e_primary_column_free)

G_END_DECLS

#endif //ENLIGHTENMENT_PRIMARY_COLUMN_H
