/* file_wrappers.h
 *
 * $Id: file_wrappers.h 3992 2008-06-10 03:13:11Z dgu $
 *
 * Wiretap Library
 * Copyright (c) 1998 by Gilbert Ramirez <gram@alumni.rice.edu>
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
 *
 */

#ifndef __FILE_H__
#define __FILE_H__

extern gint64 file_seek(void *stream, gint64 offset, int whence, int *err);
extern gint64 file_tell(void *stream);
extern int file_error(void *fh);

#ifdef HAVE_LIBZ

extern FILE_T file_open(const char *path, const char *mode);
#define filed_open gzdopen
/* XX: gzread and gzwrite return number of *bytes* (not number of elements) */
#define file_read(buf, bsize, count, file) gzread((file),(buf),((count)*(bsize)))
#define file_write(buf, bsize, count, file) gzwrite((file),(buf),((count)*(bsize)))
#define file_close gzclose
#define file_getc gzgetc
#define file_gets(buf, len, file) gzgets((file), (buf), (len))
#define file_eof gzeof

#else /* No zLib */

#define file_open(path, mode) eth_fopen(path, mode)
#define filed_open fdopen
/* XX: file_read and file_write defined to return number of *bytes* to be consistent with gzread & gzwrite */
#define file_read(buf, bsize, count, file) ((bsize) * fread((buf), (bsize), (count), (file)))
#define file_write(buf, bsize, count, file) ((bsize) * fwrite((buf), (bsize), (count), (file)))
#define file_close fclose
#define file_getc fgetc
#define file_gets fgets
#define file_eof feof

#endif /* HAVE_LIBZ */

#endif /* __FILE_H__ */
