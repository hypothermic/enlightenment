#include "1d.h"

#include "data.h"
#include "packing.h"

#define BITS_TO_BYTES(bits)     ((bits / 8 + 1))

#define DEFAULT_INDEX_OFFSET    1

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

static gboolean
_e_imh_1d_row_list(const ETable *table,
                   ERow **rows,
                   GError **error);*/

static guint64
_e_imh_1d_row_get_index(const ETable *table,
                        const ERow *row);

gboolean
e_imh_1d_alloc(EEngine *engine,
               const ETable *table,
               GError **error) {
    guint64 row_size = e_table_get_row_size(table);
    EImhData *data = g_new0(EImhData, 1);
    GArray *rows = g_array_new(FALSE, TRUE, BITS_TO_BYTES(row_size));

    data->rows = rows;
    data->row_size = row_size;

    engine->row_create_func = _e_imh_1d_row_create;
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

    if (requested_index == 0) { // append row
        g_array_append_vals(data->rows, packed, 1);
    } else { // insert row
        g_array_insert_vals(data->rows, requested_index, packed, 1);
    }

    return FALSE;
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

#undef BITS_TO_BYTES
