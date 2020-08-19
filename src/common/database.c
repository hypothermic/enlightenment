#include "enlightenment/common/database.h"

#include "enlightenment/common/error.h"

struct _Database {
    GQuark name;

    E_INTERNAL(const GPtrArray *tables);
};

E_EXPORT E_NON_NULL EDatabase *
e_database_new(void) {
    return g_new0(EDatabase, 1);
}

E_EXPORT const gchar *
e_database_get_name(EDatabase *database) {
    return g_quark_to_string(database->name);
}

E_EXPORT GQuark
e_database_get_name_as_quark(EDatabase *database) {
    return database->name;
}

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_database_get_tables(EDatabase *database) {
    return database->tables;
})

E_USE_INTERNAL(
E_EXPORT EDatabase *
e_database_for_descriptor(const EDescriptor *const descriptor,
                          GError **error) {
    e_return_error_if_null(descriptor);

    EDatabase *database = e_database_new();

    database->name = g_quark_from_string(descriptor->name);
    database->tables = g_ptr_array_new();

    // TODO reconstruct tables

    return database;
})

E_EXPORT void
e_database_free(EDatabase *database) {
    if (G_LIKELY(database)) {
        g_free(database);
    }
}
