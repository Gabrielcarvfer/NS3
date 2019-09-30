/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@cutebugs.net>
 */

#pragma once

#include <string>
#include <fstream>
#include "file-config.h"

namespace ns3 {

/**
 * \ingroup configstore
 * \brief A class to enable saving of configuration store in a raw text file
 *
 */
class RawTextConfigSave : public FileConfig
{
public:
  RawTextConfigSave ();
  virtual ~RawTextConfigSave ();
  virtual void SetFilename (std::string filename);
  virtual void Default (void);
  virtual void Global (void);
  virtual void Attributes (void);
private:
  /// Config store output stream
  std::ofstream *m_os;
};

/**
 * \ingroup configstore
 * \brief A class to enable loading of configuration store from a raw text file
 *
 */
class RawTextConfigLoad : public FileConfig
{
public:
  RawTextConfigLoad ();
  virtual ~RawTextConfigLoad ();
  virtual void SetFilename (std::string filename);
  virtual void Default (void);
  virtual void Global (void);
  virtual void Attributes (void);
private:
  /**
   * Strip out attribute value
   * \param value the input string
   * \returns the updated string
   */
  std::string Strip (std::string value); 
  /// Config store input stream
  std::ifstream *m_is;
};

} // namespace ns3


