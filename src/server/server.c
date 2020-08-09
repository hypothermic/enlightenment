#include "build/unused.h"

#include "enlightenment/common/server.h"
#include "enlightenment/server/server.h"

EServer *
e_server_new(GMainContext *context) {
    EServer *server = g_new0(EServer, 1);

    server->main_loop = g_main_loop_new(context, FALSE);

    return server;
}

E_EXPORT GSList *
e_server_get_databases(EServer *server) {
    return server->databases;
}

E_EXPORT gboolean
e_server_add_database(EServer *server,
                      EDatabase *database,
                      E_UNUSED GError **error) {
    server->databases = g_slist_append(server->databases, database);

    return TRUE;
}