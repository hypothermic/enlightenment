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
    GArray *rows;
    guint64 row_size;
};

G_END_DECLS

#endif //ENLIGHTENMENT_DATA_H
