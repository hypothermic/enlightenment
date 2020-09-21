#include "enlightenment/common/data_column.h"

E_EXPORT EDataColumn *
e_data_column_new(const gchar *name,
                  gulong cell_size) {
    EDataColumn *result = g_new0(EDataColumn, 1);

    if (result) {
        result->name = name;
        result->cell_size = cell_size;
    }

    return result;
}

E_EXPORT void
e_data_column_free(EDataColumn *data_column) {
    if (G_LIKELY(data_column)) {
        g_free(data_column);
    }
}
