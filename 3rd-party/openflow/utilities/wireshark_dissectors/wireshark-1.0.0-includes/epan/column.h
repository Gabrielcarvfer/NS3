/* column.h
 * Definitions for column handling routines
 *
 * $Id: column.h 3992 2008-06-10 03:13:11Z dgu $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __COLUMN_H__
#define __COLUMN_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _fmt_data {
  gchar *title;
  gchar *fmt;
  gchar *custom_field;
} fmt_data;

const gchar         *col_format_to_string(gint);
const gchar         *col_format_desc(gint);
gint                 get_column_format(gint);
void                 get_column_format_matches(gboolean *, gint);
gint                 get_column_format_from_str(gchar *);
gchar               *get_column_title(gint);
gchar               *get_column_custom_field(gint);
const gchar         *get_column_width_string(gint, gint);
const char          *get_column_longest_string(gint);
gint                 get_column_char_width(gint format);

void
build_column_format_array(capture_file *cfile, gboolean reset_fences);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* column.h */
