#ifndef ENLIGHTENMENT_ENGINE_IMH_ROW_H
#define ENLIGHTENMENT_ENGINE_IMH_ROW_H

#include <gio/gio.h>
#include <enlightenment/common/row.h>

G_BEGIN_DECLS

/**
 * Converts a row to bytes.
 *
 * The length of the resulting byte array is (e_table_get_row_size(table) / 8 + 1)
 *
 * @return a ptr to the first element of a byte array, or NULL if error (**error will be allocated on error)
 */
gchararray
e_imh_row_pack(ERow *row,
               GError **error);

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_IMH_ROW_H
