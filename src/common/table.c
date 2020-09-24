#include "enlightenment/common/data_column.h"
#include "enlightenment/common/table.h"

#include "enlightenment/common/error.h"

static void
_count_data_column_size(EDataColumn *data_column,
                        guint64 *size_ptr);

struct _Table {
    GQuark name;

    E_INTERNAL(const GPtrArray *primary_columns);
    E_INTERNAL(const GPtrArray *data_columns);
};

E_EXPORT E_NON_NULL ETable *
e_table_new(void) {
    return g_new0(ETable, 1);
}

E_USE_INTERNAL(
E_EXPORT gboolean
e_table_init(ETable *table,
             const gchar *const name,
             const GPtrArray *primary_columns,
             const GPtrArray *data_columns,
             GError **error) {
    e_return_error_if_null(table);

    table->name = g_quark_from_string(name);
    table->primary_columns = primary_columns;
    table->data_columns = data_columns;

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
e_table_get_primary_columns(const ETable *table) {
    return table->primary_columns;
})

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_table_get_data_columns(const ETable *table) {
    return table->data_columns;
})

E_EXPORT guint64
e_table_get_row_size(const ETable *table) {
    guint64 size = 0;

    size += e_table_get_primary_columns(table)->len * sizeof(guint64);

    // Discarding constness of the data col array is safe because foreach and _count_column_size do not modify it.
    g_ptr_array_foreach((GPtrArray *) e_table_get_data_columns(table),
                        (GFunc) _count_data_column_size,
                        &size);

    return size;
}

E_EXPORT void
e_table_free(ETable *table) {
    if (G_LIKELY(table)) {
        g_free(table);
    }
}

static void
_count_data_column_size(EDataColumn* data_column,
                        guint64 *size_ptr) {
    *size_ptr += data_column->cell_size;
}
