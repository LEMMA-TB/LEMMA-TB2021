#include <TString.h>
#include "AnaLEMMA.h"

void runAnaLEMMA()
{
  char tt[100];
  gROOT->ProcessLine(".L AnaLEMMA.C");
 
	//Here insert input file 
	sprintf(tt,"build/Lemma2018MC_Pos45000_TBe_60_FieldF_calo_gconv_N500.root");
	cout << "Input file is: " << tt << endl;

	//Opening tree and running analysis
	TFile *filename = TFile::Open(tt);
	gROOT->ProcessLine("AnaLEMMA t");
	gROOT->ProcessLine("t.Loop()");

	//Creating output file name
	tt[strlen(tt)-5]='\0';  //take input filename and remove ".root"
	TString to;		//define output string to
	to = tt;
	to += "_out.root";	//output string is same as input one + _out.root
	cout << "Output file is: " << to << endl;

	//Moving pippo in to
	TString cmd;
	cmd = "mv pippo.root "; 
	cmd += to;		//cmd is "mv pippo.root to"
	gSystem->Exec(cmd);
	
	cout << "root -l " << to << " to see the results of the analysis" << endl; 

}
