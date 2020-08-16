#ifndef ENLIGHTENMENT_EXPORTS_H
#define ENLIGHTENMENT_EXPORTS_H

#ifdef _MSC_VER
#   define E_EXPORT __declspec( dllimport )
#else
#   define E_EXPORT __attribute__((visibility("default"))) __attribute__((used)) /*__attribute((warn_unused_result))*/
#   define E_NOEXPORT __attribute__((visibility("hidden")))
#endif

#endif //ENLIGHTENMENT_EXPORTS_H
