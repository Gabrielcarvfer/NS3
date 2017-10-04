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
 * Author: Manuel Requena <manuel.requena@cttc.es>
 * Modified by Marco Miozzo <mmiozzo@ctt.es>
 *     Extend to Data and SRS frames
 */

#ifndef LTE_TEST_UPLINK_SINR_H
#define LTE_TEST_UPLINK_SINR_H

#include "ns3/spectrum-value.h"

#include "ns3/test.h"


using namespace ns3;


/**
 * Test 1.2 SINR calculation in uplink
 */
class LteUplinkSinrTestSuite : public TestSuite
{
public:
  LteUplinkSinrTestSuite ();
};


class LteUplinkDataSinrTestCase : public TestCase
{
public:
  LteUplinkDataSinrTestCase (Ptr<SpectrumValue> sv1, Ptr<SpectrumValue> sv2, Ptr<SpectrumValue> sinr, std::string name);
  virtual ~LteUplinkDataSinrTestCase ();

private:
  virtual void DoRun (void);

  Ptr<SpectrumValue> m_sv1;
  Ptr<SpectrumValue> m_sv2;
  Ptr<const SpectrumModel> m_sm;
  Ptr<SpectrumValue> m_expectedSinr;
};


class LteUplinkSrsSinrTestCase : public TestCase
{
  public:
    LteUplinkSrsSinrTestCase (Ptr<SpectrumValue> sv1, Ptr<SpectrumValue> sv2, Ptr<SpectrumValue> sinr, std::string name);
    virtual ~LteUplinkSrsSinrTestCase ();
    
  /** 
   * Callback to be connected to an LteChunkProcessor to collect the reported SINR
   * 
   * \param sinr 
   */
  void ReportSinr (const SpectrumValue& sinr);

private:
  virtual void DoRun (void);
  
  Ptr<SpectrumValue> m_sv1;
  Ptr<SpectrumValue> m_sv2;
  Ptr<const SpectrumModel> m_sm;
  
  Ptr<SpectrumValue> m_expectedSinr;
  Ptr<SpectrumValue> m_actualSinr;
};


#endif /* LTE_TEST_UPLINK_SINR_H */
