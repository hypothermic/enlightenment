#include "enlightenment/common/column.h"

E_EXPORT void
e_column_free(EColumn *column) {
    if (G_LIKELY(column)) {
        g_free(column);
    }
}