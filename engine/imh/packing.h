#ifndef ENLIGHTENMENT_ENGINE_IMH_ROW_H
#define ENLIGHTENMENT_ENGINE_IMH_ROW_H

#include <gio/gio.h>
#include <enlightenment/common/row.h>
#include <enlightenment/common/table.h>

G_BEGIN_DECLS

/**
 * Converts a row to bytes.<br />
 * <br />
 * The length of the resulting byte array is (e_table_get_row_size(table) / 8 + 1).<br />
 * <br />
 * The ownership of the resulting byte array is transferred to you (e.g. you should free it!)
 *
 * @return a ptr to the first element of a byte array, or NULL if error (**error will be allocated on error)
 */
gchararray
e_imh_row_pack(ERow *row,
               guint64 max_bytes,
               const ETable *table,
               GError **error);

/**
 * Converts bytes to a row.
 *
 * The length of the input byte array must be equal to (e_table_get_row_size(table) / 8 + 1).<br />
 * <br />
 * The ownership of the resulting row is transferred to you (e.g. you should free it!)
 *
 * @return a ptr to an allocated ERow struct.
 */
ERow *
e_imh_row_unpack(gchararray data,
                 const ETable *table,
                 GError **error);

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_IMH_ROW_H
