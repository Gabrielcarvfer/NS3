/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
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
 * Author: Jaume Nin <jnin@cttc.es>
 */

#pragma once

#include "../../core/model/object.h"
#include "../../core/model/string.h"
#include <map>

namespace ns3 {

/**
 * \ingroup lte
 *
 * Base class for ***StatsCalculator classes. Provides
 * basic functionality to parse and store IMSI and CellId.
 * Also stores names of output files.
 */

class LteStatsCalculator : public Object
{
public:
  /**
   * Constructor
   */
  LteStatsCalculator ();

  /**
   * Destructor
   */
  virtual ~LteStatsCalculator ();

  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  static TypeId GetTypeId (void);

  /**
   * Set the name of the file where the uplink statistics will be stored.
   *
   * \param outputFilename string with the name of the file
   */
  void SetUlOutputFilename (stdfwd::string outputFilename);

  /**
   * Get the name of the file where the uplink statistics will be stored.
   * @return the name of the file where the uplink statistics will be stored
   */
  stdfwd::string GetUlOutputFilename (void);

  /**
   * Set the name of the file where the downlink statistics will be stored.
   *
   * @param outputFilename string with the name of the file
   */
  void SetDlOutputFilename (stdfwd::string outputFilename);

  /**
   * Get the name of the file where the downlink statistics will be stored.
   * @return the name of the file where the downlink statistics will be stored
   */
  stdfwd::string GetDlOutputFilename (void);

  /**
   * Checks if there is an already stored IMSI for the given path
   * @param path Path in the attribute system to check
   * @return true if the path exists, false otherwise
   */
  bool ExistsImsiPath (stdfwd::string path);

  /**
   * Stores the (path, imsi) pairs in a map
   * @param path Path in the attribute system to store
   * @param imsi IMSI value to store
   */
  void SetImsiPath (stdfwd::string path, uint64_t imsi);

  /**
   * Retrieves the imsi information for the given path
   * @param path Path in the attribute system to get
   * @return the IMSI associated with the given path
   */
  uint64_t GetImsiPath (stdfwd::string path);

  /**
   * Checks if there is an already stored cell id for the given path
   * @param path Path in the attribute system to check
   * @return true if the path exists, false otherwise
   */
  bool ExistsCellIdPath (stdfwd::string path);

  /**
   * Stores the (path, cellId) pairs in a map
   * @param path Path in the attribute system to store
   * @param cellId cell id value to store
   */
  void SetCellIdPath (stdfwd::string path, uint16_t cellId);

  /**
   * Retrieves the cell id information for the given path
   * @param path Path in the attribute system to get
   * @return the cell ID associated with the given path
   */
  uint16_t GetCellIdPath (stdfwd::string path);

protected:

  /**
   * Retrieves IMSI from Enb RLC path in the attribute system
   * @param path Path in the attribute system to get
   * @return the IMSI associated with the given path
   */
  static uint64_t FindImsiFromEnbRlcPath (stdfwd::string path);

  /**
   * Retrieves IMSI from Ue PHY path in the attribute system
   * @param path Path in the attribute system to get
   * @return the IMSI associated with the given path
   */
  static uint64_t FindImsiFromUePhy (stdfwd::string path);

  /**
   * Retrieves IMSI from LteNetDevice path in the attribute system
   * @param path Path in the attribute system to get
   * @return the IMSI associated with the given path
   */
  static uint64_t FindImsiFromLteNetDevice (stdfwd::string path);

  /**
   * Retrieves CellId from Enb RLC path in the attribute system
   * @param path Path in the attribute system to get
   * @return the CellId associated with the given path
   */
  static uint16_t FindCellIdFromEnbRlcPath (stdfwd::string path);

  /**
   * Retrieves IMSI from Enb MAC path in the attribute system
   * @param path Path in the attribute system to get
   * @param rnti RNTI of UE for which IMSI is needed
   * @return the IMSI associated with the given path and RNTI
   */
  static uint64_t FindImsiFromEnbMac (stdfwd::string path, uint16_t rnti);

  /**
   * Retrieves CellId from Enb MAC path in the attribute system
   * @param path Path in the attribute system to get
   * @param rnti RNTI of UE for which CellId is needed
   * @return the CellId associated with the given path and RNTI
   */
  static uint16_t FindCellIdFromEnbMac (stdfwd::string path, uint16_t rnti);

  /**
   * Retrieves IMSI from path for Enb in the attribute system
   * @param path Path in the attribute system to get
   * @param rnti RNTI of UE for which IMSI is needed
   * @return the IMSI associated with the given path and RNTI
   */
  static uint64_t FindImsiForEnb (stdfwd::string path, uint16_t rnti);

  /**
   * Retrieves IMSI from path for Ue in the attribute system
   * @param path Path in the attribute system to get
   * @param rnti RNTI of UE for which IMSI is needed
   * @return the IMSI associated with the given path and RNTI
   */
  static uint64_t FindImsiForUe (stdfwd::string path, uint16_t rnti);

private:
  /**
   * List of IMSI by path in the attribute system
   */
  std::map<stdfwd::string, uint64_t> m_pathImsiMap;

  /**
   * List of CellId by path in the attribute system
   */
  std::map<stdfwd::string, uint16_t> m_pathCellIdMap;

  /**
   * Name of the file where the downlink results will be saved
   */
  stdfwd::string m_dlOutputFilename;

  /**
   * Name of the file where the uplink results will be saved
   */
  stdfwd::string m_ulOutputFilename;
};

} // namespace ns3


