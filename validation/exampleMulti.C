
// exampleMulit.C by will barrett

#include "TFile.h"
#include "PlottingUtils.h"
#include "MultiPlotting.h"
#include "Latex.h"

#include "filesystem"
#include "string"

using namespace std;



void exampleMulti()
{


//Each function will call for 2 vectors and the color.
//
//First vector will be the list of the graphs to be found in each file.
//
//Second vector will be the list of files to be loaded to find the graphs from.


//creating a directory to put the images in
//

	auto created_new_directory = std::filesystem::create_directory("figures");

//created the latex file
//
	std::string name = "example";

	LatexCreate("figures-" + name);



//Creating vector list of each file

	std::vector<string> files;
	files.push_back("Files/valid.hist.root");
	files.push_back("Files/prod5.root");
	files.push_back("Files/prod5p1.root");


//Creating vector list of each graph wanting to draw

	std::vector<string> bars;
	bars.push_back("validgenie/Enu");
	bars.push_back("validgenie/numu/Enu");
	bars.push_back("validgenie/nue/Enu");


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


	using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

	std::string path = "./figures";

	for (const auto& dirEntry : recursive_directory_iterator(path)){
		
		std::filesystem::path file = dirEntry.path();

		LatexAdd("figures-" + name , file);

	}


	LatexClose("figures-" + name);

//	DrawTH1Multi(files, bars, kOkabelto1);

// Drawing Layered Graph
//	DrawTH1MultiLayered(files, bars, kOkabelto1);

// Drawing Ratio Graph
//	DrawTH1MultiRatio(files, bars, kOkabelto1);

// Drawing Stacked Graph
//	DrawTH1MultiStacked(files, bars, kOkabelto1);

// Recursive Plotting
//	TFile* f = TFile::Open("valid.hist.root", "read");
//	RecursivePlotting(f, files);	


}
