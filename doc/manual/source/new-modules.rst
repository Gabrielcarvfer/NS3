.. include:: replace.txt
.. highlight:: cpp

Adding a New Module to |ns3|
----------------------------

When you have created a group of related classes, examples, and tests,
they can be combined together into an |ns3| module so that they can be
used with existing |ns3| modules and by other researchers.

This chapter walks you through the steps necessary to add a new module
to |ns3|.

.. _Step-0:

Step 0 - Module Layout
**********************

All modules can be found in the ``src`` directory.  Each module can be
found in a directory that has the same name as the module.  For
example, the ``spectrum`` module can be found here: ``src/spectrum``.
We'll be quoting from the ``spectrum`` module for illustration.

A prototypical module has the following directory structure and
required files:

.. sourcecode:: text

  src/
    module-name/
      bindings/
      doc/
      examples/
        wscript
      helper/
      model/
      test/
        examples-to-run.py
      wscript

Not all directories will be present in each module.

Step 1 - Create a Module Skeleton
*********************************

A python program is provided in the source directory that
will create a skeleton for a new module.  For the purposes
of this discussion we will assume that your new module
is called ``new-module``.  From the ``src`` directory, do the following
to create the new module:

.. sourcecode:: bash

  $ ./create-module.py new-module

Next, ``cd`` into ``new-module``; you will find this directory layout:

.. sourcecode:: text

  $ cd new-module
  $ ls
  doc examples  helper  model  test  wscript

In more detail, the ``create-module.py`` script will create the
directories as well as initial skeleton ``wscript``, ``.h``, ``.cc``
and ``.rst`` files.  The complete module with skeleton files looks like this:

.. sourcecode:: text

    src/
      new-module/
        doc/
	  new-module.rst
	examples/
	  new-module-example.cc
	  wscript
	helper/
	  new-module-helper.cc
	  new-module-helper.h
	model/
	  new-module.cc
	  new-module.h
	test/
	  new-module-test-suite.cc
	wscript

(If required the ``bindings/`` directory listed in
:ref:`Step-0 <Step-0>` will be created automatically during
the build.)

We next walk through how to customize this module.  Informing ``waf``
about the files which make up your module is done by editing the two
``wscript`` files.  We will walk through the main steps in this chapter.

All |ns3| modules depend on the ``core`` module and usually on
other modules.  This dependency is specified in the ``wscript`` file
(at the top level of the module, not the separate ``wscript`` file
in the ``examples`` directory!).  In the skeleton ``wscript``
the call that will declare your new module to ``waf`` will look
like this (before editing):

.. sourcecode:: python

  def build(bld):
      module = bld.create_ns3_module('new-module', ['core'])

Let's assume that ``new-module`` depends on the ``internet``,
``mobility``, and ``aodv`` modules.  After editing it the ``wscript`` file
should look like:

.. sourcecode:: python

  def build(bld):
      module = bld.create_ns3_module('new-module', ['internet', 'mobility', 'aodv'])

Note that only first level module dependencies should be listed, which
is why we removed ``core``; the ``internet`` module in turn depends on
``core``.

Your module will most likely have model source files.  Initial skeletons
(which will compile successfully) are created in ``model/new-module.cc``
and ``model/new-module.h``.  

If your module will have helper source files, then they will go into
the ``helper/`` directory; again, initial skeletons are created
in that directory.

Finally, it is good practice to write tests and examples.  These will
almost certainly be required for new modules to be accepted into
the official |ns3| source tree.  A skeleton
test suite and test case is created in the ``test/`` directory.
The skeleton test suite will contain the below constructor,
which declares a new unit test named ``new-module``,
with a single test case consisting of the class ``NewModuleTestCase1``::

  NewModuleTestSuite::NewModuleTestSuite ()
    : TestSuite ("new-module", UNIT)
  {
    AddTestCase (new NewModuleTestCase1);
  }

Step 3 - Declare Source Files
*****************************

The public header and source code files for your new module
should be specified in the ``wscript`` file by modifying it with
your text editor.

As an example, after declaring the ``spectrum`` module,
the ``src/spectrum/wscript`` specifies the source code files
with the following list:

.. sourcecode:: python

   def build(bld):

     module = bld.create_ns3_module('spectrum', ['internet', 'propagation', 'antenna', 'applications'])

     module.source = [
         'model/spectrum-model.cc',
         'model/spectrum-value.cc',
               .
	       .
	       .
         'model/microwave-oven-spectrum-value-helper.cc',
         'helper/spectrum-helper.cc',
         'helper/adhoc-aloha-noack-ideal-phy-helper.cc',
         'helper/waveform-generator-helper.cc',
         'helper/spectrum-analyzer-helper.cc',
         ]

The objects resulting from compiling these sources will be assembled
into a link library, which will be linked to any programs relying on this
module.

But how do such programs learn the public API of our new module?  Read on!

Step 4 - Declare Public Header Files
************************************

The header files defining the public API of your model and helpers
also should be specified in the ``wscript`` file.

Continuing with the ``spectrum`` model illustration,
the public header files are specified with the following stanza.
(Note that the argument to the ``bld`` function tells
``waf`` to install this module's headers with the other |ns3| headers):

.. sourcecode:: python

    headers = bld(features='ns3header')

    headers.module = 'spectrum'

    headers.source = [
        'model/spectrum-model.h',
        'model/spectrum-value.h',
               .
	       .
	       .
        'model/microwave-oven-spectrum-value-helper.h',
        'helper/spectrum-helper.h',
        'helper/adhoc-aloha-noack-ideal-phy-helper.h',
        'helper/waveform-generator-helper.h',
        'helper/spectrum-analyzer-helper.h',
        ]

Headers made public in this way will be accessible to users of your model
with include statements like

.. sourcecode:: cpp

    #include "ns3/spectrum-model.h"
    	
Headers used strictly internally in your implementation should not
be included here.  They are still accessible to your implemenation by
include statements like

.. sourcecode:: cpp

    #include "my-module-implementation.h"


Step 5 - Declare Tests
**********************

If your new module has tests, then they must be specified in your
``wscript`` file by modifying it with your text editor.

The ``spectrum`` model tests are specified with the following stanza:

.. sourcecode:: python

    module_test = bld.create_ns3_module_test_library('spectrum')

    module_test.source = [
        'test/spectrum-interference-test.cc',
        'test/spectrum-value-test.cc',
        ]

See :doc:`Tests <tests>` for more information on how to write test cases.	

Step 6 - Declare Examples
*************************

If your new module has examples, then they must be specified in your
``examples/wscript`` file.  (The skeleton top-level ``wscript`` will
recursively include ``examples/wscript`` only if the examples were
enabled at configure time.)

The ``spectrum`` model defines it's first example in
``src/spectrum/examples/wscript`` with

.. sourcecode:: python

  def build(bld):
    obj = bld.create_ns3_program('adhoc-aloha-ideal-phy',
                                 ['spectrum', 'mobility'])
    obj.source = 'adhoc-aloha-ideal-phy.cc'

Note that the second argument to the function ``create_ns3_program()``
is the list of modules that the program being created depends on; again,
don't forget to include ``new-module`` in the list.  It's best practice
to list only the direct module dependencies, and let ``waf`` deduce
the full dependency tree.

Occasionally, for clarity, you may want to split the implementation
for your example among several source files.  In this case, just
include those files as additional explicit sources of the example:

.. sourcecode:: python

   obj = bld.create_ns3_program('new-module-example', [new-module])
   obj.source = ['new-module-example.cc', 'new-module-example-part.cc']

Python examples are specified using the following
function call.  Note that the second argument for the function
``register_ns3_script()`` is the list of modules that the Python example
depends on:

.. sourcecode:: python

    bld.register_ns3_script('new-module-example.py', ['new-module'])

Step 7 - Examples Run as Tests
******************************

In addition to running explicit test code, the test framework
can also be instrumented to run full example programs to
try to catch regressions in the examples.  However, not all examples
are suitable for regression tests.  The file ``test/examples-to-run.py``
controls the invocation of the examples when the test framework runs.

The ``spectrum`` model examples run by ``test.py`` are specified in
``src/spectrum/test/examples-to-run.py`` using the following
two lists of C++ and Python examples:

.. sourcecode:: python

  # A list of C++ examples to run in order to ensure that they remain
  # buildable and runnable over time.  Each tuple in the list contains
  #
  #     (example_name, do_run, do_valgrind_run).
  #
  # See test.py for more information.
  cpp_examples = [
      ("adhoc-aloha-ideal-phy", "True", "True"),
      ("adhoc-aloha-ideal-phy-with-microwave-oven", "True", "True"),
      ("adhoc-aloha-ideal-phy-matrix-propagation-loss-model", "True", "True"),
  ]
  
  # A list of Python examples to run in order to ensure that they remain
  # runnable over time.  Each tuple in the list contains
  #
  #     (example_name, do_run).
  #
  # See test.py for more information.
  python_examples = [
      ("sample-simulator.py", "True"),
  ]

As indicated in the comment, each entry in the C++ list of examples to run
contains the tuple ``(example_name, do_run, do_valgrind_run)``, where

  * ``example_name`` is the executable to be run,
  * ``do_run`` is a condition under which to run the example, and
  * ``do_valgrind_run`` is a condition under which to run the example
    under valgrind.  (This is needed because NSC causes illegal instruction
    crashes with some tests when they are run under valgrind.)

Note that the two conditions are Python statements that
can depend on ``waf`` configuration variables.  For example,

.. sourcecode:: python

    ("tcp-nsc-lfn", "NSC_ENABLED == True", "NSC_ENABLED == False"),

Each entry in the Python list of examples to run contains the tuple
``(example_name, do_run)``, where, as for the C++ examples,

  * ``example_name`` is the Python script to be run, and
  * ``do_run`` is a condition under which to run the example.

Again, the condition is a Python statement that can
depend on ``waf`` configuration variables.  For example,

.. sourcecode:: python

    ("realtime-udp-echo.py", "ENABLE_REAL_TIME == False"),


Step 8 - Configure and Build
****************************

You can now configure, build and test your module as normal.
You must reconfigure the project as a first step so that ``waf``
caches the new information in your ``wscript`` files,
or else your new module will not be included in the build.

.. sourcecode:: bash

  $ ./waf configure --enable-examples --enable-tests
  $ ./waf build
  $ ./test.py

Look for your new module's test suite (and example programs,
if your module has any enabled) in the test output.


Step 9 - Python Bindings
************************

Adding Python bindings to your module is optional, and the step is
commented out by default in the ``create-module.py`` script.

.. sourcecode:: python

    # bld.ns3_python_bindings()

If you want to include Python bindings (needed only if you want
to write Python ns-3 programs instead of C++ ns-3 programs), you
should uncomment the above and install the Python API scanning
system (covered elsewhere in this manual) and scan your module to
generate new bindings.
