#ifndef ENLIGHTENMENT_ENGINE_H
#define ENLIGHTENMENT_ENGINE_H

#include <glib.h>

#include "enlightenment/common/server.h"

G_BEGIN_DECLS

#define E_ENGINE(ptr) ((EEngine *) ptr)

typedef struct _Engine EEngine;

/**
 * Create and initialize an Engine object (usually from within a dynamic module.)<br />
 * <br />
 * If NULL is returned, <i>error</i> will be assigned.
 *
 * @returns an Engine struct, or NULL if an error occurred.
 */
typedef EEngine
(* EngineInitFunc) (const EServer *server,
                    GError **error);

/*
 * TODO, equivalent of INSERT INTO
 */
typedef const gboolean
(* RowCreateFunc) (const ETable *table,
                   GError **error);
/*
 * TODO, equivalent of SELECT one row
 */
typedef const gboolean
(* RowReadFunc) (const ETable *table,
                 Row *row,
                 GError **error);
/*
 * TODO, equivalent of UPDATE WHERE
 */
typedef const gboolean
(* RowUpdateFunc) (const ETable *table,
                   /*what to update...?
                   which value to set...?*/
                   GError **error);
/*
 * TODO, equivalent of DELETE FROM
 */
typedef const gboolean
(* RowDeleteFunc) (const ETable *table,
                   GError **error);
/*
 * TODO, equivalent of SELECT multiple rows
 */
typedef const gboolean
(* RowListFunc)   (const ETable *table,
                   Row **rows,
                   GError **error);

/**
 * Data about the engine
 */
struct _Engine {
    RowCreateFunc row_create_func;
    RowReadFunc   row_read_func;
    RowUpdateFunc row_update_func;
    RowDeleteFunc row_delete_func;
    RowListFunc   row_list_func;
};

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_H
