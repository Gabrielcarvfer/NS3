/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 CTTC
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
 */


#include <ns3/spectrum-model-RANGE.h>

namespace ns3 {


Ptr<SpectrumModel> SpectrumModelRANGE;



class static_SpectrumModelRANGE_initializer
{
public:
  static_SpectrumModelRANGE_initializer ()
  {

    std::vector<double> freqs;
    for (double f = 856.5e6; f < 882e6; f+=5e6)
      {
        freqs.push_back (f);
      }
    SpectrumModelRANGE = Create<SpectrumModel> (freqs);
  }

} static_SpectrumModelRANGE_initializer_instance;





}
