/*
 * This driver opens and listens on a socket and utilizes the
 * Enlightenment Remote Connection Protocol (ERCP) to communicate with clients.
 */

#include "enlightenment/api/driver.h"

#define __MODULE_NAME "nl.hypothermic.enlightenment.ercp"

#define __OPTION_GROUP_NAME "ercp"
#define __OPTION_GROUP_DESCRIPTION "Options to configure the ERCP network socket driver"

static GOptionGroup *
e_ercp_get_option_group(const EServer *server);

static gboolean
e_ercp_free(EDriver *driver,
            const EServer *server,
            GError **error);

static guint16 port;

static const GOptionEntry option_entries[] = {
        {"port", 'p', G_OPTION_FLAG_NONE, G_OPTION_ARG_INT, &port,
                "TCP/IP port to listen on (1024-65535)", NULL},
        {NULL}
};

E_EXPORT EDriver *
E_DRIVER_INIT_FUNC(E_UNUSED const EServer *server,
                   E_UNUSED GError **error) {
    return e_driver_new(__MODULE_NAME,
                        e_ercp_get_option_group,
                        e_ercp_free);
}

static GOptionGroup *
e_ercp_get_option_group(E_UNUSED const EServer *server) {
    static GOptionGroup *group = NULL;

    if (!group) {
        group = g_option_group_new(__OPTION_GROUP_NAME,
                                   __OPTION_GROUP_DESCRIPTION,
                                   __OPTION_GROUP_DESCRIPTION,
                                   NULL,
                                   NULL);

        g_option_group_add_entries(group, option_entries);
    }

    return group;
}

static gboolean
e_ercp_free(EDriver *driver,
            E_UNUSED const EServer *server,
            E_UNUSED GError **error) {
    g_free(driver);

    return TRUE;
}

#undef __MODULE_NAME
#undef __OPTION_GROUP_NAME
#undef __OPTION_GROUP_DESCRIPTION
