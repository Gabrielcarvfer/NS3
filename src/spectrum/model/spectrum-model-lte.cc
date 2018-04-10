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


#include <ns3/spectrum-model-lte.h>

namespace ns3 {


Ptr<SpectrumModel> SpectrumModelLte;



class static_SpectrumModelLte_initializer
{
public:
  static_SpectrumModelLte_initializer ()
  {
      std::vector<double> lte_freqs = {
              2110,   1920,
              1930,   1850,
              1805,   1710,
              2110,   1710,
              869,    824,
              875,    830,
              2620,   2500,
              925,    880,
              1844.9, 1749.9,
              2110,   1710,
              1475.9, 1427.9,
              728,    698,
              746,    777,
              758,    788,
              734,    704,
              860,    815,
              875,    830,
              791,    832,
              1495.9, 1447.9,
              1900,   1900,
              2010,   2010,
              1850,   1850,
              1930,   1930,
              1910,   1910,
              2570,   2570,
              1880,   1880,
              2300,   2300};
    std::vector<double> freqs;
    for (int i = 0; i < lte_freqs.size(); i++)
      {
        freqs.push_back (lte_freqs.at(i)*1000.0);
      }
    SpectrumModelLte = Create<SpectrumModel> (freqs);
  }

} static_SpectrumModelLte_initializer_instance;





}
