/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 NICT
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
 * Author: Hajime Tazaki <tazaki@nict.go.jp>
 */
#ifndef LINUX_IPV4_RAW_SOCKET_FACTORY_H
#define LINUX_IPV4_RAW_SOCKET_FACTORY_H

#include "ns3/socket-factory.h"

namespace ns3 {

class Socket;

/**
 * \ingroup socket
 *
 * \brief API to create IPV4 RAW socket instances
 *
 * This abstract class defines the API for IPV4 RAW socket factory.
 * All IPV4-RAW implementations must provide an implementation of CreateSocket
 * below.
 *
 * \see LinuxIpv4RawSocketFactoryImpl
 */
class LinuxIpv4RawSocketFactory : public SocketFactory
{
public:
  static TypeId GetTypeId (void);

};

} // namespace ns3

#endif /* LINUX_IPV4_RAW_SOCKET_FACTORY_H */
