#include "enlightenment/common/server.h"

E_EXPORT void
e_server_free(EServer *server) {
    if (G_LIKELY(server)) {
        g_free(server);
    }
}