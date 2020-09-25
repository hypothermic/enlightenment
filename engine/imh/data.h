#ifndef ENLIGHTENMENT_DATA_H
#define ENLIGHTENMENT_DATA_H

#include <gio/gio.h>

G_BEGIN_DECLS

#define E_IMH_DATA(ptr) ((EImhData *) ptr)

typedef struct _Data EImhData;

/**
 * Internal data structure.
 */
struct _Data {
    /**
     * O(1) access for rows, fastest for accessing by index.<br />
     * <br />
     * Takes up a lot of heap memory when primary keys have high integer values
     * because all memory between rows[0] and rows[highest pk value] are zero'd out.
     * Also, inserting might take long because the whole array might have to be reallocated.
     */
    GArray *rows;

    /**
     * O(n) access for rows, fastest for listing.<br />
     * <br />
     * Is fast because it doesn't have to reallocate the entire list on every insert operation.
     */
    GSList *rows_list;

    /**
     * Internal row data length in bits
     */
    guint64 row_size;
};

G_END_DECLS

#endif //ENLIGHTENMENT_DATA_H
