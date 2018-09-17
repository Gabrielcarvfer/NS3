/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2006 INRIA
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
 */

#include "ns3/callback.h"
#include "ns3/assert.h"
#include "ns3/command-line.h"
#include "ns3/system-thread.h"
#include <iostream>

/**
 * \file
 * \ingroup core-examples
 * \ingroup callback
 * Example program illustrating use of callback functions and methods.
 *
 * See \ref callback
 */

using namespace ns3;

namespace {
  
/**
 * Example Callback function.
 *
 * \param [in] a The first argument.
 * \param [in] b The second argument.
 * \returns The first argument.
 */
static double
CbOne (double a, double b)
{
  std::cout << "invoke cbOne a=" << a << ", b=" << b << std::endl;
  return a;
}

/** Example Callback class. */
class MyCb {
public:
  /**
   * Example Callback class method.
   *
   * \param [in] a The argument.
   * \returns -5
   */
  int CbTwo (double a) {
    std::cout << "invoke cbTwo a=" << a << std::endl;
    return -5;
  }
};

}  // unnamed namespace

void imprime(void)
{
    std::cout<<"ziriguidum"<<std::endl;
}
int main (int argc, char *argv[])
{
    Ptr<SystemThread> st3 = Create<SystemThread> (
            MakeCallback (&imprime));
    st3->Start ();
    st3->Join();
  return 0;
}
