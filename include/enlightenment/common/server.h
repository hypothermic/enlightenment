#ifndef ENLIGHTENMENT_COMMON_SERVER_H
#define ENLIGHTENMENT_COMMON_SERVER_H

#include <glib.h>

#include "build/exports.h"

#include "database.h"

G_BEGIN_DECLS

#define E_SERVER(ptr) ((EServer *) ptr)

typedef struct _Server EServer;

struct _Server {
    GMainLoop *main_loop;
    GPtrArray *databases;
};

E_EXPORT GPtrArray *
e_server_get_databases(EServer *server);

/**
 * Adds a database to the server.<br />
 * <br />
 * Returns FALSE and allocates <i>error</i> upon error.
 */
E_EXPORT gboolean
e_server_add_database(EServer *server,
                      EDatabase *database,
                      GError **error);

E_EXPORT void
e_server_free(EServer *server);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EServer, e_server_free)

G_END_DECLS

#endif //ENLIGHTENMENT_COMMON_SERVER_H
