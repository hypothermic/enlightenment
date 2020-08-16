#ifndef ENLIGHTENMENT_TABLE_H
#define ENLIGHTENMENT_TABLE_H

#include <glib.h>

#include "build/exports.h"
#include "build/integrity.h"
#include "build/internals.h"

G_BEGIN_DECLS

#define E_TABLE(ptr) ((ETable *) ptr)

typedef struct _Table ETable;

/**
 * Allocates an ETable struct without instantiating its members.
 *
 * @returns An owned pointer to a new ETable struct.
 */
E_EXPORT E_NON_NULL ETable *
e_table_new(void);

/**
 * @returns An unowned pointer array with EColumn elements.
 */
E_EXPORT E_NON_NULL const GPtrArray *
e_table_get_columns(ETable *table);

G_END_DECLS

#endif //ENLIGHTENMENT_TABLE_H
