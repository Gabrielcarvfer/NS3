#!/usr/bin/env python3

# Copyright (C) 2018 Jussi Pakkanen.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of version 3, or (at your option) any later version,
# of the GNU General Public License as published
# by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import json, sys, os, shlex, subprocess, shutil, time

cppfile_templ = '''#include<%s>

int dummy_variable = 42;
'''

class SlownessFinder:
    def __init__(self):
        self.compile_cmds = json.load(open('compile_commands.json'))

    def measure(self, fname):
        cmdarr = self.get_command(fname)
        for i, switch in enumerate(cmdarr):
            if switch == '-o':
                object_index = i + 1
            if switch == fname:
                infile_index = i
        deps = self.get_deps(cmdarr, object_index)
        return self.do_measurements(deps, cmdarr, infile_index, object_index)

    def do_measurements(self, deps, cmdarr, infile_index, object_index):
        results = {}
        src_fname = 'dummy.cpp'
        obj_fname = 'dummy.o'
        build_cmd = cmdarr[:]
        build_cmd[infile_index] = src_fname
        build_cmd[object_index] = obj_fname
        for d in deps:
            if d in results:
                continue
            open(src_fname, 'w').write(cppfile_templ % d)
            start = time.time()
            if subprocess.run(build_cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode == 0:
                end = time.time()
                dur = end - start
                results[d] = dur
        return results

    def get_deps(self, cmdarr, object_index):
        # Ninja deletes the .d file. We need it so recreate.
        subprocess.check_call(cmdarr)
        dfile = cmdarr[object_index] + '.d'
        dcont = open(dfile).read().replace('\\\n', ' ')
        dfiles = dcont.strip().split()
        result = []
        for d in dfiles[1:]: # The first entry is the output .obj file.
            if os.path.splitext(d)[1] in ('.c', '.cpp', '.cxx', '.C', '.c++', '.cc'):
                continue
            result.append(d)
        return result

    def get_command(self, fname):
        for i in self.compile_cmds:
            if i['file'] == fname:
                res = shlex.split(i['command'])
                if res[0] == 'ccache':
                    return res[1:]
                return res
        sys.exit('File %s not found in compilation db.' % fname)

def sort_and_print(times):
    tarr = []
    for fname, dur in times.items():
        tarr.append([dur, fname])
    tarr.sort()
    for i in tarr[::-1]:
        print(*i)

if __name__ == '__main__':
    if not os.path.exists('compile_commands.json'):
        sys.exit('This script must be run at the root of the build dir.')
    if len(sys.argv) != 2:
        sys.exit('%s <path to source file>')
    sf = SlownessFinder()
    times = sf.measure(sys.argv[1])
    sort_and_print(times)
