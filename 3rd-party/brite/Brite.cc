/****************************************************************************/
/*                  Copyright 2001, Trustees of Boston University.          */
/*                               All Rights Reserved.                       */
/*                                                                          */
/* Permission to use, copy, or modify this software and its documentation   */
/* for educational and research purposes only and without fee is hereby     */
/* granted, provided that this copyright notice appear on all copies and    */
/* supporting documentation.  For any other uses of this software, in       */
/* original or modified form, including but not limited to distribution in  */
/* whole or in part, specific prior permission must be obtained from Boston */
/* University.  These programs shall not be used, rewritten, or adapted as  */
/* the basis of a commercial software or hardware product without first     */
/* obtaining appropriate licenses from Boston University.  Boston University*/
/* and the author(s) make no representations about the suitability of this  */
/* software for any purpose.  It is provided "as is" without express or     */
/* implied warranty.                                                        */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  Author:     Alberto Medina                                              */
/*              Anukool Lakhina                                             */
/*  Title:     BRITE: Boston university Representative Topology gEnerator   */
/*  Revision:  2.0         4/02/2001                                        */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*  Modified lightly to easily interface with ns-3                          */
/*  Author:     Josh Pelkey <jpelkey@gatech.edu>                            */
/*  Date: 3/02/2011                                                         */
/****************************************************************************/
#include <cstdlib>

#include "Brite.h"

using namespace std;
namespace brite {


Brite::Brite(string confFile, string seedFile, string newseedFile) {
    ImportFile (confFile, seedFile, newseedFile);
}

Brite::~Brite() {
}

Topology* Brite::GetTopology (void) {
    return m_topology;
}

void Brite::InitSeeds(char *file_name) {

  ofstream last_seed_file;

  /* Create Parse object */
  Parse p(file_name);

  /* Parse configuration file */
  p.ParseSeed("PLACES", Model::s_places);
  p.ParseSeed("CONNECT", Model::s_connect);
  p.ParseSeed("EDGE_CONN", Model::s_edgeconn);
  p.ParseSeed("GROUPING", Model::s_grouping);
  p.ParseSeed("ASSIGNMENT", Model::s_assignment);
  p.ParseSeed("BANDWIDTH", Model::s_bandwidth);

  cout << "Place seed used: "  
       << Model::s_places[0] << " "
       << Model::s_places[1] << " "
       << Model::s_places[2] << "\n";
  cout << "Connect seed used: " 
       << Model::s_connect[0] << " "
       << Model::s_connect[1] << " "
       << Model::s_connect[2] << "\n";
  cout << "Edge conn seed used: " 
       << Model::s_edgeconn[0] << " "
       << Model::s_edgeconn[1] << " "
       << Model::s_edgeconn[2] << "\n";
  cout << "Grouping seed used: " 
       << Model::s_grouping[0] << " "
       << Model::s_grouping[1] << " "
       << Model::s_grouping[2] << "\n";
  cout << "Assigment seed used: " 
       << Model::s_assignment[0] << " "
       << Model::s_assignment[1] << " "
       << Model::s_assignment[2] << "\n";
  cout << "Bandwidth seed used: " 
       << Model::s_bandwidth[0] << " "
       << Model::s_bandwidth[1] << " "
       << Model::s_bandwidth[2] << "\n" << flush;


  last_seed_file.open("last_seed_file", ios::out);

  if (last_seed_file.fail()) {
    cerr << "Cannot open seed files for input/output...\n";
    exit(0);
  }
  
  last_seed_file << "PLACES"
		 << " " << Model::s_places[0] 
		 << " " << Model::s_places[1] 
		 << " " << Model::s_places[2] << "\n";

  last_seed_file << "CONNECT"
		 << " " << Model::s_connect[0] 
		 << " " << Model::s_connect[1] 
		 << " " << Model::s_connect[2] << "\n";

  last_seed_file << "EDGE_CONN"
		 << " " << Model::s_edgeconn[0] 
		 << " " << Model::s_edgeconn[1] 
		 << " " << Model::s_edgeconn[2] << "\n";

  last_seed_file << "GROUPING"
		 << " " << Model::s_grouping[0] 
		 << " " << Model::s_grouping[1] 
		 << " " << Model::s_grouping[2] << "\n";

  last_seed_file << "ASSIGNMENT"
		 << " " << Model::s_assignment[0] 
		 << " " << Model::s_assignment[1] 
		 << " " << Model::s_assignment[2] << "\n";

  last_seed_file << "BANDWIDTH"
		 << " " << Model::s_bandwidth[0] 
		 << " " << Model::s_bandwidth[1] 
		 << " " << Model::s_bandwidth[2] << "\n";

  last_seed_file.close();
  
}

void Brite::OutputSeeds(char *file_name) {

  ofstream seed_file;
  seed_file.open(file_name, ios::out);
  
  if (seed_file.fail()) {
    cerr << "Cannot open seed files for input/output...\n";
    exit(0);
  }
  
  seed_file << "PLACES"
	    << " " << Model::s_places[0] 
	    << " " << Model::s_places[1] 
	    << " " << Model::s_places[2] << "\n";

  seed_file << "CONNECT"
	    << " " << Model::s_connect[0] 
	    << " " << Model::s_connect[1] 
	    << " " << Model::s_connect[2] << "\n";

  seed_file << "EDGE_CONN"
	    << " " << Model::s_edgeconn[0] 
	    << " " << Model::s_edgeconn[1] 
	    << " " << Model::s_edgeconn[2] << "\n";
  
  seed_file << "GROUPING"
	    << " " << Model::s_grouping[0] 
	    << " " << Model::s_grouping[1] 
	    << " " << Model::s_grouping[2] << "\n";

  seed_file << "ASSIGNMENT"
	    << " " << Model::s_assignment[0] 
	    << " " << Model::s_assignment[1] 
	    << " " << Model::s_assignment[2] << "\n";

  seed_file << "BANDWIDTH"
	    << " " << Model::s_bandwidth[0] 
	    << " " << Model::s_bandwidth[1] 
	    << " " << Model::s_bandwidth[2] << "\n";

  cout << "Place seed stored: " 
       << Model::s_places[0] << " "
       << Model::s_places[1] << " "
       << Model::s_places[2] << "\n";
  cout << "Connect seed stored: " 
       << Model::s_connect[0] << " "
       << Model::s_connect[1] << " "
       << Model::s_connect[2] << "\n";
  cout << "Edge Connect seed stored: " 
       << Model::s_edgeconn[0] << " "
       << Model::s_edgeconn[1] << " "
       << Model::s_edgeconn[2] << "\n";
  cout << "Grouping seed used: " 
       << Model::s_grouping[0] << " "
       << Model::s_grouping[1] << " "
       << Model::s_grouping[2] << "\n";
  cout << "Assignment seed stored: " 
       << Model::s_assignment[0] << " "
       << Model::s_assignment[1] << " "
       << Model::s_assignment[2] << "\n";
  cout << "Bandwidth seed stored: " 
       << Model::s_bandwidth[0] << " "
       << Model::s_bandwidth[1] << " "
       << Model::s_bandwidth[2] << "\n" << flush;
  seed_file.close();

}

void Brite::ImportFile(string confFile, string seedFile, string newseedFile) {

  RouterWaxman* rt_wax_model;
  RouterBarabasiAlbert* rt_bar_model;
  ASWaxman* as_wax_model;
  ASBarabasiAlbert* as_bar_model;
  TopDownHierModel* td_model;
  BottomUpHierModel* bu_model;
  ImportedBriteTopologyModel* if_brite_model;
  ImportedGTitmTopologyModel* if_gtitm_model;  
  ImportedNLANRTopologyModel* if_nlanr_model;
  ImportedInetTopologyModel* if_inet_model;

  ModelPar* par;

  /* Init seed used in generation */
  InitSeeds(const_cast<char *>(seedFile.c_str ()));

  /* Create Parse object */
  Parse p(const_cast<char *>(confFile.c_str ()));

  /* Parse configuration file */
  par = p.ParseConfigFile();
  assert(par != NULL);

  switch (par->GetModelType()) {
  case RT_WAXMAN:
    rt_wax_model = new RouterWaxman((RouterWaxPar*)par);
    m_topology = new Topology(rt_wax_model);
    break;

  case RT_BARABASI:
    rt_bar_model = new RouterBarabasiAlbert((RouterBarabasiAlbertPar*)par);
    m_topology = new Topology(rt_bar_model);
    break;

  case AS_WAXMAN:
    as_wax_model = new ASWaxman((ASWaxPar*)par);
    m_topology = new Topology(as_wax_model);
    break;

  case AS_BARABASI:
    as_bar_model = new ASBarabasiAlbert((ASBarabasiAlbertPar*)par);
    m_topology = new Topology(as_bar_model);
    break;
  
  case TD_HIER:
    td_model = new TopDownHierModel((TopDownPar*)par);
    m_topology = new Topology(td_model);
    break;

  case BU_HIER:
    bu_model = new BottomUpHierModel((BottUpPar*)par);
    m_topology = new Topology(bu_model);
    break;

  case IF_ROUTER:
  case IF_AS:

    switch (((ImportedFilePar*)par)->GetFormat()) {
    case ImportedFileModel::IF_BRITE:
      cout << "Importing brite...\n" << flush;
      if_brite_model = new ImportedBriteTopologyModel((ImportedFilePar*)par);
      m_topology = new Topology(if_brite_model);
      break;

    case ImportedFileModel::IF_GTITM:
    case ImportedFileModel::IF_GTITM_TS:
      cout << "Importing gtitm...\n" << flush;
      if_gtitm_model = new ImportedGTitmTopologyModel((ImportedFilePar*)par);
      m_topology = new Topology(if_gtitm_model);
      break;

    case ImportedFileModel::IF_NLANR:
      cout << "Importing nlanr..\n" << flush;
      cout.flush();
      if_nlanr_model = new ImportedNLANRTopologyModel((ImportedFilePar*)par);
      m_topology = new Topology(if_nlanr_model);
      break;

    case ImportedFileModel::IF_INET:
      cout << "Importing Inet..\n" << flush;
      if_inet_model = new ImportedInetTopologyModel((ImportedFilePar*)par);
      m_topology = new Topology(if_inet_model);
      break;

    case ImportedFileModel::IF_SKITTER:
    default:
      cerr << "BriteMaiin(): Invalid file format for ImportedFileModel...\n";
      exit(0);
    }
    break;

  default:
    cerr << "Parsing error: invalid parameter structure returned...\n";
    exit(0);

  }

  // Check connectivity of topology
  if (!m_topology->IsConnected()) {
    cout << "Topology is not connected...\n" << flush;
  }else {
    cout << "Topology is connected!!!\n" << flush;
  }

  // Run classification algorithm
  m_topology->Classify();

  OutputSeeds(const_cast<char *>(newseedFile.c_str ()));
  
  cout << "Done!\n";
}

} // namespace brite
