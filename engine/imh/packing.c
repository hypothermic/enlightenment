#include "packing.h"

#include "error.h"

#include <enlightenment/enlightenment.h>
#include <stdio.h>

#define BITS_TO_BYTES_LAZY(bits)    (guint)(((bits) / 8 + 0.499f))

#define _ROW_PACK_ITER(ptr)         ((struct _RowPackIter *) ptr)
#define _ROW_UNPACK_ITER(ptr)       ((struct _RowUnpackIter *) ptr)

/**
 * Internal struct for e_imh_row_pack params.
 */
struct _RowPackIter {
    const ETable *table;
    ERow *row;
    gchar *result;
    gsize current_bit;
    gsize iteration;
};

/**
 * Internal struct for e_imh_row_unpack params.
 */
struct _RowUnpackIter {
    GPtrArray *data_values;
    gchararray raw_data;
    gsize current_bit;
};

static void
_e_imh_row_pack_data_value(gpointer data_value,
                           gpointer user_data);

static void
_e_imh_row_unpack_data_value(gpointer data_column,
                             gpointer user_data);

static void
_e_imh_row_pack_memcpyb(const gchar *src,
                        gchar *dst,
                        gsize bits_to_copy);

gchararray
e_imh_row_pack(ERow *row,
               guint64 max_bytes,
               const ETable *table,
               GError **error) {
    gchar *result = g_malloc0(max_bytes);

    if (!result) {
        g_set_error(error, ENLIGHTENMENT_IMH_ERROR, E_IMH_ERROR_OUT_OF_MEMORY,
                    "Malloc returned NULL, no more memory available.");
        return NULL;
    }

    struct _RowPackIter iter = {
            .table = table,
            .row = row,
            .result = result,
            .current_bit = 0,
            .iteration = 0,
    };

    g_ptr_array_foreach(row->data_values, _e_imh_row_pack_data_value, &iter);

    return result;
}

ERow *
e_imh_row_unpack(gchararray data,
                 const ETable *table,
                 GError **error) {
    ERow *result = g_new0(ERow, 1);
    GPtrArray *data_values = g_ptr_array_new();

    if (!result) {
        g_set_error(error, ENLIGHTENMENT_IMH_ERROR, E_IMH_ERROR_OUT_OF_MEMORY,
                    "Malloc returned NULL, no more memory available.");
        return NULL;
    }

    result->data_values = data_values;

    struct _RowUnpackIter iter = {
            .data_values = data_values,
            .raw_data = data,
            .current_bit = 0,
    };

    // We're using the data columns array as read-only, so it's safe to discard constness.
    g_ptr_array_foreach((GPtrArray *) e_table_get_data_columns(table), _e_imh_row_unpack_data_value, &iter);

    return result;
}

static void
_e_imh_row_pack_data_value(gpointer data_ptr,
                           gpointer user_data) {
    struct _RowPackIter *iter = _ROW_PACK_ITER(user_data);
    EDataColumn *column = g_ptr_array_index(e_table_get_data_columns(iter->table), iter->iteration);

    // I think this is correct ??? please check it!
    gchar *current_result_pos_ptr = iter->result + BITS_TO_BYTES_LAZY(iter->current_bit);
    _e_imh_row_pack_memcpyb(data_ptr, current_result_pos_ptr, column->cell_size);

    iter->current_bit += column->cell_size;
    iter->iteration += 1;
}

static void
_e_imh_row_unpack_data_value(gpointer data_column,
                             gpointer user_data) {
    struct _RowUnpackIter *iter = _ROW_UNPACK_ITER(user_data);
    EDataColumn *column = E_DATA_COLUMN(data_column);

    gchar *result = g_malloc0(BITS_TO_BYTES_LAZY(column->cell_size)); // TODO handle malloc error

    //const gchar *current_result_pos_ptr = iter->raw_data + (guint)(*iter->current_bit / 8 + 0.499f);
    const gchar *current_result_pos_ptr = iter->raw_data + BITS_TO_BYTES_LAZY(iter->current_bit);
    _e_imh_row_pack_memcpyb(current_result_pos_ptr, result, column->cell_size);

    g_ptr_array_add(iter->data_values, result);

    iter->current_bit += column->cell_size;
    // TODO
}

static void
_e_imh_row_pack_memcpyb(const gchar *src,
                        gchar *dst,
                        gsize bits_to_copy) {
    gsize mask = -1 >> (8 - bits_to_copy);

    while (bits_to_copy / 8 > 0) {
        *dst++ = *src++;
        bits_to_copy -= 8;
    }

    *dst = (*dst & ~mask) | (*src & mask);
}
