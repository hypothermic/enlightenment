#include <glib.h>

#include <enlightenment/enlightenment.h>
#include "../engine/imh/imh.h"

static void
_print_row(const ETable *table, ERow *row);

static void
_print_primary_key_value(gpointer primary_key_value,
                         gpointer convert_func);

static void
_print_data_value(gpointer data_value,
                  gpointer unused);

/*
 * This code shows the basic usage of Enlightenment.
 * It uses a simple in-memory engine (like MEMORY or HEAP in MySQL).
 *
 * I wanted to keep this code as simple as possible, so it does not cover topics such as multithreading, parallel IO and sharding.
 * Please don't use this code in performance critical situations; the calls to EEngine are performing blocking IO!
 *
 * Here you can see rows being inserted into a Table and then being retrieved from it.
 *
 * The table we'll be creating has three columns: UserID (int64), UserDeaths (int16), UserScore (int16), with UserID being the only primary key.
 */
int
main(E_UNUSED int argc,
     E_UNUSED gchar **argv) {
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

    // If you're not using autoptr, you can free the ERows and their
    // associated GPtrArrays and data after the row has been created by the engine.
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
    if (!engine->row_create_func(table, row, engine->func_data, &error)) {
        g_error("Error while creating a row: %s", error->message);
    }

    userId = 700;
    userDeaths = 1;
    userScore = 60;

    // Insert row with UserID=700, UserDeaths=1, UserScore=60
    if (!engine->row_create_func(table, row, engine->func_data, &error)) {
        g_error("Error while creating a row: %s", error->message);
    }

    ERow **rows = NULL;

    if (!engine->row_list_func(table, &rows, engine->func_data, &error)) {
        g_error("Error while creating a row: %s", error->message);
    }

    for (int i = 0; rows[i]; i++) {
        _print_row(table, rows[i]);
    }

    return EXIT_SUCCESS;
}

static void
_print_row(const ETable *table, ERow *row) {
    g_print("Row with %d primary key values and %d data values\n", row->primary_key_values->len, row->data_values->len);

    g_ptr_array_foreach(row->primary_key_values, _print_primary_key_value, g_ptr_array_index(e_table_get_primary_columns(table), 0));
    g_ptr_array_foreach(row->data_values, _print_data_value, NULL);
}

static void
_print_primary_key_value(gpointer primary_key_value,
                         gpointer primary_column) {
    // TODO print actual key value met behulp van de convert functie in EPrimaryColumn
    EPrimaryColumn *column = E_PRIMARY_COLUMN(primary_column);

    g_print("Primary key value pointing to %p, actual value %lu\n",
            primary_key_value,
            column->convert_func(primary_key_value, column->convert_func_data));
}

static void
_print_data_value(gpointer data_value,
                  E_UNUSED gpointer unused) {
    g_print("Data value pointing to %p, actual value %d\n", data_value, *(guint16 *)data_value);
}
