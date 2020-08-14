#include "enlightenment/common/database.h"

E_EXPORT EDatabase *
e_database_for_descriptor(const EDescriptor *const descriptor,
                          GError **error) {
    EDatabase *database = g_new0(EDatabase, 1);

    database->name = g_strdup(descriptor->name);

    // TODO reconstruct tables

    return database;
}
