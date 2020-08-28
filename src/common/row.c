#include "enlightenment/common/row.h"

E_EXPORT void
e_row_free(ERow *row) {
    if (G_LIKELY(row)) {
        g_free(row);
    }
}
