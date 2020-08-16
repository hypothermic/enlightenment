#ifndef ENLIGHTENMENT_INTERNALS_H
#define ENLIGHTENMENT_INTERNALS_H

#include <glib.h>

G_BEGIN_DECLS

#ifdef __GNUC__
    #define E_INTERNAL(x) x __attribute__((deprecated("Do not access this member/variable/function directly from your program. It may break ABI compatibility.")))
#elif defined _MSC_VER
    #define E_INTERNAL(x) __pragma deprecated(x)
#else
    #define E_INTERNAL(x) x
#endif

#ifdef __GNUC__
    #define E_USE_INTERNAL(x) G_GNUC_BEGIN_IGNORE_DEPRECATIONS \
                              x \
                              G_GNUC_END_IGNORE_DEPRECATIONS
    #define E_BEGIN_USE_INTERNAL G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    #define E_END_USE_INTERNAL G_GNUC_END_IGNORE_DEPRECATIONS
#else
    #define E_USE_INTERNAL(x) x
    #define E_BEGIN_USE_INTERNAL
    #define E_END_USE_INTERNAL
#endif

G_END_DECLS

#endif //ENLIGHTENMENT_INTERNALS_H
