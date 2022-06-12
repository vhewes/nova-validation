
//MultiFile.h by will barrett 
#pragma once


#include "TCanvas.h"
#include "vector"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "Okabelto.h"
#include "PlotUtils.h"

#include "algorithm"
#include "string"

//-------------------------------------------------------------------------------------------------
// Drawing each individual graph
// loads the FILE first then the graphs from the file
void DrawTH1Indiv(std::vector<string> files, std::vector<string> bars, int color)
{
		
	int nFiles = files.size();
	int nBars = bars.size();
	
	for (size_t i=0; i < nFiles; ++i){

		TFile* f = TFile::Open(files[i].c_str());

		for (size_t j=0; j < nBars; ++j){
			
			//creates the name for each grach and changes some characters
			//so that it can be saved	
			std::string graph = files[i] + "-" +  bars[j];
			std::replace(graph.begin(), graph.end(), '/', '~');
			std::replace(graph.begin(), graph.end(), '.', '-');
			
			//Calls LoadAndDrawTH1 from PlotUtils.h
			LoadAndDrawTH1(f, bars[j], color++, "multi/" +graph);
		}
	}
}
//--------------------------------------------------------------------------------------
// Drawing each graph individually
// Calls with GRAPH to load first then calls the file to load it from
void DrawTH1Multi(std::vector<string> files, std::vector<string> bars, int color)
{
	int nFiles = files.size();
	int nBars = bars.size();

	for (size_t i=0; i < nBars; ++i){

		for (size_t j=0; j < nFiles; ++j){

			TFile* f = TFile::Open(files[j].c_str());

			std::string graph = bars[i] + "-" + files[j];

			std::replace(graph.begin(), graph.end(), '/', '~');
			std::replace(graph.begin(), graph.end(), '.', '-');

			LoadAndDrawTH1(f, bars[i], color++, "multi/" +graph);
		}
	}
}
//-----------------------------------------------------------------------------------------
// Drawing Layered Histograms of histograms with same name from different ROOT files
void DrawTH1MultiLayered(std::vector<string> files, std::vector<string> bars, int color)
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

		std::string name = "multi/" + tempname + "_stacked" ;
		
		//Runs Layered graph functiion from PlotUtils.h
		DrawTH1(hists, color, name);
	}

}
//----------------------------------------------------------------------------------------------
// Creating Ratio Graph
void DrawTH1MultiRatio(std::vector<string> files, std::vector<string> bars, int color)
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

		std::string name = "multi/" + tempname + "_ratio" ; 
		
		//Runs Ratio graph function from PlotUtils.h
		DrawTHRatio(hists, color, name);
	}

}
//-----------------------------------------------------------------------------------------
// Creating Stacked Graph
void DrawTH1MultiStacked(std::vector<string> files, std::vector<string> bars, int color)
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

		std::string name = "multi/" + tempname + "_stacked" ; 
		
		//Runs Stacked graph function from PlotUtils.h
		DrawTHStack(hists, color, name);

	}
}
//--------------------------------------------------------------------------------------
