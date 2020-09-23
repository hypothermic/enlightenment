#include "1d.h"

#include "data.h"

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

gboolean
e_imh_1d_alloc(EEngine *engine,
               const ETable *table,
               GError **error) {
    guint64 row_size = e_table_get_row_size(table);
    EImhData *data = g_new0(EImhData, 1);
    GArray *rows = g_array_new(FALSE, TRUE, row_size);

    data->rows = rows;
    data->row_size = row_size;

    // TODO
    engine->row_create_func = _e_imh_1d_row_create;

    return TRUE;
}

static gboolean
_e_imh_1d_row_create(const ETable *table,
                     ERow *row,
                     gpointer imh_data,
                     GError **error) {
    // TODO serialize row into imh_data->rows
    return FALSE;
}
