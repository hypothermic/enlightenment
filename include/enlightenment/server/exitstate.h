#ifndef ENLIGHTENMENT_EXITSTATE_H
#define ENLIGHTENMENT_EXITSTATE_H

G_BEGIN_DECLS

typedef enum /*: uint8_t*/ {

    /**
     * Desired exit code, server shut down gracefully.
     */
    E_SERVER_EXIT_SUCCESS    = 0,

    /**
     * Error while parsing arguments.
     */
    E_SERVER_EXIT_ERROR_ARGS = 101,

    /**
     * Error while initializing the server.
     */
    E_SERVER_EXIT_ERROR_INIT = 102,

    /**
     * Error while loading drivers.
     */
    E_SERVER_EXIT_ERROR_LOAD_DRIVERS = 103,

    /**
     * GModule reports that modules are unsupported on the current platform.
     */
    E_SERVER_EXIT_ERROR_MODULES_UNSUPPORTED = 104,

    /* Do not use exit codes higher than 255 */

} EServerExitState;

G_END_DECLS

#endif //ENLIGHTENMENT_EXITSTATE_H
