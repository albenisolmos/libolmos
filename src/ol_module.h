#ifndef __OL_MODULE_H__
#define __OL_MODULE_H__

#include <glib.h>
#include <gmodule.h>
#include "ol_strv_builder.h"

#define OL_MODULE_CHECK_SYMBOL(symbol, callback) \
		if (symbol != NULL) { \
			callback; \
		} \
		return TRUE;

typedef struct _olModule olModule;
typedef void (*olModuleRunFunc) (GHashTable *symbols, olStrvBuilder *contexts);
typedef gboolean (*olModuleCSFunc) ();

olModule *ol_module_new(const char *filename, GModuleFlags module_flag,
		GStrv schema, olModuleCSFunc context_selector, GError **error);

void ol_module_run(olModule *self, GError *error, gpointer data);

int ol_module_symbol(olModule *self, char *symbol, gpointer symbol_func, GError **error);

void ol_module_close(olModule *self, GError **error);

GModule *ol_module_get_gmodule(olModule *self);

void ol_module_set_contexts(olModule *self, GStrv contexts);

GStrv ol_module_get_contexts(olModule *self);

#endif
