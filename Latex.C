
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

//	std::vector<string> files;
//	files.push_back("valid.hist.root");
//	files.push_back("prod5.root");
//	files.push_back("prod5p1.root");
	
	//Creating vector list of each graph wanting to draw

//	std::vector<string> bars;
//	bars.push_back("validgenie/Enu");
//	bars.push_back("validgenie/numu/Enu");
//	bars.push_back("validgenie/nue/Enu");

	std::string name = "SubfigureTesting";

	fstream my_file;

	my_file.open(name+".tex", ios::out);

	if (!my_file) {
		cout << "File not created!";
	}
	else{
		cout << "File created successfully!";

		my_file << "\\begin{figure}[htbp]" <<endl;
		my_file << "  \\centering" <<endl;

	//	for each figure do this


		my_file.close();
	}
	return 0;
}

	
