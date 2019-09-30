/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Bucknell University
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
 * Authors: L. Felipe Perrone (perrone@bucknell.edu)
 *          Tiago G. Rodrigues (tgr002@bucknell.edu)
 *
 * Modified by: Mitch Watrous (watrous@u.washington.edu)
 */

#pragma once

#include "probe.h"
#include "../../core/model/object.h"
#include "../../core/model/callback.h"
#include "../../core/model/boolean.h"
#include "../../core/model/traced-value.h"
#include "../../core/model/simulator.h"
#include "../../core/model/nstime.h"

namespace ns3 {

/**
 * \ingroup probes
 *
 * This class is designed to probe an underlying ns3 TraceSource exporting
 * an ns3::Time.  This probe exports a trace source "Output" of type 
 * double, in units of seconds. The Output trace source emits a value when 
 * either the trace source emits a new value, or when SetValue () is called.
 *
 * The current value of the probe can be polled with the GetValue ()
 * method.
 */
class TimeProbe : public Probe
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId ();
  TimeProbe ();
  virtual ~TimeProbe ();

  /**
   * \return the most recent value (units of seconds)
   */
  double GetValue (void) const;

  /**
   * \param value set the traced Time to a new value
   */
  void SetValue (Time value);

  /**
   * \brief Set a probe value by its name in the Config system
   *
   * \param path Config path to access the probe
   * \param value set the traced Time to a new value
   */
  static void SetValueByPath (std::string path, Time value);

  /**
   * \brief connect to a trace source attribute provided by a given object
   *
   * \param traceSource the name of the attribute TraceSource to connect to
   * \param obj ns3::Object to connect to
   * \return true if the trace source was successfully connected
   */
  virtual bool ConnectByObject (std::string traceSource, Ptr<Object> obj);

  /**
   * \brief connect to a trace source provided by a config path
   *
   * \param path Config path to bind to
   *
   * Note, if an invalid path is provided, the probe will not be connected
   * to anything.
   */
  virtual void ConnectByPath (std::string path);

private:
  /**
   * \brief Method to connect to an underlying ns3::TraceSource of type Time 
   *
   * \param oldData previous value of the Time 
   * \param newData new value of the Time 
   */
  void TraceSink (Time oldData, Time newData);

  TracedValue<double> m_output; //!< Output trace source.
};

} // namespace ns3


