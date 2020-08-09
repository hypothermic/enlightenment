#ifndef ENLIGHTENMENT_COMMON_SERVER_H
#define ENLIGHTENMENT_COMMON_SERVER_H

#include <glib.h>

#include "build/exports.h"
#include "build/unused.h"

#include "database.h"

#define E_SERVER(ptr) ((EServer *) ptr)

typedef struct _Server EServer;

struct _Server {
    GMainLoop *main_loop;
    GSList *databases;
};

E_EXPORT GSList *
e_server_get_databases(EServer *server);

/**
 * Adds a database to the server.<br />
 * <br />
 * Returns FALSE and allocates <i>error</i> upon error.
 */
E_EXPORT gboolean
e_server_add_database(EServer *server,
                      EDatabase *database,
                      E_UNUSED GError **error);

#endif //ENLIGHTENMENT_COMMON_SERVER_H
