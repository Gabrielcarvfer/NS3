/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "ns3/timer.h"
#include "ns3/test.h"
#include "ns3/simulator.h"
#include "ns3/nstime.h"

namespace {
void bari (int)
{
}
void bar2i (int, int)
{
}
void bar3i (int, int, int)
{
}
void bar4i (int, int, int, int)
{
}
void bar5i (int, int, int, int, int)
{
}
void barcir (const int &)
{
}
void barir (int &)
{
}
} // anonymous namespace

using namespace ns3;

class TimerStateTestCase : public TestCase
{
public:
  TimerStateTestCase ();
  virtual void DoRun (void);
};

TimerStateTestCase::TimerStateTestCase ()
  : TestCase ("Check correct state transitions")
{
}
void
TimerStateTestCase::DoRun (void)
{
  Timer timer = Timer (Timer::CANCEL_ON_DESTROY);

  timer.SetFunction (&bari);
  timer.SetArguments (1);
  timer.SetDelay (Seconds (10.0));
  NS_TEST_ASSERT_MSG_EQ (!timer.IsRunning (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.IsExpired (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsSuspended (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.GetState (), Timer::EXPIRED, "");
  timer.Schedule ();
  NS_TEST_ASSERT_MSG_EQ (timer.IsRunning (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsExpired (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsSuspended (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.GetState (), Timer::RUNNING, "");
  timer.Suspend ();
  NS_TEST_ASSERT_MSG_EQ (!timer.IsRunning (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsExpired (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.IsSuspended (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.GetState (), Timer::SUSPENDED, "");
  timer.Resume ();
  NS_TEST_ASSERT_MSG_EQ (timer.IsRunning (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsExpired (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsSuspended (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.GetState (), Timer::RUNNING, "");
  timer.Cancel ();
  NS_TEST_ASSERT_MSG_EQ (!timer.IsRunning (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.IsExpired (), true, "");
  NS_TEST_ASSERT_MSG_EQ (!timer.IsSuspended (), true, "");
  NS_TEST_ASSERT_MSG_EQ (timer.GetState (), Timer::EXPIRED, "");
}

class TimerTemplateTestCase : public TestCase
{
public:
  TimerTemplateTestCase ();
  virtual void DoRun (void);
  virtual void DoTeardown (void);
  void bazi (int)
  {
  }
  void baz2i (int, int)
  {
  }
  void baz3i (int, int, int)
  {
  }
  void baz4i (int, int, int, int)
  {
  }
  void baz5i (int, int, int, int, int)
  {
  }
  void baz6i (int, int, int, int, int, int)
  {
  }
  void bazcir (const int&)
  {
  }
  void bazir (int&)
  {
  }
  void bazip (int *)
  {
  }
  void bazcip (const int *)
  {
  }
};

TimerTemplateTestCase::TimerTemplateTestCase ()
  : TestCase ("Check that template magic is working")
{
}

void
TimerTemplateTestCase::DoRun (void)
{
  Timer timer = Timer (Timer::CANCEL_ON_DESTROY);

  int a = 0;
  int &b = a;
  const int &c = a;

  timer.SetFunction (&bari);
  timer.SetArguments (2);
  timer.SetArguments (a);
  timer.SetArguments (b);
  timer.SetArguments (c);
  timer.SetFunction (&barir);
  timer.SetArguments (2);
  timer.SetArguments (a);
  timer.SetArguments (b);
  timer.SetArguments (c);
  timer.SetFunction (&barcir);
  timer.SetArguments (2);
  timer.SetArguments (a);
  timer.SetArguments (b);
  timer.SetArguments (c);
  // the following call cannot possibly work and is flagged by
  // a runtime error.
  // timer.SetArguments (0.0);
  timer.SetDelay (Seconds (1.0));
  timer.Schedule ();

  timer.SetFunction (&TimerTemplateTestCase::bazi, this);
  timer.SetArguments (3);
  timer.SetFunction (&TimerTemplateTestCase::bazir, this);
  timer.SetArguments (3);
  timer.SetFunction (&TimerTemplateTestCase::bazcir, this);
  timer.SetArguments (3);

  timer.SetFunction (&bar2i);
  timer.SetArguments (1, 1);
  timer.SetFunction (&bar3i);
  timer.SetArguments (1, 1, 1);
  timer.SetFunction (&bar4i);
  timer.SetArguments (1, 1, 1, 1);
  timer.SetFunction (&bar5i);
  timer.SetArguments (1, 1, 1, 1, 1);
  // unsupported in simulator class
  // timer.SetFunction (&bar6i);
  // timer.SetArguments (1, 1, 1, 1, 1, 1);

  timer.SetFunction (&TimerTemplateTestCase::baz2i, this);
  timer.SetArguments (1, 1);
  timer.SetFunction (&TimerTemplateTestCase::baz3i, this);
  timer.SetArguments (1, 1, 1);
  timer.SetFunction (&TimerTemplateTestCase::baz4i, this);
  timer.SetArguments (1, 1, 1, 1);
  timer.SetFunction (&TimerTemplateTestCase::baz5i, this);
  timer.SetArguments (1, 1, 1, 1, 1);
  // unsupported in simulator class
  // timer.SetFunction (&TimerTemplateTestCase::baz6i, this);
  // timer.SetArguments (1, 1, 1, 1, 1, 1);

  Simulator::Run ();
  Simulator::Destroy ();
}

void
TimerTemplateTestCase::DoTeardown (void)
{
  Simulator::Run ();
  Simulator::Destroy ();
}

static class TimerTestSuite : public TestSuite
{
public:
  TimerTestSuite ()
    : TestSuite ("timer", UNIT)
  {
    AddTestCase (new TimerStateTestCase (), TestCase::QUICK);
    AddTestCase (new TimerTemplateTestCase (), TestCase::QUICK);
  }
} g_timerTestSuite;
