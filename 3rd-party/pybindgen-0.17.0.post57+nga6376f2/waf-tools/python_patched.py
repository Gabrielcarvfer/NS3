#!/usr/bin/env python
# encoding: utf-8
# Thomas Nagy, 2007-2010 (ita)
# Gustavo Carneiro (gjc), 2007

"""
Support for Python, detect the headers and libraries and provide
*use* variables to link C/C++ programs against them::

	def options(opt):
		opt.load('compiler_c python')
	def configure(conf):
		conf.load('compiler_c python')
		conf.check_python_version((2,4,2))
		conf.check_python_headers()
	def build(bld):
		bld.program(features='pyembed', source='a.c', target='myprog')
		bld.shlib(features='pyext', source='b.c', target='mylib')
"""

import os, sys
from waflib import Utils, Options, Errors, Logs
from waflib.TaskGen import extension, before_method, after_method, feature
from waflib.Configure import conf

FRAG = '''
#include <Python.h>
#ifdef __cplusplus
extern "C" {
#endif
	void Py_Initialize(void);
	void Py_Finalize(void);
#ifdef __cplusplus
}
#endif
int main(int argc, char **argv)
{
   (void)argc; (void)argv;
   Py_Initialize();
   Py_Finalize();
   return 0;
}
'''
"""
Piece of C/C++ code used in :py:func:`waflib.Tools.python.check_python_headers`
"""

INST = '''
import sys, py_compile
py_compile.compile(sys.argv[1], sys.argv[2], sys.argv[3])
'''
"""
Piece of Python code used in :py:func:`waflib.Tools.python.install_pyfile` for installing python files
"""

DISTUTILS_IMP = ['from distutils.sysconfig import get_config_var, get_python_lib']

@extension('.py')
def process_py(self, node):
	"""
	Add a callback using :py:func:`waflib.Tools.python.install_pyfile` to install a python file
	"""
	try:
		if not self.bld.is_install:
			return
	except AttributeError:
		return

	try:
		if not self.install_path:
			return
	except AttributeError:
		self.install_path = '${PYTHONDIR}'

	# i wonder now why we wanted to do this after the build is over
	# issue #901: people want to preserve the structure of installed files
	def inst_py(ctx):
		install_from = getattr(self, 'install_from', None)
		if install_from:
			install_from = self.path.find_dir(install_from)
		install_pyfile(self, node, install_from)
	self.bld.add_post_fun(inst_py)

def install_pyfile(self, node, install_from=None):
	"""
	Execute the installation of a python file

	:param node: python file
	:type node: :py:class:`waflib.Node.Node`
	"""

	from_node = install_from or node.parent
	tsk = self.bld.install_as(self.install_path + '/' + node.path_from(from_node), node, postpone=False)
	path = tsk.get_install_path()

	if self.bld.is_install < 0:
		Logs.info("+ removing byte compiled python files")
		for x in 'co':
			try:
				os.remove(path + x)
			except OSError:
				pass

	if self.bld.is_install > 0:
		try:
			st1 = os.stat(path)
		except OSError:
			Logs.error('The python file is missing, this should not happen')

		for x in ['c', 'o']:
			do_inst = self.env['PY' + x.upper()]
			try:
				st2 = os.stat(path + x)
			except OSError:
				pass
			else:
				if st1.st_mtime <= st2.st_mtime:
					do_inst = False

			if do_inst:
				lst = (x == 'o') and [self.env['PYFLAGS_OPT']] or []
				(a, b, c) = (path, path + x, tsk.get_install_path(destdir=False) + x)
				argv = self.env['PYTHON'] + lst + ['-c', INST, a, b, c]
				Logs.info('+ byte compiling %r' % (path + x))
				env = self.env.env or None
				ret = Utils.subprocess.Popen(argv, env=env).wait()
				if ret:
					raise Errors.WafError('py%s compilation failed %r' % (x, path))

@feature('py')
def feature_py(self):
	"""
	Dummy feature which does nothing
	"""
	pass

@feature('pyext')
@before_method('propagate_uselib_vars', 'apply_link')
@after_method('apply_bundle')
def init_pyext(self):
	"""
	Change the values of *cshlib_PATTERN* and *cxxshlib_PATTERN* to remove the
	*lib* prefix from library names.
	"""
	self.uselib = self.to_list(getattr(self, 'uselib', []))
	if not 'PYEXT' in self.uselib:
		self.uselib.append('PYEXT')
	# override shlib_PATTERN set by the osx module
	self.env.cshlib_PATTERN = self.env.cxxshlib_PATTERN = self.env.macbundle_PATTERN = self.env.pyext_PATTERN
	self.env.fcshlib_PATTERN = self.env.dshlib_PATTERN = self.env.pyext_PATTERN

	try:
		if not self.install_path:
			return
	except AttributeError:
		self.install_path = '${PYTHONARCHDIR}'

@feature('pyext')
@before_method('apply_link', 'apply_bundle')
def set_bundle(self):
	if Utils.unversioned_sys_platform() == 'darwin':
		self.mac_bundle = True

@before_method('propagate_uselib_vars')
@feature('pyembed')
def init_pyembed(self):
	"""
	Add the PYEMBED variable.
	"""
	self.uselib = self.to_list(getattr(self, 'uselib', []))
	if not 'PYEMBED' in self.uselib:
		self.uselib.append('PYEMBED')

@conf
def get_python_variables(self, variables, imports=None):
	"""
	Spawn a new python process to dump configuration variables

	:param variables: variables to print
	:type variables: list of string
	:param imports: one import by element
	:type imports: list of string
	:return: the variable values
	:rtype: list of string
	"""
	if not imports:
		try:
			imports = self.python_imports
		except AttributeError:
			imports = DISTUTILS_IMP

	program = list(imports) # copy
	program.append('')
	for v in variables:
		program.append("print(repr(%s))" % v)
	os_env = dict(os.environ)
	try:
		del os_env['MACOSX_DEPLOYMENT_TARGET'] # see comments in the OSX tool
	except KeyError:
		pass

	try:
		out = self.cmd_and_log(self.env.PYTHON + ['-c', '\n'.join(program)], env=os_env)
	except Errors.WafError:
		self.fatal('The distutils module is unusable: install "python-devel"?')
	self.to_log(out)
	return_values = []
	for s in out.split('\n'):
		s = s.strip()
		if not s:
			continue
		if s == 'None':
			return_values.append(None)
		elif (s[0] == "'" and s[-1] == "'") or (s[0] == '"' and s[-1] == '"'):
			return_values.append(eval(s))
		elif s[0].isdigit():
			return_values.append(int(s))
		else: break
	return return_values

@conf
def check_python_headers(conf):
	"""
	Check for headers and libraries necessary to extend or embed python by using the module *distutils*.
	On success the environment variables xxx_PYEXT and xxx_PYEMBED are added:

	* PYEXT: for compiling python extensions
	* PYEMBED: for embedding a python interpreter
	"""

	# FIXME rewrite

	env = conf.env
	if not env['CC_NAME'] and not env['CXX_NAME']:
		conf.fatal('load a compiler first (gcc, g++, ..)')

	if not env['PYTHON_VERSION']:
		conf.check_python_version()

	pybin = conf.env.PYTHON
	if not pybin:
		conf.fatal('Could not find the python executable')

	v = 'prefix SO LDFLAGS LIBDIR LIBPL INCLUDEPY Py_ENABLE_SHARED MACOSX_DEPLOYMENT_TARGET LDSHARED CFLAGS LDVERSION'.split()
	try:
		lst = conf.get_python_variables(["get_config_var('%s') or ''" % x for x in v])
	except RuntimeError:
		conf.fatal("Python development headers not found (-v for details).")

	vals = ['%s = %r' % (x, y) for (x, y) in zip(v, lst)]
	conf.to_log("Configuration returned from %r:\n%r\n" % (pybin, '\n'.join(vals)))

	dct = dict(zip(v, lst))
	x = 'MACOSX_DEPLOYMENT_TARGET'
	if dct[x]:
		conf.env[x] = conf.environ[x] = dct[x]

	env['pyext_PATTERN'] = '%s' + dct['SO'] # not a mistake

	# Check for python libraries for embedding

	all_flags = dct['LDFLAGS'] + ' ' + dct['CFLAGS']
	conf.parse_flags(all_flags, 'PYEMBED')

	all_flags = dct['LDFLAGS'] + ' ' + dct['LDSHARED'] + ' ' + dct['CFLAGS']
	conf.parse_flags(all_flags, 'PYEXT')

	result = None
	#name = 'python' + env['PYTHON_VERSION']

	if not dct["LDVERSION"]:
		dct["LDVERSION"] = env['PYTHON_VERSION']

	# TODO simplify this
	for name in ('python' + dct['LDVERSION'], 'python' + env['PYTHON_VERSION'] + 'm', 'python' + env['PYTHON_VERSION'].replace('.', '')):

		# LIBPATH_PYEMBED is already set; see if it works.
		if not result and env['LIBPATH_PYEMBED']:
			path = env['LIBPATH_PYEMBED']
			conf.to_log("\n\n# Trying default LIBPATH_PYEMBED: %r\n" % path)
			result = conf.check(lib=name, uselib='PYEMBED', libpath=path, mandatory=False, msg='Checking for library %s in LIBPATH_PYEMBED' % name)

		if not result and dct['LIBDIR']:
			path = [dct['LIBDIR']]
			conf.to_log("\n\n# try again with -L$python_LIBDIR: %r\n" % path)
			result = conf.check(lib=name, uselib='PYEMBED', libpath=path, mandatory=False, msg='Checking for library %s in LIBDIR' % name)

		if not result and dct['LIBPL']:
			path = [dct['LIBPL']]
			conf.to_log("\n\n# try again with -L$python_LIBPL (some systems don't install the python library in $prefix/lib)\n")
			result = conf.check(lib=name, uselib='PYEMBED', libpath=path, mandatory=False, msg='Checking for library %s in python_LIBPL' % name)

		if not result:
			path = [os.path.join(dct['prefix'], "libs")]
			conf.to_log("\n\n# try again with -L$prefix/libs, and pythonXY name rather than pythonX.Y (win32)\n")
			result = conf.check(lib=name, uselib='PYEMBED', libpath=path, mandatory=False, msg='Checking for library %s in $prefix/libs' % name)

		if result:
			break # do not forget to set LIBPATH_PYEMBED

	if result:
		env['LIBPATH_PYEMBED'] = path
		env.append_value('LIB_PYEMBED', [name])
	else:
		conf.to_log("\n\n### LIB NOT FOUND\n")

	# under certain conditions, python extensions must link to
	# python libraries, not just python embedding programs.
	if (Utils.is_win32 or sys.platform.startswith('os2')
		or dct['Py_ENABLE_SHARED']):
		env['LIBPATH_PYEXT'] = env['LIBPATH_PYEMBED']
		env['LIB_PYEXT'] = env['LIB_PYEMBED']

	# We check that pythonX.Y-config exists, and if it exists we
	# use it to get only the includes, else fall back to distutils.
	num = '.'.join(env['PYTHON_VERSION'].split('.')[:2])
	conf.find_program([''.join(pybin) + '-config', 'python%s-config' % num, 'python-config-%s' % num, 'python%sm-config' % num], var='PYTHON_CONFIG', mandatory=False)

	includes = []
	if conf.env.PYTHON_CONFIG:
		for incstr in conf.cmd_and_log([ conf.env.PYTHON_CONFIG, '--includes']).strip().split():
			# strip the -I or /I
			if (incstr.startswith('-I') or incstr.startswith('/I')):
				incstr = incstr[2:]
			# append include path, unless already given
			if incstr not in includes:
				includes.append(incstr)
		conf.to_log("Include path for Python extensions (found via python-config --includes): %r\n" % (includes,))
		env['INCLUDES_PYEXT'] = includes
		env['INCLUDES_PYEMBED'] = includes
	else:
		conf.to_log("Include path for Python extensions "
			       "(found via distutils module): %r\n" % (dct['INCLUDEPY'],))
		env['INCLUDES_PYEXT'] = [dct['INCLUDEPY']]
		env['INCLUDES_PYEMBED'] = [dct['INCLUDEPY']]

	# Code using the Python API needs to be compiled with -fno-strict-aliasing
	if env['CC_NAME'] == 'gcc':
		env.append_value('CFLAGS_PYEMBED', ['-fno-strict-aliasing'])
		env.append_value('CFLAGS_PYEXT', ['-fno-strict-aliasing'])
	if env['CXX_NAME'] == 'gcc':
		env.append_value('CXXFLAGS_PYEMBED', ['-fno-strict-aliasing'])
		env.append_value('CXXFLAGS_PYEXT', ['-fno-strict-aliasing'])

	if env.CC_NAME == "msvc":
		from distutils.msvccompiler import MSVCCompiler
		dist_compiler = MSVCCompiler()
		dist_compiler.initialize()
		env.append_value('CFLAGS_PYEXT', dist_compiler.compile_options)
		env.append_value('CXXFLAGS_PYEXT', dist_compiler.compile_options)
		env.append_value('LINKFLAGS_PYEXT', dist_compiler.ldflags_shared)

	# See if it compiles
	try:
		conf.check(header_name='Python.h', define_name='HAVE_PYTHON_H',
		   uselib='PYEMBED', fragment=FRAG,
		   errmsg=':-(')
	except conf.errors.ConfigurationError:
		# python3.2, oh yeah
		xx = conf.env.CXX_NAME and 'cxx' or 'c'

		flags = ['--cflags', '--libs', '--ldflags']

		for f in flags:
			conf.check_cfg(msg='Asking python-config for pyembed %s flags' % f,
				path=conf.env.PYTHON_CONFIG, package='', uselib_store='PYEMBED', args=[f])
		conf.check(header_name='Python.h', define_name='HAVE_PYTHON_H', msg='Getting pyembed flags from python-config',
			fragment=FRAG, errmsg='Could not build a python embedded interpreter',
			features='%s %sprogram pyembed' % (xx, xx))

		for f in flags:
			conf.check_cfg(msg='Asking python-config for pyext %s flags' % f,
				path=conf.env.PYTHON_CONFIG, package='', uselib_store='PYEXT', args=[f])
		conf.check(header_name='Python.h', define_name='HAVE_PYTHON_H', msg='Getting pyext flags from python-config',
			features='%s %sshlib pyext' % (xx, xx), fragment=FRAG, errmsg='Could not build python extensions')

@conf
def check_python_version(conf, minver=None):
	"""
	Check if the python interpreter is found matching a given minimum version.
	minver should be a tuple, eg. to check for python >= 2.4.2 pass (2,4,2) as minver.

	If successful, PYTHON_VERSION is defined as 'MAJOR.MINOR'
	(eg. '2.4') of the actual python version found, and PYTHONDIR is
	defined, pointing to the site-packages directory appropriate for
	this python version, where modules/packages/extensions should be
	installed.

	:param minver: minimum version
	:type minver: tuple of int
	"""
	assert minver is None or isinstance(minver, tuple)
	pybin = conf.env['PYTHON']
	if not pybin:
		conf.fatal('could not find the python executable')

	# Get python version string
	cmd = pybin + ['-c', 'import sys\nfor x in sys.version_info: print(str(x))']
	Logs.debug('python: Running python command %r' % cmd)
	lines = conf.cmd_and_log(cmd).split()
	assert len(lines) == 5, "found %i lines, expected 5: %r" % (len(lines), lines)
	pyver_tuple = (int(lines[0]), int(lines[1]), int(lines[2]), lines[3], int(lines[4]))

	# compare python version with the minimum required
	result = (minver is None) or (pyver_tuple >= minver)

	if result:
		# define useful environment variables
		pyver = '.'.join([str(x) for x in pyver_tuple[:2]])
		conf.env['PYTHON_VERSION'] = pyver

		if 'PYTHONDIR' in conf.environ:
			pydir = conf.environ['PYTHONDIR']
		else:
			if Utils.is_win32:
				(python_LIBDEST, pydir) = conf.get_python_variables(
					  ["get_config_var('LIBDEST') or ''",
					   "get_python_lib(standard_lib=0, prefix=%r) or ''" % conf.env['PREFIX']])
			else:
				python_LIBDEST = None
				(pydir,) = conf.get_python_variables( ["get_python_lib(standard_lib=0, prefix=%r) or ''" % conf.env['PREFIX']])
			if python_LIBDEST is None:
				if conf.env['LIBDIR']:
					python_LIBDEST = os.path.join(conf.env['LIBDIR'], "python" + pyver)
				else:
					python_LIBDEST = os.path.join(conf.env['PREFIX'], "lib", "python" + pyver)


		if 'PYTHONARCHDIR' in conf.environ:
			pyarchdir = conf.environ['PYTHONARCHDIR']
		else:
			(pyarchdir, ) = conf.get_python_variables( ["get_python_lib(plat_specific=1, standard_lib=0, prefix=%r) or ''" % conf.env['PREFIX']])
			if not pyarchdir:
				pyarchdir = pydir

		if hasattr(conf, 'define'): # conf.define is added by the C tool, so may not exist
			conf.define('PYTHONDIR', pydir)
			conf.define('PYTHONARCHDIR', pyarchdir)

		conf.env['PYTHONDIR'] = pydir
		conf.env['PYTHONARCHDIR'] = pyarchdir

	# Feedback
	pyver_full = '.'.join(map(str, pyver_tuple[:3]))
	if minver is None:
		conf.msg('Checking for python version', pyver_full)
	else:
		minver_str = '.'.join(map(str, minver))
		conf.msg('Checking for python version', pyver_tuple, ">= %s" % (minver_str,) and 'GREEN' or 'YELLOW')

	if not result:
		conf.fatal('The python version is too old, expecting %r' % (minver,))

PYTHON_MODULE_TEMPLATE = '''
import %s as current_module
version = getattr(current_module, '__version__', None)
if version is not None:
    print(str(version))
else:
    print('unknown version')
'''

@conf
def check_python_module(conf, module_name, condition=''):
	"""
	Check if the selected python interpreter can import the given python module::

		def configure(conf):
			conf.check_python_module('pygccxml')
			conf.check_python_module('re', condition="ver > num(2, 0, 4) and ver <= num(3, 0, 0)")

	:param module_name: module
	:type module_name: string
	"""
	msg = 'Python module %s' % module_name
	if condition:
		msg = '%s (%s)' % (msg, condition)
	conf.start_msg(msg)
	try:
		ret = conf.cmd_and_log(conf.env['PYTHON'] + ['-c', PYTHON_MODULE_TEMPLATE % module_name])
	except Exception:
		conf.end_msg(False)
		conf.fatal('Could not find the python module %r' % module_name)

	ret = ret.strip()
	if condition:
		conf.end_msg(ret)
		if ret == 'unknown version':
			conf.fatal('Could not check the %s version' % module_name)

		from distutils.version import LooseVersion
		def num(*k):
			if isinstance(k[0], int):
				return LooseVersion('.'.join([str(x) for x in k]))
			else:
				return LooseVersion(k[0])
		d = {'num': num, 'ver': LooseVersion(ret)}
		ev = eval(condition, {}, d)
		if not ev:
			conf.fatal('The %s version does not satisfy the requirements' % module_name)
	else:
		if ret == 'unknown version':
			conf.end_msg(True)
		else:
			conf.end_msg(ret)

def configure(conf):
	"""
	Detect the python interpreter
	"""
	try:
		conf.find_program('python', var='PYTHON')
	except conf.errors.ConfigurationError:
		Logs.warn("could not find a python executable, setting to sys.executable '%s'" % sys.executable)
		conf.env.PYTHON = sys.executable

	if conf.env.PYTHON != sys.executable:
		Logs.warn("python executable %r differs from system %r" % (conf.env.PYTHON, sys.executable))
	conf.env.PYTHON = conf.cmd_to_list(conf.env.PYTHON)

	v = conf.env
	v['PYCMD'] = '"import sys, py_compile;py_compile.compile(sys.argv[1], sys.argv[2])"'
	v['PYFLAGS'] = ''
	v['PYFLAGS_OPT'] = '-O'

	v['PYC'] = getattr(Options.options, 'pyc', 1)
	v['PYO'] = getattr(Options.options, 'pyo', 1)

def options(opt):
	"""
	Add the options ``--nopyc`` and ``--nopyo``
	"""
	opt.add_option('--nopyc',
			action='store_false',
			default=1,
			help = 'Do not install bytecode compiled .pyc files (configuration) [Default:install]',
			dest = 'pyc')
	opt.add_option('--nopyo',
			action='store_false',
			default=1,
			help='Do not install optimised compiled .pyo files (configuration) [Default:install]',
			dest='pyo')

