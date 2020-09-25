#include "1d.h"

#include "data.h"
#include "error.h"
#include "packing.h"

#define BITS_TO_BYTES(bits)     ((bits / 8 + 1))

#define DEFAULT_INDEX_OFFSET    1

#define _ROW_LIST_FOREACH_DATA(ptr) ((struct _RowListForeachData *) ptr)

struct _RowListForeachData {
    const ETable *table;
    ERow **rows;
    gulong iteration;
};

static gboolean
_e_imh_1d_row_create(const ETable *table,
                     ERow *row,
                     gpointer imh_data,
                     GError **error);

/*static ERow *
_e_imh_1d_row_read(const ETable *table,
                   GError **error);

static gboolean
_e_imh_1d_row_update(const ETable *table,
                     gpointer primary_key,
                     GError **error);
static gboolean
_e_imh_1d_row_delete(const ETable *table,
                     gpointer primary_key,
                     GError **error);
*/

static gboolean
_e_imh_1d_row_list(const ETable *table,
                   ERow ***rows,
                   gpointer imh_data,
                   GError **error);

static guint64
_e_imh_1d_row_get_index(const ETable *table,
                        const ERow *row);

static void
_e_imh_1d_row_list_foreach(gpointer element,
                           gpointer user_data);

gboolean
e_imh_1d_alloc(EEngine *engine,
               const ETable *table,
               E_UNUSED GError **error) {
    guint64 row_size = e_table_get_row_size(table);
    EImhData *data = g_new0(EImhData, 1);
    GArray *rows = g_array_new(TRUE, TRUE, sizeof(gpointer));
    GSList *rows_list = NULL;

    data->rows = rows;
    data->rows_list = rows_list;
    data->row_size = row_size;
    engine->func_data = data;

    engine->row_create_func = _e_imh_1d_row_create;
    engine->row_list_func = _e_imh_1d_row_list;
    // TODO

    return TRUE;
}

/*
 * This function assumes the table is one-dimensional.
 *
 * Undefined behavior may happen if the table has more/less dimensions.
 */
static gboolean
_e_imh_1d_row_create(const ETable *table,
                     ERow *row,
                     gpointer imh_data,
                     GError **error) {
    EImhData *data = E_IMH_DATA(imh_data);
    // packed is ONLY data values because PK values are in index already!!! so row_size should be data_size !!!! TODO that.
    gchararray packed = e_imh_row_pack(row, BITS_TO_BYTES(data->row_size), table, error);
    guint64 requested_index = _e_imh_1d_row_get_index(table, row);

    if (!packed) {
        return FALSE;
    }

    if (requested_index == 0) { // append row
        g_array_append_vals(data->rows, packed, 1);
        data->rows_list = g_slist_append(data->rows_list, packed);
    } else { // insert row
        g_array_insert_vals(data->rows, requested_index, packed, 1);

        // TODO first delete the element with requested_index from the slist!!!!
        data->rows_list = g_slist_append(data->rows_list, packed);
    }

    //_debug_print_garray(data->rows);

    data->row_amount++;

    return TRUE;
}

/**
 * Calculates the array index from the primary key value.<br />
 * <br />
 * Undefined behavior may happen if the table has more/less dimensions.
 *
 * @returns index (> 0) if user wants to insert row, 0 if user wants to append row;
 */
static guint64
_e_imh_1d_row_get_index(const ETable *table,
                        const ERow *row) {
    gpointer raw_key = g_ptr_array_index(row->primary_key_values, 0);
    EPrimaryColumn *column = E_PRIMARY_COLUMN(g_ptr_array_index(e_table_get_primary_columns(table), 0));

    // If user has (explicitly) defined raw key as NULL (i.e. he is trying to append the row, not insert it.)
    if (raw_key == NULL) {
        return 0;
    } else {
        return column->convert_func(raw_key, column) + DEFAULT_INDEX_OFFSET;
    }
}

static gboolean
_e_imh_1d_row_list(const ETable *table,
                   ERow ***rows,
                   gpointer imh_data,
                   GError **error) {
    EImhData *data = E_IMH_DATA(imh_data);
    ERow **rows_dst = g_new0(ERow *, data->row_amount);

    if (*rows) {
        g_set_error(error, ENLIGHTENMENT_IMH_ERROR, E_IMH_ERROR_FUNCTION_RESULT_PTR,
                    "Invalid destination argument provided: **rows must point to NULL");
        return FALSE;
    }

    struct _RowListForeachData foreach_data = {
            .table = table,
            .rows = rows_dst,
            .iteration = 0,
    };

    g_slist_foreach(data->rows_list, _e_imh_1d_row_list_foreach, &foreach_data);

    *rows = rows_dst;

    return TRUE;
}

static void
_e_imh_1d_row_list_foreach(gpointer element,
                           gpointer user_data) {
    struct _RowListForeachData *data = _ROW_LIST_FOREACH_DATA(user_data);
    GError *error = NULL;
    ERow **rows = data->rows;
    ERow *unpacked = e_imh_row_unpack(((gchararray) element), data->table, &error);

    // TODO fill primary keys
    unpacked->primary_key_values = g_ptr_array_new();

    rows[data->iteration] = unpacked;

    data->iteration++;
}

#undef BITS_TO_BYTES
