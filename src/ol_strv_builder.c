/*
 * Copyright © 2020 Canonical Ltd.
 * Copyright © 2021 Alexandros Theodotou
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "ol_strv_builder.h"

/**
 * SECTION:gstrvbuilder
 * @title: GStrvBuilder
 * @short_description: Helper to create NULL-terminated string arrays.
 *
 * #GStrvBuilder is a method of easily building dynamically sized
 * NULL-terminated string arrays.
 *
 * The following example shows how to build a two element array:
 *
 * |[<!-- language="C" -->
 *   g_autoptr(GStrvBuilder) builder = g_strv_builder_new ();
 *   g_strv_builder_add (builder, "hello");
 *   g_strv_builder_add (builder, "world");
 *   g_auto(GStrv) array = g_strv_builder_end (builder);
 * ]|
 *
 * Since: 2.68
 */

struct _olStrvBuilder
{
	GPtrArray array;
};

/**
 * g_strv_builder_new:
 *
 * Creates a new #GStrvBuilder with a reference count of 1.
 * Use g_strv_builder_unref() on the returned value when no longer needed.
 *
 * Returns: (transfer full): the new #GStrvBuilder
 *
 * Since: 2.68
 */
olStrvBuilder *ol_strv_builder_new (void)
{
	return (olStrvBuilder *) g_ptr_array_new_with_free_func (g_free);
}

/**
 * g_strv_builder_unref:
 * @builder: (transfer full): a #GStrvBuilder allocated by g_strv_builder_new()
 *
 * Decreases the reference count on @builder.
 *
 * In the event that there are no more references, releases all memory
 * associated with the #GStrvBuilder.
 *
 * Since: 2.68
 **/
void ol_strv_builder_unref(olStrvBuilder *builder)
{
	g_ptr_array_unref(&builder->array);
}

/**
 * g_strv_builder_ref:
 * @builder: (transfer none): a #GStrvBuilder
 *
 * Atomically increments the reference count of @builder by one.
 * This function is thread-safe and may be called from any thread.
 *
 * Returns: (transfer full): The passed in #GStrvBuilder
 *
 * Since: 2.68
 */
olStrvBuilder *ol_strv_builder_ref(olStrvBuilder *builder)
{
	return (olStrvBuilder *) g_ptr_array_ref (&builder->array);
}

/**
 * g_strv_builder_add:
 * @builder: a #GStrvBuilder
 * @value: a string.
 *
 * Add a string to the end of the array.
 *
 * Since 2.68
 */
void ol_strv_builder_add (olStrvBuilder *builder, const char   *value)
{
	g_ptr_array_add (&builder->array, g_strdup (value));
}

/**
 * g_strv_builder_addv:
 * @builder: a #GStrvBuilder
 * @value: (array zero-terminated=1): the vector of strings to add
 *
 * Appends all the strings in the given vector to the builder.
 *
 * Since 2.70
 */
void ol_strv_builder_addv(olStrvBuilder *builder, const char **value)
{
	gsize i = 0;
	g_return_if_fail (builder != NULL);
	g_return_if_fail (value != NULL);
	for (i = 0; value[i] != NULL; i++)
		ol_strv_builder_add (builder, value[i]);
}

/**
 * g_strv_builder_add_many:
 * @builder: a #GStrvBuilder
 * @...: one or more strings followed by %NULL
 *
 * Appends all the given strings to the builder.
 *
 * Since 2.70
 */
void ol_strv_builder_add_many (olStrvBuilder *builder, ...)
{
	va_list var_args;
	const gchar *str;
	g_return_if_fail (builder != NULL);
	va_start (var_args, builder);
	while ((str = va_arg (var_args, gchar *)) != NULL)
		ol_strv_builder_add (builder, str);
	va_end (var_args);
}

/**
 * g_strv_builder_end:
 * @builder: a #GStrvBuilder
 *
 * Ends the builder process and returns the constructed NULL-terminated string
 * array. The returned value should be freed with g_strfreev() when no longer
 * needed.
 *
 * Returns: (transfer full): the constructed string array.
 *
 * Since 2.68
 */
GStrv ol_strv_builder_end (olStrvBuilder *builder)
{
	/* Add NULL terminator */
	g_ptr_array_add (&builder->array, NULL);
	return (GStrv) g_ptr_array_steal (&builder->array, NULL);
}
