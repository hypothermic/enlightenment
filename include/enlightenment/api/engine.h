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

/*
 * TODO, equivalent of INSERT INTO
 */
typedef gboolean
(* ERowCreateFunc) (const ETable *table,
                    GError **error);
/*
 * TODO, equivalent of SELECT one row
 */
typedef gboolean
(* ERowReadFunc)   (const ETable *table,
                    ERow *row,
                    GError **error);
/*
 * TODO, equivalent of UPDATE WHERE
 */
typedef gboolean
(* ERowUpdateFunc) (const ETable *table,
        /*what to update...?
        which value to set...?*/
                    GError **error);
/*
 * TODO, equivalent of DELETE FROM
 */
typedef gboolean
(* ERowDeleteFunc) (const ETable *table,
                    GError **error);
/*
 * TODO, equivalent of SELECT multiple rows
 */
typedef gboolean
(* ERowListFunc)   (const ETable *table,
                    ERow **rows,
                    GError **error);

struct _Engine {
    ERowCreateFunc row_create_func;
    ERowReadFunc   row_read_func;
    ERowUpdateFunc row_update_func;
    ERowDeleteFunc row_delete_func;
    ERowListFunc   row_list_func;
};

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_H
