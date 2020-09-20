#include <glib.h>

#include <enlightenment/enlightenment.h>

/*
 * This code shows the most simple usage of Enlightenment.
 * I wanted to keep this code as simple as possible, so it does not cover topics such as multithreading, parallel IO and sharding.
 * Please don't use this code in performance critical situations; it'll be slow because the calls to EEngine are performing blocking IO!
 *
 * Here you can see rows being inserted and retrieved from a Table.
 *
 * The table we'll be creating has three columns: UserID (int64), UserDeaths (int16), UserScore (int16), with UserID being the only primary key.
 */
int
main(E_UNUSED int argc, E_UNUSED gchar **argv) {
    g_autoptr(GError)    error = NULL;
    g_autoptr(ETable)    table = NULL;
    table = e_table_new();

    g_autoptr(GPtrArray) primary_columns = g_ptr_array_new();
    g_autoptr(GPtrArray) data_columns = g_ptr_array_new();

    if (!e_table_init(table, "User", &error)) {
        g_error("Error while initializing table: %s", error->message);
    }

    // TODO add columns
    // TODO create engine
    // TODO insert rows
    // TODO retrieve rows

    return EXIT_SUCCESS;
}
