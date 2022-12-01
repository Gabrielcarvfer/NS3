#! /usr/bin/env python3

# Copyright (C) 2008-2011 INESC Porto

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

# Author: Gustavo J. A. M. Carneiro <gjc@inescporto.pt>

import unittest
from ns import ns
import sys

UINT32_MAX = 0xFFFFFFFF


## TestSimulator class
class TestSimulator(unittest.TestCase):
    ## @var _received_packet
    #  received packet
    ## @var _args_received
    #  args
    ## @var _cb_time
    #  current time
    ## @var _context_received
    #  context

    def testScheduleNow(self):
        """! Test schedule now
        @param self this object
        @return None
        """

        def callback(args: ns.cppyy.gbl.std.vector) -> None:
            """! Callback function
            @param args arguments
            @return None
            """
            self._args_received = list(map(lambda x: x.decode("utf-8"), args))
            self._cb_time = ns.Simulator.Now()

        ns.Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        ns.cppyy.cppdef("""
            EventImpl* pythonMakeEvent(void (*f)(std::vector<std::string>), std::vector<std::string> l)
            {
                return MakeEvent(f, l);
            }
        """)
        event = ns.cppyy.gbl.pythonMakeEvent(callback, sys.argv)
        ns.Simulator.ScheduleNow(event)
        ns.Simulator.Run()
        self.assertListEqual(self._args_received, sys.argv)
        self.assertEqual(self._cb_time.GetSeconds(), 0.0)

    def testSchedule(self):
        """! Test schedule
        @param self this object
        @return None
        """

        def callback(args: ns.cppyy.gbl.std.vector):
            """! Callback function
            @param args arguments
            @return None
            """
            self._args_received = list(map(lambda x: x.decode("utf-8"), args))
            self._cb_time = ns.Simulator.Now()

        ns.Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        ns.cppyy.cppdef("""
            EventImpl* pythonMakeEvent2(void (*f)(std::vector<std::string>), std::vector<std::string> l)
            {
                return MakeEvent(f, l);
            }
        """)
        event = ns.cppyy.gbl.pythonMakeEvent2(callback, sys.argv)
        ns.Simulator.Schedule(ns.Seconds(123), event)
        ns.Simulator.Run()
        self.assertListEqual(self._args_received, sys.argv)
        self.assertEqual(self._cb_time.GetSeconds(), 123.0)

    def testScheduleDestroy(self):
        """! Test schedule destroy
        @param self this object
        @return None
        """

        def callback(args: ns.cppyy.gbl.std.vector):
            """! Callback function
            @param args
            @return None
            """
            self._args_received = list(map(lambda x: x.decode("utf-8"), args))
            self._cb_time = ns.Simulator.Now()

        ns.Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        ns.cppyy.cppdef("void null(){ return; }")
        ns.Simulator.Schedule(ns.Seconds(123), ns.cppyy.gbl.null)
        ns.cppyy.cppdef("""
            EventImpl* pythonMakeEvent3(void (*f)(std::vector<std::string>), std::vector<std::string> l)
            {
                return MakeEvent(f, l);
            }
        """)
        event = ns.cppyy.gbl.pythonMakeEvent3(callback, sys.argv)
        ns.Simulator.ScheduleDestroy(event)
        ns.Simulator.Run()
        ns.Simulator.Destroy()
        self.assertListEqual(self._args_received, sys.argv)
        self.assertEqual(self._cb_time.GetSeconds(), 123.0)

    def testScheduleWithContext(self):
        """! Test schedule with context
        @param self this object
        @return None
        """

        def callback(context, args: ns.cppyy.gbl.std.vector):
            """! Callback
            @param context the context
            @param args the arguments
            @return None
            """
            self._context_received = context
            self._args_received = list(map(lambda x: x.decode("utf-8"), args))
            self._cb_time = ns.Simulator.Now()

        ns.Simulator.Destroy()
        self._args_received = None
        self._cb_time = None
        self._context_received = None
        ns.cppyy.cppdef("""
            EventImpl* pythonMakeEvent4(void (*f)(uint32_t, std::vector<std::string>), uint32_t context, std::vector<std::string> l)
            {
                return MakeEvent(f, context, l);
            }
        """)
        event = ns.cppyy.gbl.pythonMakeEvent4(callback, 54321, sys.argv)
        ns.Simulator.ScheduleWithContext(54321, ns.Seconds(123), event)
        ns.Simulator.Run()
        self.assertEqual(self._context_received, 54321)
        self.assertListEqual(self._args_received, sys.argv)
        self.assertEqual(self._cb_time.GetSeconds(), 123.0)

    def testTimeComparison(self):
        """! Test time comparison
        @param self this object
        @return None
        """
        self.assertTrue(ns.Seconds(123) == ns.Seconds(123))
        self.assertTrue(ns.Seconds(123) >= ns.Seconds(123))
        self.assertTrue(ns.Seconds(123) <= ns.Seconds(123))
        self.assertTrue(ns.Seconds(124) > ns.Seconds(123))
        self.assertTrue(ns.Seconds(123) < ns.Seconds(124))

    def testTimeNumericOperations(self):
        """! Test numeric operations
        @param self this object
        @return None
        """
        self.assertEqual(ns.Seconds(10) + ns.Seconds(5), ns.Seconds(15))
        self.assertEqual(ns.Seconds(10) - ns.Seconds(5), ns.Seconds(5))

        v1 = ns.int64x64_t(5.0) * ns.int64x64_t(10)
        self.assertEqual(v1, ns.int64x64_t(50))

    def testConfig(self):
        """! Test configuration
        @param self this object
        @return None
        """
        ns.Config.SetDefault("ns3::OnOffApplication::PacketSize", ns.core.UintegerValue(123))
        # hm.. no Config.Get?

    def testSocket(self):
        """! Test socket
        @param self
        @return None
        """
        nc = ns.NodeContainer(1)
        node = nc.Get(0)
        internet = ns.CreateObject("InternetStackHelper")
        internet.Install(node)
        self._received_packet = None

        def python_rx_callback(socket) -> None:
            self._received_packet = socket.Recv(maxSize=UINT32_MAX, flags=0)

        ns.cppyy.cppdef("""
            Callback<void,ns3::Ptr<ns3::Socket> > make_rx_callback_test_socket(void(*func)(Ptr<Socket>))
            {
                return MakeCallback(func);
            }
        """)

        sink = ns.network.Socket.CreateSocket(node, ns.core.TypeId.LookupByName("ns3::UdpSocketFactory"))
        sink.Bind(ns.network.InetSocketAddress(ns.network.Ipv4Address.GetAny(), 80).ConvertTo())
        sink.SetRecvCallback(ns.cppyy.gbl.make_rx_callback_test_socket(python_rx_callback))

        source = ns.network.Socket.CreateSocket(node, ns.core.TypeId.LookupByName("ns3::UdpSocketFactory"))
        source.SendTo(ns.network.Packet(19), 0,
                      ns.network.InetSocketAddress(ns.network.Ipv4Address("127.0.0.1"), 80).ConvertTo())

        ns.Simulator.Run()
        self.assertTrue(self._received_packet is not None)
        self.assertEqual(self._received_packet.GetSize(), 19)

        # Delete Ptr<>'s on the python side to let C++ clean them
        del internet

    def testAttributes(self):
        """! Test attributes function
        @param self this object
        @return None
        """
        # Templated class DropTailQueue<Packet> in C++
        queue = ns.CreateObject("DropTailQueue<Packet>")
        queueSizeValue = ns.network.QueueSizeValue(ns.network.QueueSize("500p"))
        queue.SetAttribute("MaxSize", queueSizeValue)

        limit = ns.network.QueueSizeValue()
        queue.GetAttribute("MaxSize", limit)
        self.assertEqual(limit.Get(), ns.network.QueueSize("500p"))

        ## -- object pointer values
        mobility = ns.CreateObject("RandomWaypointMobilityModel")
        ptr = ns.CreateObject("PointerValue")
        mobility.GetAttribute("PositionAllocator", ptr)
        self.assertEqual(ptr.GetObject(), ns.core.Ptr["Object"](ns.cppyy.nullptr))

        pos = ns.mobility.ListPositionAllocator()
        ptr.SetObject(pos)
        mobility.SetAttribute("PositionAllocator", ptr)

        ptr2 = ns.CreateObject("PointerValue")
        mobility.GetAttribute("PositionAllocator", ptr2)
        self.assertNotEqual(ptr.GetObject(), ns.core.Ptr["Object"](ns.cppyy.nullptr))

        # Delete Ptr<>'s on the python side to let C++ clean them
        del queue, mobility, ptr, ptr2

    def testIdentity(self):
        """! Test identify
        @param self this object
        @return None
        """
        csma = ns.CreateObject("CsmaNetDevice")
        channel = ns.CreateObject("CsmaChannel")
        csma.Attach(channel)

        c1 = csma.GetChannel()
        c2 = csma.GetChannel()

        self.assertEqual(c1, c2)

        # Delete Ptr<>'s on the python side to let C++ clean them
        del csma, channel

    def testTypeId(self):
        """! Test type ID
        @param self this object
        @return None
        """
        ok, typeId1 = ns.LookupByNameFailSafe("ns3::UdpSocketFactory")
        self.assertTrue(ok)
        self.assertEqual(typeId1.GetName(), "ns3::UdpSocketFactory")

        ok, typeId1 = ns.LookupByNameFailSafe("ns3::__InvalidTypeName__")
        self.assertFalse(ok)

    def testCommandLine(self):
        """! Test command line
        @param self this object
        @return None
        """
        from ctypes import c_bool, c_int, c_double, c_char_p, create_string_buffer

        test1 = c_bool(True)
        test2 = c_int(42)
        test3 = c_double(3.1415)
        BUFFLEN = 40  # noqa
        test4Buffer = create_string_buffer(b"this is a test option", BUFFLEN)
        test4 = c_char_p(test4Buffer.raw)

        cmd = ns.core.CommandLine(__file__)
        cmd.AddValue("Test1", "this is a test option", test1)
        cmd.AddValue("Test2", "this is a test option", test2)
        cmd.AddValue("Test3", "this is a test option", test3)
        cmd.AddValue("Test4", "this is a test option", test4, BUFFLEN)

        cmd.Parse(["python"])
        self.assertEqual(test1.value, True)
        self.assertEqual(test2.value, 42)
        self.assertEqual(test3.value, 3.1415)
        self.assertEqual(test4.value, b"this is a test option")

        cmd.Parse(["python", "--Test1=false", "--Test2=0", "--Test3=0.0"])
        self.assertEqual(test1.value, False)
        self.assertEqual(test2.value, 0)
        self.assertEqual(test3.value, 0.0)

        cmd.Parse(["python", "--Test4=new_string"])
        self.assertEqual(test4.value, b"new_string")

    def testSubclass(self):
        """! Test subclass
        @param self this object
        @return None
        """

        ## MyNode class
        class MyNode(ns.network.Node):
            def GetLocalTime(self) -> ns.Time:
                return ns.Seconds(10)

        node = MyNode()
        forced_local_time = node.GetLocalTime()
        self.assertEqual(forced_local_time, ns.Seconds(10))
        del node

    def testEchoServerApplication(self):
        """! Test python-based application
        @param self this object
        @return None
        """
        ns.Simulator.Destroy()

        nodes = ns.network.NodeContainer()
        nodes.Create(2)

        pointToPoint = ns.point_to_point.PointToPointHelper()
        pointToPoint.SetDeviceAttribute("DataRate", ns.core.StringValue("5Mbps"))
        pointToPoint.SetChannelAttribute("Delay", ns.core.StringValue("2ms"))

        devices = pointToPoint.Install(nodes)

        stack = ns.internet.InternetStackHelper()
        stack.Install(nodes)

        address = ns.internet.Ipv4AddressHelper()
        address.SetBase(ns.network.Ipv4Address("10.1.1.0"),
                        ns.network.Ipv4Mask("255.255.255.0"))

        interfaces = address.Assign(devices)

        ns.cppyy.cppdef("""
            namespace ns3
            {
                Callback<void,Ptr<Socket> > make_rx_callback(void(*func)(Ptr<Socket>))
                {
                    return MakeCallback(func);
                }
                EventImpl* pythonMakeEventSend(void (*f)(Ptr<Socket>, Ptr<Packet>, Address&), Ptr<Socket> socket, Ptr<Packet> packet, Address address)
                {
                    return MakeEvent(f, socket, packet, address);
                }
            }
        """)

        ## EchoServer application class
        class EchoServer(ns.applications.Application):
            LOGGING = False
            ECHO_PORT = 1234
            socketToInstanceDict = {}

            def __init__(self, node: ns.Node, port=ECHO_PORT):
                """! Constructor needs to call first the constructor to Application (super class)
                @param self this object
                @param node node where this application will be executed
                @param port port to listen
                return None
                """
                super().__init__()
                self.__python_owns__ = False  # Let C++ destroy this on Simulator::Destroy
                ## Listen port for the server
                self.port = port
                ## Socket used by the server to listen to port
                self.m_socket = ns.network.Socket.CreateSocket(node,
                                                               ns.core.TypeId.LookupByName("ns3::UdpSocketFactory"))
                self.m_socket.Bind(ns.network.InetSocketAddress(ns.network.Ipv4Address.GetAny(), self.port).ConvertTo())
                self.m_socket.SetRecvCallback(ns.make_rx_callback(EchoServer._Receive))
                EchoServer.socketToInstanceDict[self.m_socket] = self

            def __del__(self):
                """! Destructor
                @param self this object
                return None
                """
                del EchoServer.socketToInstanceDict[self.m_socket]

            def Send(self, packet: ns.Packet, address: ns.Address) -> None:
                """! Function to send a packet to an address
                @param self this object
                @param packet packet to send
                @param address destination address
                return None
                """
                self.m_socket.SendTo(packet, 0, address)
                if EchoServer.LOGGING:
                    inetAddress = ns.InetSocketAddress.ConvertFrom(address)
                    print("At time +{s}s server sent {b} bytes from {ip} port {port}"
                          .format(s=ns.Simulator.Now().GetSeconds(),
                                  b=packet.__deref__().GetSize(),
                                  ip=inetAddress.GetIpv4(),
                                  port=inetAddress.GetPort()),
                          file=sys.stderr,
                          flush=True)

            def Receive(self):
                """! Function to receive a packet from an address
                @param self this object
                @return None
                """
                address = ns.Address()
                packet = self.m_socket.RecvFrom(address)
                if EchoServer.LOGGING:
                    inetAddress = ns.InetSocketAddress.ConvertFrom(address)
                    print("At time +{s}s server received {b} bytes from {ip} port {port}"
                          .format(s=ns.Simulator.Now().GetSeconds(),
                                  b=packet.__deref__().GetSize(),
                                  ip=inetAddress.GetIpv4(),
                                  port=inetAddress.GetPort()),
                          file=sys.stderr,
                          flush=True)
                event = ns.pythonMakeEventSend(EchoServer._Send, self.m_socket, packet, address)
                ns.Simulator.Schedule(ns.Seconds(1), event)

            @staticmethod
            def _Send(socket: ns.Socket, packet: ns.Packet, address: ns.Address):
                """! Static send function, which matches the output socket
                to the EchoServer instance to call the instance Send function
                @param socket socket from the instance that should send the packet
                @param packet packet to send
                @param address destination address
                return None
                """
                instance = EchoServer.socketToInstanceDict[socket]
                instance.Send(packet, address)

            @staticmethod
            def _Receive(socket: ns.Socket) -> None:
                """! Static receive function, which matches the input socket
                to the EchoServer instance to call the instance Receive function
                @param socket socket from the instance that should receive the packet
                return None
                """
                instance = EchoServer.socketToInstanceDict[socket]
                instance.Receive()

        echoServer = EchoServer(nodes.Get(1))
        nodes.Get(1).AddApplication(echoServer)

        serverApps = ns.ApplicationContainer()
        serverApps.Add(echoServer)
        serverApps.Start(ns.core.Seconds(1.0))
        serverApps.Stop(ns.core.Seconds(10.0))

        address = interfaces.GetAddress(1).ConvertTo()
        echoClient = ns.applications.UdpEchoClientHelper(address, EchoServer.ECHO_PORT)
        echoClient.SetAttribute("MaxPackets", ns.core.UintegerValue(10))
        echoClient.SetAttribute("Interval", ns.core.TimeValue(ns.core.Seconds(1.0)))
        echoClient.SetAttribute("PacketSize", ns.core.UintegerValue(101))

        clientApps = echoClient.Install(nodes.Get(0))
        clientApps.Start(ns.core.Seconds(2.0))
        clientApps.Stop(ns.core.Seconds(10.0))

        ns.Simulator.Run()
        ns.Simulator.Destroy()


    def testConnect(self):
        ns.Simulator.Destroy()

        def CourseChanged(context: str, mobilityModelPtr: ns.MobilityModel) -> None:
            pos = mobilityModelPtr.__deref__().GetPosition()
            vel = mobilityModelPtr.__deref__().GetVelocity()
            log = f"{ns.Simulator.Now()}, model={mobilityModelPtr.__deref__().__class__.__name__}, POS: x={pos.x}, y={pos.y}, z={pos.z}; VEL: x={vel.x}, y={vel.y}, z={vel.z}"
            self.assertNotEqual("", log)

        nodeContainer = ns.NodeContainer()
        nodeContainer.Create(1)

        mobilityHelper = ns.MobilityHelper()
        mobilityHelper.SetPositionAllocator("ns3::RandomDiscPositionAllocator",
                                            "X", ns.StringValue("100.0"),
                                            "Y", ns.StringValue("100.0"),
                                            "Rho", ns.StringValue("ns3::UniformRandomVariable[Min=0|Max=30]")
                                            )
        mobilityHelper.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                                        "Mode", ns.StringValue("Time"),
                                        "Time", ns.StringValue("2s"),
                                        "Bounds", ns.StringValue("0|200|0|200")
                                        )
        mobilityHelper.Install(nodeContainer)

        ns.cppyy.cppdef("""
            using namespace ns3;
            Callback<void,std::string,Ptr<const MobilityModel>>
            make_course_changed_callback(void(*func)(std::string, Ptr<const MobilityModel>))
            {
                return MakeCallback(func);
            }
        """)

        ns.Config.Connect("/NodeList/*/$ns3::MobilityModel/CourseChange", ns.cppyy.gbl.make_course_changed_callback(CourseChanged))
        ns.Simulator.Stop(ns.Seconds(5))
        ns.Simulator.Run()
        ns.Simulator.Destroy()


if __name__ == '__main__':
    unittest.main(verbosity=1, failfast=True)
