#include <glib.h>

#include <enlightenment/enlightenment.h>

/*
 * This code shows the basic usage of Enlightenment.
 * It uses a simple in-memory engine (like MEMORY or HEAP in MySQL).
 *
 * I wanted to keep this code as simple as possible, so it does not cover topics such as multithreading, parallel IO and sharding.
 * Please don't use this code in performance critical situations; it'll be slow because the calls to EEngine are performing blocking IO!
 *
 * Here you can see rows being inserted and retrieved from a Table.
 *
 * The table we'll be creating has three columns: UserID (int64), UserDeaths (int16), UserScore (int16), with UserID being the only primary key.
 */
int
main(E_UNUSED int argc, E_UNUSED gchar **argv) {
    g_autoptr(GError)           error = NULL;
    g_autoptr(ETable)           table = NULL;
    g_autoptr(GPtrArray)        primary_columns = g_ptr_array_new();
    g_autoptr(GPtrArray)        data_columns = g_ptr_array_new();
    g_autoptr(EPrimaryColumn)   column_userid = NULL;
    g_autoptr(EDataColumn)      column_userdeaths = NULL, column_userscore = NULL;

    table = e_table_new();
    column_userid = e_primary_column_new_s64("UserID");
    column_userdeaths = e_data_column_new("UserDeaths", 16);
    column_userscore = e_data_column_new("UserScore", 16);

    g_ptr_array_add(primary_columns, column_userid);
    g_ptr_array_add(data_columns, column_userdeaths);
    g_ptr_array_add(data_columns, column_userscore);

    if (!e_table_init(table, "User", primary_columns, data_columns, &error)) {
        g_error("Error while initializing table: %s", error->message);
    }

    // TODO create engine instance
    // TODO insert rows
    // TODO retrieve rows

    return EXIT_SUCCESS;
}
