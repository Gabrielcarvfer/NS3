import ns.point_to_point
import ns.csma
import ns.wifi
import ns.bridge
import ns.internet
import ns.mesh
import ns.wimax
import ns.wimax
import ns.lte

import gobject
import os.path
import sys

PIXELS_PER_METER = 3.0 # pixels-per-meter, at 100% zoom level

class PyVizObject(gobject.GObject):
    __gtype_name__ = "PyVizObject"

    def tooltip_query(self, tooltip):
        tooltip.set_text("TODO: tooltip for %r" % self)

class Link(PyVizObject):
    pass


class InformationWindow(object):
    def update(self):
        raise NotImplementedError

class NetDeviceTraits(object):
    def __init__(self, is_wireless=None, is_virtual=False):
        assert is_virtual or is_wireless is not None
        self.is_wireless = is_wireless
        self.is_virtual = is_virtual

netdevice_traits = {
    ns.point_to_point.PointToPointNetDevice: NetDeviceTraits(is_wireless=False),
    ns.csma.CsmaNetDevice: NetDeviceTraits(is_wireless=False),
    ns.wifi.WifiNetDevice: NetDeviceTraits(is_wireless=True),
    ns.bridge.BridgeNetDevice: NetDeviceTraits(is_virtual=True),
    ns.internet.LoopbackNetDevice: NetDeviceTraits(is_virtual=True, is_wireless=False),
    ns.mesh.MeshPointDevice: NetDeviceTraits(is_virtual=True),
    ns.wimax.SubscriberStationNetDevice: NetDeviceTraits(is_wireless=True),
    ns.wimax.BaseStationNetDevice: NetDeviceTraits(is_wireless=True),
    ns.lte.LteUeNetDevice: NetDeviceTraits(is_wireless=True),
    ns.lte.LteEnbNetDevice: NetDeviceTraits(is_wireless=True),
}

def lookup_netdevice_traits(class_type):
    try:
        return netdevice_traits[class_type]
    except KeyError:
        sys.stderr.write("WARNING: no NetDeviceTraits registered for device type %r; "
                         "I will assume this is a non-virtual wireless device, "
                         "but you should edit %r, variable 'netdevice_traits',"
                         " to make sure.\n" % (class_type.__name__, __file__))
        t = NetDeviceTraits(is_virtual=False, is_wireless=True)
        netdevice_traits[class_type] = t
        return t

def transform_distance_simulation_to_canvas(d):
    return d*PIXELS_PER_METER

def transform_point_simulation_to_canvas(x, y):
    return x*PIXELS_PER_METER, y*PIXELS_PER_METER

def transform_distance_canvas_to_simulation(d):
    return d/PIXELS_PER_METER

def transform_point_canvas_to_simulation(x, y):
    return x/PIXELS_PER_METER, y/PIXELS_PER_METER




plugins = []
plugin_modules = {}

def register_plugin(plugin_init_func, plugin_name=None, plugin_module=None):
    """
    Register a plugin.

    @param plugin: a callable object that will be invoked whenever a
    Visualizer object is created, like this: plugin(visualizer)
    """
    assert callable(plugin_init_func)
    plugins.append(plugin_init_func)
    if plugin_module is not None:
        plugin_modules[plugin_name] = plugin_module

plugins_loaded = False
def load_plugins():
    global plugins_loaded
    if plugins_loaded:
        return
    plugins_loaded = True
    plugins_dir = os.path.join(os.path.dirname(__file__), 'plugins')
    old_path = list(sys.path)
    sys.path.insert(0, plugins_dir)
    for filename in os.listdir(plugins_dir):
        name, ext = os.path.splitext(filename)
        if ext != '.py':
            continue
        try:
            plugin_module = __import__(name)
        except ImportError, ex:
            print >> sys.stderr, "Could not load plugin %r: %s" % (filename, str(ex))
            continue
        try:
            plugin_func = plugin_module.register
        except AttributeError:
            print >> sys.stderr, "Plugin %r has no 'register' function" % name
        else:
            #print >> sys.stderr, "Plugin %r registered" % name
            register_plugin(plugin_func, name, plugin_module)
    sys.path = old_path

