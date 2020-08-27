#ifndef ENLIGHTENMENT_ROW_H
#define ENLIGHTENMENT_ROW_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

#define E_ROW(ptr) ((ERow *) ptr)

typedef struct _Row ERow;

/**
 *
 */
struct _Row {
    const gchar *name;
};

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

E_EXPORT void
e_row_free(ERow *row);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(ERow, e_row_free)

G_END_DECLS

#endif //ENLIGHTENMENT_ROW_H
