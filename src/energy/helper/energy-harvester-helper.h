/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014 Wireless Communications and Networking Group (WCNG),
 * University of Rochester, Rochester, NY, USA.
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
 * Author: Cristiano Tapparello <cristiano.tapparello@rochester.edu>
 */

#pragma once

#include "../../core/model/attribute.h"
#include "../../core/model/object-factory.h"
#include "../../network/helper/node-container.h"
#include "../../core/model/ptr.h"
#include "../model/energy-harvester.h"
#include "energy-harvester-container.h"

#include "../model/energy-source.h"
#include "energy-source-container.h"


namespace ns3 {
  
/**
 * \ingroup energy
 * \brief Creates EnergyHarvester objects.
 *
 * This class creates and installs energy harvesters onto network nodes.
 *
 */
class EnergyHarvesterHelper
{
public:
  virtual ~EnergyHarvesterHelper ();

  /**
   * \param name Name of attribute to set.
   * \param v Value of the attribute.
   *
   * Sets one of the attributes of underlying EnergyHarvester.
   */
  virtual void Set (std::string name, const AttributeValue &v) = 0;

  /**
   * \param source Pointer to the energy source where EnergyHarvester will be installed.
   * \returns An EnergyHarvesterContainer which contains all the EnergyHarvesters.
   *
   * This function installs an EnergyHarvester onto an energy source.
   */
  EnergyHarvesterContainer Install (Ptr<EnergySource> source) const;

  /**
   * \param sourceContainer List of nodes where EnergyHarvester will be installed.
   * \returns An EnergyHarvesterContainer which contains all the EnergyHarvester.
   *
   * This function installs an EnergyHarvester onto a list of energy sources.
   */
  EnergyHarvesterContainer Install (EnergySourceContainer sourceContainer) const;

  /**
   * \param nodeName Name of node where EnergyHarvester will be installed.
   * \returns An EnergyHarvesterContainer which contains all the EnergyHarvesters.
   *
   * This function installs an EnergyHarvester onto a node.
   */
  EnergyHarvesterContainer Install (std::string sourceName) const;

private:
  /**
   * \param node Pointer to node where the energy harvester is to be installed.
   * \returns Pointer to the created EnergyHarvester.
   *
   * Child classes of EnergyHarvesterHelper only have to implement this function,
   * to create and aggregate an EnergyHarvester object onto a single node. Rest of
   * the installation process (eg. installing EnergyHarvester on set of nodes) is
   * implemented in the EnergyHarvesterHelper base class.
   */
  virtual Ptr<EnergyHarvester> DoInstall (Ptr<EnergySource> source) const = 0;

};

} // namespace ns3


