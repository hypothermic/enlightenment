#include "enlightenment/common/database.h"

E_USE_INTERNAL(
E_EXPORT const GPtrArray *
e_database_get_tables(EDatabase *database) {
    return database->tables;
})

E_USE_INTERNAL(
E_EXPORT EDatabase *
e_database_for_descriptor(const EDescriptor *const descriptor,
                          E_UNUSED GError **error) {
    EDatabase *database = g_new0(EDatabase, 1);

    database->name = g_strdup(descriptor->name);
    database->tables = g_ptr_array_new();

    // TODO reconstruct tables

    return database;
})
