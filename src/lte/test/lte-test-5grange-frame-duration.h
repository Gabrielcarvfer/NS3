/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
+ * Copyright (c) 2019 Luis Pacheco
+ *
+ * This program is free software; you can redistribute it and/or modify
+ * it under the terms of the GNU General Public License version 2 as
+ * published by the Free Software Foundation;
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+ * GNU General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, write to the Free Software
+ * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
+ *
+ * Author: Luis Pacheco <luisbelem@gmail.com>
+ *
+ */


#ifndef NS3_LTE_TEST_5GRANGE_FRAME_DURATION_H

#include "ns3/test.h"

using namespace ns3;

/**
 * \ingroup lte-test
 * \ingroup tests
 *
 * \brief 5G RANGE frame duration test
 */

class Lte5grangeFrameDurationTestSuite : public TestSuite
{
 public:
  Lte5grangeFrameDurationTestSuite ();

};

/**
 * \ingroup lte-test
 * \ingroup tests
 *
 * \brief
 */

class Lte5grangeFrameDurationTestCase : public TestCase
{
 public:
  /**
   * Constructor
   *
   * \param name reference name
   * \param usePdcchForCqiGeneration use PDCCH for CQI generation
   * \param dlMcs DL MCS
   * \param ulMcs UL MCS
   */
  Lte5grangeFrameDurationTestCase (std::string name, uint64_t subFrameDur);
  virtual ~Lte5grangeFrameDurationTestCase ();

  /**
   * \brief DL Scheduling function
   * \param dlInfo DL info
   */
  void DlScheduling (DlSchedulingCallbackInfo dlInfo);

  Time lastSubFrame;
  uint64_t subFrameDuration;
 private:
  virtual void DoRun (void);

};

#endif //NS3_LTE_TEST_5GRANGE_FRAME_DURATION_H
