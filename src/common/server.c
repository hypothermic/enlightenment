#include "enlightenment/common/server.h"

E_EXPORT void
e_server_free(EServer *server) {
    if (server) {
        g_free(server);
    }
}