#include "enlightenment/api/engine.h"

#include "enlightenment/common/row.h"

struct _Engine {
    ERowCreateFunc row_create_func;
    ERowReadFunc   row_read_func;
    ERowUpdateFunc row_update_func;
    ERowDeleteFunc row_delete_func;
    ERowListFunc   row_list_func;
};
