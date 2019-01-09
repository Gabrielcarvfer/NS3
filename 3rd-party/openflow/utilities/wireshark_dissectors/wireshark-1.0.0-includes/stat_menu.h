/* stat_menu.h
 * Menu definitions for use by stats
 *
 * $Id: stat_menu.h 3992 2008-06-10 03:13:11Z dgu $
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __STATMENU_H__
#define __STATMENU_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @file
 * Add a new menu item for a stat.
 */

/*
 * XXX - defines stuff usable regardless of the GUI toolkit.  Right now,
 * that's only the menu group, which is used by tap_dfilter_dlg.h.
 *
 * XXX - stats should be able to register additional menu groups, although
 * the question then would be "in what order should they appear in the menu?"
 */

/** The menu group this stat should be registered in. */
typedef enum {
    REGISTER_STAT_GROUP_NONE,
    REGISTER_STAT_GROUP_GENERIC,
    REGISTER_STAT_GROUP_CONVERSATION_LIST,
    REGISTER_STAT_GROUP_ENDPOINT_LIST,
    REGISTER_STAT_GROUP_RESPONSE_TIME,
    REGISTER_STAT_GROUP_TELEPHONY,
    /* XXX - split into telephony and VoIP? */
	REGISTER_ANALYZE_GROUP_NONE,
	REGISTER_ANALYZE_GROUP_CONVERSATION_FILTER
#ifdef HAVE_LUA_5_1
	,REGISTER_TOOLS_GROUP_NONE
#endif
} register_stat_group_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STATMENU_H__ */
