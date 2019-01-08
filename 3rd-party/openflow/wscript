## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

srcdir = '.'
blddir = 'build'

from heapq import merge

def headers():
    private_headers = ['lib/csum.h','lib/poll-loop.h', 'lib/rconn.h', 'lib/queue.h',
                       'lib/stp.h', 'lib/compiler.h', 'lib/util.h', 'lib/vconn.h',
                       'lib/xtoxll.h', 'switch/chain.h', 'switch/table.h', 'switch/datapath.h',
                       'lib/ofpbuf.h', 'switch/switch-port.h', 'lib/red-black-tree.h',
                       'lib/misc.h', 'lib/stack.h', 'switch/dp_act.h', 'switch/switch-flow.h', 
                       'lib/flow.h', 'lib/list.h', 'switch/pt_act.h',
                       'lib/packets.h', 'lib/random.h', 'lib/timeval.h', 'lib/type-props.h']
    return private_headers


def set_options(opt):
    opt.tool_options('compiler_cc')

def configure(conf):
    conf.check_tool('compiler_cc')

    import os
    import shutil
    try:
        shutil.rmtree('include/openflow/private')
    except:
        pass
    try:
        os.makedirs('include/openflow/private/')
    except:
        pass
    for header in headers():
        shutil.copy(header, 'include/openflow/private/' + os.path.basename (header))

def build(bld):
    # Build the OpenFlow C static library from the software implementation distribution
    of = bld.new_task_gen('cc', 'cstaticlib')
    of.source = list(merge(bld.glob('/switch/*.c'), bld.glob('/lib/*.c')))
    of.includes = [
	'.',
	'..',
	'include/.',
	'include/openflow/.',
	'lib/.',
	'switch/.',
	'/usr/include/libxml2',
    ]
    of.env.append_value('CCFLAGS', '-fPIC')
    of.target = 'openflow'

    # finally, let's install all this crap
    bld.install_files('${PREFIX}/lib', 'libopenflow.a')
    start_dir = bld.path.find_dir('include/openflow')
    bld.install_files('${PREFIX}/include/openflow', start_dir.ant_glob('**/*.h'), cwd=start_dir)
    bld.install_files('${PREFIX}/include/openflow/private', headers())
