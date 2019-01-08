/* commview.h
 *
 * $Id: commview.h 3992 2008-06-10 03:13:11Z dgu $
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#ifndef __COMMVIEW_H__
#define __COMMVIEW_H__

int commview_open(wtap *wth, int *err, gchar **err_info _U_);
int commview_dump_can_write_encap(int encap);
gboolean commview_dump_open(wtap_dumper *wdh, gboolean cant_seek _U_, int *err);

#endif /* __COMMVIEW_H__ */

