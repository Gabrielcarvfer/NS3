/* base64.h
 * Base-64 conversion
 *
 * $Id: base64.h 3992 2008-06-10 03:13:11Z dgu $
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
#ifndef __BASE64_H__
#define __BASE64_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* In-place decoding of a base64 string. */
size_t epan_base64_decode(char *s);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BASE64_H__ */
