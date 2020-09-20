#include "enlightenment/common/primary_column.h"

E_EXPORT void
e_primary_column_free(EPrimaryColumn *data_column) {
    if (G_LIKELY(data_column)) {
        g_free(data_column);
    }
}
