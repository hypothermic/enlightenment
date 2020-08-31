#ifndef ENLIGHTENMENT_SERVER_DRIVER_H
#define ENLIGHTENMENT_SERVER_DRIVER_H

#include "enlightenment/api/driver.h"

#include "enlightenment/server/error.h"

EDriver *
e_server_load_driver_from_file(EServer *server,
                               GFile *file,
                               GError **error);

#endif //ENLIGHTENMENT_SERVER_DRIVER_H
