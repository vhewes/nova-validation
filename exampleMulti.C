

#include "TFile.h"
#include "PlotUtils.h"
#include "MultiFile.h"


void exampleMulti()
{

	TFile* f0 = TFile::Open("valid.hist.root", "read");
	TFile* f1 = TFile::Open("prod5.root", "read");
	TFile* f2 = TFile::Open("prod5p1.root", "read");

	std::vector<string> files;
	files.push_back("valid.hist.root");
	files.push_back("prod5.root");
	files.push_back("prod5p1.root");

	std::vector<TH1*> hists;
	hists.push_back(LoadTH1(f0, "validgenie/Enu"));
	hists.push_back(LoadTH1(f1, "validgenie/numu/Enu"));
	hists.push_back(LoadTH1(f2, "validgenie/nue/Enu"));


	DrawTH1Indiv(files, hists, kOkabelto1, "plots/");


}
