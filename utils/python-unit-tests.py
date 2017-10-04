import unittest
from ns.core import Simulator, Seconds, Config, int64x64_t
import ns.core
import ns.network
import ns.internet
import ns.mobility
import ns.csma
import ns.applications


class TestSimulator(unittest.TestCase):

    def testScheduleNow(self):
        def callback(args):
            self._args_received = args
            self._cb_time = Simulator.Now()
        Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        Simulator.ScheduleNow(callback, "args")
        Simulator.Run()
        self.assertEqual(self._args_received, "args")
        self.assertEqual(self._cb_time.GetSeconds(), 0.0)

    def testSchedule(self):
        def callback(args):
            self._args_received = args
            self._cb_time = Simulator.Now()
        Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        Simulator.Schedule(Seconds(123), callback, "args")
        Simulator.Run()
        self.assertEqual(self._args_received, "args")
        self.assertEqual(self._cb_time.GetSeconds(), 123.0)

    def testScheduleDestroy(self):
        def callback(args):
            self._args_received = args
            self._cb_time = Simulator.Now()
        Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        def null(): pass
        Simulator.Schedule(Seconds(123), null)
        Simulator.ScheduleDestroy(callback, "args")
        Simulator.Run()
        Simulator.Destroy()
        self.assertEqual(self._args_received, "args")
        self.assertEqual(self._cb_time.GetSeconds(), 123.0)

    def testScheduleWithContext(self):
        def callback(context, args):
            self._context_received = context
            self._args_received = args
            self._cb_time = Simulator.Now()
        Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        self._context_received = None
        Simulator.ScheduleWithContext(54321, Seconds(123), callback, "args")
        Simulator.Run()
        self.assertEqual(self._context_received, 54321)
        self.assertEqual(self._args_received, "args")
        self.assertEqual(self._cb_time.GetSeconds(), 123.0)

    def testTimeComparison(self):
        self.assert_(Seconds(123) == Seconds(123))
        self.assert_(Seconds(123) >= Seconds(123))
        self.assert_(Seconds(123) <= Seconds(123))
        self.assert_(Seconds(124) > Seconds(123))
        self.assert_(Seconds(123) < Seconds(124))

    def testTimeNumericOperations(self):
        self.assertEqual(Seconds(10) + Seconds(5), Seconds(15))
        self.assertEqual(Seconds(10) - Seconds(5), Seconds(5))
        
        v1 = int64x64_t(5.0)*int64x64_t(10)
        self.assertEqual(v1, int64x64_t(50))

    def testConfig(self):
        Config.SetDefault("ns3::OnOffApplication::PacketSize", ns.core.UintegerValue(123))
        # hm.. no Config.Get?

    def testSocket(self):
        node = ns.network.Node()
        internet = ns.internet.InternetStackHelper()
        internet.Install(node)
        self._received_packet = None

        def rx_callback(socket):
            assert self._received_packet is None
            self._received_packet = socket.Recv()

        sink = ns.network.Socket.CreateSocket(node, ns.core.TypeId.LookupByName("ns3::UdpSocketFactory"))
        sink.Bind(ns.network.InetSocketAddress(ns.network.Ipv4Address.GetAny(), 80))
        sink.SetRecvCallback(rx_callback)

        source = ns.network.Socket.CreateSocket(node, ns.core.TypeId.LookupByName("ns3::UdpSocketFactory"))
        source.SendTo(ns.network.Packet(19), 0, ns.network.InetSocketAddress(ns.network.Ipv4Address("127.0.0.1"), 80))

        Simulator.Run()
        self.assert_(self._received_packet is not None)
        self.assertEqual(self._received_packet.GetSize(), 19)


    def testAttributes(self):
        ##
        ## Yes, I know, the GetAttribute interface for Python is
        ## horrible, we should fix this soon, I hope.
        ##
        queue = ns.network.DropTailQueue()

        queue.SetAttribute("MaxPackets", ns.core.UintegerValue(123456))

        limit = ns.core.UintegerValue()
        queue.GetAttribute("MaxPackets", limit)
        self.assertEqual(limit.Get(), 123456)

        ## -- object pointer values
        mobility = ns.mobility.RandomWaypointMobilityModel()
        ptr = ns.core.PointerValue()
        mobility.GetAttribute("PositionAllocator", ptr)
        self.assertEqual(ptr.GetObject(), None)
        
        pos = ns.mobility.ListPositionAllocator()
        mobility.SetAttribute("PositionAllocator", ns.core.PointerValue(pos))

        ptr = ns.core.PointerValue()
        mobility.GetAttribute("PositionAllocator", ptr)
        self.assert_(ptr.GetObject() is not None)

    def testIdentity(self):
        csma = ns.csma.CsmaNetDevice()
        channel = ns.csma.CsmaChannel()
        csma.Attach(channel)
        
        c1 = csma.GetChannel()
        c2 = csma.GetChannel()

        self.assert_(c1 is c2)

    def testTypeId(self):
        typeId1 = ns.core.TypeId.LookupByNameFailSafe("ns3::UdpSocketFactory")
        self.assertEqual(typeId1.GetName (), "ns3::UdpSocketFactory")
        
        self.assertRaises(KeyError, ns.core.TypeId.LookupByNameFailSafe, "__InvalidTypeName__")

    def testCommandLine(self):
        cmd = ns.core.CommandLine()
        cmd.AddValue("Test1", "this is a test option")
        cmd.AddValue("Test2", "this is a test option")
        cmd.AddValue("Test3", "this is a test option", variable="test_xxx")
        cmd.Test1 = None
        cmd.Test2 = None
        cmd.test_xxx = None
        class Foo:
            pass
        foo = Foo()
        foo.test_foo = None
        cmd.AddValue("Test4", "this is a test option", variable="test_foo", namespace=foo)
        
        cmd.Parse(["python", "--Test1=value1", "--Test2=value2", "--Test3=123", "--Test4=xpto"])

        self.assertEqual(cmd.Test1, "value1")
        self.assertEqual(cmd.Test2, "value2")
        self.assertEqual(cmd.test_xxx, "123")
        self.assertEqual(foo.test_foo, "xpto")

    def testSubclass(self):
        class MyNode(ns.network.Node):
            def __init__(self):
                super(MyNode, self).__init__()

        node = MyNode()


if __name__ == '__main__':
    unittest.main()
