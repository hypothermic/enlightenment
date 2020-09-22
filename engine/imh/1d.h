#ifndef ENLIGHTENMENT_ENGINE_IMH_1D_H
#define ENLIGHTENMENT_ENGINE_IMH_1D_H

#include <enlightenment/enlightenment.h>

G_BEGIN_DECLS

/**
 * Allocate a one-dimensional table in memory.
 */
gboolean
e_imh_1d_alloc(EEngine *engine,
               const ETable *table,
               GError **error);

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_IMH_1D_H
