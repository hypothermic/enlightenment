#ifndef ENLIGHTENMENT_ENGINE_H
#define ENLIGHTENMENT_ENGINE_H

#include <glib.h>

#include "enlightenment/common/server.h"
#include "enlightenment/common/row.h"

G_BEGIN_DECLS

#define E_ENGINE(ptr) ((EEngine *) ptr)

typedef struct _Engine EEngine;

/**
 * Create and initialize an Engine object (usually within a dynamic module.)<br />
 * <br />
 * If NULL is returned, <i>error</i> will be assigned.
 *
 * @returns a ptr to an Engine struct, or NULL if an error occurred.
 */
typedef EEngine *
(* EEngineInitFunc) (const EServer *server,
                    GError **error);

/**
 * Free an Engine object (usually within a dynamic module.)<br />
 * <br />
 * If FALSE is returned, <i>error</i> will be assigned.
 *
 * @returns TRUE if success, otherwise FALSE and <i>error</i> will be assigned.
 */
typedef gboolean
(* EEngineFreeFunc) (EEngine *engine,
                    const EServer *server,
                    GError **error);

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_H
