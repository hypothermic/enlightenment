#ifndef ENLIGHTENMENT_TABLE_H
#define ENLIGHTENMENT_TABLE_H

#include <glib.h>
#include <glib-object.h>

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
 * Initialize an ETable's members and assign a name.
 *
 * @returns TRUE if successful, otherwise FALSE will be returned and GError will be allocated.
 */
E_EXPORT gboolean
e_table_init(ETable *table,
             const gchar *const name,
             GError **error);

/**
 * @returns A null-terminated character array with the name of the table, or NULL if the ETable pointer is invalid.
 */
E_EXPORT const gchar *
e_table_get_name(ETable *table);

/**
 * @returns A string represented as 32-bit int (aka quark), or NUL if the ETable pointer is invalid.
 */
E_EXPORT GQuark
e_table_get_name_as_quark(ETable *table);

/**
 * Make sure you provide a valid ETable pointer, this will crash if you don't do so.
 *
 * @returns An unowned pointer array with EColumn elements.
 */
E_EXPORT E_NON_NULL const GPtrArray *
e_table_get_columns(ETable *table);

E_EXPORT void
e_table_free(ETable *table);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(ETable , e_table_free)

G_END_DECLS

#endif //ENLIGHTENMENT_TABLE_H
