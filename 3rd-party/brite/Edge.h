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
#ifndef EDGE_H
#define EDGE_H
#pragma interface

#include "Util.h"
#include "BriteNode.h"

namespace brite {

#define SPEED_OF_LIGHT 299792458.0

class BriteNode;
class EdgeConf;

enum EdgeType { E_NONE, E_STUB, E_BACKBONE };

class Edge {

public:

  Edge(BriteNode* s, BriteNode* d);
  ~Edge();

  EdgeConf* GetConf() { return conf; }
  int GetId() { return id; }
  void SetId(int i) { id = i; }
  int GetEdgeCount() { return edge_count; }
  void SetConf(EdgeConf* c) { conf = c; }
  Color GetColor() { return color; }
  void SetColor(Color c) { color = c; }
  BriteNode* GetSrc() { return src; }
  BriteNode* GetDst() { return dst; }
  double Length();
  void SetDirection(bool s) { directed = s;}
  bool GetDirection() { return directed;}

 private:

  int id;
  BriteNode* src;
  BriteNode* dst;
  Color color;
  EdgeConf* conf;
  static int edge_count;
  bool directed;

};



class EdgeConf {

 public:

  enum EdgeType { RT_EDGE, AS_EDGE };
  EdgeType GetEdgeType() { return edge_type; }
  void SetEdgeType(EdgeType t) { edge_type = t; }
  double GetBW() { return BW; }
  double GetCost() { return cost; }
  void SetBW(double bw) { BW = bw; }
  void SetCost(double c) { cost = c; }

 private:

  EdgeType edge_type;
  double BW;
  double cost;

};



class ASEdgeConf : public EdgeConf {

 public:

  ASEdgeConf();
  ~ASEdgeConf();
  enum ASEdgeType {AS_NONE, AS_STUB, AS_BORDER, AS_BACKBONE};  
  ASEdgeType GetASEdgeType() { return as_edge_type; }
  void SetASEdgeType(ASEdgeType t) {  as_edge_type = t; }


 private:

  ASEdgeType as_edge_type;


};

class RouterEdgeConf : public EdgeConf {

 public:

  enum RouterEdgeType { RT_NONE, RT_LEAF, RT_STUB, RT_BORDER, RT_BACKBONE };
  RouterEdgeConf(double length);
  ~RouterEdgeConf();
  double GetLength() { return length; }
  double GetDelay() { return delay; }

  RouterEdgeType GetRouterEdgeType() { return rt_edge_type; }
  void SetLength(double l) { length = l; }
  void SetDelay(double d) { delay = d; }
  void SetRouterEdgeType(RouterEdgeType t) {  rt_edge_type = t; }


 private:

  RouterEdgeType rt_edge_type;
  double length;	
  double delay;
  
};

} // namespace brite

#endif /* EDGE_H */
