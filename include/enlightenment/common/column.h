#ifndef ENLIGHTENMENT_COLUMN_H
#define ENLIGHTENMENT_COLUMN_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_COLUMN(ptr) ((EColumn *) ptr)

typedef struct _Column EColumn;

/**
 *
 */
struct _Column {
    const gchar *name;

    /**
     * Size in bits.
     *
     * Multiply by 8 to get the size in bytes.
     */
    gulong size;
};

E_EXPORT void
e_column_free(EColumn *column);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EColumn, e_column_free)

G_END_DECLS

#endif //ENLIGHTENMENT_COLUMN_H
