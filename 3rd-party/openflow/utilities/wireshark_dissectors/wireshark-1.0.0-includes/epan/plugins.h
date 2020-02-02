/* plugins.h
 * definitions for plugins structures
 *
 * $Id: plugins.h 3992 2008-06-10 03:13:11Z dgu $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1999 Gerald Combs
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

#ifndef __PLUGINS_H__
#define __PLUGINS_H__

#include <glib.h>
#include <gmodule.h>

#include "packet.h"

typedef struct _plugin {
    GModule	*handle;          /* handle returned by dlopen */
    gchar       *name;            /* plugin name */
    gchar       *version;         /* plugin version */
    void (*register_protoinfo)(void); /* routine to call to register protocol information */
    void (*reg_handoff)(void);    /* routine to call to register dissector handoff */
    void (*register_tap_listener)(void);   /* routine to call to register tap listener */
    void (*register_wtap_module)(void);  /* routine to call to register a wiretap module */
    void (*register_codec_module)(void);  /* routine to call to register a codec */
    struct _plugin *next;         /* forward link */
} plugin;

WS_VAR_IMPORT plugin *plugin_list;

extern void init_plugins(void);
extern void register_all_plugin_registrations(void);
extern void register_all_plugin_handoffs(void);
extern void register_all_plugin_tap_listeners(void);
extern void register_all_wiretap_modules(void);
extern void register_all_codecs(void);

/* get the personal plugin dir */
/* Return value is g_malloced so the caller should g_free() it. */
extern char *get_plugins_pers_dir(void);

#endif /* __PLUGINS_H__ */
