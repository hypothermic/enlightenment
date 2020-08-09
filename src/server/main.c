#include <stdio.h>
#include <gio/gio.h>

#include "enlightenment/common/descriptor.h"
#include "enlightenment/common/server.h"

#include "enlightenment/server/exitstate.h"
#include "enlightenment/server/server.h"

static gchar** descriptors = NULL;

static GOptionEntry cmd_entries[] = {
        {"database",'d', G_OPTION_FLAG_NONE, G_OPTION_ARG_STRING_ARRAY, &descriptors,
                "Database descriptor file to load", " (can be repeated)"},
        {NULL}
};

EServerExitState
main(int argc, char **argv) {
    GOptionContext  *context;
    GError          *error = NULL;
    EServer         *server;

    context = g_option_context_new(" - Enlightenment Server Arguments");
    g_option_context_add_main_entries(context, cmd_entries, NULL);
    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_printerr("%s\n", error->message);
        return E_SERVER_EXIT_ERROR_ARGS;
    }

    server = e_server_new(g_main_context_get_thread_default());

    if (descriptors) {
        for (int i = 0; descriptors[i]; i++) {
            printf("Loading descriptor %s\n", descriptors[i]);
            GFile *file = g_file_new_for_commandline_arg(descriptors[i]);

            EDescriptor *descriptor = e_descriptor_from_file(file);

            g_free(file);
        }
    }

    g_main_loop_run(server->main_loop);
    g_main_loop_unref(server->main_loop);

    return E_SERVER_EXIT_SUCCESS;
}