#ifndef ENLIGHTENMENT_TABLE_H
#define ENLIGHTENMENT_TABLE_H

#include <glib.h>

#include "build/exports.h"

#define E_TABLE(ptr) ((ETable *) ptr)

typedef struct _Table ETable;

struct _Table {
    const gchar *name;
};

#endif //ENLIGHTENMENT_TABLE_H
