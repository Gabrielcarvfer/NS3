/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 University of Washington
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
 */



#include <thread>
#include <mutex>
#include <cerrno>        // for ETIMEDOUT
#include <condition_variable>

#include "fatal-error.h"
#include "system-condition.h"
#include "log.h"


/**
 * \file
 * \ingroup thread
 * ns3::SystemCondition and ns3::SystemConditionPrivate implementations.
 */

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SystemCondition");

/**
 * \ingroup thread
 * Implementation of SystemCondition for Unix-like systems.
 */
class SystemConditionPrivate {
public:
  /** Conversion from ns to s. */
  static const uint64_t NS_PER_SEC = (uint64_t)1000000000;

  /** Constructor. */
  SystemConditionPrivate ();
  /** Destructor. */
  ~SystemConditionPrivate ();

  /**
   * Set the condition.
   *
   * \param [in] condition The new condition value.
   */
  void SetCondition (bool condition);
  /**
   * Get the condition value.
   *
   * \returns The condition value.
   */
  bool GetCondition (void);
  /** Signal the condition. */
  void Signal (void);
  /** Broadcast the condition. */
  void Broadcast (void);
  /**
   * Unset the condition, then wait for another thread
   * to set it with SetCondition. */
  void Wait (void);
  /**
   * Unset the condition, then wait for a limited amount of wall-clock
   * time for another thread to set it with SetCondition.
   *
   * \param [in] ns Maximum time to wait, in ns.
   * \returns \c true if the condition timed out; \c false if the other
   * thread set it.
   */
  bool TimedWait (uint64_t ns);

private:
  /** Mutex controlling access to the condition. */
  std::mutex m_mutex;
  /** The thread condition variable. */
  std::condition_variable m_cond;
  /** The condition state. */
  bool m_condition;
};

SystemConditionPrivate::SystemConditionPrivate ()
{
  NS_LOG_FUNCTION (this);

  m_condition = false;
}

SystemConditionPrivate::~SystemConditionPrivate() 
{
  NS_LOG_FUNCTION (this);
}
	
void
SystemConditionPrivate::SetCondition (bool condition)
{
  NS_LOG_FUNCTION (this << condition);
  m_condition = condition;
}
	
bool
SystemConditionPrivate::GetCondition (void)
{
  NS_LOG_FUNCTION (this);
  return m_condition;
}
	
void
SystemConditionPrivate::Signal (void)
{
  NS_LOG_FUNCTION (this);

  std::lock_guard<std::mutex> lk (this->m_mutex);
  this->m_cond.notify_one ();
}
	
void
SystemConditionPrivate::Broadcast (void)
{
  NS_LOG_FUNCTION (this);

  std::lock_guard<std::mutex> lk (this->m_mutex);
  this->m_cond.notify_all ();
}

void
SystemConditionPrivate::Wait (void)
{
  NS_LOG_FUNCTION (this);

  std::unique_lock<std::mutex> lk (this->m_mutex);
  m_condition = false;
  while (m_condition == false)
    {
      this->m_cond.wait (lk);

    }
  lk.unlock();

}

bool
SystemConditionPrivate::TimedWait (uint64_t ns)
{
  NS_LOG_FUNCTION (this << ns);


  std::unique_lock<std::mutex> lk (this->m_mutex);
  while (m_condition == false)
    {
      auto rc = this->m_cond.wait_for(lk, std::chrono::nanoseconds(ns));
      if (rc == std::cv_status::timeout)
        {
          lk.unlock();
          return true;
        }
    }
  lk.unlock();
  return false;
}
	
SystemCondition::SystemCondition() 
  : m_priv (new SystemConditionPrivate ())
{
  NS_LOG_FUNCTION (this);;
}

SystemCondition::~SystemCondition () 
{
  NS_LOG_FUNCTION (this);
  delete m_priv;
}

void
SystemCondition::SetCondition (bool condition) 
{
  NS_LOG_FUNCTION (this << condition);
  m_priv->SetCondition (condition);
}

bool
SystemCondition::GetCondition (void) 
{
  NS_LOG_FUNCTION (this);
  return m_priv->GetCondition ();
}

void
SystemCondition::Signal (void) 
{
  NS_LOG_FUNCTION (this);
  m_priv->Signal ();
}

void
SystemCondition::Broadcast (void) 
{
  NS_LOG_FUNCTION (this);
  m_priv->Broadcast ();
}

void
SystemCondition::Wait (void) 
{
  NS_LOG_FUNCTION (this);
  m_priv->Wait ();
}

bool
SystemCondition::TimedWait (uint64_t ns) 
{
  NS_LOG_FUNCTION (this << ns);
  return m_priv->TimedWait (ns);
}

} // namespace ns3
