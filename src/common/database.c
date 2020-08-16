#include "enlightenment/common/database.h"

struct _Database {
    const gchar *name;

    E_INTERNAL(const GPtrArray *tables);
};

E_EXPORT E_NON_NULL EDatabase *
e_database_new(void) {
    return g_new0(EDatabase, 1);
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

    database->name = g_strdup(descriptor->name);
    database->tables = g_ptr_array_new();

    // TODO reconstruct tables

    return database;
})
