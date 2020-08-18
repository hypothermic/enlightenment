#include "enlightenment/common/table.h"

struct _Table {
    GQuark name;

    E_INTERNAL(const GPtrArray *columns);
};

E_EXPORT E_NON_NULL ETable *
e_table_new(void) {
    return g_new0(ETable, 1);
}

E_USE_INTERNAL(
E_EXPORT gboolean
e_table_init(ETable *table,
             const gchar *const name) {
    g_return_val_if_fail(table, FALSE);

    table->name = g_quark_from_string(name);
    table->columns = g_ptr_array_new();

    return TRUE;
})

E_EXPORT const gchar *
e_table_get_name(ETable *table) {
    g_return_val_if_fail(table, NULL);

    return g_quark_to_string(table->name);
}

E_EXPORT GQuark
e_table_get_name_as_quark(ETable *table) {
    g_return_val_if_fail(table, FALSE);

    return table->name;
}

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_table_get_columns(ETable *table) {
    return table->columns;
})

E_EXPORT void
e_table_free(ETable *table) {
    if (G_LIKELY(table)) {
        g_free(table);
    }
}
