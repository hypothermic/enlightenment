#ifndef ENLIGHTENMENT_ROW_H
#define ENLIGHTENMENT_ROW_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_ROW(ptr) ((ERow *) ptr)

typedef struct _Row ERow;

/**
 *
 */
struct _Row {
    GPtrArray *primary_key_values;
    GPtrArray *data_values;
};

E_EXPORT void
e_row_free(ERow *row);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(ERow, e_row_free)

G_END_DECLS

#endif //ENLIGHTENMENT_ROW_H
