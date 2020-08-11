#include <stdio.h>
#include <gio/gio.h>

#include "enlightenment/common/descriptor.h"
#include "enlightenment/common/server.h"

#include "enlightenment/server/exitstate.h"
#include "enlightenment/server/server.h"

static const gchar **descriptors = NULL;

static const GOptionEntry cmd_entries[] = {
        {"database",'d', G_OPTION_FLAG_NONE, G_OPTION_ARG_STRING_ARRAY, &descriptors,
                "Database descriptor file to load", " (can be repeated)"},
        {NULL}
};

EServerExitState
main(int argc, char **argv) {
    g_autoptr(GOptionContext) context = NULL;
    g_autoptr(GError)         error   = NULL;
    g_autoptr(EServer)        server  = NULL;

    context = g_option_context_new(" - Enlightenment Server Arguments");
    g_option_context_add_main_entries(context, cmd_entries, NULL);
    if (G_UNLIKELY(!g_option_context_parse(context, &argc, &argv, &error))) {
        g_printerr("%s\n", error->message);
        return E_SERVER_EXIT_ERROR_ARGS;
    }

    server = e_server_new(g_main_context_get_thread_default());

    if (descriptors) {
        for (guint i = 0; descriptors[i]; i++) {
            g_autoptr(GFile) file = g_file_new_for_commandline_arg(descriptors[i]);

            // If the file does not exist, try to create an empty file.
            GFileOutputStream *temp_file_stream = g_file_create(file, G_FILE_CREATE_NONE, NULL, NULL);
            if (G_LIKELY(temp_file_stream)) {
                g_object_unref(temp_file_stream);
            }

            g_autoptr(EDescriptor) descriptor = e_descriptor_from_file(file, &error);
            if (G_UNLIKELY(descriptor == NULL)) {
                g_warning("Failed to reconstruct descriptor from file %s", g_file_get_path(file));
                break;
            }

            // TODO construct database from this
            g_warning("DB NAME: %s", descriptor->name);
        }
    }

    g_main_loop_run(server->main_loop);
    g_main_loop_unref(server->main_loop);

    return E_SERVER_EXIT_SUCCESS;
}