#ifndef ENLIGHTENMENT_ENGINE_IMH_H
#define ENLIGHTENMENT_ENGINE_IMH_H

#include <enlightenment/enlightenment.h>

/**
 * Creates a new engine instance for a table.
 *
 * @return Engine instance or NULL if error.
 */
E_EXPORT const EEngine *
e_imh_new(const ETable *table,
          GError **error);

#endif //ENLIGHTENMENT_ENGINE_IMH_H
