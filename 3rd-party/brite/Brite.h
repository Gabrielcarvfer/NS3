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
#ifndef BRITE_H
#define BRITE_H

#include <iostream>
#include <string>

#include "Parser.h"
#include "Models/Model.h"
#include "Models/RouterWaxmanModel.h"
#include "Models/RouterBarabasiAlbertModel.h"
#include "Models/ASWaxmanModel.h"
#include "Models/ASBarabasiAlbertModel.h"
#include "Models/ImportedFileModel.h"
#include "Models/TopDownHierModel.h"
#include "Models/BottomUpHierModel.h"
#include "Models/ImportedFileModel.h"
#include "Topology.h"

namespace brite {

class Brite {

public:

  Brite (std::string, std::string, std::string);
  ~Brite ();

  void InitSeeds(char *);
  void OutputSeeds(char *);
  void ImportFile (std::string, std::string, std::string);
  Topology* GetTopology (void);

private:
  Topology* m_topology;
};

} // namespace brite

#endif /* BRITE_H */



