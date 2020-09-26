#ifndef ENLIGHTENMENT_DATA_H
#define ENLIGHTENMENT_DATA_H

#include <gio/gio.h>

G_BEGIN_DECLS

#define E_IMH_DATA(ptr)                 ((EImhData *) ptr)
#define E_IMH_ROWS_LIST_ELEMENT(ptr)    ((EImhRowsListElement *) ptr)

typedef struct _Data                    EImhData;
typedef struct _RowsListElement         EImhRowsListElement;

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
     * Amount of rows stored.<br />
     * <br />
     * Keeping a copy of the length here is faster than traversing <i>rows_list</i>.
     */
    guint64 row_amount;

    /**
     * Internal row data length in bits/
     */
    guint64 row_size;
};

/**
 * Binds the PK to a rows list element
 */
struct _RowsListElement {
    gchararray raw_data;

    guint64 primary_key_value;
};

G_END_DECLS

#endif //ENLIGHTENMENT_DATA_H
