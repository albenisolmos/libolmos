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

#ifndef __OL_STRV_BUILDER_H__
#define __OL_STRV_BUILDER_H__

#include <glib.h>
#include <glib/gstrfuncs.h>
#include <glib/gtypes.h>

G_BEGIN_DECLS

typedef struct _olStrvBuilder olStrvBuilder;

olStrvBuilder *ol_strv_builder_new (void);

void g_strv_builder_unref (olStrvBuilder *builder);

olStrvBuilder *ol_strv_builder_ref (olStrvBuilder *builder);

void ol_strv_builder_add (olStrvBuilder *builder,
                         const char *value);

void ol_strv_builder_addv (olStrvBuilder *builder,
                          const char **value);

void ol_strv_builder_add_many (olStrvBuilder *builder,
                              ...);

GStrv ol_strv_builder_end (olStrvBuilder *builder);

G_END_DECLS

#endif /* __OL_STRV-BUILDER_H__ */
