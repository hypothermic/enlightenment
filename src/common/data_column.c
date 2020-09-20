#include "enlightenment/common/data_column.h"

E_EXPORT void
e_data_column_free(EDataColumn *data_column) {
    if (G_LIKELY(data_column)) {
        g_free(data_column);
    }
}
