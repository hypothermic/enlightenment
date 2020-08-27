#include <stdio.h>
#include <gio/gio.h>
#include <locale.h>

#include "enlightenment/api/driver.h"

#include "enlightenment/common/descriptor.h"
#include "enlightenment/common/server.h"

#include "enlightenment/server/exitstate.h"
#include "enlightenment/server/server.h"

static gboolean
e_server_add_descriptors(EServer *server,
                         const gchar **descriptors,
                         GError **error);

static void
g_option_context_add_driver_options(EDriver *driver,
                                    GOptionContext *option_context);

static const gchar **_descriptors = NULL;

static const GOptionEntry cmd_entries[] = {
        {"database",'d', G_OPTION_FLAG_NONE, G_OPTION_ARG_STRING_ARRAY, &_descriptors,
                "Database descriptor file to load", " (can be repeated)"},
        {NULL}
};

EServerExitState
main(int argc, char **argv) {
    g_autoptr(GOptionContext) context = NULL;
    g_autoptr(GError)         error   = NULL;
    g_autoptr(EServer)        server  = NULL;
    g_autoptr(GPtrArray)      drivers = g_ptr_array_new();

    if (!setlocale(LC_ALL, "")) {
        g_error("Failed to set locale to system default locale");
    }

    // TODO load drivers;; add to the drivers ptr array

    server = e_server_new(g_main_context_get_thread_default());

    context = g_option_context_new(" - Enlightenment Server Arguments");
    g_option_context_add_main_entries(context, cmd_entries, NULL);

    g_ptr_array_foreach(drivers, (GFunc) g_option_context_add_driver_options, context);

    if (G_UNLIKELY(!g_option_context_parse(context, &argc, &argv, &error))) {
        g_printerr("%s\n", error->message);
        return E_SERVER_EXIT_ERROR_ARGS;
    }

    if (_descriptors) {
        if (!e_server_add_descriptors(server, _descriptors, &error)) {
            g_critical("Failed to parse and add descriptors, error: %s (%d)", error->message, error->code);
        }
    }

    g_main_loop_run(server->main_loop);
    g_main_loop_unref(server->main_loop);

    return E_SERVER_EXIT_SUCCESS;
}

static gboolean
e_server_add_descriptors(EServer *server,
                         const gchar **descriptors,
                         GError **error) {
    for (guint i = 0; descriptors[i]; i++) {
        g_autoptr(GFile) file = g_file_new_for_commandline_arg(descriptors[i]);

        // If the file does not exist, try to create an empty file.
        GFileOutputStream *temp_file_stream = g_file_create(file, G_FILE_CREATE_NONE, NULL, NULL);
        if (G_LIKELY(temp_file_stream)) {
            g_object_unref(temp_file_stream);
        }

        g_autoptr(EDescriptor) descriptor = e_descriptor_from_file(file, error);
        if (G_UNLIKELY(descriptor == NULL)) {
            return FALSE;
        }

        EDatabase *database = e_database_for_descriptor(descriptor, error);
        if (G_UNLIKELY(database == NULL)) {
            return FALSE;
        }

        g_return_val_if_fail(e_server_add_database(server, database, error), FALSE);
    }

    return TRUE;
}

static void
g_option_context_add_driver_options(EDriver *driver,
                                    GOptionContext *option_context) {
    EDriverGetOptionsFunc options_func = e_driver_get_options_func(driver);
    GOptionGroup *option_group = options_func(NULL);

    g_option_context_add_group(option_context, option_group);
}
