#include "enlightenment/common/table.h"

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_table_get_columns(ETable *table) {
    return table->columns;
})