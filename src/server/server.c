#include "build/unused.h"

#include "enlightenment/common/server.h"
#include "enlightenment/server/server.h"

EServer *
e_server_new(GMainContext *context) {
    EServer *server = g_new0(EServer, 1);

    server->databases = g_ptr_array_new();
    server->main_loop = g_main_loop_new(context, FALSE);

    return server;
}

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