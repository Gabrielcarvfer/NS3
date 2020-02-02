/* main_window.h
 * Definitions for main window routines with toolkit-independent APIs but
 * toolkit-dependent implementations.
 *
 * $Id: main_window.h 3992 2008-06-10 03:13:11Z dgu $
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

#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Tell the main window that we have a capture file (or not) */
extern void
main_set_for_capture_file(gboolean have_capture_file_in);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MAIN_WINDOW_H__ */
