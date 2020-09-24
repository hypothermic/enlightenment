#include "packing.h"

#include <enlightenment/enlightenment.h>

#define _ROW_PACK_ITER(ptr) ((struct _RowPackIter *) ptr)

/**
 * Internal struct for e_imh_row_pack params.
 */
struct _RowPackIter {
    const ETable *table;
    ERow *row;
    gchar *result;
    guint64 *current_bit;
    gsize *iteration;
};

static void
_e_imh_row_pack_data_value(gpointer data_value,
                           gpointer user_data);

static void
_e_imh_row_pack_memcpyb(gchar *src,
                        gchar *dst,
                        gsize nbit);

gchararray
e_imh_row_pack(ERow *row,
               guint64 max_bytes,
               const ETable *table,
               E_UNUSED GError **error) {
    gchar *result = g_malloc0(max_bytes);
    guint64 current_bit = 0;
    gsize iteration;

    struct _RowPackIter iter = {
            .table = table,
            .row = row,
            .result = result,
            .current_bit = &current_bit,
            .iteration = &iteration,
    };

    g_ptr_array_foreach(row->data_values, _e_imh_row_pack_data_value, &iter);

    return result;
}

/*ERow *
e_imh_row_unpack(gchararray data,
                 const ETable *table,
                 GError **error) {
    // TODO
    return NULL;
}*/

static void
_e_imh_row_pack_data_value(gpointer data_ptr,
                           gpointer user_data) {
    struct _RowPackIter *iter = _ROW_PACK_ITER(user_data);

    EDataColumn *column = g_ptr_array_index(e_table_get_data_columns(iter->table), *iter->iteration);
    //gpointer data_ptr = g_ptr_array_index(iter->row->data_values, *iter->iteration);

    // I think this is correct ??? please check it!
    gchar *current_result_pos_ptr = iter->result + (*iter->current_bit / 8 + 1);
    _e_imh_row_pack_memcpyb(data_ptr, current_result_pos_ptr, column->cell_size);
    iter->current_bit += column->cell_size;

    *iter->iteration += 1;
}

static void
_e_imh_row_pack_memcpyb(gchar *src,
                        gchar *dst,
                        gsize nbit) {
    gsize mask = -1 >> (8 - nbit);

    while (nbit / 8 > 0) {
        *dst++ = *src++;
        nbit -= 8;
    }

    *dst = (*dst & ~mask) | (*src & mask);
}
