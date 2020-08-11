#include "enlightenment/common/server.h"
#include "enlightenment/server/server.h"

E_EXPORT EServer *
e_server_new(GMainContext *context) {
    EServer *server = g_new0(EServer, 1);

    server->databases = g_ptr_array_new();
    server->main_loop = g_main_loop_new(context, FALSE);

    return server;
}
