from pybindgen import Module, FileCodeSink, param, retval, cppclass, typehandlers


import pybindgen.settings
import warnings

class ErrorHandler(pybindgen.settings.ErrorHandler):
    def handle_error(self, wrapper, exception, traceback_):
        warnings.warn("exception %r in wrapper %s" % (exception, wrapper))
        return True
pybindgen.settings.error_handler = ErrorHandler()


import sys

def module_init():
    root_module = Module('ns.dsr', cpp_namespace='::ns3')
    return root_module

def register_types(module):
    root_module = module.get_root()
    
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacType [enumeration]
    module.add_enum('WifiMacType', ['WIFI_MAC_CTL_CTLWRAPPER', 'WIFI_MAC_CTL_RTS', 'WIFI_MAC_CTL_CTS', 'WIFI_MAC_CTL_ACK', 'WIFI_MAC_CTL_BACKREQ', 'WIFI_MAC_CTL_BACKRESP', 'WIFI_MAC_MGT_BEACON', 'WIFI_MAC_MGT_ASSOCIATION_REQUEST', 'WIFI_MAC_MGT_ASSOCIATION_RESPONSE', 'WIFI_MAC_MGT_DISASSOCIATION', 'WIFI_MAC_MGT_REASSOCIATION_REQUEST', 'WIFI_MAC_MGT_REASSOCIATION_RESPONSE', 'WIFI_MAC_MGT_PROBE_REQUEST', 'WIFI_MAC_MGT_PROBE_RESPONSE', 'WIFI_MAC_MGT_AUTHENTICATION', 'WIFI_MAC_MGT_DEAUTHENTICATION', 'WIFI_MAC_MGT_ACTION', 'WIFI_MAC_MGT_ACTION_NO_ACK', 'WIFI_MAC_MGT_MULTIHOP_ACTION', 'WIFI_MAC_DATA', 'WIFI_MAC_DATA_CFACK', 'WIFI_MAC_DATA_CFPOLL', 'WIFI_MAC_DATA_CFACK_CFPOLL', 'WIFI_MAC_DATA_NULL', 'WIFI_MAC_DATA_NULL_CFACK', 'WIFI_MAC_DATA_NULL_CFPOLL', 'WIFI_MAC_DATA_NULL_CFACK_CFPOLL', 'WIFI_MAC_QOSDATA', 'WIFI_MAC_QOSDATA_CFACK', 'WIFI_MAC_QOSDATA_CFPOLL', 'WIFI_MAC_QOSDATA_CFACK_CFPOLL', 'WIFI_MAC_QOSDATA_NULL', 'WIFI_MAC_QOSDATA_NULL_CFPOLL', 'WIFI_MAC_QOSDATA_NULL_CFACK_CFPOLL'], import_from_module='ns.wifi')
    ## wifi-preamble.h (module 'wifi'): ns3::WifiPreamble [enumeration]
    module.add_enum('WifiPreamble', ['WIFI_PREAMBLE_LONG', 'WIFI_PREAMBLE_SHORT', 'WIFI_PREAMBLE_HT_MF', 'WIFI_PREAMBLE_HT_GF', 'WIFI_PREAMBLE_VHT', 'WIFI_PREAMBLE_NONE'], import_from_module='ns.wifi')
    ## wifi-phy.h (module 'wifi'): ns3::mpduType [enumeration]
    module.add_enum('mpduType', ['NORMAL_MPDU', 'MPDU_IN_AGGREGATE', 'LAST_MPDU_IN_AGGREGATE'], import_from_module='ns.wifi')
    ## wifi-mode.h (module 'wifi'): ns3::WifiModulationClass [enumeration]
    module.add_enum('WifiModulationClass', ['WIFI_MOD_CLASS_UNKNOWN', 'WIFI_MOD_CLASS_IR', 'WIFI_MOD_CLASS_FHSS', 'WIFI_MOD_CLASS_DSSS', 'WIFI_MOD_CLASS_HR_DSSS', 'WIFI_MOD_CLASS_ERP_PBCC', 'WIFI_MOD_CLASS_DSSS_OFDM', 'WIFI_MOD_CLASS_ERP_OFDM', 'WIFI_MOD_CLASS_OFDM', 'WIFI_MOD_CLASS_HT', 'WIFI_MOD_CLASS_VHT'], import_from_module='ns.wifi')
    ## wifi-phy-standard.h (module 'wifi'): ns3::WifiPhyStandard [enumeration]
    module.add_enum('WifiPhyStandard', ['WIFI_PHY_STANDARD_80211a', 'WIFI_PHY_STANDARD_80211b', 'WIFI_PHY_STANDARD_80211g', 'WIFI_PHY_STANDARD_80211_10MHZ', 'WIFI_PHY_STANDARD_80211_5MHZ', 'WIFI_PHY_STANDARD_holland', 'WIFI_PHY_STANDARD_80211n_2_4GHZ', 'WIFI_PHY_STANDARD_80211n_5GHZ', 'WIFI_PHY_STANDARD_80211ac', 'WIFI_PHY_STANDARD_UNSPECIFIED'], import_from_module='ns.wifi')
    ## wifi-mode.h (module 'wifi'): ns3::WifiCodeRate [enumeration]
    module.add_enum('WifiCodeRate', ['WIFI_CODE_RATE_UNDEFINED', 'WIFI_CODE_RATE_3_4', 'WIFI_CODE_RATE_2_3', 'WIFI_CODE_RATE_1_2', 'WIFI_CODE_RATE_5_6'], import_from_module='ns.wifi')
    ## qos-utils.h (module 'wifi'): ns3::AcIndex [enumeration]
    module.add_enum('AcIndex', ['AC_BE', 'AC_BK', 'AC_VI', 'AC_VO', 'AC_BE_NQOS', 'AC_UNDEF'], import_from_module='ns.wifi')
    ## address.h (module 'network'): ns3::Address [class]
    module.add_class('Address', import_from_module='ns.network')
    ## address.h (module 'network'): ns3::Address::MaxSize_e [enumeration]
    module.add_enum('MaxSize_e', ['MAX_SIZE'], outer_class=root_module['ns3::Address'], import_from_module='ns.network')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList [class]
    module.add_class('AttributeConstructionList', import_from_module='ns.core')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item [struct]
    module.add_class('Item', import_from_module='ns.core', outer_class=root_module['ns3::AttributeConstructionList'])
    ## buffer.h (module 'network'): ns3::Buffer [class]
    module.add_class('Buffer', import_from_module='ns.network')
    ## buffer.h (module 'network'): ns3::Buffer::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::Buffer'])
    ## packet.h (module 'network'): ns3::ByteTagIterator [class]
    module.add_class('ByteTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagIterator'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList [class]
    module.add_class('ByteTagList', import_from_module='ns.network')
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList::Iterator'])
    ## callback.h (module 'core'): ns3::CallbackBase [class]
    module.add_class('CallbackBase', import_from_module='ns.core')
    ## dsr-helper.h (module 'dsr'): ns3::DsrHelper [class]
    module.add_class('DsrHelper')
    ## dsr-main-helper.h (module 'dsr'): ns3::DsrMainHelper [class]
    module.add_class('DsrMainHelper')
    ## event-garbage-collector.h (module 'core'): ns3::EventGarbageCollector [class]
    module.add_class('EventGarbageCollector', import_from_module='ns.core')
    ## event-id.h (module 'core'): ns3::EventId [class]
    module.add_class('EventId', import_from_module='ns.core')
    ## hash.h (module 'core'): ns3::Hasher [class]
    module.add_class('Hasher', import_from_module='ns.core')
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress [class]
    module.add_class('Inet6SocketAddress', import_from_module='ns.network')
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress [class]
    root_module['ns3::Inet6SocketAddress'].implicitly_converts_to(root_module['ns3::Address'])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress [class]
    module.add_class('InetSocketAddress', import_from_module='ns.network')
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress [class]
    root_module['ns3::InetSocketAddress'].implicitly_converts_to(root_module['ns3::Address'])
    ## int-to-type.h (module 'core'): ns3::IntToType<0> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['0'])
    ## int-to-type.h (module 'core'): ns3::IntToType<0>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 0 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<1> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['1'])
    ## int-to-type.h (module 'core'): ns3::IntToType<1>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 1 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<2> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['2'])
    ## int-to-type.h (module 'core'): ns3::IntToType<2>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 2 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<3> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['3'])
    ## int-to-type.h (module 'core'): ns3::IntToType<3>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 3 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<4> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['4'])
    ## int-to-type.h (module 'core'): ns3::IntToType<4>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 4 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<5> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['5'])
    ## int-to-type.h (module 'core'): ns3::IntToType<5>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 5 >'], import_from_module='ns.core')
    ## int-to-type.h (module 'core'): ns3::IntToType<6> [struct]
    module.add_class('IntToType', import_from_module='ns.core', template_parameters=['6'])
    ## int-to-type.h (module 'core'): ns3::IntToType<6>::v_e [enumeration]
    module.add_enum('v_e', ['value'], outer_class=root_module['ns3::IntToType< 6 >'], import_from_module='ns.core')
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper [class]
    module.add_class('InterferenceHelper', import_from_module='ns.wifi')
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer [struct]
    module.add_class('SnrPer', import_from_module='ns.wifi', outer_class=root_module['ns3::InterferenceHelper'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    module.add_class('Ipv4Address', import_from_module='ns.network')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    root_module['ns3::Ipv4Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress [class]
    module.add_class('Ipv4InterfaceAddress', import_from_module='ns.internet')
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e [enumeration]
    module.add_enum('InterfaceAddressScope_e', ['HOST', 'LINK', 'GLOBAL'], outer_class=root_module['ns3::Ipv4InterfaceAddress'], import_from_module='ns.internet')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask [class]
    module.add_class('Ipv4Mask', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    module.add_class('Ipv6Address', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    root_module['ns3::Ipv6Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix [class]
    module.add_class('Ipv6Prefix', import_from_module='ns.network')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    module.add_class('Mac48Address', import_from_module='ns.network')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    root_module['ns3::Mac48Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## node-container.h (module 'network'): ns3::NodeContainer [class]
    module.add_class('NodeContainer', import_from_module='ns.network')
    ## non-copyable.h (module 'core'): ns3::NonCopyable [class]
    module.add_class('NonCopyable', destructor_visibility='protected', import_from_module='ns.core')
    ## object-base.h (module 'core'): ns3::ObjectBase [class]
    module.add_class('ObjectBase', allow_subclassing=True, import_from_module='ns.core')
    ## object.h (module 'core'): ns3::ObjectDeleter [struct]
    module.add_class('ObjectDeleter', import_from_module='ns.core')
    ## object-factory.h (module 'core'): ns3::ObjectFactory [class]
    module.add_class('ObjectFactory', import_from_module='ns.core')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata [class]
    module.add_class('PacketMetadata', import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [enumeration]
    module.add_enum('', ['PAYLOAD', 'HEADER', 'TRAILER'], outer_class=root_module['ns3::PacketMetadata::Item'], import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator [class]
    module.add_class('ItemIterator', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet.h (module 'network'): ns3::PacketTagIterator [class]
    module.add_class('PacketTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagIterator'])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList [class]
    module.add_class('PacketTagList', import_from_module='ns.network')
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData [struct]
    module.add_class('TagData', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagList'])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData_e [enumeration]
    module.add_enum('TagData_e', ['MAX_SIZE'], outer_class=root_module['ns3::PacketTagList::TagData'], import_from_module='ns.network')
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Object', 'ns3::ObjectBase', 'ns3::ObjectDeleter'], parent=root_module['ns3::ObjectBase'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simulator.h (module 'core'): ns3::Simulator [class]
    module.add_class('Simulator', destructor_visibility='private', import_from_module='ns.core')
    ## simulator.h (module 'core'): ns3::Simulator [enumeration]
    module.add_enum('', ['NO_CONTEXT'], outer_class=root_module['ns3::Simulator'], import_from_module='ns.core')
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs [class]
    module.add_class('SystemWallClockMs', import_from_module='ns.core')
    ## tag.h (module 'network'): ns3::Tag [class]
    module.add_class('Tag', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer [class]
    module.add_class('TagBuffer', import_from_module='ns.network')
    ## nstime.h (module 'core'): ns3::TimeWithUnit [class]
    module.add_class('TimeWithUnit', import_from_module='ns.core')
    ## timer.h (module 'core'): ns3::Timer [class]
    module.add_class('Timer', import_from_module='ns.core')
    ## timer.h (module 'core'): ns3::Timer::DestroyPolicy [enumeration]
    module.add_enum('DestroyPolicy', ['CANCEL_ON_DESTROY', 'REMOVE_ON_DESTROY', 'CHECK_ON_DESTROY'], outer_class=root_module['ns3::Timer'], import_from_module='ns.core')
    ## timer.h (module 'core'): ns3::Timer::State [enumeration]
    module.add_enum('State', ['RUNNING', 'EXPIRED', 'SUSPENDED'], outer_class=root_module['ns3::Timer'], import_from_module='ns.core')
    ## timer-impl.h (module 'core'): ns3::TimerImpl [class]
    module.add_class('TimerImpl', allow_subclassing=True, import_from_module='ns.core')
    ## traced-value.h (module 'core'): ns3::TracedValue<unsigned int> [class]
    module.add_class('TracedValue', import_from_module='ns.core', template_parameters=['unsigned int'])
    ## type-id.h (module 'core'): ns3::TypeId [class]
    module.add_class('TypeId', import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeFlag [enumeration]
    module.add_enum('AttributeFlag', ['ATTR_GET', 'ATTR_SET', 'ATTR_CONSTRUCT', 'ATTR_SGC'], outer_class=root_module['ns3::TypeId'], import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::SupportLevel [enumeration]
    module.add_enum('SupportLevel', ['SUPPORTED', 'DEPRECATED', 'OBSOLETE'], outer_class=root_module['ns3::TypeId'], import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation [struct]
    module.add_class('AttributeInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation [struct]
    module.add_class('TraceSourceInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## vector.h (module 'core'): ns3::Vector2D [class]
    module.add_class('Vector2D', import_from_module='ns.core')
    ## vector.h (module 'core'): ns3::Vector3D [class]
    module.add_class('Vector3D', import_from_module='ns.core')
    ## wifi-mode.h (module 'wifi'): ns3::WifiMode [class]
    module.add_class('WifiMode', import_from_module='ns.wifi')
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeFactory [class]
    module.add_class('WifiModeFactory', import_from_module='ns.wifi')
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhyListener [class]
    module.add_class('WifiPhyListener', allow_subclassing=True, import_from_module='ns.wifi')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation [struct]
    module.add_class('WifiRemoteStation', import_from_module='ns.wifi')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationInfo [class]
    module.add_class('WifiRemoteStationInfo', import_from_module='ns.wifi')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState [struct]
    module.add_class('WifiRemoteStationState', import_from_module='ns.wifi')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState [enumeration]
    module.add_enum('', ['BRAND_NEW', 'DISASSOC', 'WAIT_ASSOC_TX_OK', 'GOT_ASSOC_TX_OK'], outer_class=root_module['ns3::WifiRemoteStationState'], import_from_module='ns.wifi')
    ## wifi-tx-vector.h (module 'wifi'): ns3::WifiTxVector [class]
    module.add_class('WifiTxVector', import_from_module='ns.wifi')
    ## empty.h (module 'core'): ns3::empty [class]
    module.add_class('empty', import_from_module='ns.core')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t [class]
    module.add_class('int64x64_t', import_from_module='ns.core')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::impl_type [enumeration]
    module.add_enum('impl_type', ['int128_impl', 'cairo_impl', 'ld_impl'], outer_class=root_module['ns3::int64x64_t'], import_from_module='ns.core')
    ## wifi-phy.h (module 'wifi'): ns3::mpduInfo [struct]
    module.add_class('mpduInfo', import_from_module='ns.wifi')
    ## wifi-phy.h (module 'wifi'): ns3::signalNoiseDbm [struct]
    module.add_class('signalNoiseDbm', import_from_module='ns.wifi')
    ## chunk.h (module 'network'): ns3::Chunk [class]
    module.add_class('Chunk', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## header.h (module 'network'): ns3::Header [class]
    module.add_class('Header', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4DestinationUnreachable [class]
    module.add_class('Icmpv4DestinationUnreachable', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4DestinationUnreachable [enumeration]
    module.add_enum('', ['NET_UNREACHABLE', 'HOST_UNREACHABLE', 'PROTOCOL_UNREACHABLE', 'PORT_UNREACHABLE', 'FRAG_NEEDED', 'SOURCE_ROUTE_FAILED'], outer_class=root_module['ns3::Icmpv4DestinationUnreachable'], import_from_module='ns.internet')
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Echo [class]
    module.add_class('Icmpv4Echo', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Header [class]
    module.add_class('Icmpv4Header', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Header [enumeration]
    module.add_enum('', ['ECHO_REPLY', 'DEST_UNREACH', 'ECHO', 'TIME_EXCEEDED'], outer_class=root_module['ns3::Icmpv4Header'], import_from_module='ns.internet')
    ## icmpv4.h (module 'internet'): ns3::Icmpv4TimeExceeded [class]
    module.add_class('Icmpv4TimeExceeded', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4TimeExceeded [enumeration]
    module.add_enum('', ['TIME_TO_LIVE', 'FRAGMENT_REASSEMBLY'], outer_class=root_module['ns3::Icmpv4TimeExceeded'], import_from_module='ns.internet')
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header [class]
    module.add_class('Ipv4Header', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::DscpType [enumeration]
    module.add_enum('DscpType', ['DscpDefault', 'DSCP_CS1', 'DSCP_AF11', 'DSCP_AF12', 'DSCP_AF13', 'DSCP_CS2', 'DSCP_AF21', 'DSCP_AF22', 'DSCP_AF23', 'DSCP_CS3', 'DSCP_AF31', 'DSCP_AF32', 'DSCP_AF33', 'DSCP_CS4', 'DSCP_AF41', 'DSCP_AF42', 'DSCP_AF43', 'DSCP_CS5', 'DSCP_EF', 'DSCP_CS6', 'DSCP_CS7'], outer_class=root_module['ns3::Ipv4Header'], import_from_module='ns.internet')
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::EcnType [enumeration]
    module.add_enum('EcnType', ['ECN_NotECT', 'ECN_ECT1', 'ECN_ECT0', 'ECN_CE'], outer_class=root_module['ns3::Ipv4Header'], import_from_module='ns.internet')
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header [class]
    module.add_class('Ipv6Header', import_from_module='ns.internet', parent=root_module['ns3::Header'])
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::DscpType [enumeration]
    module.add_enum('DscpType', ['DscpDefault', 'DSCP_CS1', 'DSCP_AF11', 'DSCP_AF12', 'DSCP_AF13', 'DSCP_CS2', 'DSCP_AF21', 'DSCP_AF22', 'DSCP_AF23', 'DSCP_CS3', 'DSCP_AF31', 'DSCP_AF32', 'DSCP_AF33', 'DSCP_CS4', 'DSCP_AF41', 'DSCP_AF42', 'DSCP_AF43', 'DSCP_CS5', 'DSCP_EF', 'DSCP_CS6', 'DSCP_CS7'], outer_class=root_module['ns3::Ipv6Header'], import_from_module='ns.internet')
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::NextHeader_e [enumeration]
    module.add_enum('NextHeader_e', ['IPV6_EXT_HOP_BY_HOP', 'IPV6_IPV4', 'IPV6_TCP', 'IPV6_UDP', 'IPV6_IPV6', 'IPV6_EXT_ROUTING', 'IPV6_EXT_FRAGMENTATION', 'IPV6_EXT_CONFIDENTIALITY', 'IPV6_EXT_AUTHENTIFICATION', 'IPV6_ICMPV6', 'IPV6_EXT_END', 'IPV6_EXT_DESTINATION', 'IPV6_SCTP', 'IPV6_EXT_MOBILITY', 'IPV6_UDP_LITE'], outer_class=root_module['ns3::Ipv6Header'], import_from_module='ns.internet')
    ## object.h (module 'core'): ns3::Object [class]
    module.add_class('Object', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    ## object.h (module 'core'): ns3::Object::AggregateIterator [class]
    module.add_class('AggregateIterator', import_from_module='ns.core', outer_class=root_module['ns3::Object'])
    ## packet-filter.h (module 'traffic-control'): ns3::PacketFilter [class]
    module.add_class('PacketFilter', import_from_module='ns.traffic_control', parent=root_module['ns3::Object'])
    ## queue.h (module 'network'): ns3::Queue [class]
    module.add_class('Queue', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## queue.h (module 'network'): ns3::Queue::QueueMode [enumeration]
    module.add_enum('QueueMode', ['QUEUE_MODE_PACKETS', 'QUEUE_MODE_BYTES'], outer_class=root_module['ns3::Queue'], import_from_module='ns.network')
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDisc [class]
    module.add_class('QueueDisc', import_from_module='ns.traffic_control', parent=root_module['ns3::Object'])
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDisc::WakeMode [enumeration]
    module.add_enum('WakeMode', ['WAKE_ROOT', 'WAKE_CHILD'], outer_class=root_module['ns3::QueueDisc'], import_from_module='ns.traffic-control')
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDiscClass [class]
    module.add_class('QueueDiscClass', import_from_module='ns.traffic_control', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::RandomVariableStream [class]
    module.add_class('RandomVariableStream', import_from_module='ns.core', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::SequentialRandomVariable [class]
    module.add_class('SequentialRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeAccessor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeChecker', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeChecker>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::AttributeValue', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeValue>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::CallbackImplBase', 'ns3::empty', 'ns3::DefaultDeleter<ns3::CallbackImplBase>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::EventImpl', 'ns3::empty', 'ns3::DefaultDeleter<ns3::EventImpl>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Hash::Implementation', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Hash::Implementation>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter<ns3::InterferenceHelper::Event> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::InterferenceHelper::Event', 'ns3::empty', 'ns3::DefaultDeleter<ns3::InterferenceHelper::Event>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Ipv4MulticastRoute', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Ipv4MulticastRoute>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Ipv4Route', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Ipv4Route>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::NetDeviceQueue', 'ns3::empty', 'ns3::DefaultDeleter<ns3::NetDeviceQueue>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::NixVector', 'ns3::empty', 'ns3::DefaultDeleter<ns3::NixVector>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::OutputStreamWrapper', 'ns3::empty', 'ns3::DefaultDeleter<ns3::OutputStreamWrapper>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::Packet', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Packet>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::QueueItem', 'ns3::empty', 'ns3::DefaultDeleter<ns3::QueueItem>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::TraceSourceAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::TraceSourceAccessor>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> > [class]
    module.add_class('SimpleRefCount', automatic_type_narrowing=True, import_from_module='ns.core', template_parameters=['ns3::WifiInformationElement', 'ns3::empty', 'ns3::DefaultDeleter<ns3::WifiInformationElement>'], parent=root_module['ns3::empty'], memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'))
    ## socket.h (module 'network'): ns3::Socket [class]
    module.add_class('Socket', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## socket.h (module 'network'): ns3::Socket::SocketErrno [enumeration]
    module.add_enum('SocketErrno', ['ERROR_NOTERROR', 'ERROR_ISCONN', 'ERROR_NOTCONN', 'ERROR_MSGSIZE', 'ERROR_AGAIN', 'ERROR_SHUTDOWN', 'ERROR_OPNOTSUPP', 'ERROR_AFNOSUPPORT', 'ERROR_INVAL', 'ERROR_BADF', 'ERROR_NOROUTETOHOST', 'ERROR_NODEV', 'ERROR_ADDRNOTAVAIL', 'ERROR_ADDRINUSE', 'SOCKET_ERRNO_LAST'], outer_class=root_module['ns3::Socket'], import_from_module='ns.network')
    ## socket.h (module 'network'): ns3::Socket::SocketType [enumeration]
    module.add_enum('SocketType', ['NS3_SOCK_STREAM', 'NS3_SOCK_SEQPACKET', 'NS3_SOCK_DGRAM', 'NS3_SOCK_RAW'], outer_class=root_module['ns3::Socket'], import_from_module='ns.network')
    ## socket.h (module 'network'): ns3::Socket::SocketPriority [enumeration]
    module.add_enum('SocketPriority', ['NS3_PRIO_BESTEFFORT', 'NS3_PRIO_FILLER', 'NS3_PRIO_BULK', 'NS3_PRIO_INTERACTIVE_BULK', 'NS3_PRIO_INTERACTIVE', 'NS3_PRIO_CONTROL'], outer_class=root_module['ns3::Socket'], import_from_module='ns.network')
    ## socket.h (module 'network'): ns3::Socket::Ipv6MulticastFilterMode [enumeration]
    module.add_enum('Ipv6MulticastFilterMode', ['INCLUDE', 'EXCLUDE'], outer_class=root_module['ns3::Socket'], import_from_module='ns.network')
    ## socket.h (module 'network'): ns3::SocketIpTosTag [class]
    module.add_class('SocketIpTosTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketIpTtlTag [class]
    module.add_class('SocketIpTtlTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketIpv6HopLimitTag [class]
    module.add_class('SocketIpv6HopLimitTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketIpv6TclassTag [class]
    module.add_class('SocketIpv6TclassTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketPriorityTag [class]
    module.add_class('SocketPriorityTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## socket.h (module 'network'): ns3::SocketSetDontFragmentTag [class]
    module.add_class('SocketSetDontFragmentTag', import_from_module='ns.network', parent=root_module['ns3::Tag'])
    ## nstime.h (module 'core'): ns3::Time [class]
    module.add_class('Time', import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time::Unit [enumeration]
    module.add_enum('Unit', ['Y', 'D', 'H', 'MIN', 'S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST'], outer_class=root_module['ns3::Time'], import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time [class]
    root_module['ns3::Time'].implicitly_converts_to(root_module['ns3::int64x64_t'])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor [class]
    module.add_class('TraceSourceAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    ## traffic-control-layer.h (module 'traffic-control'): ns3::TrafficControlLayer [class]
    module.add_class('TrafficControlLayer', import_from_module='ns.traffic_control', parent=root_module['ns3::Object'])
    ## trailer.h (module 'network'): ns3::Trailer [class]
    module.add_class('Trailer', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## random-variable-stream.h (module 'core'): ns3::TriangularRandomVariable [class]
    module.add_class('TriangularRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::UniformRandomVariable [class]
    module.add_class('UniformRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::WeibullRandomVariable [class]
    module.add_class('WeibullRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## wifi-information-element.h (module 'wifi'): ns3::WifiInformationElement [class]
    module.add_class('WifiInformationElement', import_from_module='ns.wifi', parent=root_module['ns3::SimpleRefCount< ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> >'])
    ## wifi-mac.h (module 'wifi'): ns3::WifiMac [class]
    module.add_class('WifiMac', import_from_module='ns.wifi', parent=root_module['ns3::Object'])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader [class]
    module.add_class('WifiMacHeader', import_from_module='ns.wifi', parent=root_module['ns3::Header'])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::QosAckPolicy [enumeration]
    module.add_enum('QosAckPolicy', ['NORMAL_ACK', 'NO_ACK', 'NO_EXPLICIT_ACK', 'BLOCK_ACK'], outer_class=root_module['ns3::WifiMacHeader'], import_from_module='ns.wifi')
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::AddressType [enumeration]
    module.add_enum('AddressType', ['ADDR1', 'ADDR2', 'ADDR3', 'ADDR4'], outer_class=root_module['ns3::WifiMacHeader'], import_from_module='ns.wifi')
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhy [class]
    module.add_class('WifiPhy', import_from_module='ns.wifi', parent=root_module['ns3::Object'])
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhy::State [enumeration]
    module.add_enum('State', ['IDLE', 'CCA_BUSY', 'TX', 'RX', 'SWITCHING', 'SLEEP'], outer_class=root_module['ns3::WifiPhy'], import_from_module='ns.wifi')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationManager [class]
    module.add_class('WifiRemoteStationManager', import_from_module='ns.wifi', parent=root_module['ns3::Object'])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationManager::ProtectionMode [enumeration]
    module.add_enum('ProtectionMode', ['RTS_CTS', 'CTS_TO_SELF'], outer_class=root_module['ns3::WifiRemoteStationManager'], import_from_module='ns.wifi')
    ## random-variable-stream.h (module 'core'): ns3::ZetaRandomVariable [class]
    module.add_class('ZetaRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::ZipfRandomVariable [class]
    module.add_class('ZipfRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## arp-cache.h (module 'internet'): ns3::ArpCache [class]
    module.add_class('ArpCache', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry [class]
    module.add_class('Entry', import_from_module='ns.internet', outer_class=root_module['ns3::ArpCache'])
    ## attribute.h (module 'core'): ns3::AttributeAccessor [class]
    module.add_class('AttributeAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    ## attribute.h (module 'core'): ns3::AttributeChecker [class]
    module.add_class('AttributeChecker', allow_subclassing=False, automatic_type_narrowing=True, import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    ## attribute.h (module 'core'): ns3::AttributeValue [class]
    module.add_class('AttributeValue', allow_subclassing=False, automatic_type_narrowing=True, import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    ## boolean.h (module 'core'): ns3::BooleanChecker [class]
    module.add_class('BooleanChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## boolean.h (module 'core'): ns3::BooleanValue [class]
    module.add_class('BooleanValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## callback.h (module 'core'): ns3::CallbackChecker [class]
    module.add_class('CallbackChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## callback.h (module 'core'): ns3::CallbackImplBase [class]
    module.add_class('CallbackImplBase', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >'])
    ## callback.h (module 'core'): ns3::CallbackValue [class]
    module.add_class('CallbackValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## channel.h (module 'network'): ns3::Channel [class]
    module.add_class('Channel', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::ConstantRandomVariable [class]
    module.add_class('ConstantRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::DeterministicRandomVariable [class]
    module.add_class('DeterministicRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## double.h (module 'core'): ns3::DoubleValue [class]
    module.add_class('DoubleValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## random-variable-stream.h (module 'core'): ns3::EmpiricalRandomVariable [class]
    module.add_class('EmpiricalRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## attribute.h (module 'core'): ns3::EmptyAttributeAccessor [class]
    module.add_class('EmptyAttributeAccessor', import_from_module='ns.core', parent=root_module['ns3::AttributeAccessor'])
    ## attribute.h (module 'core'): ns3::EmptyAttributeChecker [class]
    module.add_class('EmptyAttributeChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue [class]
    module.add_class('EmptyAttributeValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## enum.h (module 'core'): ns3::EnumChecker [class]
    module.add_class('EnumChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## enum.h (module 'core'): ns3::EnumValue [class]
    module.add_class('EnumValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## random-variable-stream.h (module 'core'): ns3::ErlangRandomVariable [class]
    module.add_class('ErlangRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## error-rate-model.h (module 'wifi'): ns3::ErrorRateModel [class]
    module.add_class('ErrorRateModel', import_from_module='ns.wifi', parent=root_module['ns3::Object'])
    ## event-impl.h (module 'core'): ns3::EventImpl [class]
    module.add_class('EventImpl', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    ## random-variable-stream.h (module 'core'): ns3::ExponentialRandomVariable [class]
    module.add_class('ExponentialRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::GammaRandomVariable [class]
    module.add_class('GammaRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilities [class]
    module.add_class('HtCapabilities', import_from_module='ns.wifi', parent=root_module['ns3::WifiInformationElement'])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesChecker [class]
    module.add_class('HtCapabilitiesChecker', import_from_module='ns.wifi', parent=root_module['ns3::AttributeChecker'])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesValue [class]
    module.add_class('HtCapabilitiesValue', import_from_module='ns.wifi', parent=root_module['ns3::AttributeValue'])
    ## integer.h (module 'core'): ns3::IntegerValue [class]
    module.add_class('IntegerValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol [class]
    module.add_class('IpL4Protocol', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus [enumeration]
    module.add_enum('RxStatus', ['RX_OK', 'RX_CSUM_FAILED', 'RX_ENDPOINT_CLOSED', 'RX_ENDPOINT_UNREACH'], outer_class=root_module['ns3::IpL4Protocol'], import_from_module='ns.internet')
    ## ipv4.h (module 'internet'): ns3::Ipv4 [class]
    module.add_class('Ipv4', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker [class]
    module.add_class('Ipv4AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue [class]
    module.add_class('Ipv4AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4Interface [class]
    module.add_class('Ipv4Interface', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol [class]
    module.add_class('Ipv4L3Protocol', import_from_module='ns.internet', parent=root_module['ns3::Ipv4'])
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol::DropReason [enumeration]
    module.add_enum('DropReason', ['DROP_TTL_EXPIRED', 'DROP_NO_ROUTE', 'DROP_BAD_CHECKSUM', 'DROP_INTERFACE_DOWN', 'DROP_ROUTE_ERROR', 'DROP_FRAGMENT_TIMEOUT'], outer_class=root_module['ns3::Ipv4L3Protocol'], import_from_module='ns.internet')
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker [class]
    module.add_class('Ipv4MaskChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue [class]
    module.add_class('Ipv4MaskValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute [class]
    module.add_class('Ipv4MulticastRoute', import_from_module='ns.internet', parent=root_module['ns3::SimpleRefCount< ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >'])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Route [class]
    module.add_class('Ipv4Route', import_from_module='ns.internet', parent=root_module['ns3::SimpleRefCount< ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >'])
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ipv4RoutingProtocol [class]
    module.add_class('Ipv4RoutingProtocol', import_from_module='ns.internet', parent=root_module['ns3::Object'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker [class]
    module.add_class('Ipv6AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue [class]
    module.add_class('Ipv6AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker [class]
    module.add_class('Ipv6PrefixChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue [class]
    module.add_class('Ipv6PrefixValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## random-variable-stream.h (module 'core'): ns3::LogNormalRandomVariable [class]
    module.add_class('LogNormalRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker [class]
    module.add_class('Mac48AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue [class]
    module.add_class('Mac48AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## mobility-model.h (module 'mobility'): ns3::MobilityModel [class]
    module.add_class('MobilityModel', import_from_module='ns.mobility', parent=root_module['ns3::Object'])
    ## net-device.h (module 'network'): ns3::NetDevice [class]
    module.add_class('NetDevice', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## net-device.h (module 'network'): ns3::NetDevice::PacketType [enumeration]
    module.add_enum('PacketType', ['PACKET_HOST', 'NS3_PACKET_HOST', 'PACKET_BROADCAST', 'NS3_PACKET_BROADCAST', 'PACKET_MULTICAST', 'NS3_PACKET_MULTICAST', 'PACKET_OTHERHOST', 'NS3_PACKET_OTHERHOST'], outer_class=root_module['ns3::NetDevice'], import_from_module='ns.network')
    ## net-device.h (module 'network'): ns3::NetDeviceQueue [class]
    module.add_class('NetDeviceQueue', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >'])
    ## net-device.h (module 'network'): ns3::NetDeviceQueueInterface [class]
    module.add_class('NetDeviceQueueInterface', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## nix-vector.h (module 'network'): ns3::NixVector [class]
    module.add_class('NixVector', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >'])
    ## node.h (module 'network'): ns3::Node [class]
    module.add_class('Node', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::NormalRandomVariable [class]
    module.add_class('NormalRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker [class]
    module.add_class('ObjectFactoryChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue [class]
    module.add_class('ObjectFactoryValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper [class]
    module.add_class('OutputStreamWrapper', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >'])
    ## packet.h (module 'network'): ns3::Packet [class]
    module.add_class('Packet', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >'])
    ## random-variable-stream.h (module 'core'): ns3::ParetoRandomVariable [class]
    module.add_class('ParetoRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## net-device.h (module 'network'): ns3::QueueItem [class]
    module.add_class('QueueItem', import_from_module='ns.network', parent=root_module['ns3::SimpleRefCount< ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >'])
    ## net-device.h (module 'network'): ns3::QueueItem::Uint8Values [enumeration]
    module.add_enum('Uint8Values', ['IP_DSFIELD'], outer_class=root_module['ns3::QueueItem'], import_from_module='ns.network')
    ## ssid.h (module 'wifi'): ns3::Ssid [class]
    module.add_class('Ssid', import_from_module='ns.wifi', parent=root_module['ns3::WifiInformationElement'])
    ## ssid.h (module 'wifi'): ns3::SsidChecker [class]
    module.add_class('SsidChecker', import_from_module='ns.wifi', parent=root_module['ns3::AttributeChecker'])
    ## ssid.h (module 'wifi'): ns3::SsidValue [class]
    module.add_class('SsidValue', import_from_module='ns.wifi', parent=root_module['ns3::AttributeValue'])
    ## tcp-l4-protocol.h (module 'internet'): ns3::TcpL4Protocol [class]
    module.add_class('TcpL4Protocol', import_from_module='ns.internet', parent=root_module['ns3::IpL4Protocol'])
    ## nstime.h (module 'core'): ns3::TimeValue [class]
    module.add_class('TimeValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## type-id.h (module 'core'): ns3::TypeIdChecker [class]
    module.add_class('TypeIdChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## type-id.h (module 'core'): ns3::TypeIdValue [class]
    module.add_class('TypeIdValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## udp-l4-protocol.h (module 'internet'): ns3::UdpL4Protocol [class]
    module.add_class('UdpL4Protocol', import_from_module='ns.internet', parent=root_module['ns3::IpL4Protocol'])
    ## uinteger.h (module 'core'): ns3::UintegerValue [class]
    module.add_class('UintegerValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## vector.h (module 'core'): ns3::Vector2DChecker [class]
    module.add_class('Vector2DChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## vector.h (module 'core'): ns3::Vector2DValue [class]
    module.add_class('Vector2DValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## vector.h (module 'core'): ns3::Vector3DChecker [class]
    module.add_class('Vector3DChecker', import_from_module='ns.core', parent=root_module['ns3::AttributeChecker'])
    ## vector.h (module 'core'): ns3::Vector3DValue [class]
    module.add_class('Vector3DValue', import_from_module='ns.core', parent=root_module['ns3::AttributeValue'])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilities [class]
    module.add_class('VhtCapabilities', import_from_module='ns.wifi', parent=root_module['ns3::WifiInformationElement'])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesChecker [class]
    module.add_class('VhtCapabilitiesChecker', import_from_module='ns.wifi', parent=root_module['ns3::AttributeChecker'])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesValue [class]
    module.add_class('VhtCapabilitiesValue', import_from_module='ns.wifi', parent=root_module['ns3::AttributeValue'])
    ## wifi-channel.h (module 'wifi'): ns3::WifiChannel [class]
    module.add_class('WifiChannel', import_from_module='ns.wifi', parent=root_module['ns3::Channel'])
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeChecker [class]
    module.add_class('WifiModeChecker', import_from_module='ns.wifi', parent=root_module['ns3::AttributeChecker'])
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeValue [class]
    module.add_class('WifiModeValue', import_from_module='ns.wifi', parent=root_module['ns3::AttributeValue'])
    ## address.h (module 'network'): ns3::AddressChecker [class]
    module.add_class('AddressChecker', import_from_module='ns.network', parent=root_module['ns3::AttributeChecker'])
    ## address.h (module 'network'): ns3::AddressValue [class]
    module.add_class('AddressValue', import_from_module='ns.network', parent=root_module['ns3::AttributeValue'])
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::Icmpv4L4Protocol [class]
    module.add_class('Icmpv4L4Protocol', import_from_module='ns.internet', parent=root_module['ns3::IpL4Protocol'])
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDiscItem [class]
    module.add_class('QueueDiscItem', import_from_module='ns.traffic_control', parent=root_module['ns3::QueueItem'])
    module.add_container('ns3::WifiModeList', 'ns3::WifiMode', container_type=u'vector')
    module.add_container('std::vector< ns3::Ipv6Address >', 'ns3::Ipv6Address', container_type=u'vector')
    module.add_container('std::vector< ns3::Ptr< ns3::QueueDisc > >', 'ns3::Ptr< ns3::QueueDisc >', container_type=u'vector')
    module.add_container('std::vector< unsigned int >', 'unsigned int', container_type=u'vector')
    module.add_container('std::list< std::pair< ns3::Ptr< ns3::Packet >, ns3::Ipv4Header > >', 'std::pair< ns3::Ptr< ns3::Packet >, ns3::Ipv4Header >', container_type=u'list')
    module.add_container('std::list< ns3::ArpCache::Entry * >', 'ns3::ArpCache::Entry *', container_type=u'list')
    module.add_container('std::map< unsigned int, unsigned int >', ('unsigned int', 'unsigned int'), container_type=u'map')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< short unsigned int, short int >', u'ns3::SequenceNumber16')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< short unsigned int, short int >*', u'ns3::SequenceNumber16*')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< short unsigned int, short int >&', u'ns3::SequenceNumber16&')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< unsigned int, int >', u'ns3::SequenceNumber32')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< unsigned int, int >*', u'ns3::SequenceNumber32*')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< unsigned int, int >&', u'ns3::SequenceNumber32&')
    typehandlers.add_type_alias(u'uint8_t', u'ns3::WifiInformationElementId')
    typehandlers.add_type_alias(u'uint8_t*', u'ns3::WifiInformationElementId*')
    typehandlers.add_type_alias(u'uint8_t&', u'ns3::WifiInformationElementId&')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< unsigned char, signed char >', u'ns3::SequenceNumber8')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< unsigned char, signed char >*', u'ns3::SequenceNumber8*')
    typehandlers.add_type_alias(u'ns3::SequenceNumber< unsigned char, signed char >&', u'ns3::SequenceNumber8&')
    typehandlers.add_type_alias(u'ns3::Vector3D', u'ns3::Vector')
    typehandlers.add_type_alias(u'ns3::Vector3D*', u'ns3::Vector*')
    typehandlers.add_type_alias(u'ns3::Vector3D&', u'ns3::Vector&')
    module.add_typedef(root_module['ns3::Vector3D'], 'Vector')
    typehandlers.add_type_alias(u'std::vector< ns3::WifiMode, std::allocator< ns3::WifiMode > >', u'ns3::WifiModeList')
    typehandlers.add_type_alias(u'std::vector< ns3::WifiMode, std::allocator< ns3::WifiMode > >*', u'ns3::WifiModeList*')
    typehandlers.add_type_alias(u'std::vector< ns3::WifiMode, std::allocator< ns3::WifiMode > >&', u'ns3::WifiModeList&')
    typehandlers.add_type_alias(u'ns3::Vector3DValue', u'ns3::VectorValue')
    typehandlers.add_type_alias(u'ns3::Vector3DValue*', u'ns3::VectorValue*')
    typehandlers.add_type_alias(u'ns3::Vector3DValue&', u'ns3::VectorValue&')
    module.add_typedef(root_module['ns3::Vector3DValue'], 'VectorValue')
    typehandlers.add_type_alias(u'ns3::Vector3DChecker', u'ns3::VectorChecker')
    typehandlers.add_type_alias(u'ns3::Vector3DChecker*', u'ns3::VectorChecker*')
    typehandlers.add_type_alias(u'ns3::Vector3DChecker&', u'ns3::VectorChecker&')
    module.add_typedef(root_module['ns3::Vector3DChecker'], 'VectorChecker')
    typehandlers.add_type_alias(u'__gnu_cxx::__normal_iterator< ns3::WifiMode const *, std::vector< ns3::WifiMode, std::allocator< ns3::WifiMode > > >', u'ns3::WifiModeListIterator')
    typehandlers.add_type_alias(u'__gnu_cxx::__normal_iterator< ns3::WifiMode const *, std::vector< ns3::WifiMode, std::allocator< ns3::WifiMode > > >*', u'ns3::WifiModeListIterator*')
    typehandlers.add_type_alias(u'__gnu_cxx::__normal_iterator< ns3::WifiMode const *, std::vector< ns3::WifiMode, std::allocator< ns3::WifiMode > > >&', u'ns3::WifiModeListIterator&')
    
    ## Register a nested module for the namespace FatalImpl
    
    nested_module = module.add_cpp_namespace('FatalImpl')
    register_types_ns3_FatalImpl(nested_module)
    
    
    ## Register a nested module for the namespace Hash
    
    nested_module = module.add_cpp_namespace('Hash')
    register_types_ns3_Hash(nested_module)
    
    
    ## Register a nested module for the namespace TracedValueCallback
    
    nested_module = module.add_cpp_namespace('TracedValueCallback')
    register_types_ns3_TracedValueCallback(nested_module)
    
    
    ## Register a nested module for the namespace dsr
    
    nested_module = module.add_cpp_namespace('dsr')
    register_types_ns3_dsr(nested_module)
    
    
    ## Register a nested module for the namespace internal
    
    nested_module = module.add_cpp_namespace('internal')
    register_types_ns3_internal(nested_module)
    

def register_types_ns3_FatalImpl(module):
    root_module = module.get_root()
    

def register_types_ns3_Hash(module):
    root_module = module.get_root()
    
    ## hash-function.h (module 'core'): ns3::Hash::Implementation [class]
    module.add_class('Implementation', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >'])
    typehandlers.add_type_alias(u'uint64_t ( * ) ( char const *, size_t ) *', u'ns3::Hash::Hash64Function_ptr')
    typehandlers.add_type_alias(u'uint64_t ( * ) ( char const *, size_t ) **', u'ns3::Hash::Hash64Function_ptr*')
    typehandlers.add_type_alias(u'uint64_t ( * ) ( char const *, size_t ) *&', u'ns3::Hash::Hash64Function_ptr&')
    typehandlers.add_type_alias(u'uint32_t ( * ) ( char const *, size_t ) *', u'ns3::Hash::Hash32Function_ptr')
    typehandlers.add_type_alias(u'uint32_t ( * ) ( char const *, size_t ) **', u'ns3::Hash::Hash32Function_ptr*')
    typehandlers.add_type_alias(u'uint32_t ( * ) ( char const *, size_t ) *&', u'ns3::Hash::Hash32Function_ptr&')
    
    ## Register a nested module for the namespace Function
    
    nested_module = module.add_cpp_namespace('Function')
    register_types_ns3_Hash_Function(nested_module)
    

def register_types_ns3_Hash_Function(module):
    root_module = module.get_root()
    
    ## hash-fnv.h (module 'core'): ns3::Hash::Function::Fnv1a [class]
    module.add_class('Fnv1a', import_from_module='ns.core', parent=root_module['ns3::Hash::Implementation'])
    ## hash-function.h (module 'core'): ns3::Hash::Function::Hash32 [class]
    module.add_class('Hash32', import_from_module='ns.core', parent=root_module['ns3::Hash::Implementation'])
    ## hash-function.h (module 'core'): ns3::Hash::Function::Hash64 [class]
    module.add_class('Hash64', import_from_module='ns.core', parent=root_module['ns3::Hash::Implementation'])
    ## hash-murmur3.h (module 'core'): ns3::Hash::Function::Murmur3 [class]
    module.add_class('Murmur3', import_from_module='ns.core', parent=root_module['ns3::Hash::Implementation'])

def register_types_ns3_TracedValueCallback(module):
    root_module = module.get_root()
    
    typehandlers.add_type_alias(u'void ( * ) ( double, double ) *', u'ns3::TracedValueCallback::Double')
    typehandlers.add_type_alias(u'void ( * ) ( double, double ) **', u'ns3::TracedValueCallback::Double*')
    typehandlers.add_type_alias(u'void ( * ) ( double, double ) *&', u'ns3::TracedValueCallback::Double&')
    typehandlers.add_type_alias(u'void ( * ) ( ns3::SequenceNumber32, ns3::SequenceNumber32 ) *', u'ns3::TracedValueCallback::SequenceNumber32')
    typehandlers.add_type_alias(u'void ( * ) ( ns3::SequenceNumber32, ns3::SequenceNumber32 ) **', u'ns3::TracedValueCallback::SequenceNumber32*')
    typehandlers.add_type_alias(u'void ( * ) ( ns3::SequenceNumber32, ns3::SequenceNumber32 ) *&', u'ns3::TracedValueCallback::SequenceNumber32&')
    typehandlers.add_type_alias(u'void ( * ) ( int8_t, int8_t ) *', u'ns3::TracedValueCallback::Int8')
    typehandlers.add_type_alias(u'void ( * ) ( int8_t, int8_t ) **', u'ns3::TracedValueCallback::Int8*')
    typehandlers.add_type_alias(u'void ( * ) ( int8_t, int8_t ) *&', u'ns3::TracedValueCallback::Int8&')
    typehandlers.add_type_alias(u'void ( * ) ( uint8_t, uint8_t ) *', u'ns3::TracedValueCallback::Uint8')
    typehandlers.add_type_alias(u'void ( * ) ( uint8_t, uint8_t ) **', u'ns3::TracedValueCallback::Uint8*')
    typehandlers.add_type_alias(u'void ( * ) ( uint8_t, uint8_t ) *&', u'ns3::TracedValueCallback::Uint8&')
    typehandlers.add_type_alias(u'void ( * ) ( int32_t, int32_t ) *', u'ns3::TracedValueCallback::Int32')
    typehandlers.add_type_alias(u'void ( * ) ( int32_t, int32_t ) **', u'ns3::TracedValueCallback::Int32*')
    typehandlers.add_type_alias(u'void ( * ) ( int32_t, int32_t ) *&', u'ns3::TracedValueCallback::Int32&')
    typehandlers.add_type_alias(u'void ( * ) ( bool, bool ) *', u'ns3::TracedValueCallback::Bool')
    typehandlers.add_type_alias(u'void ( * ) ( bool, bool ) **', u'ns3::TracedValueCallback::Bool*')
    typehandlers.add_type_alias(u'void ( * ) ( bool, bool ) *&', u'ns3::TracedValueCallback::Bool&')
    typehandlers.add_type_alias(u'void ( * ) ( uint16_t, uint16_t ) *', u'ns3::TracedValueCallback::Uint16')
    typehandlers.add_type_alias(u'void ( * ) ( uint16_t, uint16_t ) **', u'ns3::TracedValueCallback::Uint16*')
    typehandlers.add_type_alias(u'void ( * ) ( uint16_t, uint16_t ) *&', u'ns3::TracedValueCallback::Uint16&')
    typehandlers.add_type_alias(u'void ( * ) ( uint32_t, uint32_t ) *', u'ns3::TracedValueCallback::Uint32')
    typehandlers.add_type_alias(u'void ( * ) ( uint32_t, uint32_t ) **', u'ns3::TracedValueCallback::Uint32*')
    typehandlers.add_type_alias(u'void ( * ) ( uint32_t, uint32_t ) *&', u'ns3::TracedValueCallback::Uint32&')
    typehandlers.add_type_alias(u'void ( * ) ( int16_t, int16_t ) *', u'ns3::TracedValueCallback::Int16')
    typehandlers.add_type_alias(u'void ( * ) ( int16_t, int16_t ) **', u'ns3::TracedValueCallback::Int16*')
    typehandlers.add_type_alias(u'void ( * ) ( int16_t, int16_t ) *&', u'ns3::TracedValueCallback::Int16&')
    typehandlers.add_type_alias(u'void ( * ) ( ns3::Time, ns3::Time ) *', u'ns3::TracedValueCallback::Time')
    typehandlers.add_type_alias(u'void ( * ) ( ns3::Time, ns3::Time ) **', u'ns3::TracedValueCallback::Time*')
    typehandlers.add_type_alias(u'void ( * ) ( ns3::Time, ns3::Time ) *&', u'ns3::TracedValueCallback::Time&')
    typehandlers.add_type_alias(u'void ( * ) (  ) *', u'ns3::TracedValueCallback::Void')
    typehandlers.add_type_alias(u'void ( * ) (  ) **', u'ns3::TracedValueCallback::Void*')
    typehandlers.add_type_alias(u'void ( * ) (  ) *&', u'ns3::TracedValueCallback::Void&')

def register_types_ns3_dsr(module):
    root_module = module.get_root()
    
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::ErrorType [enumeration]
    module.add_enum('ErrorType', ['NODE_UNREACHABLE', 'FLOW_STATE_NOT_SUPPORTED', 'OPTION_NOT_SUPPORTED'])
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrMessageType [enumeration]
    module.add_enum('DsrMessageType', ['DSR_CONTROL_PACKET', 'DSR_DATA_PACKET'])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::LinkStates [enumeration]
    module.add_enum('LinkStates', ['PROBABLE', 'QUESTIONABLE'])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList [struct]
    module.add_class('BlackList')
    ## dsr-errorbuff.h (module 'dsr'): ns3::dsr::DsrErrorBuffEntry [class]
    module.add_class('DsrErrorBuffEntry')
    ## dsr-errorbuff.h (module 'dsr'): ns3::dsr::DsrErrorBuffer [class]
    module.add_class('DsrErrorBuffer')
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrFsHeader [class]
    module.add_class('DsrFsHeader', parent=root_module['ns3::Header'])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::DsrGraReply [class]
    module.add_class('DsrGraReply', parent=root_module['ns3::Object'])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrLinkStab [class]
    module.add_class('DsrLinkStab')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::DsrMaintainBuffEntry [class]
    module.add_class('DsrMaintainBuffEntry')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::DsrMaintainBuffer [class]
    module.add_class('DsrMaintainBuffer')
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueue [class]
    module.add_class('DsrNetworkQueue', parent=root_module['ns3::Object'])
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueueEntry [class]
    module.add_class('DsrNetworkQueueEntry')
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrNodeStab [class]
    module.add_class('DsrNodeStab')
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrOptionField [class]
    module.add_class('DsrOptionField')
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader [class]
    module.add_class('DsrOptionHeader', parent=root_module['ns3::Header'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment [struct]
    module.add_class('Alignment', outer_class=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionPad1Header [class]
    module.add_class('DsrOptionPad1Header', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionPadnHeader [class]
    module.add_class('DsrOptionPadnHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrHeader [class]
    module.add_class('DsrOptionRerrHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrUnreachHeader [class]
    module.add_class('DsrOptionRerrUnreachHeader', parent=root_module['ns3::dsr::DsrOptionRerrHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrUnsupportHeader [class]
    module.add_class('DsrOptionRerrUnsupportHeader', parent=root_module['ns3::dsr::DsrOptionRerrHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRrepHeader [class]
    module.add_class('DsrOptionRrepHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRreqHeader [class]
    module.add_class('DsrOptionRreqHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionSRHeader [class]
    module.add_class('DsrOptionSRHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptions [class]
    module.add_class('DsrOptions', parent=root_module['ns3::Object'])
    ## dsr-passive-buff.h (module 'dsr'): ns3::dsr::DsrPassiveBuffEntry [class]
    module.add_class('DsrPassiveBuffEntry')
    ## dsr-passive-buff.h (module 'dsr'): ns3::dsr::DsrPassiveBuffer [class]
    module.add_class('DsrPassiveBuffer', parent=root_module['ns3::Object'])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::DsrReceivedRreqEntry [class]
    module.add_class('DsrReceivedRreqEntry')
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache [class]
    module.add_class('DsrRouteCache', parent=root_module['ns3::Object'])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor [struct]
    module.add_class('Neighbor', outer_class=root_module['ns3::dsr::DsrRouteCache'])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCacheEntry [class]
    module.add_class('DsrRouteCacheEntry')
    ## dsr-routing.h (module 'dsr'): ns3::dsr::DsrRouting [class]
    module.add_class('DsrRouting', parent=root_module['ns3::IpL4Protocol'])
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrRoutingHeader [class]
    module.add_class('DsrRoutingHeader', parent=[root_module['ns3::dsr::DsrFsHeader'], root_module['ns3::dsr::DsrOptionField']])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::DsrRreqTable [class]
    module.add_class('DsrRreqTable', parent=root_module['ns3::Object'])
    ## dsr-rsendbuff.h (module 'dsr'): ns3::dsr::DsrSendBuffEntry [class]
    module.add_class('DsrSendBuffEntry')
    ## dsr-rsendbuff.h (module 'dsr'): ns3::dsr::DsrSendBuffer [class]
    module.add_class('DsrSendBuffer')
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::GraReplyEntry [struct]
    module.add_class('GraReplyEntry')
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::Link [struct]
    module.add_class('Link')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey [struct]
    module.add_class('LinkKey')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey [struct]
    module.add_class('NetworkKey')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey [struct]
    module.add_class('PassiveKey')
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::RreqTableEntry [struct]
    module.add_class('RreqTableEntry')
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAck [class]
    module.add_class('DsrOptionAck', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionAckHeader [class]
    module.add_class('DsrOptionAckHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAckReq [class]
    module.add_class('DsrOptionAckReq', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionAckReqHeader [class]
    module.add_class('DsrOptionAckReqHeader', parent=root_module['ns3::dsr::DsrOptionHeader'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPad1 [class]
    module.add_class('DsrOptionPad1', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPadn [class]
    module.add_class('DsrOptionPadn', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRerr [class]
    module.add_class('DsrOptionRerr', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRrep [class]
    module.add_class('DsrOptionRrep', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRreq [class]
    module.add_class('DsrOptionRreq', parent=root_module['ns3::dsr::DsrOptions'])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionSR [class]
    module.add_class('DsrOptionSR', parent=root_module['ns3::dsr::DsrOptions'])
    module.add_container('std::vector< ns3::dsr::DsrErrorBuffEntry >', 'ns3::dsr::DsrErrorBuffEntry', container_type=u'vector')
    module.add_container('std::vector< ns3::dsr::DsrNetworkQueueEntry >', 'ns3::dsr::DsrNetworkQueueEntry', container_type=u'vector')
    module.add_container('std::vector< ns3::Ipv4Address >', 'ns3::Ipv4Address', container_type=u'vector')
    module.add_container('std::vector< ns3::dsr::DsrRouteCache::Neighbor >', 'ns3::dsr::DsrRouteCache::Neighbor', container_type=u'vector')
    module.add_container('std::vector< ns3::Ptr< ns3::ArpCache > >', 'ns3::Ptr< ns3::ArpCache >', container_type=u'vector')
    module.add_container('std::list< std::vector< ns3::Ipv4Address > >', 'std::vector< ns3::Ipv4Address >', container_type=u'list')
    module.add_container('std::list< ns3::dsr::DsrRouteCacheEntry >', 'ns3::dsr::DsrRouteCacheEntry', container_type=u'list')
    module.add_container('std::vector< std::string >', 'std::string', container_type=u'vector')
    module.add_container('std::map< ns3::Ipv4Address, ns3::dsr::RreqTableEntry >', ('ns3::Ipv4Address', 'ns3::dsr::RreqTableEntry'), container_type=u'map')
    module.add_container('std::vector< ns3::dsr::DsrSendBuffEntry >', 'ns3::dsr::DsrSendBuffEntry', container_type=u'vector')

def register_types_ns3_internal(module):
    root_module = module.get_root()
    

def register_methods(root_module):
    register_Ns3Address_methods(root_module, root_module['ns3::Address'])
    register_Ns3AttributeConstructionList_methods(root_module, root_module['ns3::AttributeConstructionList'])
    register_Ns3AttributeConstructionListItem_methods(root_module, root_module['ns3::AttributeConstructionList::Item'])
    register_Ns3Buffer_methods(root_module, root_module['ns3::Buffer'])
    register_Ns3BufferIterator_methods(root_module, root_module['ns3::Buffer::Iterator'])
    register_Ns3ByteTagIterator_methods(root_module, root_module['ns3::ByteTagIterator'])
    register_Ns3ByteTagIteratorItem_methods(root_module, root_module['ns3::ByteTagIterator::Item'])
    register_Ns3ByteTagList_methods(root_module, root_module['ns3::ByteTagList'])
    register_Ns3ByteTagListIterator_methods(root_module, root_module['ns3::ByteTagList::Iterator'])
    register_Ns3ByteTagListIteratorItem_methods(root_module, root_module['ns3::ByteTagList::Iterator::Item'])
    register_Ns3CallbackBase_methods(root_module, root_module['ns3::CallbackBase'])
    register_Ns3DsrHelper_methods(root_module, root_module['ns3::DsrHelper'])
    register_Ns3DsrMainHelper_methods(root_module, root_module['ns3::DsrMainHelper'])
    register_Ns3EventGarbageCollector_methods(root_module, root_module['ns3::EventGarbageCollector'])
    register_Ns3EventId_methods(root_module, root_module['ns3::EventId'])
    register_Ns3Hasher_methods(root_module, root_module['ns3::Hasher'])
    register_Ns3Inet6SocketAddress_methods(root_module, root_module['ns3::Inet6SocketAddress'])
    register_Ns3InetSocketAddress_methods(root_module, root_module['ns3::InetSocketAddress'])
    register_Ns3IntToType__0_methods(root_module, root_module['ns3::IntToType< 0 >'])
    register_Ns3IntToType__1_methods(root_module, root_module['ns3::IntToType< 1 >'])
    register_Ns3IntToType__2_methods(root_module, root_module['ns3::IntToType< 2 >'])
    register_Ns3IntToType__3_methods(root_module, root_module['ns3::IntToType< 3 >'])
    register_Ns3IntToType__4_methods(root_module, root_module['ns3::IntToType< 4 >'])
    register_Ns3IntToType__5_methods(root_module, root_module['ns3::IntToType< 5 >'])
    register_Ns3IntToType__6_methods(root_module, root_module['ns3::IntToType< 6 >'])
    register_Ns3InterferenceHelper_methods(root_module, root_module['ns3::InterferenceHelper'])
    register_Ns3InterferenceHelperSnrPer_methods(root_module, root_module['ns3::InterferenceHelper::SnrPer'])
    register_Ns3Ipv4Address_methods(root_module, root_module['ns3::Ipv4Address'])
    register_Ns3Ipv4InterfaceAddress_methods(root_module, root_module['ns3::Ipv4InterfaceAddress'])
    register_Ns3Ipv4Mask_methods(root_module, root_module['ns3::Ipv4Mask'])
    register_Ns3Ipv6Address_methods(root_module, root_module['ns3::Ipv6Address'])
    register_Ns3Ipv6Prefix_methods(root_module, root_module['ns3::Ipv6Prefix'])
    register_Ns3Mac48Address_methods(root_module, root_module['ns3::Mac48Address'])
    register_Ns3NodeContainer_methods(root_module, root_module['ns3::NodeContainer'])
    register_Ns3NonCopyable_methods(root_module, root_module['ns3::NonCopyable'])
    register_Ns3ObjectBase_methods(root_module, root_module['ns3::ObjectBase'])
    register_Ns3ObjectDeleter_methods(root_module, root_module['ns3::ObjectDeleter'])
    register_Ns3ObjectFactory_methods(root_module, root_module['ns3::ObjectFactory'])
    register_Ns3PacketMetadata_methods(root_module, root_module['ns3::PacketMetadata'])
    register_Ns3PacketMetadataItem_methods(root_module, root_module['ns3::PacketMetadata::Item'])
    register_Ns3PacketMetadataItemIterator_methods(root_module, root_module['ns3::PacketMetadata::ItemIterator'])
    register_Ns3PacketTagIterator_methods(root_module, root_module['ns3::PacketTagIterator'])
    register_Ns3PacketTagIteratorItem_methods(root_module, root_module['ns3::PacketTagIterator::Item'])
    register_Ns3PacketTagList_methods(root_module, root_module['ns3::PacketTagList'])
    register_Ns3PacketTagListTagData_methods(root_module, root_module['ns3::PacketTagList::TagData'])
    register_Ns3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_methods(root_module, root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    register_Ns3Simulator_methods(root_module, root_module['ns3::Simulator'])
    register_Ns3SystemWallClockMs_methods(root_module, root_module['ns3::SystemWallClockMs'])
    register_Ns3Tag_methods(root_module, root_module['ns3::Tag'])
    register_Ns3TagBuffer_methods(root_module, root_module['ns3::TagBuffer'])
    register_Ns3TimeWithUnit_methods(root_module, root_module['ns3::TimeWithUnit'])
    register_Ns3Timer_methods(root_module, root_module['ns3::Timer'])
    register_Ns3TimerImpl_methods(root_module, root_module['ns3::TimerImpl'])
    register_Ns3TracedValue__Unsigned_int_methods(root_module, root_module['ns3::TracedValue< unsigned int >'])
    register_Ns3TypeId_methods(root_module, root_module['ns3::TypeId'])
    register_Ns3TypeIdAttributeInformation_methods(root_module, root_module['ns3::TypeId::AttributeInformation'])
    register_Ns3TypeIdTraceSourceInformation_methods(root_module, root_module['ns3::TypeId::TraceSourceInformation'])
    register_Ns3Vector2D_methods(root_module, root_module['ns3::Vector2D'])
    register_Ns3Vector3D_methods(root_module, root_module['ns3::Vector3D'])
    register_Ns3WifiMode_methods(root_module, root_module['ns3::WifiMode'])
    register_Ns3WifiModeFactory_methods(root_module, root_module['ns3::WifiModeFactory'])
    register_Ns3WifiPhyListener_methods(root_module, root_module['ns3::WifiPhyListener'])
    register_Ns3WifiRemoteStation_methods(root_module, root_module['ns3::WifiRemoteStation'])
    register_Ns3WifiRemoteStationInfo_methods(root_module, root_module['ns3::WifiRemoteStationInfo'])
    register_Ns3WifiRemoteStationState_methods(root_module, root_module['ns3::WifiRemoteStationState'])
    register_Ns3WifiTxVector_methods(root_module, root_module['ns3::WifiTxVector'])
    register_Ns3Empty_methods(root_module, root_module['ns3::empty'])
    register_Ns3Int64x64_t_methods(root_module, root_module['ns3::int64x64_t'])
    register_Ns3MpduInfo_methods(root_module, root_module['ns3::mpduInfo'])
    register_Ns3SignalNoiseDbm_methods(root_module, root_module['ns3::signalNoiseDbm'])
    register_Ns3Chunk_methods(root_module, root_module['ns3::Chunk'])
    register_Ns3Header_methods(root_module, root_module['ns3::Header'])
    register_Ns3Icmpv4DestinationUnreachable_methods(root_module, root_module['ns3::Icmpv4DestinationUnreachable'])
    register_Ns3Icmpv4Echo_methods(root_module, root_module['ns3::Icmpv4Echo'])
    register_Ns3Icmpv4Header_methods(root_module, root_module['ns3::Icmpv4Header'])
    register_Ns3Icmpv4TimeExceeded_methods(root_module, root_module['ns3::Icmpv4TimeExceeded'])
    register_Ns3Ipv4Header_methods(root_module, root_module['ns3::Ipv4Header'])
    register_Ns3Ipv6Header_methods(root_module, root_module['ns3::Ipv6Header'])
    register_Ns3Object_methods(root_module, root_module['ns3::Object'])
    register_Ns3ObjectAggregateIterator_methods(root_module, root_module['ns3::Object::AggregateIterator'])
    register_Ns3PacketFilter_methods(root_module, root_module['ns3::PacketFilter'])
    register_Ns3Queue_methods(root_module, root_module['ns3::Queue'])
    register_Ns3QueueDisc_methods(root_module, root_module['ns3::QueueDisc'])
    register_Ns3QueueDiscClass_methods(root_module, root_module['ns3::QueueDiscClass'])
    register_Ns3RandomVariableStream_methods(root_module, root_module['ns3::RandomVariableStream'])
    register_Ns3SequentialRandomVariable_methods(root_module, root_module['ns3::SequentialRandomVariable'])
    register_Ns3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    register_Ns3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    register_Ns3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    register_Ns3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >'])
    register_Ns3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >'])
    register_Ns3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >'])
    register_Ns3SimpleRefCount__Ns3InterferenceHelperEvent_Ns3Empty_Ns3DefaultDeleter__lt__ns3InterferenceHelperEvent__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter<ns3::InterferenceHelper::Event> >'])
    register_Ns3SimpleRefCount__Ns3Ipv4MulticastRoute_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4MulticastRoute__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >'])
    register_Ns3SimpleRefCount__Ns3Ipv4Route_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4Route__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >'])
    register_Ns3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >'])
    register_Ns3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >'])
    register_Ns3SimpleRefCount__Ns3OutputStreamWrapper_Ns3Empty_Ns3DefaultDeleter__lt__ns3OutputStreamWrapper__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >'])
    register_Ns3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >'])
    register_Ns3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >'])
    register_Ns3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    register_Ns3SimpleRefCount__Ns3WifiInformationElement_Ns3Empty_Ns3DefaultDeleter__lt__ns3WifiInformationElement__gt___methods(root_module, root_module['ns3::SimpleRefCount< ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> >'])
    register_Ns3Socket_methods(root_module, root_module['ns3::Socket'])
    register_Ns3SocketIpTosTag_methods(root_module, root_module['ns3::SocketIpTosTag'])
    register_Ns3SocketIpTtlTag_methods(root_module, root_module['ns3::SocketIpTtlTag'])
    register_Ns3SocketIpv6HopLimitTag_methods(root_module, root_module['ns3::SocketIpv6HopLimitTag'])
    register_Ns3SocketIpv6TclassTag_methods(root_module, root_module['ns3::SocketIpv6TclassTag'])
    register_Ns3SocketPriorityTag_methods(root_module, root_module['ns3::SocketPriorityTag'])
    register_Ns3SocketSetDontFragmentTag_methods(root_module, root_module['ns3::SocketSetDontFragmentTag'])
    register_Ns3Time_methods(root_module, root_module['ns3::Time'])
    register_Ns3TraceSourceAccessor_methods(root_module, root_module['ns3::TraceSourceAccessor'])
    register_Ns3TrafficControlLayer_methods(root_module, root_module['ns3::TrafficControlLayer'])
    register_Ns3Trailer_methods(root_module, root_module['ns3::Trailer'])
    register_Ns3TriangularRandomVariable_methods(root_module, root_module['ns3::TriangularRandomVariable'])
    register_Ns3UniformRandomVariable_methods(root_module, root_module['ns3::UniformRandomVariable'])
    register_Ns3WeibullRandomVariable_methods(root_module, root_module['ns3::WeibullRandomVariable'])
    register_Ns3WifiInformationElement_methods(root_module, root_module['ns3::WifiInformationElement'])
    register_Ns3WifiMac_methods(root_module, root_module['ns3::WifiMac'])
    register_Ns3WifiMacHeader_methods(root_module, root_module['ns3::WifiMacHeader'])
    register_Ns3WifiPhy_methods(root_module, root_module['ns3::WifiPhy'])
    register_Ns3WifiRemoteStationManager_methods(root_module, root_module['ns3::WifiRemoteStationManager'])
    register_Ns3ZetaRandomVariable_methods(root_module, root_module['ns3::ZetaRandomVariable'])
    register_Ns3ZipfRandomVariable_methods(root_module, root_module['ns3::ZipfRandomVariable'])
    register_Ns3ArpCache_methods(root_module, root_module['ns3::ArpCache'])
    register_Ns3ArpCacheEntry_methods(root_module, root_module['ns3::ArpCache::Entry'])
    register_Ns3AttributeAccessor_methods(root_module, root_module['ns3::AttributeAccessor'])
    register_Ns3AttributeChecker_methods(root_module, root_module['ns3::AttributeChecker'])
    register_Ns3AttributeValue_methods(root_module, root_module['ns3::AttributeValue'])
    register_Ns3BooleanChecker_methods(root_module, root_module['ns3::BooleanChecker'])
    register_Ns3BooleanValue_methods(root_module, root_module['ns3::BooleanValue'])
    register_Ns3CallbackChecker_methods(root_module, root_module['ns3::CallbackChecker'])
    register_Ns3CallbackImplBase_methods(root_module, root_module['ns3::CallbackImplBase'])
    register_Ns3CallbackValue_methods(root_module, root_module['ns3::CallbackValue'])
    register_Ns3Channel_methods(root_module, root_module['ns3::Channel'])
    register_Ns3ConstantRandomVariable_methods(root_module, root_module['ns3::ConstantRandomVariable'])
    register_Ns3DeterministicRandomVariable_methods(root_module, root_module['ns3::DeterministicRandomVariable'])
    register_Ns3DoubleValue_methods(root_module, root_module['ns3::DoubleValue'])
    register_Ns3EmpiricalRandomVariable_methods(root_module, root_module['ns3::EmpiricalRandomVariable'])
    register_Ns3EmptyAttributeAccessor_methods(root_module, root_module['ns3::EmptyAttributeAccessor'])
    register_Ns3EmptyAttributeChecker_methods(root_module, root_module['ns3::EmptyAttributeChecker'])
    register_Ns3EmptyAttributeValue_methods(root_module, root_module['ns3::EmptyAttributeValue'])
    register_Ns3EnumChecker_methods(root_module, root_module['ns3::EnumChecker'])
    register_Ns3EnumValue_methods(root_module, root_module['ns3::EnumValue'])
    register_Ns3ErlangRandomVariable_methods(root_module, root_module['ns3::ErlangRandomVariable'])
    register_Ns3ErrorRateModel_methods(root_module, root_module['ns3::ErrorRateModel'])
    register_Ns3EventImpl_methods(root_module, root_module['ns3::EventImpl'])
    register_Ns3ExponentialRandomVariable_methods(root_module, root_module['ns3::ExponentialRandomVariable'])
    register_Ns3GammaRandomVariable_methods(root_module, root_module['ns3::GammaRandomVariable'])
    register_Ns3HtCapabilities_methods(root_module, root_module['ns3::HtCapabilities'])
    register_Ns3HtCapabilitiesChecker_methods(root_module, root_module['ns3::HtCapabilitiesChecker'])
    register_Ns3HtCapabilitiesValue_methods(root_module, root_module['ns3::HtCapabilitiesValue'])
    register_Ns3IntegerValue_methods(root_module, root_module['ns3::IntegerValue'])
    register_Ns3IpL4Protocol_methods(root_module, root_module['ns3::IpL4Protocol'])
    register_Ns3Ipv4_methods(root_module, root_module['ns3::Ipv4'])
    register_Ns3Ipv4AddressChecker_methods(root_module, root_module['ns3::Ipv4AddressChecker'])
    register_Ns3Ipv4AddressValue_methods(root_module, root_module['ns3::Ipv4AddressValue'])
    register_Ns3Ipv4Interface_methods(root_module, root_module['ns3::Ipv4Interface'])
    register_Ns3Ipv4L3Protocol_methods(root_module, root_module['ns3::Ipv4L3Protocol'])
    register_Ns3Ipv4MaskChecker_methods(root_module, root_module['ns3::Ipv4MaskChecker'])
    register_Ns3Ipv4MaskValue_methods(root_module, root_module['ns3::Ipv4MaskValue'])
    register_Ns3Ipv4MulticastRoute_methods(root_module, root_module['ns3::Ipv4MulticastRoute'])
    register_Ns3Ipv4Route_methods(root_module, root_module['ns3::Ipv4Route'])
    register_Ns3Ipv4RoutingProtocol_methods(root_module, root_module['ns3::Ipv4RoutingProtocol'])
    register_Ns3Ipv6AddressChecker_methods(root_module, root_module['ns3::Ipv6AddressChecker'])
    register_Ns3Ipv6AddressValue_methods(root_module, root_module['ns3::Ipv6AddressValue'])
    register_Ns3Ipv6PrefixChecker_methods(root_module, root_module['ns3::Ipv6PrefixChecker'])
    register_Ns3Ipv6PrefixValue_methods(root_module, root_module['ns3::Ipv6PrefixValue'])
    register_Ns3LogNormalRandomVariable_methods(root_module, root_module['ns3::LogNormalRandomVariable'])
    register_Ns3Mac48AddressChecker_methods(root_module, root_module['ns3::Mac48AddressChecker'])
    register_Ns3Mac48AddressValue_methods(root_module, root_module['ns3::Mac48AddressValue'])
    register_Ns3MobilityModel_methods(root_module, root_module['ns3::MobilityModel'])
    register_Ns3NetDevice_methods(root_module, root_module['ns3::NetDevice'])
    register_Ns3NetDeviceQueue_methods(root_module, root_module['ns3::NetDeviceQueue'])
    register_Ns3NetDeviceQueueInterface_methods(root_module, root_module['ns3::NetDeviceQueueInterface'])
    register_Ns3NixVector_methods(root_module, root_module['ns3::NixVector'])
    register_Ns3Node_methods(root_module, root_module['ns3::Node'])
    register_Ns3NormalRandomVariable_methods(root_module, root_module['ns3::NormalRandomVariable'])
    register_Ns3ObjectFactoryChecker_methods(root_module, root_module['ns3::ObjectFactoryChecker'])
    register_Ns3ObjectFactoryValue_methods(root_module, root_module['ns3::ObjectFactoryValue'])
    register_Ns3OutputStreamWrapper_methods(root_module, root_module['ns3::OutputStreamWrapper'])
    register_Ns3Packet_methods(root_module, root_module['ns3::Packet'])
    register_Ns3ParetoRandomVariable_methods(root_module, root_module['ns3::ParetoRandomVariable'])
    register_Ns3QueueItem_methods(root_module, root_module['ns3::QueueItem'])
    register_Ns3Ssid_methods(root_module, root_module['ns3::Ssid'])
    register_Ns3SsidChecker_methods(root_module, root_module['ns3::SsidChecker'])
    register_Ns3SsidValue_methods(root_module, root_module['ns3::SsidValue'])
    register_Ns3TcpL4Protocol_methods(root_module, root_module['ns3::TcpL4Protocol'])
    register_Ns3TimeValue_methods(root_module, root_module['ns3::TimeValue'])
    register_Ns3TypeIdChecker_methods(root_module, root_module['ns3::TypeIdChecker'])
    register_Ns3TypeIdValue_methods(root_module, root_module['ns3::TypeIdValue'])
    register_Ns3UdpL4Protocol_methods(root_module, root_module['ns3::UdpL4Protocol'])
    register_Ns3UintegerValue_methods(root_module, root_module['ns3::UintegerValue'])
    register_Ns3Vector2DChecker_methods(root_module, root_module['ns3::Vector2DChecker'])
    register_Ns3Vector2DValue_methods(root_module, root_module['ns3::Vector2DValue'])
    register_Ns3Vector3DChecker_methods(root_module, root_module['ns3::Vector3DChecker'])
    register_Ns3Vector3DValue_methods(root_module, root_module['ns3::Vector3DValue'])
    register_Ns3VhtCapabilities_methods(root_module, root_module['ns3::VhtCapabilities'])
    register_Ns3VhtCapabilitiesChecker_methods(root_module, root_module['ns3::VhtCapabilitiesChecker'])
    register_Ns3VhtCapabilitiesValue_methods(root_module, root_module['ns3::VhtCapabilitiesValue'])
    register_Ns3WifiChannel_methods(root_module, root_module['ns3::WifiChannel'])
    register_Ns3WifiModeChecker_methods(root_module, root_module['ns3::WifiModeChecker'])
    register_Ns3WifiModeValue_methods(root_module, root_module['ns3::WifiModeValue'])
    register_Ns3AddressChecker_methods(root_module, root_module['ns3::AddressChecker'])
    register_Ns3AddressValue_methods(root_module, root_module['ns3::AddressValue'])
    register_Ns3Icmpv4L4Protocol_methods(root_module, root_module['ns3::Icmpv4L4Protocol'])
    register_Ns3QueueDiscItem_methods(root_module, root_module['ns3::QueueDiscItem'])
    register_Ns3HashImplementation_methods(root_module, root_module['ns3::Hash::Implementation'])
    register_Ns3HashFunctionFnv1a_methods(root_module, root_module['ns3::Hash::Function::Fnv1a'])
    register_Ns3HashFunctionHash32_methods(root_module, root_module['ns3::Hash::Function::Hash32'])
    register_Ns3HashFunctionHash64_methods(root_module, root_module['ns3::Hash::Function::Hash64'])
    register_Ns3HashFunctionMurmur3_methods(root_module, root_module['ns3::Hash::Function::Murmur3'])
    register_Ns3DsrBlackList_methods(root_module, root_module['ns3::dsr::BlackList'])
    register_Ns3DsrDsrErrorBuffEntry_methods(root_module, root_module['ns3::dsr::DsrErrorBuffEntry'])
    register_Ns3DsrDsrErrorBuffer_methods(root_module, root_module['ns3::dsr::DsrErrorBuffer'])
    register_Ns3DsrDsrFsHeader_methods(root_module, root_module['ns3::dsr::DsrFsHeader'])
    register_Ns3DsrDsrGraReply_methods(root_module, root_module['ns3::dsr::DsrGraReply'])
    register_Ns3DsrDsrLinkStab_methods(root_module, root_module['ns3::dsr::DsrLinkStab'])
    register_Ns3DsrDsrMaintainBuffEntry_methods(root_module, root_module['ns3::dsr::DsrMaintainBuffEntry'])
    register_Ns3DsrDsrMaintainBuffer_methods(root_module, root_module['ns3::dsr::DsrMaintainBuffer'])
    register_Ns3DsrDsrNetworkQueue_methods(root_module, root_module['ns3::dsr::DsrNetworkQueue'])
    register_Ns3DsrDsrNetworkQueueEntry_methods(root_module, root_module['ns3::dsr::DsrNetworkQueueEntry'])
    register_Ns3DsrDsrNodeStab_methods(root_module, root_module['ns3::dsr::DsrNodeStab'])
    register_Ns3DsrDsrOptionField_methods(root_module, root_module['ns3::dsr::DsrOptionField'])
    register_Ns3DsrDsrOptionHeader_methods(root_module, root_module['ns3::dsr::DsrOptionHeader'])
    register_Ns3DsrDsrOptionHeaderAlignment_methods(root_module, root_module['ns3::dsr::DsrOptionHeader::Alignment'])
    register_Ns3DsrDsrOptionPad1Header_methods(root_module, root_module['ns3::dsr::DsrOptionPad1Header'])
    register_Ns3DsrDsrOptionPadnHeader_methods(root_module, root_module['ns3::dsr::DsrOptionPadnHeader'])
    register_Ns3DsrDsrOptionRerrHeader_methods(root_module, root_module['ns3::dsr::DsrOptionRerrHeader'])
    register_Ns3DsrDsrOptionRerrUnreachHeader_methods(root_module, root_module['ns3::dsr::DsrOptionRerrUnreachHeader'])
    register_Ns3DsrDsrOptionRerrUnsupportHeader_methods(root_module, root_module['ns3::dsr::DsrOptionRerrUnsupportHeader'])
    register_Ns3DsrDsrOptionRrepHeader_methods(root_module, root_module['ns3::dsr::DsrOptionRrepHeader'])
    register_Ns3DsrDsrOptionRreqHeader_methods(root_module, root_module['ns3::dsr::DsrOptionRreqHeader'])
    register_Ns3DsrDsrOptionSRHeader_methods(root_module, root_module['ns3::dsr::DsrOptionSRHeader'])
    register_Ns3DsrDsrOptions_methods(root_module, root_module['ns3::dsr::DsrOptions'])
    register_Ns3DsrDsrPassiveBuffEntry_methods(root_module, root_module['ns3::dsr::DsrPassiveBuffEntry'])
    register_Ns3DsrDsrPassiveBuffer_methods(root_module, root_module['ns3::dsr::DsrPassiveBuffer'])
    register_Ns3DsrDsrReceivedRreqEntry_methods(root_module, root_module['ns3::dsr::DsrReceivedRreqEntry'])
    register_Ns3DsrDsrRouteCache_methods(root_module, root_module['ns3::dsr::DsrRouteCache'])
    register_Ns3DsrDsrRouteCacheNeighbor_methods(root_module, root_module['ns3::dsr::DsrRouteCache::Neighbor'])
    register_Ns3DsrDsrRouteCacheEntry_methods(root_module, root_module['ns3::dsr::DsrRouteCacheEntry'])
    register_Ns3DsrDsrRouting_methods(root_module, root_module['ns3::dsr::DsrRouting'])
    register_Ns3DsrDsrRoutingHeader_methods(root_module, root_module['ns3::dsr::DsrRoutingHeader'])
    register_Ns3DsrDsrRreqTable_methods(root_module, root_module['ns3::dsr::DsrRreqTable'])
    register_Ns3DsrDsrSendBuffEntry_methods(root_module, root_module['ns3::dsr::DsrSendBuffEntry'])
    register_Ns3DsrDsrSendBuffer_methods(root_module, root_module['ns3::dsr::DsrSendBuffer'])
    register_Ns3DsrGraReplyEntry_methods(root_module, root_module['ns3::dsr::GraReplyEntry'])
    register_Ns3DsrLink_methods(root_module, root_module['ns3::dsr::Link'])
    register_Ns3DsrLinkKey_methods(root_module, root_module['ns3::dsr::LinkKey'])
    register_Ns3DsrNetworkKey_methods(root_module, root_module['ns3::dsr::NetworkKey'])
    register_Ns3DsrPassiveKey_methods(root_module, root_module['ns3::dsr::PassiveKey'])
    register_Ns3DsrRreqTableEntry_methods(root_module, root_module['ns3::dsr::RreqTableEntry'])
    register_Ns3DsrDsrOptionAck_methods(root_module, root_module['ns3::dsr::DsrOptionAck'])
    register_Ns3DsrDsrOptionAckHeader_methods(root_module, root_module['ns3::dsr::DsrOptionAckHeader'])
    register_Ns3DsrDsrOptionAckReq_methods(root_module, root_module['ns3::dsr::DsrOptionAckReq'])
    register_Ns3DsrDsrOptionAckReqHeader_methods(root_module, root_module['ns3::dsr::DsrOptionAckReqHeader'])
    register_Ns3DsrDsrOptionPad1_methods(root_module, root_module['ns3::dsr::DsrOptionPad1'])
    register_Ns3DsrDsrOptionPadn_methods(root_module, root_module['ns3::dsr::DsrOptionPadn'])
    register_Ns3DsrDsrOptionRerr_methods(root_module, root_module['ns3::dsr::DsrOptionRerr'])
    register_Ns3DsrDsrOptionRrep_methods(root_module, root_module['ns3::dsr::DsrOptionRrep'])
    register_Ns3DsrDsrOptionRreq_methods(root_module, root_module['ns3::dsr::DsrOptionRreq'])
    register_Ns3DsrDsrOptionSR_methods(root_module, root_module['ns3::dsr::DsrOptionSR'])
    return

def register_Ns3Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## address.h (module 'network'): ns3::Address::Address() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::Address::Address(uint8_t type, uint8_t const * buffer, uint8_t len) [constructor]
    cls.add_constructor([param('uint8_t', 'type'), param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): ns3::Address::Address(ns3::Address const & address) [copy constructor]
    cls.add_constructor([param('ns3::Address const &', 'address')])
    ## address.h (module 'network'): bool ns3::Address::CheckCompatible(uint8_t type, uint8_t len) const [member function]
    cls.add_method('CheckCompatible', 
                   'bool', 
                   [param('uint8_t', 'type'), param('uint8_t', 'len')], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::CopyAllFrom(uint8_t const * buffer, uint8_t len) [member function]
    cls.add_method('CopyAllFrom', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): uint32_t ns3::Address::CopyAllTo(uint8_t * buffer, uint8_t len) const [member function]
    cls.add_method('CopyAllTo', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint8_t', 'len')], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::CopyFrom(uint8_t const * buffer, uint8_t len) [member function]
    cls.add_method('CopyFrom', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint8_t', 'len')])
    ## address.h (module 'network'): uint32_t ns3::Address::CopyTo(uint8_t * buffer) const [member function]
    cls.add_method('CopyTo', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer')], 
                   is_const=True)
    ## address.h (module 'network'): void ns3::Address::Deserialize(ns3::TagBuffer buffer) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'buffer')])
    ## address.h (module 'network'): uint8_t ns3::Address::GetLength() const [member function]
    cls.add_method('GetLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): uint32_t ns3::Address::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): bool ns3::Address::IsInvalid() const [member function]
    cls.add_method('IsInvalid', 
                   'bool', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): bool ns3::Address::IsMatchingType(uint8_t type) const [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('uint8_t', 'type')], 
                   is_const=True)
    ## address.h (module 'network'): static uint8_t ns3::Address::Register() [member function]
    cls.add_method('Register', 
                   'uint8_t', 
                   [], 
                   is_static=True)
    ## address.h (module 'network'): void ns3::Address::Serialize(ns3::TagBuffer buffer) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'buffer')], 
                   is_const=True)
    return

def register_Ns3AttributeConstructionList_methods(root_module, cls):
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::AttributeConstructionList(ns3::AttributeConstructionList const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeConstructionList const &', 'arg0')])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::AttributeConstructionList() [constructor]
    cls.add_constructor([])
    ## attribute-construction-list.h (module 'core'): void ns3::AttributeConstructionList::Add(std::string name, ns3::Ptr<ns3::AttributeChecker const> checker, ns3::Ptr<ns3::AttributeValue> value) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker'), param('ns3::Ptr< ns3::AttributeValue >', 'value')])
    ## attribute-construction-list.h (module 'core'): std::_List_const_iterator<ns3::AttributeConstructionList::Item> ns3::AttributeConstructionList::Begin() const [member function]
    cls.add_method('Begin', 
                   'std::_List_const_iterator< ns3::AttributeConstructionList::Item >', 
                   [], 
                   is_const=True)
    ## attribute-construction-list.h (module 'core'): std::_List_const_iterator<ns3::AttributeConstructionList::Item> ns3::AttributeConstructionList::End() const [member function]
    cls.add_method('End', 
                   'std::_List_const_iterator< ns3::AttributeConstructionList::Item >', 
                   [], 
                   is_const=True)
    ## attribute-construction-list.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeConstructionList::Find(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('Find', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True)
    return

def register_Ns3AttributeConstructionListItem_methods(root_module, cls):
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::Item() [constructor]
    cls.add_constructor([])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::Item(ns3::AttributeConstructionList::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeConstructionList::Item const &', 'arg0')])
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::checker [variable]
    cls.add_instance_attribute('checker', 'ns3::Ptr< ns3::AttributeChecker const >', is_const=False)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item::value [variable]
    cls.add_instance_attribute('value', 'ns3::Ptr< ns3::AttributeValue >', is_const=False)
    return

def register_Ns3Buffer_methods(root_module, cls):
    ## buffer.h (module 'network'): ns3::Buffer::Buffer() [constructor]
    cls.add_constructor([])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(uint32_t dataSize) [constructor]
    cls.add_constructor([param('uint32_t', 'dataSize')])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(uint32_t dataSize, bool initialize) [constructor]
    cls.add_constructor([param('uint32_t', 'dataSize'), param('bool', 'initialize')])
    ## buffer.h (module 'network'): ns3::Buffer::Buffer(ns3::Buffer const & o) [copy constructor]
    cls.add_constructor([param('ns3::Buffer const &', 'o')])
    ## buffer.h (module 'network'): void ns3::Buffer::AddAtEnd(uint32_t end) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::AddAtEnd(ns3::Buffer const & o) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::Buffer const &', 'o')])
    ## buffer.h (module 'network'): void ns3::Buffer::AddAtStart(uint32_t start) [member function]
    cls.add_method('AddAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator ns3::Buffer::Begin() const [member function]
    cls.add_method('Begin', 
                   'ns3::Buffer::Iterator', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::CopyData(std::ostream * os, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'void', 
                   [param('std::ostream *', 'os'), param('uint32_t', 'size')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::CopyData(uint8_t * buffer, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')], 
                   is_const=True)
    ## buffer.h (module 'network'): ns3::Buffer ns3::Buffer::CreateFragment(uint32_t start, uint32_t length) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::Buffer', 
                   [param('uint32_t', 'start'), param('uint32_t', 'length')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Deserialize(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator ns3::Buffer::End() const [member function]
    cls.add_method('End', 
                   'ns3::Buffer::Iterator', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint8_t const * ns3::Buffer::PeekData() const [member function]
    cls.add_method('PeekData', 
                   'uint8_t const *', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::RemoveAtEnd(uint32_t end) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::RemoveAtStart(uint32_t start) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3BufferIterator_methods(root_module, cls):
    ## buffer.h (module 'network'): ns3::Buffer::Iterator::Iterator(ns3::Buffer::Iterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Buffer::Iterator const &', 'arg0')])
    ## buffer.h (module 'network'): ns3::Buffer::Iterator::Iterator() [constructor]
    cls.add_constructor([])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::CalculateIpChecksum(uint16_t size) [member function]
    cls.add_method('CalculateIpChecksum', 
                   'uint16_t', 
                   [param('uint16_t', 'size')])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::CalculateIpChecksum(uint16_t size, uint32_t initialChecksum) [member function]
    cls.add_method('CalculateIpChecksum', 
                   'uint16_t', 
                   [param('uint16_t', 'size'), param('uint32_t', 'initialChecksum')])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetDistanceFrom(ns3::Buffer::Iterator const & o) const [member function]
    cls.add_method('GetDistanceFrom', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator const &', 'o')], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetRemainingSize() const [member function]
    cls.add_method('GetRemainingSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): bool ns3::Buffer::Iterator::IsEnd() const [member function]
    cls.add_method('IsEnd', 
                   'bool', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): bool ns3::Buffer::Iterator::IsStart() const [member function]
    cls.add_method('IsStart', 
                   'bool', 
                   [], 
                   is_const=True)
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Next() [member function]
    cls.add_method('Next', 
                   'void', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Next(uint32_t delta) [member function]
    cls.add_method('Next', 
                   'void', 
                   [param('uint32_t', 'delta')])
    ## buffer.h (module 'network'): uint8_t ns3::Buffer::Iterator::PeekU8() [member function]
    cls.add_method('PeekU8', 
                   'uint8_t', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Prev() [member function]
    cls.add_method('Prev', 
                   'void', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Prev(uint32_t delta) [member function]
    cls.add_method('Prev', 
                   'void', 
                   [param('uint32_t', 'delta')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Read(uint8_t * buffer, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Read(ns3::Buffer::Iterator start, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadLsbtohU16() [member function]
    cls.add_method('ReadLsbtohU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadLsbtohU32() [member function]
    cls.add_method('ReadLsbtohU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadLsbtohU64() [member function]
    cls.add_method('ReadLsbtohU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadNtohU16() [member function]
    cls.add_method('ReadNtohU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadNtohU32() [member function]
    cls.add_method('ReadNtohU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadNtohU64() [member function]
    cls.add_method('ReadNtohU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint16_t ns3::Buffer::Iterator::ReadU16() [member function]
    cls.add_method('ReadU16', 
                   'uint16_t', 
                   [])
    ## buffer.h (module 'network'): uint32_t ns3::Buffer::Iterator::ReadU32() [member function]
    cls.add_method('ReadU32', 
                   'uint32_t', 
                   [])
    ## buffer.h (module 'network'): uint64_t ns3::Buffer::Iterator::ReadU64() [member function]
    cls.add_method('ReadU64', 
                   'uint64_t', 
                   [])
    ## buffer.h (module 'network'): uint8_t ns3::Buffer::Iterator::ReadU8() [member function]
    cls.add_method('ReadU8', 
                   'uint8_t', 
                   [])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Write(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::Write(ns3::Buffer::Iterator start, ns3::Buffer::Iterator end) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start'), param('ns3::Buffer::Iterator', 'end')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU16(uint16_t data) [member function]
    cls.add_method('WriteHtolsbU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU32(uint32_t data) [member function]
    cls.add_method('WriteHtolsbU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtolsbU64(uint64_t data) [member function]
    cls.add_method('WriteHtolsbU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU16(uint16_t data) [member function]
    cls.add_method('WriteHtonU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU32(uint32_t data) [member function]
    cls.add_method('WriteHtonU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteHtonU64(uint64_t data) [member function]
    cls.add_method('WriteHtonU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU16(uint16_t data) [member function]
    cls.add_method('WriteU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU32(uint32_t data) [member function]
    cls.add_method('WriteU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU64(uint64_t data) [member function]
    cls.add_method('WriteU64', 
                   'void', 
                   [param('uint64_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU8(uint8_t data) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'data')])
    ## buffer.h (module 'network'): void ns3::Buffer::Iterator::WriteU8(uint8_t data, uint32_t len) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'data'), param('uint32_t', 'len')])
    return

def register_Ns3ByteTagIterator_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::ByteTagIterator::ByteTagIterator(ns3::ByteTagIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagIterator const &', 'arg0')])
    ## packet.h (module 'network'): bool ns3::ByteTagIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item ns3::ByteTagIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::ByteTagIterator::Item', 
                   [])
    return

def register_Ns3ByteTagIteratorItem_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item::Item(ns3::ByteTagIterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagIterator::Item const &', 'arg0')])
    ## packet.h (module 'network'): uint32_t ns3::ByteTagIterator::Item::GetEnd() const [member function]
    cls.add_method('GetEnd', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::ByteTagIterator::Item::GetStart() const [member function]
    cls.add_method('GetStart', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::ByteTagIterator::Item::GetTag(ns3::Tag & tag) const [member function]
    cls.add_method('GetTag', 
                   'void', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::TypeId ns3::ByteTagIterator::Item::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    return

def register_Ns3ByteTagList_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::ByteTagList() [constructor]
    cls.add_constructor([])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::ByteTagList(ns3::ByteTagList const & o) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList const &', 'o')])
    ## byte-tag-list.h (module 'network'): ns3::TagBuffer ns3::ByteTagList::Add(ns3::TypeId tid, uint32_t bufferSize, int32_t start, int32_t end) [member function]
    cls.add_method('Add', 
                   'ns3::TagBuffer', 
                   [param('ns3::TypeId', 'tid'), param('uint32_t', 'bufferSize'), param('int32_t', 'start'), param('int32_t', 'end')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::Add(ns3::ByteTagList const & o) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::ByteTagList const &', 'o')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::AddAtEnd(int32_t appendOffset) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('int32_t', 'appendOffset')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::AddAtStart(int32_t prependOffset) [member function]
    cls.add_method('AddAtStart', 
                   'void', 
                   [param('int32_t', 'prependOffset')])
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::Adjust(int32_t adjustment) [member function]
    cls.add_method('Adjust', 
                   'void', 
                   [param('int32_t', 'adjustment')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator ns3::ByteTagList::Begin(int32_t offsetStart, int32_t offsetEnd) const [member function]
    cls.add_method('Begin', 
                   'ns3::ByteTagList::Iterator', 
                   [param('int32_t', 'offsetStart'), param('int32_t', 'offsetEnd')], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): void ns3::ByteTagList::RemoveAll() [member function]
    cls.add_method('RemoveAll', 
                   'void', 
                   [])
    return

def register_Ns3ByteTagListIterator_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Iterator(ns3::ByteTagList::Iterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList::Iterator const &', 'arg0')])
    ## byte-tag-list.h (module 'network'): uint32_t ns3::ByteTagList::Iterator::GetOffsetStart() const [member function]
    cls.add_method('GetOffsetStart', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): bool ns3::ByteTagList::Iterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item ns3::ByteTagList::Iterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::ByteTagList::Iterator::Item', 
                   [])
    return

def register_Ns3ByteTagListIteratorItem_methods(root_module, cls):
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::Item(ns3::ByteTagList::Iterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ByteTagList::Iterator::Item const &', 'arg0')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::Item(ns3::TagBuffer buf) [constructor]
    cls.add_constructor([param('ns3::TagBuffer', 'buf')])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::buf [variable]
    cls.add_instance_attribute('buf', 'ns3::TagBuffer', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::end [variable]
    cls.add_instance_attribute('end', 'int32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::size [variable]
    cls.add_instance_attribute('size', 'uint32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::start [variable]
    cls.add_instance_attribute('start', 'int32_t', is_const=False)
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3CallbackBase_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase(ns3::CallbackBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackBase const &', 'arg0')])
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::Ptr<ns3::CallbackImplBase> ns3::CallbackBase::GetImpl() const [member function]
    cls.add_method('GetImpl', 
                   'ns3::Ptr< ns3::CallbackImplBase >', 
                   [], 
                   is_const=True)
    ## callback.h (module 'core'): ns3::CallbackBase::CallbackBase(ns3::Ptr<ns3::CallbackImplBase> impl) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::CallbackImplBase >', 'impl')], 
                        visibility='protected')
    return

def register_Ns3DsrHelper_methods(root_module, cls):
    ## dsr-helper.h (module 'dsr'): ns3::DsrHelper::DsrHelper() [constructor]
    cls.add_constructor([])
    ## dsr-helper.h (module 'dsr'): ns3::DsrHelper::DsrHelper(ns3::DsrHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DsrHelper const &', 'arg0')])
    ## dsr-helper.h (module 'dsr'): ns3::DsrHelper * ns3::DsrHelper::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::DsrHelper *', 
                   [], 
                   is_const=True)
    ## dsr-helper.h (module 'dsr'): ns3::Ptr<ns3::dsr::DsrRouting> ns3::DsrHelper::Create(ns3::Ptr<ns3::Node> node) const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::dsr::DsrRouting >', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_const=True)
    ## dsr-helper.h (module 'dsr'): void ns3::DsrHelper::Set(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    return

def register_Ns3DsrMainHelper_methods(root_module, cls):
    ## dsr-main-helper.h (module 'dsr'): ns3::DsrMainHelper::DsrMainHelper() [constructor]
    cls.add_constructor([])
    ## dsr-main-helper.h (module 'dsr'): ns3::DsrMainHelper::DsrMainHelper(ns3::DsrMainHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DsrMainHelper const &', 'arg0')])
    ## dsr-main-helper.h (module 'dsr'): void ns3::DsrMainHelper::Install(ns3::DsrHelper & dsrHelper, ns3::NodeContainer nodes) [member function]
    cls.add_method('Install', 
                   'void', 
                   [param('ns3::DsrHelper &', 'dsrHelper'), param('ns3::NodeContainer', 'nodes')])
    ## dsr-main-helper.h (module 'dsr'): void ns3::DsrMainHelper::SetDsrHelper(ns3::DsrHelper & dsrHelper) [member function]
    cls.add_method('SetDsrHelper', 
                   'void', 
                   [param('ns3::DsrHelper &', 'dsrHelper')])
    return

def register_Ns3EventGarbageCollector_methods(root_module, cls):
    ## event-garbage-collector.h (module 'core'): ns3::EventGarbageCollector::EventGarbageCollector(ns3::EventGarbageCollector const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventGarbageCollector const &', 'arg0')])
    ## event-garbage-collector.h (module 'core'): ns3::EventGarbageCollector::EventGarbageCollector() [constructor]
    cls.add_constructor([])
    ## event-garbage-collector.h (module 'core'): void ns3::EventGarbageCollector::Track(ns3::EventId event) [member function]
    cls.add_method('Track', 
                   'void', 
                   [param('ns3::EventId', 'event')])
    return

def register_Ns3EventId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('==')
    ## event-id.h (module 'core'): ns3::EventId::EventId(ns3::EventId const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventId const &', 'arg0')])
    ## event-id.h (module 'core'): ns3::EventId::EventId() [constructor]
    cls.add_constructor([])
    ## event-id.h (module 'core'): ns3::EventId::EventId(ns3::Ptr<ns3::EventImpl> const & impl, uint64_t ts, uint32_t context, uint32_t uid) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::EventImpl > const &', 'impl'), param('uint64_t', 'ts'), param('uint32_t', 'context'), param('uint32_t', 'uid')])
    ## event-id.h (module 'core'): void ns3::EventId::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-id.h (module 'core'): uint32_t ns3::EventId::GetContext() const [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): uint64_t ns3::EventId::GetTs() const [member function]
    cls.add_method('GetTs', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): uint32_t ns3::EventId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): bool ns3::EventId::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): bool ns3::EventId::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## event-id.h (module 'core'): ns3::EventImpl * ns3::EventId::PeekEventImpl() const [member function]
    cls.add_method('PeekEventImpl', 
                   'ns3::EventImpl *', 
                   [], 
                   is_const=True)
    return

def register_Ns3Hasher_methods(root_module, cls):
    ## hash.h (module 'core'): ns3::Hasher::Hasher(ns3::Hasher const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Hasher const &', 'arg0')])
    ## hash.h (module 'core'): ns3::Hasher::Hasher() [constructor]
    cls.add_constructor([])
    ## hash.h (module 'core'): ns3::Hasher::Hasher(ns3::Ptr<ns3::Hash::Implementation> hp) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Hash::Implementation >', 'hp')])
    ## hash.h (module 'core'): uint32_t ns3::Hasher::GetHash32(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')])
    ## hash.h (module 'core'): uint32_t ns3::Hasher::GetHash32(std::string const s) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('std::string const', 's')])
    ## hash.h (module 'core'): uint64_t ns3::Hasher::GetHash64(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash64', 
                   'uint64_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')])
    ## hash.h (module 'core'): uint64_t ns3::Hasher::GetHash64(std::string const s) [member function]
    cls.add_method('GetHash64', 
                   'uint64_t', 
                   [param('std::string const', 's')])
    ## hash.h (module 'core'): ns3::Hasher & ns3::Hasher::clear() [member function]
    cls.add_method('clear', 
                   'ns3::Hasher &', 
                   [])
    return

def register_Ns3Inet6SocketAddress_methods(root_module, cls):
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress::Inet6SocketAddress(ns3::Inet6SocketAddress const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Inet6SocketAddress const &', 'arg0')])
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress::Inet6SocketAddress(ns3::Ipv6Address ipv6, uint16_t port) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address', 'ipv6'), param('uint16_t', 'port')])
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress::Inet6SocketAddress(ns3::Ipv6Address ipv6) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address', 'ipv6')])
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress::Inet6SocketAddress(uint16_t port) [constructor]
    cls.add_constructor([param('uint16_t', 'port')])
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress::Inet6SocketAddress(char const * ipv6, uint16_t port) [constructor]
    cls.add_constructor([param('char const *', 'ipv6'), param('uint16_t', 'port')])
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress::Inet6SocketAddress(char const * ipv6) [constructor]
    cls.add_constructor([param('char const *', 'ipv6')])
    ## inet6-socket-address.h (module 'network'): static ns3::Inet6SocketAddress ns3::Inet6SocketAddress::ConvertFrom(ns3::Address const & addr) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Inet6SocketAddress', 
                   [param('ns3::Address const &', 'addr')], 
                   is_static=True)
    ## inet6-socket-address.h (module 'network'): ns3::Ipv6Address ns3::Inet6SocketAddress::GetIpv6() const [member function]
    cls.add_method('GetIpv6', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## inet6-socket-address.h (module 'network'): uint16_t ns3::Inet6SocketAddress::GetPort() const [member function]
    cls.add_method('GetPort', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## inet6-socket-address.h (module 'network'): static bool ns3::Inet6SocketAddress::IsMatchingType(ns3::Address const & addr) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'addr')], 
                   is_static=True)
    ## inet6-socket-address.h (module 'network'): void ns3::Inet6SocketAddress::SetIpv6(ns3::Ipv6Address ipv6) [member function]
    cls.add_method('SetIpv6', 
                   'void', 
                   [param('ns3::Ipv6Address', 'ipv6')])
    ## inet6-socket-address.h (module 'network'): void ns3::Inet6SocketAddress::SetPort(uint16_t port) [member function]
    cls.add_method('SetPort', 
                   'void', 
                   [param('uint16_t', 'port')])
    return

def register_Ns3InetSocketAddress_methods(root_module, cls):
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress::InetSocketAddress(ns3::InetSocketAddress const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::InetSocketAddress const &', 'arg0')])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress::InetSocketAddress(ns3::Ipv4Address ipv4, uint16_t port) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ipv4'), param('uint16_t', 'port')])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress::InetSocketAddress(ns3::Ipv4Address ipv4) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ipv4')])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress::InetSocketAddress(uint16_t port) [constructor]
    cls.add_constructor([param('uint16_t', 'port')])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress::InetSocketAddress(char const * ipv4, uint16_t port) [constructor]
    cls.add_constructor([param('char const *', 'ipv4'), param('uint16_t', 'port')])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress::InetSocketAddress(char const * ipv4) [constructor]
    cls.add_constructor([param('char const *', 'ipv4')])
    ## inet-socket-address.h (module 'network'): static ns3::InetSocketAddress ns3::InetSocketAddress::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::InetSocketAddress', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## inet-socket-address.h (module 'network'): ns3::Ipv4Address ns3::InetSocketAddress::GetIpv4() const [member function]
    cls.add_method('GetIpv4', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## inet-socket-address.h (module 'network'): uint16_t ns3::InetSocketAddress::GetPort() const [member function]
    cls.add_method('GetPort', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## inet-socket-address.h (module 'network'): uint8_t ns3::InetSocketAddress::GetTos() const [member function]
    cls.add_method('GetTos', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## inet-socket-address.h (module 'network'): static bool ns3::InetSocketAddress::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## inet-socket-address.h (module 'network'): void ns3::InetSocketAddress::SetIpv4(ns3::Ipv4Address address) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ipv4Address', 'address')])
    ## inet-socket-address.h (module 'network'): void ns3::InetSocketAddress::SetPort(uint16_t port) [member function]
    cls.add_method('SetPort', 
                   'void', 
                   [param('uint16_t', 'port')])
    ## inet-socket-address.h (module 'network'): void ns3::InetSocketAddress::SetTos(uint8_t tos) [member function]
    cls.add_method('SetTos', 
                   'void', 
                   [param('uint8_t', 'tos')])
    return

def register_Ns3IntToType__0_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<0>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<0>::IntToType(ns3::IntToType<0> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 0 > const &', 'arg0')])
    return

def register_Ns3IntToType__1_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<1>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<1>::IntToType(ns3::IntToType<1> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 1 > const &', 'arg0')])
    return

def register_Ns3IntToType__2_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<2>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<2>::IntToType(ns3::IntToType<2> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 2 > const &', 'arg0')])
    return

def register_Ns3IntToType__3_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<3>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<3>::IntToType(ns3::IntToType<3> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 3 > const &', 'arg0')])
    return

def register_Ns3IntToType__4_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<4>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<4>::IntToType(ns3::IntToType<4> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 4 > const &', 'arg0')])
    return

def register_Ns3IntToType__5_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<5>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<5>::IntToType(ns3::IntToType<5> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 5 > const &', 'arg0')])
    return

def register_Ns3IntToType__6_methods(root_module, cls):
    ## int-to-type.h (module 'core'): ns3::IntToType<6>::IntToType() [constructor]
    cls.add_constructor([])
    ## int-to-type.h (module 'core'): ns3::IntToType<6>::IntToType(ns3::IntToType<6> const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntToType< 6 > const &', 'arg0')])
    return

def register_Ns3InterferenceHelper_methods(root_module, cls):
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::InterferenceHelper(ns3::InterferenceHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::InterferenceHelper const &', 'arg0')])
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::InterferenceHelper() [constructor]
    cls.add_constructor([])
    ## interference-helper.h (module 'wifi'): ns3::Ptr<ns3::InterferenceHelper::Event> ns3::InterferenceHelper::Add(uint32_t size, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble, ns3::Time duration, double rxPower) [member function]
    cls.add_method('Add', 
                   'ns3::Ptr< ns3::InterferenceHelper::Event >', 
                   [param('uint32_t', 'size'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble'), param('ns3::Time', 'duration'), param('double', 'rxPower')])
    ## interference-helper.h (module 'wifi'): void ns3::InterferenceHelper::AddForeignSignal(ns3::Time duration, double rxPower) [member function]
    cls.add_method('AddForeignSignal', 
                   'void', 
                   [param('ns3::Time', 'duration'), param('double', 'rxPower')])
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer ns3::InterferenceHelper::CalculatePlcpHeaderSnrPer(ns3::Ptr<ns3::InterferenceHelper::Event> event) [member function]
    cls.add_method('CalculatePlcpHeaderSnrPer', 
                   'ns3::InterferenceHelper::SnrPer', 
                   [param('ns3::Ptr< ns3::InterferenceHelper::Event >', 'event')])
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer ns3::InterferenceHelper::CalculatePlcpPayloadSnrPer(ns3::Ptr<ns3::InterferenceHelper::Event> event) [member function]
    cls.add_method('CalculatePlcpPayloadSnrPer', 
                   'ns3::InterferenceHelper::SnrPer', 
                   [param('ns3::Ptr< ns3::InterferenceHelper::Event >', 'event')])
    ## interference-helper.h (module 'wifi'): void ns3::InterferenceHelper::EraseEvents() [member function]
    cls.add_method('EraseEvents', 
                   'void', 
                   [])
    ## interference-helper.h (module 'wifi'): ns3::Time ns3::InterferenceHelper::GetEnergyDuration(double energyW) [member function]
    cls.add_method('GetEnergyDuration', 
                   'ns3::Time', 
                   [param('double', 'energyW')])
    ## interference-helper.h (module 'wifi'): ns3::Ptr<ns3::ErrorRateModel> ns3::InterferenceHelper::GetErrorRateModel() const [member function]
    cls.add_method('GetErrorRateModel', 
                   'ns3::Ptr< ns3::ErrorRateModel >', 
                   [], 
                   is_const=True)
    ## interference-helper.h (module 'wifi'): double ns3::InterferenceHelper::GetNoiseFigure() const [member function]
    cls.add_method('GetNoiseFigure', 
                   'double', 
                   [], 
                   is_const=True)
    ## interference-helper.h (module 'wifi'): void ns3::InterferenceHelper::NotifyRxEnd() [member function]
    cls.add_method('NotifyRxEnd', 
                   'void', 
                   [])
    ## interference-helper.h (module 'wifi'): void ns3::InterferenceHelper::NotifyRxStart() [member function]
    cls.add_method('NotifyRxStart', 
                   'void', 
                   [])
    ## interference-helper.h (module 'wifi'): void ns3::InterferenceHelper::SetErrorRateModel(ns3::Ptr<ns3::ErrorRateModel> rate) [member function]
    cls.add_method('SetErrorRateModel', 
                   'void', 
                   [param('ns3::Ptr< ns3::ErrorRateModel >', 'rate')])
    ## interference-helper.h (module 'wifi'): void ns3::InterferenceHelper::SetNoiseFigure(double value) [member function]
    cls.add_method('SetNoiseFigure', 
                   'void', 
                   [param('double', 'value')])
    return

def register_Ns3InterferenceHelperSnrPer_methods(root_module, cls):
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer::SnrPer() [constructor]
    cls.add_constructor([])
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer::SnrPer(ns3::InterferenceHelper::SnrPer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::InterferenceHelper::SnrPer const &', 'arg0')])
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer::per [variable]
    cls.add_instance_attribute('per', 'double', is_const=False)
    ## interference-helper.h (module 'wifi'): ns3::InterferenceHelper::SnrPer::snr [variable]
    cls.add_instance_attribute('snr', 'double', is_const=False)
    return

def register_Ns3Ipv4Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(ns3::Ipv4Address const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Address const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(uint32_t address) [constructor]
    cls.add_constructor([param('uint32_t', 'address')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address::Ipv4Address(char const * address) [constructor]
    cls.add_constructor([param('char const *', 'address')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4Address::CombineMask(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('CombineMask', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::Deserialize(uint8_t const * buf) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Ipv4Address', 
                   [param('uint8_t const *', 'buf')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Address::Get() const [member function]
    cls.add_method('Get', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetAny() [member function]
    cls.add_method('GetAny', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetBroadcast() [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4Address::GetSubnetDirectedBroadcast(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('GetSubnetDirectedBroadcast', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Address ns3::Ipv4Address::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsAny() const [member function]
    cls.add_method('IsAny', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsEqual(ns3::Ipv4Address const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'other')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsLocalMulticast() const [member function]
    cls.add_method('IsLocalMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsLocalhost() const [member function]
    cls.add_method('IsLocalhost', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static bool ns3::Ipv4Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Address::IsSubnetDirectedBroadcast(ns3::Ipv4Mask const & mask) const [member function]
    cls.add_method('IsSubnetDirectedBroadcast', 
                   'bool', 
                   [param('ns3::Ipv4Mask const &', 'mask')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Serialize(uint8_t * buf) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Set(uint32_t address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint32_t', 'address')])
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Address::Set(char const * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('char const *', 'address')])
    return

def register_Ns3Ipv4InterfaceAddress_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::Ipv4InterfaceAddress() [constructor]
    cls.add_constructor([])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::Ipv4InterfaceAddress(ns3::Ipv4Address local, ns3::Ipv4Mask mask) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'local'), param('ns3::Ipv4Mask', 'mask')])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::Ipv4InterfaceAddress(ns3::Ipv4InterfaceAddress const & o) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4InterfaceAddress const &', 'o')])
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4InterfaceAddress::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4InterfaceAddress::GetLocal() const [member function]
    cls.add_method('GetLocal', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4Mask ns3::Ipv4InterfaceAddress::GetMask() const [member function]
    cls.add_method('GetMask', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e ns3::Ipv4InterfaceAddress::GetScope() const [member function]
    cls.add_method('GetScope', 
                   'ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): bool ns3::Ipv4InterfaceAddress::IsSecondary() const [member function]
    cls.add_method('IsSecondary', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetBroadcast(ns3::Ipv4Address broadcast) [member function]
    cls.add_method('SetBroadcast', 
                   'void', 
                   [param('ns3::Ipv4Address', 'broadcast')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetLocal(ns3::Ipv4Address local) [member function]
    cls.add_method('SetLocal', 
                   'void', 
                   [param('ns3::Ipv4Address', 'local')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetMask(ns3::Ipv4Mask mask) [member function]
    cls.add_method('SetMask', 
                   'void', 
                   [param('ns3::Ipv4Mask', 'mask')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetPrimary() [member function]
    cls.add_method('SetPrimary', 
                   'void', 
                   [])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetScope(ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e scope) [member function]
    cls.add_method('SetScope', 
                   'void', 
                   [param('ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 'scope')])
    ## ipv4-interface-address.h (module 'internet'): void ns3::Ipv4InterfaceAddress::SetSecondary() [member function]
    cls.add_method('SetSecondary', 
                   'void', 
                   [])
    return

def register_Ns3Ipv4Mask_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(ns3::Ipv4Mask const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Mask const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(uint32_t mask) [constructor]
    cls.add_constructor([param('uint32_t', 'mask')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask::Ipv4Mask(char const * mask) [constructor]
    cls.add_constructor([param('char const *', 'mask')])
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Mask::Get() const [member function]
    cls.add_method('Get', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): uint32_t ns3::Ipv4Mask::GetInverse() const [member function]
    cls.add_method('GetInverse', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): uint16_t ns3::Ipv4Mask::GetPrefixLength() const [member function]
    cls.add_method('GetPrefixLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): static ns3::Ipv4Mask ns3::Ipv4Mask::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_static=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Mask::IsEqual(ns3::Ipv4Mask other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv4Mask', 'other')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4Mask::IsMatch(ns3::Ipv4Address a, ns3::Ipv4Address b) const [member function]
    cls.add_method('IsMatch', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'a'), param('ns3::Ipv4Address', 'b')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Mask::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4Mask::Set(uint32_t mask) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint32_t', 'mask')])
    return

def register_Ns3Ipv6Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(char const * address) [constructor]
    cls.add_constructor([param('char const *', 'address')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(uint8_t * address) [constructor]
    cls.add_constructor([param('uint8_t *', 'address')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(ns3::Ipv6Address const & addr) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Address const &', 'addr')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address::Ipv6Address(ns3::Ipv6Address const * addr) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address const *', 'addr')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address ns3::Ipv6Address::CombinePrefix(ns3::Ipv6Prefix const & prefix) [member function]
    cls.add_method('CombinePrefix', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv6Prefix const &', 'prefix')])
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::Deserialize(uint8_t const * buf) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Ipv6Address', 
                   [param('uint8_t const *', 'buf')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllHostsMulticast() [member function]
    cls.add_method('GetAllHostsMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllNodesMulticast() [member function]
    cls.add_method('GetAllNodesMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAllRoutersMulticast() [member function]
    cls.add_method('GetAllRoutersMulticast', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetAny() [member function]
    cls.add_method('GetAny', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::GetBytes(uint8_t * buf) const [member function]
    cls.add_method('GetBytes', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv6Address::GetIpv4MappedAddress() const [member function]
    cls.add_method('GetIpv4MappedAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllHostsMulticast() const [member function]
    cls.add_method('IsAllHostsMulticast', 
                   'bool', 
                   [], 
                   deprecated=True, is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllNodesMulticast() const [member function]
    cls.add_method('IsAllNodesMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAllRoutersMulticast() const [member function]
    cls.add_method('IsAllRoutersMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsAny() const [member function]
    cls.add_method('IsAny', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsDocumentation() const [member function]
    cls.add_method('IsDocumentation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsEqual(ns3::Ipv6Address const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv6Address const &', 'other')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsIpv4MappedAddress() const [member function]
    cls.add_method('IsIpv4MappedAddress', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLinkLocal() const [member function]
    cls.add_method('IsLinkLocal', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLinkLocalMulticast() const [member function]
    cls.add_method('IsLinkLocalMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsLocalhost() const [member function]
    cls.add_method('IsLocalhost', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static bool ns3::Ipv6Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Address::IsSolicitedMulticast() const [member function]
    cls.add_method('IsSolicitedMulticast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredAddress(ns3::Mac16Address addr, ns3::Ipv6Address prefix) [member function]
    cls.add_method('MakeAutoconfiguredAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac16Address', 'addr'), param('ns3::Ipv6Address', 'prefix')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredAddress(ns3::Mac48Address addr, ns3::Ipv6Address prefix) [member function]
    cls.add_method('MakeAutoconfiguredAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac48Address', 'addr'), param('ns3::Ipv6Address', 'prefix')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredAddress(ns3::Mac64Address addr, ns3::Ipv6Address prefix) [member function]
    cls.add_method('MakeAutoconfiguredAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac64Address', 'addr'), param('ns3::Ipv6Address', 'prefix')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredLinkLocalAddress(ns3::Mac16Address mac) [member function]
    cls.add_method('MakeAutoconfiguredLinkLocalAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac16Address', 'mac')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredLinkLocalAddress(ns3::Mac48Address mac) [member function]
    cls.add_method('MakeAutoconfiguredLinkLocalAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac48Address', 'mac')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeAutoconfiguredLinkLocalAddress(ns3::Mac64Address mac) [member function]
    cls.add_method('MakeAutoconfiguredLinkLocalAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Mac64Address', 'mac')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeIpv4MappedAddress(ns3::Ipv4Address addr) [member function]
    cls.add_method('MakeIpv4MappedAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv4Address', 'addr')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Address ns3::Ipv6Address::MakeSolicitedAddress(ns3::Ipv6Address addr) [member function]
    cls.add_method('MakeSolicitedAddress', 
                   'ns3::Ipv6Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Serialize(uint8_t * buf) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Set(char const * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('char const *', 'address')])
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Address::Set(uint8_t * address) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint8_t *', 'address')])
    return

def register_Ns3Ipv6Prefix_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(uint8_t * prefix) [constructor]
    cls.add_constructor([param('uint8_t *', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(char const * prefix) [constructor]
    cls.add_constructor([param('char const *', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(uint8_t prefix) [constructor]
    cls.add_constructor([param('uint8_t', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(ns3::Ipv6Prefix const & prefix) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const &', 'prefix')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix::Ipv6Prefix(ns3::Ipv6Prefix const * prefix) [constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const *', 'prefix')])
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Prefix::GetBytes(uint8_t * buf) const [member function]
    cls.add_method('GetBytes', 
                   'void', 
                   [param('uint8_t *', 'buf')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetLoopback() [member function]
    cls.add_method('GetLoopback', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetOnes() [member function]
    cls.add_method('GetOnes', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): uint8_t ns3::Ipv6Prefix::GetPrefixLength() const [member function]
    cls.add_method('GetPrefixLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): static ns3::Ipv6Prefix ns3::Ipv6Prefix::GetZero() [member function]
    cls.add_method('GetZero', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_static=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Prefix::IsEqual(ns3::Ipv6Prefix const & other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ipv6Prefix const &', 'other')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6Prefix::IsMatch(ns3::Ipv6Address a, ns3::Ipv6Address b) const [member function]
    cls.add_method('IsMatch', 
                   'bool', 
                   [param('ns3::Ipv6Address', 'a'), param('ns3::Ipv6Address', 'b')], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6Prefix::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    return

def register_Ns3Mac48Address_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address(ns3::Mac48Address const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48Address const &', 'arg0')])
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48Address::Mac48Address(char const * str) [constructor]
    cls.add_constructor([param('char const *', 'str')])
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::Allocate() [member function]
    cls.add_method('Allocate', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::ConvertFrom(ns3::Address const & address) [member function]
    cls.add_method('ConvertFrom', 
                   'ns3::Mac48Address', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): void ns3::Mac48Address::CopyFrom(uint8_t const * buffer) [member function]
    cls.add_method('CopyFrom', 
                   'void', 
                   [param('uint8_t const *', 'buffer')])
    ## mac48-address.h (module 'network'): void ns3::Mac48Address::CopyTo(uint8_t * buffer) const [member function]
    cls.add_method('CopyTo', 
                   'void', 
                   [param('uint8_t *', 'buffer')], 
                   is_const=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetBroadcast() [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast(ns3::Ipv4Address address) [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv4Address', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast(ns3::Ipv6Address address) [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv6Address', 'address')], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticast6Prefix() [member function]
    cls.add_method('GetMulticast6Prefix', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): static ns3::Mac48Address ns3::Mac48Address::GetMulticastPrefix() [member function]
    cls.add_method('GetMulticastPrefix', 
                   'ns3::Mac48Address', 
                   [], 
                   is_static=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48Address::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48Address::IsGroup() const [member function]
    cls.add_method('IsGroup', 
                   'bool', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): static bool ns3::Mac48Address::IsMatchingType(ns3::Address const & address) [member function]
    cls.add_method('IsMatchingType', 
                   'bool', 
                   [param('ns3::Address const &', 'address')], 
                   is_static=True)
    return

def register_Ns3NodeContainer_methods(root_module, cls):
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'arg0')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer() [constructor]
    cls.add_constructor([])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::Ptr<ns3::Node> node) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Node >', 'node')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(std::string nodeName) [constructor]
    cls.add_constructor([param('std::string', 'nodeName')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b, ns3::NodeContainer const & c) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b'), param('ns3::NodeContainer const &', 'c')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b, ns3::NodeContainer const & c, ns3::NodeContainer const & d) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b'), param('ns3::NodeContainer const &', 'c'), param('ns3::NodeContainer const &', 'd')])
    ## node-container.h (module 'network'): ns3::NodeContainer::NodeContainer(ns3::NodeContainer const & a, ns3::NodeContainer const & b, ns3::NodeContainer const & c, ns3::NodeContainer const & d, ns3::NodeContainer const & e) [constructor]
    cls.add_constructor([param('ns3::NodeContainer const &', 'a'), param('ns3::NodeContainer const &', 'b'), param('ns3::NodeContainer const &', 'c'), param('ns3::NodeContainer const &', 'd'), param('ns3::NodeContainer const &', 'e')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Add(ns3::NodeContainer other) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::NodeContainer', 'other')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Add(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Add(std::string nodeName) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('std::string', 'nodeName')])
    ## node-container.h (module 'network'): __gnu_cxx::__normal_iterator<const ns3::Ptr<ns3::Node>*,std::vector<ns3::Ptr<ns3::Node>, std::allocator<ns3::Ptr<ns3::Node> > > > ns3::NodeContainer::Begin() const [member function]
    cls.add_method('Begin', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::Node > const, std::vector< ns3::Ptr< ns3::Node > > >', 
                   [], 
                   is_const=True)
    ## node-container.h (module 'network'): void ns3::NodeContainer::Create(uint32_t n) [member function]
    cls.add_method('Create', 
                   'void', 
                   [param('uint32_t', 'n')])
    ## node-container.h (module 'network'): void ns3::NodeContainer::Create(uint32_t n, uint32_t systemId) [member function]
    cls.add_method('Create', 
                   'void', 
                   [param('uint32_t', 'n'), param('uint32_t', 'systemId')])
    ## node-container.h (module 'network'): __gnu_cxx::__normal_iterator<const ns3::Ptr<ns3::Node>*,std::vector<ns3::Ptr<ns3::Node>, std::allocator<ns3::Ptr<ns3::Node> > > > ns3::NodeContainer::End() const [member function]
    cls.add_method('End', 
                   '__gnu_cxx::__normal_iterator< ns3::Ptr< ns3::Node > const, std::vector< ns3::Ptr< ns3::Node > > >', 
                   [], 
                   is_const=True)
    ## node-container.h (module 'network'): ns3::Ptr<ns3::Node> ns3::NodeContainer::Get(uint32_t i) const [member function]
    cls.add_method('Get', 
                   'ns3::Ptr< ns3::Node >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## node-container.h (module 'network'): static ns3::NodeContainer ns3::NodeContainer::GetGlobal() [member function]
    cls.add_method('GetGlobal', 
                   'ns3::NodeContainer', 
                   [], 
                   is_static=True)
    ## node-container.h (module 'network'): uint32_t ns3::NodeContainer::GetN() const [member function]
    cls.add_method('GetN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    return

def register_Ns3NonCopyable_methods(root_module, cls):
    ## non-copyable.h (module 'core'): ns3::NonCopyable::NonCopyable() [constructor]
    cls.add_constructor([], 
                        visibility='protected')
    return

def register_Ns3ObjectBase_methods(root_module, cls):
    ## object-base.h (module 'core'): ns3::ObjectBase::ObjectBase() [constructor]
    cls.add_constructor([])
    ## object-base.h (module 'core'): ns3::ObjectBase::ObjectBase(ns3::ObjectBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectBase const &', 'arg0')])
    ## object-base.h (module 'core'): void ns3::ObjectBase::GetAttribute(std::string name, ns3::AttributeValue & value) const [member function]
    cls.add_method('GetAttribute', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue &', 'value')], 
                   is_const=True)
    ## object-base.h (module 'core'): bool ns3::ObjectBase::GetAttributeFailSafe(std::string name, ns3::AttributeValue & value) const [member function]
    cls.add_method('GetAttributeFailSafe', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::AttributeValue &', 'value')], 
                   is_const=True)
    ## object-base.h (module 'core'): ns3::TypeId ns3::ObjectBase::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## object-base.h (module 'core'): static ns3::TypeId ns3::ObjectBase::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## object-base.h (module 'core'): void ns3::ObjectBase::SetAttribute(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('SetAttribute', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::SetAttributeFailSafe(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('SetAttributeFailSafe', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceConnect(std::string name, std::string context, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceConnect', 
                   'bool', 
                   [param('std::string', 'name'), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceConnectWithoutContext(std::string name, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceConnectWithoutContext', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceDisconnect(std::string name, std::string context, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceDisconnect', 
                   'bool', 
                   [param('std::string', 'name'), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): bool ns3::ObjectBase::TraceDisconnectWithoutContext(std::string name, ns3::CallbackBase const & cb) [member function]
    cls.add_method('TraceDisconnectWithoutContext', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::CallbackBase const &', 'cb')])
    ## object-base.h (module 'core'): void ns3::ObjectBase::ConstructSelf(ns3::AttributeConstructionList const & attributes) [member function]
    cls.add_method('ConstructSelf', 
                   'void', 
                   [param('ns3::AttributeConstructionList const &', 'attributes')], 
                   visibility='protected')
    ## object-base.h (module 'core'): void ns3::ObjectBase::NotifyConstructionCompleted() [member function]
    cls.add_method('NotifyConstructionCompleted', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectDeleter_methods(root_module, cls):
    ## object.h (module 'core'): ns3::ObjectDeleter::ObjectDeleter() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): ns3::ObjectDeleter::ObjectDeleter(ns3::ObjectDeleter const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectDeleter const &', 'arg0')])
    ## object.h (module 'core'): static void ns3::ObjectDeleter::Delete(ns3::Object * object) [member function]
    cls.add_method('Delete', 
                   'void', 
                   [param('ns3::Object *', 'object')], 
                   is_static=True)
    return

def register_Ns3ObjectFactory_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory(ns3::ObjectFactory const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactory const &', 'arg0')])
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactory::ObjectFactory(std::string typeId) [constructor]
    cls.add_constructor([param('std::string', 'typeId')])
    ## object-factory.h (module 'core'): ns3::Ptr<ns3::Object> ns3::ObjectFactory::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::Object >', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): ns3::TypeId ns3::ObjectFactory::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::Set(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(ns3::TypeId tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('ns3::TypeId', 'tid')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(char const * tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('char const *', 'tid')])
    ## object-factory.h (module 'core'): void ns3::ObjectFactory::SetTypeId(std::string tid) [member function]
    cls.add_method('SetTypeId', 
                   'void', 
                   [param('std::string', 'tid')])
    return

def register_Ns3PacketMetadata_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::PacketMetadata(uint64_t uid, uint32_t size) [constructor]
    cls.add_constructor([param('uint64_t', 'uid'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::PacketMetadata(ns3::PacketMetadata const & o) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata const &', 'o')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddAtEnd(ns3::PacketMetadata const & o) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::PacketMetadata const &', 'o')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddHeader(ns3::Header const & header, uint32_t size) [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddPaddingAtEnd(uint32_t end) [member function]
    cls.add_method('AddPaddingAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::AddTrailer(ns3::Trailer const & trailer, uint32_t size) [member function]
    cls.add_method('AddTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator ns3::PacketMetadata::BeginItem(ns3::Buffer buffer) const [member function]
    cls.add_method('BeginItem', 
                   'ns3::PacketMetadata::ItemIterator', 
                   [param('ns3::Buffer', 'buffer')], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata ns3::PacketMetadata::CreateFragment(uint32_t start, uint32_t end) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::PacketMetadata', 
                   [param('uint32_t', 'start'), param('uint32_t', 'end')], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::Deserialize(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): static void ns3::PacketMetadata::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet-metadata.h (module 'network'): static void ns3::PacketMetadata::EnableChecking() [member function]
    cls.add_method('EnableChecking', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): uint64_t ns3::PacketMetadata::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveAtEnd(uint32_t end) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'end')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveAtStart(uint32_t start) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'start')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveHeader(ns3::Header const & header, uint32_t size) [member function]
    cls.add_method('RemoveHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): void ns3::PacketMetadata::RemoveTrailer(ns3::Trailer const & trailer, uint32_t size) [member function]
    cls.add_method('RemoveTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer'), param('uint32_t', 'size')])
    ## packet-metadata.h (module 'network'): uint32_t ns3::PacketMetadata::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3PacketMetadataItem_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::Item() [constructor]
    cls.add_constructor([])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::Item(ns3::PacketMetadata::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata::Item const &', 'arg0')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::current [variable]
    cls.add_instance_attribute('current', 'ns3::Buffer::Iterator', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentSize [variable]
    cls.add_instance_attribute('currentSize', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentTrimedFromEnd [variable]
    cls.add_instance_attribute('currentTrimedFromEnd', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::currentTrimedFromStart [variable]
    cls.add_instance_attribute('currentTrimedFromStart', 'uint32_t', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::isFragment [variable]
    cls.add_instance_attribute('isFragment', 'bool', is_const=False)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3PacketMetadataItemIterator_methods(root_module, cls):
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator::ItemIterator(ns3::PacketMetadata::ItemIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketMetadata::ItemIterator const &', 'arg0')])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator::ItemIterator(ns3::PacketMetadata const * metadata, ns3::Buffer buffer) [constructor]
    cls.add_constructor([param('ns3::PacketMetadata const *', 'metadata'), param('ns3::Buffer', 'buffer')])
    ## packet-metadata.h (module 'network'): bool ns3::PacketMetadata::ItemIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item ns3::PacketMetadata::ItemIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::PacketMetadata::Item', 
                   [])
    return

def register_Ns3PacketTagIterator_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::PacketTagIterator::PacketTagIterator(ns3::PacketTagIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagIterator const &', 'arg0')])
    ## packet.h (module 'network'): bool ns3::PacketTagIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item ns3::PacketTagIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::PacketTagIterator::Item', 
                   [])
    return

def register_Ns3PacketTagIteratorItem_methods(root_module, cls):
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item::Item(ns3::PacketTagIterator::Item const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagIterator::Item const &', 'arg0')])
    ## packet.h (module 'network'): void ns3::PacketTagIterator::Item::GetTag(ns3::Tag & tag) const [member function]
    cls.add_method('GetTag', 
                   'void', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::TypeId ns3::PacketTagIterator::Item::GetTypeId() const [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    return

def register_Ns3PacketTagList_methods(root_module, cls):
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::PacketTagList() [constructor]
    cls.add_constructor([])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::PacketTagList(ns3::PacketTagList const & o) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagList const &', 'o')])
    ## packet-tag-list.h (module 'network'): void ns3::PacketTagList::Add(ns3::Tag const & tag) const [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData const * ns3::PacketTagList::Head() const [member function]
    cls.add_method('Head', 
                   'ns3::PacketTagList::TagData const *', 
                   [], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Peek(ns3::Tag & tag) const [member function]
    cls.add_method('Peek', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Remove(ns3::Tag & tag) [member function]
    cls.add_method('Remove', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet-tag-list.h (module 'network'): void ns3::PacketTagList::RemoveAll() [member function]
    cls.add_method('RemoveAll', 
                   'void', 
                   [])
    ## packet-tag-list.h (module 'network'): bool ns3::PacketTagList::Replace(ns3::Tag & tag) [member function]
    cls.add_method('Replace', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    return

def register_Ns3PacketTagListTagData_methods(root_module, cls):
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData() [constructor]
    cls.add_constructor([])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::TagData(ns3::PacketTagList::TagData const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketTagList::TagData const &', 'arg0')])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::count [variable]
    cls.add_instance_attribute('count', 'uint32_t', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::data [variable]
    cls.add_instance_attribute('data', 'uint8_t [ 21 ]', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::next [variable]
    cls.add_instance_attribute('next', 'ns3::PacketTagList::TagData *', is_const=False)
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData::tid [variable]
    cls.add_instance_attribute('tid', 'ns3::TypeId', is_const=False)
    return

def register_Ns3SimpleRefCount__Ns3Object_Ns3ObjectBase_Ns3ObjectDeleter_methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::SimpleRefCount(ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter>::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3Simulator_methods(root_module, cls):
    ## simulator.h (module 'core'): ns3::Simulator::Simulator(ns3::Simulator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Simulator const &', 'arg0')])
    ## simulator.h (module 'core'): static void ns3::Simulator::Cancel(ns3::EventId const & id) [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Destroy() [member function]
    cls.add_method('Destroy', 
                   'void', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static uint32_t ns3::Simulator::GetContext() [member function]
    cls.add_method('GetContext', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Time ns3::Simulator::GetDelayLeft(ns3::EventId const & id) [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Ptr<ns3::SimulatorImpl> ns3::Simulator::GetImplementation() [member function]
    cls.add_method('GetImplementation', 
                   'ns3::Ptr< ns3::SimulatorImpl >', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Time ns3::Simulator::GetMaximumSimulationTime() [member function]
    cls.add_method('GetMaximumSimulationTime', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static uint32_t ns3::Simulator::GetSystemId() [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static bool ns3::Simulator::IsExpired(ns3::EventId const & id) [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static bool ns3::Simulator::IsFinished() [member function]
    cls.add_method('IsFinished', 
                   'bool', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static ns3::Time ns3::Simulator::Now() [member function]
    cls.add_method('Now', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Remove(ns3::EventId const & id) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::EventId const &', 'id')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::SetImplementation(ns3::Ptr<ns3::SimulatorImpl> impl) [member function]
    cls.add_method('SetImplementation', 
                   'void', 
                   [param('ns3::Ptr< ns3::SimulatorImpl >', 'impl')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::SetScheduler(ns3::ObjectFactory schedulerFactory) [member function]
    cls.add_method('SetScheduler', 
                   'void', 
                   [param('ns3::ObjectFactory', 'schedulerFactory')], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_static=True)
    ## simulator.h (module 'core'): static void ns3::Simulator::Stop(ns3::Time const & delay) [member function]
    cls.add_method('Stop', 
                   'void', 
                   [param('ns3::Time const &', 'delay')], 
                   is_static=True)
    return

def register_Ns3SystemWallClockMs_methods(root_module, cls):
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs::SystemWallClockMs(ns3::SystemWallClockMs const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SystemWallClockMs const &', 'arg0')])
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs::SystemWallClockMs() [constructor]
    cls.add_constructor([])
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::End() [member function]
    cls.add_method('End', 
                   'int64_t', 
                   [])
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::GetElapsedReal() const [member function]
    cls.add_method('GetElapsedReal', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::GetElapsedSystem() const [member function]
    cls.add_method('GetElapsedSystem', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## system-wall-clock-ms.h (module 'core'): int64_t ns3::SystemWallClockMs::GetElapsedUser() const [member function]
    cls.add_method('GetElapsedUser', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## system-wall-clock-ms.h (module 'core'): void ns3::SystemWallClockMs::Start() [member function]
    cls.add_method('Start', 
                   'void', 
                   [])
    return

def register_Ns3Tag_methods(root_module, cls):
    ## tag.h (module 'network'): ns3::Tag::Tag() [constructor]
    cls.add_constructor([])
    ## tag.h (module 'network'): ns3::Tag::Tag(ns3::Tag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Tag const &', 'arg0')])
    ## tag.h (module 'network'): void ns3::Tag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_pure_virtual=True, is_virtual=True)
    ## tag.h (module 'network'): uint32_t ns3::Tag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## tag.h (module 'network'): static ns3::TypeId ns3::Tag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## tag.h (module 'network'): void ns3::Tag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## tag.h (module 'network'): void ns3::Tag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3TagBuffer_methods(root_module, cls):
    ## tag-buffer.h (module 'network'): ns3::TagBuffer::TagBuffer(ns3::TagBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TagBuffer const &', 'arg0')])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer::TagBuffer(uint8_t * start, uint8_t * end) [constructor]
    cls.add_constructor([param('uint8_t *', 'start'), param('uint8_t *', 'end')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::CopyFrom(ns3::TagBuffer o) [member function]
    cls.add_method('CopyFrom', 
                   'void', 
                   [param('ns3::TagBuffer', 'o')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::Read(uint8_t * buffer, uint32_t size) [member function]
    cls.add_method('Read', 
                   'void', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')])
    ## tag-buffer.h (module 'network'): double ns3::TagBuffer::ReadDouble() [member function]
    cls.add_method('ReadDouble', 
                   'double', 
                   [])
    ## tag-buffer.h (module 'network'): uint16_t ns3::TagBuffer::ReadU16() [member function]
    cls.add_method('ReadU16', 
                   'uint16_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint32_t ns3::TagBuffer::ReadU32() [member function]
    cls.add_method('ReadU32', 
                   'uint32_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint64_t ns3::TagBuffer::ReadU64() [member function]
    cls.add_method('ReadU64', 
                   'uint64_t', 
                   [])
    ## tag-buffer.h (module 'network'): uint8_t ns3::TagBuffer::ReadU8() [member function]
    cls.add_method('ReadU8', 
                   'uint8_t', 
                   [])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::TrimAtEnd(uint32_t trim) [member function]
    cls.add_method('TrimAtEnd', 
                   'void', 
                   [param('uint32_t', 'trim')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::Write(uint8_t const * buffer, uint32_t size) [member function]
    cls.add_method('Write', 
                   'void', 
                   [param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteDouble(double v) [member function]
    cls.add_method('WriteDouble', 
                   'void', 
                   [param('double', 'v')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU16(uint16_t data) [member function]
    cls.add_method('WriteU16', 
                   'void', 
                   [param('uint16_t', 'data')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU32(uint32_t data) [member function]
    cls.add_method('WriteU32', 
                   'void', 
                   [param('uint32_t', 'data')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU64(uint64_t v) [member function]
    cls.add_method('WriteU64', 
                   'void', 
                   [param('uint64_t', 'v')])
    ## tag-buffer.h (module 'network'): void ns3::TagBuffer::WriteU8(uint8_t v) [member function]
    cls.add_method('WriteU8', 
                   'void', 
                   [param('uint8_t', 'v')])
    return

def register_Ns3TimeWithUnit_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## nstime.h (module 'core'): ns3::TimeWithUnit::TimeWithUnit(ns3::TimeWithUnit const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeWithUnit const &', 'arg0')])
    ## nstime.h (module 'core'): ns3::TimeWithUnit::TimeWithUnit(ns3::Time const time, ns3::Time::Unit const unit) [constructor]
    cls.add_constructor([param('ns3::Time const', 'time'), param('ns3::Time::Unit const', 'unit')])
    return

def register_Ns3Timer_methods(root_module, cls):
    ## timer.h (module 'core'): ns3::Timer::Timer(ns3::Timer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Timer const &', 'arg0')])
    ## timer.h (module 'core'): ns3::Timer::Timer() [constructor]
    cls.add_constructor([])
    ## timer.h (module 'core'): ns3::Timer::Timer(ns3::Timer::DestroyPolicy destroyPolicy) [constructor]
    cls.add_constructor([param('ns3::Timer::DestroyPolicy', 'destroyPolicy')])
    ## timer.h (module 'core'): void ns3::Timer::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## timer.h (module 'core'): ns3::Time ns3::Timer::GetDelay() const [member function]
    cls.add_method('GetDelay', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): ns3::Time ns3::Timer::GetDelayLeft() const [member function]
    cls.add_method('GetDelayLeft', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): ns3::Timer::State ns3::Timer::GetState() const [member function]
    cls.add_method('GetState', 
                   'ns3::Timer::State', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): bool ns3::Timer::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): bool ns3::Timer::IsRunning() const [member function]
    cls.add_method('IsRunning', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): bool ns3::Timer::IsSuspended() const [member function]
    cls.add_method('IsSuspended', 
                   'bool', 
                   [], 
                   is_const=True)
    ## timer.h (module 'core'): void ns3::Timer::Remove() [member function]
    cls.add_method('Remove', 
                   'void', 
                   [])
    ## timer.h (module 'core'): void ns3::Timer::Resume() [member function]
    cls.add_method('Resume', 
                   'void', 
                   [])
    ## timer.h (module 'core'): void ns3::Timer::Schedule() [member function]
    cls.add_method('Schedule', 
                   'void', 
                   [])
    ## timer.h (module 'core'): void ns3::Timer::Schedule(ns3::Time delay) [member function]
    cls.add_method('Schedule', 
                   'void', 
                   [param('ns3::Time', 'delay')])
    ## timer.h (module 'core'): void ns3::Timer::SetDelay(ns3::Time const & delay) [member function]
    cls.add_method('SetDelay', 
                   'void', 
                   [param('ns3::Time const &', 'delay')])
    ## timer.h (module 'core'): void ns3::Timer::Suspend() [member function]
    cls.add_method('Suspend', 
                   'void', 
                   [])
    return

def register_Ns3TimerImpl_methods(root_module, cls):
    ## timer-impl.h (module 'core'): ns3::TimerImpl::TimerImpl() [constructor]
    cls.add_constructor([])
    ## timer-impl.h (module 'core'): ns3::TimerImpl::TimerImpl(ns3::TimerImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimerImpl const &', 'arg0')])
    ## timer-impl.h (module 'core'): void ns3::TimerImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## timer-impl.h (module 'core'): ns3::EventId ns3::TimerImpl::Schedule(ns3::Time const & delay) [member function]
    cls.add_method('Schedule', 
                   'ns3::EventId', 
                   [param('ns3::Time const &', 'delay')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3TracedValue__Unsigned_int_methods(root_module, cls):
    ## traced-value.h (module 'core'): ns3::TracedValue<unsigned int>::TracedValue() [constructor]
    cls.add_constructor([])
    ## traced-value.h (module 'core'): ns3::TracedValue<unsigned int>::TracedValue(ns3::TracedValue<unsigned int> const & o) [copy constructor]
    cls.add_constructor([param('ns3::TracedValue< unsigned int > const &', 'o')])
    ## traced-value.h (module 'core'): ns3::TracedValue<unsigned int>::TracedValue(unsigned int const & v) [constructor]
    cls.add_constructor([param('unsigned int const &', 'v')])
    ## traced-value.h (module 'core'): void ns3::TracedValue<unsigned int>::Connect(ns3::CallbackBase const & cb, std::basic_string<char,std::char_traits<char>,std::allocator<char> > path) [member function]
    cls.add_method('Connect', 
                   'void', 
                   [param('ns3::CallbackBase const &', 'cb'), param('std::string', 'path')])
    ## traced-value.h (module 'core'): void ns3::TracedValue<unsigned int>::ConnectWithoutContext(ns3::CallbackBase const & cb) [member function]
    cls.add_method('ConnectWithoutContext', 
                   'void', 
                   [param('ns3::CallbackBase const &', 'cb')])
    ## traced-value.h (module 'core'): void ns3::TracedValue<unsigned int>::Disconnect(ns3::CallbackBase const & cb, std::basic_string<char,std::char_traits<char>,std::allocator<char> > path) [member function]
    cls.add_method('Disconnect', 
                   'void', 
                   [param('ns3::CallbackBase const &', 'cb'), param('std::string', 'path')])
    ## traced-value.h (module 'core'): void ns3::TracedValue<unsigned int>::DisconnectWithoutContext(ns3::CallbackBase const & cb) [member function]
    cls.add_method('DisconnectWithoutContext', 
                   'void', 
                   [param('ns3::CallbackBase const &', 'cb')])
    ## traced-value.h (module 'core'): unsigned int ns3::TracedValue<unsigned int>::Get() const [member function]
    cls.add_method('Get', 
                   'unsigned int', 
                   [], 
                   is_const=True)
    ## traced-value.h (module 'core'): void ns3::TracedValue<unsigned int>::Set(unsigned int const & v) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('unsigned int const &', 'v')])
    return

def register_Ns3TypeId_methods(root_module, cls):
    cls.add_binary_comparison_operator('!=')
    cls.add_binary_comparison_operator('<')
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## type-id.h (module 'core'): ns3::TypeId::TypeId(char const * name) [constructor]
    cls.add_constructor([param('char const *', 'name')])
    ## type-id.h (module 'core'): ns3::TypeId::TypeId() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::TypeId(ns3::TypeId const & o) [copy constructor]
    cls.add_constructor([param('ns3::TypeId const &', 'o')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddAttribute(std::string name, std::string help, ns3::AttributeValue const & initialValue, ns3::Ptr<ns3::AttributeAccessor const> accessor, ns3::Ptr<ns3::AttributeChecker const> checker, ns3::TypeId::SupportLevel supportLevel=::ns3::TypeId::SUPPORTED, std::string const & supportMsg="") [member function]
    cls.add_method('AddAttribute', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::AttributeValue const &', 'initialValue'), param('ns3::Ptr< ns3::AttributeAccessor const >', 'accessor'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker'), param('ns3::TypeId::SupportLevel', 'supportLevel', default_value='::ns3::TypeId::SUPPORTED'), param('std::string const &', 'supportMsg', default_value='""')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddAttribute(std::string name, std::string help, uint32_t flags, ns3::AttributeValue const & initialValue, ns3::Ptr<ns3::AttributeAccessor const> accessor, ns3::Ptr<ns3::AttributeChecker const> checker, ns3::TypeId::SupportLevel supportLevel=::ns3::TypeId::SUPPORTED, std::string const & supportMsg="") [member function]
    cls.add_method('AddAttribute', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('uint32_t', 'flags'), param('ns3::AttributeValue const &', 'initialValue'), param('ns3::Ptr< ns3::AttributeAccessor const >', 'accessor'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker'), param('ns3::TypeId::SupportLevel', 'supportLevel', default_value='::ns3::TypeId::SUPPORTED'), param('std::string const &', 'supportMsg', default_value='""')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddTraceSource(std::string name, std::string help, ns3::Ptr<ns3::TraceSourceAccessor const> accessor) [member function]
    cls.add_method('AddTraceSource', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::Ptr< ns3::TraceSourceAccessor const >', 'accessor')], 
                   deprecated=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::AddTraceSource(std::string name, std::string help, ns3::Ptr<ns3::TraceSourceAccessor const> accessor, std::string callback, ns3::TypeId::SupportLevel supportLevel=::ns3::TypeId::SUPPORTED, std::string const & supportMsg="") [member function]
    cls.add_method('AddTraceSource', 
                   'ns3::TypeId', 
                   [param('std::string', 'name'), param('std::string', 'help'), param('ns3::Ptr< ns3::TraceSourceAccessor const >', 'accessor'), param('std::string', 'callback'), param('ns3::TypeId::SupportLevel', 'supportLevel', default_value='::ns3::TypeId::SUPPORTED'), param('std::string const &', 'supportMsg', default_value='""')])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation ns3::TypeId::GetAttribute(uint32_t i) const [member function]
    cls.add_method('GetAttribute', 
                   'ns3::TypeId::AttributeInformation', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetAttributeFullName(uint32_t i) const [member function]
    cls.add_method('GetAttributeFullName', 
                   'std::string', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetAttributeN() const [member function]
    cls.add_method('GetAttributeN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::Callback<ns3::ObjectBase*,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ns3::TypeId::GetConstructor() const [member function]
    cls.add_method('GetConstructor', 
                   'ns3::Callback< ns3::ObjectBase *, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetGroupName() const [member function]
    cls.add_method('GetGroupName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetHash() const [member function]
    cls.add_method('GetHash', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeId::GetName() const [member function]
    cls.add_method('GetName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::GetParent() const [member function]
    cls.add_method('GetParent', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::GetRegistered(uint32_t i) [member function]
    cls.add_method('GetRegistered', 
                   'ns3::TypeId', 
                   [param('uint32_t', 'i')], 
                   is_static=True)
    ## type-id.h (module 'core'): static uint32_t ns3::TypeId::GetRegisteredN() [member function]
    cls.add_method('GetRegisteredN', 
                   'uint32_t', 
                   [], 
                   is_static=True)
    ## type-id.h (module 'core'): std::size_t ns3::TypeId::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'std::size_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation ns3::TypeId::GetTraceSource(uint32_t i) const [member function]
    cls.add_method('GetTraceSource', 
                   'ns3::TypeId::TraceSourceInformation', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## type-id.h (module 'core'): uint32_t ns3::TypeId::GetTraceSourceN() const [member function]
    cls.add_method('GetTraceSourceN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): uint16_t ns3::TypeId::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::HasConstructor() const [member function]
    cls.add_method('HasConstructor', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::HasParent() const [member function]
    cls.add_method('HasParent', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::HideFromDocumentation() [member function]
    cls.add_method('HideFromDocumentation', 
                   'ns3::TypeId', 
                   [])
    ## type-id.h (module 'core'): bool ns3::TypeId::IsChildOf(ns3::TypeId other) const [member function]
    cls.add_method('IsChildOf', 
                   'bool', 
                   [param('ns3::TypeId', 'other')], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::LookupAttributeByName(std::string name, ns3::TypeId::AttributeInformation * info) const [member function]
    cls.add_method('LookupAttributeByName', 
                   'bool', 
                   [param('std::string', 'name'), param('ns3::TypeId::AttributeInformation *', 'info', transfer_ownership=False)], 
                   is_const=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::LookupByHash(uint32_t hash) [member function]
    cls.add_method('LookupByHash', 
                   'ns3::TypeId', 
                   [param('uint32_t', 'hash')], 
                   is_static=True)
    ## type-id.h (module 'core'): static bool ns3::TypeId::LookupByHashFailSafe(uint32_t hash, ns3::TypeId * tid) [member function]
    cls.add_method('LookupByHashFailSafe', 
                   'bool', 
                   [param('uint32_t', 'hash'), param('ns3::TypeId *', 'tid')], 
                   is_static=True)
    ## type-id.h (module 'core'): static ns3::TypeId ns3::TypeId::LookupByName(std::string name) [member function]
    cls.add_method('LookupByName', 
                   'ns3::TypeId', 
                   [param('std::string', 'name')], 
                   is_static=True)
    ## type-id.h (module 'core'): ns3::Ptr<ns3::TraceSourceAccessor const> ns3::TypeId::LookupTraceSourceByName(std::string name) const [member function]
    cls.add_method('LookupTraceSourceByName', 
                   'ns3::Ptr< ns3::TraceSourceAccessor const >', 
                   [param('std::string', 'name')], 
                   is_const=True)
    ## type-id.h (module 'core'): ns3::Ptr<ns3::TraceSourceAccessor const> ns3::TypeId::LookupTraceSourceByName(std::string name, ns3::TypeId::TraceSourceInformation * info) const [member function]
    cls.add_method('LookupTraceSourceByName', 
                   'ns3::Ptr< ns3::TraceSourceAccessor const >', 
                   [param('std::string', 'name'), param('ns3::TypeId::TraceSourceInformation *', 'info')], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::MustHideFromDocumentation() const [member function]
    cls.add_method('MustHideFromDocumentation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): bool ns3::TypeId::SetAttributeInitialValue(uint32_t i, ns3::Ptr<ns3::AttributeValue const> initialValue) [member function]
    cls.add_method('SetAttributeInitialValue', 
                   'bool', 
                   [param('uint32_t', 'i'), param('ns3::Ptr< ns3::AttributeValue const >', 'initialValue')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetGroupName(std::string groupName) [member function]
    cls.add_method('SetGroupName', 
                   'ns3::TypeId', 
                   [param('std::string', 'groupName')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetParent(ns3::TypeId tid) [member function]
    cls.add_method('SetParent', 
                   'ns3::TypeId', 
                   [param('ns3::TypeId', 'tid')])
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeId::SetSize(std::size_t size) [member function]
    cls.add_method('SetSize', 
                   'ns3::TypeId', 
                   [param('std::size_t', 'size')])
    ## type-id.h (module 'core'): void ns3::TypeId::SetUid(uint16_t uid) [member function]
    cls.add_method('SetUid', 
                   'void', 
                   [param('uint16_t', 'uid')])
    return

def register_Ns3TypeIdAttributeInformation_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::AttributeInformation() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::AttributeInformation(ns3::TypeId::AttributeInformation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeId::AttributeInformation const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::accessor [variable]
    cls.add_instance_attribute('accessor', 'ns3::Ptr< ns3::AttributeAccessor const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::checker [variable]
    cls.add_instance_attribute('checker', 'ns3::Ptr< ns3::AttributeChecker const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::flags [variable]
    cls.add_instance_attribute('flags', 'uint32_t', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::help [variable]
    cls.add_instance_attribute('help', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::initialValue [variable]
    cls.add_instance_attribute('initialValue', 'ns3::Ptr< ns3::AttributeValue const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::originalInitialValue [variable]
    cls.add_instance_attribute('originalInitialValue', 'ns3::Ptr< ns3::AttributeValue const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::supportLevel [variable]
    cls.add_instance_attribute('supportLevel', 'ns3::TypeId::SupportLevel', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation::supportMsg [variable]
    cls.add_instance_attribute('supportMsg', 'std::string', is_const=False)
    return

def register_Ns3TypeIdTraceSourceInformation_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::TraceSourceInformation() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::TraceSourceInformation(ns3::TypeId::TraceSourceInformation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeId::TraceSourceInformation const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::accessor [variable]
    cls.add_instance_attribute('accessor', 'ns3::Ptr< ns3::TraceSourceAccessor const >', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::callback [variable]
    cls.add_instance_attribute('callback', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::help [variable]
    cls.add_instance_attribute('help', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::name [variable]
    cls.add_instance_attribute('name', 'std::string', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::supportLevel [variable]
    cls.add_instance_attribute('supportLevel', 'ns3::TypeId::SupportLevel', is_const=False)
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation::supportMsg [variable]
    cls.add_instance_attribute('supportMsg', 'std::string', is_const=False)
    return

def register_Ns3Vector2D_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## vector.h (module 'core'): ns3::Vector2D::Vector2D(ns3::Vector2D const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector2D const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector2D::Vector2D(double _x, double _y) [constructor]
    cls.add_constructor([param('double', '_x'), param('double', '_y')])
    ## vector.h (module 'core'): ns3::Vector2D::Vector2D() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector2D::x [variable]
    cls.add_instance_attribute('x', 'double', is_const=False)
    ## vector.h (module 'core'): ns3::Vector2D::y [variable]
    cls.add_instance_attribute('y', 'double', is_const=False)
    return

def register_Ns3Vector3D_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## vector.h (module 'core'): ns3::Vector3D::Vector3D(ns3::Vector3D const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector3D const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector3D::Vector3D(double _x, double _y, double _z) [constructor]
    cls.add_constructor([param('double', '_x'), param('double', '_y'), param('double', '_z')])
    ## vector.h (module 'core'): ns3::Vector3D::Vector3D() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector3D::x [variable]
    cls.add_instance_attribute('x', 'double', is_const=False)
    ## vector.h (module 'core'): ns3::Vector3D::y [variable]
    cls.add_instance_attribute('y', 'double', is_const=False)
    ## vector.h (module 'core'): ns3::Vector3D::z [variable]
    cls.add_instance_attribute('z', 'double', is_const=False)
    return

def register_Ns3WifiMode_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## wifi-mode.h (module 'wifi'): ns3::WifiMode::WifiMode(ns3::WifiMode const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiMode const &', 'arg0')])
    ## wifi-mode.h (module 'wifi'): ns3::WifiMode::WifiMode() [constructor]
    cls.add_constructor([])
    ## wifi-mode.h (module 'wifi'): ns3::WifiMode::WifiMode(std::string name) [constructor]
    cls.add_constructor([param('std::string', 'name')])
    ## wifi-mode.h (module 'wifi'): ns3::WifiCodeRate ns3::WifiMode::GetCodeRate() const [member function]
    cls.add_method('GetCodeRate', 
                   'ns3::WifiCodeRate', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint16_t ns3::WifiMode::GetConstellationSize() const [member function]
    cls.add_method('GetConstellationSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint64_t ns3::WifiMode::GetDataRate(uint32_t channelWidth, bool isShortGuardInterval, uint8_t nss) const [member function]
    cls.add_method('GetDataRate', 
                   'uint64_t', 
                   [param('uint32_t', 'channelWidth'), param('bool', 'isShortGuardInterval'), param('uint8_t', 'nss')], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint64_t ns3::WifiMode::GetDataRate(ns3::WifiTxVector txVector) const [member function]
    cls.add_method('GetDataRate', 
                   'uint64_t', 
                   [param('ns3::WifiTxVector', 'txVector')], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint8_t ns3::WifiMode::GetMcsValue() const [member function]
    cls.add_method('GetMcsValue', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): ns3::WifiModulationClass ns3::WifiMode::GetModulationClass() const [member function]
    cls.add_method('GetModulationClass', 
                   'ns3::WifiModulationClass', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint64_t ns3::WifiMode::GetNonHtReferenceRate() const [member function]
    cls.add_method('GetNonHtReferenceRate', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint64_t ns3::WifiMode::GetPhyRate(uint32_t channelWidth, bool isShortGuardInterval, uint8_t nss) const [member function]
    cls.add_method('GetPhyRate', 
                   'uint64_t', 
                   [param('uint32_t', 'channelWidth'), param('bool', 'isShortGuardInterval'), param('uint8_t', 'nss')], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint64_t ns3::WifiMode::GetPhyRate(ns3::WifiTxVector txVector) const [member function]
    cls.add_method('GetPhyRate', 
                   'uint64_t', 
                   [param('ns3::WifiTxVector', 'txVector')], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): uint32_t ns3::WifiMode::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): std::string ns3::WifiMode::GetUniqueName() const [member function]
    cls.add_method('GetUniqueName', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): bool ns3::WifiMode::IsHigherCodeRate(ns3::WifiMode mode) const [member function]
    cls.add_method('IsHigherCodeRate', 
                   'bool', 
                   [param('ns3::WifiMode', 'mode')], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): bool ns3::WifiMode::IsHigherDataRate(ns3::WifiMode mode) const [member function]
    cls.add_method('IsHigherDataRate', 
                   'bool', 
                   [param('ns3::WifiMode', 'mode')], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): bool ns3::WifiMode::IsMandatory() const [member function]
    cls.add_method('IsMandatory', 
                   'bool', 
                   [], 
                   is_const=True)
    return

def register_Ns3WifiModeFactory_methods(root_module, cls):
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeFactory::WifiModeFactory(ns3::WifiModeFactory const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiModeFactory const &', 'arg0')])
    ## wifi-mode.h (module 'wifi'): static ns3::WifiMode ns3::WifiModeFactory::CreateWifiMcs(std::string uniqueName, uint8_t mcsValue, ns3::WifiModulationClass modClass) [member function]
    cls.add_method('CreateWifiMcs', 
                   'ns3::WifiMode', 
                   [param('std::string', 'uniqueName'), param('uint8_t', 'mcsValue'), param('ns3::WifiModulationClass', 'modClass')], 
                   is_static=True)
    ## wifi-mode.h (module 'wifi'): static ns3::WifiMode ns3::WifiModeFactory::CreateWifiMode(std::string uniqueName, ns3::WifiModulationClass modClass, bool isMandatory, ns3::WifiCodeRate codingRate, uint16_t constellationSize) [member function]
    cls.add_method('CreateWifiMode', 
                   'ns3::WifiMode', 
                   [param('std::string', 'uniqueName'), param('ns3::WifiModulationClass', 'modClass'), param('bool', 'isMandatory'), param('ns3::WifiCodeRate', 'codingRate'), param('uint16_t', 'constellationSize')], 
                   is_static=True)
    return

def register_Ns3WifiPhyListener_methods(root_module, cls):
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhyListener::WifiPhyListener() [constructor]
    cls.add_constructor([])
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhyListener::WifiPhyListener(ns3::WifiPhyListener const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiPhyListener const &', 'arg0')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifyMaybeCcaBusyStart(ns3::Time duration) [member function]
    cls.add_method('NotifyMaybeCcaBusyStart', 
                   'void', 
                   [param('ns3::Time', 'duration')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifyRxEndError() [member function]
    cls.add_method('NotifyRxEndError', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifyRxEndOk() [member function]
    cls.add_method('NotifyRxEndOk', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifyRxStart(ns3::Time duration) [member function]
    cls.add_method('NotifyRxStart', 
                   'void', 
                   [param('ns3::Time', 'duration')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifySleep() [member function]
    cls.add_method('NotifySleep', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifySwitchingStart(ns3::Time duration) [member function]
    cls.add_method('NotifySwitchingStart', 
                   'void', 
                   [param('ns3::Time', 'duration')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifyTxStart(ns3::Time duration, double txPowerDbm) [member function]
    cls.add_method('NotifyTxStart', 
                   'void', 
                   [param('ns3::Time', 'duration'), param('double', 'txPowerDbm')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhyListener::NotifyWakeup() [member function]
    cls.add_method('NotifyWakeup', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3WifiRemoteStation_methods(root_module, cls):
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation::WifiRemoteStation() [constructor]
    cls.add_constructor([])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation::WifiRemoteStation(ns3::WifiRemoteStation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiRemoteStation const &', 'arg0')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation::m_slrc [variable]
    cls.add_instance_attribute('m_slrc', 'uint32_t', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation::m_ssrc [variable]
    cls.add_instance_attribute('m_ssrc', 'uint32_t', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation::m_state [variable]
    cls.add_instance_attribute('m_state', 'ns3::WifiRemoteStationState *', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation::m_tid [variable]
    cls.add_instance_attribute('m_tid', 'uint8_t', is_const=False)
    return

def register_Ns3WifiRemoteStationInfo_methods(root_module, cls):
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationInfo::WifiRemoteStationInfo(ns3::WifiRemoteStationInfo const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiRemoteStationInfo const &', 'arg0')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationInfo::WifiRemoteStationInfo() [constructor]
    cls.add_constructor([])
    ## wifi-remote-station-manager.h (module 'wifi'): double ns3::WifiRemoteStationInfo::GetFrameErrorRate() const [member function]
    cls.add_method('GetFrameErrorRate', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationInfo::NotifyTxFailed() [member function]
    cls.add_method('NotifyTxFailed', 
                   'void', 
                   [])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationInfo::NotifyTxSuccess(uint32_t retryCounter) [member function]
    cls.add_method('NotifyTxSuccess', 
                   'void', 
                   [param('uint32_t', 'retryCounter')])
    return

def register_Ns3WifiRemoteStationState_methods(root_module, cls):
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::WifiRemoteStationState() [constructor]
    cls.add_constructor([])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::WifiRemoteStationState(ns3::WifiRemoteStationState const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiRemoteStationState const &', 'arg0')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_address [variable]
    cls.add_instance_attribute('m_address', 'ns3::Mac48Address', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_aggregation [variable]
    cls.add_instance_attribute('m_aggregation', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_channelWidth [variable]
    cls.add_instance_attribute('m_channelWidth', 'uint32_t', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_greenfield [variable]
    cls.add_instance_attribute('m_greenfield', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_htSupported [variable]
    cls.add_instance_attribute('m_htSupported', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_info [variable]
    cls.add_instance_attribute('m_info', 'ns3::WifiRemoteStationInfo', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_ness [variable]
    cls.add_instance_attribute('m_ness', 'uint32_t', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_operationalMcsSet [variable]
    cls.add_instance_attribute('m_operationalMcsSet', 'ns3::WifiModeList', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_operationalRateSet [variable]
    cls.add_instance_attribute('m_operationalRateSet', 'ns3::WifiModeList', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_rx [variable]
    cls.add_instance_attribute('m_rx', 'uint8_t', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_shortGuardInterval [variable]
    cls.add_instance_attribute('m_shortGuardInterval', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_shortPreamble [variable]
    cls.add_instance_attribute('m_shortPreamble', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_shortSlotTime [variable]
    cls.add_instance_attribute('m_shortSlotTime', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_stbc [variable]
    cls.add_instance_attribute('m_stbc', 'bool', is_const=False)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationState::m_vhtSupported [variable]
    cls.add_instance_attribute('m_vhtSupported', 'bool', is_const=False)
    return

def register_Ns3WifiTxVector_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## wifi-tx-vector.h (module 'wifi'): ns3::WifiTxVector::WifiTxVector(ns3::WifiTxVector const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiTxVector const &', 'arg0')])
    ## wifi-tx-vector.h (module 'wifi'): ns3::WifiTxVector::WifiTxVector() [constructor]
    cls.add_constructor([])
    ## wifi-tx-vector.h (module 'wifi'): ns3::WifiTxVector::WifiTxVector(ns3::WifiMode mode, uint8_t powerLevel, uint8_t retries, bool shortGuardInterval, uint8_t nss, uint8_t ness, uint32_t channelWidth, bool aggregation, bool stbc) [constructor]
    cls.add_constructor([param('ns3::WifiMode', 'mode'), param('uint8_t', 'powerLevel'), param('uint8_t', 'retries'), param('bool', 'shortGuardInterval'), param('uint8_t', 'nss'), param('uint8_t', 'ness'), param('uint32_t', 'channelWidth'), param('bool', 'aggregation'), param('bool', 'stbc')])
    ## wifi-tx-vector.h (module 'wifi'): uint32_t ns3::WifiTxVector::GetChannelWidth() const [member function]
    cls.add_method('GetChannelWidth', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): ns3::WifiMode ns3::WifiTxVector::GetMode() const [member function]
    cls.add_method('GetMode', 
                   'ns3::WifiMode', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): uint8_t ns3::WifiTxVector::GetNess() const [member function]
    cls.add_method('GetNess', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): uint8_t ns3::WifiTxVector::GetNss() const [member function]
    cls.add_method('GetNss', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): uint8_t ns3::WifiTxVector::GetRetries() const [member function]
    cls.add_method('GetRetries', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): uint8_t ns3::WifiTxVector::GetTxPowerLevel() const [member function]
    cls.add_method('GetTxPowerLevel', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): bool ns3::WifiTxVector::IsAggregation() const [member function]
    cls.add_method('IsAggregation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): bool ns3::WifiTxVector::IsShortGuardInterval() const [member function]
    cls.add_method('IsShortGuardInterval', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): bool ns3::WifiTxVector::IsStbc() const [member function]
    cls.add_method('IsStbc', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetAggregation(bool aggregation) [member function]
    cls.add_method('SetAggregation', 
                   'void', 
                   [param('bool', 'aggregation')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetChannelWidth(uint32_t channelWidth) [member function]
    cls.add_method('SetChannelWidth', 
                   'void', 
                   [param('uint32_t', 'channelWidth')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetMode(ns3::WifiMode mode) [member function]
    cls.add_method('SetMode', 
                   'void', 
                   [param('ns3::WifiMode', 'mode')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetNess(uint8_t ness) [member function]
    cls.add_method('SetNess', 
                   'void', 
                   [param('uint8_t', 'ness')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetNss(uint8_t nss) [member function]
    cls.add_method('SetNss', 
                   'void', 
                   [param('uint8_t', 'nss')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetRetries(uint8_t retries) [member function]
    cls.add_method('SetRetries', 
                   'void', 
                   [param('uint8_t', 'retries')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetShortGuardInterval(bool guardinterval) [member function]
    cls.add_method('SetShortGuardInterval', 
                   'void', 
                   [param('bool', 'guardinterval')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetStbc(bool stbc) [member function]
    cls.add_method('SetStbc', 
                   'void', 
                   [param('bool', 'stbc')])
    ## wifi-tx-vector.h (module 'wifi'): void ns3::WifiTxVector::SetTxPowerLevel(uint8_t powerlevel) [member function]
    cls.add_method('SetTxPowerLevel', 
                   'void', 
                   [param('uint8_t', 'powerlevel')])
    return

def register_Ns3Empty_methods(root_module, cls):
    ## empty.h (module 'core'): ns3::empty::empty() [constructor]
    cls.add_constructor([])
    ## empty.h (module 'core'): ns3::empty::empty(ns3::empty const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::empty const &', 'arg0')])
    return

def register_Ns3Int64x64_t_methods(root_module, cls):
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('+=', param('ns3::int64x64_t const &', u'right'))
    cls.add_inplace_numeric_operator('/=', param('ns3::int64x64_t const &', u'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', u'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', u'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', u'right'))
    cls.add_unary_numeric_operator('-')
    cls.add_binary_numeric_operator('/', root_module['ns3::int64x64_t'], root_module['ns3::int64x64_t'], param('ns3::int64x64_t const &', u'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_inplace_numeric_operator('*=', param('ns3::int64x64_t const &', u'right'))
    cls.add_inplace_numeric_operator('-=', param('ns3::int64x64_t const &', u'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t() [constructor]
    cls.add_constructor([])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long double v) [constructor]
    cls.add_constructor([param('long double', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long int v) [constructor]
    cls.add_constructor([param('long int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long long int v) [constructor]
    cls.add_constructor([param('long long int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(unsigned int v) [constructor]
    cls.add_constructor([param('unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long unsigned int v) [constructor]
    cls.add_constructor([param('long unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(long long unsigned int v) [constructor]
    cls.add_constructor([param('long long unsigned int', 'v')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(int64_t hi, uint64_t lo) [constructor]
    cls.add_constructor([param('int64_t', 'hi'), param('uint64_t', 'lo')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::int64x64_t(ns3::int64x64_t const & o) [copy constructor]
    cls.add_constructor([param('ns3::int64x64_t const &', 'o')])
    ## int64x64-double.h (module 'core'): double ns3::int64x64_t::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): int64_t ns3::int64x64_t::GetHigh() const [member function]
    cls.add_method('GetHigh', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): uint64_t ns3::int64x64_t::GetLow() const [member function]
    cls.add_method('GetLow', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## int64x64-double.h (module 'core'): static ns3::int64x64_t ns3::int64x64_t::Invert(uint64_t v) [member function]
    cls.add_method('Invert', 
                   'ns3::int64x64_t', 
                   [param('uint64_t', 'v')], 
                   is_static=True)
    ## int64x64-double.h (module 'core'): void ns3::int64x64_t::MulByInvert(ns3::int64x64_t const & o) [member function]
    cls.add_method('MulByInvert', 
                   'void', 
                   [param('ns3::int64x64_t const &', 'o')])
    ## int64x64-double.h (module 'core'): ns3::int64x64_t::implementation [variable]
    cls.add_static_attribute('implementation', 'ns3::int64x64_t::impl_type const', is_const=True)
    return

def register_Ns3MpduInfo_methods(root_module, cls):
    ## wifi-phy.h (module 'wifi'): ns3::mpduInfo::mpduInfo() [constructor]
    cls.add_constructor([])
    ## wifi-phy.h (module 'wifi'): ns3::mpduInfo::mpduInfo(ns3::mpduInfo const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::mpduInfo const &', 'arg0')])
    ## wifi-phy.h (module 'wifi'): ns3::mpduInfo::mpduRefNumber [variable]
    cls.add_instance_attribute('mpduRefNumber', 'uint32_t', is_const=False)
    ## wifi-phy.h (module 'wifi'): ns3::mpduInfo::type [variable]
    cls.add_instance_attribute('type', 'ns3::mpduType', is_const=False)
    return

def register_Ns3SignalNoiseDbm_methods(root_module, cls):
    ## wifi-phy.h (module 'wifi'): ns3::signalNoiseDbm::signalNoiseDbm() [constructor]
    cls.add_constructor([])
    ## wifi-phy.h (module 'wifi'): ns3::signalNoiseDbm::signalNoiseDbm(ns3::signalNoiseDbm const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::signalNoiseDbm const &', 'arg0')])
    ## wifi-phy.h (module 'wifi'): ns3::signalNoiseDbm::noise [variable]
    cls.add_instance_attribute('noise', 'double', is_const=False)
    ## wifi-phy.h (module 'wifi'): ns3::signalNoiseDbm::signal [variable]
    cls.add_instance_attribute('signal', 'double', is_const=False)
    return

def register_Ns3Chunk_methods(root_module, cls):
    ## chunk.h (module 'network'): ns3::Chunk::Chunk() [constructor]
    cls.add_constructor([])
    ## chunk.h (module 'network'): ns3::Chunk::Chunk(ns3::Chunk const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Chunk const &', 'arg0')])
    ## chunk.h (module 'network'): uint32_t ns3::Chunk::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_virtual=True)
    ## chunk.h (module 'network'): static ns3::TypeId ns3::Chunk::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## chunk.h (module 'network'): void ns3::Chunk::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3Header_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## header.h (module 'network'): ns3::Header::Header() [constructor]
    cls.add_constructor([])
    ## header.h (module 'network'): ns3::Header::Header(ns3::Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Header const &', 'arg0')])
    ## header.h (module 'network'): uint32_t ns3::Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_virtual=True)
    ## header.h (module 'network'): uint32_t ns3::Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## header.h (module 'network'): static ns3::TypeId ns3::Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## header.h (module 'network'): void ns3::Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## header.h (module 'network'): void ns3::Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3Icmpv4DestinationUnreachable_methods(root_module, cls):
    ## icmpv4.h (module 'internet'): ns3::Icmpv4DestinationUnreachable::Icmpv4DestinationUnreachable(ns3::Icmpv4DestinationUnreachable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Icmpv4DestinationUnreachable const &', 'arg0')])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4DestinationUnreachable::Icmpv4DestinationUnreachable() [constructor]
    cls.add_constructor([])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4DestinationUnreachable::GetData(uint8_t * payload) const [member function]
    cls.add_method('GetData', 
                   'void', 
                   [param('uint8_t *', 'payload')], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): ns3::Ipv4Header ns3::Icmpv4DestinationUnreachable::GetHeader() const [member function]
    cls.add_method('GetHeader', 
                   'ns3::Ipv4Header', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): uint16_t ns3::Icmpv4DestinationUnreachable::GetNextHopMtu() const [member function]
    cls.add_method('GetNextHopMtu', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): static ns3::TypeId ns3::Icmpv4DestinationUnreachable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4DestinationUnreachable::SetData(ns3::Ptr<ns3::Packet const> data) [member function]
    cls.add_method('SetData', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'data')])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4DestinationUnreachable::SetHeader(ns3::Ipv4Header header) [member function]
    cls.add_method('SetHeader', 
                   'void', 
                   [param('ns3::Ipv4Header', 'header')])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4DestinationUnreachable::SetNextHopMtu(uint16_t mtu) [member function]
    cls.add_method('SetNextHopMtu', 
                   'void', 
                   [param('uint16_t', 'mtu')])
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4DestinationUnreachable::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   visibility='private', is_virtual=True)
    ## icmpv4.h (module 'internet'): ns3::TypeId ns3::Icmpv4DestinationUnreachable::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4DestinationUnreachable::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4DestinationUnreachable::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, visibility='private', is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4DestinationUnreachable::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, visibility='private', is_virtual=True)
    return

def register_Ns3Icmpv4Echo_methods(root_module, cls):
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Echo::Icmpv4Echo(ns3::Icmpv4Echo const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Icmpv4Echo const &', 'arg0')])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Echo::Icmpv4Echo() [constructor]
    cls.add_constructor([])
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4Echo::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4Echo::GetData(uint8_t * payload) const [member function]
    cls.add_method('GetData', 
                   'uint32_t', 
                   [param('uint8_t *', 'payload')], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4Echo::GetDataSize() const [member function]
    cls.add_method('GetDataSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): uint16_t ns3::Icmpv4Echo::GetIdentifier() const [member function]
    cls.add_method('GetIdentifier', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): ns3::TypeId ns3::Icmpv4Echo::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): uint16_t ns3::Icmpv4Echo::GetSequenceNumber() const [member function]
    cls.add_method('GetSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4Echo::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): static ns3::TypeId ns3::Icmpv4Echo::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Echo::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Echo::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Echo::SetData(ns3::Ptr<ns3::Packet const> data) [member function]
    cls.add_method('SetData', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'data')])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Echo::SetIdentifier(uint16_t id) [member function]
    cls.add_method('SetIdentifier', 
                   'void', 
                   [param('uint16_t', 'id')])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Echo::SetSequenceNumber(uint16_t seq) [member function]
    cls.add_method('SetSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'seq')])
    return

def register_Ns3Icmpv4Header_methods(root_module, cls):
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Header::Icmpv4Header(ns3::Icmpv4Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Icmpv4Header const &', 'arg0')])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4Header::Icmpv4Header() [constructor]
    cls.add_constructor([])
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Header::EnableChecksum() [member function]
    cls.add_method('EnableChecksum', 
                   'void', 
                   [])
    ## icmpv4.h (module 'internet'): uint8_t ns3::Icmpv4Header::GetCode() const [member function]
    cls.add_method('GetCode', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): ns3::TypeId ns3::Icmpv4Header::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): uint8_t ns3::Icmpv4Header::GetType() const [member function]
    cls.add_method('GetType', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): static ns3::TypeId ns3::Icmpv4Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Header::SetCode(uint8_t code) [member function]
    cls.add_method('SetCode', 
                   'void', 
                   [param('uint8_t', 'code')])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4Header::SetType(uint8_t type) [member function]
    cls.add_method('SetType', 
                   'void', 
                   [param('uint8_t', 'type')])
    return

def register_Ns3Icmpv4TimeExceeded_methods(root_module, cls):
    ## icmpv4.h (module 'internet'): ns3::Icmpv4TimeExceeded::Icmpv4TimeExceeded(ns3::Icmpv4TimeExceeded const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Icmpv4TimeExceeded const &', 'arg0')])
    ## icmpv4.h (module 'internet'): ns3::Icmpv4TimeExceeded::Icmpv4TimeExceeded() [constructor]
    cls.add_constructor([])
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4TimeExceeded::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4TimeExceeded::GetData(uint8_t * payload) const [member function]
    cls.add_method('GetData', 
                   'void', 
                   [param('uint8_t *', 'payload')], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): ns3::Ipv4Header ns3::Icmpv4TimeExceeded::GetHeader() const [member function]
    cls.add_method('GetHeader', 
                   'ns3::Ipv4Header', 
                   [], 
                   is_const=True)
    ## icmpv4.h (module 'internet'): ns3::TypeId ns3::Icmpv4TimeExceeded::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): uint32_t ns3::Icmpv4TimeExceeded::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): static ns3::TypeId ns3::Icmpv4TimeExceeded::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4TimeExceeded::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4TimeExceeded::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4TimeExceeded::SetData(ns3::Ptr<ns3::Packet const> data) [member function]
    cls.add_method('SetData', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'data')])
    ## icmpv4.h (module 'internet'): void ns3::Icmpv4TimeExceeded::SetHeader(ns3::Ipv4Header header) [member function]
    cls.add_method('SetHeader', 
                   'void', 
                   [param('ns3::Ipv4Header', 'header')])
    return

def register_Ns3Ipv4Header_methods(root_module, cls):
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::Ipv4Header(ns3::Ipv4Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Header const &', 'arg0')])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::Ipv4Header() [constructor]
    cls.add_constructor([])
    ## ipv4-header.h (module 'internet'): uint32_t ns3::Ipv4Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## ipv4-header.h (module 'internet'): std::string ns3::Ipv4Header::DscpTypeToString(ns3::Ipv4Header::DscpType dscp) const [member function]
    cls.add_method('DscpTypeToString', 
                   'std::string', 
                   [param('ns3::Ipv4Header::DscpType', 'dscp')], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): std::string ns3::Ipv4Header::EcnTypeToString(ns3::Ipv4Header::EcnType ecn) const [member function]
    cls.add_method('EcnTypeToString', 
                   'std::string', 
                   [param('ns3::Ipv4Header::EcnType', 'ecn')], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::EnableChecksum() [member function]
    cls.add_method('EnableChecksum', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Header::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::DscpType ns3::Ipv4Header::GetDscp() const [member function]
    cls.add_method('GetDscp', 
                   'ns3::Ipv4Header::DscpType', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Header::EcnType ns3::Ipv4Header::GetEcn() const [member function]
    cls.add_method('GetEcn', 
                   'ns3::Ipv4Header::EcnType', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint16_t ns3::Ipv4Header::GetFragmentOffset() const [member function]
    cls.add_method('GetFragmentOffset', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint16_t ns3::Ipv4Header::GetIdentification() const [member function]
    cls.add_method('GetIdentification', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): ns3::TypeId ns3::Ipv4Header::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): uint16_t ns3::Ipv4Header::GetPayloadSize() const [member function]
    cls.add_method('GetPayloadSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint8_t ns3::Ipv4Header::GetProtocol() const [member function]
    cls.add_method('GetProtocol', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint32_t ns3::Ipv4Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Header::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint8_t ns3::Ipv4Header::GetTos() const [member function]
    cls.add_method('GetTos', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): uint8_t ns3::Ipv4Header::GetTtl() const [member function]
    cls.add_method('GetTtl', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): static ns3::TypeId ns3::Ipv4Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-header.h (module 'internet'): bool ns3::Ipv4Header::IsChecksumOk() const [member function]
    cls.add_method('IsChecksumOk', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): bool ns3::Ipv4Header::IsDontFragment() const [member function]
    cls.add_method('IsDontFragment', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): bool ns3::Ipv4Header::IsLastFragment() const [member function]
    cls.add_method('IsLastFragment', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetDestination(ns3::Ipv4Address destination) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetDontFragment() [member function]
    cls.add_method('SetDontFragment', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetDscp(ns3::Ipv4Header::DscpType dscp) [member function]
    cls.add_method('SetDscp', 
                   'void', 
                   [param('ns3::Ipv4Header::DscpType', 'dscp')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetEcn(ns3::Ipv4Header::EcnType ecn) [member function]
    cls.add_method('SetEcn', 
                   'void', 
                   [param('ns3::Ipv4Header::EcnType', 'ecn')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetFragmentOffset(uint16_t offsetBytes) [member function]
    cls.add_method('SetFragmentOffset', 
                   'void', 
                   [param('uint16_t', 'offsetBytes')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetIdentification(uint16_t identification) [member function]
    cls.add_method('SetIdentification', 
                   'void', 
                   [param('uint16_t', 'identification')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetLastFragment() [member function]
    cls.add_method('SetLastFragment', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetMayFragment() [member function]
    cls.add_method('SetMayFragment', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetMoreFragments() [member function]
    cls.add_method('SetMoreFragments', 
                   'void', 
                   [])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetPayloadSize(uint16_t size) [member function]
    cls.add_method('SetPayloadSize', 
                   'void', 
                   [param('uint16_t', 'size')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetProtocol(uint8_t num) [member function]
    cls.add_method('SetProtocol', 
                   'void', 
                   [param('uint8_t', 'num')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetSource(ns3::Ipv4Address source) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetTos(uint8_t tos) [member function]
    cls.add_method('SetTos', 
                   'void', 
                   [param('uint8_t', 'tos')])
    ## ipv4-header.h (module 'internet'): void ns3::Ipv4Header::SetTtl(uint8_t ttl) [member function]
    cls.add_method('SetTtl', 
                   'void', 
                   [param('uint8_t', 'ttl')])
    return

def register_Ns3Ipv6Header_methods(root_module, cls):
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::Ipv6Header(ns3::Ipv6Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6Header const &', 'arg0')])
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::Ipv6Header() [constructor]
    cls.add_constructor([])
    ## ipv6-header.h (module 'internet'): uint32_t ns3::Ipv6Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## ipv6-header.h (module 'internet'): std::string ns3::Ipv6Header::DscpTypeToString(ns3::Ipv6Header::DscpType dscp) const [member function]
    cls.add_method('DscpTypeToString', 
                   'std::string', 
                   [param('ns3::Ipv6Header::DscpType', 'dscp')], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Address ns3::Ipv6Header::GetDestinationAddress() const [member function]
    cls.add_method('GetDestinationAddress', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Header::DscpType ns3::Ipv6Header::GetDscp() const [member function]
    cls.add_method('GetDscp', 
                   'ns3::Ipv6Header::DscpType', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint32_t ns3::Ipv6Header::GetFlowLabel() const [member function]
    cls.add_method('GetFlowLabel', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint8_t ns3::Ipv6Header::GetHopLimit() const [member function]
    cls.add_method('GetHopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): ns3::TypeId ns3::Ipv6Header::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): uint8_t ns3::Ipv6Header::GetNextHeader() const [member function]
    cls.add_method('GetNextHeader', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint16_t ns3::Ipv6Header::GetPayloadLength() const [member function]
    cls.add_method('GetPayloadLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint32_t ns3::Ipv6Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): ns3::Ipv6Address ns3::Ipv6Header::GetSourceAddress() const [member function]
    cls.add_method('GetSourceAddress', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): uint8_t ns3::Ipv6Header::GetTrafficClass() const [member function]
    cls.add_method('GetTrafficClass', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ipv6-header.h (module 'internet'): static ns3::TypeId ns3::Ipv6Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetDestinationAddress(ns3::Ipv6Address dst) [member function]
    cls.add_method('SetDestinationAddress', 
                   'void', 
                   [param('ns3::Ipv6Address', 'dst')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetDscp(ns3::Ipv6Header::DscpType dscp) [member function]
    cls.add_method('SetDscp', 
                   'void', 
                   [param('ns3::Ipv6Header::DscpType', 'dscp')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetFlowLabel(uint32_t flow) [member function]
    cls.add_method('SetFlowLabel', 
                   'void', 
                   [param('uint32_t', 'flow')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetHopLimit(uint8_t limit) [member function]
    cls.add_method('SetHopLimit', 
                   'void', 
                   [param('uint8_t', 'limit')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetNextHeader(uint8_t next) [member function]
    cls.add_method('SetNextHeader', 
                   'void', 
                   [param('uint8_t', 'next')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetPayloadLength(uint16_t len) [member function]
    cls.add_method('SetPayloadLength', 
                   'void', 
                   [param('uint16_t', 'len')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetSourceAddress(ns3::Ipv6Address src) [member function]
    cls.add_method('SetSourceAddress', 
                   'void', 
                   [param('ns3::Ipv6Address', 'src')])
    ## ipv6-header.h (module 'internet'): void ns3::Ipv6Header::SetTrafficClass(uint8_t traffic) [member function]
    cls.add_method('SetTrafficClass', 
                   'void', 
                   [param('uint8_t', 'traffic')])
    return

def register_Ns3Object_methods(root_module, cls):
    ## object.h (module 'core'): ns3::Object::Object() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): void ns3::Object::AggregateObject(ns3::Ptr<ns3::Object> other) [member function]
    cls.add_method('AggregateObject', 
                   'void', 
                   [param('ns3::Ptr< ns3::Object >', 'other')])
    ## object.h (module 'core'): void ns3::Object::Dispose() [member function]
    cls.add_method('Dispose', 
                   'void', 
                   [])
    ## object.h (module 'core'): ns3::Object::AggregateIterator ns3::Object::GetAggregateIterator() const [member function]
    cls.add_method('GetAggregateIterator', 
                   'ns3::Object::AggregateIterator', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::TypeId ns3::Object::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## object.h (module 'core'): static ns3::TypeId ns3::Object::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## object.h (module 'core'): void ns3::Object::Initialize() [member function]
    cls.add_method('Initialize', 
                   'void', 
                   [])
    ## object.h (module 'core'): bool ns3::Object::IsInitialized() const [member function]
    cls.add_method('IsInitialized', 
                   'bool', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::Object::Object(ns3::Object const & o) [copy constructor]
    cls.add_constructor([param('ns3::Object const &', 'o')], 
                        visibility='protected')
    ## object.h (module 'core'): void ns3::Object::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## object.h (module 'core'): void ns3::Object::DoInitialize() [member function]
    cls.add_method('DoInitialize', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## object.h (module 'core'): void ns3::Object::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3ObjectAggregateIterator_methods(root_module, cls):
    ## object.h (module 'core'): ns3::Object::AggregateIterator::AggregateIterator(ns3::Object::AggregateIterator const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Object::AggregateIterator const &', 'arg0')])
    ## object.h (module 'core'): ns3::Object::AggregateIterator::AggregateIterator() [constructor]
    cls.add_constructor([])
    ## object.h (module 'core'): bool ns3::Object::AggregateIterator::HasNext() const [member function]
    cls.add_method('HasNext', 
                   'bool', 
                   [], 
                   is_const=True)
    ## object.h (module 'core'): ns3::Ptr<ns3::Object const> ns3::Object::AggregateIterator::Next() [member function]
    cls.add_method('Next', 
                   'ns3::Ptr< ns3::Object const >', 
                   [])
    return

def register_Ns3PacketFilter_methods(root_module, cls):
    ## packet-filter.h (module 'traffic-control'): ns3::PacketFilter::PacketFilter(ns3::PacketFilter const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::PacketFilter const &', 'arg0')])
    ## packet-filter.h (module 'traffic-control'): ns3::PacketFilter::PacketFilter() [constructor]
    cls.add_constructor([])
    ## packet-filter.h (module 'traffic-control'): int32_t ns3::PacketFilter::Classify(ns3::Ptr<ns3::QueueDiscItem> item) const [member function]
    cls.add_method('Classify', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::QueueDiscItem >', 'item')], 
                   is_const=True)
    ## packet-filter.h (module 'traffic-control'): static ns3::TypeId ns3::PacketFilter::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## packet-filter.h (module 'traffic-control'): ns3::PacketFilter::PF_NO_MATCH [variable]
    cls.add_static_attribute('PF_NO_MATCH', 'int const', is_const=True)
    ## packet-filter.h (module 'traffic-control'): bool ns3::PacketFilter::CheckProtocol(ns3::Ptr<ns3::QueueDiscItem> item) const [member function]
    cls.add_method('CheckProtocol', 
                   'bool', 
                   [param('ns3::Ptr< ns3::QueueDiscItem >', 'item')], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## packet-filter.h (module 'traffic-control'): int32_t ns3::PacketFilter::DoClassify(ns3::Ptr<ns3::QueueDiscItem> item) const [member function]
    cls.add_method('DoClassify', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::QueueDiscItem >', 'item')], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    return

def register_Ns3Queue_methods(root_module, cls):
    ## queue.h (module 'network'): ns3::Queue::Queue(ns3::Queue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Queue const &', 'arg0')])
    ## queue.h (module 'network'): ns3::Queue::Queue() [constructor]
    cls.add_constructor([])
    ## queue.h (module 'network'): ns3::Ptr<ns3::QueueItem> ns3::Queue::Dequeue() [member function]
    cls.add_method('Dequeue', 
                   'ns3::Ptr< ns3::QueueItem >', 
                   [])
    ## queue.h (module 'network'): void ns3::Queue::DequeueAll() [member function]
    cls.add_method('DequeueAll', 
                   'void', 
                   [])
    ## queue.h (module 'network'): bool ns3::Queue::Enqueue(ns3::Ptr<ns3::QueueItem> item) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::Ptr< ns3::QueueItem >', 'item')])
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetMaxBytes() const [member function]
    cls.add_method('GetMaxBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetMaxPackets() const [member function]
    cls.add_method('GetMaxPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): ns3::Queue::QueueMode ns3::Queue::GetMode() const [member function]
    cls.add_method('GetMode', 
                   'ns3::Queue::QueueMode', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetNBytes() const [member function]
    cls.add_method('GetNBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetNPackets() const [member function]
    cls.add_method('GetNPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetTotalDroppedBytes() const [member function]
    cls.add_method('GetTotalDroppedBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetTotalDroppedPackets() const [member function]
    cls.add_method('GetTotalDroppedPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetTotalReceivedBytes() const [member function]
    cls.add_method('GetTotalReceivedBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): uint32_t ns3::Queue::GetTotalReceivedPackets() const [member function]
    cls.add_method('GetTotalReceivedPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): static ns3::TypeId ns3::Queue::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## queue.h (module 'network'): bool ns3::Queue::IsEmpty() const [member function]
    cls.add_method('IsEmpty', 
                   'bool', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): ns3::Ptr<const ns3::QueueItem> ns3::Queue::Peek() const [member function]
    cls.add_method('Peek', 
                   'ns3::Ptr< ns3::QueueItem const >', 
                   [], 
                   is_const=True)
    ## queue.h (module 'network'): ns3::Ptr<ns3::QueueItem> ns3::Queue::Remove() [member function]
    cls.add_method('Remove', 
                   'ns3::Ptr< ns3::QueueItem >', 
                   [])
    ## queue.h (module 'network'): void ns3::Queue::ResetStatistics() [member function]
    cls.add_method('ResetStatistics', 
                   'void', 
                   [])
    ## queue.h (module 'network'): void ns3::Queue::SetDropCallback(ns3::Callback<void, ns3::Ptr<ns3::QueueItem>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDropCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::QueueItem >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## queue.h (module 'network'): void ns3::Queue::SetMaxBytes(uint32_t maxBytes) [member function]
    cls.add_method('SetMaxBytes', 
                   'void', 
                   [param('uint32_t', 'maxBytes')])
    ## queue.h (module 'network'): void ns3::Queue::SetMaxPackets(uint32_t maxPackets) [member function]
    cls.add_method('SetMaxPackets', 
                   'void', 
                   [param('uint32_t', 'maxPackets')])
    ## queue.h (module 'network'): void ns3::Queue::SetMode(ns3::Queue::QueueMode mode) [member function]
    cls.add_method('SetMode', 
                   'void', 
                   [param('ns3::Queue::QueueMode', 'mode')])
    ## queue.h (module 'network'): void ns3::Queue::Drop(ns3::Ptr<ns3::QueueItem> item) [member function]
    cls.add_method('Drop', 
                   'void', 
                   [param('ns3::Ptr< ns3::QueueItem >', 'item')], 
                   visibility='protected')
    ## queue.h (module 'network'): ns3::Ptr<ns3::QueueItem> ns3::Queue::DoDequeue() [member function]
    cls.add_method('DoDequeue', 
                   'ns3::Ptr< ns3::QueueItem >', 
                   [], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## queue.h (module 'network'): bool ns3::Queue::DoEnqueue(ns3::Ptr<ns3::QueueItem> item) [member function]
    cls.add_method('DoEnqueue', 
                   'bool', 
                   [param('ns3::Ptr< ns3::QueueItem >', 'item')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## queue.h (module 'network'): ns3::Ptr<const ns3::QueueItem> ns3::Queue::DoPeek() const [member function]
    cls.add_method('DoPeek', 
                   'ns3::Ptr< ns3::QueueItem const >', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## queue.h (module 'network'): ns3::Ptr<ns3::QueueItem> ns3::Queue::DoRemove() [member function]
    cls.add_method('DoRemove', 
                   'ns3::Ptr< ns3::QueueItem >', 
                   [], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    return

def register_Ns3QueueDisc_methods(root_module, cls):
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDisc::QueueDisc(ns3::QueueDisc const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::QueueDisc const &', 'arg0')])
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDisc::QueueDisc() [constructor]
    cls.add_constructor([])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::AddInternalQueue(ns3::Ptr<ns3::Queue> queue) [member function]
    cls.add_method('AddInternalQueue', 
                   'void', 
                   [param('ns3::Ptr< ns3::Queue >', 'queue')])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::AddPacketFilter(ns3::Ptr<ns3::PacketFilter> filter) [member function]
    cls.add_method('AddPacketFilter', 
                   'void', 
                   [param('ns3::Ptr< ns3::PacketFilter >', 'filter')])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::AddQueueDiscClass(ns3::Ptr<ns3::QueueDiscClass> qdClass) [member function]
    cls.add_method('AddQueueDiscClass', 
                   'void', 
                   [param('ns3::Ptr< ns3::QueueDiscClass >', 'qdClass')])
    ## queue-disc.h (module 'traffic-control'): int32_t ns3::QueueDisc::Classify(ns3::Ptr<ns3::QueueDiscItem> item) [member function]
    cls.add_method('Classify', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::QueueDiscItem >', 'item')])
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::QueueDiscItem> ns3::QueueDisc::Dequeue() [member function]
    cls.add_method('Dequeue', 
                   'ns3::Ptr< ns3::QueueDiscItem >', 
                   [])
    ## queue-disc.h (module 'traffic-control'): bool ns3::QueueDisc::Enqueue(ns3::Ptr<ns3::QueueDiscItem> item) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::Ptr< ns3::QueueDiscItem >', 'item')])
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::Queue> ns3::QueueDisc::GetInternalQueue(uint32_t i) const [member function]
    cls.add_method('GetInternalQueue', 
                   'ns3::Ptr< ns3::Queue >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetNBytes() const [member function]
    cls.add_method('GetNBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetNInternalQueues() const [member function]
    cls.add_method('GetNInternalQueues', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetNPacketFilters() const [member function]
    cls.add_method('GetNPacketFilters', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetNPackets() const [member function]
    cls.add_method('GetNPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetNQueueDiscClasses() const [member function]
    cls.add_method('GetNQueueDiscClasses', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::NetDevice> ns3::QueueDisc::GetNetDevice() const [member function]
    cls.add_method('GetNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::PacketFilter> ns3::QueueDisc::GetPacketFilter(uint32_t i) const [member function]
    cls.add_method('GetPacketFilter', 
                   'ns3::Ptr< ns3::PacketFilter >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::QueueDiscClass> ns3::QueueDisc::GetQueueDiscClass(uint32_t i) const [member function]
    cls.add_method('GetQueueDiscClass', 
                   'ns3::Ptr< ns3::QueueDiscClass >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetQuota() const [member function]
    cls.add_method('GetQuota', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetTotalDroppedBytes() const [member function]
    cls.add_method('GetTotalDroppedBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetTotalDroppedPackets() const [member function]
    cls.add_method('GetTotalDroppedPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetTotalReceivedBytes() const [member function]
    cls.add_method('GetTotalReceivedBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetTotalReceivedPackets() const [member function]
    cls.add_method('GetTotalReceivedPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetTotalRequeuedBytes() const [member function]
    cls.add_method('GetTotalRequeuedBytes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint32_t ns3::QueueDisc::GetTotalRequeuedPackets() const [member function]
    cls.add_method('GetTotalRequeuedPackets', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): static ns3::TypeId ns3::QueueDisc::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDisc::WakeMode ns3::QueueDisc::GetWakeMode() [member function]
    cls.add_method('GetWakeMode', 
                   'ns3::QueueDisc::WakeMode', 
                   [])
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<const ns3::QueueDiscItem> ns3::QueueDisc::Peek() const [member function]
    cls.add_method('Peek', 
                   'ns3::Ptr< ns3::QueueDiscItem const >', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::Run() [member function]
    cls.add_method('Run', 
                   'void', 
                   [])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::SetNetDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetNetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::SetParentDropCallback(ns3::Callback<void, ns3::Ptr<ns3::QueueItem>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetParentDropCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::QueueItem >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::SetQuota(uint32_t const quota) [member function]
    cls.add_method('SetQuota', 
                   'void', 
                   [param('uint32_t const', 'quota')], 
                   is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::DoInitialize() [member function]
    cls.add_method('DoInitialize', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::Drop(ns3::Ptr<ns3::QueueItem> item) [member function]
    cls.add_method('Drop', 
                   'void', 
                   [param('ns3::Ptr< ns3::QueueItem >', 'item')], 
                   visibility='protected')
    ## queue-disc.h (module 'traffic-control'): bool ns3::QueueDisc::CheckConfig() [member function]
    cls.add_method('CheckConfig', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::QueueDiscItem> ns3::QueueDisc::DoDequeue() [member function]
    cls.add_method('DoDequeue', 
                   'ns3::Ptr< ns3::QueueDiscItem >', 
                   [], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): bool ns3::QueueDisc::DoEnqueue(ns3::Ptr<ns3::QueueDiscItem> item) [member function]
    cls.add_method('DoEnqueue', 
                   'bool', 
                   [param('ns3::Ptr< ns3::QueueDiscItem >', 'item')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<const ns3::QueueDiscItem> ns3::QueueDisc::DoPeek() const [member function]
    cls.add_method('DoPeek', 
                   'ns3::Ptr< ns3::QueueDiscItem const >', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDisc::InitializeParams() [member function]
    cls.add_method('InitializeParams', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    return

def register_Ns3QueueDiscClass_methods(root_module, cls):
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDiscClass::QueueDiscClass(ns3::QueueDiscClass const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::QueueDiscClass const &', 'arg0')])
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDiscClass::QueueDiscClass() [constructor]
    cls.add_constructor([])
    ## queue-disc.h (module 'traffic-control'): ns3::Ptr<ns3::QueueDisc> ns3::QueueDiscClass::GetQueueDisc() const [member function]
    cls.add_method('GetQueueDisc', 
                   'ns3::Ptr< ns3::QueueDisc >', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): static ns3::TypeId ns3::QueueDiscClass::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDiscClass::SetQueueDisc(ns3::Ptr<ns3::QueueDisc> qd) [member function]
    cls.add_method('SetQueueDisc', 
                   'void', 
                   [param('ns3::Ptr< ns3::QueueDisc >', 'qd')])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDiscClass::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3RandomVariableStream_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::RandomVariableStream::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::RandomVariableStream::RandomVariableStream() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): void ns3::RandomVariableStream::SetStream(int64_t stream) [member function]
    cls.add_method('SetStream', 
                   'void', 
                   [param('int64_t', 'stream')])
    ## random-variable-stream.h (module 'core'): int64_t ns3::RandomVariableStream::GetStream() const [member function]
    cls.add_method('GetStream', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): void ns3::RandomVariableStream::SetAntithetic(bool isAntithetic) [member function]
    cls.add_method('SetAntithetic', 
                   'void', 
                   [param('bool', 'isAntithetic')])
    ## random-variable-stream.h (module 'core'): bool ns3::RandomVariableStream::IsAntithetic() const [member function]
    cls.add_method('IsAntithetic', 
                   'bool', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::RandomVariableStream::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::RandomVariableStream::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## random-variable-stream.h (module 'core'): ns3::RngStream * ns3::RandomVariableStream::Peek() const [member function]
    cls.add_method('Peek', 
                   'ns3::RngStream *', 
                   [], 
                   is_const=True, visibility='protected')
    return

def register_Ns3SequentialRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::SequentialRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::SequentialRandomVariable::SequentialRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::SequentialRandomVariable::GetMin() const [member function]
    cls.add_method('GetMin', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::SequentialRandomVariable::GetMax() const [member function]
    cls.add_method('GetMax', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): ns3::Ptr<ns3::RandomVariableStream> ns3::SequentialRandomVariable::GetIncrement() const [member function]
    cls.add_method('GetIncrement', 
                   'ns3::Ptr< ns3::RandomVariableStream >', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::SequentialRandomVariable::GetConsecutive() const [member function]
    cls.add_method('GetConsecutive', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::SequentialRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::SequentialRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeAccessor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter< ns3::AttributeAccessor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeChecker_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeChecker__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter< ns3::AttributeChecker > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3AttributeValue_Ns3Empty_Ns3DefaultDeleter__lt__ns3AttributeValue__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::SimpleRefCount(ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter< ns3::AttributeValue > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3CallbackImplBase_Ns3Empty_Ns3DefaultDeleter__lt__ns3CallbackImplBase__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::SimpleRefCount(ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter< ns3::CallbackImplBase > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3EventImpl_Ns3Empty_Ns3DefaultDeleter__lt__ns3EventImpl__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::SimpleRefCount(ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::EventImpl, ns3::empty, ns3::DefaultDeleter< ns3::EventImpl > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3HashImplementation_Ns3Empty_Ns3DefaultDeleter__lt__ns3HashImplementation__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter< ns3::Hash::Implementation > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3InterferenceHelperEvent_Ns3Empty_Ns3DefaultDeleter__lt__ns3InterferenceHelperEvent__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter<ns3::InterferenceHelper::Event> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter<ns3::InterferenceHelper::Event> >::SimpleRefCount(ns3::SimpleRefCount<ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter<ns3::InterferenceHelper::Event> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter< ns3::InterferenceHelper::Event > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::InterferenceHelper::Event, ns3::empty, ns3::DefaultDeleter<ns3::InterferenceHelper::Event> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Ipv4MulticastRoute_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4MulticastRoute__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter< ns3::Ipv4MulticastRoute > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Ipv4MulticastRoute, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4MulticastRoute> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Ipv4Route_Ns3Empty_Ns3DefaultDeleter__lt__ns3Ipv4Route__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter< ns3::Ipv4Route > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Ipv4Route, ns3::empty, ns3::DefaultDeleter<ns3::Ipv4Route> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3NetDeviceQueue_Ns3Empty_Ns3DefaultDeleter__lt__ns3NetDeviceQueue__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >::SimpleRefCount(ns3::SimpleRefCount<ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter< ns3::NetDeviceQueue > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::NetDeviceQueue, ns3::empty, ns3::DefaultDeleter<ns3::NetDeviceQueue> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3NixVector_Ns3Empty_Ns3DefaultDeleter__lt__ns3NixVector__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::SimpleRefCount(ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::NixVector, ns3::empty, ns3::DefaultDeleter< ns3::NixVector > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3OutputStreamWrapper_Ns3Empty_Ns3DefaultDeleter__lt__ns3OutputStreamWrapper__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >::SimpleRefCount(ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter< ns3::OutputStreamWrapper > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3Packet_Ns3Empty_Ns3DefaultDeleter__lt__ns3Packet__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::SimpleRefCount(ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::Packet, ns3::empty, ns3::DefaultDeleter< ns3::Packet > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3QueueItem_Ns3Empty_Ns3DefaultDeleter__lt__ns3QueueItem__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >::SimpleRefCount(ns3::SimpleRefCount<ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::QueueItem, ns3::empty, ns3::DefaultDeleter< ns3::QueueItem > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::QueueItem, ns3::empty, ns3::DefaultDeleter<ns3::QueueItem> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3TraceSourceAccessor_Ns3Empty_Ns3DefaultDeleter__lt__ns3TraceSourceAccessor__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::SimpleRefCount(ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter< ns3::TraceSourceAccessor > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3SimpleRefCount__Ns3WifiInformationElement_Ns3Empty_Ns3DefaultDeleter__lt__ns3WifiInformationElement__gt___methods(root_module, cls):
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> >::SimpleRefCount() [constructor]
    cls.add_constructor([])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> >::SimpleRefCount(ns3::SimpleRefCount<ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> > const & o) [copy constructor]
    cls.add_constructor([param('ns3::SimpleRefCount< ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter< ns3::WifiInformationElement > > const &', 'o')])
    ## simple-ref-count.h (module 'core'): static void ns3::SimpleRefCount<ns3::WifiInformationElement, ns3::empty, ns3::DefaultDeleter<ns3::WifiInformationElement> >::Cleanup() [member function]
    cls.add_method('Cleanup', 
                   'void', 
                   [], 
                   is_static=True)
    return

def register_Ns3Socket_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::Socket::Socket(ns3::Socket const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Socket const &', 'arg0')])
    ## socket.h (module 'network'): ns3::Socket::Socket() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): int ns3::Socket::Bind(ns3::Address const & address) [member function]
    cls.add_method('Bind', 
                   'int', 
                   [param('ns3::Address const &', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Bind() [member function]
    cls.add_method('Bind', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Bind6() [member function]
    cls.add_method('Bind6', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::BindToNetDevice(ns3::Ptr<ns3::NetDevice> netdevice) [member function]
    cls.add_method('BindToNetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'netdevice')], 
                   is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Close() [member function]
    cls.add_method('Close', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Connect(ns3::Address const & address) [member function]
    cls.add_method('Connect', 
                   'int', 
                   [param('ns3::Address const &', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::Ptr<ns3::Socket> ns3::Socket::CreateSocket(ns3::Ptr<ns3::Node> node, ns3::TypeId tid) [member function]
    cls.add_method('CreateSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [param('ns3::Ptr< ns3::Node >', 'node'), param('ns3::TypeId', 'tid')], 
                   is_static=True)
    ## socket.h (module 'network'): bool ns3::Socket::GetAllowBroadcast() const [member function]
    cls.add_method('GetAllowBroadcast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Socket::GetBoundNetDevice() [member function]
    cls.add_method('GetBoundNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [])
    ## socket.h (module 'network'): ns3::Socket::SocketErrno ns3::Socket::GetErrno() const [member function]
    cls.add_method('GetErrno', 
                   'ns3::Socket::SocketErrno', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::Socket::GetIpTos() const [member function]
    cls.add_method('GetIpTos', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): uint8_t ns3::Socket::GetIpTtl() const [member function]
    cls.add_method('GetIpTtl', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::Socket::GetIpv6HopLimit() const [member function]
    cls.add_method('GetIpv6HopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::Socket::GetIpv6Tclass() const [member function]
    cls.add_method('GetIpv6Tclass', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Node> ns3::Socket::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::GetPeerName(ns3::Address & address) const [member function]
    cls.add_method('GetPeerName', 
                   'int', 
                   [param('ns3::Address &', 'address')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::Socket::GetPriority() const [member function]
    cls.add_method('GetPriority', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): uint32_t ns3::Socket::GetRxAvailable() const [member function]
    cls.add_method('GetRxAvailable', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::GetSockName(ns3::Address & address) const [member function]
    cls.add_method('GetSockName', 
                   'int', 
                   [param('ns3::Address &', 'address')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Socket::SocketType ns3::Socket::GetSocketType() const [member function]
    cls.add_method('GetSocketType', 
                   'ns3::Socket::SocketType', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::Socket::GetTxAvailable() const [member function]
    cls.add_method('GetTxAvailable', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::Socket::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): static uint8_t ns3::Socket::IpTos2Priority(uint8_t ipTos) [member function]
    cls.add_method('IpTos2Priority', 
                   'uint8_t', 
                   [param('uint8_t', 'ipTos')], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::Socket::Ipv6JoinGroup(ns3::Ipv6Address address, ns3::Socket::Ipv6MulticastFilterMode filterMode, std::vector<ns3::Ipv6Address,std::allocator<ns3::Ipv6Address> > sourceAddresses) [member function]
    cls.add_method('Ipv6JoinGroup', 
                   'void', 
                   [param('ns3::Ipv6Address', 'address'), param('ns3::Socket::Ipv6MulticastFilterMode', 'filterMode'), param('std::vector< ns3::Ipv6Address >', 'sourceAddresses')], 
                   is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::Ipv6JoinGroup(ns3::Ipv6Address address) [member function]
    cls.add_method('Ipv6JoinGroup', 
                   'void', 
                   [param('ns3::Ipv6Address', 'address')], 
                   is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::Ipv6LeaveGroup() [member function]
    cls.add_method('Ipv6LeaveGroup', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsIpRecvTos() const [member function]
    cls.add_method('IsIpRecvTos', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsIpRecvTtl() const [member function]
    cls.add_method('IsIpRecvTtl', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsIpv6RecvHopLimit() const [member function]
    cls.add_method('IsIpv6RecvHopLimit', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsIpv6RecvTclass() const [member function]
    cls.add_method('IsIpv6RecvTclass', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsRecvPktInfo() const [member function]
    cls.add_method('IsRecvPktInfo', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): int ns3::Socket::Listen() [member function]
    cls.add_method('Listen', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::Recv(uint32_t maxSize, uint32_t flags) [member function]
    cls.add_method('Recv', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'maxSize'), param('uint32_t', 'flags')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::Recv() [member function]
    cls.add_method('Recv', 
                   'ns3::Ptr< ns3::Packet >', 
                   [])
    ## socket.h (module 'network'): int ns3::Socket::Recv(uint8_t * buf, uint32_t size, uint32_t flags) [member function]
    cls.add_method('Recv', 
                   'int', 
                   [param('uint8_t *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags')])
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::RecvFrom(uint32_t maxSize, uint32_t flags, ns3::Address & fromAddress) [member function]
    cls.add_method('RecvFrom', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'maxSize'), param('uint32_t', 'flags'), param('ns3::Address &', 'fromAddress')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Socket::RecvFrom(ns3::Address & fromAddress) [member function]
    cls.add_method('RecvFrom', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('ns3::Address &', 'fromAddress')])
    ## socket.h (module 'network'): int ns3::Socket::RecvFrom(uint8_t * buf, uint32_t size, uint32_t flags, ns3::Address & fromAddress) [member function]
    cls.add_method('RecvFrom', 
                   'int', 
                   [param('uint8_t *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags'), param('ns3::Address &', 'fromAddress')])
    ## socket.h (module 'network'): int ns3::Socket::Send(ns3::Ptr<ns3::Packet> p, uint32_t flags) [member function]
    cls.add_method('Send', 
                   'int', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('uint32_t', 'flags')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::Send(ns3::Ptr<ns3::Packet> p) [member function]
    cls.add_method('Send', 
                   'int', 
                   [param('ns3::Ptr< ns3::Packet >', 'p')])
    ## socket.h (module 'network'): int ns3::Socket::Send(uint8_t const * buf, uint32_t size, uint32_t flags) [member function]
    cls.add_method('Send', 
                   'int', 
                   [param('uint8_t const *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags')])
    ## socket.h (module 'network'): int ns3::Socket::SendTo(ns3::Ptr<ns3::Packet> p, uint32_t flags, ns3::Address const & toAddress) [member function]
    cls.add_method('SendTo', 
                   'int', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('uint32_t', 'flags'), param('ns3::Address const &', 'toAddress')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::SendTo(uint8_t const * buf, uint32_t size, uint32_t flags, ns3::Address const & address) [member function]
    cls.add_method('SendTo', 
                   'int', 
                   [param('uint8_t const *', 'buf'), param('uint32_t', 'size'), param('uint32_t', 'flags'), param('ns3::Address const &', 'address')])
    ## socket.h (module 'network'): void ns3::Socket::SetAcceptCallback(ns3::Callback<bool, ns3::Ptr<ns3::Socket>, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> connectionRequest, ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::Address const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> newConnectionCreated) [member function]
    cls.add_method('SetAcceptCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::Socket >, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'connectionRequest'), param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'newConnectionCreated')])
    ## socket.h (module 'network'): bool ns3::Socket::SetAllowBroadcast(bool allowBroadcast) [member function]
    cls.add_method('SetAllowBroadcast', 
                   'bool', 
                   [param('bool', 'allowBroadcast')], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::SetCloseCallbacks(ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> normalClose, ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> errorClose) [member function]
    cls.add_method('SetCloseCallbacks', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'normalClose'), param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'errorClose')])
    ## socket.h (module 'network'): void ns3::Socket::SetConnectCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> connectionSucceeded, ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> connectionFailed) [member function]
    cls.add_method('SetConnectCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'connectionSucceeded'), param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'connectionFailed')])
    ## socket.h (module 'network'): void ns3::Socket::SetDataSentCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> dataSent) [member function]
    cls.add_method('SetDataSentCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'dataSent')])
    ## socket.h (module 'network'): void ns3::Socket::SetIpRecvTos(bool ipv4RecvTos) [member function]
    cls.add_method('SetIpRecvTos', 
                   'void', 
                   [param('bool', 'ipv4RecvTos')])
    ## socket.h (module 'network'): void ns3::Socket::SetIpRecvTtl(bool ipv4RecvTtl) [member function]
    cls.add_method('SetIpRecvTtl', 
                   'void', 
                   [param('bool', 'ipv4RecvTtl')])
    ## socket.h (module 'network'): void ns3::Socket::SetIpTos(uint8_t ipTos) [member function]
    cls.add_method('SetIpTos', 
                   'void', 
                   [param('uint8_t', 'ipTos')])
    ## socket.h (module 'network'): void ns3::Socket::SetIpTtl(uint8_t ipTtl) [member function]
    cls.add_method('SetIpTtl', 
                   'void', 
                   [param('uint8_t', 'ipTtl')], 
                   is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::SetIpv6HopLimit(uint8_t ipHopLimit) [member function]
    cls.add_method('SetIpv6HopLimit', 
                   'void', 
                   [param('uint8_t', 'ipHopLimit')], 
                   is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::SetIpv6RecvHopLimit(bool ipv6RecvHopLimit) [member function]
    cls.add_method('SetIpv6RecvHopLimit', 
                   'void', 
                   [param('bool', 'ipv6RecvHopLimit')])
    ## socket.h (module 'network'): void ns3::Socket::SetIpv6RecvTclass(bool ipv6RecvTclass) [member function]
    cls.add_method('SetIpv6RecvTclass', 
                   'void', 
                   [param('bool', 'ipv6RecvTclass')])
    ## socket.h (module 'network'): void ns3::Socket::SetIpv6Tclass(int ipTclass) [member function]
    cls.add_method('SetIpv6Tclass', 
                   'void', 
                   [param('int', 'ipTclass')])
    ## socket.h (module 'network'): void ns3::Socket::SetPriority(uint8_t priority) [member function]
    cls.add_method('SetPriority', 
                   'void', 
                   [param('uint8_t', 'priority')])
    ## socket.h (module 'network'): void ns3::Socket::SetRecvCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> arg0) [member function]
    cls.add_method('SetRecvCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'arg0')])
    ## socket.h (module 'network'): void ns3::Socket::SetRecvPktInfo(bool flag) [member function]
    cls.add_method('SetRecvPktInfo', 
                   'void', 
                   [param('bool', 'flag')])
    ## socket.h (module 'network'): void ns3::Socket::SetSendCallback(ns3::Callback<void, ns3::Ptr<ns3::Socket>, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> sendCb) [member function]
    cls.add_method('SetSendCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Socket >, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'sendCb')])
    ## socket.h (module 'network'): int ns3::Socket::ShutdownRecv() [member function]
    cls.add_method('ShutdownRecv', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): int ns3::Socket::ShutdownSend() [member function]
    cls.add_method('ShutdownSend', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::Socket::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## socket.h (module 'network'): bool ns3::Socket::IsManualIpTtl() const [member function]
    cls.add_method('IsManualIpTtl', 
                   'bool', 
                   [], 
                   is_const=True, visibility='protected')
    ## socket.h (module 'network'): bool ns3::Socket::IsManualIpv6HopLimit() const [member function]
    cls.add_method('IsManualIpv6HopLimit', 
                   'bool', 
                   [], 
                   is_const=True, visibility='protected')
    ## socket.h (module 'network'): bool ns3::Socket::IsManualIpv6Tclass() const [member function]
    cls.add_method('IsManualIpv6Tclass', 
                   'bool', 
                   [], 
                   is_const=True, visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyConnectionFailed() [member function]
    cls.add_method('NotifyConnectionFailed', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): bool ns3::Socket::NotifyConnectionRequest(ns3::Address const & from) [member function]
    cls.add_method('NotifyConnectionRequest', 
                   'bool', 
                   [param('ns3::Address const &', 'from')], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyConnectionSucceeded() [member function]
    cls.add_method('NotifyConnectionSucceeded', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyDataRecv() [member function]
    cls.add_method('NotifyDataRecv', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyDataSent(uint32_t size) [member function]
    cls.add_method('NotifyDataSent', 
                   'void', 
                   [param('uint32_t', 'size')], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyErrorClose() [member function]
    cls.add_method('NotifyErrorClose', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyNewConnectionCreated(ns3::Ptr<ns3::Socket> socket, ns3::Address const & from) [member function]
    cls.add_method('NotifyNewConnectionCreated', 
                   'void', 
                   [param('ns3::Ptr< ns3::Socket >', 'socket'), param('ns3::Address const &', 'from')], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifyNormalClose() [member function]
    cls.add_method('NotifyNormalClose', 
                   'void', 
                   [], 
                   visibility='protected')
    ## socket.h (module 'network'): void ns3::Socket::NotifySend(uint32_t spaceAvailable) [member function]
    cls.add_method('NotifySend', 
                   'void', 
                   [param('uint32_t', 'spaceAvailable')], 
                   visibility='protected')
    return

def register_Ns3SocketIpTosTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketIpTosTag::SocketIpTosTag(ns3::SocketIpTosTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketIpTosTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketIpTosTag::SocketIpTosTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketIpTosTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketIpTosTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketIpTosTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::SocketIpTosTag::GetTos() const [member function]
    cls.add_method('GetTos', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketIpTosTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketIpTosTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpTosTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpTosTag::SetTos(uint8_t tos) [member function]
    cls.add_method('SetTos', 
                   'void', 
                   [param('uint8_t', 'tos')])
    return

def register_Ns3SocketIpTtlTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketIpTtlTag::SocketIpTtlTag(ns3::SocketIpTtlTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketIpTtlTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketIpTtlTag::SocketIpTtlTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketIpTtlTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketIpTtlTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::SocketIpTtlTag::GetTtl() const [member function]
    cls.add_method('GetTtl', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketIpTtlTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpTtlTag::SetTtl(uint8_t ttl) [member function]
    cls.add_method('SetTtl', 
                   'void', 
                   [param('uint8_t', 'ttl')])
    return

def register_Ns3SocketIpv6HopLimitTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketIpv6HopLimitTag::SocketIpv6HopLimitTag(ns3::SocketIpv6HopLimitTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketIpv6HopLimitTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketIpv6HopLimitTag::SocketIpv6HopLimitTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketIpv6HopLimitTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::SocketIpv6HopLimitTag::GetHopLimit() const [member function]
    cls.add_method('GetHopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketIpv6HopLimitTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketIpv6HopLimitTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketIpv6HopLimitTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketIpv6HopLimitTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpv6HopLimitTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpv6HopLimitTag::SetHopLimit(uint8_t hopLimit) [member function]
    cls.add_method('SetHopLimit', 
                   'void', 
                   [param('uint8_t', 'hopLimit')])
    return

def register_Ns3SocketIpv6TclassTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketIpv6TclassTag::SocketIpv6TclassTag(ns3::SocketIpv6TclassTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketIpv6TclassTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketIpv6TclassTag::SocketIpv6TclassTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketIpv6TclassTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketIpv6TclassTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketIpv6TclassTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::SocketIpv6TclassTag::GetTclass() const [member function]
    cls.add_method('GetTclass', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketIpv6TclassTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketIpv6TclassTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpv6TclassTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketIpv6TclassTag::SetTclass(uint8_t tclass) [member function]
    cls.add_method('SetTclass', 
                   'void', 
                   [param('uint8_t', 'tclass')])
    return

def register_Ns3SocketPriorityTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketPriorityTag::SocketPriorityTag(ns3::SocketPriorityTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketPriorityTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketPriorityTag::SocketPriorityTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketPriorityTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketPriorityTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint8_t ns3::SocketPriorityTag::GetPriority() const [member function]
    cls.add_method('GetPriority', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketPriorityTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketPriorityTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): void ns3::SocketPriorityTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketPriorityTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketPriorityTag::SetPriority(uint8_t priority) [member function]
    cls.add_method('SetPriority', 
                   'void', 
                   [param('uint8_t', 'priority')])
    return

def register_Ns3SocketSetDontFragmentTag_methods(root_module, cls):
    ## socket.h (module 'network'): ns3::SocketSetDontFragmentTag::SocketSetDontFragmentTag(ns3::SocketSetDontFragmentTag const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SocketSetDontFragmentTag const &', 'arg0')])
    ## socket.h (module 'network'): ns3::SocketSetDontFragmentTag::SocketSetDontFragmentTag() [constructor]
    cls.add_constructor([])
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Deserialize(ns3::TagBuffer i) [member function]
    cls.add_method('Deserialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Disable() [member function]
    cls.add_method('Disable', 
                   'void', 
                   [])
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Enable() [member function]
    cls.add_method('Enable', 
                   'void', 
                   [])
    ## socket.h (module 'network'): ns3::TypeId ns3::SocketSetDontFragmentTag::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): uint32_t ns3::SocketSetDontFragmentTag::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): static ns3::TypeId ns3::SocketSetDontFragmentTag::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## socket.h (module 'network'): bool ns3::SocketSetDontFragmentTag::IsEnabled() const [member function]
    cls.add_method('IsEnabled', 
                   'bool', 
                   [], 
                   is_const=True)
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## socket.h (module 'network'): void ns3::SocketSetDontFragmentTag::Serialize(ns3::TagBuffer i) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::TagBuffer', 'i')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3Time_methods(root_module, cls):
    cls.add_binary_comparison_operator('<=')
    cls.add_binary_comparison_operator('!=')
    cls.add_inplace_numeric_operator('+=', param('ns3::Time const &', u'right'))
    cls.add_binary_numeric_operator('*', root_module['ns3::Time'], root_module['ns3::Time'], param('int64_t const &', u'right'))
    cls.add_binary_numeric_operator('+', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', u'right'))
    cls.add_binary_numeric_operator('-', root_module['ns3::Time'], root_module['ns3::Time'], param('ns3::Time const &', u'right'))
    cls.add_binary_numeric_operator('/', root_module['ns3::Time'], root_module['ns3::Time'], param('int64_t const &', u'right'))
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('>')
    cls.add_inplace_numeric_operator('-=', param('ns3::Time const &', u'right'))
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    cls.add_binary_comparison_operator('>=')
    ## nstime.h (module 'core'): ns3::Time::Time() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::Time::Time(ns3::Time const & o) [copy constructor]
    cls.add_constructor([param('ns3::Time const &', 'o')])
    ## nstime.h (module 'core'): ns3::Time::Time(double v) [constructor]
    cls.add_constructor([param('double', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(int v) [constructor]
    cls.add_constructor([param('int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long int v) [constructor]
    cls.add_constructor([param('long int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long long int v) [constructor]
    cls.add_constructor([param('long long int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(unsigned int v) [constructor]
    cls.add_constructor([param('unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long unsigned int v) [constructor]
    cls.add_constructor([param('long unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(long long unsigned int v) [constructor]
    cls.add_constructor([param('long long unsigned int', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(ns3::int64x64_t const & v) [constructor]
    cls.add_constructor([param('ns3::int64x64_t const &', 'v')])
    ## nstime.h (module 'core'): ns3::Time::Time(std::string const & s) [constructor]
    cls.add_constructor([param('std::string const &', 's')])
    ## nstime.h (module 'core'): ns3::TimeWithUnit ns3::Time::As(ns3::Time::Unit const unit) const [member function]
    cls.add_method('As', 
                   'ns3::TimeWithUnit', 
                   [param('ns3::Time::Unit const', 'unit')], 
                   is_const=True)
    ## nstime.h (module 'core'): int ns3::Time::Compare(ns3::Time const & o) const [member function]
    cls.add_method('Compare', 
                   'int', 
                   [param('ns3::Time const &', 'o')], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::From(ns3::int64x64_t const & value) [member function]
    cls.add_method('From', 
                   'ns3::Time', 
                   [param('ns3::int64x64_t const &', 'value')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::From(ns3::int64x64_t const & value, ns3::Time::Unit unit) [member function]
    cls.add_method('From', 
                   'ns3::Time', 
                   [param('ns3::int64x64_t const &', 'value'), param('ns3::Time::Unit', 'unit')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::FromDouble(double value, ns3::Time::Unit unit) [member function]
    cls.add_method('FromDouble', 
                   'ns3::Time', 
                   [param('double', 'value'), param('ns3::Time::Unit', 'unit')], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::FromInteger(uint64_t value, ns3::Time::Unit unit) [member function]
    cls.add_method('FromInteger', 
                   'ns3::Time', 
                   [param('uint64_t', 'value'), param('ns3::Time::Unit', 'unit')], 
                   is_static=True)
    ## nstime.h (module 'core'): double ns3::Time::GetDays() const [member function]
    cls.add_method('GetDays', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::GetDouble() const [member function]
    cls.add_method('GetDouble', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetFemtoSeconds() const [member function]
    cls.add_method('GetFemtoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::GetHours() const [member function]
    cls.add_method('GetHours', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetInteger() const [member function]
    cls.add_method('GetInteger', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetMicroSeconds() const [member function]
    cls.add_method('GetMicroSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetMilliSeconds() const [member function]
    cls.add_method('GetMilliSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::GetMinutes() const [member function]
    cls.add_method('GetMinutes', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetNanoSeconds() const [member function]
    cls.add_method('GetNanoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetPicoSeconds() const [member function]
    cls.add_method('GetPicoSeconds', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time::Unit ns3::Time::GetResolution() [member function]
    cls.add_method('GetResolution', 
                   'ns3::Time::Unit', 
                   [], 
                   is_static=True)
    ## nstime.h (module 'core'): double ns3::Time::GetSeconds() const [member function]
    cls.add_method('GetSeconds', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::GetTimeStep() const [member function]
    cls.add_method('GetTimeStep', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::GetYears() const [member function]
    cls.add_method('GetYears', 
                   'double', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsNegative() const [member function]
    cls.add_method('IsNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsPositive() const [member function]
    cls.add_method('IsPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsStrictlyNegative() const [member function]
    cls.add_method('IsStrictlyNegative', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsStrictlyPositive() const [member function]
    cls.add_method('IsStrictlyPositive', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): bool ns3::Time::IsZero() const [member function]
    cls.add_method('IsZero', 
                   'bool', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::Max() [member function]
    cls.add_method('Max', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## nstime.h (module 'core'): static ns3::Time ns3::Time::Min() [member function]
    cls.add_method('Min', 
                   'ns3::Time', 
                   [], 
                   is_static=True)
    ## nstime.h (module 'core'): static void ns3::Time::SetResolution(ns3::Time::Unit resolution) [member function]
    cls.add_method('SetResolution', 
                   'void', 
                   [param('ns3::Time::Unit', 'resolution')], 
                   is_static=True)
    ## nstime.h (module 'core'): static bool ns3::Time::StaticInit() [member function]
    cls.add_method('StaticInit', 
                   'bool', 
                   [], 
                   is_static=True)
    ## nstime.h (module 'core'): ns3::int64x64_t ns3::Time::To(ns3::Time::Unit unit) const [member function]
    cls.add_method('To', 
                   'ns3::int64x64_t', 
                   [param('ns3::Time::Unit', 'unit')], 
                   is_const=True)
    ## nstime.h (module 'core'): double ns3::Time::ToDouble(ns3::Time::Unit unit) const [member function]
    cls.add_method('ToDouble', 
                   'double', 
                   [param('ns3::Time::Unit', 'unit')], 
                   is_const=True)
    ## nstime.h (module 'core'): int64_t ns3::Time::ToInteger(ns3::Time::Unit unit) const [member function]
    cls.add_method('ToInteger', 
                   'int64_t', 
                   [param('ns3::Time::Unit', 'unit')], 
                   is_const=True)
    return

def register_Ns3TraceSourceAccessor_methods(root_module, cls):
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor::TraceSourceAccessor(ns3::TraceSourceAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TraceSourceAccessor const &', 'arg0')])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor::TraceSourceAccessor() [constructor]
    cls.add_constructor([])
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::Connect(ns3::ObjectBase * obj, std::string context, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('Connect', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::ConnectWithoutContext(ns3::ObjectBase * obj, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('ConnectWithoutContext', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::Disconnect(ns3::ObjectBase * obj, std::string context, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('Disconnect', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('std::string', 'context'), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trace-source-accessor.h (module 'core'): bool ns3::TraceSourceAccessor::DisconnectWithoutContext(ns3::ObjectBase * obj, ns3::CallbackBase const & cb) const [member function]
    cls.add_method('DisconnectWithoutContext', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'obj', transfer_ownership=False), param('ns3::CallbackBase const &', 'cb')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3TrafficControlLayer_methods(root_module, cls):
    ## traffic-control-layer.h (module 'traffic-control'): ns3::TrafficControlLayer::TrafficControlLayer() [constructor]
    cls.add_constructor([])
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::DeleteRootQueueDiscOnDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('DeleteRootQueueDiscOnDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): ns3::TypeId ns3::TrafficControlLayer::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): ns3::Ptr<ns3::QueueDisc> ns3::TrafficControlLayer::GetRootQueueDiscOnDevice(ns3::Ptr<ns3::NetDevice> device) const [member function]
    cls.add_method('GetRootQueueDiscOnDevice', 
                   'ns3::Ptr< ns3::QueueDisc >', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_const=True, is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): static ns3::TypeId ns3::TrafficControlLayer::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::Receive(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::Packet const> p, uint16_t protocol, ns3::Address const & from, ns3::Address const & to, ns3::NetDevice::PacketType packetType) [member function]
    cls.add_method('Receive', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint16_t', 'protocol'), param('ns3::Address const &', 'from'), param('ns3::Address const &', 'to'), param('ns3::NetDevice::PacketType', 'packetType')], 
                   is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::RegisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler, uint16_t protocolType, ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('RegisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler'), param('uint16_t', 'protocolType'), param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::Send(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::QueueDiscItem> item) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::QueueDiscItem >', 'item')], 
                   is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::SetRootQueueDiscOnDevice(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::QueueDisc> qDisc) [member function]
    cls.add_method('SetRootQueueDiscOnDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::QueueDisc >', 'qDisc')], 
                   is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::SetupDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetupDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::DoInitialize() [member function]
    cls.add_method('DoInitialize', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## traffic-control-layer.h (module 'traffic-control'): void ns3::TrafficControlLayer::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3Trailer_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## trailer.h (module 'network'): ns3::Trailer::Trailer() [constructor]
    cls.add_constructor([])
    ## trailer.h (module 'network'): ns3::Trailer::Trailer(ns3::Trailer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Trailer const &', 'arg0')])
    ## trailer.h (module 'network'): uint32_t ns3::Trailer::Deserialize(ns3::Buffer::Iterator end) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'end')], 
                   is_pure_virtual=True, is_virtual=True)
    ## trailer.h (module 'network'): uint32_t ns3::Trailer::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trailer.h (module 'network'): static ns3::TypeId ns3::Trailer::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## trailer.h (module 'network'): void ns3::Trailer::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## trailer.h (module 'network'): void ns3::Trailer::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3TriangularRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::TriangularRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::TriangularRandomVariable::TriangularRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetMin() const [member function]
    cls.add_method('GetMin', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetMax() const [member function]
    cls.add_method('GetMax', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetValue(double mean, double min, double max) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'min'), param('double', 'max')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::TriangularRandomVariable::GetInteger(uint32_t mean, uint32_t min, uint32_t max) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'min'), param('uint32_t', 'max')])
    ## random-variable-stream.h (module 'core'): double ns3::TriangularRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::TriangularRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3UniformRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::UniformRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::UniformRandomVariable::UniformRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetMin() const [member function]
    cls.add_method('GetMin', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetMax() const [member function]
    cls.add_method('GetMax', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetValue(double min, double max) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'min'), param('double', 'max')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::UniformRandomVariable::GetInteger(uint32_t min, uint32_t max) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'min'), param('uint32_t', 'max')])
    ## random-variable-stream.h (module 'core'): double ns3::UniformRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::UniformRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3WeibullRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::WeibullRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::WeibullRandomVariable::WeibullRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetScale() const [member function]
    cls.add_method('GetScale', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetShape() const [member function]
    cls.add_method('GetShape', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetValue(double scale, double shape, double bound) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'scale'), param('double', 'shape'), param('double', 'bound')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::WeibullRandomVariable::GetInteger(uint32_t scale, uint32_t shape, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'scale'), param('uint32_t', 'shape'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::WeibullRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::WeibullRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3WifiInformationElement_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    cls.add_binary_comparison_operator('==')
    ## wifi-information-element.h (module 'wifi'): ns3::WifiInformationElement::WifiInformationElement() [constructor]
    cls.add_constructor([])
    ## wifi-information-element.h (module 'wifi'): ns3::WifiInformationElement::WifiInformationElement(ns3::WifiInformationElement const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiInformationElement const &', 'arg0')])
    ## wifi-information-element.h (module 'wifi'): ns3::Buffer::Iterator ns3::WifiInformationElement::Deserialize(ns3::Buffer::Iterator i) [member function]
    cls.add_method('Deserialize', 
                   'ns3::Buffer::Iterator', 
                   [param('ns3::Buffer::Iterator', 'i')])
    ## wifi-information-element.h (module 'wifi'): ns3::Buffer::Iterator ns3::WifiInformationElement::DeserializeIfPresent(ns3::Buffer::Iterator i) [member function]
    cls.add_method('DeserializeIfPresent', 
                   'ns3::Buffer::Iterator', 
                   [param('ns3::Buffer::Iterator', 'i')])
    ## wifi-information-element.h (module 'wifi'): uint8_t ns3::WifiInformationElement::DeserializeInformationField(ns3::Buffer::Iterator start, uint8_t length) [member function]
    cls.add_method('DeserializeInformationField', 
                   'uint8_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint8_t', 'length')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-information-element.h (module 'wifi'): ns3::WifiInformationElementId ns3::WifiInformationElement::ElementId() const [member function]
    cls.add_method('ElementId', 
                   'ns3::WifiInformationElementId', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-information-element.h (module 'wifi'): uint8_t ns3::WifiInformationElement::GetInformationFieldSize() const [member function]
    cls.add_method('GetInformationFieldSize', 
                   'uint8_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-information-element.h (module 'wifi'): uint16_t ns3::WifiInformationElement::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-information-element.h (module 'wifi'): void ns3::WifiInformationElement::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## wifi-information-element.h (module 'wifi'): ns3::Buffer::Iterator ns3::WifiInformationElement::Serialize(ns3::Buffer::Iterator i) const [member function]
    cls.add_method('Serialize', 
                   'ns3::Buffer::Iterator', 
                   [param('ns3::Buffer::Iterator', 'i')], 
                   is_const=True)
    ## wifi-information-element.h (module 'wifi'): void ns3::WifiInformationElement::SerializeInformationField(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('SerializeInformationField', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3WifiMac_methods(root_module, cls):
    ## wifi-mac.h (module 'wifi'): ns3::WifiMac::WifiMac() [constructor]
    cls.add_constructor([])
    ## wifi-mac.h (module 'wifi'): ns3::WifiMac::WifiMac(ns3::WifiMac const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiMac const &', 'arg0')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::ConfigureStandard(ns3::WifiPhyStandard standard) [member function]
    cls.add_method('ConfigureStandard', 
                   'void', 
                   [param('ns3::WifiPhyStandard', 'standard')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::Enqueue(ns3::Ptr<ns3::Packet const> packet, ns3::Mac48Address to, ns3::Mac48Address from) [member function]
    cls.add_method('Enqueue', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::Mac48Address', 'to'), param('ns3::Mac48Address', 'from')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::Enqueue(ns3::Ptr<ns3::Packet const> packet, ns3::Mac48Address to) [member function]
    cls.add_method('Enqueue', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::Mac48Address', 'to')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetAckTimeout() const [member function]
    cls.add_method('GetAckTimeout', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Mac48Address ns3::WifiMac::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Mac48Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetBasicBlockAckTimeout() const [member function]
    cls.add_method('GetBasicBlockAckTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Mac48Address ns3::WifiMac::GetBssid() const [member function]
    cls.add_method('GetBssid', 
                   'ns3::Mac48Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetCompressedBlockAckTimeout() const [member function]
    cls.add_method('GetCompressedBlockAckTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetCtsTimeout() const [member function]
    cls.add_method('GetCtsTimeout', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetEifsNoDifs() const [member function]
    cls.add_method('GetEifsNoDifs', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetMaxPropagationDelay() const [member function]
    cls.add_method('GetMaxPropagationDelay', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetMsduLifetime() const [member function]
    cls.add_method('GetMsduLifetime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetPifs() const [member function]
    cls.add_method('GetPifs', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetRifs() const [member function]
    cls.add_method('GetRifs', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): bool ns3::WifiMac::GetShortSlotTimeSupported() const [member function]
    cls.add_method('GetShortSlotTimeSupported', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetSifs() const [member function]
    cls.add_method('GetSifs', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Time ns3::WifiMac::GetSlot() const [member function]
    cls.add_method('GetSlot', 
                   'ns3::Time', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Ssid ns3::WifiMac::GetSsid() const [member function]
    cls.add_method('GetSsid', 
                   'ns3::Ssid', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): static ns3::TypeId ns3::WifiMac::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## wifi-mac.h (module 'wifi'): ns3::Ptr<ns3::WifiPhy> ns3::WifiMac::GetWifiPhy() const [member function]
    cls.add_method('GetWifiPhy', 
                   'ns3::Ptr< ns3::WifiPhy >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): ns3::Ptr<ns3::WifiRemoteStationManager> ns3::WifiMac::GetWifiRemoteStationManager() const [member function]
    cls.add_method('GetWifiRemoteStationManager', 
                   'ns3::Ptr< ns3::WifiRemoteStationManager >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::NotifyPromiscRx(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyPromiscRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::NotifyRx(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::NotifyRxDrop(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyRxDrop', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::NotifyTx(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyTx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::NotifyTxDrop(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyTxDrop', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::ResetWifiPhy() [member function]
    cls.add_method('ResetWifiPhy', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetAckTimeout(ns3::Time ackTimeout) [member function]
    cls.add_method('SetAckTimeout', 
                   'void', 
                   [param('ns3::Time', 'ackTimeout')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetAddress(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetBasicBlockAckTimeout(ns3::Time blockAckTimeout) [member function]
    cls.add_method('SetBasicBlockAckTimeout', 
                   'void', 
                   [param('ns3::Time', 'blockAckTimeout')], 
                   is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetCompressedBlockAckTimeout(ns3::Time blockAckTimeout) [member function]
    cls.add_method('SetCompressedBlockAckTimeout', 
                   'void', 
                   [param('ns3::Time', 'blockAckTimeout')], 
                   is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetCtsTimeout(ns3::Time ctsTimeout) [member function]
    cls.add_method('SetCtsTimeout', 
                   'void', 
                   [param('ns3::Time', 'ctsTimeout')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetEifsNoDifs(ns3::Time eifsNoDifs) [member function]
    cls.add_method('SetEifsNoDifs', 
                   'void', 
                   [param('ns3::Time', 'eifsNoDifs')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetForwardUpCallback(ns3::Callback<void,ns3::Ptr<ns3::Packet>,ns3::Mac48Address,ns3::Mac48Address,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> upCallback) [member function]
    cls.add_method('SetForwardUpCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Mac48Address, ns3::Mac48Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'upCallback')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetLinkDownCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> linkDown) [member function]
    cls.add_method('SetLinkDownCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'linkDown')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetLinkUpCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> linkUp) [member function]
    cls.add_method('SetLinkUpCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'linkUp')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetMaxPropagationDelay(ns3::Time delay) [member function]
    cls.add_method('SetMaxPropagationDelay', 
                   'void', 
                   [param('ns3::Time', 'delay')])
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetPifs(ns3::Time pifs) [member function]
    cls.add_method('SetPifs', 
                   'void', 
                   [param('ns3::Time', 'pifs')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetPromisc() [member function]
    cls.add_method('SetPromisc', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetRifs(ns3::Time rifs) [member function]
    cls.add_method('SetRifs', 
                   'void', 
                   [param('ns3::Time', 'rifs')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetShortSlotTimeSupported(bool enable) [member function]
    cls.add_method('SetShortSlotTimeSupported', 
                   'void', 
                   [param('bool', 'enable')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetSifs(ns3::Time sifs) [member function]
    cls.add_method('SetSifs', 
                   'void', 
                   [param('ns3::Time', 'sifs')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetSlot(ns3::Time slotTime) [member function]
    cls.add_method('SetSlot', 
                   'void', 
                   [param('ns3::Time', 'slotTime')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetSsid(ns3::Ssid ssid) [member function]
    cls.add_method('SetSsid', 
                   'void', 
                   [param('ns3::Ssid', 'ssid')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetWifiPhy(ns3::Ptr<ns3::WifiPhy> phy) [member function]
    cls.add_method('SetWifiPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::WifiPhy >', 'phy')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::SetWifiRemoteStationManager(ns3::Ptr<ns3::WifiRemoteStationManager> stationManager) [member function]
    cls.add_method('SetWifiRemoteStationManager', 
                   'void', 
                   [param('ns3::Ptr< ns3::WifiRemoteStationManager >', 'stationManager')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): bool ns3::WifiMac::SupportsSendFrom() const [member function]
    cls.add_method('SupportsSendFrom', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::ConfigureDcf(ns3::Ptr<ns3::Dcf> dcf, uint32_t cwmin, uint32_t cwmax, bool isDsss, ns3::AcIndex ac) [member function]
    cls.add_method('ConfigureDcf', 
                   'void', 
                   [param('ns3::Ptr< ns3::Dcf >', 'dcf'), param('uint32_t', 'cwmin'), param('uint32_t', 'cwmax'), param('bool', 'isDsss'), param('ns3::AcIndex', 'ac')], 
                   visibility='protected')
    ## wifi-mac.h (module 'wifi'): void ns3::WifiMac::FinishConfigureStandard(ns3::WifiPhyStandard standard) [member function]
    cls.add_method('FinishConfigureStandard', 
                   'void', 
                   [param('ns3::WifiPhyStandard', 'standard')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    return

def register_Ns3WifiMacHeader_methods(root_module, cls):
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::WifiMacHeader(ns3::WifiMacHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiMacHeader const &', 'arg0')])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::WifiMacHeader() [constructor]
    cls.add_constructor([])
    ## wifi-mac-header.h (module 'wifi'): uint32_t ns3::WifiMacHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr1() const [member function]
    cls.add_method('GetAddr1', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr2() const [member function]
    cls.add_method('GetAddr2', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr3() const [member function]
    cls.add_method('GetAddr3', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Mac48Address ns3::WifiMacHeader::GetAddr4() const [member function]
    cls.add_method('GetAddr4', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::Time ns3::WifiMacHeader::GetDuration() const [member function]
    cls.add_method('GetDuration', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetFragmentNumber() const [member function]
    cls.add_method('GetFragmentNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::TypeId ns3::WifiMacHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacHeader::QosAckPolicy ns3::WifiMacHeader::GetQosAckPolicy() const [member function]
    cls.add_method('GetQosAckPolicy', 
                   'ns3::WifiMacHeader::QosAckPolicy', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint8_t ns3::WifiMacHeader::GetQosTid() const [member function]
    cls.add_method('GetQosTid', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint8_t ns3::WifiMacHeader::GetQosTxopLimit() const [member function]
    cls.add_method('GetQosTxopLimit', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetRawDuration() const [member function]
    cls.add_method('GetRawDuration', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetSequenceControl() const [member function]
    cls.add_method('GetSequenceControl', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint16_t ns3::WifiMacHeader::GetSequenceNumber() const [member function]
    cls.add_method('GetSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): uint32_t ns3::WifiMacHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): uint32_t ns3::WifiMacHeader::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacType ns3::WifiMacHeader::GetType() const [member function]
    cls.add_method('GetType', 
                   'ns3::WifiMacType', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): static ns3::TypeId ns3::WifiMacHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## wifi-mac-header.h (module 'wifi'): char const * ns3::WifiMacHeader::GetTypeString() const [member function]
    cls.add_method('GetTypeString', 
                   'char const *', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAck() const [member function]
    cls.add_method('IsAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAction() const [member function]
    cls.add_method('IsAction', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAssocReq() const [member function]
    cls.add_method('IsAssocReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAssocResp() const [member function]
    cls.add_method('IsAssocResp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsAuthentication() const [member function]
    cls.add_method('IsAuthentication', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsBeacon() const [member function]
    cls.add_method('IsBeacon', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsBlockAck() const [member function]
    cls.add_method('IsBlockAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsBlockAckReq() const [member function]
    cls.add_method('IsBlockAckReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsCfpoll() const [member function]
    cls.add_method('IsCfpoll', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsCtl() const [member function]
    cls.add_method('IsCtl', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsCts() const [member function]
    cls.add_method('IsCts', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsData() const [member function]
    cls.add_method('IsData', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsDeauthentication() const [member function]
    cls.add_method('IsDeauthentication', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsDisassociation() const [member function]
    cls.add_method('IsDisassociation', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsFromDs() const [member function]
    cls.add_method('IsFromDs', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsMgt() const [member function]
    cls.add_method('IsMgt', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsMoreFragments() const [member function]
    cls.add_method('IsMoreFragments', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsMultihopAction() const [member function]
    cls.add_method('IsMultihopAction', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsProbeReq() const [member function]
    cls.add_method('IsProbeReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsProbeResp() const [member function]
    cls.add_method('IsProbeResp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosAck() const [member function]
    cls.add_method('IsQosAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosAmsdu() const [member function]
    cls.add_method('IsQosAmsdu', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosBlockAck() const [member function]
    cls.add_method('IsQosBlockAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosData() const [member function]
    cls.add_method('IsQosData', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosEosp() const [member function]
    cls.add_method('IsQosEosp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsQosNoAck() const [member function]
    cls.add_method('IsQosNoAck', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsReassocReq() const [member function]
    cls.add_method('IsReassocReq', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsReassocResp() const [member function]
    cls.add_method('IsReassocResp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsRetry() const [member function]
    cls.add_method('IsRetry', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsRts() const [member function]
    cls.add_method('IsRts', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): bool ns3::WifiMacHeader::IsToDs() const [member function]
    cls.add_method('IsToDs', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAction() [member function]
    cls.add_method('SetAction', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr1(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr1', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr2(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr2', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr3(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr3', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAddr4(ns3::Mac48Address address) [member function]
    cls.add_method('SetAddr4', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAssocReq() [member function]
    cls.add_method('SetAssocReq', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetAssocResp() [member function]
    cls.add_method('SetAssocResp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetBeacon() [member function]
    cls.add_method('SetBeacon', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetBlockAck() [member function]
    cls.add_method('SetBlockAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetBlockAckReq() [member function]
    cls.add_method('SetBlockAckReq', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsFrom() [member function]
    cls.add_method('SetDsFrom', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsNotFrom() [member function]
    cls.add_method('SetDsNotFrom', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsNotTo() [member function]
    cls.add_method('SetDsNotTo', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDsTo() [member function]
    cls.add_method('SetDsTo', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetDuration(ns3::Time duration) [member function]
    cls.add_method('SetDuration', 
                   'void', 
                   [param('ns3::Time', 'duration')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetFragmentNumber(uint8_t frag) [member function]
    cls.add_method('SetFragmentNumber', 
                   'void', 
                   [param('uint8_t', 'frag')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetId(uint16_t id) [member function]
    cls.add_method('SetId', 
                   'void', 
                   [param('uint16_t', 'id')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetMoreFragments() [member function]
    cls.add_method('SetMoreFragments', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetMultihopAction() [member function]
    cls.add_method('SetMultihopAction', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetNoMoreFragments() [member function]
    cls.add_method('SetNoMoreFragments', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetNoOrder() [member function]
    cls.add_method('SetNoOrder', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetNoRetry() [member function]
    cls.add_method('SetNoRetry', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetOrder() [member function]
    cls.add_method('SetOrder', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetProbeReq() [member function]
    cls.add_method('SetProbeReq', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetProbeResp() [member function]
    cls.add_method('SetProbeResp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosAckPolicy(ns3::WifiMacHeader::QosAckPolicy policy) [member function]
    cls.add_method('SetQosAckPolicy', 
                   'void', 
                   [param('ns3::WifiMacHeader::QosAckPolicy', 'policy')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosAmsdu() [member function]
    cls.add_method('SetQosAmsdu', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosBlockAck() [member function]
    cls.add_method('SetQosBlockAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosEosp() [member function]
    cls.add_method('SetQosEosp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosMeshControlPresent() [member function]
    cls.add_method('SetQosMeshControlPresent', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoAck() [member function]
    cls.add_method('SetQosNoAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoAmsdu() [member function]
    cls.add_method('SetQosNoAmsdu', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoEosp() [member function]
    cls.add_method('SetQosNoEosp', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNoMeshControlPresent() [member function]
    cls.add_method('SetQosNoMeshControlPresent', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosNormalAck() [member function]
    cls.add_method('SetQosNormalAck', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosTid(uint8_t tid) [member function]
    cls.add_method('SetQosTid', 
                   'void', 
                   [param('uint8_t', 'tid')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetQosTxopLimit(uint8_t txop) [member function]
    cls.add_method('SetQosTxopLimit', 
                   'void', 
                   [param('uint8_t', 'txop')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetRawDuration(uint16_t duration) [member function]
    cls.add_method('SetRawDuration', 
                   'void', 
                   [param('uint16_t', 'duration')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetRetry() [member function]
    cls.add_method('SetRetry', 
                   'void', 
                   [])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetSequenceNumber(uint16_t seq) [member function]
    cls.add_method('SetSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'seq')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetType(ns3::WifiMacType type) [member function]
    cls.add_method('SetType', 
                   'void', 
                   [param('ns3::WifiMacType', 'type')])
    ## wifi-mac-header.h (module 'wifi'): void ns3::WifiMacHeader::SetTypeData() [member function]
    cls.add_method('SetTypeData', 
                   'void', 
                   [])
    return

def register_Ns3WifiPhy_methods(root_module, cls):
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhy::WifiPhy(ns3::WifiPhy const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiPhy const &', 'arg0')])
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhy::WifiPhy() [constructor]
    cls.add_constructor([])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::AddSupportedChannelWidth(uint32_t channelwidth) [member function]
    cls.add_method('AddSupportedChannelWidth', 
                   'void', 
                   [param('uint32_t', 'channelwidth')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): int64_t ns3::WifiPhy::AssignStreams(int64_t stream) [member function]
    cls.add_method('AssignStreams', 
                   'int64_t', 
                   [param('int64_t', 'stream')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::CalculatePlcpPreambleAndHeaderDuration(ns3::WifiTxVector txVector, ns3::WifiPreamble preamble) [member function]
    cls.add_method('CalculatePlcpPreambleAndHeaderDuration', 
                   'ns3::Time', 
                   [param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble')])
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::CalculateSnr(ns3::WifiTxVector txVector, double ber) const [member function]
    cls.add_method('CalculateSnr', 
                   'double', 
                   [param('ns3::WifiTxVector', 'txVector'), param('double', 'ber')], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::CalculateTxDuration(uint32_t size, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble, double frequency) [member function]
    cls.add_method('CalculateTxDuration', 
                   'ns3::Time', 
                   [param('uint32_t', 'size'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble'), param('double', 'frequency')])
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::CalculateTxDuration(uint32_t size, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble, double frequency, ns3::mpduType mpdutype, uint8_t incFlag) [member function]
    cls.add_method('CalculateTxDuration', 
                   'ns3::Time', 
                   [param('uint32_t', 'size'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble'), param('double', 'frequency'), param('ns3::mpduType', 'mpdutype'), param('uint8_t', 'incFlag')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::ConfigureStandard(ns3::WifiPhyStandard standard) [member function]
    cls.add_method('ConfigureStandard', 
                   'void', 
                   [param('ns3::WifiPhyStandard', 'standard')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::DbToRatio(double db) const [member function]
    cls.add_method('DbToRatio', 
                   'double', 
                   [param('double', 'db')], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::DbmToW(double dbm) const [member function]
    cls.add_method('DbmToW', 
                   'double', 
                   [param('double', 'dbm')], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::DefineChannelNumber(uint16_t channelNumber, ns3::WifiPhyStandard standard, uint32_t frequency, uint32_t channelWidth) [member function]
    cls.add_method('DefineChannelNumber', 
                   'bool', 
                   [param('uint16_t', 'channelNumber'), param('ns3::WifiPhyStandard', 'standard'), param('uint32_t', 'frequency'), param('uint32_t', 'channelWidth')])
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetBssMembershipSelector(uint32_t selector) const [member function]
    cls.add_method('GetBssMembershipSelector', 
                   'uint32_t', 
                   [param('uint32_t', 'selector')], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetCcaMode1Threshold() const [member function]
    cls.add_method('GetCcaMode1Threshold', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): ns3::Ptr<ns3::WifiChannel> ns3::WifiPhy::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::WifiChannel >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint16_t ns3::WifiPhy::GetChannelNumber() const [member function]
    cls.add_method('GetChannelNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::GetChannelSwitchDelay() const [member function]
    cls.add_method('GetChannelSwitchDelay', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetChannelWidth() const [member function]
    cls.add_method('GetChannelWidth', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::GetDelayUntilIdle() [member function]
    cls.add_method('GetDelayUntilIdle', 
                   'ns3::Time', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Ptr<ns3::NetDevice> ns3::WifiPhy::GetDevice() const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetDsssRate11Mbps() [member function]
    cls.add_method('GetDsssRate11Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetDsssRate1Mbps() [member function]
    cls.add_method('GetDsssRate1Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetDsssRate2Mbps() [member function]
    cls.add_method('GetDsssRate2Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetDsssRate5_5Mbps() [member function]
    cls.add_method('GetDsssRate5_5Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetEdThreshold() const [member function]
    cls.add_method('GetEdThreshold', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetEdThresholdW() const [member function]
    cls.add_method('GetEdThresholdW', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate12Mbps() [member function]
    cls.add_method('GetErpOfdmRate12Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate18Mbps() [member function]
    cls.add_method('GetErpOfdmRate18Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate24Mbps() [member function]
    cls.add_method('GetErpOfdmRate24Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate36Mbps() [member function]
    cls.add_method('GetErpOfdmRate36Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate48Mbps() [member function]
    cls.add_method('GetErpOfdmRate48Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate54Mbps() [member function]
    cls.add_method('GetErpOfdmRate54Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate6Mbps() [member function]
    cls.add_method('GetErpOfdmRate6Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetErpOfdmRate9Mbps() [member function]
    cls.add_method('GetErpOfdmRate9Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): ns3::Ptr<ns3::ErrorRateModel> ns3::WifiPhy::GetErrorRateModel() const [member function]
    cls.add_method('GetErrorRateModel', 
                   'ns3::Ptr< ns3::ErrorRateModel >', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetFrequency() const [member function]
    cls.add_method('GetFrequency', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::GetGreenfield() const [member function]
    cls.add_method('GetGreenfield', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::GetGuardInterval() const [member function]
    cls.add_method('GetGuardInterval', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs0() [member function]
    cls.add_method('GetHtMcs0', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs1() [member function]
    cls.add_method('GetHtMcs1', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs10() [member function]
    cls.add_method('GetHtMcs10', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs11() [member function]
    cls.add_method('GetHtMcs11', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs12() [member function]
    cls.add_method('GetHtMcs12', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs13() [member function]
    cls.add_method('GetHtMcs13', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs14() [member function]
    cls.add_method('GetHtMcs14', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs15() [member function]
    cls.add_method('GetHtMcs15', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs16() [member function]
    cls.add_method('GetHtMcs16', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs17() [member function]
    cls.add_method('GetHtMcs17', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs18() [member function]
    cls.add_method('GetHtMcs18', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs19() [member function]
    cls.add_method('GetHtMcs19', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs2() [member function]
    cls.add_method('GetHtMcs2', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs20() [member function]
    cls.add_method('GetHtMcs20', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs21() [member function]
    cls.add_method('GetHtMcs21', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs22() [member function]
    cls.add_method('GetHtMcs22', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs23() [member function]
    cls.add_method('GetHtMcs23', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs24() [member function]
    cls.add_method('GetHtMcs24', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs25() [member function]
    cls.add_method('GetHtMcs25', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs26() [member function]
    cls.add_method('GetHtMcs26', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs27() [member function]
    cls.add_method('GetHtMcs27', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs28() [member function]
    cls.add_method('GetHtMcs28', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs29() [member function]
    cls.add_method('GetHtMcs29', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs3() [member function]
    cls.add_method('GetHtMcs3', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs30() [member function]
    cls.add_method('GetHtMcs30', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs31() [member function]
    cls.add_method('GetHtMcs31', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs4() [member function]
    cls.add_method('GetHtMcs4', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs5() [member function]
    cls.add_method('GetHtMcs5', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs6() [member function]
    cls.add_method('GetHtMcs6', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs7() [member function]
    cls.add_method('GetHtMcs7', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs8() [member function]
    cls.add_method('GetHtMcs8', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtMcs9() [member function]
    cls.add_method('GetHtMcs9', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetHtPlcpHeaderMode(ns3::WifiMode payloadMode) [member function]
    cls.add_method('GetHtPlcpHeaderMode', 
                   'ns3::WifiMode', 
                   [param('ns3::WifiMode', 'payloadMode')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::GetLastRxStartTime() const [member function]
    cls.add_method('GetLastRxStartTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::GetLdpc() const [member function]
    cls.add_method('GetLdpc', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::WifiMode ns3::WifiPhy::GetMcs(uint8_t mcs) const [member function]
    cls.add_method('GetMcs', 
                   'ns3::WifiMode', 
                   [param('uint8_t', 'mcs')], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::WifiModeList ns3::WifiPhy::GetMembershipSelectorModes(uint32_t selector) [member function]
    cls.add_method('GetMembershipSelectorModes', 
                   'ns3::WifiModeList', 
                   [param('uint32_t', 'selector')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Ptr<ns3::MobilityModel> ns3::WifiPhy::GetMobility() [member function]
    cls.add_method('GetMobility', 
                   'ns3::Ptr< ns3::MobilityModel >', 
                   [])
    ## wifi-phy.h (module 'wifi'): ns3::WifiMode ns3::WifiPhy::GetMode(uint32_t mode) const [member function]
    cls.add_method('GetMode', 
                   'ns3::WifiMode', 
                   [param('uint32_t', 'mode')], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetNBssMembershipSelectors() const [member function]
    cls.add_method('GetNBssMembershipSelectors', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint8_t ns3::WifiPhy::GetNMcs() const [member function]
    cls.add_method('GetNMcs', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetNModes() const [member function]
    cls.add_method('GetNModes', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetNTxPower() const [member function]
    cls.add_method('GetNTxPower', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetNumberOfReceiveAntennas() const [member function]
    cls.add_method('GetNumberOfReceiveAntennas', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint32_t ns3::WifiPhy::GetNumberOfTransmitAntennas() const [member function]
    cls.add_method('GetNumberOfTransmitAntennas', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate12Mbps() [member function]
    cls.add_method('GetOfdmRate12Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate12MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate12MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate12MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate12MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate13_5MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate13_5MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate18Mbps() [member function]
    cls.add_method('GetOfdmRate18Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate18MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate18MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate1_5MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate1_5MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate24Mbps() [member function]
    cls.add_method('GetOfdmRate24Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate24MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate24MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate27MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate27MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate2_25MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate2_25MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate36Mbps() [member function]
    cls.add_method('GetOfdmRate36Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate3MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate3MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate3MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate3MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate48Mbps() [member function]
    cls.add_method('GetOfdmRate48Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate4_5MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate4_5MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate4_5MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate4_5MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate54Mbps() [member function]
    cls.add_method('GetOfdmRate54Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate6Mbps() [member function]
    cls.add_method('GetOfdmRate6Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate6MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate6MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate6MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate6MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate9Mbps() [member function]
    cls.add_method('GetOfdmRate9Mbps', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate9MbpsBW10MHz() [member function]
    cls.add_method('GetOfdmRate9MbpsBW10MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetOfdmRate9MbpsBW5MHz() [member function]
    cls.add_method('GetOfdmRate9MbpsBW5MHz', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::GetPayloadDuration(uint32_t size, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble, double frequency) [member function]
    cls.add_method('GetPayloadDuration', 
                   'ns3::Time', 
                   [param('uint32_t', 'size'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble'), param('double', 'frequency')])
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::GetPayloadDuration(uint32_t size, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble, double frequency, ns3::mpduType mpdutype, uint8_t incFlag) [member function]
    cls.add_method('GetPayloadDuration', 
                   'ns3::Time', 
                   [param('uint32_t', 'size'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble'), param('double', 'frequency'), param('ns3::mpduType', 'mpdutype'), param('uint8_t', 'incFlag')])
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpHeaderDuration(ns3::WifiTxVector txVector, ns3::WifiPreamble preamble) [member function]
    cls.add_method('GetPlcpHeaderDuration', 
                   'ns3::Time', 
                   [param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetPlcpHeaderMode(ns3::WifiMode payloadMode, ns3::WifiPreamble preamble, ns3::WifiTxVector txVector) [member function]
    cls.add_method('GetPlcpHeaderMode', 
                   'ns3::WifiMode', 
                   [param('ns3::WifiMode', 'payloadMode'), param('ns3::WifiPreamble', 'preamble'), param('ns3::WifiTxVector', 'txVector')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpHtSigHeaderDuration(ns3::WifiPreamble preamble) [member function]
    cls.add_method('GetPlcpHtSigHeaderDuration', 
                   'ns3::Time', 
                   [param('ns3::WifiPreamble', 'preamble')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpHtTrainingSymbolDuration(ns3::WifiPreamble preamble, ns3::WifiTxVector txVector) [member function]
    cls.add_method('GetPlcpHtTrainingSymbolDuration', 
                   'ns3::Time', 
                   [param('ns3::WifiPreamble', 'preamble'), param('ns3::WifiTxVector', 'txVector')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpPreambleDuration(ns3::WifiTxVector txVector, ns3::WifiPreamble preamble) [member function]
    cls.add_method('GetPlcpPreambleDuration', 
                   'ns3::Time', 
                   [param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpVhtSigA1Duration(ns3::WifiPreamble preamble) [member function]
    cls.add_method('GetPlcpVhtSigA1Duration', 
                   'ns3::Time', 
                   [param('ns3::WifiPreamble', 'preamble')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpVhtSigA2Duration(ns3::WifiPreamble preamble) [member function]
    cls.add_method('GetPlcpVhtSigA2Duration', 
                   'ns3::Time', 
                   [param('ns3::WifiPreamble', 'preamble')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::Time ns3::WifiPhy::GetPlcpVhtSigBDuration(ns3::WifiPreamble preamble) [member function]
    cls.add_method('GetPlcpVhtSigBDuration', 
                   'ns3::Time', 
                   [param('ns3::WifiPreamble', 'preamble')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetRxGain() const [member function]
    cls.add_method('GetRxGain', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetRxNoiseFigure() const [member function]
    cls.add_method('GetRxNoiseFigure', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::GetShortPlcpPreambleSupported() const [member function]
    cls.add_method('GetShortPlcpPreambleSupported', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhyStandard ns3::WifiPhy::GetStandard() const [member function]
    cls.add_method('GetStandard', 
                   'ns3::WifiPhyStandard', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): ns3::Time ns3::WifiPhy::GetStateDuration() [member function]
    cls.add_method('GetStateDuration', 
                   'ns3::Time', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::GetStbc() const [member function]
    cls.add_method('GetStbc', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): std::vector<unsigned int, std::allocator<unsigned int> > ns3::WifiPhy::GetSupportedChannelWidthSet() const [member function]
    cls.add_method('GetSupportedChannelWidthSet', 
                   'std::vector< unsigned int >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint8_t ns3::WifiPhy::GetSupportedRxSpatialStreams() const [member function]
    cls.add_method('GetSupportedRxSpatialStreams', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): uint8_t ns3::WifiPhy::GetSupportedTxSpatialStreams() const [member function]
    cls.add_method('GetSupportedTxSpatialStreams', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetTxGain() const [member function]
    cls.add_method('GetTxGain', 
                   'double', 
                   [], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetTxPowerEnd() const [member function]
    cls.add_method('GetTxPowerEnd', 
                   'double', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetTxPowerStart() const [member function]
    cls.add_method('GetTxPowerStart', 
                   'double', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): static ns3::TypeId ns3::WifiPhy::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs0() [member function]
    cls.add_method('GetVhtMcs0', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs1() [member function]
    cls.add_method('GetVhtMcs1', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs2() [member function]
    cls.add_method('GetVhtMcs2', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs3() [member function]
    cls.add_method('GetVhtMcs3', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs4() [member function]
    cls.add_method('GetVhtMcs4', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs5() [member function]
    cls.add_method('GetVhtMcs5', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs6() [member function]
    cls.add_method('GetVhtMcs6', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs7() [member function]
    cls.add_method('GetVhtMcs7', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs8() [member function]
    cls.add_method('GetVhtMcs8', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtMcs9() [member function]
    cls.add_method('GetVhtMcs9', 
                   'ns3::WifiMode', 
                   [], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): static ns3::WifiMode ns3::WifiPhy::GetVhtPlcpHeaderMode(ns3::WifiMode payloadMode) [member function]
    cls.add_method('GetVhtPlcpHeaderMode', 
                   'ns3::WifiMode', 
                   [param('ns3::WifiMode', 'payloadMode')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsMcsSupported(ns3::WifiMode mcs) const [member function]
    cls.add_method('IsMcsSupported', 
                   'bool', 
                   [param('ns3::WifiMode', 'mcs')], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsModeSupported(ns3::WifiMode mode) const [member function]
    cls.add_method('IsModeSupported', 
                   'bool', 
                   [param('ns3::WifiMode', 'mode')], 
                   is_const=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateBusy() [member function]
    cls.add_method('IsStateBusy', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateCcaBusy() [member function]
    cls.add_method('IsStateCcaBusy', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateIdle() [member function]
    cls.add_method('IsStateIdle', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateRx() [member function]
    cls.add_method('IsStateRx', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateSleep() [member function]
    cls.add_method('IsStateSleep', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateSwitching() [member function]
    cls.add_method('IsStateSwitching', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::IsStateTx() [member function]
    cls.add_method('IsStateTx', 
                   'bool', 
                   [], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): static bool ns3::WifiPhy::IsValidTxVector(ns3::WifiTxVector txVector) [member function]
    cls.add_method('IsValidTxVector', 
                   'bool', 
                   [param('ns3::WifiTxVector', 'txVector')], 
                   is_static=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyMonitorSniffRx(ns3::Ptr<ns3::Packet const> packet, uint16_t channelFreqMhz, uint16_t channelNumber, uint32_t rate, ns3::WifiPreamble preamble, ns3::WifiTxVector txVector, ns3::mpduInfo aMpdu, ns3::signalNoiseDbm signalNoise) [member function]
    cls.add_method('NotifyMonitorSniffRx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint16_t', 'channelFreqMhz'), param('uint16_t', 'channelNumber'), param('uint32_t', 'rate'), param('ns3::WifiPreamble', 'preamble'), param('ns3::WifiTxVector', 'txVector'), param('ns3::mpduInfo', 'aMpdu'), param('ns3::signalNoiseDbm', 'signalNoise')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyMonitorSniffTx(ns3::Ptr<ns3::Packet const> packet, uint16_t channelFreqMhz, uint16_t channelNumber, uint32_t rate, ns3::WifiPreamble preamble, ns3::WifiTxVector txVector, ns3::mpduInfo aMpdu) [member function]
    cls.add_method('NotifyMonitorSniffTx', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint16_t', 'channelFreqMhz'), param('uint16_t', 'channelNumber'), param('uint32_t', 'rate'), param('ns3::WifiPreamble', 'preamble'), param('ns3::WifiTxVector', 'txVector'), param('ns3::mpduInfo', 'aMpdu')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyRxBegin(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyRxBegin', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyRxDrop(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyRxDrop', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyRxEnd(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyRxEnd', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyTxBegin(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyTxBegin', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyTxDrop(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyTxDrop', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::NotifyTxEnd(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NotifyTxEnd', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::RatioToDb(double ratio) const [member function]
    cls.add_method('RatioToDb', 
                   'double', 
                   [param('double', 'ratio')], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::RegisterListener(ns3::WifiPhyListener * listener) [member function]
    cls.add_method('RegisterListener', 
                   'void', 
                   [param('ns3::WifiPhyListener *', 'listener')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::ResumeFromSleep() [member function]
    cls.add_method('ResumeFromSleep', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SendPacket(ns3::Ptr<ns3::Packet const> packet, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble) [member function]
    cls.add_method('SendPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SendPacket(ns3::Ptr<ns3::Packet const> packet, ns3::WifiTxVector txVector, ns3::WifiPreamble preamble, ns3::mpduType mpdutype) [member function]
    cls.add_method('SendPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::WifiTxVector', 'txVector'), param('ns3::WifiPreamble', 'preamble'), param('ns3::mpduType', 'mpdutype')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetCcaMode1Threshold(double threshold) [member function]
    cls.add_method('SetCcaMode1Threshold', 
                   'void', 
                   [param('double', 'threshold')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetChannelNumber(uint16_t id) [member function]
    cls.add_method('SetChannelNumber', 
                   'void', 
                   [param('uint16_t', 'id')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetChannelWidth(uint32_t channelwidth) [member function]
    cls.add_method('SetChannelWidth', 
                   'void', 
                   [param('uint32_t', 'channelwidth')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetEdThreshold(double threshold) [member function]
    cls.add_method('SetEdThreshold', 
                   'void', 
                   [param('double', 'threshold')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetErrorRateModel(ns3::Ptr<ns3::ErrorRateModel> rate) [member function]
    cls.add_method('SetErrorRateModel', 
                   'void', 
                   [param('ns3::Ptr< ns3::ErrorRateModel >', 'rate')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetFrequency(uint32_t freq) [member function]
    cls.add_method('SetFrequency', 
                   'void', 
                   [param('uint32_t', 'freq')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetGreenfield(bool greenfield) [member function]
    cls.add_method('SetGreenfield', 
                   'void', 
                   [param('bool', 'greenfield')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetGuardInterval(bool guardInterval) [member function]
    cls.add_method('SetGuardInterval', 
                   'void', 
                   [param('bool', 'guardInterval')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetLdpc(bool ldpc) [member function]
    cls.add_method('SetLdpc', 
                   'void', 
                   [param('bool', 'ldpc')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetMobility(ns3::Ptr<ns3::MobilityModel> mobility) [member function]
    cls.add_method('SetMobility', 
                   'void', 
                   [param('ns3::Ptr< ns3::MobilityModel >', 'mobility')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetNTxPower(uint32_t n) [member function]
    cls.add_method('SetNTxPower', 
                   'void', 
                   [param('uint32_t', 'n')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetNumberOfReceiveAntennas(uint32_t rx) [member function]
    cls.add_method('SetNumberOfReceiveAntennas', 
                   'void', 
                   [param('uint32_t', 'rx')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetNumberOfTransmitAntennas(uint32_t tx) [member function]
    cls.add_method('SetNumberOfTransmitAntennas', 
                   'void', 
                   [param('uint32_t', 'tx')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetReceiveErrorCallback(ns3::Callback<void,ns3::Ptr<ns3::Packet>,double,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> callback) [member function]
    cls.add_method('SetReceiveErrorCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, double, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetReceiveOkCallback(ns3::Callback<void,ns3::Ptr<ns3::Packet>,double,ns3::WifiTxVector,ns3::WifiPreamble,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> callback) [member function]
    cls.add_method('SetReceiveOkCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, double, ns3::WifiTxVector, ns3::WifiPreamble, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetRxGain(double gain) [member function]
    cls.add_method('SetRxGain', 
                   'void', 
                   [param('double', 'gain')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetRxNoiseFigure(double noiseFigureDb) [member function]
    cls.add_method('SetRxNoiseFigure', 
                   'void', 
                   [param('double', 'noiseFigureDb')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetShortPlcpPreambleSupported(bool preamble) [member function]
    cls.add_method('SetShortPlcpPreambleSupported', 
                   'void', 
                   [param('bool', 'preamble')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetSleepMode() [member function]
    cls.add_method('SetSleepMode', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetStbc(bool stbc) [member function]
    cls.add_method('SetStbc', 
                   'void', 
                   [param('bool', 'stbc')], 
                   is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetTxGain(double gain) [member function]
    cls.add_method('SetTxGain', 
                   'void', 
                   [param('double', 'gain')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetTxPowerEnd(double end) [member function]
    cls.add_method('SetTxPowerEnd', 
                   'void', 
                   [param('double', 'end')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::SetTxPowerStart(double start) [member function]
    cls.add_method('SetTxPowerStart', 
                   'void', 
                   [param('double', 'start')])
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::UnregisterListener(ns3::WifiPhyListener * listener) [member function]
    cls.add_method('UnregisterListener', 
                   'void', 
                   [param('ns3::WifiPhyListener *', 'listener')], 
                   is_pure_virtual=True, is_virtual=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::WToDbm(double w) const [member function]
    cls.add_method('WToDbm', 
                   'double', 
                   [param('double', 'w')], 
                   is_const=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::DoChannelSwitch(uint16_t id) [member function]
    cls.add_method('DoChannelSwitch', 
                   'bool', 
                   [param('uint16_t', 'id')], 
                   visibility='protected', is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wifi-phy.h (module 'wifi'): bool ns3::WifiPhy::DoFrequencySwitch(uint32_t frequency) [member function]
    cls.add_method('DoFrequencySwitch', 
                   'bool', 
                   [param('uint32_t', 'frequency')], 
                   visibility='protected', is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::DoInitialize() [member function]
    cls.add_method('DoInitialize', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wifi-phy.h (module 'wifi'): double ns3::WifiPhy::GetPowerDbm(uint8_t power) const [member function]
    cls.add_method('GetPowerDbm', 
                   'double', 
                   [param('uint8_t', 'power')], 
                   is_const=True, visibility='protected')
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::ConfigureChannelForStandard(ns3::WifiPhyStandard standard) [member function]
    cls.add_method('ConfigureChannelForStandard', 
                   'void', 
                   [param('ns3::WifiPhyStandard', 'standard')], 
                   visibility='private', is_virtual=True)
    ## wifi-phy.h (module 'wifi'): void ns3::WifiPhy::ConfigureDefaultsForStandard(ns3::WifiPhyStandard standard) [member function]
    cls.add_method('ConfigureDefaultsForStandard', 
                   'void', 
                   [param('ns3::WifiPhyStandard', 'standard')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3WifiRemoteStationManager_methods(root_module, cls):
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationManager::WifiRemoteStationManager(ns3::WifiRemoteStationManager const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiRemoteStationManager const &', 'arg0')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationManager::WifiRemoteStationManager() [constructor]
    cls.add_constructor([])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddAllSupportedMcs(ns3::Mac48Address address) [member function]
    cls.add_method('AddAllSupportedMcs', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddAllSupportedModes(ns3::Mac48Address address) [member function]
    cls.add_method('AddAllSupportedModes', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddBasicMcs(ns3::WifiMode mcs) [member function]
    cls.add_method('AddBasicMcs', 
                   'void', 
                   [param('ns3::WifiMode', 'mcs')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddBasicMode(ns3::WifiMode mode) [member function]
    cls.add_method('AddBasicMode', 
                   'void', 
                   [param('ns3::WifiMode', 'mode')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddStationHtCapabilities(ns3::Mac48Address from, ns3::HtCapabilities htcapabilities) [member function]
    cls.add_method('AddStationHtCapabilities', 
                   'void', 
                   [param('ns3::Mac48Address', 'from'), param('ns3::HtCapabilities', 'htcapabilities')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddStationVhtCapabilities(ns3::Mac48Address from, ns3::VhtCapabilities vhtcapabilities) [member function]
    cls.add_method('AddStationVhtCapabilities', 
                   'void', 
                   [param('ns3::Mac48Address', 'from'), param('ns3::VhtCapabilities', 'vhtcapabilities')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddSupportedErpSlotTime(ns3::Mac48Address address, bool isShortSlotTimeSupported) [member function]
    cls.add_method('AddSupportedErpSlotTime', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('bool', 'isShortSlotTimeSupported')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddSupportedMcs(ns3::Mac48Address address, ns3::WifiMode mcs) [member function]
    cls.add_method('AddSupportedMcs', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'mcs')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddSupportedMode(ns3::Mac48Address address, ns3::WifiMode mode) [member function]
    cls.add_method('AddSupportedMode', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'mode')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::AddSupportedPlcpPreamble(ns3::Mac48Address address, bool isShortPreambleSupported) [member function]
    cls.add_method('AddSupportedPlcpPreamble', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('bool', 'isShortPreambleSupported')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::DoGetCtsToSelfTxVector() [member function]
    cls.add_method('DoGetCtsToSelfTxVector', 
                   'ns3::WifiTxVector', 
                   [])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::GetAckTxVector(ns3::Mac48Address address, ns3::WifiMode dataMode) [member function]
    cls.add_method('GetAckTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'dataMode')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetBasicMcs(uint32_t i) const [member function]
    cls.add_method('GetBasicMcs', 
                   'ns3::WifiMode', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetBasicMode(uint32_t i) const [member function]
    cls.add_method('GetBasicMode', 
                   'ns3::WifiMode', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::GetBlockAckTxVector(ns3::Mac48Address address, ns3::WifiMode dataMode) [member function]
    cls.add_method('GetBlockAckTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'dataMode')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::GetCtsToSelfTxVector(ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('GetCtsToSelfTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::GetCtsTxVector(ns3::Mac48Address address, ns3::WifiMode rtsMode) [member function]
    cls.add_method('GetCtsTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'rtsMode')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::GetDataTxVector(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('GetDataTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetDefaultMcs() const [member function]
    cls.add_method('GetDefaultMcs', 
                   'ns3::WifiMode', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetDefaultMode() const [member function]
    cls.add_method('GetDefaultMode', 
                   'ns3::WifiMode', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::GetDefaultTxPowerLevel() const [member function]
    cls.add_method('GetDefaultTxPowerLevel', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetFragmentOffset(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet, uint32_t fragmentNumber) [member function]
    cls.add_method('GetFragmentOffset', 
                   'uint32_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint32_t', 'fragmentNumber')])
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetFragmentSize(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet, uint32_t fragmentNumber) [member function]
    cls.add_method('GetFragmentSize', 
                   'uint32_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint32_t', 'fragmentNumber')])
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetFragmentationThreshold() const [member function]
    cls.add_method('GetFragmentationThreshold', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetGreenfieldSupported(ns3::Mac48Address address) const [member function]
    cls.add_method('GetGreenfieldSupported', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationInfo ns3::WifiRemoteStationManager::GetInfo(ns3::Mac48Address address) [member function]
    cls.add_method('GetInfo', 
                   'ns3::WifiRemoteStationInfo', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetMaxSlrc() const [member function]
    cls.add_method('GetMaxSlrc', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetMaxSsrc() const [member function]
    cls.add_method('GetMaxSsrc', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNBasicMcs() const [member function]
    cls.add_method('GetNBasicMcs', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNBasicModes() const [member function]
    cls.add_method('GetNBasicModes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNNonErpBasicModes() const [member function]
    cls.add_method('GetNNonErpBasicModes', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetNonErpBasicMode(uint32_t i) const [member function]
    cls.add_method('GetNonErpBasicMode', 
                   'ns3::WifiMode', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetNonUnicastMode() const [member function]
    cls.add_method('GetNonUnicastMode', 
                   'ns3::WifiMode', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNumberOfTransmitAntennas() [member function]
    cls.add_method('GetNumberOfTransmitAntennas', 
                   'uint32_t', 
                   [])
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStationManager::ProtectionMode ns3::WifiRemoteStationManager::GetProtectionMode() const [member function]
    cls.add_method('GetProtectionMode', 
                   'ns3::WifiRemoteStationManager::ProtectionMode', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetRtsCtsThreshold() const [member function]
    cls.add_method('GetRtsCtsThreshold', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::GetRtsTxVector(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('GetRtsTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetShortPreambleEnabled() const [member function]
    cls.add_method('GetShortPreambleEnabled', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetShortPreambleSupported(ns3::Mac48Address address) const [member function]
    cls.add_method('GetShortPreambleSupported', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetShortSlotTimeEnabled() const [member function]
    cls.add_method('GetShortSlotTimeEnabled', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetShortSlotTimeSupported(ns3::Mac48Address address) const [member function]
    cls.add_method('GetShortSlotTimeSupported', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): static ns3::TypeId ns3::WifiRemoteStationManager::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetUseNonErpProtection() const [member function]
    cls.add_method('GetUseNonErpProtection', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::HasHtSupported() const [member function]
    cls.add_method('HasHtSupported', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::HasVhtSupported() const [member function]
    cls.add_method('HasVhtSupported', 
                   'bool', 
                   [], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::IsAssociated(ns3::Mac48Address address) const [member function]
    cls.add_method('IsAssociated', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::IsBrandNew(ns3::Mac48Address address) const [member function]
    cls.add_method('IsBrandNew', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::IsLastFragment(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet, uint32_t fragmentNumber) [member function]
    cls.add_method('IsLastFragment', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('uint32_t', 'fragmentNumber')])
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::IsWaitAssocTxOk(ns3::Mac48Address address) const [member function]
    cls.add_method('IsWaitAssocTxOk', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address')], 
                   is_const=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::NeedCtsToSelf(ns3::WifiTxVector txVector) [member function]
    cls.add_method('NeedCtsToSelf', 
                   'bool', 
                   [param('ns3::WifiTxVector', 'txVector')])
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::NeedDataRetransmission(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NeedDataRetransmission', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::NeedFragmentation(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NeedFragmentation', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::NeedRts(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet, ns3::WifiTxVector txVector) [member function]
    cls.add_method('NeedRts', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::WifiTxVector', 'txVector')])
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::NeedRtsRetransmission(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('NeedRtsRetransmission', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::PrepareForQueue(ns3::Mac48Address address, ns3::WifiMacHeader const * header, ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('PrepareForQueue', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::RecordDisassociated(ns3::Mac48Address address) [member function]
    cls.add_method('RecordDisassociated', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::RecordGotAssocTxFailed(ns3::Mac48Address address) [member function]
    cls.add_method('RecordGotAssocTxFailed', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::RecordGotAssocTxOk(ns3::Mac48Address address) [member function]
    cls.add_method('RecordGotAssocTxOk', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::RecordWaitAssocTxOk(ns3::Mac48Address address) [member function]
    cls.add_method('RecordWaitAssocTxOk', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportAmpduTxStatus(ns3::Mac48Address address, uint8_t tid, uint32_t nSuccessfulMpdus, uint32_t nFailedMpdus, double rxSnr, double dataSnr) [member function]
    cls.add_method('ReportAmpduTxStatus', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('uint8_t', 'tid'), param('uint32_t', 'nSuccessfulMpdus'), param('uint32_t', 'nFailedMpdus'), param('double', 'rxSnr'), param('double', 'dataSnr')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportDataFailed(ns3::Mac48Address address, ns3::WifiMacHeader const * header) [member function]
    cls.add_method('ReportDataFailed', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportDataOk(ns3::Mac48Address address, ns3::WifiMacHeader const * header, double ackSnr, ns3::WifiMode ackMode, double dataSnr) [member function]
    cls.add_method('ReportDataOk', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('double', 'ackSnr'), param('ns3::WifiMode', 'ackMode'), param('double', 'dataSnr')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportFinalDataFailed(ns3::Mac48Address address, ns3::WifiMacHeader const * header) [member function]
    cls.add_method('ReportFinalDataFailed', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportFinalRtsFailed(ns3::Mac48Address address, ns3::WifiMacHeader const * header) [member function]
    cls.add_method('ReportFinalRtsFailed', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportRtsFailed(ns3::Mac48Address address, ns3::WifiMacHeader const * header) [member function]
    cls.add_method('ReportRtsFailed', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportRtsOk(ns3::Mac48Address address, ns3::WifiMacHeader const * header, double ctsSnr, ns3::WifiMode ctsMode, double rtsSnr) [member function]
    cls.add_method('ReportRtsOk', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('double', 'ctsSnr'), param('ns3::WifiMode', 'ctsMode'), param('double', 'rtsSnr')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::ReportRxOk(ns3::Mac48Address address, ns3::WifiMacHeader const * header, double rxSnr, ns3::WifiMode txMode) [member function]
    cls.add_method('ReportRxOk', 
                   'void', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMacHeader const *', 'header'), param('double', 'rxSnr'), param('ns3::WifiMode', 'txMode')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::Reset() [member function]
    cls.add_method('Reset', 
                   'void', 
                   [])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::Reset(ns3::Mac48Address address) [member function]
    cls.add_method('Reset', 
                   'void', 
                   [param('ns3::Mac48Address', 'address')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetDefaultTxPowerLevel(uint8_t txPower) [member function]
    cls.add_method('SetDefaultTxPowerLevel', 
                   'void', 
                   [param('uint8_t', 'txPower')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetFragmentationThreshold(uint32_t threshold) [member function]
    cls.add_method('SetFragmentationThreshold', 
                   'void', 
                   [param('uint32_t', 'threshold')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetHtSupported(bool enable) [member function]
    cls.add_method('SetHtSupported', 
                   'void', 
                   [param('bool', 'enable')], 
                   is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetMaxSlrc(uint32_t maxSlrc) [member function]
    cls.add_method('SetMaxSlrc', 
                   'void', 
                   [param('uint32_t', 'maxSlrc')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetMaxSsrc(uint32_t maxSsrc) [member function]
    cls.add_method('SetMaxSsrc', 
                   'void', 
                   [param('uint32_t', 'maxSsrc')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetProtectionMode(ns3::WifiRemoteStationManager::ProtectionMode mode) [member function]
    cls.add_method('SetProtectionMode', 
                   'void', 
                   [param('ns3::WifiRemoteStationManager::ProtectionMode', 'mode')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetRtsCtsThreshold(uint32_t threshold) [member function]
    cls.add_method('SetRtsCtsThreshold', 
                   'void', 
                   [param('uint32_t', 'threshold')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetShortPreambleEnabled(bool enable) [member function]
    cls.add_method('SetShortPreambleEnabled', 
                   'void', 
                   [param('bool', 'enable')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetShortSlotTimeEnabled(bool enable) [member function]
    cls.add_method('SetShortSlotTimeEnabled', 
                   'void', 
                   [param('bool', 'enable')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetUseNonErpProtection(bool enable) [member function]
    cls.add_method('SetUseNonErpProtection', 
                   'void', 
                   [param('bool', 'enable')])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetVhtSupported(bool enable) [member function]
    cls.add_method('SetVhtSupported', 
                   'void', 
                   [param('bool', 'enable')], 
                   is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetupMac(ns3::Ptr<ns3::WifiMac> mac) [member function]
    cls.add_method('SetupMac', 
                   'void', 
                   [param('ns3::Ptr< ns3::WifiMac >', 'mac')], 
                   is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::SetupPhy(ns3::Ptr<ns3::WifiPhy> phy) [member function]
    cls.add_method('SetupPhy', 
                   'void', 
                   [param('ns3::Ptr< ns3::WifiPhy >', 'phy')], 
                   is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::UpdateFragmentationThreshold() [member function]
    cls.add_method('UpdateFragmentationThreshold', 
                   'void', 
                   [])
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetAggregation(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetAggregation', 
                   'bool', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetChannelWidth(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetChannelWidth', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetGreenfield(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetGreenfield', 
                   'bool', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetHtSupported(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetHtSupported', 
                   'bool', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetLongRetryCount(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetLongRetryCount', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::Ptr<ns3::WifiMac> ns3::WifiRemoteStationManager::GetMac() const [member function]
    cls.add_method('GetMac', 
                   'ns3::Ptr< ns3::WifiMac >', 
                   [], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetMcsSupported(ns3::WifiRemoteStation const * station, uint32_t i) const [member function]
    cls.add_method('GetMcsSupported', 
                   'ns3::WifiMode', 
                   [param('ns3::WifiRemoteStation const *', 'station'), param('uint32_t', 'i')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNMcsSupported(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetNMcsSupported', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNNonErpSupported(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetNNonErpSupported', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNSupported(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetNSupported', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetNess(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetNess', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetNonErpSupported(ns3::WifiRemoteStation const * station, uint32_t i) const [member function]
    cls.add_method('GetNonErpSupported', 
                   'ns3::WifiMode', 
                   [param('ns3::WifiRemoteStation const *', 'station'), param('uint32_t', 'i')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::GetNumberOfSupportedRxAntennas(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetNumberOfSupportedRxAntennas', 
                   'uint8_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::Ptr<ns3::WifiPhy> ns3::WifiRemoteStationManager::GetPhy() const [member function]
    cls.add_method('GetPhy', 
                   'ns3::Ptr< ns3::WifiPhy >', 
                   [], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetShortGuardInterval(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetShortGuardInterval', 
                   'bool', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::GetShortRetryCount(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetShortRetryCount', 
                   'uint32_t', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetStbc(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetStbc', 
                   'bool', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiMode ns3::WifiRemoteStationManager::GetSupported(ns3::WifiRemoteStation const * station, uint32_t i) const [member function]
    cls.add_method('GetSupported', 
                   'ns3::WifiMode', 
                   [param('ns3::WifiRemoteStation const *', 'station'), param('uint32_t', 'i')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::GetVhtSupported(ns3::WifiRemoteStation const * station) const [member function]
    cls.add_method('GetVhtSupported', 
                   'bool', 
                   [param('ns3::WifiRemoteStation const *', 'station')], 
                   is_const=True, visibility='protected')
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiRemoteStation * ns3::WifiRemoteStationManager::DoCreateStation() const [member function]
    cls.add_method('DoCreateStation', 
                   'ns3::WifiRemoteStation *', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::DoGetAckTxChannelWidth(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetAckTxChannelWidth', 
                   'uint32_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoGetAckTxGuardInterval(ns3::Mac48Address address, ns3::WifiMode ackMode) [member function]
    cls.add_method('DoGetAckTxGuardInterval', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ackMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetAckTxNess(ns3::Mac48Address address, ns3::WifiMode ackMode) [member function]
    cls.add_method('DoGetAckTxNess', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ackMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetAckTxNss(ns3::Mac48Address address, ns3::WifiMode ackMode) [member function]
    cls.add_method('DoGetAckTxNss', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ackMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetAckTxPowerLevel(ns3::Mac48Address address, ns3::WifiMode ackMode) [member function]
    cls.add_method('DoGetAckTxPowerLevel', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ackMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoGetAckTxStbc(ns3::Mac48Address address, ns3::WifiMode ackMode) [member function]
    cls.add_method('DoGetAckTxStbc', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ackMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::DoGetBlockAckTxChannelWidth(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetBlockAckTxChannelWidth', 
                   'uint32_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoGetBlockAckTxGuardInterval(ns3::Mac48Address address, ns3::WifiMode blockAckMode) [member function]
    cls.add_method('DoGetBlockAckTxGuardInterval', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'blockAckMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetBlockAckTxNess(ns3::Mac48Address address, ns3::WifiMode blockAckMode) [member function]
    cls.add_method('DoGetBlockAckTxNess', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'blockAckMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetBlockAckTxNss(ns3::Mac48Address address, ns3::WifiMode blockAckMode) [member function]
    cls.add_method('DoGetBlockAckTxNss', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'blockAckMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetBlockAckTxPowerLevel(ns3::Mac48Address address, ns3::WifiMode blockAckMode) [member function]
    cls.add_method('DoGetBlockAckTxPowerLevel', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'blockAckMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoGetBlockAckTxStbc(ns3::Mac48Address address, ns3::WifiMode blockAckMode) [member function]
    cls.add_method('DoGetBlockAckTxStbc', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'blockAckMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint32_t ns3::WifiRemoteStationManager::DoGetCtsTxChannelWidth(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetCtsTxChannelWidth', 
                   'uint32_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoGetCtsTxGuardInterval(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetCtsTxGuardInterval', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetCtsTxNess(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetCtsTxNess', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetCtsTxNss(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetCtsTxNss', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): uint8_t ns3::WifiRemoteStationManager::DoGetCtsTxPowerLevel(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetCtsTxPowerLevel', 
                   'uint8_t', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoGetCtsTxStbc(ns3::Mac48Address address, ns3::WifiMode ctsMode) [member function]
    cls.add_method('DoGetCtsTxStbc', 
                   'bool', 
                   [param('ns3::Mac48Address', 'address'), param('ns3::WifiMode', 'ctsMode')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::DoGetDataTxVector(ns3::WifiRemoteStation * station) [member function]
    cls.add_method('DoGetDataTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::WifiRemoteStation *', 'station')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): ns3::WifiTxVector ns3::WifiRemoteStationManager::DoGetRtsTxVector(ns3::WifiRemoteStation * station) [member function]
    cls.add_method('DoGetRtsTxVector', 
                   'ns3::WifiTxVector', 
                   [param('ns3::WifiRemoteStation *', 'station')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoNeedDataRetransmission(ns3::WifiRemoteStation * station, ns3::Ptr<ns3::Packet const> packet, bool normally) [member function]
    cls.add_method('DoNeedDataRetransmission', 
                   'bool', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('bool', 'normally')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoNeedFragmentation(ns3::WifiRemoteStation * station, ns3::Ptr<ns3::Packet const> packet, bool normally) [member function]
    cls.add_method('DoNeedFragmentation', 
                   'bool', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('bool', 'normally')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoNeedRts(ns3::WifiRemoteStation * station, ns3::Ptr<ns3::Packet const> packet, bool normally) [member function]
    cls.add_method('DoNeedRts', 
                   'bool', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('bool', 'normally')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::DoNeedRtsRetransmission(ns3::WifiRemoteStation * station, ns3::Ptr<ns3::Packet const> packet, bool normally) [member function]
    cls.add_method('DoNeedRtsRetransmission', 
                   'bool', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('ns3::Ptr< ns3::Packet const >', 'packet'), param('bool', 'normally')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportAmpduTxStatus(ns3::WifiRemoteStation * station, uint32_t nSuccessfulMpdus, uint32_t nFailedMpdus, double rxSnr, double dataSnr) [member function]
    cls.add_method('DoReportAmpduTxStatus', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('uint32_t', 'nSuccessfulMpdus'), param('uint32_t', 'nFailedMpdus'), param('double', 'rxSnr'), param('double', 'dataSnr')], 
                   visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportDataFailed(ns3::WifiRemoteStation * station) [member function]
    cls.add_method('DoReportDataFailed', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportDataOk(ns3::WifiRemoteStation * station, double ackSnr, ns3::WifiMode ackMode, double dataSnr) [member function]
    cls.add_method('DoReportDataOk', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('double', 'ackSnr'), param('ns3::WifiMode', 'ackMode'), param('double', 'dataSnr')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportFinalDataFailed(ns3::WifiRemoteStation * station) [member function]
    cls.add_method('DoReportFinalDataFailed', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportFinalRtsFailed(ns3::WifiRemoteStation * station) [member function]
    cls.add_method('DoReportFinalRtsFailed', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportRtsFailed(ns3::WifiRemoteStation * station) [member function]
    cls.add_method('DoReportRtsFailed', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportRtsOk(ns3::WifiRemoteStation * station, double ctsSnr, ns3::WifiMode ctsMode, double rtsSnr) [member function]
    cls.add_method('DoReportRtsOk', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('double', 'ctsSnr'), param('ns3::WifiMode', 'ctsMode'), param('double', 'rtsSnr')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): void ns3::WifiRemoteStationManager::DoReportRxOk(ns3::WifiRemoteStation * station, double rxSnr, ns3::WifiMode txMode) [member function]
    cls.add_method('DoReportRxOk', 
                   'void', 
                   [param('ns3::WifiRemoteStation *', 'station'), param('double', 'rxSnr'), param('ns3::WifiMode', 'txMode')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## wifi-remote-station-manager.h (module 'wifi'): bool ns3::WifiRemoteStationManager::IsLowLatency() const [member function]
    cls.add_method('IsLowLatency', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    return

def register_Ns3ZetaRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ZetaRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ZetaRandomVariable::ZetaRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ZetaRandomVariable::GetAlpha() const [member function]
    cls.add_method('GetAlpha', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ZetaRandomVariable::GetValue(double alpha) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'alpha')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZetaRandomVariable::GetInteger(uint32_t alpha) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'alpha')])
    ## random-variable-stream.h (module 'core'): double ns3::ZetaRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZetaRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ZipfRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ZipfRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ZipfRandomVariable::ZipfRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZipfRandomVariable::GetN() const [member function]
    cls.add_method('GetN', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ZipfRandomVariable::GetAlpha() const [member function]
    cls.add_method('GetAlpha', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ZipfRandomVariable::GetValue(uint32_t n, double alpha) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('uint32_t', 'n'), param('double', 'alpha')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZipfRandomVariable::GetInteger(uint32_t n, uint32_t alpha) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'n'), param('uint32_t', 'alpha')])
    ## random-variable-stream.h (module 'core'): double ns3::ZipfRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ZipfRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ArpCache_methods(root_module, cls):
    ## arp-cache.h (module 'internet'): ns3::ArpCache::ArpCache() [constructor]
    cls.add_constructor([])
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry * ns3::ArpCache::Add(ns3::Ipv4Address to) [member function]
    cls.add_method('Add', 
                   'ns3::ArpCache::Entry *', 
                   [param('ns3::Ipv4Address', 'to')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Flush() [member function]
    cls.add_method('Flush', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): ns3::Time ns3::ArpCache::GetAliveTimeout() const [member function]
    cls.add_method('GetAliveTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Time ns3::ArpCache::GetDeadTimeout() const [member function]
    cls.add_method('GetDeadTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::ArpCache::GetDevice() const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Ptr<ns3::Ipv4Interface> ns3::ArpCache::GetInterface() const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ptr< ns3::Ipv4Interface >', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): static ns3::TypeId ns3::ArpCache::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## arp-cache.h (module 'internet'): ns3::Time ns3::ArpCache::GetWaitReplyTimeout() const [member function]
    cls.add_method('GetWaitReplyTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry * ns3::ArpCache::Lookup(ns3::Ipv4Address destination) [member function]
    cls.add_method('Lookup', 
                   'ns3::ArpCache::Entry *', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## arp-cache.h (module 'internet'): std::list<ns3::ArpCache::Entry*,std::allocator<ns3::ArpCache::Entry*> > ns3::ArpCache::LookupInverse(ns3::Address destination) [member function]
    cls.add_method('LookupInverse', 
                   'std::list< ns3::ArpCache::Entry * >', 
                   [param('ns3::Address', 'destination')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::PrintArpCache(ns3::Ptr<ns3::OutputStreamWrapper> stream) [member function]
    cls.add_method('PrintArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Remove(ns3::ArpCache::Entry * entry) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::ArpCache::Entry *', 'entry')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetAliveTimeout(ns3::Time aliveTimeout) [member function]
    cls.add_method('SetAliveTimeout', 
                   'void', 
                   [param('ns3::Time', 'aliveTimeout')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetArpRequestCallback(ns3::Callback<void, ns3::Ptr<ns3::ArpCache const>, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> arpRequestCallback) [member function]
    cls.add_method('SetArpRequestCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::ArpCache const >, ns3::Ipv4Address, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'arpRequestCallback')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetDeadTimeout(ns3::Time deadTimeout) [member function]
    cls.add_method('SetDeadTimeout', 
                   'void', 
                   [param('ns3::Time', 'deadTimeout')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetDevice(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::Ipv4Interface> interface) [member function]
    cls.add_method('SetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::Ipv4Interface >', 'interface')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::SetWaitReplyTimeout(ns3::Time waitReplyTimeout) [member function]
    cls.add_method('SetWaitReplyTimeout', 
                   'void', 
                   [param('ns3::Time', 'waitReplyTimeout')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::StartWaitReplyTimer() [member function]
    cls.add_method('StartWaitReplyTimer', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3ArpCacheEntry_methods(root_module, cls):
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry::Entry(ns3::ArpCache::Entry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ArpCache::Entry const &', 'arg0')])
    ## arp-cache.h (module 'internet'): ns3::ArpCache::Entry::Entry(ns3::ArpCache * arp) [constructor]
    cls.add_constructor([param('ns3::ArpCache *', 'arp')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::ClearPendingPacket() [member function]
    cls.add_method('ClearPendingPacket', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::ClearRetries() [member function]
    cls.add_method('ClearRetries', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): std::pair<ns3::Ptr<ns3::Packet>,ns3::Ipv4Header> ns3::ArpCache::Entry::DequeuePending() [member function]
    cls.add_method('DequeuePending', 
                   'std::pair< ns3::Ptr< ns3::Packet >, ns3::Ipv4Header >', 
                   [])
    ## arp-cache.h (module 'internet'): ns3::Ipv4Address ns3::ArpCache::Entry::GetIpv4Address() const [member function]
    cls.add_method('GetIpv4Address', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): ns3::Address ns3::ArpCache::Entry::GetMacAddress() const [member function]
    cls.add_method('GetMacAddress', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): uint32_t ns3::ArpCache::Entry::GetRetries() const [member function]
    cls.add_method('GetRetries', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::IncrementRetries() [member function]
    cls.add_method('IncrementRetries', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsAlive() [member function]
    cls.add_method('IsAlive', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsDead() [member function]
    cls.add_method('IsDead', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsExpired() const [member function]
    cls.add_method('IsExpired', 
                   'bool', 
                   [], 
                   is_const=True)
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsPermanent() [member function]
    cls.add_method('IsPermanent', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::IsWaitReply() [member function]
    cls.add_method('IsWaitReply', 
                   'bool', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkAlive(ns3::Address macAddress) [member function]
    cls.add_method('MarkAlive', 
                   'void', 
                   [param('ns3::Address', 'macAddress')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkDead() [member function]
    cls.add_method('MarkDead', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkPermanent() [member function]
    cls.add_method('MarkPermanent', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::MarkWaitReply(std::pair<ns3::Ptr<ns3::Packet>,ns3::Ipv4Header> waiting) [member function]
    cls.add_method('MarkWaitReply', 
                   'void', 
                   [param('std::pair< ns3::Ptr< ns3::Packet >, ns3::Ipv4Header >', 'waiting')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::SetIpv4Address(ns3::Ipv4Address destination) [member function]
    cls.add_method('SetIpv4Address', 
                   'void', 
                   [param('ns3::Ipv4Address', 'destination')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::SetMacAddresss(ns3::Address macAddress) [member function]
    cls.add_method('SetMacAddresss', 
                   'void', 
                   [param('ns3::Address', 'macAddress')])
    ## arp-cache.h (module 'internet'): void ns3::ArpCache::Entry::UpdateSeen() [member function]
    cls.add_method('UpdateSeen', 
                   'void', 
                   [])
    ## arp-cache.h (module 'internet'): bool ns3::ArpCache::Entry::UpdateWaitReply(std::pair<ns3::Ptr<ns3::Packet>,ns3::Ipv4Header> waiting) [member function]
    cls.add_method('UpdateWaitReply', 
                   'bool', 
                   [param('std::pair< ns3::Ptr< ns3::Packet >, ns3::Ipv4Header >', 'waiting')])
    return

def register_Ns3AttributeAccessor_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeAccessor::AttributeAccessor(ns3::AttributeAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeAccessor const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeAccessor::AttributeAccessor() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::Get(ns3::ObjectBase const * object, ns3::AttributeValue & attribute) const [member function]
    cls.add_method('Get', 
                   'bool', 
                   [param('ns3::ObjectBase const *', 'object'), param('ns3::AttributeValue &', 'attribute')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::HasGetter() const [member function]
    cls.add_method('HasGetter', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::HasSetter() const [member function]
    cls.add_method('HasSetter', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeAccessor::Set(ns3::ObjectBase * object, ns3::AttributeValue const & value) const [member function]
    cls.add_method('Set', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'object', transfer_ownership=False), param('ns3::AttributeValue const &', 'value')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeChecker_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeChecker::AttributeChecker(ns3::AttributeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeChecker const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeChecker::AttributeChecker() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::Copy(ns3::AttributeValue const & source, ns3::AttributeValue & destination) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'source'), param('ns3::AttributeValue &', 'destination')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeChecker::CreateValidValue(ns3::AttributeValue const & value) const [member function]
    cls.add_method('CreateValidValue', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3AttributeValue_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::AttributeValue::AttributeValue(ns3::AttributeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AttributeValue const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::AttributeValue::AttributeValue() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::AttributeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::AttributeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_pure_virtual=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::AttributeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3BooleanChecker_methods(root_module, cls):
    ## boolean.h (module 'core'): ns3::BooleanChecker::BooleanChecker() [constructor]
    cls.add_constructor([])
    ## boolean.h (module 'core'): ns3::BooleanChecker::BooleanChecker(ns3::BooleanChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::BooleanChecker const &', 'arg0')])
    return

def register_Ns3BooleanValue_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## boolean.h (module 'core'): ns3::BooleanValue::BooleanValue(ns3::BooleanValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::BooleanValue const &', 'arg0')])
    ## boolean.h (module 'core'): ns3::BooleanValue::BooleanValue() [constructor]
    cls.add_constructor([])
    ## boolean.h (module 'core'): ns3::BooleanValue::BooleanValue(bool value) [constructor]
    cls.add_constructor([param('bool', 'value')])
    ## boolean.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::BooleanValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## boolean.h (module 'core'): bool ns3::BooleanValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## boolean.h (module 'core'): bool ns3::BooleanValue::Get() const [member function]
    cls.add_method('Get', 
                   'bool', 
                   [], 
                   is_const=True)
    ## boolean.h (module 'core'): std::string ns3::BooleanValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## boolean.h (module 'core'): void ns3::BooleanValue::Set(bool value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('bool', 'value')])
    return

def register_Ns3CallbackChecker_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackChecker::CallbackChecker() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackChecker::CallbackChecker(ns3::CallbackChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackChecker const &', 'arg0')])
    return

def register_Ns3CallbackImplBase_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackImplBase::CallbackImplBase() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackImplBase::CallbackImplBase(ns3::CallbackImplBase const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackImplBase const &', 'arg0')])
    ## callback.h (module 'core'): std::string ns3::CallbackImplBase::GetTypeid() const [member function]
    cls.add_method('GetTypeid', 
                   'std::string', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## callback.h (module 'core'): bool ns3::CallbackImplBase::IsEqual(ns3::Ptr<ns3::CallbackImplBase const> other) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ptr< ns3::CallbackImplBase const >', 'other')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## callback.h (module 'core'): static std::string ns3::CallbackImplBase::Demangle(std::string const & mangled) [member function]
    cls.add_method('Demangle', 
                   'std::string', 
                   [param('std::string const &', 'mangled')], 
                   is_static=True, visibility='protected')
    return

def register_Ns3CallbackValue_methods(root_module, cls):
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue(ns3::CallbackValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::CallbackValue const &', 'arg0')])
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue() [constructor]
    cls.add_constructor([])
    ## callback.h (module 'core'): ns3::CallbackValue::CallbackValue(ns3::CallbackBase const & base) [constructor]
    cls.add_constructor([param('ns3::CallbackBase const &', 'base')])
    ## callback.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::CallbackValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## callback.h (module 'core'): bool ns3::CallbackValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## callback.h (module 'core'): std::string ns3::CallbackValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## callback.h (module 'core'): void ns3::CallbackValue::Set(ns3::CallbackBase base) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::CallbackBase', 'base')])
    return

def register_Ns3Channel_methods(root_module, cls):
    ## channel.h (module 'network'): ns3::Channel::Channel(ns3::Channel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Channel const &', 'arg0')])
    ## channel.h (module 'network'): ns3::Channel::Channel() [constructor]
    cls.add_constructor([])
    ## channel.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Channel::GetDevice(uint32_t i) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'i')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## channel.h (module 'network'): uint32_t ns3::Channel::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## channel.h (module 'network'): uint32_t ns3::Channel::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## channel.h (module 'network'): static ns3::TypeId ns3::Channel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3ConstantRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ConstantRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ConstantRandomVariable::ConstantRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ConstantRandomVariable::GetConstant() const [member function]
    cls.add_method('GetConstant', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ConstantRandomVariable::GetValue(double constant) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'constant')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ConstantRandomVariable::GetInteger(uint32_t constant) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'constant')])
    ## random-variable-stream.h (module 'core'): double ns3::ConstantRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ConstantRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3DeterministicRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::DeterministicRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::DeterministicRandomVariable::DeterministicRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): void ns3::DeterministicRandomVariable::SetValueArray(double * values, uint64_t length) [member function]
    cls.add_method('SetValueArray', 
                   'void', 
                   [param('double *', 'values'), param('uint64_t', 'length')])
    ## random-variable-stream.h (module 'core'): double ns3::DeterministicRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::DeterministicRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3DoubleValue_methods(root_module, cls):
    ## double.h (module 'core'): ns3::DoubleValue::DoubleValue() [constructor]
    cls.add_constructor([])
    ## double.h (module 'core'): ns3::DoubleValue::DoubleValue(ns3::DoubleValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::DoubleValue const &', 'arg0')])
    ## double.h (module 'core'): ns3::DoubleValue::DoubleValue(double const & value) [constructor]
    cls.add_constructor([param('double const &', 'value')])
    ## double.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::DoubleValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## double.h (module 'core'): bool ns3::DoubleValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## double.h (module 'core'): double ns3::DoubleValue::Get() const [member function]
    cls.add_method('Get', 
                   'double', 
                   [], 
                   is_const=True)
    ## double.h (module 'core'): std::string ns3::DoubleValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## double.h (module 'core'): void ns3::DoubleValue::Set(double const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('double const &', 'value')])
    return

def register_Ns3EmpiricalRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): ns3::EmpiricalRandomVariable::EmpiricalRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): void ns3::EmpiricalRandomVariable::CDF(double v, double c) [member function]
    cls.add_method('CDF', 
                   'void', 
                   [param('double', 'v'), param('double', 'c')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::EmpiricalRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::EmpiricalRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): double ns3::EmpiricalRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): double ns3::EmpiricalRandomVariable::Interpolate(double c1, double c2, double v1, double v2, double r) [member function]
    cls.add_method('Interpolate', 
                   'double', 
                   [param('double', 'c1'), param('double', 'c2'), param('double', 'v1'), param('double', 'v2'), param('double', 'r')], 
                   visibility='private', is_virtual=True)
    ## random-variable-stream.h (module 'core'): void ns3::EmpiricalRandomVariable::Validate() [member function]
    cls.add_method('Validate', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3EmptyAttributeAccessor_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::EmptyAttributeAccessor::EmptyAttributeAccessor(ns3::EmptyAttributeAccessor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmptyAttributeAccessor const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::EmptyAttributeAccessor::EmptyAttributeAccessor() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeAccessor::Get(ns3::ObjectBase const * object, ns3::AttributeValue & attribute) const [member function]
    cls.add_method('Get', 
                   'bool', 
                   [param('ns3::ObjectBase const *', 'object'), param('ns3::AttributeValue &', 'attribute')], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeAccessor::HasGetter() const [member function]
    cls.add_method('HasGetter', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeAccessor::HasSetter() const [member function]
    cls.add_method('HasSetter', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeAccessor::Set(ns3::ObjectBase * object, ns3::AttributeValue const & value) const [member function]
    cls.add_method('Set', 
                   'bool', 
                   [param('ns3::ObjectBase *', 'object'), param('ns3::AttributeValue const &', 'value')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3EmptyAttributeChecker_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::EmptyAttributeChecker::EmptyAttributeChecker(ns3::EmptyAttributeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmptyAttributeChecker const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::EmptyAttributeChecker::EmptyAttributeChecker() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeChecker::Copy(ns3::AttributeValue const & source, ns3::AttributeValue & destination) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'source'), param('ns3::AttributeValue &', 'destination')], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EmptyAttributeChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::EmptyAttributeChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::EmptyAttributeChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3EmptyAttributeValue_methods(root_module, cls):
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue::EmptyAttributeValue(ns3::EmptyAttributeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EmptyAttributeValue const &', 'arg0')])
    ## attribute.h (module 'core'): ns3::EmptyAttributeValue::EmptyAttributeValue() [constructor]
    cls.add_constructor([])
    ## attribute.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EmptyAttributeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## attribute.h (module 'core'): bool ns3::EmptyAttributeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   visibility='private', is_virtual=True)
    ## attribute.h (module 'core'): std::string ns3::EmptyAttributeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, visibility='private', is_virtual=True)
    return

def register_Ns3EnumChecker_methods(root_module, cls):
    ## enum.h (module 'core'): ns3::EnumChecker::EnumChecker(ns3::EnumChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EnumChecker const &', 'arg0')])
    ## enum.h (module 'core'): ns3::EnumChecker::EnumChecker() [constructor]
    cls.add_constructor([])
    ## enum.h (module 'core'): void ns3::EnumChecker::Add(int value, std::string name) [member function]
    cls.add_method('Add', 
                   'void', 
                   [param('int', 'value'), param('std::string', 'name')])
    ## enum.h (module 'core'): void ns3::EnumChecker::AddDefault(int value, std::string name) [member function]
    cls.add_method('AddDefault', 
                   'void', 
                   [param('int', 'value'), param('std::string', 'name')])
    ## enum.h (module 'core'): bool ns3::EnumChecker::Check(ns3::AttributeValue const & value) const [member function]
    cls.add_method('Check', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'value')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumChecker::Copy(ns3::AttributeValue const & src, ns3::AttributeValue & dst) const [member function]
    cls.add_method('Copy', 
                   'bool', 
                   [param('ns3::AttributeValue const &', 'src'), param('ns3::AttributeValue &', 'dst')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EnumChecker::Create() const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): std::string ns3::EnumChecker::GetUnderlyingTypeInformation() const [member function]
    cls.add_method('GetUnderlyingTypeInformation', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): std::string ns3::EnumChecker::GetValueTypeName() const [member function]
    cls.add_method('GetValueTypeName', 
                   'std::string', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumChecker::HasUnderlyingTypeInformation() const [member function]
    cls.add_method('HasUnderlyingTypeInformation', 
                   'bool', 
                   [], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3EnumValue_methods(root_module, cls):
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue(ns3::EnumValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EnumValue const &', 'arg0')])
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue() [constructor]
    cls.add_constructor([])
    ## enum.h (module 'core'): ns3::EnumValue::EnumValue(int value) [constructor]
    cls.add_constructor([param('int', 'value')])
    ## enum.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::EnumValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): bool ns3::EnumValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## enum.h (module 'core'): int ns3::EnumValue::Get() const [member function]
    cls.add_method('Get', 
                   'int', 
                   [], 
                   is_const=True)
    ## enum.h (module 'core'): std::string ns3::EnumValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## enum.h (module 'core'): void ns3::EnumValue::Set(int value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('int', 'value')])
    return

def register_Ns3ErlangRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ErlangRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ErlangRandomVariable::ErlangRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ErlangRandomVariable::GetK() const [member function]
    cls.add_method('GetK', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ErlangRandomVariable::GetLambda() const [member function]
    cls.add_method('GetLambda', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ErlangRandomVariable::GetValue(uint32_t k, double lambda) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('uint32_t', 'k'), param('double', 'lambda')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ErlangRandomVariable::GetInteger(uint32_t k, uint32_t lambda) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'k'), param('uint32_t', 'lambda')])
    ## random-variable-stream.h (module 'core'): double ns3::ErlangRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ErlangRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ErrorRateModel_methods(root_module, cls):
    ## error-rate-model.h (module 'wifi'): ns3::ErrorRateModel::ErrorRateModel() [constructor]
    cls.add_constructor([])
    ## error-rate-model.h (module 'wifi'): ns3::ErrorRateModel::ErrorRateModel(ns3::ErrorRateModel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ErrorRateModel const &', 'arg0')])
    ## error-rate-model.h (module 'wifi'): double ns3::ErrorRateModel::CalculateSnr(ns3::WifiTxVector txVector, double ber) const [member function]
    cls.add_method('CalculateSnr', 
                   'double', 
                   [param('ns3::WifiTxVector', 'txVector'), param('double', 'ber')], 
                   is_const=True)
    ## error-rate-model.h (module 'wifi'): double ns3::ErrorRateModel::GetChunkSuccessRate(ns3::WifiMode mode, ns3::WifiTxVector txVector, double snr, uint32_t nbits) const [member function]
    cls.add_method('GetChunkSuccessRate', 
                   'double', 
                   [param('ns3::WifiMode', 'mode'), param('ns3::WifiTxVector', 'txVector'), param('double', 'snr'), param('uint32_t', 'nbits')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## error-rate-model.h (module 'wifi'): static ns3::TypeId ns3::ErrorRateModel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3EventImpl_methods(root_module, cls):
    ## event-impl.h (module 'core'): ns3::EventImpl::EventImpl(ns3::EventImpl const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::EventImpl const &', 'arg0')])
    ## event-impl.h (module 'core'): ns3::EventImpl::EventImpl() [constructor]
    cls.add_constructor([])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Cancel() [member function]
    cls.add_method('Cancel', 
                   'void', 
                   [])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Invoke() [member function]
    cls.add_method('Invoke', 
                   'void', 
                   [])
    ## event-impl.h (module 'core'): bool ns3::EventImpl::IsCancelled() [member function]
    cls.add_method('IsCancelled', 
                   'bool', 
                   [])
    ## event-impl.h (module 'core'): void ns3::EventImpl::Notify() [member function]
    cls.add_method('Notify', 
                   'void', 
                   [], 
                   is_pure_virtual=True, visibility='protected', is_virtual=True)
    return

def register_Ns3ExponentialRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ExponentialRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ExponentialRandomVariable::ExponentialRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetValue(double mean, double bound) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'bound')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ExponentialRandomVariable::GetInteger(uint32_t mean, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::ExponentialRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ExponentialRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3GammaRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::GammaRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::GammaRandomVariable::GammaRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetAlpha() const [member function]
    cls.add_method('GetAlpha', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetBeta() const [member function]
    cls.add_method('GetBeta', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetValue(double alpha, double beta) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'alpha'), param('double', 'beta')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::GammaRandomVariable::GetInteger(uint32_t alpha, uint32_t beta) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'alpha'), param('uint32_t', 'beta')])
    ## random-variable-stream.h (module 'core'): double ns3::GammaRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::GammaRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3HtCapabilities_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilities::HtCapabilities(ns3::HtCapabilities const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::HtCapabilities const &', 'arg0')])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilities::HtCapabilities() [constructor]
    cls.add_constructor([])
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::DeserializeInformationField(ns3::Buffer::Iterator start, uint8_t length) [member function]
    cls.add_method('DeserializeInformationField', 
                   'uint8_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint8_t', 'length')], 
                   is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): ns3::WifiInformationElementId ns3::HtCapabilities::ElementId() const [member function]
    cls.add_method('ElementId', 
                   'ns3::WifiInformationElementId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetAmpduParameters() const [member function]
    cls.add_method('GetAmpduParameters', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetAntennaSelectionCapabilities() const [member function]
    cls.add_method('GetAntennaSelectionCapabilities', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint16_t ns3::HtCapabilities::GetExtendedHtCapabilities() const [member function]
    cls.add_method('GetExtendedHtCapabilities', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetGreenfield() const [member function]
    cls.add_method('GetGreenfield', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint16_t ns3::HtCapabilities::GetHtCapabilitiesInfo() const [member function]
    cls.add_method('GetHtCapabilitiesInfo', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetInformationFieldSize() const [member function]
    cls.add_method('GetInformationFieldSize', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetLSigProtectionSupport() const [member function]
    cls.add_method('GetLSigProtectionSupport', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetLdpc() const [member function]
    cls.add_method('GetLdpc', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetMaxAmpduLength() const [member function]
    cls.add_method('GetMaxAmpduLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetMaxAmsduLength() const [member function]
    cls.add_method('GetMaxAmsduLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetRxHighestSupportedAntennas() const [member function]
    cls.add_method('GetRxHighestSupportedAntennas', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint16_t ns3::HtCapabilities::GetRxHighestSupportedDataRate() const [member function]
    cls.add_method('GetRxHighestSupportedDataRate', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t * ns3::HtCapabilities::GetRxMcsBitmask() [member function]
    cls.add_method('GetRxMcsBitmask', 
                   'uint8_t *', 
                   [])
    ## ht-capabilities.h (module 'wifi'): uint16_t ns3::HtCapabilities::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetShortGuardInterval20() const [member function]
    cls.add_method('GetShortGuardInterval20', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetShortGuardInterval40() const [member function]
    cls.add_method('GetShortGuardInterval40', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetSupportedChannelWidth() const [member function]
    cls.add_method('GetSupportedChannelWidth', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint64_t ns3::HtCapabilities::GetSupportedMcsSet1() const [member function]
    cls.add_method('GetSupportedMcsSet1', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint64_t ns3::HtCapabilities::GetSupportedMcsSet2() const [member function]
    cls.add_method('GetSupportedMcsSet2', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint32_t ns3::HtCapabilities::GetTxBfCapabilities() const [member function]
    cls.add_method('GetTxBfCapabilities', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetTxMaxNSpatialStreams() const [member function]
    cls.add_method('GetTxMaxNSpatialStreams', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetTxMcsSetDefined() const [member function]
    cls.add_method('GetTxMcsSetDefined', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetTxRxMcsSetUnequal() const [member function]
    cls.add_method('GetTxRxMcsSetUnequal', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): uint8_t ns3::HtCapabilities::GetTxUnequalModulation() const [member function]
    cls.add_method('GetTxUnequalModulation', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): bool ns3::HtCapabilities::IsSupportedMcs(uint8_t mcs) const [member function]
    cls.add_method('IsSupportedMcs', 
                   'bool', 
                   [param('uint8_t', 'mcs')], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): ns3::Buffer::Iterator ns3::HtCapabilities::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'ns3::Buffer::Iterator', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SerializeInformationField(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('SerializeInformationField', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetAmpduParameters(uint8_t ctrl) [member function]
    cls.add_method('SetAmpduParameters', 
                   'void', 
                   [param('uint8_t', 'ctrl')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetAntennaSelectionCapabilities(uint8_t ctrl) [member function]
    cls.add_method('SetAntennaSelectionCapabilities', 
                   'void', 
                   [param('uint8_t', 'ctrl')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetExtendedHtCapabilities(uint16_t ctrl) [member function]
    cls.add_method('SetExtendedHtCapabilities', 
                   'void', 
                   [param('uint16_t', 'ctrl')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetGreenfield(uint8_t greenfield) [member function]
    cls.add_method('SetGreenfield', 
                   'void', 
                   [param('uint8_t', 'greenfield')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetHtCapabilitiesInfo(uint16_t ctrl) [member function]
    cls.add_method('SetHtCapabilitiesInfo', 
                   'void', 
                   [param('uint16_t', 'ctrl')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetHtSupported(uint8_t htsupported) [member function]
    cls.add_method('SetHtSupported', 
                   'void', 
                   [param('uint8_t', 'htsupported')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetLSigProtectionSupport(uint8_t lsigprotection) [member function]
    cls.add_method('SetLSigProtectionSupport', 
                   'void', 
                   [param('uint8_t', 'lsigprotection')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetLdpc(uint8_t ldpc) [member function]
    cls.add_method('SetLdpc', 
                   'void', 
                   [param('uint8_t', 'ldpc')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetMaxAmpduLength(uint8_t maxampdulength) [member function]
    cls.add_method('SetMaxAmpduLength', 
                   'void', 
                   [param('uint8_t', 'maxampdulength')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetMaxAmsduLength(uint8_t maxamsdulength) [member function]
    cls.add_method('SetMaxAmsduLength', 
                   'void', 
                   [param('uint8_t', 'maxamsdulength')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetRxHighestSupportedDataRate(uint16_t maxsupportedrate) [member function]
    cls.add_method('SetRxHighestSupportedDataRate', 
                   'void', 
                   [param('uint16_t', 'maxsupportedrate')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetRxMcsBitmask(uint8_t index) [member function]
    cls.add_method('SetRxMcsBitmask', 
                   'void', 
                   [param('uint8_t', 'index')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetShortGuardInterval20(uint8_t shortguardinterval) [member function]
    cls.add_method('SetShortGuardInterval20', 
                   'void', 
                   [param('uint8_t', 'shortguardinterval')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetShortGuardInterval40(uint8_t shortguardinterval) [member function]
    cls.add_method('SetShortGuardInterval40', 
                   'void', 
                   [param('uint8_t', 'shortguardinterval')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetSupportedChannelWidth(uint8_t supportedchannelwidth) [member function]
    cls.add_method('SetSupportedChannelWidth', 
                   'void', 
                   [param('uint8_t', 'supportedchannelwidth')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetSupportedMcsSet(uint64_t ctrl1, uint64_t ctrl2) [member function]
    cls.add_method('SetSupportedMcsSet', 
                   'void', 
                   [param('uint64_t', 'ctrl1'), param('uint64_t', 'ctrl2')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetTxBfCapabilities(uint32_t ctrl) [member function]
    cls.add_method('SetTxBfCapabilities', 
                   'void', 
                   [param('uint32_t', 'ctrl')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetTxMaxNSpatialStreams(uint8_t maxtxspatialstreams) [member function]
    cls.add_method('SetTxMaxNSpatialStreams', 
                   'void', 
                   [param('uint8_t', 'maxtxspatialstreams')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetTxMcsSetDefined(uint8_t txmcssetdefined) [member function]
    cls.add_method('SetTxMcsSetDefined', 
                   'void', 
                   [param('uint8_t', 'txmcssetdefined')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetTxRxMcsSetUnequal(uint8_t txrxmcssetunequal) [member function]
    cls.add_method('SetTxRxMcsSetUnequal', 
                   'void', 
                   [param('uint8_t', 'txrxmcssetunequal')])
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilities::SetTxUnequalModulation(uint8_t txunequalmodulation) [member function]
    cls.add_method('SetTxUnequalModulation', 
                   'void', 
                   [param('uint8_t', 'txunequalmodulation')])
    return

def register_Ns3HtCapabilitiesChecker_methods(root_module, cls):
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesChecker::HtCapabilitiesChecker() [constructor]
    cls.add_constructor([])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesChecker::HtCapabilitiesChecker(ns3::HtCapabilitiesChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::HtCapabilitiesChecker const &', 'arg0')])
    return

def register_Ns3HtCapabilitiesValue_methods(root_module, cls):
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesValue::HtCapabilitiesValue() [constructor]
    cls.add_constructor([])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesValue::HtCapabilitiesValue(ns3::HtCapabilitiesValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::HtCapabilitiesValue const &', 'arg0')])
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilitiesValue::HtCapabilitiesValue(ns3::HtCapabilities const & value) [constructor]
    cls.add_constructor([param('ns3::HtCapabilities const &', 'value')])
    ## ht-capabilities.h (module 'wifi'): ns3::Ptr<ns3::AttributeValue> ns3::HtCapabilitiesValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): bool ns3::HtCapabilitiesValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): ns3::HtCapabilities ns3::HtCapabilitiesValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::HtCapabilities', 
                   [], 
                   is_const=True)
    ## ht-capabilities.h (module 'wifi'): std::string ns3::HtCapabilitiesValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ht-capabilities.h (module 'wifi'): void ns3::HtCapabilitiesValue::Set(ns3::HtCapabilities const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::HtCapabilities const &', 'value')])
    return

def register_Ns3IntegerValue_methods(root_module, cls):
    ## integer.h (module 'core'): ns3::IntegerValue::IntegerValue() [constructor]
    cls.add_constructor([])
    ## integer.h (module 'core'): ns3::IntegerValue::IntegerValue(ns3::IntegerValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IntegerValue const &', 'arg0')])
    ## integer.h (module 'core'): ns3::IntegerValue::IntegerValue(int64_t const & value) [constructor]
    cls.add_constructor([param('int64_t const &', 'value')])
    ## integer.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::IntegerValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## integer.h (module 'core'): bool ns3::IntegerValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## integer.h (module 'core'): int64_t ns3::IntegerValue::Get() const [member function]
    cls.add_method('Get', 
                   'int64_t', 
                   [], 
                   is_const=True)
    ## integer.h (module 'core'): std::string ns3::IntegerValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## integer.h (module 'core'): void ns3::IntegerValue::Set(int64_t const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('int64_t const &', 'value')])
    return

def register_Ns3IpL4Protocol_methods(root_module, cls):
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::IpL4Protocol() [constructor]
    cls.add_constructor([])
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::IpL4Protocol(ns3::IpL4Protocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::IpL4Protocol const &', 'arg0')])
    ## ip-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::IpL4Protocol::GetDownTarget() const [member function]
    cls.add_method('GetDownTarget', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::IpL4Protocol::GetDownTarget6() const [member function]
    cls.add_method('GetDownTarget6', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): int ns3::IpL4Protocol::GetProtocolNumber() const [member function]
    cls.add_method('GetProtocolNumber', 
                   'int', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): static ns3::TypeId ns3::IpL4Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::IpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::Ipv4Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::Ipv4Interface >', 'incomingInterface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::IpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Header const & header, ns3::Ptr<ns3::Ipv6Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Header const &', 'header'), param('ns3::Ptr< ns3::Ipv6Interface >', 'incomingInterface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::ReceiveIcmp(ns3::Ipv4Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv4Address payloadSource, ns3::Ipv4Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv4Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv4Address', 'payloadSource'), param('ns3::Ipv4Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::ReceiveIcmp(ns3::Ipv6Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv6Address payloadSource, ns3::Ipv6Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv6Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv6Address', 'payloadSource'), param('ns3::Ipv6Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::SetDownTarget(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ip-l4-protocol.h (module 'internet'): void ns3::IpL4Protocol::SetDownTarget6(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget6', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3Ipv4_methods(root_module, cls):
    ## ipv4.h (module 'internet'): ns3::Ipv4::Ipv4(ns3::Ipv4 const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4 const &', 'arg0')])
    ## ipv4.h (module 'internet'): ns3::Ipv4::Ipv4() [constructor]
    cls.add_constructor([])
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::AddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint32_t ns3::Ipv4::AddInterface(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddInterface', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::Ipv4::CreateRawSocket() [member function]
    cls.add_method('CreateRawSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::DeleteRawSocket(ns3::Ptr<ns3::Socket> socket) [member function]
    cls.add_method('DeleteRawSocket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Socket >', 'socket')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4::GetAddress(uint32_t interface, uint32_t addressIndex) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'interface'), param('uint32_t', 'addressIndex')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): int32_t ns3::Ipv4::GetInterfaceForAddress(ns3::Ipv4Address address) const [member function]
    cls.add_method('GetInterfaceForAddress', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'address')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): int32_t ns3::Ipv4::GetInterfaceForDevice(ns3::Ptr<const ns3::NetDevice> device) const [member function]
    cls.add_method('GetInterfaceForDevice', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): int32_t ns3::Ipv4::GetInterfaceForPrefix(ns3::Ipv4Address address, ns3::Ipv4Mask mask) const [member function]
    cls.add_method('GetInterfaceForPrefix', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'address'), param('ns3::Ipv4Mask', 'mask')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint16_t ns3::Ipv4::GetMetric(uint32_t interface) const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint16_t ns3::Ipv4::GetMtu(uint32_t interface) const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint32_t ns3::Ipv4::GetNAddresses(uint32_t interface) const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): uint32_t ns3::Ipv4::GetNInterfaces() const [member function]
    cls.add_method('GetNInterfaces', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4::GetNetDevice(uint32_t interface) [member function]
    cls.add_method('GetNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::IpL4Protocol> ns3::Ipv4::GetProtocol(int protocolNumber) const [member function]
    cls.add_method('GetProtocol', 
                   'ns3::Ptr< ns3::IpL4Protocol >', 
                   [param('int', 'protocolNumber')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::IpL4Protocol> ns3::Ipv4::GetProtocol(int protocolNumber, int32_t interfaceIndex) const [member function]
    cls.add_method('GetProtocol', 
                   'ns3::Ptr< ns3::IpL4Protocol >', 
                   [param('int', 'protocolNumber'), param('int32_t', 'interfaceIndex')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::Ipv4::GetRoutingProtocol() const [member function]
    cls.add_method('GetRoutingProtocol', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): static ns3::TypeId ns3::Ipv4::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Insert(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Insert(ns3::Ptr<ns3::IpL4Protocol> protocol, uint32_t interfaceIndex) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol'), param('uint32_t', 'interfaceIndex')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::IsDestinationAddress(ns3::Ipv4Address address, uint32_t iif) const [member function]
    cls.add_method('IsDestinationAddress', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address'), param('uint32_t', 'iif')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::IsForwarding(uint32_t interface) const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::IsUp(uint32_t interface) const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Remove(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Remove(ns3::Ptr<ns3::IpL4Protocol> protocol, uint32_t interfaceIndex) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol'), param('uint32_t', 'interfaceIndex')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::RemoveAddress(uint32_t interface, uint32_t addressIndex) [member function]
    cls.add_method('RemoveAddress', 
                   'bool', 
                   [param('uint32_t', 'interface'), param('uint32_t', 'addressIndex')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::RemoveAddress(uint32_t interface, ns3::Ipv4Address address) [member function]
    cls.add_method('RemoveAddress', 
                   'bool', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4Address', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4::SelectSourceAddress(ns3::Ptr<const ns3::NetDevice> device, ns3::Ipv4Address dst, ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e scope) [member function]
    cls.add_method('SelectSourceAddress', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device'), param('ns3::Ipv4Address', 'dst'), param('ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 'scope')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SendWithHeader(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Header ipHeader, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SendWithHeader', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Header', 'ipHeader'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetDown(uint32_t interface) [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetForwarding(uint32_t interface, bool val) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('uint32_t', 'interface'), param('bool', 'val')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetMetric(uint32_t interface, uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint32_t', 'interface'), param('uint16_t', 'metric')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetRoutingProtocol(ns3::Ptr<ns3::Ipv4RoutingProtocol> routingProtocol) [member function]
    cls.add_method('SetRoutingProtocol', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4RoutingProtocol >', 'routingProtocol')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetUp(uint32_t interface) [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4::SourceAddressSelection(uint32_t interface, ns3::Ipv4Address dest) [member function]
    cls.add_method('SourceAddressSelection', 
                   'ns3::Ipv4Address', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4Address', 'dest')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4.h (module 'internet'): ns3::Ipv4::IF_ANY [variable]
    cls.add_static_attribute('IF_ANY', 'uint32_t const', is_const=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::GetIpForward() const [member function]
    cls.add_method('GetIpForward', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## ipv4.h (module 'internet'): bool ns3::Ipv4::GetWeakEsModel() const [member function]
    cls.add_method('GetWeakEsModel', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetIpForward(bool forward) [member function]
    cls.add_method('SetIpForward', 
                   'void', 
                   [param('bool', 'forward')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    ## ipv4.h (module 'internet'): void ns3::Ipv4::SetWeakEsModel(bool model) [member function]
    cls.add_method('SetWeakEsModel', 
                   'void', 
                   [param('bool', 'model')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    return

def register_Ns3Ipv4AddressChecker_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker::Ipv4AddressChecker() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressChecker::Ipv4AddressChecker(ns3::Ipv4AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4AddressChecker const &', 'arg0')])
    return

def register_Ns3Ipv4AddressValue_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue(ns3::Ipv4AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4AddressValue const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4AddressValue::Ipv4AddressValue(ns3::Ipv4Address const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address const &', 'value')])
    ## ipv4-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv4AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address ns3::Ipv4AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): std::string ns3::Ipv4AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4AddressValue::Set(ns3::Ipv4Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'value')])
    return

def register_Ns3Ipv4Interface_methods(root_module, cls):
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4Interface::Ipv4Interface(ns3::Ipv4Interface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Interface const &', 'arg0')])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4Interface::Ipv4Interface() [constructor]
    cls.add_constructor([])
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::AddAddress(ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('ns3::Ipv4InterfaceAddress', 'address')])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4Interface::GetAddress(uint32_t index) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): ns3::Ptr<ns3::ArpCache> ns3::Ipv4Interface::GetArpCache() const [member function]
    cls.add_method('GetArpCache', 
                   'ns3::Ptr< ns3::ArpCache >', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4Interface::GetDevice() const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): uint16_t ns3::Ipv4Interface::GetMetric() const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): uint32_t ns3::Ipv4Interface::GetNAddresses() const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): static ns3::TypeId ns3::Ipv4Interface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::IsDown() const [member function]
    cls.add_method('IsDown', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::IsForwarding() const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): bool ns3::Ipv4Interface::IsUp() const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4Interface::RemoveAddress(uint32_t index) [member function]
    cls.add_method('RemoveAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'index')])
    ## ipv4-interface.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4Interface::RemoveAddress(ns3::Ipv4Address address) [member function]
    cls.add_method('RemoveAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('ns3::Ipv4Address', 'address')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::Send(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & hdr, ns3::Ipv4Address dest) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'hdr'), param('ns3::Ipv4Address', 'dest')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetArpCache(ns3::Ptr<ns3::ArpCache> arpCache) [member function]
    cls.add_method('SetArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arpCache')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('SetDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetDown() [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetForwarding(bool val) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('bool', 'val')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetMetric(uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint16_t', 'metric')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetTrafficControl(ns3::Ptr<ns3::TrafficControlLayer> tc) [member function]
    cls.add_method('SetTrafficControl', 
                   'void', 
                   [param('ns3::Ptr< ns3::TrafficControlLayer >', 'tc')])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::SetUp() [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [])
    ## ipv4-interface.h (module 'internet'): void ns3::Ipv4Interface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3Ipv4L3Protocol_methods(root_module, cls):
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol::Ipv4L3Protocol() [constructor]
    cls.add_constructor([])
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::AddAddress(uint32_t i, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('AddAddress', 
                   'bool', 
                   [param('uint32_t', 'i'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint32_t ns3::Ipv4L3Protocol::AddInterface(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddInterface', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::Ipv4L3Protocol::CreateRawSocket() [member function]
    cls.add_method('CreateRawSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::DeleteRawSocket(ns3::Ptr<ns3::Socket> socket) [member function]
    cls.add_method('DeleteRawSocket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Socket >', 'socket')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4InterfaceAddress ns3::Ipv4L3Protocol::GetAddress(uint32_t interfaceIndex, uint32_t addressIndex) const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Ipv4InterfaceAddress', 
                   [param('uint32_t', 'interfaceIndex'), param('uint32_t', 'addressIndex')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::Ipv4Interface> ns3::Ipv4L3Protocol::GetInterface(uint32_t i) const [member function]
    cls.add_method('GetInterface', 
                   'ns3::Ptr< ns3::Ipv4Interface >', 
                   [param('uint32_t', 'i')], 
                   is_const=True)
    ## ipv4-l3-protocol.h (module 'internet'): int32_t ns3::Ipv4L3Protocol::GetInterfaceForAddress(ns3::Ipv4Address addr) const [member function]
    cls.add_method('GetInterfaceForAddress', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'addr')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): int32_t ns3::Ipv4L3Protocol::GetInterfaceForDevice(ns3::Ptr<const ns3::NetDevice> device) const [member function]
    cls.add_method('GetInterfaceForDevice', 
                   'int32_t', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): int32_t ns3::Ipv4L3Protocol::GetInterfaceForPrefix(ns3::Ipv4Address addr, ns3::Ipv4Mask mask) const [member function]
    cls.add_method('GetInterfaceForPrefix', 
                   'int32_t', 
                   [param('ns3::Ipv4Address', 'addr'), param('ns3::Ipv4Mask', 'mask')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint16_t ns3::Ipv4L3Protocol::GetMetric(uint32_t i) const [member function]
    cls.add_method('GetMetric', 
                   'uint16_t', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint16_t ns3::Ipv4L3Protocol::GetMtu(uint32_t i) const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint32_t ns3::Ipv4L3Protocol::GetNAddresses(uint32_t interface) const [member function]
    cls.add_method('GetNAddresses', 
                   'uint32_t', 
                   [param('uint32_t', 'interface')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): uint32_t ns3::Ipv4L3Protocol::GetNInterfaces() const [member function]
    cls.add_method('GetNInterfaces', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4L3Protocol::GetNetDevice(uint32_t i) [member function]
    cls.add_method('GetNetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'i')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::IpL4Protocol> ns3::Ipv4L3Protocol::GetProtocol(int protocolNumber) const [member function]
    cls.add_method('GetProtocol', 
                   'ns3::Ptr< ns3::IpL4Protocol >', 
                   [param('int', 'protocolNumber')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::IpL4Protocol> ns3::Ipv4L3Protocol::GetProtocol(int protocolNumber, int32_t interfaceIndex) const [member function]
    cls.add_method('GetProtocol', 
                   'ns3::Ptr< ns3::IpL4Protocol >', 
                   [param('int', 'protocolNumber'), param('int32_t', 'interfaceIndex')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::Ipv4L3Protocol::GetRoutingProtocol() const [member function]
    cls.add_method('GetRoutingProtocol', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): static ns3::TypeId ns3::Ipv4L3Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Insert(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Insert(ns3::Ptr<ns3::IpL4Protocol> protocol, uint32_t interfaceIndex) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol'), param('uint32_t', 'interfaceIndex')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsDestinationAddress(ns3::Ipv4Address address, uint32_t iif) const [member function]
    cls.add_method('IsDestinationAddress', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'address'), param('uint32_t', 'iif')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsForwarding(uint32_t i) const [member function]
    cls.add_method('IsForwarding', 
                   'bool', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsUnicast(ns3::Ipv4Address ad) const [member function]
    cls.add_method('IsUnicast', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'ad')], 
                   is_const=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::IsUp(uint32_t i) const [member function]
    cls.add_method('IsUp', 
                   'bool', 
                   [param('uint32_t', 'i')], 
                   is_const=True, is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Receive(ns3::Ptr<ns3::NetDevice> device, ns3::Ptr<ns3::Packet const> p, uint16_t protocol, ns3::Address const & from, ns3::Address const & to, ns3::NetDevice::PacketType packetType) [member function]
    cls.add_method('Receive', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device'), param('ns3::Ptr< ns3::Packet const >', 'p'), param('uint16_t', 'protocol'), param('ns3::Address const &', 'from'), param('ns3::Address const &', 'to'), param('ns3::NetDevice::PacketType', 'packetType')])
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Remove(ns3::Ptr<ns3::IpL4Protocol> protocol) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Remove(ns3::Ptr<ns3::IpL4Protocol> protocol, uint32_t interfaceIndex) [member function]
    cls.add_method('Remove', 
                   'void', 
                   [param('ns3::Ptr< ns3::IpL4Protocol >', 'protocol'), param('uint32_t', 'interfaceIndex')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::RemoveAddress(uint32_t interfaceIndex, uint32_t addressIndex) [member function]
    cls.add_method('RemoveAddress', 
                   'bool', 
                   [param('uint32_t', 'interfaceIndex'), param('uint32_t', 'addressIndex')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::RemoveAddress(uint32_t interface, ns3::Ipv4Address address) [member function]
    cls.add_method('RemoveAddress', 
                   'bool', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4Address', 'address')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4L3Protocol::SelectSourceAddress(ns3::Ptr<const ns3::NetDevice> device, ns3::Ipv4Address dst, ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e scope) [member function]
    cls.add_method('SelectSourceAddress', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ptr< ns3::NetDevice const >', 'device'), param('ns3::Ipv4Address', 'dst'), param('ns3::Ipv4InterfaceAddress::InterfaceAddressScope_e', 'scope')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SendWithHeader(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Header ipHeader, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SendWithHeader', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Header', 'ipHeader'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetDefaultTtl(uint8_t ttl) [member function]
    cls.add_method('SetDefaultTtl', 
                   'void', 
                   [param('uint8_t', 'ttl')])
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetDown(uint32_t i) [member function]
    cls.add_method('SetDown', 
                   'void', 
                   [param('uint32_t', 'i')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetForwarding(uint32_t i, bool val) [member function]
    cls.add_method('SetForwarding', 
                   'void', 
                   [param('uint32_t', 'i'), param('bool', 'val')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetMetric(uint32_t i, uint16_t metric) [member function]
    cls.add_method('SetMetric', 
                   'void', 
                   [param('uint32_t', 'i'), param('uint16_t', 'metric')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetRoutingProtocol(ns3::Ptr<ns3::Ipv4RoutingProtocol> routingProtocol) [member function]
    cls.add_method('SetRoutingProtocol', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4RoutingProtocol >', 'routingProtocol')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetUp(uint32_t i) [member function]
    cls.add_method('SetUp', 
                   'void', 
                   [param('uint32_t', 'i')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4L3Protocol::SourceAddressSelection(uint32_t interface, ns3::Ipv4Address dest) [member function]
    cls.add_method('SourceAddressSelection', 
                   'ns3::Ipv4Address', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4Address', 'dest')], 
                   is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): ns3::Ipv4L3Protocol::PROT_NUMBER [variable]
    cls.add_static_attribute('PROT_NUMBER', 'uint16_t const', is_const=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::GetIpForward() const [member function]
    cls.add_method('GetIpForward', 
                   'bool', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): bool ns3::Ipv4L3Protocol::GetWeakEsModel() const [member function]
    cls.add_method('GetWeakEsModel', 
                   'bool', 
                   [], 
                   is_const=True, visibility='private', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetIpForward(bool forward) [member function]
    cls.add_method('SetIpForward', 
                   'void', 
                   [param('bool', 'forward')], 
                   visibility='private', is_virtual=True)
    ## ipv4-l3-protocol.h (module 'internet'): void ns3::Ipv4L3Protocol::SetWeakEsModel(bool model) [member function]
    cls.add_method('SetWeakEsModel', 
                   'void', 
                   [param('bool', 'model')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3Ipv4MaskChecker_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker::Ipv4MaskChecker() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskChecker::Ipv4MaskChecker(ns3::Ipv4MaskChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MaskChecker const &', 'arg0')])
    return

def register_Ns3Ipv4MaskValue_methods(root_module, cls):
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue() [constructor]
    cls.add_constructor([])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue(ns3::Ipv4MaskValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MaskValue const &', 'arg0')])
    ## ipv4-address.h (module 'network'): ns3::Ipv4MaskValue::Ipv4MaskValue(ns3::Ipv4Mask const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv4Mask const &', 'value')])
    ## ipv4-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv4MaskValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): bool ns3::Ipv4MaskValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask ns3::Ipv4MaskValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv4Mask', 
                   [], 
                   is_const=True)
    ## ipv4-address.h (module 'network'): std::string ns3::Ipv4MaskValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv4-address.h (module 'network'): void ns3::Ipv4MaskValue::Set(ns3::Ipv4Mask const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv4Mask const &', 'value')])
    return

def register_Ns3Ipv4MulticastRoute_methods(root_module, cls):
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::Ipv4MulticastRoute(ns3::Ipv4MulticastRoute const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4MulticastRoute const &', 'arg0')])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::Ipv4MulticastRoute() [constructor]
    cls.add_constructor([])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4MulticastRoute::GetGroup() const [member function]
    cls.add_method('GetGroup', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4MulticastRoute::GetOrigin() const [member function]
    cls.add_method('GetOrigin', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): std::map<unsigned int, unsigned int, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, unsigned int> > > ns3::Ipv4MulticastRoute::GetOutputTtlMap() const [member function]
    cls.add_method('GetOutputTtlMap', 
                   'std::map< unsigned int, unsigned int >', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): uint32_t ns3::Ipv4MulticastRoute::GetParent() const [member function]
    cls.add_method('GetParent', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetGroup(ns3::Ipv4Address const group) [member function]
    cls.add_method('SetGroup', 
                   'void', 
                   [param('ns3::Ipv4Address const', 'group')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetOrigin(ns3::Ipv4Address const origin) [member function]
    cls.add_method('SetOrigin', 
                   'void', 
                   [param('ns3::Ipv4Address const', 'origin')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetOutputTtl(uint32_t oif, uint32_t ttl) [member function]
    cls.add_method('SetOutputTtl', 
                   'void', 
                   [param('uint32_t', 'oif'), param('uint32_t', 'ttl')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4MulticastRoute::SetParent(uint32_t iif) [member function]
    cls.add_method('SetParent', 
                   'void', 
                   [param('uint32_t', 'iif')])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::MAX_INTERFACES [variable]
    cls.add_static_attribute('MAX_INTERFACES', 'uint32_t const', is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4MulticastRoute::MAX_TTL [variable]
    cls.add_static_attribute('MAX_TTL', 'uint32_t const', is_const=True)
    return

def register_Ns3Ipv4Route_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Route::Ipv4Route(ns3::Ipv4Route const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4Route const &', 'arg0')])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Route::Ipv4Route() [constructor]
    cls.add_constructor([])
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Route::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Route::GetGateway() const [member function]
    cls.add_method('GetGateway', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ptr<ns3::NetDevice> ns3::Ipv4Route::GetOutputDevice() const [member function]
    cls.add_method('GetOutputDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): ns3::Ipv4Address ns3::Ipv4Route::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetDestination(ns3::Ipv4Address dest) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dest')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetGateway(ns3::Ipv4Address gw) [member function]
    cls.add_method('SetGateway', 
                   'void', 
                   [param('ns3::Ipv4Address', 'gw')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetOutputDevice(ns3::Ptr<ns3::NetDevice> outputDevice) [member function]
    cls.add_method('SetOutputDevice', 
                   'void', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'outputDevice')])
    ## ipv4-route.h (module 'internet'): void ns3::Ipv4Route::SetSource(ns3::Ipv4Address src) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 'src')])
    return

def register_Ns3Ipv4RoutingProtocol_methods(root_module, cls):
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ipv4RoutingProtocol::Ipv4RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ipv4RoutingProtocol::Ipv4RoutingProtocol(ns3::Ipv4RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv4RoutingProtocol const &', 'arg0')])
    ## ipv4-routing-protocol.h (module 'internet'): static ns3::TypeId ns3::Ipv4RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): bool ns3::Ipv4RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void,ns3::Ptr<ns3::Ipv4Route>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::Socket::SocketErrno,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): ns3::Ptr<ns3::Ipv4Route> ns3::Ipv4RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   is_pure_virtual=True, is_virtual=True)
    ## ipv4-routing-protocol.h (module 'internet'): void ns3::Ipv4RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3Ipv6AddressChecker_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker::Ipv6AddressChecker() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressChecker::Ipv6AddressChecker(ns3::Ipv6AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6AddressChecker const &', 'arg0')])
    return

def register_Ns3Ipv6AddressValue_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue(ns3::Ipv6AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6AddressValue const &', 'arg0')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6AddressValue::Ipv6AddressValue(ns3::Ipv6Address const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv6Address const &', 'value')])
    ## ipv6-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv6AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address ns3::Ipv6AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv6Address', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): std::string ns3::Ipv6AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6AddressValue::Set(ns3::Ipv6Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv6Address const &', 'value')])
    return

def register_Ns3Ipv6PrefixChecker_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker::Ipv6PrefixChecker() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixChecker::Ipv6PrefixChecker(ns3::Ipv6PrefixChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6PrefixChecker const &', 'arg0')])
    return

def register_Ns3Ipv6PrefixValue_methods(root_module, cls):
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue() [constructor]
    cls.add_constructor([])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue(ns3::Ipv6PrefixValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ipv6PrefixValue const &', 'arg0')])
    ## ipv6-address.h (module 'network'): ns3::Ipv6PrefixValue::Ipv6PrefixValue(ns3::Ipv6Prefix const & value) [constructor]
    cls.add_constructor([param('ns3::Ipv6Prefix const &', 'value')])
    ## ipv6-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Ipv6PrefixValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): bool ns3::Ipv6PrefixValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix ns3::Ipv6PrefixValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ipv6Prefix', 
                   [], 
                   is_const=True)
    ## ipv6-address.h (module 'network'): std::string ns3::Ipv6PrefixValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ipv6-address.h (module 'network'): void ns3::Ipv6PrefixValue::Set(ns3::Ipv6Prefix const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ipv6Prefix const &', 'value')])
    return

def register_Ns3LogNormalRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::LogNormalRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::LogNormalRandomVariable::LogNormalRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetMu() const [member function]
    cls.add_method('GetMu', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetSigma() const [member function]
    cls.add_method('GetSigma', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetValue(double mu, double sigma) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mu'), param('double', 'sigma')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::LogNormalRandomVariable::GetInteger(uint32_t mu, uint32_t sigma) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mu'), param('uint32_t', 'sigma')])
    ## random-variable-stream.h (module 'core'): double ns3::LogNormalRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::LogNormalRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3Mac48AddressChecker_methods(root_module, cls):
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker::Mac48AddressChecker() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressChecker::Mac48AddressChecker(ns3::Mac48AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48AddressChecker const &', 'arg0')])
    return

def register_Ns3Mac48AddressValue_methods(root_module, cls):
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue() [constructor]
    cls.add_constructor([])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue(ns3::Mac48AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Mac48AddressValue const &', 'arg0')])
    ## mac48-address.h (module 'network'): ns3::Mac48AddressValue::Mac48AddressValue(ns3::Mac48Address const & value) [constructor]
    cls.add_constructor([param('ns3::Mac48Address const &', 'value')])
    ## mac48-address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::Mac48AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## mac48-address.h (module 'network'): bool ns3::Mac48AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## mac48-address.h (module 'network'): ns3::Mac48Address ns3::Mac48AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Mac48Address', 
                   [], 
                   is_const=True)
    ## mac48-address.h (module 'network'): std::string ns3::Mac48AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## mac48-address.h (module 'network'): void ns3::Mac48AddressValue::Set(ns3::Mac48Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Mac48Address const &', 'value')])
    return

def register_Ns3MobilityModel_methods(root_module, cls):
    ## mobility-model.h (module 'mobility'): ns3::MobilityModel::MobilityModel(ns3::MobilityModel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::MobilityModel const &', 'arg0')])
    ## mobility-model.h (module 'mobility'): ns3::MobilityModel::MobilityModel() [constructor]
    cls.add_constructor([])
    ## mobility-model.h (module 'mobility'): int64_t ns3::MobilityModel::AssignStreams(int64_t stream) [member function]
    cls.add_method('AssignStreams', 
                   'int64_t', 
                   [param('int64_t', 'stream')])
    ## mobility-model.h (module 'mobility'): double ns3::MobilityModel::GetDistanceFrom(ns3::Ptr<const ns3::MobilityModel> position) const [member function]
    cls.add_method('GetDistanceFrom', 
                   'double', 
                   [param('ns3::Ptr< ns3::MobilityModel const >', 'position')], 
                   is_const=True)
    ## mobility-model.h (module 'mobility'): ns3::Vector ns3::MobilityModel::GetPosition() const [member function]
    cls.add_method('GetPosition', 
                   'ns3::Vector', 
                   [], 
                   is_const=True)
    ## mobility-model.h (module 'mobility'): double ns3::MobilityModel::GetRelativeSpeed(ns3::Ptr<const ns3::MobilityModel> other) const [member function]
    cls.add_method('GetRelativeSpeed', 
                   'double', 
                   [param('ns3::Ptr< ns3::MobilityModel const >', 'other')], 
                   is_const=True)
    ## mobility-model.h (module 'mobility'): static ns3::TypeId ns3::MobilityModel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## mobility-model.h (module 'mobility'): ns3::Vector ns3::MobilityModel::GetVelocity() const [member function]
    cls.add_method('GetVelocity', 
                   'ns3::Vector', 
                   [], 
                   is_const=True)
    ## mobility-model.h (module 'mobility'): void ns3::MobilityModel::SetPosition(ns3::Vector const & position) [member function]
    cls.add_method('SetPosition', 
                   'void', 
                   [param('ns3::Vector const &', 'position')])
    ## mobility-model.h (module 'mobility'): void ns3::MobilityModel::NotifyCourseChange() const [member function]
    cls.add_method('NotifyCourseChange', 
                   'void', 
                   [], 
                   is_const=True, visibility='protected')
    ## mobility-model.h (module 'mobility'): int64_t ns3::MobilityModel::DoAssignStreams(int64_t start) [member function]
    cls.add_method('DoAssignStreams', 
                   'int64_t', 
                   [param('int64_t', 'start')], 
                   visibility='private', is_virtual=True)
    ## mobility-model.h (module 'mobility'): ns3::Vector ns3::MobilityModel::DoGetPosition() const [member function]
    cls.add_method('DoGetPosition', 
                   'ns3::Vector', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## mobility-model.h (module 'mobility'): ns3::Vector ns3::MobilityModel::DoGetVelocity() const [member function]
    cls.add_method('DoGetVelocity', 
                   'ns3::Vector', 
                   [], 
                   is_pure_virtual=True, is_const=True, visibility='private', is_virtual=True)
    ## mobility-model.h (module 'mobility'): void ns3::MobilityModel::DoSetPosition(ns3::Vector const & position) [member function]
    cls.add_method('DoSetPosition', 
                   'void', 
                   [param('ns3::Vector const &', 'position')], 
                   is_pure_virtual=True, visibility='private', is_virtual=True)
    return

def register_Ns3NetDevice_methods(root_module, cls):
    ## net-device.h (module 'network'): ns3::NetDevice::NetDevice() [constructor]
    cls.add_constructor([])
    ## net-device.h (module 'network'): ns3::NetDevice::NetDevice(ns3::NetDevice const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NetDevice const &', 'arg0')])
    ## net-device.h (module 'network'): void ns3::NetDevice::AddLinkChangeCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [member function]
    cls.add_method('AddLinkChangeCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetBroadcast() const [member function]
    cls.add_method('GetBroadcast', 
                   'ns3::Address', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Channel> ns3::NetDevice::GetChannel() const [member function]
    cls.add_method('GetChannel', 
                   'ns3::Ptr< ns3::Channel >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): uint32_t ns3::NetDevice::GetIfIndex() const [member function]
    cls.add_method('GetIfIndex', 
                   'uint32_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): uint16_t ns3::NetDevice::GetMtu() const [member function]
    cls.add_method('GetMtu', 
                   'uint16_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetMulticast(ns3::Ipv4Address multicastGroup) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv4Address', 'multicastGroup')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Address ns3::NetDevice::GetMulticast(ns3::Ipv6Address addr) const [member function]
    cls.add_method('GetMulticast', 
                   'ns3::Address', 
                   [param('ns3::Ipv6Address', 'addr')], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Node> ns3::NetDevice::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): static ns3::TypeId ns3::NetDevice::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsBridge() const [member function]
    cls.add_method('IsBridge', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsLinkUp() const [member function]
    cls.add_method('IsLinkUp', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsMulticast() const [member function]
    cls.add_method('IsMulticast', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::IsPointToPoint() const [member function]
    cls.add_method('IsPointToPoint', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::NeedsArp() const [member function]
    cls.add_method('NeedsArp', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::Send(ns3::Ptr<ns3::Packet> packet, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('Send', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SendFrom(ns3::Ptr<ns3::Packet> packet, ns3::Address const & source, ns3::Address const & dest, uint16_t protocolNumber) [member function]
    cls.add_method('SendFrom', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'dest'), param('uint16_t', 'protocolNumber')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetAddress(ns3::Address address) [member function]
    cls.add_method('SetAddress', 
                   'void', 
                   [param('ns3::Address', 'address')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetIfIndex(uint32_t const index) [member function]
    cls.add_method('SetIfIndex', 
                   'void', 
                   [param('uint32_t const', 'index')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SetMtu(uint16_t const mtu) [member function]
    cls.add_method('SetMtu', 
                   'bool', 
                   [param('uint16_t const', 'mtu')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetPromiscReceiveCallback(ns3::Callback<bool,ns3::Ptr<ns3::NetDevice>,ns3::Ptr<const ns3::Packet>,short unsigned int,const ns3::Address&,const ns3::Address&,ns3::NetDevice::PacketType,ns3::empty,ns3::empty,ns3::empty> cb) [member function]
    cls.add_method('SetPromiscReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, short unsigned int, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDevice::SetReceiveCallback(ns3::Callback<bool,ns3::Ptr<ns3::NetDevice>,ns3::Ptr<const ns3::Packet>,short unsigned int,const ns3::Address&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> cb) [member function]
    cls.add_method('SetReceiveCallback', 
                   'void', 
                   [param('ns3::Callback< bool, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, short unsigned int, ns3::Address const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_pure_virtual=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::NetDevice::SupportsSendFrom() const [member function]
    cls.add_method('SupportsSendFrom', 
                   'bool', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    return

def register_Ns3NetDeviceQueue_methods(root_module, cls):
    ## net-device.h (module 'network'): ns3::NetDeviceQueue::NetDeviceQueue(ns3::NetDeviceQueue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NetDeviceQueue const &', 'arg0')])
    ## net-device.h (module 'network'): ns3::NetDeviceQueue::NetDeviceQueue() [constructor]
    cls.add_constructor([])
    ## net-device.h (module 'network'): ns3::Ptr<ns3::QueueLimits> ns3::NetDeviceQueue::GetQueueLimits() [member function]
    cls.add_method('GetQueueLimits', 
                   'ns3::Ptr< ns3::QueueLimits >', 
                   [])
    ## net-device.h (module 'network'): bool ns3::NetDeviceQueue::IsStopped() const [member function]
    cls.add_method('IsStopped', 
                   'bool', 
                   [], 
                   is_const=True)
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::NotifyQueuedBytes(uint32_t bytes) [member function]
    cls.add_method('NotifyQueuedBytes', 
                   'void', 
                   [param('uint32_t', 'bytes')])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::NotifyTransmittedBytes(uint32_t bytes) [member function]
    cls.add_method('NotifyTransmittedBytes', 
                   'void', 
                   [param('uint32_t', 'bytes')])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::ResetQueueLimits() [member function]
    cls.add_method('ResetQueueLimits', 
                   'void', 
                   [])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::SetQueueLimits(ns3::Ptr<ns3::QueueLimits> ql) [member function]
    cls.add_method('SetQueueLimits', 
                   'void', 
                   [param('ns3::Ptr< ns3::QueueLimits >', 'ql')])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::SetWakeCallback(ns3::Callback<void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetWakeCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::Start() [member function]
    cls.add_method('Start', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::Stop() [member function]
    cls.add_method('Stop', 
                   'void', 
                   [], 
                   is_virtual=True)
    ## net-device.h (module 'network'): void ns3::NetDeviceQueue::Wake() [member function]
    cls.add_method('Wake', 
                   'void', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3NetDeviceQueueInterface_methods(root_module, cls):
    ## net-device.h (module 'network'): ns3::NetDeviceQueueInterface::NetDeviceQueueInterface(ns3::NetDeviceQueueInterface const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::NetDeviceQueueInterface const &', 'arg0')])
    ## net-device.h (module 'network'): ns3::NetDeviceQueueInterface::NetDeviceQueueInterface() [constructor]
    cls.add_constructor([])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueueInterface::CreateTxQueues() [member function]
    cls.add_method('CreateTxQueues', 
                   'void', 
                   [])
    ## net-device.h (module 'network'): uint8_t ns3::NetDeviceQueueInterface::GetNTxQueues() const [member function]
    cls.add_method('GetNTxQueues', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## net-device.h (module 'network'): ns3::Callback<unsigned char, ns3::Ptr<ns3::QueueItem>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::NetDeviceQueueInterface::GetSelectQueueCallback() const [member function]
    cls.add_method('GetSelectQueueCallback', 
                   'ns3::Callback< unsigned char, ns3::Ptr< ns3::QueueItem >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## net-device.h (module 'network'): ns3::Ptr<ns3::NetDeviceQueue> ns3::NetDeviceQueueInterface::GetTxQueue(uint8_t i) const [member function]
    cls.add_method('GetTxQueue', 
                   'ns3::Ptr< ns3::NetDeviceQueue >', 
                   [param('uint8_t', 'i')], 
                   is_const=True)
    ## net-device.h (module 'network'): static ns3::TypeId ns3::NetDeviceQueueInterface::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## net-device.h (module 'network'): void ns3::NetDeviceQueueInterface::SetSelectQueueCallback(ns3::Callback<unsigned char, ns3::Ptr<ns3::QueueItem>, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetSelectQueueCallback', 
                   'void', 
                   [param('ns3::Callback< unsigned char, ns3::Ptr< ns3::QueueItem >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueueInterface::SetTxQueuesN(uint8_t numTxQueues) [member function]
    cls.add_method('SetTxQueuesN', 
                   'void', 
                   [param('uint8_t', 'numTxQueues')])
    ## net-device.h (module 'network'): void ns3::NetDeviceQueueInterface::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3NixVector_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## nix-vector.h (module 'network'): ns3::NixVector::NixVector() [constructor]
    cls.add_constructor([])
    ## nix-vector.h (module 'network'): ns3::NixVector::NixVector(ns3::NixVector const & o) [copy constructor]
    cls.add_constructor([param('ns3::NixVector const &', 'o')])
    ## nix-vector.h (module 'network'): void ns3::NixVector::AddNeighborIndex(uint32_t newBits, uint32_t numberOfBits) [member function]
    cls.add_method('AddNeighborIndex', 
                   'void', 
                   [param('uint32_t', 'newBits'), param('uint32_t', 'numberOfBits')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::BitCount(uint32_t numberOfNeighbors) const [member function]
    cls.add_method('BitCount', 
                   'uint32_t', 
                   [param('uint32_t', 'numberOfNeighbors')], 
                   is_const=True)
    ## nix-vector.h (module 'network'): ns3::Ptr<ns3::NixVector> ns3::NixVector::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::NixVector >', 
                   [], 
                   is_const=True)
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::Deserialize(uint32_t const * buffer, uint32_t size) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('uint32_t const *', 'buffer'), param('uint32_t', 'size')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::ExtractNeighborIndex(uint32_t numberOfBits) [member function]
    cls.add_method('ExtractNeighborIndex', 
                   'uint32_t', 
                   [param('uint32_t', 'numberOfBits')])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::GetRemainingBits() [member function]
    cls.add_method('GetRemainingBits', 
                   'uint32_t', 
                   [])
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## nix-vector.h (module 'network'): uint32_t ns3::NixVector::Serialize(uint32_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint32_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    return

def register_Ns3Node_methods(root_module, cls):
    ## node.h (module 'network'): ns3::Node::Node(ns3::Node const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Node const &', 'arg0')])
    ## node.h (module 'network'): ns3::Node::Node() [constructor]
    cls.add_constructor([])
    ## node.h (module 'network'): ns3::Node::Node(uint32_t systemId) [constructor]
    cls.add_constructor([param('uint32_t', 'systemId')])
    ## node.h (module 'network'): uint32_t ns3::Node::AddApplication(ns3::Ptr<ns3::Application> application) [member function]
    cls.add_method('AddApplication', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::Application >', 'application')])
    ## node.h (module 'network'): uint32_t ns3::Node::AddDevice(ns3::Ptr<ns3::NetDevice> device) [member function]
    cls.add_method('AddDevice', 
                   'uint32_t', 
                   [param('ns3::Ptr< ns3::NetDevice >', 'device')])
    ## node.h (module 'network'): static bool ns3::Node::ChecksumEnabled() [member function]
    cls.add_method('ChecksumEnabled', 
                   'bool', 
                   [], 
                   is_static=True)
    ## node.h (module 'network'): ns3::Ptr<ns3::Application> ns3::Node::GetApplication(uint32_t index) const [member function]
    cls.add_method('GetApplication', 
                   'ns3::Ptr< ns3::Application >', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## node.h (module 'network'): ns3::Ptr<ns3::NetDevice> ns3::Node::GetDevice(uint32_t index) const [member function]
    cls.add_method('GetDevice', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('uint32_t', 'index')], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): ns3::Time ns3::Node::GetLocalTime() const [member function]
    cls.add_method('GetLocalTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetNApplications() const [member function]
    cls.add_method('GetNApplications', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetNDevices() const [member function]
    cls.add_method('GetNDevices', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): uint32_t ns3::Node::GetSystemId() const [member function]
    cls.add_method('GetSystemId', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## node.h (module 'network'): static ns3::TypeId ns3::Node::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## node.h (module 'network'): void ns3::Node::RegisterDeviceAdditionListener(ns3::Callback<void,ns3::Ptr<ns3::NetDevice>,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> listener) [member function]
    cls.add_method('RegisterDeviceAdditionListener', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'listener')])
    ## node.h (module 'network'): void ns3::Node::RegisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler, uint16_t protocolType, ns3::Ptr<ns3::NetDevice> device, bool promiscuous=false) [member function]
    cls.add_method('RegisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler'), param('uint16_t', 'protocolType'), param('ns3::Ptr< ns3::NetDevice >', 'device'), param('bool', 'promiscuous', default_value='false')])
    ## node.h (module 'network'): void ns3::Node::UnregisterDeviceAdditionListener(ns3::Callback<void,ns3::Ptr<ns3::NetDevice>,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> listener) [member function]
    cls.add_method('UnregisterDeviceAdditionListener', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'listener')])
    ## node.h (module 'network'): void ns3::Node::UnregisterProtocolHandler(ns3::Callback<void, ns3::Ptr<ns3::NetDevice>, ns3::Ptr<ns3::Packet const>, unsigned short, ns3::Address const&, ns3::Address const&, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty> handler) [member function]
    cls.add_method('UnregisterProtocolHandler', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::NetDevice >, ns3::Ptr< ns3::Packet const >, unsigned short, ns3::Address const &, ns3::Address const &, ns3::NetDevice::PacketType, ns3::empty, ns3::empty, ns3::empty >', 'handler')])
    ## node.h (module 'network'): void ns3::Node::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## node.h (module 'network'): void ns3::Node::DoInitialize() [member function]
    cls.add_method('DoInitialize', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3NormalRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): ns3::NormalRandomVariable::INFINITE_VALUE [variable]
    cls.add_static_attribute('INFINITE_VALUE', 'double const', is_const=True)
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::NormalRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::NormalRandomVariable::NormalRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetVariance() const [member function]
    cls.add_method('GetVariance', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetValue(double mean, double variance, double bound=ns3::NormalRandomVariable::INFINITE_VALUE) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'variance'), param('double', 'bound', default_value='ns3::NormalRandomVariable::INFINITE_VALUE')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::NormalRandomVariable::GetInteger(uint32_t mean, uint32_t variance, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'variance'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::NormalRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::NormalRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3ObjectFactoryChecker_methods(root_module, cls):
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker::ObjectFactoryChecker() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryChecker::ObjectFactoryChecker(ns3::ObjectFactoryChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactoryChecker const &', 'arg0')])
    return

def register_Ns3ObjectFactoryValue_methods(root_module, cls):
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue() [constructor]
    cls.add_constructor([])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue(ns3::ObjectFactoryValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::ObjectFactoryValue const &', 'arg0')])
    ## object-factory.h (module 'core'): ns3::ObjectFactoryValue::ObjectFactoryValue(ns3::ObjectFactory const & value) [constructor]
    cls.add_constructor([param('ns3::ObjectFactory const &', 'value')])
    ## object-factory.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::ObjectFactoryValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## object-factory.h (module 'core'): bool ns3::ObjectFactoryValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## object-factory.h (module 'core'): ns3::ObjectFactory ns3::ObjectFactoryValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::ObjectFactory', 
                   [], 
                   is_const=True)
    ## object-factory.h (module 'core'): std::string ns3::ObjectFactoryValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## object-factory.h (module 'core'): void ns3::ObjectFactoryValue::Set(ns3::ObjectFactory const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::ObjectFactory const &', 'value')])
    return

def register_Ns3OutputStreamWrapper_methods(root_module, cls):
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper::OutputStreamWrapper(ns3::OutputStreamWrapper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::OutputStreamWrapper const &', 'arg0')])
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper::OutputStreamWrapper(std::string filename, std::_Ios_Openmode filemode) [constructor]
    cls.add_constructor([param('std::string', 'filename'), param('std::_Ios_Openmode', 'filemode')])
    ## output-stream-wrapper.h (module 'network'): ns3::OutputStreamWrapper::OutputStreamWrapper(std::ostream * os) [constructor]
    cls.add_constructor([param('std::ostream *', 'os')])
    ## output-stream-wrapper.h (module 'network'): std::ostream * ns3::OutputStreamWrapper::GetStream() [member function]
    cls.add_method('GetStream', 
                   'std::ostream *', 
                   [])
    return

def register_Ns3Packet_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## packet.h (module 'network'): ns3::Packet::Packet() [constructor]
    cls.add_constructor([])
    ## packet.h (module 'network'): ns3::Packet::Packet(ns3::Packet const & o) [copy constructor]
    cls.add_constructor([param('ns3::Packet const &', 'o')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint32_t size) [constructor]
    cls.add_constructor([param('uint32_t', 'size')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint8_t const * buffer, uint32_t size, bool magic) [constructor]
    cls.add_constructor([param('uint8_t const *', 'buffer'), param('uint32_t', 'size'), param('bool', 'magic')])
    ## packet.h (module 'network'): ns3::Packet::Packet(uint8_t const * buffer, uint32_t size) [constructor]
    cls.add_constructor([param('uint8_t const *', 'buffer'), param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::AddAtEnd(ns3::Ptr<ns3::Packet const> packet) [member function]
    cls.add_method('AddAtEnd', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet')])
    ## packet.h (module 'network'): void ns3::Packet::AddByteTag(ns3::Tag const & tag) const [member function]
    cls.add_method('AddByteTag', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::AddHeader(ns3::Header const & header) [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [param('ns3::Header const &', 'header')])
    ## packet.h (module 'network'): void ns3::Packet::AddPacketTag(ns3::Tag const & tag) const [member function]
    cls.add_method('AddPacketTag', 
                   'void', 
                   [param('ns3::Tag const &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::AddPaddingAtEnd(uint32_t size) [member function]
    cls.add_method('AddPaddingAtEnd', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::AddTrailer(ns3::Trailer const & trailer) [member function]
    cls.add_method('AddTrailer', 
                   'void', 
                   [param('ns3::Trailer const &', 'trailer')])
    ## packet.h (module 'network'): ns3::PacketMetadata::ItemIterator ns3::Packet::BeginItem() const [member function]
    cls.add_method('BeginItem', 
                   'ns3::PacketMetadata::ItemIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Packet::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::Packet >', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::CopyData(uint8_t * buffer, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'size')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::CopyData(std::ostream * os, uint32_t size) const [member function]
    cls.add_method('CopyData', 
                   'void', 
                   [param('std::ostream *', 'os'), param('uint32_t', 'size')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::Packet::CreateFragment(uint32_t start, uint32_t length) const [member function]
    cls.add_method('CreateFragment', 
                   'ns3::Ptr< ns3::Packet >', 
                   [param('uint32_t', 'start'), param('uint32_t', 'length')], 
                   is_const=True)
    ## packet.h (module 'network'): static void ns3::Packet::EnableChecking() [member function]
    cls.add_method('EnableChecking', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet.h (module 'network'): static void ns3::Packet::EnablePrinting() [member function]
    cls.add_method('EnablePrinting', 
                   'void', 
                   [], 
                   is_static=True)
    ## packet.h (module 'network'): bool ns3::Packet::FindFirstMatchingByteTag(ns3::Tag & tag) const [member function]
    cls.add_method('FindFirstMatchingByteTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::ByteTagIterator ns3::Packet::GetByteTagIterator() const [member function]
    cls.add_method('GetByteTagIterator', 
                   'ns3::ByteTagIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::Ptr<ns3::NixVector> ns3::Packet::GetNixVector() const [member function]
    cls.add_method('GetNixVector', 
                   'ns3::Ptr< ns3::NixVector >', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): ns3::PacketTagIterator ns3::Packet::GetPacketTagIterator() const [member function]
    cls.add_method('GetPacketTagIterator', 
                   'ns3::PacketTagIterator', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::GetSize() const [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint64_t ns3::Packet::GetUid() const [member function]
    cls.add_method('GetUid', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::PeekHeader(ns3::Header & header) const [member function]
    cls.add_method('PeekHeader', 
                   'uint32_t', 
                   [param('ns3::Header &', 'header')], 
                   is_const=True)
    ## packet.h (module 'network'): bool ns3::Packet::PeekPacketTag(ns3::Tag & tag) const [member function]
    cls.add_method('PeekPacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')], 
                   is_const=True)
    ## packet.h (module 'network'): uint32_t ns3::Packet::PeekTrailer(ns3::Trailer & trailer) [member function]
    cls.add_method('PeekTrailer', 
                   'uint32_t', 
                   [param('ns3::Trailer &', 'trailer')])
    ## packet.h (module 'network'): void ns3::Packet::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::PrintByteTags(std::ostream & os) const [member function]
    cls.add_method('PrintByteTags', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::PrintPacketTags(std::ostream & os) const [member function]
    cls.add_method('PrintPacketTags', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::RemoveAllByteTags() [member function]
    cls.add_method('RemoveAllByteTags', 
                   'void', 
                   [])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAllPacketTags() [member function]
    cls.add_method('RemoveAllPacketTags', 
                   'void', 
                   [])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAtEnd(uint32_t size) [member function]
    cls.add_method('RemoveAtEnd', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): void ns3::Packet::RemoveAtStart(uint32_t size) [member function]
    cls.add_method('RemoveAtStart', 
                   'void', 
                   [param('uint32_t', 'size')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::RemoveHeader(ns3::Header & header) [member function]
    cls.add_method('RemoveHeader', 
                   'uint32_t', 
                   [param('ns3::Header &', 'header')])
    ## packet.h (module 'network'): bool ns3::Packet::RemovePacketTag(ns3::Tag & tag) [member function]
    cls.add_method('RemovePacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::RemoveTrailer(ns3::Trailer & trailer) [member function]
    cls.add_method('RemoveTrailer', 
                   'uint32_t', 
                   [param('ns3::Trailer &', 'trailer')])
    ## packet.h (module 'network'): bool ns3::Packet::ReplacePacketTag(ns3::Tag & tag) [member function]
    cls.add_method('ReplacePacketTag', 
                   'bool', 
                   [param('ns3::Tag &', 'tag')])
    ## packet.h (module 'network'): uint32_t ns3::Packet::Serialize(uint8_t * buffer, uint32_t maxSize) const [member function]
    cls.add_method('Serialize', 
                   'uint32_t', 
                   [param('uint8_t *', 'buffer'), param('uint32_t', 'maxSize')], 
                   is_const=True)
    ## packet.h (module 'network'): void ns3::Packet::SetNixVector(ns3::Ptr<ns3::NixVector> nixVector) [member function]
    cls.add_method('SetNixVector', 
                   'void', 
                   [param('ns3::Ptr< ns3::NixVector >', 'nixVector')])
    ## packet.h (module 'network'): std::string ns3::Packet::ToString() const [member function]
    cls.add_method('ToString', 
                   'std::string', 
                   [], 
                   is_const=True)
    return

def register_Ns3ParetoRandomVariable_methods(root_module, cls):
    ## random-variable-stream.h (module 'core'): static ns3::TypeId ns3::ParetoRandomVariable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## random-variable-stream.h (module 'core'): ns3::ParetoRandomVariable::ParetoRandomVariable() [constructor]
    cls.add_constructor([])
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetMean() const [member function]
    cls.add_method('GetMean', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetShape() const [member function]
    cls.add_method('GetShape', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetBound() const [member function]
    cls.add_method('GetBound', 
                   'double', 
                   [], 
                   is_const=True)
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetValue(double mean, double shape, double bound) [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [param('double', 'mean'), param('double', 'shape'), param('double', 'bound')])
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ParetoRandomVariable::GetInteger(uint32_t mean, uint32_t shape, uint32_t bound) [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [param('uint32_t', 'mean'), param('uint32_t', 'shape'), param('uint32_t', 'bound')])
    ## random-variable-stream.h (module 'core'): double ns3::ParetoRandomVariable::GetValue() [member function]
    cls.add_method('GetValue', 
                   'double', 
                   [], 
                   is_virtual=True)
    ## random-variable-stream.h (module 'core'): uint32_t ns3::ParetoRandomVariable::GetInteger() [member function]
    cls.add_method('GetInteger', 
                   'uint32_t', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3QueueItem_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## net-device.h (module 'network'): ns3::QueueItem::QueueItem(ns3::Ptr<ns3::Packet> p) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet >', 'p')])
    ## net-device.h (module 'network'): ns3::Ptr<ns3::Packet> ns3::QueueItem::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet >', 
                   [], 
                   is_const=True)
    ## net-device.h (module 'network'): uint32_t ns3::QueueItem::GetPacketSize() const [member function]
    cls.add_method('GetPacketSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): bool ns3::QueueItem::GetUint8Value(ns3::QueueItem::Uint8Values field, uint8_t & value) const [member function]
    cls.add_method('GetUint8Value', 
                   'bool', 
                   [param('ns3::QueueItem::Uint8Values', 'field'), param('uint8_t &', 'value')], 
                   is_const=True, is_virtual=True)
    ## net-device.h (module 'network'): void ns3::QueueItem::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3Ssid_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## ssid.h (module 'wifi'): ns3::Ssid::Ssid(ns3::Ssid const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Ssid const &', 'arg0')])
    ## ssid.h (module 'wifi'): ns3::Ssid::Ssid() [constructor]
    cls.add_constructor([])
    ## ssid.h (module 'wifi'): ns3::Ssid::Ssid(std::string s) [constructor]
    cls.add_constructor([param('std::string', 's')])
    ## ssid.h (module 'wifi'): ns3::Ssid::Ssid(char const * ssid, uint8_t length) [constructor]
    cls.add_constructor([param('char const *', 'ssid'), param('uint8_t', 'length')])
    ## ssid.h (module 'wifi'): uint8_t ns3::Ssid::DeserializeInformationField(ns3::Buffer::Iterator start, uint8_t length) [member function]
    cls.add_method('DeserializeInformationField', 
                   'uint8_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint8_t', 'length')], 
                   is_virtual=True)
    ## ssid.h (module 'wifi'): ns3::WifiInformationElementId ns3::Ssid::ElementId() const [member function]
    cls.add_method('ElementId', 
                   'ns3::WifiInformationElementId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ssid.h (module 'wifi'): uint8_t ns3::Ssid::GetInformationFieldSize() const [member function]
    cls.add_method('GetInformationFieldSize', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ssid.h (module 'wifi'): bool ns3::Ssid::IsBroadcast() const [member function]
    cls.add_method('IsBroadcast', 
                   'bool', 
                   [], 
                   is_const=True)
    ## ssid.h (module 'wifi'): bool ns3::Ssid::IsEqual(ns3::Ssid const & o) const [member function]
    cls.add_method('IsEqual', 
                   'bool', 
                   [param('ns3::Ssid const &', 'o')], 
                   is_const=True)
    ## ssid.h (module 'wifi'): char * ns3::Ssid::PeekString() const [member function]
    cls.add_method('PeekString', 
                   'char *', 
                   [], 
                   is_const=True)
    ## ssid.h (module 'wifi'): void ns3::Ssid::SerializeInformationField(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('SerializeInformationField', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3SsidChecker_methods(root_module, cls):
    ## ssid.h (module 'wifi'): ns3::SsidChecker::SsidChecker() [constructor]
    cls.add_constructor([])
    ## ssid.h (module 'wifi'): ns3::SsidChecker::SsidChecker(ns3::SsidChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SsidChecker const &', 'arg0')])
    return

def register_Ns3SsidValue_methods(root_module, cls):
    ## ssid.h (module 'wifi'): ns3::SsidValue::SsidValue() [constructor]
    cls.add_constructor([])
    ## ssid.h (module 'wifi'): ns3::SsidValue::SsidValue(ns3::SsidValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::SsidValue const &', 'arg0')])
    ## ssid.h (module 'wifi'): ns3::SsidValue::SsidValue(ns3::Ssid const & value) [constructor]
    cls.add_constructor([param('ns3::Ssid const &', 'value')])
    ## ssid.h (module 'wifi'): ns3::Ptr<ns3::AttributeValue> ns3::SsidValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## ssid.h (module 'wifi'): bool ns3::SsidValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## ssid.h (module 'wifi'): ns3::Ssid ns3::SsidValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Ssid', 
                   [], 
                   is_const=True)
    ## ssid.h (module 'wifi'): std::string ns3::SsidValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## ssid.h (module 'wifi'): void ns3::SsidValue::Set(ns3::Ssid const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Ssid const &', 'value')])
    return

def register_Ns3TcpL4Protocol_methods(root_module, cls):
    ## tcp-l4-protocol.h (module 'internet'): ns3::TcpL4Protocol::PROT_NUMBER [variable]
    cls.add_static_attribute('PROT_NUMBER', 'uint8_t const', is_const=True)
    ## tcp-l4-protocol.h (module 'internet'): static ns3::TypeId ns3::TcpL4Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## tcp-l4-protocol.h (module 'internet'): ns3::TcpL4Protocol::TcpL4Protocol() [constructor]
    cls.add_constructor([])
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::TcpL4Protocol::CreateSocket() [member function]
    cls.add_method('CreateSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::TcpL4Protocol::CreateSocket(ns3::TypeId congestionTypeId) [member function]
    cls.add_method('CreateSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [param('ns3::TypeId', 'congestionTypeId')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::TcpL4Protocol::Allocate() [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::TcpL4Protocol::Allocate(ns3::Ipv4Address address) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('ns3::Ipv4Address', 'address')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::TcpL4Protocol::Allocate(uint16_t port) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('uint16_t', 'port')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::TcpL4Protocol::Allocate(ns3::Ipv4Address address, uint16_t port) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('ns3::Ipv4Address', 'address'), param('uint16_t', 'port')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::TcpL4Protocol::Allocate(ns3::Ipv4Address localAddress, uint16_t localPort, ns3::Ipv4Address peerAddress, uint16_t peerPort) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('ns3::Ipv4Address', 'localAddress'), param('uint16_t', 'localPort'), param('ns3::Ipv4Address', 'peerAddress'), param('uint16_t', 'peerPort')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::TcpL4Protocol::Allocate6() [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::TcpL4Protocol::Allocate6(ns3::Ipv6Address address) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('ns3::Ipv6Address', 'address')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::TcpL4Protocol::Allocate6(uint16_t port) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('uint16_t', 'port')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::TcpL4Protocol::Allocate6(ns3::Ipv6Address address, uint16_t port) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('ns3::Ipv6Address', 'address'), param('uint16_t', 'port')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::TcpL4Protocol::Allocate6(ns3::Ipv6Address localAddress, uint16_t localPort, ns3::Ipv6Address peerAddress, uint16_t peerPort) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('ns3::Ipv6Address', 'localAddress'), param('uint16_t', 'localPort'), param('ns3::Ipv6Address', 'peerAddress'), param('uint16_t', 'peerPort')])
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::SendPacket(ns3::Ptr<ns3::Packet> pkt, ns3::TcpHeader const & outgoing, ns3::Address const & saddr, ns3::Address const & daddr, ns3::Ptr<ns3::NetDevice> oif=0) const [member function]
    cls.add_method('SendPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'pkt'), param('ns3::TcpHeader const &', 'outgoing'), param('ns3::Address const &', 'saddr'), param('ns3::Address const &', 'daddr'), param('ns3::Ptr< ns3::NetDevice >', 'oif', default_value='0')], 
                   is_const=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::AddSocket(ns3::Ptr<ns3::TcpSocketBase> socket) [member function]
    cls.add_method('AddSocket', 
                   'void', 
                   [param('ns3::Ptr< ns3::TcpSocketBase >', 'socket')])
    ## tcp-l4-protocol.h (module 'internet'): bool ns3::TcpL4Protocol::RemoveSocket(ns3::Ptr<ns3::TcpSocketBase> socket) [member function]
    cls.add_method('RemoveSocket', 
                   'bool', 
                   [param('ns3::Ptr< ns3::TcpSocketBase >', 'socket')])
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::DeAllocate(ns3::Ipv4EndPoint * endPoint) [member function]
    cls.add_method('DeAllocate', 
                   'void', 
                   [param('ns3::Ipv4EndPoint *', 'endPoint')])
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::DeAllocate(ns3::Ipv6EndPoint * endPoint) [member function]
    cls.add_method('DeAllocate', 
                   'void', 
                   [param('ns3::Ipv6EndPoint *', 'endPoint')])
    ## tcp-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::TcpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & incomingIpHeader, ns3::Ptr<ns3::Ipv4Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'incomingIpHeader'), param('ns3::Ptr< ns3::Ipv4Interface >', 'incomingInterface')], 
                   is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::TcpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Header const & incomingIpHeader, ns3::Ptr<ns3::Ipv6Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Header const &', 'incomingIpHeader'), param('ns3::Ptr< ns3::Ipv6Interface >', 'incomingInterface')], 
                   is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::ReceiveIcmp(ns3::Ipv4Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv4Address payloadSource, ns3::Ipv4Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv4Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv4Address', 'payloadSource'), param('ns3::Ipv4Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::ReceiveIcmp(ns3::Ipv6Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv6Address payloadSource, ns3::Ipv6Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv6Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv6Address', 'payloadSource'), param('ns3::Ipv6Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::SetDownTarget(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::SetDownTarget6(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget6', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): int ns3::TcpL4Protocol::GetProtocolNumber() const [member function]
    cls.add_method('GetProtocolNumber', 
                   'int', 
                   [], 
                   is_const=True, is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::TcpL4Protocol::GetDownTarget() const [member function]
    cls.add_method('GetDownTarget', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::TcpL4Protocol::GetDownTarget6() const [member function]
    cls.add_method('GetDownTarget6', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## tcp-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::TcpL4Protocol::PacketReceived(ns3::Ptr<ns3::Packet> packet, ns3::TcpHeader & incomingTcpHeader, ns3::Address const & source, ns3::Address const & destination) [member function]
    cls.add_method('PacketReceived', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::TcpHeader &', 'incomingTcpHeader'), param('ns3::Address const &', 'source'), param('ns3::Address const &', 'destination')], 
                   visibility='protected')
    ## tcp-l4-protocol.h (module 'internet'): void ns3::TcpL4Protocol::NoEndPointsFound(ns3::TcpHeader const & incomingHeader, ns3::Address const & incomingSAddr, ns3::Address const & incomingDAddr) [member function]
    cls.add_method('NoEndPointsFound', 
                   'void', 
                   [param('ns3::TcpHeader const &', 'incomingHeader'), param('ns3::Address const &', 'incomingSAddr'), param('ns3::Address const &', 'incomingDAddr')], 
                   visibility='protected')
    return

def register_Ns3TimeValue_methods(root_module, cls):
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue() [constructor]
    cls.add_constructor([])
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue(ns3::TimeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TimeValue const &', 'arg0')])
    ## nstime.h (module 'core'): ns3::TimeValue::TimeValue(ns3::Time const & value) [constructor]
    cls.add_constructor([param('ns3::Time const &', 'value')])
    ## nstime.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::TimeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## nstime.h (module 'core'): bool ns3::TimeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## nstime.h (module 'core'): ns3::Time ns3::TimeValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## nstime.h (module 'core'): std::string ns3::TimeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## nstime.h (module 'core'): void ns3::TimeValue::Set(ns3::Time const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Time const &', 'value')])
    return

def register_Ns3TypeIdChecker_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeIdChecker::TypeIdChecker() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeIdChecker::TypeIdChecker(ns3::TypeIdChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeIdChecker const &', 'arg0')])
    return

def register_Ns3TypeIdValue_methods(root_module, cls):
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue() [constructor]
    cls.add_constructor([])
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue(ns3::TypeIdValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::TypeIdValue const &', 'arg0')])
    ## type-id.h (module 'core'): ns3::TypeIdValue::TypeIdValue(ns3::TypeId const & value) [constructor]
    cls.add_constructor([param('ns3::TypeId const &', 'value')])
    ## type-id.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::TypeIdValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## type-id.h (module 'core'): bool ns3::TypeIdValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## type-id.h (module 'core'): ns3::TypeId ns3::TypeIdValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True)
    ## type-id.h (module 'core'): std::string ns3::TypeIdValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## type-id.h (module 'core'): void ns3::TypeIdValue::Set(ns3::TypeId const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::TypeId const &', 'value')])
    return

def register_Ns3UdpL4Protocol_methods(root_module, cls):
    ## udp-l4-protocol.h (module 'internet'): ns3::UdpL4Protocol::PROT_NUMBER [variable]
    cls.add_static_attribute('PROT_NUMBER', 'uint8_t const', is_const=True)
    ## udp-l4-protocol.h (module 'internet'): static ns3::TypeId ns3::UdpL4Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## udp-l4-protocol.h (module 'internet'): ns3::UdpL4Protocol::UdpL4Protocol() [constructor]
    cls.add_constructor([])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## udp-l4-protocol.h (module 'internet'): int ns3::UdpL4Protocol::GetProtocolNumber() const [member function]
    cls.add_method('GetProtocolNumber', 
                   'int', 
                   [], 
                   is_const=True, is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): ns3::Ptr<ns3::Socket> ns3::UdpL4Protocol::CreateSocket() [member function]
    cls.add_method('CreateSocket', 
                   'ns3::Ptr< ns3::Socket >', 
                   [])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::UdpL4Protocol::Allocate() [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::UdpL4Protocol::Allocate(ns3::Ipv4Address address) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('ns3::Ipv4Address', 'address')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::UdpL4Protocol::Allocate(uint16_t port) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('uint16_t', 'port')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::UdpL4Protocol::Allocate(ns3::Ipv4Address address, uint16_t port) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('ns3::Ipv4Address', 'address'), param('uint16_t', 'port')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv4EndPoint * ns3::UdpL4Protocol::Allocate(ns3::Ipv4Address localAddress, uint16_t localPort, ns3::Ipv4Address peerAddress, uint16_t peerPort) [member function]
    cls.add_method('Allocate', 
                   'ns3::Ipv4EndPoint *', 
                   [param('ns3::Ipv4Address', 'localAddress'), param('uint16_t', 'localPort'), param('ns3::Ipv4Address', 'peerAddress'), param('uint16_t', 'peerPort')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::UdpL4Protocol::Allocate6() [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::UdpL4Protocol::Allocate6(ns3::Ipv6Address address) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('ns3::Ipv6Address', 'address')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::UdpL4Protocol::Allocate6(uint16_t port) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('uint16_t', 'port')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::UdpL4Protocol::Allocate6(ns3::Ipv6Address address, uint16_t port) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('ns3::Ipv6Address', 'address'), param('uint16_t', 'port')])
    ## udp-l4-protocol.h (module 'internet'): ns3::Ipv6EndPoint * ns3::UdpL4Protocol::Allocate6(ns3::Ipv6Address localAddress, uint16_t localPort, ns3::Ipv6Address peerAddress, uint16_t peerPort) [member function]
    cls.add_method('Allocate6', 
                   'ns3::Ipv6EndPoint *', 
                   [param('ns3::Ipv6Address', 'localAddress'), param('uint16_t', 'localPort'), param('ns3::Ipv6Address', 'peerAddress'), param('uint16_t', 'peerPort')])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::DeAllocate(ns3::Ipv4EndPoint * endPoint) [member function]
    cls.add_method('DeAllocate', 
                   'void', 
                   [param('ns3::Ipv4EndPoint *', 'endPoint')])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::DeAllocate(ns3::Ipv6EndPoint * endPoint) [member function]
    cls.add_method('DeAllocate', 
                   'void', 
                   [param('ns3::Ipv6EndPoint *', 'endPoint')])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address saddr, ns3::Ipv4Address daddr, uint16_t sport, uint16_t dport) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'saddr'), param('ns3::Ipv4Address', 'daddr'), param('uint16_t', 'sport'), param('uint16_t', 'dport')])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address saddr, ns3::Ipv4Address daddr, uint16_t sport, uint16_t dport, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'saddr'), param('ns3::Ipv4Address', 'daddr'), param('uint16_t', 'sport'), param('uint16_t', 'dport'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv6Address saddr, ns3::Ipv6Address daddr, uint16_t sport, uint16_t dport) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv6Address', 'saddr'), param('ns3::Ipv6Address', 'daddr'), param('uint16_t', 'sport'), param('uint16_t', 'dport')])
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv6Address saddr, ns3::Ipv6Address daddr, uint16_t sport, uint16_t dport, ns3::Ptr<ns3::Ipv6Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv6Address', 'saddr'), param('ns3::Ipv6Address', 'daddr'), param('uint16_t', 'sport'), param('uint16_t', 'dport'), param('ns3::Ptr< ns3::Ipv6Route >', 'route')])
    ## udp-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::UdpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::Ipv4Interface> interface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::Ipv4Interface >', 'interface')], 
                   is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::UdpL4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Header const & header, ns3::Ptr<ns3::Ipv6Interface> interface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Header const &', 'header'), param('ns3::Ptr< ns3::Ipv6Interface >', 'interface')], 
                   is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::ReceiveIcmp(ns3::Ipv4Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv4Address payloadSource, ns3::Ipv4Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv4Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv4Address', 'payloadSource'), param('ns3::Ipv4Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::ReceiveIcmp(ns3::Ipv6Address icmpSource, uint8_t icmpTtl, uint8_t icmpType, uint8_t icmpCode, uint32_t icmpInfo, ns3::Ipv6Address payloadSource, ns3::Ipv6Address payloadDestination, uint8_t const * payload) [member function]
    cls.add_method('ReceiveIcmp', 
                   'void', 
                   [param('ns3::Ipv6Address', 'icmpSource'), param('uint8_t', 'icmpTtl'), param('uint8_t', 'icmpType'), param('uint8_t', 'icmpCode'), param('uint32_t', 'icmpInfo'), param('ns3::Ipv6Address', 'payloadSource'), param('ns3::Ipv6Address', 'payloadDestination'), param('uint8_t const *', 'payload')], 
                   is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::SetDownTarget(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::SetDownTarget6(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget6', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::UdpL4Protocol::GetDownTarget() const [member function]
    cls.add_method('GetDownTarget', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::UdpL4Protocol::GetDownTarget6() const [member function]
    cls.add_method('GetDownTarget6', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## udp-l4-protocol.h (module 'internet'): void ns3::UdpL4Protocol::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3UintegerValue_methods(root_module, cls):
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue() [constructor]
    cls.add_constructor([])
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue(ns3::UintegerValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::UintegerValue const &', 'arg0')])
    ## uinteger.h (module 'core'): ns3::UintegerValue::UintegerValue(uint64_t const & value) [constructor]
    cls.add_constructor([param('uint64_t const &', 'value')])
    ## uinteger.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::UintegerValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## uinteger.h (module 'core'): bool ns3::UintegerValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## uinteger.h (module 'core'): uint64_t ns3::UintegerValue::Get() const [member function]
    cls.add_method('Get', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## uinteger.h (module 'core'): std::string ns3::UintegerValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## uinteger.h (module 'core'): void ns3::UintegerValue::Set(uint64_t const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('uint64_t const &', 'value')])
    return

def register_Ns3Vector2DChecker_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector2DChecker::Vector2DChecker() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector2DChecker::Vector2DChecker(ns3::Vector2DChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector2DChecker const &', 'arg0')])
    return

def register_Ns3Vector2DValue_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector2DValue::Vector2DValue() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector2DValue::Vector2DValue(ns3::Vector2DValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector2DValue const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector2DValue::Vector2DValue(ns3::Vector2D const & value) [constructor]
    cls.add_constructor([param('ns3::Vector2D const &', 'value')])
    ## vector.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::Vector2DValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): bool ns3::Vector2DValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## vector.h (module 'core'): ns3::Vector2D ns3::Vector2DValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Vector2D', 
                   [], 
                   is_const=True)
    ## vector.h (module 'core'): std::string ns3::Vector2DValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): void ns3::Vector2DValue::Set(ns3::Vector2D const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Vector2D const &', 'value')])
    return

def register_Ns3Vector3DChecker_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector3DChecker::Vector3DChecker() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector3DChecker::Vector3DChecker(ns3::Vector3DChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector3DChecker const &', 'arg0')])
    return

def register_Ns3Vector3DValue_methods(root_module, cls):
    ## vector.h (module 'core'): ns3::Vector3DValue::Vector3DValue() [constructor]
    cls.add_constructor([])
    ## vector.h (module 'core'): ns3::Vector3DValue::Vector3DValue(ns3::Vector3DValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Vector3DValue const &', 'arg0')])
    ## vector.h (module 'core'): ns3::Vector3DValue::Vector3DValue(ns3::Vector3D const & value) [constructor]
    cls.add_constructor([param('ns3::Vector3D const &', 'value')])
    ## vector.h (module 'core'): ns3::Ptr<ns3::AttributeValue> ns3::Vector3DValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): bool ns3::Vector3DValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## vector.h (module 'core'): ns3::Vector3D ns3::Vector3DValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Vector3D', 
                   [], 
                   is_const=True)
    ## vector.h (module 'core'): std::string ns3::Vector3DValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## vector.h (module 'core'): void ns3::Vector3DValue::Set(ns3::Vector3D const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Vector3D const &', 'value')])
    return

def register_Ns3VhtCapabilities_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilities::VhtCapabilities(ns3::VhtCapabilities const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::VhtCapabilities const &', 'arg0')])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilities::VhtCapabilities() [constructor]
    cls.add_constructor([])
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::DeserializeInformationField(ns3::Buffer::Iterator start, uint8_t length) [member function]
    cls.add_method('DeserializeInformationField', 
                   'uint8_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint8_t', 'length')], 
                   is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): ns3::WifiInformationElementId ns3::VhtCapabilities::ElementId() const [member function]
    cls.add_method('ElementId', 
                   'ns3::WifiInformationElementId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetInformationFieldSize() const [member function]
    cls.add_method('GetInformationFieldSize', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetMaxAmpduLengthExponent() const [member function]
    cls.add_method('GetMaxAmpduLengthExponent', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetMaxMpduLength() const [member function]
    cls.add_method('GetMaxMpduLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint16_t ns3::VhtCapabilities::GetRxHighestSupportedLgiDataRate() const [member function]
    cls.add_method('GetRxHighestSupportedLgiDataRate', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetRxLdpc() const [member function]
    cls.add_method('GetRxLdpc', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint16_t ns3::VhtCapabilities::GetRxMcsMap() const [member function]
    cls.add_method('GetRxMcsMap', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetRxStbc() const [member function]
    cls.add_method('GetRxStbc', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint16_t ns3::VhtCapabilities::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetShortGuardIntervalFor160Mhz() const [member function]
    cls.add_method('GetShortGuardIntervalFor160Mhz', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetShortGuardIntervalFor80Mhz() const [member function]
    cls.add_method('GetShortGuardIntervalFor80Mhz', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetSupportedChannelWidthSet() const [member function]
    cls.add_method('GetSupportedChannelWidthSet', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint64_t ns3::VhtCapabilities::GetSupportedMcsAndNssSet() const [member function]
    cls.add_method('GetSupportedMcsAndNssSet', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint16_t ns3::VhtCapabilities::GetTxHighestSupportedLgiDataRate() const [member function]
    cls.add_method('GetTxHighestSupportedLgiDataRate', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint16_t ns3::VhtCapabilities::GetTxMcsMap() const [member function]
    cls.add_method('GetTxMcsMap', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint8_t ns3::VhtCapabilities::GetTxStbc() const [member function]
    cls.add_method('GetTxStbc', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): uint32_t ns3::VhtCapabilities::GetVhtCapabilitiesInfo() const [member function]
    cls.add_method('GetVhtCapabilitiesInfo', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): bool ns3::VhtCapabilities::IsSupportedMcs(uint8_t mcs, uint8_t Nss) const [member function]
    cls.add_method('IsSupportedMcs', 
                   'bool', 
                   [param('uint8_t', 'mcs'), param('uint8_t', 'Nss')], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): bool ns3::VhtCapabilities::IsSupportedRxMcs(uint8_t mcs) const [member function]
    cls.add_method('IsSupportedRxMcs', 
                   'bool', 
                   [param('uint8_t', 'mcs')], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): bool ns3::VhtCapabilities::IsSupportedTxMcs(uint8_t mcs) const [member function]
    cls.add_method('IsSupportedTxMcs', 
                   'bool', 
                   [param('uint8_t', 'mcs')], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): ns3::Buffer::Iterator ns3::VhtCapabilities::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'ns3::Buffer::Iterator', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SerializeInformationField(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('SerializeInformationField', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetMaxAmpduLengthExponent(uint8_t exponent) [member function]
    cls.add_method('SetMaxAmpduLengthExponent', 
                   'void', 
                   [param('uint8_t', 'exponent')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetMaxMpduLength(uint8_t length) [member function]
    cls.add_method('SetMaxMpduLength', 
                   'void', 
                   [param('uint8_t', 'length')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetRxHighestSupportedLgiDataRate(uint16_t supporteddatarate) [member function]
    cls.add_method('SetRxHighestSupportedLgiDataRate', 
                   'void', 
                   [param('uint16_t', 'supporteddatarate')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetRxLdpc(uint8_t rxldpc) [member function]
    cls.add_method('SetRxLdpc', 
                   'void', 
                   [param('uint8_t', 'rxldpc')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetRxMcsMap(uint16_t map) [member function]
    cls.add_method('SetRxMcsMap', 
                   'void', 
                   [param('uint16_t', 'map')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetRxMcsMap(uint8_t mcs, uint8_t nss) [member function]
    cls.add_method('SetRxMcsMap', 
                   'void', 
                   [param('uint8_t', 'mcs'), param('uint8_t', 'nss')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetRxStbc(uint8_t rxstbc) [member function]
    cls.add_method('SetRxStbc', 
                   'void', 
                   [param('uint8_t', 'rxstbc')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetShortGuardIntervalFor160Mhz(uint8_t shortguardinterval) [member function]
    cls.add_method('SetShortGuardIntervalFor160Mhz', 
                   'void', 
                   [param('uint8_t', 'shortguardinterval')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetShortGuardIntervalFor80Mhz(uint8_t shortguardinterval) [member function]
    cls.add_method('SetShortGuardIntervalFor80Mhz', 
                   'void', 
                   [param('uint8_t', 'shortguardinterval')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetSupportedChannelWidthSet(uint8_t channelwidthset) [member function]
    cls.add_method('SetSupportedChannelWidthSet', 
                   'void', 
                   [param('uint8_t', 'channelwidthset')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetSupportedMcsAndNssSet(uint64_t ctrl) [member function]
    cls.add_method('SetSupportedMcsAndNssSet', 
                   'void', 
                   [param('uint64_t', 'ctrl')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetTxHighestSupportedLgiDataRate(uint16_t supporteddatarate) [member function]
    cls.add_method('SetTxHighestSupportedLgiDataRate', 
                   'void', 
                   [param('uint16_t', 'supporteddatarate')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetTxMcsMap(uint16_t map) [member function]
    cls.add_method('SetTxMcsMap', 
                   'void', 
                   [param('uint16_t', 'map')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetTxMcsMap(uint8_t mcs, uint8_t nss) [member function]
    cls.add_method('SetTxMcsMap', 
                   'void', 
                   [param('uint8_t', 'mcs'), param('uint8_t', 'nss')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetTxStbc(uint8_t txstbc) [member function]
    cls.add_method('SetTxStbc', 
                   'void', 
                   [param('uint8_t', 'txstbc')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetVhtCapabilitiesInfo(uint32_t ctrl) [member function]
    cls.add_method('SetVhtCapabilitiesInfo', 
                   'void', 
                   [param('uint32_t', 'ctrl')])
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilities::SetVhtSupported(uint8_t vhtsupported) [member function]
    cls.add_method('SetVhtSupported', 
                   'void', 
                   [param('uint8_t', 'vhtsupported')])
    return

def register_Ns3VhtCapabilitiesChecker_methods(root_module, cls):
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesChecker::VhtCapabilitiesChecker() [constructor]
    cls.add_constructor([])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesChecker::VhtCapabilitiesChecker(ns3::VhtCapabilitiesChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::VhtCapabilitiesChecker const &', 'arg0')])
    return

def register_Ns3VhtCapabilitiesValue_methods(root_module, cls):
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesValue::VhtCapabilitiesValue() [constructor]
    cls.add_constructor([])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesValue::VhtCapabilitiesValue(ns3::VhtCapabilitiesValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::VhtCapabilitiesValue const &', 'arg0')])
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilitiesValue::VhtCapabilitiesValue(ns3::VhtCapabilities const & value) [constructor]
    cls.add_constructor([param('ns3::VhtCapabilities const &', 'value')])
    ## vht-capabilities.h (module 'wifi'): ns3::Ptr<ns3::AttributeValue> ns3::VhtCapabilitiesValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): bool ns3::VhtCapabilitiesValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): ns3::VhtCapabilities ns3::VhtCapabilitiesValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::VhtCapabilities', 
                   [], 
                   is_const=True)
    ## vht-capabilities.h (module 'wifi'): std::string ns3::VhtCapabilitiesValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## vht-capabilities.h (module 'wifi'): void ns3::VhtCapabilitiesValue::Set(ns3::VhtCapabilities const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::VhtCapabilities const &', 'value')])
    return

def register_Ns3WifiChannel_methods(root_module, cls):
    ## wifi-channel.h (module 'wifi'): ns3::WifiChannel::WifiChannel() [constructor]
    cls.add_constructor([])
    ## wifi-channel.h (module 'wifi'): ns3::WifiChannel::WifiChannel(ns3::WifiChannel const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiChannel const &', 'arg0')])
    ## wifi-channel.h (module 'wifi'): static ns3::TypeId ns3::WifiChannel::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    return

def register_Ns3WifiModeChecker_methods(root_module, cls):
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeChecker::WifiModeChecker() [constructor]
    cls.add_constructor([])
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeChecker::WifiModeChecker(ns3::WifiModeChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiModeChecker const &', 'arg0')])
    return

def register_Ns3WifiModeValue_methods(root_module, cls):
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeValue::WifiModeValue() [constructor]
    cls.add_constructor([])
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeValue::WifiModeValue(ns3::WifiModeValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::WifiModeValue const &', 'arg0')])
    ## wifi-mode.h (module 'wifi'): ns3::WifiModeValue::WifiModeValue(ns3::WifiMode const & value) [constructor]
    cls.add_constructor([param('ns3::WifiMode const &', 'value')])
    ## wifi-mode.h (module 'wifi'): ns3::Ptr<ns3::AttributeValue> ns3::WifiModeValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## wifi-mode.h (module 'wifi'): bool ns3::WifiModeValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## wifi-mode.h (module 'wifi'): ns3::WifiMode ns3::WifiModeValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::WifiMode', 
                   [], 
                   is_const=True)
    ## wifi-mode.h (module 'wifi'): std::string ns3::WifiModeValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## wifi-mode.h (module 'wifi'): void ns3::WifiModeValue::Set(ns3::WifiMode const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::WifiMode const &', 'value')])
    return

def register_Ns3AddressChecker_methods(root_module, cls):
    ## address.h (module 'network'): ns3::AddressChecker::AddressChecker() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::AddressChecker::AddressChecker(ns3::AddressChecker const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AddressChecker const &', 'arg0')])
    return

def register_Ns3AddressValue_methods(root_module, cls):
    ## address.h (module 'network'): ns3::AddressValue::AddressValue() [constructor]
    cls.add_constructor([])
    ## address.h (module 'network'): ns3::AddressValue::AddressValue(ns3::AddressValue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::AddressValue const &', 'arg0')])
    ## address.h (module 'network'): ns3::AddressValue::AddressValue(ns3::Address const & value) [constructor]
    cls.add_constructor([param('ns3::Address const &', 'value')])
    ## address.h (module 'network'): ns3::Ptr<ns3::AttributeValue> ns3::AddressValue::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::Ptr< ns3::AttributeValue >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## address.h (module 'network'): bool ns3::AddressValue::DeserializeFromString(std::string value, ns3::Ptr<ns3::AttributeChecker const> checker) [member function]
    cls.add_method('DeserializeFromString', 
                   'bool', 
                   [param('std::string', 'value'), param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_virtual=True)
    ## address.h (module 'network'): ns3::Address ns3::AddressValue::Get() const [member function]
    cls.add_method('Get', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## address.h (module 'network'): std::string ns3::AddressValue::SerializeToString(ns3::Ptr<ns3::AttributeChecker const> checker) const [member function]
    cls.add_method('SerializeToString', 
                   'std::string', 
                   [param('ns3::Ptr< ns3::AttributeChecker const >', 'checker')], 
                   is_const=True, is_virtual=True)
    ## address.h (module 'network'): void ns3::AddressValue::Set(ns3::Address const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('ns3::Address const &', 'value')])
    return

def register_Ns3Icmpv4L4Protocol_methods(root_module, cls):
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::Icmpv4L4Protocol::Icmpv4L4Protocol(ns3::Icmpv4L4Protocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Icmpv4L4Protocol const &', 'arg0')])
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::Icmpv4L4Protocol::Icmpv4L4Protocol() [constructor]
    cls.add_constructor([])
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::Icmpv4L4Protocol::GetDownTarget() const [member function]
    cls.add_method('GetDownTarget', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::Icmpv4L4Protocol::GetDownTarget6() const [member function]
    cls.add_method('GetDownTarget6', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): int ns3::Icmpv4L4Protocol::GetProtocolNumber() const [member function]
    cls.add_method('GetProtocolNumber', 
                   'int', 
                   [], 
                   is_const=True, is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): static uint16_t ns3::Icmpv4L4Protocol::GetStaticProtocolNumber() [member function]
    cls.add_method('GetStaticProtocolNumber', 
                   'uint16_t', 
                   [], 
                   is_static=True)
    ## icmpv4-l4-protocol.h (module 'internet'): static ns3::TypeId ns3::Icmpv4L4Protocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::Icmpv4L4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::Ipv4Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::Ipv4Interface >', 'incomingInterface')], 
                   is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::IpL4Protocol::RxStatus ns3::Icmpv4L4Protocol::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Header const & header, ns3::Ptr<ns3::Ipv6Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Header const &', 'header'), param('ns3::Ptr< ns3::Ipv6Interface >', 'incomingInterface')], 
                   is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::SendDestUnreachFragNeeded(ns3::Ipv4Header header, ns3::Ptr<ns3::Packet const> orgData, uint16_t nextHopMtu) [member function]
    cls.add_method('SendDestUnreachFragNeeded', 
                   'void', 
                   [param('ns3::Ipv4Header', 'header'), param('ns3::Ptr< ns3::Packet const >', 'orgData'), param('uint16_t', 'nextHopMtu')])
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::SendDestUnreachPort(ns3::Ipv4Header header, ns3::Ptr<ns3::Packet const> orgData) [member function]
    cls.add_method('SendDestUnreachPort', 
                   'void', 
                   [param('ns3::Ipv4Header', 'header'), param('ns3::Ptr< ns3::Packet const >', 'orgData')])
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::SendTimeExceededTtl(ns3::Ipv4Header header, ns3::Ptr<ns3::Packet const> orgData) [member function]
    cls.add_method('SendTimeExceededTtl', 
                   'void', 
                   [param('ns3::Ipv4Header', 'header'), param('ns3::Ptr< ns3::Packet const >', 'orgData')])
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::SetDownTarget(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::SetDownTarget6(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetDownTarget6', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')], 
                   is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## icmpv4-l4-protocol.h (module 'internet'): ns3::Icmpv4L4Protocol::PROT_NUMBER [variable]
    cls.add_static_attribute('PROT_NUMBER', 'uint8_t const', is_const=True)
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## icmpv4-l4-protocol.h (module 'internet'): void ns3::Icmpv4L4Protocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3QueueDiscItem_methods(root_module, cls):
    ## queue-disc.h (module 'traffic-control'): ns3::QueueDiscItem::QueueDiscItem(ns3::Ptr<ns3::Packet> p, ns3::Address const & addr, uint16_t protocol) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Address const &', 'addr'), param('uint16_t', 'protocol')])
    ## queue-disc.h (module 'traffic-control'): ns3::Address ns3::QueueDiscItem::GetAddress() const [member function]
    cls.add_method('GetAddress', 
                   'ns3::Address', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint16_t ns3::QueueDiscItem::GetProtocol() const [member function]
    cls.add_method('GetProtocol', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): uint8_t ns3::QueueDiscItem::GetTxQueueIndex() const [member function]
    cls.add_method('GetTxQueueIndex', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDiscItem::SetTxQueueIndex(uint8_t txq) [member function]
    cls.add_method('SetTxQueueIndex', 
                   'void', 
                   [param('uint8_t', 'txq')])
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDiscItem::AddHeader() [member function]
    cls.add_method('AddHeader', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    ## queue-disc.h (module 'traffic-control'): void ns3::QueueDiscItem::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3HashImplementation_methods(root_module, cls):
    ## hash-function.h (module 'core'): ns3::Hash::Implementation::Implementation(ns3::Hash::Implementation const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Hash::Implementation const &', 'arg0')])
    ## hash-function.h (module 'core'): ns3::Hash::Implementation::Implementation() [constructor]
    cls.add_constructor([])
    ## hash-function.h (module 'core'): uint32_t ns3::Hash::Implementation::GetHash32(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_pure_virtual=True, is_virtual=True)
    ## hash-function.h (module 'core'): uint64_t ns3::Hash::Implementation::GetHash64(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash64', 
                   'uint64_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-function.h (module 'core'): void ns3::Hash::Implementation::clear() [member function]
    cls.add_method('clear', 
                   'void', 
                   [], 
                   is_pure_virtual=True, is_virtual=True)
    return

def register_Ns3HashFunctionFnv1a_methods(root_module, cls):
    ## hash-fnv.h (module 'core'): ns3::Hash::Function::Fnv1a::Fnv1a(ns3::Hash::Function::Fnv1a const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Hash::Function::Fnv1a const &', 'arg0')])
    ## hash-fnv.h (module 'core'): ns3::Hash::Function::Fnv1a::Fnv1a() [constructor]
    cls.add_constructor([])
    ## hash-fnv.h (module 'core'): uint32_t ns3::Hash::Function::Fnv1a::GetHash32(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-fnv.h (module 'core'): uint64_t ns3::Hash::Function::Fnv1a::GetHash64(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash64', 
                   'uint64_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-fnv.h (module 'core'): void ns3::Hash::Function::Fnv1a::clear() [member function]
    cls.add_method('clear', 
                   'void', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3HashFunctionHash32_methods(root_module, cls):
    ## hash-function.h (module 'core'): ns3::Hash::Function::Hash32::Hash32(ns3::Hash::Function::Hash32 const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Hash::Function::Hash32 const &', 'arg0')])
    ## hash-function.h (module 'core'): ns3::Hash::Function::Hash32::Hash32(ns3::Hash::Hash32Function_ptr hp) [constructor]
    cls.add_constructor([param('ns3::Hash::Hash32Function_ptr', 'hp')])
    ## hash-function.h (module 'core'): uint32_t ns3::Hash::Function::Hash32::GetHash32(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-function.h (module 'core'): void ns3::Hash::Function::Hash32::clear() [member function]
    cls.add_method('clear', 
                   'void', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3HashFunctionHash64_methods(root_module, cls):
    ## hash-function.h (module 'core'): ns3::Hash::Function::Hash64::Hash64(ns3::Hash::Function::Hash64 const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Hash::Function::Hash64 const &', 'arg0')])
    ## hash-function.h (module 'core'): ns3::Hash::Function::Hash64::Hash64(ns3::Hash::Hash64Function_ptr hp) [constructor]
    cls.add_constructor([param('ns3::Hash::Hash64Function_ptr', 'hp')])
    ## hash-function.h (module 'core'): uint32_t ns3::Hash::Function::Hash64::GetHash32(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-function.h (module 'core'): uint64_t ns3::Hash::Function::Hash64::GetHash64(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash64', 
                   'uint64_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-function.h (module 'core'): void ns3::Hash::Function::Hash64::clear() [member function]
    cls.add_method('clear', 
                   'void', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3HashFunctionMurmur3_methods(root_module, cls):
    ## hash-murmur3.h (module 'core'): ns3::Hash::Function::Murmur3::Murmur3(ns3::Hash::Function::Murmur3 const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::Hash::Function::Murmur3 const &', 'arg0')])
    ## hash-murmur3.h (module 'core'): ns3::Hash::Function::Murmur3::Murmur3() [constructor]
    cls.add_constructor([])
    ## hash-murmur3.h (module 'core'): uint32_t ns3::Hash::Function::Murmur3::GetHash32(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash32', 
                   'uint32_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-murmur3.h (module 'core'): uint64_t ns3::Hash::Function::Murmur3::GetHash64(char const * buffer, size_t const size) [member function]
    cls.add_method('GetHash64', 
                   'uint64_t', 
                   [param('char const *', 'buffer'), param('size_t const', 'size')], 
                   is_virtual=True)
    ## hash-murmur3.h (module 'core'): void ns3::Hash::Function::Murmur3::clear() [member function]
    cls.add_method('clear', 
                   'void', 
                   [], 
                   is_virtual=True)
    return

def register_Ns3DsrBlackList_methods(root_module, cls):
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList::BlackList(ns3::dsr::BlackList const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::BlackList const &', 'arg0')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList::BlackList(ns3::Ipv4Address ip, ns3::Time t) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ip'), param('ns3::Time', 't')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList::m_expireTime [variable]
    cls.add_instance_attribute('m_expireTime', 'ns3::Time', is_const=False)
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList::m_linkStates [variable]
    cls.add_instance_attribute('m_linkStates', 'ns3::dsr::LinkStates', is_const=False)
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList::m_neighborAddress [variable]
    cls.add_instance_attribute('m_neighborAddress', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrDsrErrorBuffEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsr-errorbuff.h (module 'dsr'): ns3::dsr::DsrErrorBuffEntry::DsrErrorBuffEntry(ns3::dsr::DsrErrorBuffEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrErrorBuffEntry const &', 'arg0')])
    ## dsr-errorbuff.h (module 'dsr'): ns3::dsr::DsrErrorBuffEntry::DsrErrorBuffEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Address d=ns3::Ipv4Address(), ns3::Ipv4Address s=ns3::Ipv4Address(), ns3::Ipv4Address n=ns3::Ipv4Address(), ns3::Time exp=ns3::Simulator::Now( ), uint8_t p=0) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Address', 'd', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 's', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 'n', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )'), param('uint8_t', 'p', default_value='0')])
    ## dsr-errorbuff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrErrorBuffEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): ns3::Time ns3::dsr::DsrErrorBuffEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrErrorBuffEntry::GetNextHop() const [member function]
    cls.add_method('GetNextHop', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): ns3::Ptr<ns3::Packet const> ns3::dsr::DsrErrorBuffEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): uint8_t ns3::dsr::DsrErrorBuffEntry::GetProtocol() const [member function]
    cls.add_method('GetProtocol', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrErrorBuffEntry::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffEntry::SetDestination(ns3::Ipv4Address d) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'd')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffEntry::SetNextHop(ns3::Ipv4Address n) [member function]
    cls.add_method('SetNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'n')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffEntry::SetProtocol(uint8_t p) [member function]
    cls.add_method('SetProtocol', 
                   'void', 
                   [param('uint8_t', 'p')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffEntry::SetSource(ns3::Ipv4Address s) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 's')])
    return

def register_Ns3DsrDsrErrorBuffer_methods(root_module, cls):
    ## dsr-errorbuff.h (module 'dsr'): ns3::dsr::DsrErrorBuffer::DsrErrorBuffer(ns3::dsr::DsrErrorBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrErrorBuffer const &', 'arg0')])
    ## dsr-errorbuff.h (module 'dsr'): ns3::dsr::DsrErrorBuffer::DsrErrorBuffer() [constructor]
    cls.add_constructor([])
    ## dsr-errorbuff.h (module 'dsr'): bool ns3::dsr::DsrErrorBuffer::Dequeue(ns3::Ipv4Address dst, ns3::dsr::DsrErrorBuffEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::dsr::DsrErrorBuffEntry &', 'entry')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffer::DropPacketForErrLink(ns3::Ipv4Address source, ns3::Ipv4Address nextHop) [member function]
    cls.add_method('DropPacketForErrLink', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'nextHop')])
    ## dsr-errorbuff.h (module 'dsr'): bool ns3::dsr::DsrErrorBuffer::Enqueue(ns3::dsr::DsrErrorBuffEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::dsr::DsrErrorBuffEntry &', 'entry')])
    ## dsr-errorbuff.h (module 'dsr'): bool ns3::dsr::DsrErrorBuffer::Find(ns3::Ipv4Address dst) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-errorbuff.h (module 'dsr'): std::vector<ns3::dsr::DsrErrorBuffEntry, std::allocator<ns3::dsr::DsrErrorBuffEntry> > & ns3::dsr::DsrErrorBuffer::GetBuffer() [member function]
    cls.add_method('GetBuffer', 
                   'std::vector< ns3::dsr::DsrErrorBuffEntry > &', 
                   [])
    ## dsr-errorbuff.h (module 'dsr'): ns3::Time ns3::dsr::DsrErrorBuffer::GetErrorBufferTimeout() const [member function]
    cls.add_method('GetErrorBufferTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): uint32_t ns3::dsr::DsrErrorBuffer::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-errorbuff.h (module 'dsr'): uint32_t ns3::dsr::DsrErrorBuffer::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffer::SetErrorBufferTimeout(ns3::Time t) [member function]
    cls.add_method('SetErrorBufferTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## dsr-errorbuff.h (module 'dsr'): void ns3::dsr::DsrErrorBuffer::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    return

def register_Ns3DsrDsrFsHeader_methods(root_module, cls):
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrFsHeader::DsrFsHeader(ns3::dsr::DsrFsHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrFsHeader const &', 'arg0')])
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrFsHeader::DsrFsHeader() [constructor]
    cls.add_constructor([])
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrFsHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): uint16_t ns3::dsr::DsrFsHeader::GetDestId() const [member function]
    cls.add_method('GetDestId', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-fs-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrFsHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): uint8_t ns3::dsr::DsrFsHeader::GetMessageType() const [member function]
    cls.add_method('GetMessageType', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-fs-header.h (module 'dsr'): uint8_t ns3::dsr::DsrFsHeader::GetNextHeader() const [member function]
    cls.add_method('GetNextHeader', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-fs-header.h (module 'dsr'): uint16_t ns3::dsr::DsrFsHeader::GetPayloadLength() const [member function]
    cls.add_method('GetPayloadLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrFsHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): uint16_t ns3::dsr::DsrFsHeader::GetSourceId() const [member function]
    cls.add_method('GetSourceId', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-fs-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrFsHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::SetDestId(uint16_t destId) [member function]
    cls.add_method('SetDestId', 
                   'void', 
                   [param('uint16_t', 'destId')])
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::SetMessageType(uint8_t messageType) [member function]
    cls.add_method('SetMessageType', 
                   'void', 
                   [param('uint8_t', 'messageType')])
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::SetNextHeader(uint8_t protocol) [member function]
    cls.add_method('SetNextHeader', 
                   'void', 
                   [param('uint8_t', 'protocol')])
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::SetPayloadLength(uint16_t length) [member function]
    cls.add_method('SetPayloadLength', 
                   'void', 
                   [param('uint16_t', 'length')])
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrFsHeader::SetSourceId(uint16_t sourceId) [member function]
    cls.add_method('SetSourceId', 
                   'void', 
                   [param('uint16_t', 'sourceId')])
    return

def register_Ns3DsrDsrGraReply_methods(root_module, cls):
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::DsrGraReply::DsrGraReply(ns3::dsr::DsrGraReply const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrGraReply const &', 'arg0')])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::DsrGraReply::DsrGraReply() [constructor]
    cls.add_constructor([])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): bool ns3::dsr::DsrGraReply::AddEntry(ns3::dsr::GraReplyEntry & graTableEntry) [member function]
    cls.add_method('AddEntry', 
                   'bool', 
                   [param('ns3::dsr::GraReplyEntry &', 'graTableEntry')])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): void ns3::dsr::DsrGraReply::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): bool ns3::dsr::DsrGraReply::FindAndUpdate(ns3::Ipv4Address replyTo, ns3::Ipv4Address replyFrom, ns3::Time gratReplyHoldoff) [member function]
    cls.add_method('FindAndUpdate', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'replyTo'), param('ns3::Ipv4Address', 'replyFrom'), param('ns3::Time', 'gratReplyHoldoff')])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): uint32_t ns3::dsr::DsrGraReply::GetGraTableSize() const [member function]
    cls.add_method('GetGraTableSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-gratuitous-reply-table.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrGraReply::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-gratuitous-reply-table.h (module 'dsr'): void ns3::dsr::DsrGraReply::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): void ns3::dsr::DsrGraReply::SetGraTableSize(uint32_t g) [member function]
    cls.add_method('SetGraTableSize', 
                   'void', 
                   [param('uint32_t', 'g')])
    return

def register_Ns3DsrDsrLinkStab_methods(root_module, cls):
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrLinkStab::DsrLinkStab(ns3::dsr::DsrLinkStab const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrLinkStab const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrLinkStab::DsrLinkStab(ns3::Time linkStab=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Time', 'linkStab', default_value='ns3::Simulator::Now( )')])
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrLinkStab::GetLinkStability() const [member function]
    cls.add_method('GetLinkStability', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrLinkStab::Print() const [member function]
    cls.add_method('Print', 
                   'void', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrLinkStab::SetLinkStability(ns3::Time linkStab) [member function]
    cls.add_method('SetLinkStability', 
                   'void', 
                   [param('ns3::Time', 'linkStab')])
    return

def register_Ns3DsrDsrMaintainBuffEntry_methods(root_module, cls):
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::DsrMaintainBuffEntry::DsrMaintainBuffEntry(ns3::dsr::DsrMaintainBuffEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrMaintainBuffEntry const &', 'arg0')])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::DsrMaintainBuffEntry::DsrMaintainBuffEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Address us=ns3::Ipv4Address(), ns3::Ipv4Address n=ns3::Ipv4Address(), ns3::Ipv4Address s=ns3::Ipv4Address(), ns3::Ipv4Address dst=ns3::Ipv4Address(), uint16_t ackId=0, uint8_t segs=0, ns3::Time exp=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Address', 'us', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 'n', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 's', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('uint16_t', 'ackId', default_value='0'), param('uint8_t', 'segs', default_value='0'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )')])
    ## dsr-maintain-buff.h (module 'dsr'): uint16_t ns3::dsr::DsrMaintainBuffEntry::GetAckId() const [member function]
    cls.add_method('GetAckId', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrMaintainBuffEntry::GetDst() const [member function]
    cls.add_method('GetDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Time ns3::dsr::DsrMaintainBuffEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrMaintainBuffEntry::GetNextHop() const [member function]
    cls.add_method('GetNextHop', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrMaintainBuffEntry::GetOurAdd() const [member function]
    cls.add_method('GetOurAdd', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Ptr<ns3::Packet const> ns3::dsr::DsrMaintainBuffEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): uint8_t ns3::dsr::DsrMaintainBuffEntry::GetSegsLeft() const [member function]
    cls.add_method('GetSegsLeft', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrMaintainBuffEntry::GetSrc() const [member function]
    cls.add_method('GetSrc', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetAckId(uint16_t ackId) [member function]
    cls.add_method('SetAckId', 
                   'void', 
                   [param('uint16_t', 'ackId')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetDst(ns3::Ipv4Address n) [member function]
    cls.add_method('SetDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'n')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetNextHop(ns3::Ipv4Address n) [member function]
    cls.add_method('SetNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'n')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetOurAdd(ns3::Ipv4Address us) [member function]
    cls.add_method('SetOurAdd', 
                   'void', 
                   [param('ns3::Ipv4Address', 'us')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetSegsLeft(uint8_t segs) [member function]
    cls.add_method('SetSegsLeft', 
                   'void', 
                   [param('uint8_t', 'segs')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffEntry::SetSrc(ns3::Ipv4Address s) [member function]
    cls.add_method('SetSrc', 
                   'void', 
                   [param('ns3::Ipv4Address', 's')])
    return

def register_Ns3DsrDsrMaintainBuffer_methods(root_module, cls):
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::DsrMaintainBuffer::DsrMaintainBuffer(ns3::dsr::DsrMaintainBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrMaintainBuffer const &', 'arg0')])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::DsrMaintainBuffer::DsrMaintainBuffer() [constructor]
    cls.add_constructor([])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::AllEqual(ns3::dsr::DsrMaintainBuffEntry & entry) [member function]
    cls.add_method('AllEqual', 
                   'bool', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'entry')])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::Dequeue(ns3::Ipv4Address dst, ns3::dsr::DsrMaintainBuffEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::dsr::DsrMaintainBuffEntry &', 'entry')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffer::DropPacketWithNextHop(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('DropPacketWithNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::Enqueue(ns3::dsr::DsrMaintainBuffEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'entry')])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::Find(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::Time ns3::dsr::DsrMaintainBuffer::GetMaintainBufferTimeout() const [member function]
    cls.add_method('GetMaintainBufferTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): uint32_t ns3::dsr::DsrMaintainBuffer::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-maintain-buff.h (module 'dsr'): uint32_t ns3::dsr::DsrMaintainBuffer::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::LinkEqual(ns3::dsr::DsrMaintainBuffEntry & entry) [member function]
    cls.add_method('LinkEqual', 
                   'bool', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'entry')])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::NetworkEqual(ns3::dsr::DsrMaintainBuffEntry & entry) [member function]
    cls.add_method('NetworkEqual', 
                   'bool', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'entry')])
    ## dsr-maintain-buff.h (module 'dsr'): bool ns3::dsr::DsrMaintainBuffer::PromiscEqual(ns3::dsr::DsrMaintainBuffEntry & entry) [member function]
    cls.add_method('PromiscEqual', 
                   'bool', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'entry')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffer::SetMaintainBufferTimeout(ns3::Time t) [member function]
    cls.add_method('SetMaintainBufferTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## dsr-maintain-buff.h (module 'dsr'): void ns3::dsr::DsrMaintainBuffer::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    return

def register_Ns3DsrDsrNetworkQueue_methods(root_module, cls):
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueue::DsrNetworkQueue(ns3::dsr::DsrNetworkQueue const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrNetworkQueue const &', 'arg0')])
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueue::DsrNetworkQueue() [constructor]
    cls.add_constructor([])
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueue::DsrNetworkQueue(uint32_t maxLen, ns3::Time maxDelay) [constructor]
    cls.add_constructor([param('uint32_t', 'maxLen'), param('ns3::Time', 'maxDelay')])
    ## dsr-network-queue.h (module 'dsr'): bool ns3::dsr::DsrNetworkQueue::Dequeue(ns3::dsr::DsrNetworkQueueEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::dsr::DsrNetworkQueueEntry &', 'entry')])
    ## dsr-network-queue.h (module 'dsr'): bool ns3::dsr::DsrNetworkQueue::Enqueue(ns3::dsr::DsrNetworkQueueEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::dsr::DsrNetworkQueueEntry &', 'entry')])
    ## dsr-network-queue.h (module 'dsr'): bool ns3::dsr::DsrNetworkQueue::Find(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## dsr-network-queue.h (module 'dsr'): bool ns3::dsr::DsrNetworkQueue::FindPacketWithNexthop(ns3::Ipv4Address nextHop, ns3::dsr::DsrNetworkQueueEntry & entry) [member function]
    cls.add_method('FindPacketWithNexthop', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('ns3::dsr::DsrNetworkQueueEntry &', 'entry')])
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueue::Flush() [member function]
    cls.add_method('Flush', 
                   'void', 
                   [])
    ## dsr-network-queue.h (module 'dsr'): ns3::Time ns3::dsr::DsrNetworkQueue::GetMaxNetworkDelay() const [member function]
    cls.add_method('GetMaxNetworkDelay', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): uint32_t ns3::dsr::DsrNetworkQueue::GetMaxNetworkSize() const [member function]
    cls.add_method('GetMaxNetworkSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): std::vector<ns3::dsr::DsrNetworkQueueEntry, std::allocator<ns3::dsr::DsrNetworkQueueEntry> > & ns3::dsr::DsrNetworkQueue::GetQueue() [member function]
    cls.add_method('GetQueue', 
                   'std::vector< ns3::dsr::DsrNetworkQueueEntry > &', 
                   [])
    ## dsr-network-queue.h (module 'dsr'): uint32_t ns3::dsr::DsrNetworkQueue::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## dsr-network-queue.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrNetworkQueue::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueue::SetMaxNetworkDelay(ns3::Time delay) [member function]
    cls.add_method('SetMaxNetworkDelay', 
                   'void', 
                   [param('ns3::Time', 'delay')])
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueue::SetMaxNetworkSize(uint32_t maxSize) [member function]
    cls.add_method('SetMaxNetworkSize', 
                   'void', 
                   [param('uint32_t', 'maxSize')])
    return

def register_Ns3DsrDsrNetworkQueueEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueueEntry::DsrNetworkQueueEntry(ns3::dsr::DsrNetworkQueueEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrNetworkQueueEntry const &', 'arg0')])
    ## dsr-network-queue.h (module 'dsr'): ns3::dsr::DsrNetworkQueueEntry::DsrNetworkQueueEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Address s=ns3::Ipv4Address(), ns3::Ipv4Address n=ns3::Ipv4Address(), ns3::Time exp=ns3::Simulator::Now( ), ns3::Ptr<ns3::Ipv4Route> r=0) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Address', 's', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 'n', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )'), param('ns3::Ptr< ns3::Ipv4Route >', 'r', default_value='0')])
    ## dsr-network-queue.h (module 'dsr'): ns3::Time ns3::dsr::DsrNetworkQueueEntry::GetInsertedTimeStamp() const [member function]
    cls.add_method('GetInsertedTimeStamp', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): ns3::Ptr<ns3::Ipv4Route> ns3::dsr::DsrNetworkQueueEntry::GetIpv4Route() const [member function]
    cls.add_method('GetIpv4Route', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrNetworkQueueEntry::GetNextHopAddress() const [member function]
    cls.add_method('GetNextHopAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): ns3::Ptr<ns3::Packet const> ns3::dsr::DsrNetworkQueueEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrNetworkQueueEntry::GetSourceAddress() const [member function]
    cls.add_method('GetSourceAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueueEntry::SetInsertedTimeStamp(ns3::Time time) [member function]
    cls.add_method('SetInsertedTimeStamp', 
                   'void', 
                   [param('ns3::Time', 'time')])
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueueEntry::SetIpv4Route(ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SetIpv4Route', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueueEntry::SetNextHopAddress(ns3::Ipv4Address addr) [member function]
    cls.add_method('SetNextHopAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueueEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## dsr-network-queue.h (module 'dsr'): void ns3::dsr::DsrNetworkQueueEntry::SetSourceAddress(ns3::Ipv4Address addr) [member function]
    cls.add_method('SetSourceAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'addr')])
    return

def register_Ns3DsrDsrNodeStab_methods(root_module, cls):
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrNodeStab::DsrNodeStab(ns3::dsr::DsrNodeStab const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrNodeStab const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrNodeStab::DsrNodeStab(ns3::Time nodeStab=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('ns3::Time', 'nodeStab', default_value='ns3::Simulator::Now( )')])
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrNodeStab::GetNodeStability() const [member function]
    cls.add_method('GetNodeStability', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrNodeStab::SetNodeStability(ns3::Time nodeStab) [member function]
    cls.add_method('SetNodeStability', 
                   'void', 
                   [param('ns3::Time', 'nodeStab')])
    return

def register_Ns3DsrDsrOptionField_methods(root_module, cls):
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrOptionField::DsrOptionField(ns3::dsr::DsrOptionField const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionField const &', 'arg0')])
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrOptionField::DsrOptionField(uint32_t optionsOffset) [constructor]
    cls.add_constructor([param('uint32_t', 'optionsOffset')])
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrOptionField::AddDsrOption(ns3::dsr::DsrOptionHeader const & option) [member function]
    cls.add_method('AddDsrOption', 
                   'void', 
                   [param('ns3::dsr::DsrOptionHeader const &', 'option')])
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionField::Deserialize(ns3::Buffer::Iterator start, uint32_t length) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'length')])
    ## dsr-fs-header.h (module 'dsr'): ns3::Buffer ns3::dsr::DsrOptionField::GetDsrOptionBuffer() [member function]
    cls.add_method('GetDsrOptionBuffer', 
                   'ns3::Buffer', 
                   [])
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionField::GetDsrOptionsOffset() [member function]
    cls.add_method('GetDsrOptionsOffset', 
                   'uint32_t', 
                   [])
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionField::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrOptionField::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    return

def register_Ns3DsrDsrOptionHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::DsrOptionHeader(ns3::dsr::DsrOptionHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::DsrOptionHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionHeader::GetLength() const [member function]
    cls.add_method('GetLength', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionHeader::GetType() const [member function]
    cls.add_method('GetType', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionHeader::SetLength(uint8_t length) [member function]
    cls.add_method('SetLength', 
                   'void', 
                   [param('uint8_t', 'length')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionHeader::SetType(uint8_t type) [member function]
    cls.add_method('SetType', 
                   'void', 
                   [param('uint8_t', 'type')])
    return

def register_Ns3DsrDsrOptionHeaderAlignment_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment::Alignment() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment::Alignment(ns3::dsr::DsrOptionHeader::Alignment const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionHeader::Alignment const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment::factor [variable]
    cls.add_instance_attribute('factor', 'uint8_t', is_const=False)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment::offset [variable]
    cls.add_instance_attribute('offset', 'uint8_t', is_const=False)
    return

def register_Ns3DsrDsrOptionPad1Header_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionPad1Header::DsrOptionPad1Header(ns3::dsr::DsrOptionPad1Header const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionPad1Header const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionPad1Header::DsrOptionPad1Header() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionPad1Header::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionPad1Header::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionPad1Header::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionPad1Header::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionPad1Header::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionPad1Header::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3DsrDsrOptionPadnHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionPadnHeader::DsrOptionPadnHeader(ns3::dsr::DsrOptionPadnHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionPadnHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionPadnHeader::DsrOptionPadnHeader(uint32_t pad=2) [constructor]
    cls.add_constructor([param('uint32_t', 'pad', default_value='2')])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionPadnHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionPadnHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionPadnHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionPadnHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionPadnHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionPadnHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3DsrDsrOptionRerrHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrHeader::DsrOptionRerrHeader(ns3::dsr::DsrOptionRerrHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRerrHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrHeader::DsrOptionRerrHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRerrHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionRerrHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrHeader::GetErrorDst() const [member function]
    cls.add_method('GetErrorDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrHeader::GetErrorSrc() const [member function]
    cls.add_method('GetErrorSrc', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerrHeader::GetErrorType() const [member function]
    cls.add_method('GetErrorType', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRerrHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerrHeader::GetSalvage() const [member function]
    cls.add_method('GetSalvage', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRerrHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRerrHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrHeader::SetErrorDst(ns3::Ipv4Address errorDstAddress) [member function]
    cls.add_method('SetErrorDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorDstAddress')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrHeader::SetErrorSrc(ns3::Ipv4Address errorSrcAddress) [member function]
    cls.add_method('SetErrorSrc', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorSrcAddress')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrHeader::SetErrorType(uint8_t errorType) [member function]
    cls.add_method('SetErrorType', 
                   'void', 
                   [param('uint8_t', 'errorType')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrHeader::SetSalvage(uint8_t salvage) [member function]
    cls.add_method('SetSalvage', 
                   'void', 
                   [param('uint8_t', 'salvage')], 
                   is_virtual=True)
    return

def register_Ns3DsrDsrOptionRerrUnreachHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrUnreachHeader::DsrOptionRerrUnreachHeader(ns3::dsr::DsrOptionRerrUnreachHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRerrUnreachHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrUnreachHeader::DsrOptionRerrUnreachHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRerrUnreachHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionRerrUnreachHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrUnreachHeader::GetErrorDst() const [member function]
    cls.add_method('GetErrorDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrUnreachHeader::GetErrorSrc() const [member function]
    cls.add_method('GetErrorSrc', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRerrUnreachHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrUnreachHeader::GetOriginalDst() const [member function]
    cls.add_method('GetOriginalDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerrUnreachHeader::GetSalvage() const [member function]
    cls.add_method('GetSalvage', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRerrUnreachHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRerrUnreachHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrUnreachHeader::GetUnreachNode() const [member function]
    cls.add_method('GetUnreachNode', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::SetErrorDst(ns3::Ipv4Address errorDstAddress) [member function]
    cls.add_method('SetErrorDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorDstAddress')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::SetErrorSrc(ns3::Ipv4Address errorSrcAddress) [member function]
    cls.add_method('SetErrorSrc', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorSrcAddress')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::SetOriginalDst(ns3::Ipv4Address originalDst) [member function]
    cls.add_method('SetOriginalDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'originalDst')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::SetSalvage(uint8_t salvage) [member function]
    cls.add_method('SetSalvage', 
                   'void', 
                   [param('uint8_t', 'salvage')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnreachHeader::SetUnreachNode(ns3::Ipv4Address unreachNode) [member function]
    cls.add_method('SetUnreachNode', 
                   'void', 
                   [param('ns3::Ipv4Address', 'unreachNode')])
    return

def register_Ns3DsrDsrOptionRerrUnsupportHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrUnsupportHeader::DsrOptionRerrUnsupportHeader(ns3::dsr::DsrOptionRerrUnsupportHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRerrUnsupportHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRerrUnsupportHeader::DsrOptionRerrUnsupportHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRerrUnsupportHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionRerrUnsupportHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrUnsupportHeader::GetErrorDst() const [member function]
    cls.add_method('GetErrorDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRerrUnsupportHeader::GetErrorSrc() const [member function]
    cls.add_method('GetErrorSrc', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRerrUnsupportHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerrUnsupportHeader::GetSalvage() const [member function]
    cls.add_method('GetSalvage', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRerrUnsupportHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRerrUnsupportHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): uint16_t ns3::dsr::DsrOptionRerrUnsupportHeader::GetUnsupported() const [member function]
    cls.add_method('GetUnsupported', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnsupportHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnsupportHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnsupportHeader::SetErrorDst(ns3::Ipv4Address errorDstAddress) [member function]
    cls.add_method('SetErrorDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorDstAddress')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnsupportHeader::SetErrorSrc(ns3::Ipv4Address errorSrcAddress) [member function]
    cls.add_method('SetErrorSrc', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorSrcAddress')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnsupportHeader::SetSalvage(uint8_t salvage) [member function]
    cls.add_method('SetSalvage', 
                   'void', 
                   [param('uint8_t', 'salvage')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRerrUnsupportHeader::SetUnsupported(uint16_t optionType) [member function]
    cls.add_method('SetUnsupported', 
                   'void', 
                   [param('uint16_t', 'optionType')])
    return

def register_Ns3DsrDsrOptionRrepHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRrepHeader::DsrOptionRrepHeader(ns3::dsr::DsrOptionRrepHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRrepHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRrepHeader::DsrOptionRrepHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRrepHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionRrepHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRrepHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRrepHeader::GetNodeAddress(uint8_t index) const [member function]
    cls.add_method('GetNodeAddress', 
                   'ns3::Ipv4Address', 
                   [param('uint8_t', 'index')], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::dsr::DsrOptionRrepHeader::GetNodesAddress() const [member function]
    cls.add_method('GetNodesAddress', 
                   'std::vector< ns3::Ipv4Address >', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRrepHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRrepHeader::GetTargetAddress(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ipv4Address) const [member function]
    cls.add_method('GetTargetAddress', 
                   'ns3::Ipv4Address', 
                   [param('std::vector< ns3::Ipv4Address >', 'ipv4Address')], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRrepHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRrepHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRrepHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRrepHeader::SetNodeAddress(uint8_t index, ns3::Ipv4Address addr) [member function]
    cls.add_method('SetNodeAddress', 
                   'void', 
                   [param('uint8_t', 'index'), param('ns3::Ipv4Address', 'addr')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRrepHeader::SetNodesAddress(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ipv4Address) [member function]
    cls.add_method('SetNodesAddress', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'ipv4Address')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRrepHeader::SetNumberAddress(uint8_t n) [member function]
    cls.add_method('SetNumberAddress', 
                   'void', 
                   [param('uint8_t', 'n')])
    return

def register_Ns3DsrDsrOptionRreqHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRreqHeader::DsrOptionRreqHeader(ns3::dsr::DsrOptionRreqHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRreqHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionRreqHeader::DsrOptionRreqHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::AddNodeAddress(ns3::Ipv4Address ipv4) [member function]
    cls.add_method('AddNodeAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'ipv4')])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRreqHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionRreqHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint16_t ns3::dsr::DsrOptionRreqHeader::GetId() const [member function]
    cls.add_method('GetId', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRreqHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRreqHeader::GetNodeAddress(uint8_t index) const [member function]
    cls.add_method('GetNodeAddress', 
                   'ns3::Ipv4Address', 
                   [param('uint8_t', 'index')], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::dsr::DsrOptionRreqHeader::GetNodesAddresses() const [member function]
    cls.add_method('GetNodesAddresses', 
                   'std::vector< ns3::Ipv4Address >', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRreqHeader::GetNodesNumber() const [member function]
    cls.add_method('GetNodesNumber', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionRreqHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionRreqHeader::GetTarget() [member function]
    cls.add_method('GetTarget', 
                   'ns3::Ipv4Address', 
                   [])
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRreqHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::SetId(uint16_t identification) [member function]
    cls.add_method('SetId', 
                   'void', 
                   [param('uint16_t', 'identification')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::SetNodeAddress(uint8_t index, ns3::Ipv4Address addr) [member function]
    cls.add_method('SetNodeAddress', 
                   'void', 
                   [param('uint8_t', 'index'), param('ns3::Ipv4Address', 'addr')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::SetNodesAddress(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ipv4Address) [member function]
    cls.add_method('SetNodesAddress', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'ipv4Address')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::SetNumberAddress(uint8_t n) [member function]
    cls.add_method('SetNumberAddress', 
                   'void', 
                   [param('uint8_t', 'n')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionRreqHeader::SetTarget(ns3::Ipv4Address target) [member function]
    cls.add_method('SetTarget', 
                   'void', 
                   [param('ns3::Ipv4Address', 'target')])
    return

def register_Ns3DsrDsrOptionSRHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionSRHeader::DsrOptionSRHeader(ns3::dsr::DsrOptionSRHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionSRHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionSRHeader::DsrOptionSRHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionSRHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionSRHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionSRHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionSRHeader::GetNodeAddress(uint8_t index) const [member function]
    cls.add_method('GetNodeAddress', 
                   'ns3::Ipv4Address', 
                   [param('uint8_t', 'index')], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionSRHeader::GetNodeListSize() const [member function]
    cls.add_method('GetNodeListSize', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::dsr::DsrOptionSRHeader::GetNodesAddress() const [member function]
    cls.add_method('GetNodesAddress', 
                   'std::vector< ns3::Ipv4Address >', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionSRHeader::GetSalvage() const [member function]
    cls.add_method('GetSalvage', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionSRHeader::GetSegmentsLeft() const [member function]
    cls.add_method('GetSegmentsLeft', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionSRHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionSRHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::SetNodeAddress(uint8_t index, ns3::Ipv4Address addr) [member function]
    cls.add_method('SetNodeAddress', 
                   'void', 
                   [param('uint8_t', 'index'), param('ns3::Ipv4Address', 'addr')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::SetNodesAddress(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ipv4Address) [member function]
    cls.add_method('SetNodesAddress', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'ipv4Address')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::SetNumberAddress(uint8_t n) [member function]
    cls.add_method('SetNumberAddress', 
                   'void', 
                   [param('uint8_t', 'n')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::SetSalvage(uint8_t salvage) [member function]
    cls.add_method('SetSalvage', 
                   'void', 
                   [param('uint8_t', 'salvage')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionSRHeader::SetSegmentsLeft(uint8_t segmentsLeft) [member function]
    cls.add_method('SetSegmentsLeft', 
                   'void', 
                   [param('uint8_t', 'segmentsLeft')])
    return

def register_Ns3DsrDsrOptions_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptions::DsrOptions(ns3::dsr::DsrOptions const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptions const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptions::DsrOptions() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): bool ns3::dsr::DsrOptions::CheckDuplicates(ns3::Ipv4Address ipv4Address, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('CheckDuplicates', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): bool ns3::dsr::DsrOptions::ContainAddressAfter(ns3::Ipv4Address ipv4Address, ns3::Ipv4Address destAddress, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & nodeList) [member function]
    cls.add_method('ContainAddressAfter', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'destAddress'), param('std::vector< ns3::Ipv4Address > &', 'nodeList')])
    ## dsr-options.h (module 'dsr'): std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::dsr::DsrOptions::CutRoute(ns3::Ipv4Address ipv4Address, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & nodeList) [member function]
    cls.add_method('CutRoute', 
                   'std::vector< ns3::Ipv4Address >', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('std::vector< ns3::Ipv4Address > &', 'nodeList')])
    ## dsr-options.h (module 'dsr'): uint32_t ns3::dsr::DsrOptions::GetIDfromIP(ns3::Ipv4Address address) [member function]
    cls.add_method('GetIDfromIP', 
                   'uint32_t', 
                   [param('ns3::Ipv4Address', 'address')])
    ## dsr-options.h (module 'dsr'): ns3::Ptr<ns3::Node> ns3::dsr::DsrOptions::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_const=True)
    ## dsr-options.h (module 'dsr'): ns3::Ptr<ns3::Node> ns3::dsr::DsrOptions::GetNodeWithAddress(ns3::Ipv4Address ipv4Address) [member function]
    cls.add_method('GetNodeWithAddress', 
                   'ns3::Ptr< ns3::Node >', 
                   [param('ns3::Ipv4Address', 'ipv4Address')])
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptions::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_pure_virtual=True, is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptions::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): bool ns3::dsr::DsrOptions::IfDuplicates(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec2) [member function]
    cls.add_method('IfDuplicates', 
                   'bool', 
                   [param('std::vector< ns3::Ipv4Address > &', 'vec'), param('std::vector< ns3::Ipv4Address > &', 'vec2')])
    ## dsr-options.h (module 'dsr'): void ns3::dsr::DsrOptions::PrintVector(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('PrintVector', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptions::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_pure_virtual=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): void ns3::dsr::DsrOptions::RemoveDuplicates(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('RemoveDuplicates', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): bool ns3::dsr::DsrOptions::ReverseRoutes(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('ReverseRoutes', 
                   'bool', 
                   [param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptions::ReverseSearchNextHop(ns3::Ipv4Address ipv4Address, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('ReverseSearchNextHop', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptions::ReverseSearchNextTwoHop(ns3::Ipv4Address ipv4Address, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('ReverseSearchNextTwoHop', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): void ns3::dsr::DsrOptions::ScheduleReply(ns3::Ptr<ns3::Packet> & packet, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & nodeList, ns3::Ipv4Address & source, ns3::Ipv4Address & destination) [member function]
    cls.add_method('ScheduleReply', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet > &', 'packet'), param('std::vector< ns3::Ipv4Address > &', 'nodeList'), param('ns3::Ipv4Address &', 'source'), param('ns3::Ipv4Address &', 'destination')])
    ## dsr-options.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptions::SearchNextHop(ns3::Ipv4Address ipv4Address, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('SearchNextHop', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-options.h (module 'dsr'): void ns3::dsr::DsrOptions::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## dsr-options.h (module 'dsr'): ns3::Ptr<ns3::Ipv4Route> ns3::dsr::DsrOptions::SetRoute(ns3::Ipv4Address nextHop, ns3::Ipv4Address srcAddress) [member function]
    cls.add_method('SetRoute', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('ns3::Ipv4Address', 'srcAddress')], 
                   is_virtual=True)
    return

def register_Ns3DsrDsrPassiveBuffEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsr-passive-buff.h (module 'dsr'): ns3::dsr::DsrPassiveBuffEntry::DsrPassiveBuffEntry(ns3::dsr::DsrPassiveBuffEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrPassiveBuffEntry const &', 'arg0')])
    ## dsr-passive-buff.h (module 'dsr'): ns3::dsr::DsrPassiveBuffEntry::DsrPassiveBuffEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Address d=ns3::Ipv4Address(), ns3::Ipv4Address s=ns3::Ipv4Address(), ns3::Ipv4Address n=ns3::Ipv4Address(), uint16_t i=0, uint16_t f=0, uint8_t seg=0, ns3::Time exp=ns3::Simulator::Now( ), uint8_t p=0) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Address', 'd', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 's', default_value='ns3::Ipv4Address()'), param('ns3::Ipv4Address', 'n', default_value='ns3::Ipv4Address()'), param('uint16_t', 'i', default_value='0'), param('uint16_t', 'f', default_value='0'), param('uint8_t', 'seg', default_value='0'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )'), param('uint8_t', 'p', default_value='0')])
    ## dsr-passive-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrPassiveBuffEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): ns3::Time ns3::dsr::DsrPassiveBuffEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): uint16_t ns3::dsr::DsrPassiveBuffEntry::GetFragmentOffset() const [member function]
    cls.add_method('GetFragmentOffset', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): uint16_t ns3::dsr::DsrPassiveBuffEntry::GetIdentification() const [member function]
    cls.add_method('GetIdentification', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrPassiveBuffEntry::GetNextHop() const [member function]
    cls.add_method('GetNextHop', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): ns3::Ptr<ns3::Packet const> ns3::dsr::DsrPassiveBuffEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): uint8_t ns3::dsr::DsrPassiveBuffEntry::GetProtocol() const [member function]
    cls.add_method('GetProtocol', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): uint8_t ns3::dsr::DsrPassiveBuffEntry::GetSegsLeft() const [member function]
    cls.add_method('GetSegsLeft', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrPassiveBuffEntry::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetDestination(ns3::Ipv4Address d) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'd')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetFragmentOffset(uint16_t f) [member function]
    cls.add_method('SetFragmentOffset', 
                   'void', 
                   [param('uint16_t', 'f')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetIdentification(uint16_t i) [member function]
    cls.add_method('SetIdentification', 
                   'void', 
                   [param('uint16_t', 'i')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetNextHop(ns3::Ipv4Address n) [member function]
    cls.add_method('SetNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'n')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetProtocol(uint8_t p) [member function]
    cls.add_method('SetProtocol', 
                   'void', 
                   [param('uint8_t', 'p')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetSegsLeft(uint8_t seg) [member function]
    cls.add_method('SetSegsLeft', 
                   'void', 
                   [param('uint8_t', 'seg')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffEntry::SetSource(ns3::Ipv4Address s) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 's')])
    return

def register_Ns3DsrDsrPassiveBuffer_methods(root_module, cls):
    ## dsr-passive-buff.h (module 'dsr'): ns3::dsr::DsrPassiveBuffer::DsrPassiveBuffer(ns3::dsr::DsrPassiveBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrPassiveBuffer const &', 'arg0')])
    ## dsr-passive-buff.h (module 'dsr'): ns3::dsr::DsrPassiveBuffer::DsrPassiveBuffer() [constructor]
    cls.add_constructor([])
    ## dsr-passive-buff.h (module 'dsr'): bool ns3::dsr::DsrPassiveBuffer::AllEqual(ns3::dsr::DsrPassiveBuffEntry & entry) [member function]
    cls.add_method('AllEqual', 
                   'bool', 
                   [param('ns3::dsr::DsrPassiveBuffEntry &', 'entry')])
    ## dsr-passive-buff.h (module 'dsr'): bool ns3::dsr::DsrPassiveBuffer::Dequeue(ns3::Ipv4Address dst, ns3::dsr::DsrPassiveBuffEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::dsr::DsrPassiveBuffEntry &', 'entry')])
    ## dsr-passive-buff.h (module 'dsr'): bool ns3::dsr::DsrPassiveBuffer::Enqueue(ns3::dsr::DsrPassiveBuffEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::dsr::DsrPassiveBuffEntry &', 'entry')])
    ## dsr-passive-buff.h (module 'dsr'): bool ns3::dsr::DsrPassiveBuffer::Find(ns3::Ipv4Address dst) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-passive-buff.h (module 'dsr'): uint32_t ns3::dsr::DsrPassiveBuffer::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): ns3::Time ns3::dsr::DsrPassiveBuffer::GetPassiveBufferTimeout() const [member function]
    cls.add_method('GetPassiveBufferTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-passive-buff.h (module 'dsr'): uint32_t ns3::dsr::DsrPassiveBuffer::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## dsr-passive-buff.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrPassiveBuffer::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffer::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## dsr-passive-buff.h (module 'dsr'): void ns3::dsr::DsrPassiveBuffer::SetPassiveBufferTimeout(ns3::Time t) [member function]
    cls.add_method('SetPassiveBufferTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    return

def register_Ns3DsrDsrReceivedRreqEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::DsrReceivedRreqEntry::DsrReceivedRreqEntry(ns3::dsr::DsrReceivedRreqEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrReceivedRreqEntry const &', 'arg0')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::DsrReceivedRreqEntry::DsrReceivedRreqEntry(ns3::Ipv4Address d=ns3::Ipv4Address(), uint16_t i=0) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'd', default_value='ns3::Ipv4Address()'), param('uint16_t', 'i', default_value='0')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrReceivedRreqEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): ns3::Time ns3::dsr::DsrReceivedRreqEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): uint16_t ns3::dsr::DsrReceivedRreqEntry::GetIdentification() const [member function]
    cls.add_method('GetIdentification', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrReceivedRreqEntry::GetSource() const [member function]
    cls.add_method('GetSource', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrReceivedRreqEntry::SetDestination(ns3::Ipv4Address d) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'd')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrReceivedRreqEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrReceivedRreqEntry::SetIdentification(uint16_t i) [member function]
    cls.add_method('SetIdentification', 
                   'void', 
                   [param('uint16_t', 'i')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrReceivedRreqEntry::SetSource(ns3::Ipv4Address s) [member function]
    cls.add_method('SetSource', 
                   'void', 
                   [param('ns3::Ipv4Address', 's')])
    return

def register_Ns3DsrDsrRouteCache_methods(root_module, cls):
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::DsrRouteCache(ns3::dsr::DsrRouteCache const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrRouteCache const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::DsrRouteCache() [constructor]
    cls.add_constructor([])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::AddArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('AddArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::AddNeighbor(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > nodeList, ns3::Ipv4Address ownAddress, ns3::Time expire) [member function]
    cls.add_method('AddNeighbor', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'nodeList'), param('ns3::Ipv4Address', 'ownAddress'), param('ns3::Time', 'expire')])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::AddRoute(ns3::dsr::DsrRouteCacheEntry & rt) [member function]
    cls.add_method('AddRoute', 
                   'bool', 
                   [param('ns3::dsr::DsrRouteCacheEntry &', 'rt')])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::AddRoute_Link(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > nodelist, ns3::Ipv4Address node) [member function]
    cls.add_method('AddRoute_Link', 
                   'bool', 
                   [param('std::vector< ns3::Ipv4Address >', 'nodelist'), param('ns3::Ipv4Address', 'node')])
    ## dsr-rcache.h (module 'dsr'): uint16_t ns3::dsr::DsrRouteCache::CheckUniqueAckId(ns3::Ipv4Address nextHop) [member function]
    cls.add_method('CheckUniqueAckId', 
                   'uint16_t', 
                   [param('ns3::Ipv4Address', 'nextHop')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::Clear() [member function]
    cls.add_method('Clear', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::ClearMac() [member function]
    cls.add_method('ClearMac', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::DelArpCache(ns3::Ptr<ns3::ArpCache> arg0) [member function]
    cls.add_method('DelArpCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::ArpCache >', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::DeleteAllRoutesIncludeLink(ns3::Ipv4Address errorSrc, ns3::Ipv4Address unreachNode, ns3::Ipv4Address node) [member function]
    cls.add_method('DeleteAllRoutesIncludeLink', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorSrc'), param('ns3::Ipv4Address', 'unreachNode'), param('ns3::Ipv4Address', 'node')])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::DeleteRoute(ns3::Ipv4Address dst) [member function]
    cls.add_method('DeleteRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::FindSameRoute(ns3::dsr::DsrRouteCacheEntry & rt, std::list<ns3::dsr::DsrRouteCacheEntry, std::allocator<ns3::dsr::DsrRouteCacheEntry> > & rtVector) [member function]
    cls.add_method('FindSameRoute', 
                   'bool', 
                   [param('ns3::dsr::DsrRouteCacheEntry &', 'rt'), param('std::list< ns3::dsr::DsrRouteCacheEntry > &', 'rtVector')])
    ## dsr-rcache.h (module 'dsr'): uint16_t ns3::dsr::DsrRouteCache::GetAckSize() [member function]
    cls.add_method('GetAckSize', 
                   'uint16_t', 
                   [])
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCache::GetBadLinkLifetime() const [member function]
    cls.add_method('GetBadLinkLifetime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCache::GetCacheTimeout() const [member function]
    cls.add_method('GetCacheTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Callback<void, ns3::Ipv4Address, unsigned char, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::dsr::DsrRouteCache::GetCallback() const [member function]
    cls.add_method('GetCallback', 
                   'ns3::Callback< void, ns3::Ipv4Address, unsigned char, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCache::GetExpireTime(ns3::Ipv4Address addr) [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCache::GetInitStability() const [member function]
    cls.add_method('GetInitStability', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): uint32_t ns3::dsr::DsrRouteCache::GetMaxCacheLen() const [member function]
    cls.add_method('GetMaxCacheLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): uint32_t ns3::dsr::DsrRouteCache::GetMaxEntriesEachDst() const [member function]
    cls.add_method('GetMaxEntriesEachDst', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCache::GetMinLifeTime() const [member function]
    cls.add_method('GetMinLifeTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): uint64_t ns3::dsr::DsrRouteCache::GetStabilityDecrFactor() const [member function]
    cls.add_method('GetStabilityDecrFactor', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): uint64_t ns3::dsr::DsrRouteCache::GetStabilityIncrFactor() const [member function]
    cls.add_method('GetStabilityIncrFactor', 
                   'uint64_t', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::GetSubRoute() const [member function]
    cls.add_method('GetSubRoute', 
                   'bool', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Callback<void, ns3::WifiMacHeader const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::dsr::DsrRouteCache::GetTxErrorCallback() const [member function]
    cls.add_method('GetTxErrorCallback', 
                   'ns3::Callback< void, ns3::WifiMacHeader const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrRouteCache::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCache::GetUseExtends() const [member function]
    cls.add_method('GetUseExtends', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::IsLinkCache() [member function]
    cls.add_method('IsLinkCache', 
                   'bool', 
                   [])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::IsNeighbor(ns3::Ipv4Address addr) [member function]
    cls.add_method('IsNeighbor', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'addr')])
    ## dsr-rcache.h (module 'dsr'): ns3::Mac48Address ns3::dsr::DsrRouteCache::LookupMacAddress(ns3::Ipv4Address arg0) [member function]
    cls.add_method('LookupMacAddress', 
                   'ns3::Mac48Address', 
                   [param('ns3::Ipv4Address', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::LookupRoute(ns3::Ipv4Address id, ns3::dsr::DsrRouteCacheEntry & rt) [member function]
    cls.add_method('LookupRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id'), param('ns3::dsr::DsrRouteCacheEntry &', 'rt')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::Print(std::ostream & os) [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::PrintRouteVector(std::list<ns3::dsr::DsrRouteCacheEntry, std::allocator<ns3::dsr::DsrRouteCacheEntry> > route) [member function]
    cls.add_method('PrintRouteVector', 
                   'void', 
                   [param('std::list< ns3::dsr::DsrRouteCacheEntry >', 'route')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::PrintVector(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('PrintVector', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::ProcessTxError(ns3::WifiMacHeader const & arg0) [member function]
    cls.add_method('ProcessTxError', 
                   'void', 
                   [param('ns3::WifiMacHeader const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::Purge() [member function]
    cls.add_method('Purge', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::PurgeLinkNode() [member function]
    cls.add_method('PurgeLinkNode', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::PurgeMac() [member function]
    cls.add_method('PurgeMac', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::RebuildBestRouteTable(ns3::Ipv4Address source) [member function]
    cls.add_method('RebuildBestRouteTable', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::RemoveLastEntry(std::list<ns3::dsr::DsrRouteCacheEntry, std::allocator<ns3::dsr::DsrRouteCacheEntry> > & rtVector) [member function]
    cls.add_method('RemoveLastEntry', 
                   'void', 
                   [param('std::list< ns3::dsr::DsrRouteCacheEntry > &', 'rtVector')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::ScheduleTimer() [member function]
    cls.add_method('ScheduleTimer', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetBadLinkLifetime(ns3::Time t) [member function]
    cls.add_method('SetBadLinkLifetime', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetCacheTimeout(ns3::Time t) [member function]
    cls.add_method('SetCacheTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetCacheType(std::string type) [member function]
    cls.add_method('SetCacheType', 
                   'void', 
                   [param('std::string', 'type')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetCallback(ns3::Callback<void, ns3::Ipv4Address, unsigned char, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> cb) [member function]
    cls.add_method('SetCallback', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ipv4Address, unsigned char, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'cb')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetInitStability(ns3::Time initStability) [member function]
    cls.add_method('SetInitStability', 
                   'void', 
                   [param('ns3::Time', 'initStability')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetMaxCacheLen(uint32_t len) [member function]
    cls.add_method('SetMaxCacheLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetMaxEntriesEachDst(uint32_t entries) [member function]
    cls.add_method('SetMaxEntriesEachDst', 
                   'void', 
                   [param('uint32_t', 'entries')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetMinLifeTime(ns3::Time minLifeTime) [member function]
    cls.add_method('SetMinLifeTime', 
                   'void', 
                   [param('ns3::Time', 'minLifeTime')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetStabilityDecrFactor(uint64_t decrFactor) [member function]
    cls.add_method('SetStabilityDecrFactor', 
                   'void', 
                   [param('uint64_t', 'decrFactor')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetStabilityIncrFactor(uint64_t incrFactor) [member function]
    cls.add_method('SetStabilityIncrFactor', 
                   'void', 
                   [param('uint64_t', 'incrFactor')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetSubRoute(bool subRoute) [member function]
    cls.add_method('SetSubRoute', 
                   'void', 
                   [param('bool', 'subRoute')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::SetUseExtends(ns3::Time useExtends) [member function]
    cls.add_method('SetUseExtends', 
                   'void', 
                   [param('ns3::Time', 'useExtends')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::UpdateNeighbor(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > nodeList, ns3::Time expire) [member function]
    cls.add_method('UpdateNeighbor', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'nodeList'), param('ns3::Time', 'expire')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::UpdateNetGraph() [member function]
    cls.add_method('UpdateNetGraph', 
                   'void', 
                   [])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCache::UpdateRouteEntry(ns3::Ipv4Address dst) [member function]
    cls.add_method('UpdateRouteEntry', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCache::UseExtends(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > rt) [member function]
    cls.add_method('UseExtends', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'rt')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::m_arp [variable]
    cls.add_instance_attribute('m_arp', 'std::vector< ns3::Ptr< ns3::ArpCache > >', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::m_delay [variable]
    cls.add_instance_attribute('m_delay', 'ns3::Time', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::m_handleLinkFailure [variable]
    cls.add_instance_attribute('m_handleLinkFailure', 'ns3::Callback< void, ns3::Ipv4Address, unsigned char, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::m_nb [variable]
    cls.add_instance_attribute('m_nb', 'std::vector< ns3::dsr::DsrRouteCache::Neighbor >', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::m_ntimer [variable]
    cls.add_instance_attribute('m_ntimer', 'ns3::Timer', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::m_txErrorCallback [variable]
    cls.add_instance_attribute('m_txErrorCallback', 'ns3::Callback< void, ns3::WifiMacHeader const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', is_const=False)
    return

def register_Ns3DsrDsrRouteCacheNeighbor_methods(root_module, cls):
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::Neighbor(ns3::dsr::DsrRouteCache::Neighbor const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrRouteCache::Neighbor const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::Neighbor(ns3::Ipv4Address ip, ns3::Mac48Address mac, ns3::Time t) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ip'), param('ns3::Mac48Address', 'mac'), param('ns3::Time', 't')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::Neighbor() [constructor]
    cls.add_constructor([])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::close [variable]
    cls.add_instance_attribute('close', 'bool', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::m_expireTime [variable]
    cls.add_instance_attribute('m_expireTime', 'ns3::Time', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::m_hardwareAddress [variable]
    cls.add_instance_attribute('m_hardwareAddress', 'ns3::Mac48Address', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCache::Neighbor::m_neighborAddress [variable]
    cls.add_instance_attribute('m_neighborAddress', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrDsrRouteCacheEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCacheEntry::DsrRouteCacheEntry(ns3::dsr::DsrRouteCacheEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrRouteCacheEntry const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::DsrRouteCacheEntry::DsrRouteCacheEntry(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > const & ip=std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> >(), ns3::Ipv4Address dst=ns3::Ipv4Address(), ns3::Time exp=ns3::Simulator::Now( )) [constructor]
    cls.add_constructor([param('std::vector< ns3::Ipv4Address > const &', 'ip', default_value='std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> >()'), param('ns3::Ipv4Address', 'dst', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )')])
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCacheEntry::GetBlacklistTimeout() const [member function]
    cls.add_method('GetBlacklistTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrRouteCacheEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::Time ns3::dsr::DsrRouteCacheEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::dsr::DsrRouteCacheEntry::GetVector() const [member function]
    cls.add_method('GetVector', 
                   'std::vector< ns3::Ipv4Address >', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::Invalidate(ns3::Time badLinkLifetime) [member function]
    cls.add_method('Invalidate', 
                   'void', 
                   [param('ns3::Time', 'badLinkLifetime')])
    ## dsr-rcache.h (module 'dsr'): bool ns3::dsr::DsrRouteCacheEntry::IsUnidirectional() const [member function]
    cls.add_method('IsUnidirectional', 
                   'bool', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::SetBlacklistTimeout(ns3::Time t) [member function]
    cls.add_method('SetBlacklistTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::SetDestination(ns3::Ipv4Address d) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'd')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::SetUnidirectional(bool u) [member function]
    cls.add_method('SetUnidirectional', 
                   'void', 
                   [param('bool', 'u')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::DsrRouteCacheEntry::SetVector(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > v) [member function]
    cls.add_method('SetVector', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'v')])
    return

def register_Ns3DsrDsrRouting_methods(root_module, cls):
    ## dsr-routing.h (module 'dsr'): ns3::dsr::DsrRouting::DsrRouting(ns3::dsr::DsrRouting const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrRouting const &', 'arg0')])
    ## dsr-routing.h (module 'dsr'): ns3::dsr::DsrRouting::DsrRouting() [constructor]
    cls.add_constructor([])
    ## dsr-routing.h (module 'dsr'): uint16_t ns3::dsr::DsrRouting::AddAckReqHeader(ns3::Ptr<ns3::Packet> & packet, ns3::Ipv4Address nextHop) [member function]
    cls.add_method('AddAckReqHeader', 
                   'uint16_t', 
                   [param('ns3::Ptr< ns3::Packet > &', 'packet'), param('ns3::Ipv4Address', 'nextHop')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::AddRoute(ns3::dsr::DsrRouteCacheEntry & rt) [member function]
    cls.add_method('AddRoute', 
                   'bool', 
                   [param('ns3::dsr::DsrRouteCacheEntry &', 'rt')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::AddRoute_Link(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > nodelist, ns3::Ipv4Address source) [member function]
    cls.add_method('AddRoute_Link', 
                   'bool', 
                   [param('std::vector< ns3::Ipv4Address >', 'nodelist'), param('ns3::Ipv4Address', 'source')])
    ## dsr-routing.h (module 'dsr'): int64_t ns3::dsr::DsrRouting::AssignStreams(int64_t stream) [member function]
    cls.add_method('AssignStreams', 
                   'int64_t', 
                   [param('int64_t', 'stream')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CallCancelPacketTimer(uint16_t ackId, ns3::Ipv4Header const & ipv4Header, ns3::Ipv4Address realSrc, ns3::Ipv4Address realDst) [member function]
    cls.add_method('CallCancelPacketTimer', 
                   'void', 
                   [param('uint16_t', 'ackId'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('ns3::Ipv4Address', 'realSrc'), param('ns3::Ipv4Address', 'realDst')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CancelLinkPacketTimer(ns3::dsr::DsrMaintainBuffEntry & mb) [member function]
    cls.add_method('CancelLinkPacketTimer', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CancelNetworkPacketTimer(ns3::dsr::DsrMaintainBuffEntry & mb) [member function]
    cls.add_method('CancelNetworkPacketTimer', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CancelPacketAllTimer(ns3::dsr::DsrMaintainBuffEntry & mb) [member function]
    cls.add_method('CancelPacketAllTimer', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CancelPacketTimerNextHop(ns3::Ipv4Address nextHop, uint8_t protocol) [member function]
    cls.add_method('CancelPacketTimerNextHop', 
                   'void', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CancelPassivePacketTimer(ns3::dsr::DsrMaintainBuffEntry & mb) [member function]
    cls.add_method('CancelPassivePacketTimer', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::CancelPassiveTimer(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t segsLeft) [member function]
    cls.add_method('CancelPassiveTimer', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'segsLeft')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CancelRreqTimer(ns3::Ipv4Address dst, bool isRemove) [member function]
    cls.add_method('CancelRreqTimer', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst'), param('bool', 'isRemove')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::CheckSendBuffer() [member function]
    cls.add_method('CheckSendBuffer', 
                   'void', 
                   [])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::DeleteAllRoutesIncludeLink(ns3::Ipv4Address errorSrc, ns3::Ipv4Address unreachNode, ns3::Ipv4Address node) [member function]
    cls.add_method('DeleteAllRoutesIncludeLink', 
                   'void', 
                   [param('ns3::Ipv4Address', 'errorSrc'), param('ns3::Ipv4Address', 'unreachNode'), param('ns3::Ipv4Address', 'node')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::FindSourceEntry(ns3::Ipv4Address src, ns3::Ipv4Address dst, uint16_t id) [member function]
    cls.add_method('FindSourceEntry', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'src'), param('ns3::Ipv4Address', 'dst'), param('uint16_t', 'id')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ForwardErrPacket(ns3::dsr::DsrOptionRerrUnreachHeader & rerr, ns3::dsr::DsrOptionSRHeader & sourceRoute, ns3::Ipv4Address nextHop, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('ForwardErrPacket', 
                   'void', 
                   [param('ns3::dsr::DsrOptionRerrUnreachHeader &', 'rerr'), param('ns3::dsr::DsrOptionSRHeader &', 'sourceRoute'), param('ns3::Ipv4Address', 'nextHop'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ForwardPacket(ns3::Ptr<ns3::Packet const> packet, ns3::dsr::DsrOptionSRHeader & sourceRoute, ns3::Ipv4Header const & ipv4Header, ns3::Ipv4Address source, ns3::Ipv4Address destination, ns3::Ipv4Address targetAddress, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('ForwardPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::dsr::DsrOptionSRHeader &', 'sourceRoute'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('ns3::Ipv4Address', 'targetAddress'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-routing.h (module 'dsr'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::dsr::DsrRouting::GetDownTarget() const [member function]
    cls.add_method('GetDownTarget', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-routing.h (module 'dsr'): ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ns3::dsr::DsrRouting::GetDownTarget6() const [member function]
    cls.add_method('GetDownTarget6', 
                   'ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-routing.h (module 'dsr'): std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >,std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > ns3::dsr::DsrRouting::GetElementsFromContext(std::string context) [member function]
    cls.add_method('GetElementsFromContext', 
                   'std::vector< std::string >', 
                   [param('std::string', 'context')])
    ## dsr-routing.h (module 'dsr'): uint16_t ns3::dsr::DsrRouting::GetIDfromIP(ns3::Ipv4Address address) [member function]
    cls.add_method('GetIDfromIP', 
                   'uint16_t', 
                   [param('ns3::Ipv4Address', 'address')])
    ## dsr-routing.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrRouting::GetIPfromID(uint16_t id) [member function]
    cls.add_method('GetIPfromID', 
                   'ns3::Ipv4Address', 
                   [param('uint16_t', 'id')])
    ## dsr-routing.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrRouting::GetIPfromMAC(ns3::Mac48Address address) [member function]
    cls.add_method('GetIPfromMAC', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Mac48Address', 'address')])
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::NetDevice> ns3::dsr::DsrRouting::GetNetDeviceFromContext(std::string context) [member function]
    cls.add_method('GetNetDeviceFromContext', 
                   'ns3::Ptr< ns3::NetDevice >', 
                   [param('std::string', 'context')])
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::Node> ns3::dsr::DsrRouting::GetNode() const [member function]
    cls.add_method('GetNode', 
                   'ns3::Ptr< ns3::Node >', 
                   [], 
                   is_const=True)
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::Node> ns3::dsr::DsrRouting::GetNodeWithAddress(ns3::Ipv4Address ipv4Address) [member function]
    cls.add_method('GetNodeWithAddress', 
                   'ns3::Ptr< ns3::Node >', 
                   [param('ns3::Ipv4Address', 'ipv4Address')])
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::dsr::DsrOptions> ns3::dsr::DsrRouting::GetOption(int optionNumber) [member function]
    cls.add_method('GetOption', 
                   'ns3::Ptr< ns3::dsr::DsrOptions >', 
                   [param('int', 'optionNumber')])
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::dsr::DsrPassiveBuffer> ns3::dsr::DsrRouting::GetPassiveBuffer() const [member function]
    cls.add_method('GetPassiveBuffer', 
                   'ns3::Ptr< ns3::dsr::DsrPassiveBuffer >', 
                   [], 
                   is_const=True)
    ## dsr-routing.h (module 'dsr'): uint32_t ns3::dsr::DsrRouting::GetPriority(ns3::dsr::DsrMessageType messageType) [member function]
    cls.add_method('GetPriority', 
                   'uint32_t', 
                   [param('ns3::dsr::DsrMessageType', 'messageType')])
    ## dsr-routing.h (module 'dsr'): int ns3::dsr::DsrRouting::GetProtocolNumber() const [member function]
    cls.add_method('GetProtocolNumber', 
                   'int', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::dsr::DsrRreqTable> ns3::dsr::DsrRouting::GetRequestTable() const [member function]
    cls.add_method('GetRequestTable', 
                   'ns3::Ptr< ns3::dsr::DsrRreqTable >', 
                   [], 
                   is_const=True)
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::dsr::DsrRouteCache> ns3::dsr::DsrRouting::GetRouteCache() const [member function]
    cls.add_method('GetRouteCache', 
                   'ns3::Ptr< ns3::dsr::DsrRouteCache >', 
                   [], 
                   is_const=True)
    ## dsr-routing.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrRouting::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::IncreaseRetransTimer() [member function]
    cls.add_method('IncreaseRetransTimer', 
                   'void', 
                   [])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::Insert(ns3::Ptr<ns3::dsr::DsrOptions> option) [member function]
    cls.add_method('Insert', 
                   'void', 
                   [param('ns3::Ptr< ns3::dsr::DsrOptions >', 'option')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::IsLinkCache() [member function]
    cls.add_method('IsLinkCache', 
                   'bool', 
                   [])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::LinkScheduleTimerExpire(ns3::dsr::DsrMaintainBuffEntry & mb, uint8_t protocol) [member function]
    cls.add_method('LinkScheduleTimerExpire', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::LookupRoute(ns3::Ipv4Address id, ns3::dsr::DsrRouteCacheEntry & rt) [member function]
    cls.add_method('LookupRoute', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'id'), param('ns3::dsr::DsrRouteCacheEntry &', 'rt')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::NetworkScheduleTimerExpire(ns3::dsr::DsrMaintainBuffEntry & mb, uint8_t protocol) [member function]
    cls.add_method('NetworkScheduleTimerExpire', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::PacketNewRoute(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol) [member function]
    cls.add_method('PacketNewRoute', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::PassiveEntryCheck(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t segsLeft, uint16_t fragmentOffset, uint16_t identification, bool saveEntry) [member function]
    cls.add_method('PassiveEntryCheck', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'segsLeft'), param('uint16_t', 'fragmentOffset'), param('uint16_t', 'identification'), param('bool', 'saveEntry')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::PassiveScheduleTimerExpire(ns3::dsr::DsrMaintainBuffEntry & mb, uint8_t protocol) [member function]
    cls.add_method('PassiveScheduleTimerExpire', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::PrintVector(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('PrintVector', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::PriorityScheduler(uint32_t priority, bool continueWithFirst) [member function]
    cls.add_method('PriorityScheduler', 
                   'void', 
                   [param('uint32_t', 'priority'), param('bool', 'continueWithFirst')])
    ## dsr-routing.h (module 'dsr'): uint8_t ns3::dsr::DsrRouting::Process(ns3::Ptr<ns3::Packet> & packet, ns3::Ipv4Header const & ipv4Header, ns3::Ipv4Address dst, uint8_t * nextHeader, uint8_t protocol, bool & isDropped) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet > &', 'packet'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('ns3::Ipv4Address', 'dst'), param('uint8_t *', 'nextHeader'), param('uint8_t', 'protocol'), param('bool &', 'isDropped')])
    ## dsr-routing.h (module 'dsr'): ns3::IpL4Protocol::RxStatus ns3::dsr::DsrRouting::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::Ipv4Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::Ipv4Interface >', 'incomingInterface')], 
                   is_virtual=True)
    ## dsr-routing.h (module 'dsr'): ns3::IpL4Protocol::RxStatus ns3::dsr::DsrRouting::Receive(ns3::Ptr<ns3::Packet> p, ns3::Ipv6Header const & header, ns3::Ptr<ns3::Ipv6Interface> incomingInterface) [member function]
    cls.add_method('Receive', 
                   'ns3::IpL4Protocol::RxStatus', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv6Header const &', 'header'), param('ns3::Ptr< ns3::Ipv6Interface >', 'incomingInterface')], 
                   is_virtual=True)
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::RouteRequestTimerExpire(ns3::Ptr<ns3::Packet> packet, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > address, uint32_t requestId, uint8_t protocol) [member function]
    cls.add_method('RouteRequestTimerExpire', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('std::vector< ns3::Ipv4Address >', 'address'), param('uint32_t', 'requestId'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SalvagePacket(ns3::Ptr<ns3::Packet const> packet, ns3::Ipv4Address source, ns3::Ipv4Address dst, uint8_t protocol) [member function]
    cls.add_method('SalvagePacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'dst'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ScheduleCachedReply(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, ns3::Ptr<ns3::Ipv4Route> route, double hops) [member function]
    cls.add_method('ScheduleCachedReply', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('ns3::Ptr< ns3::Ipv4Route >', 'route'), param('double', 'hops')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ScheduleInitialReply(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address nextHop, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('ScheduleInitialReply', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'nextHop'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ScheduleInterRequest(ns3::Ptr<ns3::Packet> packet) [member function]
    cls.add_method('ScheduleInterRequest', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ScheduleLinkPacketRetry(ns3::dsr::DsrMaintainBuffEntry & mb, uint8_t protocol) [member function]
    cls.add_method('ScheduleLinkPacketRetry', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ScheduleNetworkPacketRetry(ns3::dsr::DsrMaintainBuffEntry & mb, bool isFirst, uint8_t protocol) [member function]
    cls.add_method('ScheduleNetworkPacketRetry', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb'), param('bool', 'isFirst'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SchedulePassivePacketRetry(ns3::dsr::DsrMaintainBuffEntry & mb, uint8_t protocol) [member function]
    cls.add_method('SchedulePassivePacketRetry', 
                   'void', 
                   [param('ns3::dsr::DsrMaintainBuffEntry &', 'mb'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::ScheduleRreqRetry(ns3::Ptr<ns3::Packet> packet, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > address, bool nonProp, uint32_t requestId, uint8_t protocol) [member function]
    cls.add_method('ScheduleRreqRetry', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('std::vector< ns3::Ipv4Address >', 'address'), param('bool', 'nonProp'), param('uint32_t', 'requestId'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::Scheduler(uint32_t priority) [member function]
    cls.add_method('Scheduler', 
                   'void', 
                   [param('uint32_t', 'priority')])
    ## dsr-routing.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrRouting::SearchNextHop(ns3::Ipv4Address ipv4Address, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & vec) [member function]
    cls.add_method('SearchNextHop', 
                   'ns3::Ipv4Address', 
                   [param('ns3::Ipv4Address', 'ipv4Address'), param('std::vector< ns3::Ipv4Address > &', 'vec')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::Send(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('Send', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendAck(uint16_t ackId, ns3::Ipv4Address destination, ns3::Ipv4Address realSrc, ns3::Ipv4Address realDst, uint8_t protocol, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SendAck', 
                   'void', 
                   [param('uint16_t', 'ackId'), param('ns3::Ipv4Address', 'destination'), param('ns3::Ipv4Address', 'realSrc'), param('ns3::Ipv4Address', 'realDst'), param('uint8_t', 'protocol'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendBuffTimerExpire() [member function]
    cls.add_method('SendBuffTimerExpire', 
                   'void', 
                   [])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendErrorRequest(ns3::dsr::DsrOptionRerrUnreachHeader & rerr, uint8_t protocol) [member function]
    cls.add_method('SendErrorRequest', 
                   'void', 
                   [param('ns3::dsr::DsrOptionRerrUnreachHeader &', 'rerr'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendGratuitousReply(ns3::Ipv4Address replyTo, ns3::Ipv4Address replyFrom, std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > & nodeList, uint8_t protocol) [member function]
    cls.add_method('SendGratuitousReply', 
                   'void', 
                   [param('ns3::Ipv4Address', 'replyTo'), param('ns3::Ipv4Address', 'replyFrom'), param('std::vector< ns3::Ipv4Address > &', 'nodeList'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendInitialRequest(ns3::Ipv4Address source, ns3::Ipv4Address destination, uint8_t protocol) [member function]
    cls.add_method('SendInitialRequest', 
                   'void', 
                   [param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'destination'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendPacket(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address nextHop, uint8_t protocol) [member function]
    cls.add_method('SendPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'nextHop'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendPacketFromBuffer(ns3::dsr::DsrOptionSRHeader const & sourceRoute, ns3::Ipv4Address nextHop, uint8_t protocol) [member function]
    cls.add_method('SendPacketFromBuffer', 
                   'void', 
                   [param('ns3::dsr::DsrOptionSRHeader const &', 'sourceRoute'), param('ns3::Ipv4Address', 'nextHop'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::SendRealDown(ns3::dsr::DsrNetworkQueueEntry & newEntry) [member function]
    cls.add_method('SendRealDown', 
                   'bool', 
                   [param('ns3::dsr::DsrNetworkQueueEntry &', 'newEntry')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendReply(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source, ns3::Ipv4Address nextHop, ns3::Ptr<ns3::Ipv4Route> route) [member function]
    cls.add_method('SendReply', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Address', 'nextHop'), param('ns3::Ptr< ns3::Ipv4Route >', 'route')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendRequest(ns3::Ptr<ns3::Packet> packet, ns3::Ipv4Address source) [member function]
    cls.add_method('SendRequest', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ipv4Address', 'source')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SendUnreachError(ns3::Ipv4Address unreachNode, ns3::Ipv4Address destination, ns3::Ipv4Address originalDst, uint8_t salvage, uint8_t protocol) [member function]
    cls.add_method('SendUnreachError', 
                   'void', 
                   [param('ns3::Ipv4Address', 'unreachNode'), param('ns3::Ipv4Address', 'destination'), param('ns3::Ipv4Address', 'originalDst'), param('uint8_t', 'salvage'), param('uint8_t', 'protocol')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SetDownTarget(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr<ns3::Ipv4Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [member function]
    cls.add_method('SetDownTarget', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv4Address, ns3::Ipv4Address, unsigned char, ns3::Ptr< ns3::Ipv4Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_virtual=True)
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SetDownTarget6(ns3::Callback<void, ns3::Ptr<ns3::Packet>, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr<ns3::Ipv6Route>, ns3::empty, ns3::empty, ns3::empty, ns3::empty> callback) [member function]
    cls.add_method('SetDownTarget6', 
                   'void', 
                   [param('ns3::Callback< void, ns3::Ptr< ns3::Packet >, ns3::Ipv6Address, ns3::Ipv6Address, unsigned char, ns3::Ptr< ns3::Ipv6Route >, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'callback')], 
                   is_virtual=True)
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SetNode(ns3::Ptr<ns3::Node> node) [member function]
    cls.add_method('SetNode', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SetPassiveBuffer(ns3::Ptr<ns3::dsr::DsrPassiveBuffer> r) [member function]
    cls.add_method('SetPassiveBuffer', 
                   'void', 
                   [param('ns3::Ptr< ns3::dsr::DsrPassiveBuffer >', 'r')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SetRequestTable(ns3::Ptr<ns3::dsr::DsrRreqTable> r) [member function]
    cls.add_method('SetRequestTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::dsr::DsrRreqTable >', 'r')])
    ## dsr-routing.h (module 'dsr'): ns3::Ptr<ns3::Ipv4Route> ns3::dsr::DsrRouting::SetRoute(ns3::Ipv4Address nextHop, ns3::Ipv4Address srcAddress) [member function]
    cls.add_method('SetRoute', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ipv4Address', 'nextHop'), param('ns3::Ipv4Address', 'srcAddress')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::SetRouteCache(ns3::Ptr<ns3::dsr::DsrRouteCache> r) [member function]
    cls.add_method('SetRouteCache', 
                   'void', 
                   [param('ns3::Ptr< ns3::dsr::DsrRouteCache >', 'r')])
    ## dsr-routing.h (module 'dsr'): bool ns3::dsr::DsrRouting::UpdateRouteEntry(ns3::Ipv4Address dst) [member function]
    cls.add_method('UpdateRouteEntry', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::UseExtends(std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > rt) [member function]
    cls.add_method('UseExtends', 
                   'void', 
                   [param('std::vector< ns3::Ipv4Address >', 'rt')])
    ## dsr-routing.h (module 'dsr'): ns3::dsr::DsrRouting::PROT_NUMBER [variable]
    cls.add_static_attribute('PROT_NUMBER', 'uint8_t const', is_const=True)
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## dsr-routing.h (module 'dsr'): void ns3::dsr::DsrRouting::NotifyNewAggregate() [member function]
    cls.add_method('NotifyNewAggregate', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    return

def register_Ns3DsrDsrRoutingHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrRoutingHeader::DsrRoutingHeader(ns3::dsr::DsrRoutingHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrRoutingHeader const &', 'arg0')])
    ## dsr-fs-header.h (module 'dsr'): ns3::dsr::DsrRoutingHeader::DsrRoutingHeader() [constructor]
    cls.add_constructor([])
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrRoutingHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrRoutingHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): uint32_t ns3::dsr::DsrRoutingHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrRoutingHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrRoutingHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-fs-header.h (module 'dsr'): void ns3::dsr::DsrRoutingHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    return

def register_Ns3DsrDsrRreqTable_methods(root_module, cls):
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::DsrRreqTable::DsrRreqTable(ns3::dsr::DsrRreqTable const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrRreqTable const &', 'arg0')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::DsrRreqTable::DsrRreqTable() [constructor]
    cls.add_constructor([])
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::CheckUniqueRreqId(ns3::Ipv4Address dst) [member function]
    cls.add_method('CheckUniqueRreqId', 
                   'uint32_t', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::FindAndUpdate(ns3::Ipv4Address dst) [member function]
    cls.add_method('FindAndUpdate', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rreq-table.h (module 'dsr'): bool ns3::dsr::DsrRreqTable::FindSourceEntry(ns3::Ipv4Address src, ns3::Ipv4Address dst, uint16_t id) [member function]
    cls.add_method('FindSourceEntry', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'src'), param('ns3::Ipv4Address', 'dst'), param('uint16_t', 'id')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::BlackList * ns3::dsr::DsrRreqTable::FindUnidirectional(ns3::Ipv4Address neighbor) [member function]
    cls.add_method('FindUnidirectional', 
                   'ns3::dsr::BlackList *', 
                   [param('ns3::Ipv4Address', 'neighbor')])
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::GetInitHopLimit() const [member function]
    cls.add_method('GetInitHopLimit', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::GetRreqCnt(ns3::Ipv4Address dst) [member function]
    cls.add_method('GetRreqCnt', 
                   'uint32_t', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::GetRreqIdSize() const [member function]
    cls.add_method('GetRreqIdSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::GetRreqSize() [member function]
    cls.add_method('GetRreqSize', 
                   'uint32_t', 
                   [])
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::GetRreqTableSize() const [member function]
    cls.add_method('GetRreqTableSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrRreqTable::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-rreq-table.h (module 'dsr'): uint32_t ns3::dsr::DsrRreqTable::GetUniqueRreqIdSize() const [member function]
    cls.add_method('GetUniqueRreqIdSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::Invalidate() [member function]
    cls.add_method('Invalidate', 
                   'void', 
                   [])
    ## dsr-rreq-table.h (module 'dsr'): bool ns3::dsr::DsrRreqTable::MarkLinkAsUnidirectional(ns3::Ipv4Address neighbor, ns3::Time blacklistTimeout) [member function]
    cls.add_method('MarkLinkAsUnidirectional', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'neighbor'), param('ns3::Time', 'blacklistTimeout')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::PurgeNeighbor() [member function]
    cls.add_method('PurgeNeighbor', 
                   'void', 
                   [])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::RemoveLeastExpire(std::map<ns3::Ipv4Address, ns3::dsr::RreqTableEntry, std::less<ns3::Ipv4Address>, std::allocator<std::pair<ns3::Ipv4Address const, ns3::dsr::RreqTableEntry> > > & rreqDstMap) [member function]
    cls.add_method('RemoveLeastExpire', 
                   'void', 
                   [param('std::map< ns3::Ipv4Address, ns3::dsr::RreqTableEntry > &', 'rreqDstMap')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::RemoveRreqEntry(ns3::Ipv4Address dst) [member function]
    cls.add_method('RemoveRreqEntry', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::SetInitHopLimit(uint32_t hl) [member function]
    cls.add_method('SetInitHopLimit', 
                   'void', 
                   [param('uint32_t', 'hl')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::SetRreqIdSize(uint32_t id) [member function]
    cls.add_method('SetRreqIdSize', 
                   'void', 
                   [param('uint32_t', 'id')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::SetRreqTableSize(uint32_t rt) [member function]
    cls.add_method('SetRreqTableSize', 
                   'void', 
                   [param('uint32_t', 'rt')])
    ## dsr-rreq-table.h (module 'dsr'): void ns3::dsr::DsrRreqTable::SetUniqueRreqIdSize(uint32_t uid) [member function]
    cls.add_method('SetUniqueRreqIdSize', 
                   'void', 
                   [param('uint32_t', 'uid')])
    return

def register_Ns3DsrDsrSendBuffEntry_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## dsr-rsendbuff.h (module 'dsr'): ns3::dsr::DsrSendBuffEntry::DsrSendBuffEntry(ns3::dsr::DsrSendBuffEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrSendBuffEntry const &', 'arg0')])
    ## dsr-rsendbuff.h (module 'dsr'): ns3::dsr::DsrSendBuffEntry::DsrSendBuffEntry(ns3::Ptr<ns3::Packet const> pa=0, ns3::Ipv4Address d=ns3::Ipv4Address(), ns3::Time exp=ns3::Simulator::Now( ), uint8_t p=0) [constructor]
    cls.add_constructor([param('ns3::Ptr< ns3::Packet const >', 'pa', default_value='0'), param('ns3::Ipv4Address', 'd', default_value='ns3::Ipv4Address()'), param('ns3::Time', 'exp', default_value='ns3::Simulator::Now( )'), param('uint8_t', 'p', default_value='0')])
    ## dsr-rsendbuff.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrSendBuffEntry::GetDestination() const [member function]
    cls.add_method('GetDestination', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-rsendbuff.h (module 'dsr'): ns3::Time ns3::dsr::DsrSendBuffEntry::GetExpireTime() const [member function]
    cls.add_method('GetExpireTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rsendbuff.h (module 'dsr'): ns3::Ptr<ns3::Packet const> ns3::dsr::DsrSendBuffEntry::GetPacket() const [member function]
    cls.add_method('GetPacket', 
                   'ns3::Ptr< ns3::Packet const >', 
                   [], 
                   is_const=True)
    ## dsr-rsendbuff.h (module 'dsr'): uint8_t ns3::dsr::DsrSendBuffEntry::GetProtocol() const [member function]
    cls.add_method('GetProtocol', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffEntry::SetDestination(ns3::Ipv4Address d) [member function]
    cls.add_method('SetDestination', 
                   'void', 
                   [param('ns3::Ipv4Address', 'd')])
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffEntry::SetExpireTime(ns3::Time exp) [member function]
    cls.add_method('SetExpireTime', 
                   'void', 
                   [param('ns3::Time', 'exp')])
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffEntry::SetPacket(ns3::Ptr<ns3::Packet const> p) [member function]
    cls.add_method('SetPacket', 
                   'void', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p')])
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffEntry::SetProtocol(uint8_t p) [member function]
    cls.add_method('SetProtocol', 
                   'void', 
                   [param('uint8_t', 'p')])
    return

def register_Ns3DsrDsrSendBuffer_methods(root_module, cls):
    ## dsr-rsendbuff.h (module 'dsr'): ns3::dsr::DsrSendBuffer::DsrSendBuffer(ns3::dsr::DsrSendBuffer const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrSendBuffer const &', 'arg0')])
    ## dsr-rsendbuff.h (module 'dsr'): ns3::dsr::DsrSendBuffer::DsrSendBuffer() [constructor]
    cls.add_constructor([])
    ## dsr-rsendbuff.h (module 'dsr'): bool ns3::dsr::DsrSendBuffer::Dequeue(ns3::Ipv4Address dst, ns3::dsr::DsrSendBuffEntry & entry) [member function]
    cls.add_method('Dequeue', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst'), param('ns3::dsr::DsrSendBuffEntry &', 'entry')])
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffer::DropPacketWithDst(ns3::Ipv4Address dst) [member function]
    cls.add_method('DropPacketWithDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rsendbuff.h (module 'dsr'): bool ns3::dsr::DsrSendBuffer::Enqueue(ns3::dsr::DsrSendBuffEntry & entry) [member function]
    cls.add_method('Enqueue', 
                   'bool', 
                   [param('ns3::dsr::DsrSendBuffEntry &', 'entry')])
    ## dsr-rsendbuff.h (module 'dsr'): bool ns3::dsr::DsrSendBuffer::Find(ns3::Ipv4Address dst) [member function]
    cls.add_method('Find', 
                   'bool', 
                   [param('ns3::Ipv4Address', 'dst')])
    ## dsr-rsendbuff.h (module 'dsr'): std::vector<ns3::dsr::DsrSendBuffEntry, std::allocator<ns3::dsr::DsrSendBuffEntry> > & ns3::dsr::DsrSendBuffer::GetBuffer() [member function]
    cls.add_method('GetBuffer', 
                   'std::vector< ns3::dsr::DsrSendBuffEntry > &', 
                   [])
    ## dsr-rsendbuff.h (module 'dsr'): uint32_t ns3::dsr::DsrSendBuffer::GetMaxQueueLen() const [member function]
    cls.add_method('GetMaxQueueLen', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## dsr-rsendbuff.h (module 'dsr'): ns3::Time ns3::dsr::DsrSendBuffer::GetSendBufferTimeout() const [member function]
    cls.add_method('GetSendBufferTimeout', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## dsr-rsendbuff.h (module 'dsr'): uint32_t ns3::dsr::DsrSendBuffer::GetSize() [member function]
    cls.add_method('GetSize', 
                   'uint32_t', 
                   [])
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffer::SetMaxQueueLen(uint32_t len) [member function]
    cls.add_method('SetMaxQueueLen', 
                   'void', 
                   [param('uint32_t', 'len')])
    ## dsr-rsendbuff.h (module 'dsr'): void ns3::dsr::DsrSendBuffer::SetSendBufferTimeout(ns3::Time t) [member function]
    cls.add_method('SetSendBufferTimeout', 
                   'void', 
                   [param('ns3::Time', 't')])
    return

def register_Ns3DsrGraReplyEntry_methods(root_module, cls):
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::GraReplyEntry::GraReplyEntry(ns3::dsr::GraReplyEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::GraReplyEntry const &', 'arg0')])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::GraReplyEntry::GraReplyEntry(ns3::Ipv4Address t, ns3::Ipv4Address f, ns3::Time h) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 't'), param('ns3::Ipv4Address', 'f'), param('ns3::Time', 'h')])
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::GraReplyEntry::m_gratReplyHoldoff [variable]
    cls.add_instance_attribute('m_gratReplyHoldoff', 'ns3::Time', is_const=False)
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::GraReplyEntry::m_hearFrom [variable]
    cls.add_instance_attribute('m_hearFrom', 'ns3::Ipv4Address', is_const=False)
    ## dsr-gratuitous-reply-table.h (module 'dsr'): ns3::dsr::GraReplyEntry::m_replyTo [variable]
    cls.add_instance_attribute('m_replyTo', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrLink_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::Link::Link(ns3::dsr::Link const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::Link const &', 'arg0')])
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::Link::Link(ns3::Ipv4Address ip1, ns3::Ipv4Address ip2) [constructor]
    cls.add_constructor([param('ns3::Ipv4Address', 'ip1'), param('ns3::Ipv4Address', 'ip2')])
    ## dsr-rcache.h (module 'dsr'): void ns3::dsr::Link::Print() const [member function]
    cls.add_method('Print', 
                   'void', 
                   [], 
                   is_const=True)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::Link::m_high [variable]
    cls.add_instance_attribute('m_high', 'ns3::Ipv4Address', is_const=False)
    ## dsr-rcache.h (module 'dsr'): ns3::dsr::Link::m_low [variable]
    cls.add_instance_attribute('m_low', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrLinkKey_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey::LinkKey() [constructor]
    cls.add_constructor([])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey::LinkKey(ns3::dsr::LinkKey const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::LinkKey const &', 'arg0')])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey::m_destination [variable]
    cls.add_instance_attribute('m_destination', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey::m_nextHop [variable]
    cls.add_instance_attribute('m_nextHop', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey::m_ourAdd [variable]
    cls.add_instance_attribute('m_ourAdd', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::LinkKey::m_source [variable]
    cls.add_instance_attribute('m_source', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrNetworkKey_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::NetworkKey() [constructor]
    cls.add_constructor([])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::NetworkKey(ns3::dsr::NetworkKey const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::NetworkKey const &', 'arg0')])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::m_ackId [variable]
    cls.add_instance_attribute('m_ackId', 'uint16_t', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::m_destination [variable]
    cls.add_instance_attribute('m_destination', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::m_nextHop [variable]
    cls.add_instance_attribute('m_nextHop', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::m_ourAdd [variable]
    cls.add_instance_attribute('m_ourAdd', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::NetworkKey::m_source [variable]
    cls.add_instance_attribute('m_source', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrPassiveKey_methods(root_module, cls):
    cls.add_binary_comparison_operator('<')
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey::PassiveKey() [constructor]
    cls.add_constructor([])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey::PassiveKey(ns3::dsr::PassiveKey const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::PassiveKey const &', 'arg0')])
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey::m_ackId [variable]
    cls.add_instance_attribute('m_ackId', 'uint16_t', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey::m_destination [variable]
    cls.add_instance_attribute('m_destination', 'ns3::Ipv4Address', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey::m_segsLeft [variable]
    cls.add_instance_attribute('m_segsLeft', 'uint8_t', is_const=False)
    ## dsr-maintain-buff.h (module 'dsr'): ns3::dsr::PassiveKey::m_source [variable]
    cls.add_instance_attribute('m_source', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3DsrRreqTableEntry_methods(root_module, cls):
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::RreqTableEntry::RreqTableEntry() [constructor]
    cls.add_constructor([])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::RreqTableEntry::RreqTableEntry(ns3::dsr::RreqTableEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::RreqTableEntry const &', 'arg0')])
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::RreqTableEntry::m_expire [variable]
    cls.add_instance_attribute('m_expire', 'ns3::Time', is_const=False)
    ## dsr-rreq-table.h (module 'dsr'): ns3::dsr::RreqTableEntry::m_reqNo [variable]
    cls.add_instance_attribute('m_reqNo', 'uint32_t', is_const=False)
    return

def register_Ns3DsrDsrOptionAck_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAck::DsrOptionAck(ns3::dsr::DsrOptionAck const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionAck const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAck::DsrOptionAck() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionAck::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionAck::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionAck::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionAck::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAck::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionAckHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionAckHeader::DsrOptionAckHeader(ns3::dsr::DsrOptionAckHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionAckHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionAckHeader::DsrOptionAckHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionAckHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint16_t ns3::dsr::DsrOptionAckHeader::GetAckId() const [member function]
    cls.add_method('GetAckId', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionAckHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionAckHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionAckHeader::GetRealDst() const [member function]
    cls.add_method('GetRealDst', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): ns3::Ipv4Address ns3::dsr::DsrOptionAckHeader::GetRealSrc() const [member function]
    cls.add_method('GetRealSrc', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionAckHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionAckHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckHeader::SetAckId(uint16_t identification) [member function]
    cls.add_method('SetAckId', 
                   'void', 
                   [param('uint16_t', 'identification')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckHeader::SetRealDst(ns3::Ipv4Address realDstAddress) [member function]
    cls.add_method('SetRealDst', 
                   'void', 
                   [param('ns3::Ipv4Address', 'realDstAddress')])
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckHeader::SetRealSrc(ns3::Ipv4Address realSrcAddress) [member function]
    cls.add_method('SetRealSrc', 
                   'void', 
                   [param('ns3::Ipv4Address', 'realSrcAddress')])
    return

def register_Ns3DsrDsrOptionAckReq_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAckReq::DsrOptionAckReq(ns3::dsr::DsrOptionAckReq const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionAckReq const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAckReq::DsrOptionAckReq() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionAckReq::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionAckReq::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionAckReq::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionAckReq::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionAckReq::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionAckReqHeader_methods(root_module, cls):
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionAckReqHeader::DsrOptionAckReqHeader(ns3::dsr::DsrOptionAckReqHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionAckReqHeader const &', 'arg0')])
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionAckReqHeader::DsrOptionAckReqHeader() [constructor]
    cls.add_constructor([])
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionAckReqHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint16_t ns3::dsr::DsrOptionAckReqHeader::GetAckId() const [member function]
    cls.add_method('GetAckId', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## dsr-option-header.h (module 'dsr'): ns3::dsr::DsrOptionHeader::Alignment ns3::dsr::DsrOptionAckReqHeader::GetAlignment() const [member function]
    cls.add_method('GetAlignment', 
                   'ns3::dsr::DsrOptionHeader::Alignment', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionAckReqHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): uint32_t ns3::dsr::DsrOptionAckReqHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionAckReqHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckReqHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckReqHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## dsr-option-header.h (module 'dsr'): void ns3::dsr::DsrOptionAckReqHeader::SetAckId(uint16_t identification) [member function]
    cls.add_method('SetAckId', 
                   'void', 
                   [param('uint16_t', 'identification')])
    return

def register_Ns3DsrDsrOptionPad1_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPad1::DsrOptionPad1(ns3::dsr::DsrOptionPad1 const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionPad1 const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPad1::DsrOptionPad1() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionPad1::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionPad1::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionPad1::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPad1::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionPadn_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPadn::DsrOptionPadn(ns3::dsr::DsrOptionPadn const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionPadn const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPadn::DsrOptionPadn() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionPadn::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionPadn::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionPadn::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionPadn::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionRerr_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRerr::DsrOptionRerr(ns3::dsr::DsrOptionRerr const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRerr const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRerr::DsrOptionRerr() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerr::DoSendError(ns3::Ptr<ns3::Packet> p, ns3::dsr::DsrOptionRerrUnreachHeader & rerr, uint32_t rerrSize, ns3::Ipv4Address ipv4Address, uint8_t protocol) [member function]
    cls.add_method('DoSendError', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::dsr::DsrOptionRerrUnreachHeader &', 'rerr'), param('uint32_t', 'rerrSize'), param('ns3::Ipv4Address', 'ipv4Address'), param('uint8_t', 'protocol')])
    ## dsr-options.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRerr::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerr::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRerr::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRerr::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRerr::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionRrep_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRrep::DsrOptionRrep(ns3::dsr::DsrOptionRrep const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRrep const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRrep::DsrOptionRrep() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRrep::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRrep::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRrep::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRrep::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRrep::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionRreq_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRreq::DsrOptionRreq(ns3::dsr::DsrOptionRreq const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionRreq const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRreq::DsrOptionRreq() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionRreq::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRreq::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionRreq::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionRreq::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionRreq::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_Ns3DsrDsrOptionSR_methods(root_module, cls):
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionSR::DsrOptionSR(ns3::dsr::DsrOptionSR const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::dsr::DsrOptionSR const &', 'arg0')])
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionSR::DsrOptionSR() [constructor]
    cls.add_constructor([])
    ## dsr-options.h (module 'dsr'): ns3::TypeId ns3::dsr::DsrOptionSR::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionSR::GetOptionNumber() const [member function]
    cls.add_method('GetOptionNumber', 
                   'uint8_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## dsr-options.h (module 'dsr'): static ns3::TypeId ns3::dsr::DsrOptionSR::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## dsr-options.h (module 'dsr'): uint8_t ns3::dsr::DsrOptionSR::Process(ns3::Ptr<ns3::Packet> packet, ns3::Ptr<ns3::Packet> dsrP, ns3::Ipv4Address ipv4Address, ns3::Ipv4Address source, ns3::Ipv4Header const & ipv4Header, uint8_t protocol, bool & isPromisc, ns3::Ipv4Address promiscSource) [member function]
    cls.add_method('Process', 
                   'uint8_t', 
                   [param('ns3::Ptr< ns3::Packet >', 'packet'), param('ns3::Ptr< ns3::Packet >', 'dsrP'), param('ns3::Ipv4Address', 'ipv4Address'), param('ns3::Ipv4Address', 'source'), param('ns3::Ipv4Header const &', 'ipv4Header'), param('uint8_t', 'protocol'), param('bool &', 'isPromisc'), param('ns3::Ipv4Address', 'promiscSource')], 
                   is_virtual=True)
    ## dsr-options.h (module 'dsr'): ns3::dsr::DsrOptionSR::OPT_NUMBER [variable]
    cls.add_static_attribute('OPT_NUMBER', 'uint8_t const', is_const=True)
    return

def register_functions(root_module):
    module = root_module
    register_functions_ns3_FatalImpl(module.get_submodule('FatalImpl'), root_module)
    register_functions_ns3_Hash(module.get_submodule('Hash'), root_module)
    register_functions_ns3_TracedValueCallback(module.get_submodule('TracedValueCallback'), root_module)
    register_functions_ns3_dsr(module.get_submodule('dsr'), root_module)
    register_functions_ns3_internal(module.get_submodule('internal'), root_module)
    return

def register_functions_ns3_FatalImpl(module, root_module):
    return

def register_functions_ns3_Hash(module, root_module):
    register_functions_ns3_Hash_Function(module.get_submodule('Function'), root_module)
    return

def register_functions_ns3_Hash_Function(module, root_module):
    return

def register_functions_ns3_TracedValueCallback(module, root_module):
    return

def register_functions_ns3_dsr(module, root_module):
    return

def register_functions_ns3_internal(module, root_module):
    return

def main():
    out = FileCodeSink(sys.stdout)
    root_module = module_init()
    register_types(root_module)
    register_methods(root_module)
    register_functions(root_module)
    root_module.generate(out)

if __name__ == '__main__':
    main()

