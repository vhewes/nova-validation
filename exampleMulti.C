

#include "TFile.h"
#include "PlotUtils.h"
#include "MultiFile.h"


void exampleMulti()
{

//Loading each root file

	//TFile* f0 = TFile::Open("valid.hist.root", "read");
	//TFile* f1 = TFile::Open("prod5.root", "read");
	//TFile* f2 = TFile::Open("prod5p1.root", "read");

//Creating vector list of each file

	std::vector<string> files;
	files.push_back("valid.hist.root");
	files.push_back("prod5.root");
	files.push_back("prod5p1.root");


//Creating vector list of each graph wanting to draw

	//std::vector<TH1*> hists;
	//hists.push_back(LoadTH1(f, "validgenie/Enu"));
	//hists.push_back(LoadTH1(f, "validgenie/numu/Enu"));
	//hists.push_back(LoadTH1(f, "validgenie/nue/Enu"));

	std::vector<string> bars;
	bars.push_back("validgenie/Enu");
	bars.push_back("validgenie/numu/Enu");
	bars.push_back("validgenie/nue/Enu");

	DrawTH1Indiv(files, bars, kOkabelto1);
	
	DrawTH1Multi(files, bars, kOkabelto1);

	DrawTH1MultiLayered(files, bars, kOkabelto1);
	
	DrawTH1MultiRatio(files, bars, kOkabelto1);

	DrawTH1MultiStacked(files, bars, kOkabelto1);

}
