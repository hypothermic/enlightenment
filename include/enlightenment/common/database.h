#ifndef ENLIGHTENMENT_DATABASE_H
#define ENLIGHTENMENT_DATABASE_H

#include <glib.h>

#include "build/exports.h"
#include "build/internals.h"

#include "descriptor.h"
#include "table.h"

G_BEGIN_DECLS

#define E_DATABASE(ptr) ((EDatabase *) ptr)

typedef struct _Database EDatabase;

/**
 * Allocates an EDatabase struct without instantiating its members.
 *
 * @returns An owned pointer to a EDatabase struct.
 */
E_EXPORT E_NON_NULL EDatabase *
e_database_new(void);

/**
 * @returns A null-terminated character array with the name of the database.
 */
E_EXPORT const gchar *
e_database_get_name(EDatabase *database);

/**
 * @returns A string represented as 32-bit int (aka quark)
 */
E_EXPORT GQuark
e_database_get_name_as_quark(EDatabase *database);

/**
 * @returns An unowned pointer array with ETable elements.
 */
E_EXPORT const GPtrArray *
e_database_get_tables(EDatabase *database);

/**
 * @returns An owned pointer to a fully instantiated EDatabase struct.
 */
E_EXPORT EDatabase *
e_database_for_descriptor(const EDescriptor *descriptor,
                          GError **error);

E_EXPORT void
e_database_free(EDatabase *database);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EDatabase, e_database_free)

G_END_DECLS

#endif //ENLIGHTENMENT_DATABASE_H
