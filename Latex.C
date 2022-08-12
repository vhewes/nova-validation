
// Latex.C by Will Barrett
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PlotUtils.h"
#include "MultiFile.h"

//---------------------------------------------------------

//---------------------------------------------------------
void Latex() {
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

	std::string name = "LatexTesting";

	ofstream MyFile (name+".txt");
	
	//initializes the doc
	MyFile << "\\documentclass[a4paper, landscape]{article} \n";
	MyFile << "\\usepackage{graphicx} \n";
	MyFile << "\\DeclareGraphicsExtension{.pdf, .png} \n";
	MyFile << "\\usepackage{pdflscape} \n";
	MyFile << "\\begin{document} \n";
	MyFile << "\n";

	//code to generate the images in the doc
	
	std::vector<string> images;
	int nImages = images.size();

       	images.push_back(DrawTH1Multi(files, bars, kOkabelto1));

	for (size_t i=0; i < nImages; i++){
		MyFile << "\n";
		MyFile << "\\includegraphics[scale=0.5]{" << images[i]<< "} \n";
		MyFile << "\n";
	}

	//closes the doc
	MyFile << "\n";
	MyFile << "\\end{document} \n";
	
	MyFile.close();

}

