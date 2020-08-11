#ifndef ENLIGHTENMENT_DATABASE_H
#define ENLIGHTENMENT_DATABASE_H

#include <glib.h>

#include "build/exports.h"

#include "descriptor.h"
#include "table.h"

G_BEGIN_DECLS

#define E_DATABASE(ptr) ((EDatabase *) ptr)

typedef struct _Database EDatabase;

struct _Database {
    const gchar *name;
};

E_EXPORT ETable *
e_database_get_tables(EDatabase *database);

E_EXPORT EDatabase *
e_database_for_descriptor(EDescriptor *descriptor);

G_END_DECLS

#endif //ENLIGHTENMENT_DATABASE_H
