#ifndef ENLIGHTENMENT_UNUSED_H
#define ENLIGHTENMENT_UNUSED_H

#ifdef _MSC_VER
#   define E_UNUSED
#else
#   define E_UNUSED __attribute__((unused))
#endif

#endif //ENLIGHTENMENT_UNUSED_H
