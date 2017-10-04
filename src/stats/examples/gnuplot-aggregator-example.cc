/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 University of Washington
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
 * Author: Mitch Watrous (watrous@u.washington.edu)
 */

#include "ns3/core-module.h"
#include "ns3/stats-module.h"

using namespace ns3;

namespace {

//===========================================================================
// Function: Create2dPlot
//
//
// This function creates a 2-Dimensional plot.
//===========================================================================

void Create2dPlot ()
{
  using namespace std;

  string fileNameWithoutExtension = "gnuplot-aggregator";
  string plotTitle                = "Gnuplot Aggregator Plot";
  string plotXAxisHeading         = "Time (seconds)";
  string plotYAxisHeading         = "Double Values";
  string plotDatasetLabel         = "Data Values";
  string datasetContext           = "Dataset/Context/String";

  // Create an aggregator.
  Ptr<GnuplotAggregator> aggregator =
    CreateObject<GnuplotAggregator> (fileNameWithoutExtension);

  // Set the aggregator's properties.
  aggregator->SetTerminal ("png");
  aggregator->SetTitle (plotTitle);
  aggregator->SetLegend (plotXAxisHeading, plotYAxisHeading);

  // Add a data set to the aggregator.
  aggregator->Add2dDataset (datasetContext, plotDatasetLabel);

  // aggregator must be turned on
  aggregator->Enable ();

  double time;
  double value;

  // Create the 2-D dataset.
  for (time = -5.0; time <= +5.0; time += 1.0)
    {
      // Calculate the 2-D curve
      //
      //                   2
      //     value  =  time   .
      //
      value = time * time;

      // Add this point to the plot.
      aggregator->Write2d (datasetContext, time, value);
    }

  // Disable logging of data for the aggregator.
  aggregator->Disable ();
}


} // anonymous namespace


int main (int argc, char *argv[])
{
  Create2dPlot ();

  return 0;
}
