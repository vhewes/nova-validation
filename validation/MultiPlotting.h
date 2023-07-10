
//MultiFile.h by will barrett 
#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "Okabelto.h"
#include "PlottingUtils.h"
//-------------------------------------------------------------------------------------------------
// Drawing each individual graph
// loads the FILE first then the graphs from the file
void DrawTH1Indiv(std::vector<std::string> files, std::vector<std::string> bars, int color, std::string outputDest)
{
	int nFiles = files.size();
	int nBars = bars.size();
	for (size_t i=0; i < nFiles; ++i){
		TFile* f = TFile::Open(files[i].c_str());
		for (size_t j=0; j < nBars; ++j){
			//creates the name for each grach and changes some characters
			//so that it can be saved	
			std::string graph = files[i] + "-" +  bars[j];
			std::replace(graph.begin(), graph.end(), '/', '_');
			std::replace(graph.begin(), graph.end(), '.', '_');
			//Calls LoadAndDrawTH1 from PlotUtils.h
			LoadAndDrawTH1(f, bars[j], color++, outputDest+ "/" +graph);
		}
	}
}
//--------------------------------------------------------------------------------------
// Drawing each graph individually
// Calls with GRAPH to load first then calls the file to load it from
{
	int nFiles = files.size();
	int nBars = bars.size();
	for (size_t i=0; i < nBars; ++i){
		for (size_t j=0; j < nFiles; ++j){
			TFile* f = TFile::Open(files[j].c_str());
			std::string graph = bars[i] + "-" + files[j];
			std::replace(graph.begin(), graph.end(), '/', '_');
			std::replace(graph.begin(), graph.end(), '.', '_');
			LoadAndDrawTH1(f, bars[i], color++, outputDest+ "/" +graph);
		}
	}
}
//-----------------------------------------------------------------------------------------
// Drawing Layered Histograms of histograms with same name from different ROOT files
{
	int nFiles = files.size();
	int nBars = bars.size();
	// Cycles first through each graph requested
	for (size_t i=0; i < nBars; ++i){
		// Creates vector for graphs to be loaded into
		std::vector<TH1*> hists;
		
		// Cycles through each file
		for (size_t j=0; j < nFiles; ++j){
			TFile* f = TFile::Open(files[j].c_str());
			// Loads each graph pulled from each file into the  vector
			hists.push_back(LoadTH1(f, bars[i]));			
		}
		// creates a temp name for the graph
		// changes the characters so that it can be read by function
		std::string tempname = bars[i];
		std::replace(tempname.begin(), tempname.end(), '/', '_');
		std::string name = outputDest+ "/" + tempname + "_layered" ;
		//Runs Layered graph functiion from PlotUtils.h
		DrawTH1(hists, files, color, name);
	}
}
//----------------------------------------------------------------------------------------------
// Creating Ratio Graph
void DrawTH1MultiRatio(std::vector<std::string> files, std::vector<std::string> bars, int color, std::string outputDest)
{
	int nFiles = files.size();
	int nBars = bars.size();
	for (size_t i=0; i < nBars; ++i){
		std::vector<TH1*> hists;
		for (size_t j=0; j < nFiles; ++j){
			TFile* f = TFile::Open(files[j].c_str());
			hists.push_back(LoadTH1(f, bars[i]));
		}
		std::string tempname = bars[i];
		std::replace(tempname.begin(), tempname.end(), '/', '_');
		std::string name = outputDest+ "/" + tempname + "_ratio" ; 
		//Runs Ratio graph function from PlotUtils.h
		DrawTHRatio(hists, color, name);
	}
}
//-----------------------------------------------------------------------------------------
// Creating Stacked Graph
void DrawTH1MultiStacked(std::vector<std::string> files, std::vector<std::string> bars, int color, std::string outputDest)
{
	int nFiles = files.size();
	int nBars = bars.size();
	for (size_t i=0; i < nBars; ++i){
		std::vector<TH1*> hists;
		for (size_t j=0; j < nFiles; ++j){
			TFile* f = TFile::Open(files[j].c_str());
			hists.push_back(LoadTH1(f, bars[i]));
		}
		std::string tempname = bars[i];
		std::replace(tempname.begin(), tempname.end(), '/', '_');
		std::string name = outputDest+ "/" + tempname + "_stacked" ;
		//Runs Stacked graph function from PlotUtils.h
		DrawTHStack(hists, files, color, name);
	}
}
//------------------------------------------------------------------------------------
// Recursive Plotting
void RecursivePlotting(TDirectory* dir, std::vector<std::string> files, std::string const& name="")
{
   TIter next(dir->GetListOfKeys());
   TKey* k;
   std::string prefix = name;
   if(!prefix.empty()) prefix += "/";
   while ((k = (TKey*)next())){
	std::string tag = prefix + std::string(k->GetName());
	auto d = dynamic_cast<TDirectory*>(k->ReadObj());
	auto h = dynamic_cast<TH1*>(k->ReadObj());
	if(d){
		RecursivePlotting(d, files, tag);
	}
	else if(h){
		int nFiles = files.size();
		std::vector<TH1*> hists;
		for (size_t i=0; i < nFiles; i++){
			TFile* q = TFile::Open(files[i].c_str());
			hists.push_back(LoadTH1(q, tag));
		}
		std::string tempname = tag;
		std::replace(tempname.begin(), tempname.end(), '/', '_');
		std::string name = "figures/" + tempname;
		DrawTH1(hists, files, kOkabelto1, name);
		DrawTHStack(hists, files, kOkabelto1, name);
	}
	else{
	std::cout << "object " << k->GetName() << " is not a directory or 1D histogram, skipping..." << std::endl;
	}
  }
}
//--------------------------------------------------------------------------------------
