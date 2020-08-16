#include "enlightenment/common/table.h"

struct _Table {
    GQuark name;

    E_INTERNAL(const GPtrArray *columns);
};

E_EXPORT E_NON_NULL ETable *
e_table_new(void) {
    return g_new0(ETable, 1);
}

E_EXPORT const gchar *
e_table_get_name(ETable *table) {
    return g_quark_to_string(table->name);
}

E_EXPORT GQuark
e_table_get_name_as_quark(ETable *table) {
    return table->name;
}

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_table_get_columns(ETable *table) {
    return table->columns;
})
