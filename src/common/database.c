#include "enlightenment/common/database.h"

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
                          E_UNUSED GError **error) {
    EDatabase *database = e_database_new();

    database->name = g_quark_from_string(descriptor->name);
    database->tables = g_ptr_array_new();

    // TODO reconstruct tables

    return database;
})
