#include <glib.h>

#include <enlightenment/enlightenment.h>
#include "../engine/imh/imh.h"

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
    g_autoptr(GError)           error               = NULL;
    g_autoptr(ETable)           table               = NULL;
    g_autoptr(GPtrArray)        primary_columns     = g_ptr_array_new();
    g_autoptr(GPtrArray)        data_columns        = g_ptr_array_new();
    g_autoptr(EPrimaryColumn)   column_userid       = NULL;
    g_autoptr(EDataColumn)      column_userdeaths   = NULL,
                                column_userscore    = NULL;
    const EEngine               *engine             = NULL;

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

    engine = e_imh_new(table, &error);
    if (!engine) {
        g_error("Error while initializing engine: %s", error->message);
    }

    g_autoptr(ERow)             row                 = NULL;
    g_autoptr(GPtrArray)        primary_key_values  = g_ptr_array_new();
    g_autoptr(GPtrArray)        data_values         = g_ptr_array_new();
    guint64                     userId              = 420;
    guint16                     userDeaths          = 6,
                                userScore           = 100;

    g_ptr_array_add(primary_key_values, &userId);
    g_ptr_array_add(data_values,        &userDeaths);
    g_ptr_array_add(data_values,        &userScore);

    row = e_row_new(primary_key_values, data_values);

    // Insert row with UserID=420, UserDeaths=6, UserScore=100
    if (!engine->row_create_func(table, row, NULL, &error)) {
        g_error("Error while creating a row: %s", error->message);
    }

    userId = 700;
    userDeaths = 1;
    userScore = 60;

    // Insert row with UserID=700, UserDeaths=1, UserScore=60
    if (!engine->row_create_func(table, row, NULL, &error)) {
        g_error("Error while creating a row: %s", error->message);
    }

    // TODO retrieve rows

    return EXIT_SUCCESS;
}
