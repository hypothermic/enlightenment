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

/**
 * Insert a row into the table.<br />
 * <br />
 * If the primary key value(s) are NULL, the row will be appended to the table.<br />
 * If the primary key value(s) are non-NULL, the row will be inserted at the index matching the primary key value(s).
 * In this case, if there exists already a row with the exact primary key value(s) as given in the parameters,
 * it will be overwritten.<br />
 * <br />
 * A similar SQL statement would include the keywords "INSERT INTO".
 *
 * @return TRUE if successful. Upon error, FALSE will be returned and <i>error</i> will be assigned.
 */
typedef gboolean
(* ERowCreateFunc) (const ETable *table,
                    ERow *row,
                    gpointer func_data,
                    GError **error);

/**
 * Select one row by primary key value(s).<br />
 * <br />
 * A similar SQL statement would include the keywords "SELECT ... LIMIT 1".
 *
 * @return An array of ERow objects if successful. Upon error, NULL will be returned and <i>error</i> will be assigned.
 */
typedef ERow *
(* ERowReadFunc)   (const ETable *table,
                    GPtrArray *primary_key_values,
                    gpointer func_data,
                    GError **error);
/**
 * Set data value(s) where the primary key value(s) match(es) the given primary key value(s).<br />
 * <br />
 * Note that the ptr arrays in arguments <i>data_columns_to_be_replaced</i>
 * and <i>replacement_data_values</i> need to be of equal length.<br />
 * <br />
 * A similar SQL statement would include the keywords "UPDATE WHERE".
 *
 * @return TRUE if successful. Upon error, FALSE will be returned and <i>error</i> will be assigned.
 */
typedef gboolean
(* ERowUpdateFunc) (const ETable *table,
                    GPtrArray *primary_key_values,
                    GPtrArray *data_columns_to_be_replaced,
                    GPtrArray *replacement_data_values,
                    gpointer func_data,
                    GError **error);
/**
 * Delete a row where the primary key value(s) match(es) the given primary key value(s).<br />
 * <br />
 * A similar SQL statement would include the keywords "DELETE FROM".
 *
 * @return TRUE if successful. Upon error, FALSE will be returned and <i>error</i> will be assigned.
 */
typedef gboolean
(* ERowDeleteFunc) (const ETable *table,
                    GPtrArray *primary_key_values,
                    gpointer func_data,
                    GError **error);
/**
 * Retrieve all rows in a table.<br />
 * <br />
 * A similar SQL statement would include the keywords "SELECT * FROM".
 *
 * @return TRUE if successful. Upon error, FALSE will be returned and <i>error</i> will be assigned.
 */
typedef gboolean
(* ERowListFunc)   (const ETable *table,
                    ERow ***rows,
                    gpointer func_data,
                    GError **error);

struct _Engine {
    ERowCreateFunc  row_create_func;
    ERowReadFunc    row_read_func;
    ERowUpdateFunc  row_update_func;
    ERowDeleteFunc  row_delete_func;
    ERowListFunc    row_list_func;
    gpointer        func_data;
};

G_END_DECLS

#endif //ENLIGHTENMENT_ENGINE_H
