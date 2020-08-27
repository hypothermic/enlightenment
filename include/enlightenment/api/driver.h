#ifndef ENLIGHTENMENT_DRIVER_H
#define ENLIGHTENMENT_DRIVER_H

#include <glib.h>

#include "enlightenment/common/server.h"

G_BEGIN_DECLS

#define E_DRIVER(ptr) ((EDriver *) ptr)

typedef struct _Driver EDriver;

/**
 * Create and initialize a Driver object (usually from within a dynamic module.)<br />
 * <br />
 * If NULL is returned, <i>error</i> will be assigned.
 *
 * @returns a ptr to a Driver struct, or NULL if an error occurred.
 */
typedef EDriver *
(* EDriverInitFunc) (const EServer *server,
                     GError **error);

/**
 * Create and initialize a Driver object (usually from within a dynamic module.)<br />
 * <br />
 * If NULL is returned, <i>error</i> will be assigned.
 *
 * @returns a ptr to a GOptionGroup, or NULL if driver has no options.
 */
typedef GOptionGroup *
(* EDriverGetOptionsFunc) (const EServer *server);

/**
 * Free a Driver object (usually from within a dynamic module.)<br />
 * <br />
 * If FALSE is returned, <i>error</i> will be assigned.
 *
 * @returns TRUE if success, otherwise FALSE and <i>error</i> will be assigned.
 */
typedef gboolean
(* EDriverFreeFunc) (EDriver *driver,
                     const EServer *server,
                     GError **error);

G_END_DECLS

#endif //ENLIGHTENMENT_DRIVER_H
