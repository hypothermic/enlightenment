#include "enlightenment/server/driver.h"

#define __STRINGIFY(V) #V
#define __ESCAPE(X) __STRINGIFY(X)

#define E_DRIVER_INIT_FUNC_STR __ESCAPE(E_DRIVER_INIT_FUNC)

#define g_module_try_close(module, file_path) \
        G_STMT_START { \
            if (!g_module_close(module)) { \
                g_warning("Failed to close module %s: %s", file_path, g_module_error()); \
            } \
        } G_STMT_END \

EDriver *
e_server_load_driver_from_file(EServer *server,
                               GFile *file,
                               GError **error) {
    g_autofree gchar* file_path = g_file_get_path(file);
    GModule *module = g_module_open(file_path, G_MODULE_BIND_LOCAL);

    if (!module) {
        g_set_error(error, ENLIGHTENMENT_SERVER_ERROR, E_SERVER_ERROR_MODULE_INIT,
                    "Failed to open driver module at %s: %s", g_file_get_path(file), g_module_error());
    }

    EDriverInitFunc init_func;

    if (!g_module_symbol(module, E_DRIVER_INIT_FUNC_STR, (gpointer *) &init_func)) {
        g_set_error(error, ENLIGHTENMENT_SERVER_ERROR, E_SERVER_ERROR_MODULE_FUNC,
                    "Could not find function symbol " E_DRIVER_INIT_FUNC_STR " in module %s: %s", file_path, g_module_error());

        g_module_try_close(module, file_path);

        return FALSE;
    }

    if (init_func == NULL) {
        g_set_error(error, ENLIGHTENMENT_SERVER_ERROR, E_SERVER_ERROR_MODULE_FUNC,
                    "Function symbol " E_DRIVER_INIT_FUNC_STR " is NULL in module %s", file_path);

        g_module_try_close(module, file_path);

        return FALSE;
    }

    return init_func(server, error);
}

#undef __STRINGIFY
#undef __ESCAPE
