/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*-

   peony-thumbnails.h: Thumbnail code for icon factory.

   Copyright (C) 2000 Eazel, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with this program; if not, write to the
   Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Author: Andy Hertzfeld <andy@eazel.com>
*/

#ifndef PEONY_THUMBNAILS_H
#define PEONY_THUMBNAILS_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <libpeony-private/peony-file.h>

/* Returns NULL if there's no thumbnail yet. */
void       peony_create_thumbnail                (PeonyFile *file);
gboolean   peony_can_thumbnail                   (PeonyFile *file);
gboolean   peony_can_thumbnail_internally        (PeonyFile *file);
gboolean   peony_thumbnail_is_mimetype_limited_by_size
(const char *mime_type);

/* Queue handling: */
void       peony_thumbnail_remove_from_queue     (const char   *file_uri);
void       peony_thumbnail_prioritize            (const char   *file_uri);


#endif /* PEONY_THUMBNAILS_H */
