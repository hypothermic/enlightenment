#include "enlightenment/common/row.h"

E_EXPORT ERow *
e_row_new(GPtrArray *primary_key_values,
          GPtrArray *data_values) {
    ERow *row = g_new0(ERow, 1);

    if (row) {
        row->primary_key_values = primary_key_values;
        row->data_values = data_values;
    }

    return row;
}

E_EXPORT void
e_row_free(ERow *row) {
    if (G_LIKELY(row)) {
        g_free(row);
    }
}
