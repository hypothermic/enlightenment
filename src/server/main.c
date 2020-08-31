#include <stdio.h>
#include <locale.h>
#include <gio/gio.h>

#include "enlightenment/api/driver.h"

#include "enlightenment/common/descriptor.h"
#include "enlightenment/common/server.h"

#include "enlightenment/server/driver.h"
#include "enlightenment/server/error.h"
#include "enlightenment/server/exitstate.h"
#include "enlightenment/server/server.h"

// TODO add config options for these (or cmdline args)
#define CLI_DEFAULT_DRIVER_DIR_PATH "."
#define CLI_DEFAULT_DRIVER_SUFFIX   ".edm." G_MODULE_SUFFIX
#define CLI_DEFAULT_ENGINE_DIR_PATH "."
#define CLI_DEFAULT_ENGINE_SUFFIX   ".eem." G_MODULE_SUFFIX

static gboolean
e_server_add_descriptors(EServer *server,
                         const gchar **descriptors,
                         GError **error);

static void
e_server_free_driver(EDriver *driver,
                     EServer *server);

static void
g_option_context_add_driver_options(EDriver *driver,
                                    GOptionContext *option_context);

static gboolean
_load_drivers(GPtrArray *drivers,
              EServer *server,
              GError **error);

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

    if (G_UNLIKELY(!setlocale(LC_ALL, ""))) {
        g_error("Failed to set locale to system default locale");
    }

    server = e_server_new(g_main_context_get_thread_default());

    if (G_UNLIKELY(!g_module_supported())) {
        g_error("Modules not supported on this platform");
        return E_SERVER_EXIT_ERROR_MODULES_UNSUPPORTED;
    }

    if (G_UNLIKELY(!_load_drivers(drivers, server, &error))) {
        g_error("Failed to load drivers, error: %s (%d)", error->message, error->code);
        return E_SERVER_EXIT_ERROR_LOAD_DRIVERS;
    }

    g_debug("Loaded %d drivers", drivers->len);

    context = g_option_context_new(" - Enlightenment Server Arguments");
    g_option_context_add_main_entries(context, cmd_entries, NULL);

    g_ptr_array_foreach(drivers, (GFunc) g_option_context_add_driver_options, context);

    if (G_UNLIKELY(!g_option_context_parse(context, &argc, &argv, &error))) {
        g_printerr("%s\n", error->message);
        return E_SERVER_EXIT_ERROR_ARGS;
    }

    if (G_LIKELY(_descriptors)) {
        if (!e_server_add_descriptors(server, _descriptors, &error)) {
            g_error("Failed to parse and add descriptors, error: %s (%d)", error->message, error->code);
        }
    }

    g_debug("Starting main loop");

    g_main_loop_run(server->main_loop);
    g_main_loop_unref(server->main_loop);

    g_debug("Cleaning up");

    g_ptr_array_foreach(drivers, (GFunc) e_server_free_driver, server);

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
e_server_free_driver(EDriver *driver,
                     EServer *server) {
    g_autoptr(GError) error;
    EDriverFreeFunc free_func = e_driver_get_free_func(driver);

    if (!free_func(driver, server, &error)) {
        g_error("Failed to free driver %s: %s (%d)", e_driver_get_id(driver), error->message, error->code);
    }

    // TODO we should g_module_close here
}

static void
g_option_context_add_driver_options(EDriver *driver,
                                    GOptionContext *option_context) {
    EDriverGetOptionsFunc options_func = e_driver_get_options_func(driver);
    GOptionGroup *option_group = options_func(NULL);

    g_option_context_add_group(option_context, option_group);
}

static gboolean
_load_drivers(GPtrArray *drivers,
              EServer *server,
              GError **error) {
    g_autoptr(GError) local_error = NULL;
    g_autoptr(GFile) dir = g_file_new_for_path(CLI_DEFAULT_DRIVER_DIR_PATH);

    // Create the directory if it doesn't already exist.
    if (!g_file_make_directory_with_parents(dir, NULL, &local_error)
        && !g_error_matches(local_error, G_IO_ERROR, G_IO_ERROR_EXISTS)) {
        g_propagate_error(error, local_error);
        return FALSE;
    }

    {
        g_autofree gchar *current_path = g_file_get_path(dir);
        g_info("Searching in directory %s", current_path);
    }

    g_autoptr(GFileEnumerator) enumerator = g_file_enumerate_children(dir,
                                                                      G_FILE_ATTRIBUTE_STANDARD_NAME,
                                                                      G_FILE_QUERY_INFO_NONE,
                                                                      NULL,
                                                                      &local_error);

    if (!enumerator) {
        g_propagate_error(error, local_error);
        return FALSE;
    }

    GFileInfo* info;
    while ((info = g_file_enumerator_next_file(enumerator, NULL, NULL)) != NULL) {
        if (g_str_has_suffix(g_file_info_get_name(info), CLI_DEFAULT_DRIVER_SUFFIX)) {
            g_autoptr(GFile) file = g_file_enumerator_get_child(enumerator, info);

            EDriver *driver = e_server_load_driver_from_file(server, file, &local_error);

            if (!driver) {
                g_propagate_error(error, local_error);
                return FALSE;
            }

            g_ptr_array_add(drivers, driver);
        }

        g_object_unref(info);
    }

    return TRUE;
}
