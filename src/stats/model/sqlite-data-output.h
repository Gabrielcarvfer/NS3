/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 Drexel University
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
 * Author: Joe Kopena (tjkopena@cs.drexel.edu)
 */

#pragma once

#include "../../core/model/nstime.h"

#include "data-output-interface.h"

#define STATS_HAS_SQLITE3

#include <sqlite3.h>

namespace ns3 {

//------------------------------------------------------------
//--------------------------------------------
/**
 * \ingroup dataoutput
 * \class SqliteDataOutput
 * \brief Outputs data in a format compatible with SQLite
 */
class SqliteDataOutput : public DataOutputInterface {
public:
  SqliteDataOutput();
  virtual ~SqliteDataOutput();

  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void);
  
  virtual void Output (DataCollector &dc);

protected:
  virtual void DoDispose ();

private:
  /**
   * \ingroup dataoutput
   *
   * \brief Class to generate OMNeT output
   */
  class SqliteOutputCallback : public DataOutputCallback {
public:
    /**
     * Constructor
     * \param owner pointer to the instance this object belongs to
     * \param run experiment descriptor
     */
    SqliteOutputCallback(Ptr<SqliteDataOutput> owner, stdfwd::string run);

    /**
     * Destructor
     */
    ~SqliteOutputCallback ();

    /**
     * \brief Generates data statistics
     * \param key the SQL key to use
     * \param variable the variable name
     * \param statSum the stats to print
     */
    void OutputStatistic (stdfwd::string key,
                          stdfwd::string variable,
                          const StatisticalSummary *statSum);

    /**
     * \brief Generates a single data output
     * \param key the SQL key to use
     * \param variable the variable name
     * \param val the value
     */
    void OutputSingleton (stdfwd::string key,
                          stdfwd::string variable,
                          int val);

    /**
     * \brief Generates a single data output
     * \param key the SQL key to use
     * \param variable the variable name
     * \param val the value
     */
    void OutputSingleton (stdfwd::string key,
                          stdfwd::string variable,
                          uint32_t val);

    /**
     * \brief Generates a single data output
     * \param key the SQL key to use
     * \param variable the variable name
     * \param val the value
     */
    void OutputSingleton (stdfwd::string key,
                          stdfwd::string variable,
                          double val);

    /**
     * \brief Generates a single data output
     * \param key the SQL key to use
     * \param variable the variable name
     * \param val the value
     */
    void OutputSingleton (stdfwd::string key,
                          stdfwd::string variable,
                          stdfwd::string val);

    /**
     * \brief Generates a single data output
     * \param key the SQL key to use
     * \param variable the variable name
     * \param val the value
     */
    void OutputSingleton (stdfwd::string key,
                          stdfwd::string variable,
                          Time val);

private:
    Ptr<SqliteDataOutput> m_owner; //!< the instance this object belongs to
    stdfwd::string m_runLabel; //!< Run label
    sqlite3_stmt *m_insertSingletonStatement; //!< Prepared singleton insert statement

    // end class SqliteOutputCallback
  };


  sqlite3 *m_db; //!< pointer to the SQL database

  /**
   * \brief Execute a sqlite3 query
   * \param exe the query to execute
   * \return sqlite return code.
   */
  int Exec (stdfwd::string exe);

  // end class SqliteDataOutput
};

// end namespace ns3
};



