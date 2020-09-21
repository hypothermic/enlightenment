#ifndef ENLIGHTENMENT_DATA_COLUMN_H
#define ENLIGHTENMENT_DATA_COLUMN_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_DATA_COLUMN(ptr) ((EDataColumn *) ptr)

typedef struct _DataColumn EDataColumn;

/**
 * Data columns should only be used to store data that can be retrieved by using the Primary Key Columns.<br />
 * <br />
 * Therefore, data columns cannot be filtered upon.
 */
struct _DataColumn {
    const gchar *name;

    /**
     * Size in bits.
     */
    gulong cell_size;
};

/**
 * Allocates a new EDataColumn and sets it's attributes to the ones provided in the arguments.<br />
 * <br />
 * May return NULL if not enough memory was available (depends on your libc's malloc implementation)
 *
 * @return An allocated EDataColumn or NULL if error
 */
E_EXPORT EDataColumn *
e_data_column_new(const gchar *name,
                  gulong cell_size);

E_EXPORT void
e_data_column_free(EDataColumn *data_column);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EDataColumn, e_data_column_free)

G_END_DECLS

#endif //ENLIGHTENMENT_DATA_COLUMN_H
