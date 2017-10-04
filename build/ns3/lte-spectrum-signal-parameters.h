/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 CTTC
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
 * Author: Nicola Baldo <nbaldo@cttc.es>
 * Modified by Marco Miozzo <mmiozzo@cttc.es> (add data and ctrl diversity)
 */

#ifndef LTE_SPECTRUM_SIGNAL_PARAMETERS_H
#define LTE_SPECTRUM_SIGNAL_PARAMETERS_H


#include <ns3/spectrum-signal-parameters.h>

namespace ns3 {

class PacketBurst;
class LteControlMessage;


/**
 * \ingroup lte
 *
 * Signal parameters for Lte
 */
struct LteSpectrumSignalParameters : public SpectrumSignalParameters
{

  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();

  /**
   * default constructor
   */
  LteSpectrumSignalParameters ();

  /**
   * copy constructor
   */
  LteSpectrumSignalParameters (const LteSpectrumSignalParameters& p);

  /**
   * The packet burst being transmitted with this signal
   */
  Ptr<PacketBurst> packetBurst;
};


/**
* \ingroup lte
*
* Signal parameters for Lte Data Frame (PDSCH), and eventually after some 
* control messages through other control channel embedded in PDSCH
* (i.e. PBCH)
*/
struct LteSpectrumSignalParametersDataFrame : public SpectrumSignalParameters
{
  
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
  
  /**
  * default constructor
  */
  LteSpectrumSignalParametersDataFrame ();
  
  /**
  * copy constructor
  */
  LteSpectrumSignalParametersDataFrame (const LteSpectrumSignalParametersDataFrame& p);
  
  /**
  * The packet burst being transmitted with this signal
  */
  Ptr<PacketBurst> packetBurst;
  
  std::list<Ptr<LteControlMessage> > ctrlMsgList;
  
  uint16_t cellId;
};


/**
* \ingroup lte
*
* Signal parameters for Lte DL Ctrl Frame (RS, PCFICH and PDCCH)
*/
struct LteSpectrumSignalParametersDlCtrlFrame : public SpectrumSignalParameters
{
  
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
  
  /**
  * default constructor
  */
  LteSpectrumSignalParametersDlCtrlFrame ();
  
  /**
  * copy constructor
  */
  LteSpectrumSignalParametersDlCtrlFrame (const LteSpectrumSignalParametersDlCtrlFrame& p);


  std::list<Ptr<LteControlMessage> > ctrlMsgList;
  
  uint16_t cellId;
  bool pss; // primary synchronization signal
};



/**
* \ingroup lte
*
* Signal parameters for Lte SRS Frame
*/
struct LteSpectrumSignalParametersUlSrsFrame : public SpectrumSignalParameters
{
  
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
  
  /**
  * default constructor
  */
  LteSpectrumSignalParametersUlSrsFrame ();
  
  /**
  * copy constructor
  */
  LteSpectrumSignalParametersUlSrsFrame (const LteSpectrumSignalParametersUlSrsFrame& p);
  
  uint16_t cellId;
};


}  // namespace ns3


#endif /* LTE_SPECTRUM_SIGNAL_PARAMETERS_H */
