#include "build/integrity.h"

#include "enlightenment/common/server.h"

E_EXPORT GPtrArray *
e_server_get_databases(EServer *server) {
    return server->databases;
}

E_EXPORT gboolean
e_server_add_database(EServer *server,
                      EDatabase *database,
                      E_UNUSED GError **error) {
    g_ptr_array_add(server->databases, database);

    return TRUE;
}

E_EXPORT void
e_server_free(EServer *server) {
    if (G_LIKELY(server)) {
        g_free(server);
    }
}
