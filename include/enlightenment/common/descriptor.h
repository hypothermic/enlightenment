#ifndef ENLIGHTENMENT_DESCRIPTOR_H
#define ENLIGHTENMENT_DESCRIPTOR_H

#include <gio/gio.h>

#include "build/exports.h"

G_BEGIN_DECLS

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

/**
 * Parses a descriptor object from a file.<br />
 * <br />
 * Returns null if an error has occurred, and <i>error</i> will be assigned.
 */
E_EXPORT EDescriptor *
e_descriptor_from_file(GFile *file,
                       GError **error);

E_EXPORT void
e_descriptor_free(EDescriptor *descriptor);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(EDescriptor, e_descriptor_free)

G_END_DECLS

#endif //ENLIGHTENMENT_DESCRIPTOR_H
