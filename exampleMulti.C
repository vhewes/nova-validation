
// exampleMulit.C by will barrett

#include "TFile.h"
#include "PlottingUtils.h"
#include "MultiPlotting.h"
#include "Latex.h"
#include "string"
#include "fstream"
#include "filesystem"

using namespace std;

void exampleMulti()
{
//Creating and checking for directory "figures" to store the PDFs

	auto create_new_directory = std::filesystem::create_directory("figures");


//Each function will call for 2 vectors and the color.
//
//First vector will be the list of the graphs to be found in each file.
//
//Second vector will be the list of files to be loaded to find the graphs from.

// Creating the Latex Document that will be getting the figures
	
	std::string name = "FigureTesting";

	LatexCreate(name);

//Creating vector list of each file

	std::vector<string> files;
	files.push_back("valid.hist.root");
	files.push_back("prod5.root");
	files.push_back("prod5p1.root");


//Creating vector list of each graph wanting to draw

	std::vector<string> bars;
	bars.push_back("validgenie/Enu");
	bars.push_back("validgenie/numu/Enu");
	bars.push_back("validgenie/nue/Enu");

	
//	Hist ("graph1", "valid.hist.root", "validgenie/Enu");

//Drawing each individual graph - FILE FIRST
//	DrawTH1Indiv(files, bars, kOkabelto1);

//Drawing each individual graph - GRAPH FIRST
	DrawTH1Multi(files, bars, kOkabelto1);

// Drawing Layered Graph
	DrawTH1MultiLayered(files, bars, kOkabelto1);

// Drawing Ratio Graph
	DrawTH1MultiRatio(files, bars, kOkabelto1);

// Drawing Stacked Graph
	DrawTH1MultiStacked(files, bars, kOkabelto1);

// Recursive Plotting
//	TFile* f = TFile::Open("valid.hist.root", "read");
//	RecursivePlotting(f, files);	

// adding the plots to the figure file


//	LatexAdd(name, file);


//Closing the Latex Doc to be used	
	LatexClose(name);

//Uploading the Doc to Github repo



}
