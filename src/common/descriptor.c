#include "enlightenment/common/descriptor.h"

static const GKeyFileFlags KEY_FILE_FLAGS            = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;

static const gchar        *METADATA_GROUP_NAME       = "Metadata",
                              *DATABASE_NAME_KEY     = "Name",
                              *DATABASE_NAME_DEFAULT = "Unnamed Database";

static gchar *
g_key_file_get_string_or_default(GKeyFile *key_file,
                                 const gchar *group_name,
                                 const gchar *key,
                                 const gchar *default_value,
                                 GError **error);

E_EXPORT EDescriptor *
e_descriptor_from_file(GFile *file,
                       GError **error) {
    g_return_val_if_fail(error == NULL || *error == NULL, NULL);

    g_autoptr(GKeyFile) key_file = g_key_file_new();
    EDescriptor* descriptor = g_new0(EDescriptor, 1);

    if (G_UNLIKELY(!g_key_file_load_from_file(key_file, g_file_peek_path(file), KEY_FILE_FLAGS, error))) {
        return NULL;
    }

    descriptor->name = g_key_file_get_string_or_default(key_file, METADATA_GROUP_NAME, DATABASE_NAME_KEY, DATABASE_NAME_DEFAULT, error);

    return descriptor;
}

E_EXPORT void
e_descriptor_free(EDescriptor *descriptor) {
    if (G_LIKELY(descriptor)) {
        g_free(descriptor);
    }
}

static gchar *
g_key_file_get_string_or_default(GKeyFile *key_file,
                                 const gchar *group_name,
                                 const gchar *key,
                                 const gchar *default_value,
                                 GError **error) {
    gchar *val = g_key_file_get_string(key_file, group_name, key, error);

    if (G_UNLIKELY(val == NULL)) {
        g_warning("Missing key (%s) in descriptor file, using default value (%s)", key, default_value);
        val = g_strdup(default_value);
    }

    return val;
}