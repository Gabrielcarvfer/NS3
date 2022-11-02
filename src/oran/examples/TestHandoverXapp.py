from ns import ns

def NotifyConnectionEstablishedUe(context : str, imsi : int, cellid : int, rnti : int) -> None:
  print(f"{context} UE IMSI {imsi} : connected to CellId {cellid} with RNTI {rnti}")


def NotifyHandoverStartUe(context : str, imsi : int, cellid : int, rnti : int, targetCellId : int) -> None:
  print(f"{context} UE IMSI {imsi} : previously connected to CellId {cellid} with RNTI {rnti}, doing handover to CellId {targetCellId}")


def NotifyHandoverEndOkUe(context : str, imsi : int, cellid : int, rnti : int) -> None:
  print(f"{context} UE IMSI {imsi} : successful handover to CellId {cellid} with RNTI {rnti}")


def NotifyConnectionEstablishedEnb(context : str, imsi : int, cellid : int, rnti : int) -> None:
  print(f"{context} eNB CellId {cellid} : successful connection of UE with IMSI {imsi} RNTI {rnti}")

def NotifyHandoverStartEnb(context : str, imsi : int, cellid : int, rnti : int, targetCellId : int) -> None:
  print(f"{context} eNB CellId {cellid} : start handover of UE with IMSI {imsi} RNTI {rnti} to CellId {targetCellId}")


def NotifyHandoverEndOkEnb(context : str, imsi : int, cellid : int, rnti : int) -> None:
  print(f"{context} eNB CellId {cellid} : completed handover of UE with IMSI {imsi} RNTI {rnti}")

# Testes de conexão de nós
ns.GlobalValue.Bind ("ChecksumEnabled", ns.BooleanValue (True))

numberOfUes = 1
numberOfEnbs = 3
numBearersPerUe = 0
distance = 200.0                                        # m
yForUe = 500.0                                          # m
speed = 1#20                                              # m/s
simTime = (numberOfEnbs + 1) * distance / speed # 1500 m / 20 m/s = 75 secs
enbTxPowerDbm = 46.0

# change some default attributes so that they are reasonable for
# this scenario, but do this before processing command line
# arguments, so that the user is allowed to override these settings
ns.Config.SetDefault("ns3::UdpClient::Interval", ns.TimeValue(ns.MilliSeconds(10)))
ns.Config.SetDefault("ns3::UdpClient::MaxPackets", ns.UintegerValue(1000000))
ns.Config.SetDefault("ns3::LteHelper::UseIdealRrc", ns.BooleanValue(True))

lteHelper = ns.CreateObject("LteHelper")
epcHelper = ns.CreateObject("PointToPointEpcHelper")
epcHelper.SetAttribute("S1uLinkEnablePcap", ns.BooleanValue(True))
lteHelper.SetEpcHelper(epcHelper)
lteHelper.SetSchedulerType("ns3::RrFfMacScheduler")

lteHelper.SetHandoverAlgorithmType ("ns3::NoOpHandoverAlgorithm") # select an algorithm that does nothing
pgw = epcHelper.GetPgwNode()
sgw = epcHelper.GetSgwNode()

# Create a single RemoteHost
remoteHostContainer = ns.NodeContainer()
remoteHostContainer.Create(1)
remoteHost = remoteHostContainer.Get(0)
internet = ns.InternetStackHelper()
internet.Install(remoteHostContainer)

# Create the Internet
p2ph = ns.PointToPointHelper()
p2ph.SetDeviceAttribute("DataRate", ns.DataRateValue(ns.DataRate("100Gb/s")))
p2ph.SetDeviceAttribute("Mtu", ns.UintegerValue(1500))
p2ph.SetChannelAttribute("Delay", ns.TimeValue(ns.Seconds(0.010)))
internetDevices = p2ph.Install(pgw, remoteHost)
ipv4h = ns.Ipv4AddressHelper()
ipv4h.SetBase("1.0.0.0", "255.0.0.0")
internetIpIfaces = ipv4h.Assign(internetDevices)
remoteHostAddr = internetIpIfaces.GetAddress(1)

# Routing of the Internet Host (towards the LTE network)
ipv4RoutingHelper = ns.Ipv4StaticRoutingHelper()
remoteHostIpv4 = remoteHost.__deref__().GetObject["Ipv4"]()
remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(remoteHostIpv4)
# interface 0 is localhost, 1 is the p2p device
remoteHostStaticRouting.AddNetworkRouteTo(ns.Ipv4Address("7.0.0.0"), ns.Ipv4Mask("255.0.0.0"), 1)

#
# Network topology:
#
#      |     + --------------------------------------------------------.
#      |     UE
#      |
#      |               d                   d                   d
#    y |     |-------------------x-------------------x-------------------
#      |     |                 eNodeB              eNodeB
#      |   d |
#      |     |
#      |     |                                             d = distance
#            o (0, 0, 0)                                   y = yForUe
#

ueNodes = ns.NodeContainer()
enbNodes = ns.NodeContainer()
enbNodes.Create(numberOfEnbs)
ueNodes.Create(numberOfUes)

# Install Mobility Model in eNB
enbPositionAlloc = ns.CreateObject("ListPositionAllocator")
for i in range(1,numberOfEnbs+1):# i = 1 => UE is in the middle of two eNBs
    enbPosition = ns.Vector(distance * (i + 1), distance, 0)
    enbPositionAlloc.Add(enbPosition)

enbMobility = ns.MobilityHelper()
enbMobility.SetMobilityModel("ns3::ConstantPositionMobilityModel")
enbMobility.SetPositionAllocator(enbPositionAlloc)
enbMobility.Install(enbNodes)

# Install Mobility Model in UE
ueMobility = ns.MobilityHelper()
ueMobility.SetMobilityModel("ns3::ConstantVelocityMobilityModel")
ueMobility.Install(ueNodes)
ueNodes.Get(0).__deref__().GetObject[ns.MobilityModel]().SetPosition(ns.Vector(0, yForUe, 0))
ueNodes.Get(0).__deref__().GetObject[ns.ConstantVelocityMobilityModel]().SetVelocity(ns.Vector(speed, 0, 0))

# Install LTE Devices in eNB and UEs
ns.Config.SetDefault("ns3::LteEnbPhy::TxPower", ns.DoubleValue(enbTxPowerDbm))
enbLteDevs = lteHelper.InstallEnbDevice(enbNodes)
ueLteDevs = lteHelper.InstallUeDevice(ueNodes)

# Install the IP stack on the UEs
internet.Install(ueNodes)
ueIpIfaces = epcHelper.AssignUeIpv4Address(ns.NetDeviceContainer(ueLteDevs))

# Attach all UEs to the first eNodeB
for i in range(0, numberOfUes):
    lteHelper.Attach(ueLteDevs.Get(i), enbLteDevs.Get(0))

for u in range(0, numberOfUes):
    ue = ueNodes.Get(u)
    # Set the default gateway for the UE
    ueStaticRouting = ipv4RoutingHelper.GetStaticRouting(ue.GetObject[ns.Ipv4]())
    ueStaticRouting.SetDefaultRoute(epcHelper.GetUeDefaultGatewayAddress(), 1)

# Add X2 interface
lteHelper.AddX2Interface(enbNodes)

# Configura regra de encaminhamento para eNBs que não sejam o primeiro
for i in range (1, numberOfEnbs):
    ipv4RoutingHelper = ns.Ipv4StaticRoutingHelper()
    remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting(enbNodes.Get (i).GetObject[ns.Ipv4]())
    remoteHostStaticRouting.AddNetworkRouteTo(ns.Ipv4Address("10.0.0.6"), ns.Ipv4Mask("255.255.255.252"), 1)

# connect custom trace sinks for RRC connection establishment and handover notification
###ns.Config.Connect("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
###                  ns.MakeCallback(NotifyConnectionEstablishedEnb))
###ns.Config.Connect("/NodeList/*/DeviceList/*/LteUeRrc/ConnectionEstablished",
###                  ns.MakeCallback(NotifyConnectionEstablishedUe))
###ns.Config.Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverStart",
###                  ns.MakeCallback(NotifyHandoverStartEnb))
###ns.Config.Connect("/NodeList/*/DeviceList/*/LteUeRrc/HandoverStart",
###                  ns.MakeCallback(NotifyHandoverStartUe))
###ns.Config.Connect("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
###                  ns.MakeCallback(NotifyHandoverEndOkEnb))
###ns.Config.Connect("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndOk",
###                  ns.MakeCallback(NotifyHandoverEndOkUe))
# end of x2-handover-measures example

e2t = ns.CreateObject("E2AP")
e2n1 = ns.CreateObject("E2AP")

# Create the handover xApp
xAppHandover = ns.xApp_Handover()

# Depois de instalar aplicações, conseguiremos obter seus endereços de IP para
# estabelecer os sockets TCP
sgw.AddApplication(e2t)
sgw.AddApplication(xAppHandover)

# Configurar eNodeBs/nós E2
enbNodes.Get(0).AddApplication(e2n1)

ns.Simulator.Schedule(ns.Seconds(0.5), ns.E2AP.Connect, e2t)
ns.Simulator.Schedule(ns.Seconds(1.0), ns.E2AP.Connect, e2n1)
ns.Simulator.Schedule(ns.Seconds(2.0), ns.E2AP.RegisterDefaultEndpoints, e2n1)
ns.Simulator.Schedule(ns.Seconds(2.5), ns.E2AP.SubscribeToDefaultEndpoints, e2t, e2n1)

e2n2 = ns.cppyy.gbl.getE2AP()
enbNodes.Get(1).AddApplication(e2n2)
ns.Simulator.Schedule(ns.Seconds(1.0), ns.E2AP.Connect, e2n2)
ns.Simulator.Schedule(ns.Seconds(2.0), ns.E2AP.RegisterDefaultEndpoints, e2n2)
ns.Simulator.Schedule(ns.Seconds(2.5), ns.E2AP.SubscribeToDefaultEndpoints, e2t, e2n2)

e2n3 = ns.cppyy.gbl.getE2AP()
enbNodes.Get(2).AddApplication(e2n3)
ns.Simulator.Schedule(ns.Seconds(1.0), ns.E2AP.Connect, e2n3)
ns.Simulator.Schedule(ns.Seconds(2.0), ns.E2AP.RegisterDefaultEndpoints, e2n3)
ns.Simulator.Schedule(ns.Seconds(2.5), ns.E2AP.SubscribeToDefaultEndpoints, e2t, e2n3)

# Executa um handover do primeiro eNB para o segundo
lteHelper.HandoverRequest (ns.Seconds (4.0), ueLteDevs.Get (0), enbLteDevs.Get (0), enbLteDevs.Get (1))

# Executar handover de volta para primeiro eNB
lteHelper.HandoverRequest (ns.Seconds (5.0), ueLteDevs.Get (0), enbLteDevs.Get (1), enbLteDevs.Get (0))

# Executar handover do primeiro eNB para terceiro
lteHelper.HandoverRequest (ns.Seconds (6.0), ueLteDevs.Get (0), enbLteDevs.Get (0), enbLteDevs.Get (2))

# Executar handover do terceiro eNB para o primeiro
lteHelper.HandoverRequest (ns.Seconds (7.0), ueLteDevs.Get (0), enbLteDevs.Get (2), enbLteDevs.Get (0))

ns.Simulator.Stop(ns.Seconds(8.0))
ns.Simulator.Run()
ns.Simulator.Destroy()
exit(0)
