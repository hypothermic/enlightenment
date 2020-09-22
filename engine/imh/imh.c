#include "imh.h"

#include <enlightenment/api/engine.h>
#include <enlightenment/common/error.h>

#include "1d.h"
#include "error.h"

E_EXPORT const EEngine *
e_imh_new(const ETable *table,
          GError **error) {
    EEngine *engine = g_new0(EEngine, 1);

    e_return_error_if_null_msg(engine, "Engine structure could not be allocated");

    // find the right kind of driver for the table
    switch (e_table_get_primary_columns(table)->len) {
        case 0: {
            g_set_error(error, ENLIGHTENMENT_IMH_ERROR, E_IMH_ERROR_TABLE_NO_PRIMARY_COLUMNS,
                        "Table does not have any primary columns");
            return NULL;
        }
        case 1: {
            if (G_UNLIKELY(!e_imh_1d_alloc(engine, table, error))) {
                return NULL;
            }
            break;
        }
        // currently only uncomposited primary keys (one-dimensional tables) are supported
        default: {
            g_set_error(error, ENLIGHTENMENT_IMH_ERROR, E_IMH_ERROR_TABLE_UNSUPPORTED,
                        "Currently, only tables with uncomposited primary keys are supported. PRs welcome.");
            return NULL;
        }
    }

    return engine;
}
