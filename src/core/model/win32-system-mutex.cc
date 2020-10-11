/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage.inria.fr>
 */

#include <thread>
#include <mutex>
#include <cstring>
#include <cerrno> // for strerror

#include "fatal-error.h"
#include "system-mutex.h"
#include "log.h"


/**
 * @file
 * @ingroup thread
 * Mutex critical section primitive definitions for Unix-like systems.
 */

namespace ns3 {

NS_LOG_COMPONENT_DEFINE_MASK ("SystemMutex", ns3::LOG_PREFIX_TIME);

/** System-dependent implementation of SystemMutex. */
class SystemMutexPrivate
{
public:
  SystemMutexPrivate ();
  ~SystemMutexPrivate ();

  void Lock (void);         /**< Acquire ownership of the mutex. */
  void Unlock (void);       /**< Release ownership of the mutex. */

private:
  std::mutex m_mutex{}; /**< The mutex. */
};

SystemMutexPrivate::SystemMutexPrivate ()
{
  NS_LOG_FUNCTION (this);
}

SystemMutexPrivate::~SystemMutexPrivate ()
{
  NS_LOG_FUNCTION (this);
}

void
SystemMutexPrivate::Lock (void)
{
  NS_LOG_FUNCTION (this);

  m_mutex.lock();
}

void
SystemMutexPrivate::Unlock (void)
{
  NS_LOG_FUNCTION (this);

  m_mutex.unlock();
}

SystemMutex::SystemMutex ()
  : m_priv (new SystemMutexPrivate ())
{
  NS_LOG_FUNCTION (this);
}

SystemMutex::~SystemMutex ()
{
  NS_LOG_FUNCTION (this);
  delete m_priv;
}

void
SystemMutex::Lock ()
{
  NS_LOG_FUNCTION (this);
  m_priv->Lock ();
}

void
SystemMutex::Unlock ()
{
  NS_LOG_FUNCTION (this);
  m_priv->Unlock ();
}

CriticalSection::CriticalSection (SystemMutex &mutex)
  : m_mutex (mutex)
{
  NS_LOG_FUNCTION (this << &mutex);
  m_mutex.Lock ();
}

CriticalSection::~CriticalSection ()
{
  NS_LOG_FUNCTION (this);
  m_mutex.Unlock ();
}

} // namespace ns3
