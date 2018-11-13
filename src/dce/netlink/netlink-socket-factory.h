/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 Liu Jian
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
 * Author: Liu Jian <liujatp@gmail.com>
 *         Hajime Tazaki <tazaki@sfc.wide.ad.jp>
 */

#ifndef NETLINK_SOCKET_FACTORY_H
#define NETLINK_SOCKET_FACTORY_H

#include "ns3/socket-factory.h"
#include <set>

namespace ns3 {

class Socket;

/**
 * This can be used as an interface in a node in order for the node to
 * generate NetlinkSockets.
 */
class NetlinkSocketFactory : public SocketFactory
{
public:
  static TypeId GetTypeId (void);

  NetlinkSocketFactory ();

  /**
   * Creates a NetlinkSocket and returns a pointer to it.
   *
   * \return a pointer to the created socket
   */
  virtual Ptr<Socket> CreateSocket (void);

  std::multiset<uint32_t> m_pidsList; // to prevent PID reuse (unique per node)
};

} // namespace ns3

#endif /* NETLINK_SOCKET_FACTORY_H */
