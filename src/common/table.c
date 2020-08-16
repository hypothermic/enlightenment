#include "enlightenment/common/table.h"

struct _Table {
    const gchar *name;

    E_INTERNAL(const GPtrArray *columns);
};

E_EXPORT E_NON_NULL ETable *
e_table_new(void) {
    return g_new0(ETable, 1);
}

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_table_get_columns(ETable *table) {
    return table->columns;
})
