#!/usr/bin/env python
#
# Looks for registration routines in the protocol dissectors,
# and assembles C code to call all the routines.
#
# This is a Python version of the make-reg-dotc shell script.
# Running the shell script on Win32 is very very slow because of
# all the process-launching that goes on --- multiple greps and
# seds for each input file.  I wrote this python version so that
# less processes would have to be started.
#
# $Id: make-dissector-reg.py 24390 2008-02-19 13:44:02Z wmeier $

import os
import sys
import re
import pickle
from stat import *

#
# The first argument is the directory in which the source files live.
#
srcdir = sys.argv[1]

#
# The second argument is either "plugin" or "dissectors"; if it's
# "plugin", we build a plugin.c for a plugin, and if it's
# "dissectors", we build a register.c for libwireshark.
#
registertype = sys.argv[2]
if registertype == "plugin":
	tmp_filename = "plugin.c-tmp"
	final_filename = "plugin.c"
	cache_filename = None
elif registertype == "dissectors":
	tmp_filename = "register.c-tmp"
	final_filename = "register.c"
	cache_filename = "register-cache.pkl"
else:
	print "Unknown output type '%s'" % registertype
	sys.exit(1)


#
# All subsequent arguments are the files to scan.
#
files = sys.argv[3:]

# Create the proper list of filenames
filenames = []
for file in files:
	if os.path.isfile(file):
		filenames.append(file)
	else:
		filenames.append("%s/%s" % (srcdir, file))

if len(filenames) < 1:
	print "No files found"
	sys.exit(1)


# Look through all files, applying the regex to each line.
# If the pattern matches, save the "symbol" section to the
# appropriate array.
regs = {
	'proto_reg': [],
	'handoff_reg': [],
	}

# For those that don't know Python, r"" indicates a raw string,
# devoid of Python escapes.
proto_regex0 = r"^(?P<symbol>proto_register_[_A-Za-z0-9]+)\s*\([^;]+$"
proto_regex1 = r"void\s+(?P<symbol>proto_register_[_A-Za-z0-9]+)\s*\([^;]+$"

handoff_regex0 = r"^(?P<symbol>proto_reg_handoff_[_A-Za-z0-9]+)\s*\([^;]+$"
handoff_regex1 = r"void\s+(?P<symbol>proto_reg_handoff_[_A-Za-z0-9]+)\s*\([^;]+$"

# This table drives the pattern-matching and symbol-harvesting
patterns = [
	( 'proto_reg', re.compile(proto_regex0) ),
	( 'proto_reg', re.compile(proto_regex1) ),
	( 'handoff_reg', re.compile(handoff_regex0) ),
	( 'handoff_reg', re.compile(handoff_regex1) ),
	]

# Open our registration symbol cache
cache = None
if cache_filename:
	try:
		cache_file = open(cache_filename, 'rb')
		cache = pickle.load(cache_file)
		cache_file.close()
	except:
		cache = {}

# Grep
for filename in filenames:
	file = open(filename)
	cur_mtime = os.fstat(file.fileno())[ST_MTIME]
	if cache and cache.has_key(filename):
		cdict = cache[filename]
		if cur_mtime == cdict['mtime']:
#			print "Pulling %s from cache" % (filename)
			regs['proto_reg'].extend(cdict['proto_reg'])
			regs['handoff_reg'].extend(cdict['handoff_reg'])
			file.close()
			continue
	# We don't have a cache entry
	if cache is not None:
		cache[filename] = {
			'mtime': cur_mtime,
			'proto_reg': [],
			'handoff_reg': [],
			}
#	print "Searching %s" % (filename)
	for line in file.readlines():
		for action in patterns:
			regex = action[1]
			match = regex.search(line)
			if match:
				symbol = match.group("symbol")
				sym_type = action[0]
				regs[sym_type].append(symbol)
				if cache is not None:
#					print "Caching %s for %s: %s" % (sym_type, filename, symbol)
					cache[filename][sym_type].append(symbol)
	file.close()

if cache is not None and cache_filename is not None:
	cache_file = open(cache_filename, 'wb')
	pickle.dump(cache, cache_file)
	cache_file.close()

# Make sure we actually processed something
if len(regs['proto_reg']) < 1:
	print "No protocol registrations found"
	sys.exit(1)

# Sort the lists to make them pretty
regs['proto_reg'].sort()
regs['handoff_reg'].sort()

reg_code = open(tmp_filename, "w")

reg_code.write("/* Do not modify this file.  */\n")
reg_code.write("/* It is created automatically by the Makefile.  */\n")

# Make the routine to register all protocols
if registertype == "plugin":
	reg_code.write("""
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <gmodule.h>

#include "moduleinfo.h"

#ifndef ENABLE_STATIC
G_MODULE_EXPORT const gchar version[] = VERSION;

/* Start the functions we need for the plugin stuff */

G_MODULE_EXPORT void
plugin_register (void)
{
""");
else:
	reg_code.write("""
#include "register.h"
void
register_all_protocols(register_cb cb, gpointer client_data)
{
""");

for symbol in regs['proto_reg']:
	if registertype == "plugin":
		line = "  {extern void %s (void); %s ();}\n" % (symbol, symbol)
	else:
		line = "  {extern void %s (void); if(cb) (*cb)(RA_REGISTER, \"%s\", client_data); %s ();}\n" % (symbol, symbol, symbol)
	reg_code.write(line)

reg_code.write("}\n")


# Make the routine to register all protocol handoffs
if registertype == "plugin":
	reg_code.write("""
G_MODULE_EXPORT void
plugin_reg_handoff(void)
{
""");
else:
	reg_code.write("""
void
register_all_protocol_handoffs(register_cb cb, gpointer client_data)
{
""");

for symbol in regs['handoff_reg']:
	if registertype == "plugin":
		line = "  {extern void %s (void); %s ();}\n" % (symbol, symbol)
	else:
		line = "  {extern void %s (void); if(cb) (*cb)(RA_HANDOFF, \"%s\", client_data); %s ();}\n" % (symbol, symbol, symbol)
	reg_code.write(line)

reg_code.write("}\n")

if registertype == "plugin":
	reg_code.write("#endif\n");
else:
	reg_code.write("""
gulong register_count(void)
{
""");

	line = "  return %d + %d;\n" % (len(regs['proto_reg']), len(regs['handoff_reg']))
	reg_code.write(line)

	reg_code.write("""
}
""");


# Close the file
reg_code.close()

# Remove the old final_file if it exists.
try:
	os.stat(final_filename)
	os.remove(final_filename)
except OSError:
	pass

# Move from tmp file to final file
os.rename(tmp_filename, final_filename)


