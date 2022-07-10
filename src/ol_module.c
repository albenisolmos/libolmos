#include "ol_module.h"
#include "ol_error.h"

static gboolean on_foreach_symbols(gpointer, gpointer, gpointer);

struct _olModule {
	GModule *module;
	GHashTable *symbols;
	GStrv selected_contexts;
	GStrv contexts;
	olModuleCSFunc context_selector;
};

struct olModuleData {
	olModule *module;
	gpointer data;
};

olModule *ol_module_new(const char *filename, GModuleFlags module_flag,
		GStrv schema, olModuleCSFunc context_selector, GError **error)
{
	olModule *self = (olModule*) malloc(sizeof(olModule));

	if (!g_module_supported()) {
		g_set_error(error, OL_MODULE_ERROR,
				OL_MODULE_ERROR_NOT_SOPORTED, "%s", g_module_error());
		return NULL;
	}

	self->module = g_module_open(filename, module_flag);
	if (self->module == NULL) {
		g_set_error(error, OL_MODULE_ERROR, OL_MODULE_ERROR_OPENING,
				"%s", g_module_error());
		return NULL;
	}

	self->context_selector = context_selector;
	return self;
}

int ol_module_symbol(olModule *self, char *symbol_name, gpointer symbol,
		GError **error)
{
	GModule *mod = self->module;
	const gchar *filename = g_module_name(mod);

	if (!g_module_symbol(self->module, symbol_name, symbol))
	{
		g_set_error(error, OL_MODULE_ERROR, OL_MODULE_ERROR_SYMBOL,
				"%s: %s", filename, g_module_error());

		return FALSE;
	}

	if (symbol == NULL)
	{
		g_set_error (error, OL_MODULE_ERROR, OL_MODULE_ERROR_SYMBOL_IS_NULL,
				"symbol %s is NULL", symbol_name);

		return FALSE;
	}

	return TRUE;
}

void ol_module_run(olModule *self, GError *error, gpointer _data)
{
	olModuleRunFunc run;
	GHashTable *symbols = g_hash_table_new(g_direct_hash,  g_direct_equal);
	olStrvBuilder *contexts = ol_strv_builder_new();
	struct olModuleData data;
	data.module = self;
	data.data = _data;

	ol_module_symbol(self, "run", (gpointer) &run, &error);

	g_return_if_fail(run != NULL);
	run(symbols, contexts);

	self->contexts = ol_strv_builder_end(contexts);

	g_hash_table_foreach((gpointer) symbols, (gpointer) &on_foreach_symbols, (gpointer) &data);
}

GModule *ol_module_get_gmodule(olModule *self) {
	return self->module;
}

void ol_module_close(olModule *self, GError **error)
{
	if (!g_module_close(self->module))
		g_warning("%s: %s", g_module_name(self->module), g_module_error());
}

static gboolean on_foreach_symbols(gpointer _symbol_name, gpointer symbol,
		gpointer _data)
{
	struct olModuleData *data = (struct olModuleData *) _data;
	olModule *module = data->module;
	char *symbol_name = (char *) _symbol_name;
	guint length = module->contexts == NULL ? 0 : g_strv_length(module->contexts);

	if (length == 0)
			module->context_selector(NULL, symbol_name, symbol);
	else
		for (guint i = 0; i < length; i++)
			module->context_selector(module->contexts[i], symbol_name, symbol,
					data->data);

	return TRUE;
}
