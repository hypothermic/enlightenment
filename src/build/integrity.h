#ifndef ENLIGHTENMENT_INTEGRITY_H
#define ENLIGHTENMENT_INTEGRITY_H

#ifdef __GNUC__
    #define E_NON_NULL __attribute__((returns_nonnull)) __attribute__((nonnull))
    #define E_UNUSED G_GNUC_UNUSED
#else
    #define E_NON_NULL
    #define E_UNUSED
#endif

#endif //ENLIGHTENMENT_INTEGRITY_H
