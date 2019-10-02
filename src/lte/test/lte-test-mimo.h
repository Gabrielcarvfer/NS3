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
 * Author: Marco Miozzo <marco.miozzo@cttc.es>
 */

#pragma once

#include "../../core/model/simulator.h"
#include "../../core/model/test.h"


using namespace ns3;


/**
 * \ingroup lte-test
 * \ingroup tests
 *
 * \brief This system test program creates different test cases with a 
 * single eNB and single UE. The traffic is configured to be in saturation 
 * mode. It is checked if the throughput reaches the expected values 
 * when MIMO is used.
 */
class LenaMimoTestCase : public TestCase
{
public:
  /**
   * Constructor
   *
   * \param dist the distance
   * \param estThrDl the estimated throughput DL
   * \param schedulerType the scheduler type
   * \param useIdealRrc true if use ideal RRC
   */
  LenaMimoTestCase (uint16_t dist, std::vector<uint32_t> estThrDl, stdfwd::string schedulerType, bool useIdealRrc);
  virtual ~LenaMimoTestCase ();

private:
  virtual void DoRun (void);
  
  /**
   * Get RLC buffer sample
   * \param rlcStats Ptr<RadioBearerStatsCalculator>
   * \param imsi the IMSI
   * \param rnti the RNTI
   */
  void GetRlcBufferSample (Ptr<RadioBearerStatsCalculator> rlcStats, uint64_t imsi, uint8_t rnti);
  
  /**
   * Builds the test name string based on provided parameter values
   * \param dist the distance
   * \param schedulerType the scheduler type
   * \param useIdealRrc if true use the ideal RRC
   * \returns the name string
   */
  static stdfwd::string BuildNameString (uint16_t dist, stdfwd::string schedulerType, bool useIdealRrc);
  uint16_t m_dist; ///< the distance
  std::vector<uint32_t> m_estThrDl; ///< estimated throughput DL
  stdfwd::string m_schedulerType; ///< the scheduler type
  bool m_useIdealRrc; ///< whether to use the ideal RRC
  
  std::vector <uint64_t> m_dlDataRxed; ///< DL data received

};


/**
 * \ingroup lte-test
 * \ingroup tests
 *
 * \brief Lena Test Mimo Suite
 */

class LenaTestMimoSuite : public TestSuite
{
public:
  LenaTestMimoSuite ();
};


