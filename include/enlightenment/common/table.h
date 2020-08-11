#ifndef ENLIGHTENMENT_TABLE_H
#define ENLIGHTENMENT_TABLE_H

#include <glib.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_TABLE(ptr) ((ETable *) ptr)

typedef struct _Table ETable;

struct _Table {
    const gchar *name;
};

G_END_DECLS

#endif //ENLIGHTENMENT_TABLE_H
