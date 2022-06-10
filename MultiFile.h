
#pragma once


#include "TCanvas.h"
#include "vector"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "Okabelto.h"

#include "PlotUtils.h"


void DrawTH1Indiv(std::vector<string> files, std::vector<TH1*> hists, int color, std::string const& name)
{
	int nFiles = files.size();
	int nHists = hists.size();
	
	for (size_t i=1; i < nFiles; ++i){

		for (size_t j=1; j < nHists; ++j){

			LoadAndDrawTH1(TFile* files[i], hists[i], color, "plots/" +name);
	
		}
	}
}
