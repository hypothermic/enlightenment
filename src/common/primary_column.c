#include "enlightenment/common/primary_column.h"

#include "build/integrity.h"

static gint64
_s64_primary_key_convert(gpointer key_data,
                         gpointer convert_func_data);

E_EXPORT EPrimaryColumn *
e_primary_column_new_s64(const gchar *name) {
    return e_primary_column_new(name, _s64_primary_key_convert, NULL);
}

E_EXPORT EPrimaryColumn *
e_primary_column_new(const gchar *const name,
                     EPrimaryColumnIntValueFunc const convert_func,
                     gpointer convert_func_data) {
    EPrimaryColumn *result = g_new0(EPrimaryColumn, 1);

    if (G_LIKELY(result)) {
        result->name = name;
        result->convert_func = convert_func;
        result->convert_func_data = convert_func_data;
    }

    return result;
}

E_EXPORT void
e_primary_column_free(EPrimaryColumn *data_column) {
    if (G_LIKELY(data_column)) {
        g_free(data_column);
    }
}

static gint64
_s64_primary_key_convert(gpointer const key_data,
                         E_UNUSED gpointer convert_func_data) {
    return *((gint64 *) key_data);
}
