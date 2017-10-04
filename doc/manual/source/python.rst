.. include:: replace.txt
.. highlight:: python

Using Python to Run |ns3|
-------------------------

Python bindings allow the C++ code in |ns3| to be called from Python.

This chapter shows you how to create a Python script that can run |ns3| and also the process of creating Python bindings for a C++ |ns3| module.

Introduction
************

Python bindings provide support for importing |ns3| model libraries as Python
modules.  Coverage of most of the |ns3| C++ API is provided.  The intent
has been to allow the programmer to write complete simulation scripts in
Python, to allow integration of |ns3| with other Python tools and workflows.
The intent is not to provide a different language choice to author new
|ns3| models implemented in Python.

Python bindings for |ns3| use a tool called PyBindGen (https://github.com/gjcarneiro/pybindgen).

An Example Python Script that Runs |ns3|
****************************************

Here is some example code that is written in Python and that runs |ns3|, which is written in C++.  This Python example can be found in ``examples/tutorial/first.py``:

::

  import ns.applications
  import ns.core
  import ns.internet
  import ns.network
  import ns.point_to_point
  
  ns.core.LogComponentEnable("UdpEchoClientApplication", ns.core.LOG_LEVEL_INFO)
  ns.core.LogComponentEnable("UdpEchoServerApplication", ns.core.LOG_LEVEL_INFO)
  
  nodes = ns.network.NodeContainer()
  nodes.Create(2)
  
  pointToPoint = ns.point_to_point.PointToPointHelper()
  pointToPoint.SetDeviceAttribute("DataRate", ns.core.StringValue("5Mbps"))
  pointToPoint.SetChannelAttribute("Delay", ns.core.StringValue("2ms"))
  
  devices = pointToPoint.Install(nodes)
  
  stack = ns.internet.InternetStackHelper()
  stack.Install(nodes)
  
  address = ns.internet.Ipv4AddressHelper()
  address.SetBase(ns.network.Ipv4Address("10.1.1.0"), ns.network.Ipv4Mask("255.255.255.0"))
  
  interfaces = address.Assign (devices);
  
  echoServer = ns.applications.UdpEchoServerHelper(9)
  
  serverApps = echoServer.Install(nodes.Get(1))
  serverApps.Start(ns.core.Seconds(1.0))
  serverApps.Stop(ns.core.Seconds(10.0))
  
  echoClient = ns.applications.UdpEchoClientHelper(interfaces.GetAddress(1), 9)
  echoClient.SetAttribute("MaxPackets", ns.core.UintegerValue(1))
  echoClient.SetAttribute("Interval", ns.core.TimeValue(ns.core.Seconds (1.0)))
  echoClient.SetAttribute("PacketSize", ns.core.UintegerValue(1024))
  
  clientApps = echoClient.Install(nodes.Get(0))
  clientApps.Start(ns.core.Seconds(2.0))
  clientApps.Stop(ns.core.Seconds(10.0))
  
  ns.core.Simulator.Run()
  ns.core.Simulator.Destroy()

Running Python Scripts
**********************

waf contains some options that automatically update the python path to find the ns3 module.  To run example programs, there are two ways to use waf to take care of this.  One is to run a waf shell; e.g.:

.. sourcecode:: bash

  $ ./waf shell
  $ python examples/wireless/mixed-wireless.py

and the other is to use the --pyrun option to waf:

.. sourcecode:: bash

  $ ./waf --pyrun examples/wireless/mixed-wireless.py

To run a python script under the C debugger:

.. sourcecode:: bash

  $ ./waf shell
  $ gdb --args python examples/wireless/mixed-wireless.py

To run your own Python script that calls |ns3| and that has this path, ``/path/to/your/example/my-script.py``, do the following:

.. sourcecode:: bash

  $ ./waf shell
  $ python /path/to/your/example/my-script.py

Caveats
*******

Python bindings for |ns3| are a work in progress, and some limitations are known by developers.  Some of these limitations (not all) are listed here.

Incomplete Coverage
+++++++++++++++++++

First of all, keep in mind that not 100% of the API is supported in Python.  Some of the reasons are:

#. some of the APIs involve pointers, which require knowledge of what kind of memory passing semantics (who owns what memory). Such knowledge is not part of the function signatures, and is either documented or sometimes not even documented.  Annotations are needed to bind those functions;
#. Sometimes a unusual fundamental data type or C++ construct is used which is not yet supported by PyBindGen;
#. GCC-XML does not report template based classes unless they are instantiated.

Most of the missing APIs can be wrapped, given enough time, patience, and expertise, and will likely be wrapped if bug reports are submitted.  However, don't file a bug report saying "bindings are incomplete", because we do not have manpower to complete 100% of the bindings.

Conversion Constructors
+++++++++++++++++++++++

`Conversion constructors <http://publib.boulder.ibm.com/infocenter/compbgpl/v9v111/topic/com.ibm.xlcpp9.bg.doc/language_ref/cplr384.htm>`_ are not fully supported yet by PyBindGen, and they always act as explicit constructors when translating an API into Python.  For example, in C++ you can do this:

.. sourcecode:: cpp

 Ipv4AddressHelper ipAddrs;
 ipAddrs.SetBase ("192.168.0.0", "255.255.255.0");
 ipAddrs.Assign (backboneDevices);

In Python, for the time being you have to do:

::

 ipAddrs = ns.internet.Ipv4AddressHelper()
 ipAddrs.SetBase(ns.network.Ipv4Address("192.168.0.0"), ns.network.Ipv4Mask("255.255.255.0"))
 ipAddrs.Assign(backboneDevices)

CommandLine
+++++++++++

:cpp:func:`CommandLine::AddValue` works differently in Python than it does in |ns3|.  In Python, the first parameter is a string that represents the command-line option name.  When the option is set, an attribute with the same name as the option name is set on the :cpp:func:`CommandLine` object.  Example:

::

    NUM_NODES_SIDE_DEFAULT = 3

    cmd = ns3.CommandLine()

    cmd.NumNodesSide = None
    cmd.AddValue("NumNodesSide", "Grid side number of nodes (total number of nodes will be this number squared)")

    cmd.Parse(argv)

    [...]

    if cmd.NumNodesSide is None:
        num_nodes_side = NUM_NODES_SIDE_DEFAULT
    else:
        num_nodes_side = int(cmd.NumNodesSide)

Tracing
+++++++

Callback based tracing is not yet properly supported for Python, as new |ns3| API needs to be provided for this to be supported.

Pcap file writing is supported via the normal API.

Ascii tracing is supported since |ns3|.4 via the normal C++ API translated to Python.  However, ascii tracing requires the creation of an ostream object to pass into the ascii tracing methods.  In Python, the C++ std::ofstream has been minimally wrapped to allow this.  For example:

::

    ascii = ns3.ofstream("wifi-ap.tr") # create the file
    ns3.YansWifiPhyHelper.EnableAsciiAll(ascii)
    ns3.Simulator.Run()
    ns3.Simulator.Destroy()
    ascii.close() # close the file

There is one caveat: you must not allow the file object to be garbage collected while |ns3| is still using it.  That means that the 'ascii' variable above must not be allowed to go out of scope or else the program will crash.

Cygwin limitation
+++++++++++++++++

Python bindings do not work on Cygwin.  This is due to a gccxml bug.

You might get away with it by re-scanning API definitions from within the
cygwin environment (./waf --apiscan=all).  However the most likely solution
will probably have to be that we disable python bindings in CygWin.

If you really care about Python bindings on Windows, try building with mingw and native
python instead.  Or else, to build without python bindings, disable python bindings in the configuration stage:  

.. sourcecode:: bash

  $ ./waf configure --disable-python

Working with Python Bindings
****************************

Python bindings are built on a module-by-module basis, and can be found in each module's  ``bindings`` directory. 

Python Bindings Workflow
++++++++++++++++++++++++

The process by which Python bindings are handled is the following:

#. Periodically a developer uses a GCC-XML (http://www.gccxml.org) based API scanning script, which saves the scanned API definition as ``bindings/python/ns3_module_*.py`` files or as Python files in each modules' ``bindings`` directory.  These files are kept under version control in the main |ns3| repository;
#. Other developers clone the repository and use the already scanned API definitions;
#. When configuring |ns3|, pybindgen will be automatically downloaded if not already installed.  Released |ns3| tarballs will ship a copy of pybindgen.

If something goes wrong with compiling Python bindings and you just want to ignore them and move on with C++, you can disable Python with:

.. sourcecode:: bash

  $ ./waf --disable-python

Instructions for Handling New Files or Changed API's
****************************************************

So you have been changing existing |ns3| APIs and Python bindings no longer compile?  Do not despair, you can rescan the bindings to create new bindings that reflect the changes to the |ns3| API.

Overview
++++++++

The python bindings are generated into an 'ns' namespace.  Examples:

::

  from ns.network import Node
  n1 = Node()

or

::

  import ns.network
  n1 = ns.network.Node()

The best way to explore the bindings is to look at the various example
programs provided in |ns3|; some C++ examples have a corresponding Python
example.  There is no structured documentation for the Python bindings
like there is Doxygen for the C++ API, but the Doxygen can be consulted
to understand how the C++ API works.

Scanning the Modular Python Bindings
++++++++++++++++++++++++++++++++++++

Scanning of the C++ API is only necessary if a user is using Python and
is changing the C++ API to introduce new methods (that he or she wishes
to be accessible from Python) or is changing the C++ API in a way that
breaks the compilation of the existing Python bindings.

There are two steps.  First, the bindings toolchain must be enabled in
the |ns3| build.  This requires that the gccxml and pygccxml tools be
installed on the system or using the bake build tool.  Second, Waf
can be used to update the bindings.

The output of './waf configure' can be inspected to see if Python API scanning
support is enabled:

::

  Python API Scanning Support   : enabled

It may say something like this, if the support is not active:

::

  Python API Scanning Support   : not enabled (Missing 'pygccxml' Python module)

In this case, the user must take steps to install gccxml and pygccxml;
gccxml binary must be in the shell's path, and pygccxml must be in the
Python path.

An automated setup for this is provided by the `bake` build system, if the
user selects the 'ns-allinone-3.nn' configuration target (where 'nn' is the
release number.  For example:

::

  ./bake.py configure -e ns-allinone-3.26
  ./bake.py download
  ./bake.py build

At present, this toolchain is only supported for gcc version 4; gcc-5
and gcc-6 are not supported due to the gccxml project stopping maintenance
a few years ago.  clang compiler is also not supported.  The |ns3| project
plans to convert to the CastXML project to replace gccxml in the future,
in which case newer versions of gcc as well as clang will be supported.

Once API scanning support is enabled, to scan the modular Python bindings 
for the core module, for example, do the following:

.. sourcecode:: bash

  $ ./waf --apiscan=core

To scan the modular Python bindings for all of the modules, do the following:

.. sourcecode:: bash

  $ ./waf --apiscan=all

Adding Modular Bindings To A Existing or New Module
+++++++++++++++++++++++++++++++++++++++++++++++++++

To add support for modular bindings to an existing or new |ns3| module, simply add the following line to its wscript build() function:

::

    bld.ns3_python_bindings()

Organization of the Modular Python Bindings
+++++++++++++++++++++++++++++++++++++++++++

The ``src/<module>/bindings`` directory may contain the following files, some of them optional:

* ``callbacks_list.py``: this is a scanned file, DO NOT TOUCH.  Contains a list of Callback<...> template instances found in the scanned headers;
* ``modulegen__gcc_LP64.py``: this is a scanned file, DO NOT TOUCH.  Scanned API definitions for the GCC, LP64 architecture (64-bit)
* ``modulegen__gcc_ILP32.py``: this is a scanned file, DO NOT TOUCH.  Scanned API definitions for the GCC, ILP32 architecture (32-bit)
* ``modulegen_customizations.py``: you may optionally add this file in order to customize the pybindgen code generation
* ``scan-header.h``: you may optionally add this file to customize what header file is scanned for the module.  Basically this file is scanned instead of ns3/<module>-module.h.  Typically, the first statement is #include "ns3/<module>-module.h", plus some other stuff to force template instantiations;
* ``module_helpers.cc``: you may add additional files, such as this, to be linked to python extension module, but they have to be registered in the wscript. Look at src/core/wscript for an example of how to do so;
* ``<module>.py``: if this file exists, it becomes the "frontend" python module for the ns3 module, and the extension module (.so file) becomes _<module>.so instead of <module>.so.  The <module>.py file has to import all symbols from the module _<module> (this is more tricky than it sounds, see src/core/bindings/core.py for an example), and then can add some additional pure-python definitions.   

More Information for Developers
*******************************

If you are a developer and need more information on |ns3|'s Python bindings, please see the `Python Bindings wiki page <http://www.nsnam.org/wiki/NS-3_Python_Bindings>`_.
