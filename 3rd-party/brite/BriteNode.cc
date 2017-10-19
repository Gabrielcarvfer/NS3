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
#pragma implementation "BriteNode.h"

#include "BriteNode.h"

namespace brite {

BriteNode::BriteNode(int i) {

  nodeId = i;
  nodeAddr = 0;
  inDegree = 0;
  outDegree = 0;
  nodeColor = BLACK;

}

BriteNode::BriteNode(NodeConf* c) {

  nodeInfo = c;

}

ASNodeConf::ASNodeConf() { 

  SetCost(1.0);
  t = NULL;
  SetNodeType(AS_NODE);
  astype = AS_NONE;
  
}

RouterNodeConf::RouterNodeConf() { 

  SetCost(1.0);
  SetNodeType(RT_NODE);
  rttype = RT_NONE;

}


void ASNodeConf::SetTopology(Topology* top, int asid) {
  
  t = top; 
  if (t != NULL) {
    Graph* g = t->GetGraph();
    for (int i = 0; i < g->GetNumNodes(); i++) {
      RouterNodeConf* rt_conf = (RouterNodeConf*)(g->GetNodePtr(i)->GetNodeInfo());
      rt_conf->SetASId(asid);
    }
  } 
}

} // namespace brite
