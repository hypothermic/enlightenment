#ifndef ENLIGHTENMENT_DESCRIPTOR_H
#define ENLIGHTENMENT_DESCRIPTOR_H

#include <gio/gio.h>

#include "build/exports.h"

#define E_DESCRIPTOR(ptr) ((EDescriptor *) ptr)

typedef struct _Descriptor EDescriptor;

/**
 * Metadata file which describes a database structure.<br />
 * <br />
 * Specific details may vary per implementation.
 */
struct _Descriptor {
    const gchar *name;
};

E_EXPORT EDescriptor *
e_descriptor_from_file(GFile *file);

#endif //ENLIGHTENMENT_DESCRIPTOR_H
