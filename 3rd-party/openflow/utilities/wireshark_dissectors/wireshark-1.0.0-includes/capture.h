/* capture.h
 * Definitions for packet capture windows
 *
 * $Id: capture.h 3992 2008-06-10 03:13:11Z dgu $
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

/* This file should only be included if libpcap is present */

#ifndef __CAPTURE_H__
#define __CAPTURE_H__

/** @file
 *  Capture related things.
 */

#include "capture_opts.h"

/**
 * Start a capture session.
 *
 * @param capture_opts the numerous capture options
 * @return TRUE if the capture starts successfully, FALSE otherwise.
 */
extern gboolean capture_start(capture_options *capture_opts);

/** Stop a capture session (usually from a menu item). */
extern void capture_stop(capture_options *capture_opts);

/** Restart the current captured packets and start again. */
extern void capture_restart(capture_options *capture_opts);

/** Terminate the capture child cleanly when exiting. */
extern void capture_kill_child(capture_options *capture_opts);

/**
 * Capture child told us we have a new (or the first) capture file.
 */
extern gboolean capture_input_new_file(capture_options *capture_opts, gchar *new_file);

/**
 * Capture child told us we have new packets to read.
 */
extern void capture_input_new_packets(capture_options *capture_opts, int to_read);

/**
 * Capture child told us how many dropped packets it counted.
 */
extern void capture_input_drops(capture_options *capture_opts, int dropped);

/**
 * Capture child told us that an error has occurred while starting the capture.
 */
extern void capture_input_error_message(capture_options *capture_opts, char *error_message, char *secondary_error_msg);

/**
 * Capture child told us that an error has occurred while parsing a
 * capture filter when starting/running the capture.
 */
extern void capture_input_cfilter_error_message(capture_options *capture_opts, char *error_message);

/**
 * Capture child closed its side of the pipe, do the required cleanup.
 */
extern void capture_input_closed(capture_options *capture_opts);

#ifdef HAVE_LIBPCAP
/**
 * Fetch the interface list from a child process.
 */
extern GList *capture_interface_list(int *err, char **err_str);

/**
 * Fetch the linktype list for the specified interface from a child process.
 */
extern GList *capture_pcap_linktype_list(const char *devname, char **err_str);


struct if_stat_cache_s;
typedef struct if_stat_cache_s if_stat_cache_t;

/**
 * Start gathering capture statistics for the interfaces specified.
 * @param A GList of if_info_t items
 * @return A pointer to the statistics state data.
 */
extern if_stat_cache_t * capture_stat_start(GList *if_list);

/**
 * Fetch capture statistics, similar to pcap_stats().
 */
struct pcap_stat; /* Stub in case we don't or haven't yet included pcap.h */
extern gboolean capture_stats(if_stat_cache_t *sc, char *ifname, struct pcap_stat *ps);

/**
 * Stop gathering capture statistics.
 */
void capture_stat_stop(if_stat_cache_t *sc);
#endif /* HAVE_LIBPCAP */

#endif /* capture.h */
