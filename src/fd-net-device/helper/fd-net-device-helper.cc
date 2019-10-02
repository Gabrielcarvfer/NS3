/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alina Quereilhac <alina.quereilhac@inria.fr>
 *
 */

#include "fd-net-device-helper.h"

#include "../../core/model/abort.h"
#include "../../core/model/config.h"
#include "../model/fd-net-device.h"
#include "../../core/model/log.h"
#include "../../core/model/names.h"
#include "../../core/model/object-factory.h"
#include "../../network/model/packet.h"
#include "../../core/model/simulator.h"
#include "../../network/helper/trace-helper.h"

#include "../../../3rd-party/cpp-std-fwd/stdfwd.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("FdNetDeviceHelper");

FdNetDeviceHelper::FdNetDeviceHelper ()
{
  m_deviceFactory.SetTypeId ("ns3::FdNetDevice");
}

void
FdNetDeviceHelper::SetAttribute (stdfwd::string n1, const AttributeValue &v1)
{
  NS_LOG_FUNCTION (this);
  m_deviceFactory.Set (n1, v1);
}

void
FdNetDeviceHelper::EnablePcapInternal (stdfwd::string prefix, Ptr<NetDevice> nd, bool promiscuous, bool explicitFilename)
{
  //
  // All of the Pcap enable functions vector through here including the ones
  // that are wandering through all of devices on perhaps all of the nodes in
  // the system.  We can only deal with devices of type FdNetDevice.
  //
  Ptr<FdNetDevice> device = nd->GetObject<FdNetDevice> ();
  if (device == 0)
    {
      NS_LOG_INFO ("FdNetDeviceHelper::EnablePcapInternal(): Device " << device << " not of type ns3::FdNetDevice");
      return;
    }

  PcapHelper pcapHelper;

  stdfwd::string filename;
  if (explicitFilename)
    {
      filename = prefix;
    }
  else
    {
      filename = pcapHelper.GetFilenameFromDevice (prefix, device);
    }

  Ptr<PcapFileWrapper> file = pcapHelper.CreateFile (filename, std::ios::out, PcapHelper::DLT_EN10MB);
  if (promiscuous)
    {
      pcapHelper.HookDefaultSink<FdNetDevice> (device, "PromiscSniffer", file);
    }
  else
    {
      pcapHelper.HookDefaultSink<FdNetDevice> (device, "Sniffer", file);
    }
}

void
FdNetDeviceHelper::EnableAsciiInternal (
  Ptr<OutputStreamWrapper> stream,
  stdfwd::string prefix,
  Ptr<NetDevice> nd,
  bool explicitFilename)
{
  //
  // All of the ascii enable functions vector through here including the ones
  // that are wandering through all of devices on perhaps all of the nodes in
  // the system.  We can only deal with devices of type FdNetDevice.
  //
  Ptr<FdNetDevice> device = nd->GetObject<FdNetDevice> ();
  if (device == 0)
    {
      NS_LOG_INFO ("FdNetDeviceHelper::EnableAsciiInternal(): Device " << device << " not of type ns3::FdNetDevice");
      return;
    }

  //
  // Our default trace sinks are going to use packet printing, so we have to
  // make sure that is turned on.
  //
  Packet::EnablePrinting ();

  //
  // If we are not provided an OutputStreamWrapper, we are expected to create
  // one using the usual trace filename conventions and do a Hook*WithoutContext
  // since there will be one file per context and therefore the context would
  // be redundant.
  //
  if (stream == 0)
    {
      //
      // Set up an output stream object to deal with private ofstream copy
      // constructor and lifetime issues.  Let the helper decide the actual
      // name of the file given the prefix.
      //
      AsciiTraceHelper asciiTraceHelper;

      stdfwd::string filename;
      if (explicitFilename)
        {
          filename = prefix;
        }
      else
        {
          filename = asciiTraceHelper.GetFilenameFromDevice (prefix, device);
        }

      Ptr<OutputStreamWrapper> theStream = asciiTraceHelper.CreateFileStream (filename);

      //
      // The MacRx trace source provides our "r" event.
      //
      asciiTraceHelper.HookDefaultReceiveSinkWithoutContext<FdNetDevice> (device, "MacRx", theStream);

      return;
    }

  //
  // If we are provided an OutputStreamWrapper, we are expected to use it, and
  // to providd a context.  We are free to come up with our own context if we
  // want, and use the AsciiTraceHelper Hook*WithContext functions, but for
  // compatibility and simplicity, we just use Config::Connect and let it deal
  // with the context.
  //
  // Note that we are going to use the default trace sinks provided by the
  // ascii trace helper.  There is actually no AsciiTraceHelper in sight here,
  // but the default trace sinks are actually publicly available static
  // functions that are always there waiting for just such a case.
  //
  uint32_t deviceid = nd->GetIfIndex ();
  std::ostringstream oss;

  oss << "/NodeList/" << nd->GetNode ()->GetId () << "/DeviceList/" << deviceid << "/$ns3::FdNetDevice/MacRx";
  Config::Connect (oss.str (), MakeBoundCallback (&AsciiTraceHelper::DefaultReceiveSinkWithContext, stream));
}

NetDeviceContainer
FdNetDeviceHelper::Install (Ptr<Node> node) const
{
  return NetDeviceContainer (InstallPriv (node));
}

NetDeviceContainer
FdNetDeviceHelper::Install (stdfwd::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return NetDeviceContainer (InstallPriv (node));
}

NetDeviceContainer
FdNetDeviceHelper::Install (const NodeContainer &c) const
{
  NetDeviceContainer devs;

  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); i++)
    {
      devs.Add (InstallPriv (*i));
    }

  return devs;
}

Ptr<NetDevice>
FdNetDeviceHelper::InstallPriv (Ptr<Node> node) const
{
  Ptr<FdNetDevice> device = m_deviceFactory.Create<FdNetDevice> ();
  device->SetAddress (Mac48Address::Allocate ());
  node->AddDevice (device);
  return device;
}

} // namespace ns3
