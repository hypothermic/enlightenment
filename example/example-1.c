#include <glib.h>

#include <enlightenment/enlightenment.h>

/*
 * This code illustrates how to create a simple database with Enlightenment.
 * We will be using the "imop" in-memory engine, but you can swap the engine with your preference.
 *
 * Because Enlightenment uses parallel computation for IO, you will need to run a GMainContext (as seen in the example).
 * You may use this GMainContext for your own operations too if you'd like to do so.
 *
 * The table we'll be creating has three columns: UserID (int64), UserScore (int16),
 */

int
main(int argc, gchar **argv) {
    g_autoptr(GError)    error    = NULL;
    g_autoptr(EServer)   server   = NULL;
    g_autoptr(EDatabase) database = NULL;
    g_autoptr(ETable)    table = NULL;

    server = e_server_new(g_main_context_get_thread_default());

    database = e_database_new();

    e_server_add_database()

    g_main_loop_run(server->main_loop);
    g_main_loop_unref(server->main_loop);

    return EXIT_SUCCESS;
}
