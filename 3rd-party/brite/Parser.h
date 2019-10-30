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
#ifndef PARSER_H
#define PARSER_H

#include "Util.h"
namespace brite {

#define MAXLINE 10000
#define MAXFILENAME 50

class ModelPar {

public:
  int GetHS() {return HS;}
  int GetLS() {return LS;}
  void SetHS(int hs) { HS = hs;}
  void SetLS(int ls) { LS = ls;}
  void SetModelType(int t) { model = t; }
  int GetModelType() { return model; }

protected:
  int model;
  int HS;             // Side one of plane
  int LS;             // Inner Side one of plane

};

class RouterWaxPar : public ModelPar{

public:

  RouterWaxPar(int n, int hs, int ls, int np, 
	       int ig, int m_edges, double a, double b, 
	       int bw, double bw_min, double bw_max);

  int GetN() { return N; }
  int GetNP() { return NP; }
  int GetIG() { return IG; }
  int GetM() { return m; }
  double GetA() { return alpha; }
  double GetB() { return beta; }
  int GetBW() { return BW; }
  double GetBWMin() { return BWmin; }
  double GetBWMax() { return BWmax; }
  void SetBW(int bw) { BW = bw; }
  void SetBWMin(double bw_min) { BWmin = bw_min; }
  void SetBWMax(double bw_max) { BWmax = bw_max; }  

private:
  int N;              // Size
  int NP;             // Node placement strategy
  int IG;             // Growth type
  int m;              // Number of edges per newly added node
  double alpha, beta; // Waxman parameters
  int BW;             // Bandwidth distribution
  double BWmin;
  double BWmax;

};

class ASWaxPar : public ModelPar {

public:

  ASWaxPar(int n, int hs, int ls, int np, 
	   int ig, int m_edges, double a, double b, 
	   int bw, double bw_min, double bw_max);

  int GetN() { return N; }
  int GetNP() { return NP; }
  int GetIG() { return IG; }
  int GetM() { return m; }
  double GetA() { return alpha; }
  double GetB() { return beta; }
  int GetBW() { return BW; }
  double GetBWMin() { return BWmin; }
  double GetBWMax() { return BWmax; }
  void SetBW(int bw) { BW = bw; }
  void SetBWMin(double bw_min) { BWmin = bw_min; }
  void SetBWMax(double bw_max) { BWmax = bw_max; }  

private:

  int N;              // Size
  int NP;             // Node placement strategy
  int IG;             // Growth type
  int m;              // Number of edges per newly added node
  double alpha, beta; // Waxman parameters
  int BW;             // Bandwidth distribution
  double BWmin;
  double BWmax;

};

class RouterBarabasiAlbertPar : public ModelPar{

public:

  RouterBarabasiAlbertPar(int n, int hs, int ls, int np, int m_edges, 
		    int bw, double bw_min, double bw_max);

  int GetN() { return N; }
  int GetNP() { return NP; }
  int GetM() { return m; }
  int GetBW() { return BW; }
  double GetBWMin() { return BWmin; }
  double GetBWMax() { return BWmax; }
  void SetBW(int bw) { BW = bw; }
  void SetBWMin(double bw_min) { BWmin = bw_min; }
  void SetBWMax(double bw_max) { BWmax = bw_max; }

private:

  int N;              // Size
  int NP;             // Node placement strategy
  int m;              // Number of edges per newly added node
  int BW;             // Bandwidth distribution
  double BWmin;
  double BWmax;

};

class ASBarabasiAlbertPar : public ModelPar {

public:

  ASBarabasiAlbertPar(int n, int hs, int ls, int np, int m_edges, 
		int bw, double bw_min, double bw_max);
  int GetN() { return N; }
  int GetNP() { return NP; }
  int GetM() { return m; }
  int GetBW() { return BW; }
  double GetBWMin() { return BWmin; }
  double GetBWMax() { return BWmax; }
  void SetBW(int bw) { BW = bw; }
  void SetBWMin(double bw_min) { BWmin = bw_min; }
  void SetBWMax(double bw_max) { BWmax = bw_max; }

 private:
  int N;              // Size
  int NP;             // Node placement strategy
  int m;              // Number of edges per newly added node
  int BW;             // Bandwidth distribution
  double BWmin;
  double BWmax;

};

class TopDownPar : public ModelPar {

public:

  TopDownPar(int ec, int K, 
	     int bw_inter, double bw_inter_min, double bw_inter_max,
	     int bw_intra, double bw_intra_min, double bw_intra_max);

  void SetModelPar(int i, ModelPar* model) {
    assert(i >= 0 && i <= 1);
    model_pars[i] = model;
  }
  ModelPar* GetModelPar(int i) { return model_pars[i]; }
  int GetK() { return k; }
  int GetEC() { return EC; }
  void SetM(int m) { m_edges = m; }
  int GetM() { return m_edges; }
  int GetBWInter() { return BWInter; }
  double GetBWInterMin() { return BWIntermin; }
  double GetBWInterMax() { return BWIntermax; }
  int GetBWIntra() { return BWIntra; }
  double GetBWIntraMin() { return BWIntramin; }
  double GetBWIntraMax() { return BWIntramax; }

private:

  int EC;             // Edge connection method
  int k;
  int m_edges;
  int BWInter;             // Bandwidth distribution (Inter-domain)
  double BWIntermin;
  double BWIntermax;
  int BWIntra;             // Bandwidth distribution (Intra-somain)
  double BWIntramin;
  double BWIntramax;
  ModelPar* model_pars[2];    // Models for AS and Router-level

};

class BottUpPar : public ModelPar{

public:

  BottUpPar(int gm, int at, int m, 
	    int bw_inter, double bw_inter_min, double bw_inter_max);

  void SetModelPar(int i, ModelPar* model) {
    assert(i >= 0 && i <= 1);
    model_pars[i] = model;
  }
  ModelPar* GetModelPar(int i) { return model_pars[i]; }
  int GetGM() { return GM; }
  int GetAT() { return AT; }
  int GetASNodes() { return as_nodes; }
  void SetM(int m) { m_edges = m; }
  int GetM() { return m_edges; }
  int GetBWInter() { return BWInter; }
  double GetBWInterMin() { return BWIntermin; }
  double GetBWInterMax() { return BWIntermax; }

private:
  int as_nodes;       // Number of AS Nodes
  int GM;             // Groping Method
  int AT;             // Assignment type of routers to ASes
  int m_edges;
  int BWInter;             // Bandwidth distribution (Inter-domain)
  double BWIntermin;
  double BWIntermax;
  ModelPar* model_pars[2];    // Models for AS and Router-level

};

class ImportedFilePar : public ModelPar {

public:

  enum FileFormat {BRITE = 1, GTITM = 2, NLANR = 3, CAIDA = 4};
  ImportedFilePar(std::string f, FileFormat t, 
		  int hs, int ls, int bw, 
		  double bw_min, double bw_max);
  std::string GetFileName() { return filename; }
  FileFormat GetFormat() { return format; }
  int GetHS() { return HS; } 
  int GetLS() { return LS; } 
  int  GetBW() { return BW; } 
  double GetBWMin() { return BWmin; } 
  double GetBWMax() { return BWmax; } 

private:

  std::string filename;
  FileFormat format;
  int HS;
  int LS;
  int BW;
  double BWmin;
  double BWmax;
  
};


class Parse {

  friend class ImportedBriteTopologyModel;
  friend class ImportedGTitmTopologyModel;
  friend class ImportedNLANRTopologyModel;
  friend class ImportedInetTopologyModel;

public:

  Parse(std::string filename);
  ~Parse();
  ModelPar* ParseConfigFile();
  void ParseSeed(std::string f, unsigned short int s[]);
  void ResetFilePointer();
  void ParseError(std::string e, std::string g);
  bool OutputBrite() { return (output_formats[0] == 1)?true:false;}
  bool OutputOtter() { return (output_formats[1] == 1)?true:false;}

private:

  std::ifstream infile;
  int GetNextToken(std::string& a);
  int GetNextTokenList(std::vector<std::string>& a);
  int GetNextTokenList(std::string& from, int& pos, std::vector<std::string>& toks);
  void ParseIntField(std::string f, int& v);
  void ParseIntField(int& v);
  void ParseDoubleField(std::string f, double& v);
  void ParseDoubleField(double& v);
  void ParseStringField(std::string f);
  void ParseStringField(std::string f, std::string& s);
  int FileSize();
  bool IsDelim(char ch);
  bool IsComment(char ch);
  std::vector<char> delimiters;
  std::vector<int> output_formats;

  RouterWaxPar* ParseRouterWaxman();
  ASWaxPar* ParseASWaxman();
  RouterBarabasiAlbertPar* ParseRouterBarabasiAlbert();
  ASBarabasiAlbertPar* ParseASBarabasiAlbert();
  TopDownPar* ParseTopDownHier();
  BottUpPar* ParseBottUpHier();
  ImportedFilePar* ParseImportedFile(int model);

};

} // namespace brite

#endif /* PARSER_H */
