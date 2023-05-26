//
// Main.C by William Barrett
//
//
//----------------------------------------

#include "filesystem"
#include "fstream"
#include "vector"

#include "TFile.h"
#include "PlottingUtils.h"
#include "MultiPlotting.h"
#include "Latex.h"

using namespace std;

//----------------------------------------

void Main()
{
	ifstream plot_list;
	ifstream file_list;

// Creating and populating a Plots Vector from ListofPlots.txt
	
	std::vector<string> plots;

	plot_list.open("validation/ListofPlots.txt",ios::out);

	if(plot_list.is_open()){
		
		string plot;

		while(getline(plot_list, plot)){

			plots.push_back(plot);
		}
		
		plot_list.close();
	}


// Creating and populating a Files Vector from ListofFiles.txt

	file_list.open("validation/ListofFiles.txt", ios::out);

	std::vector<string> files;

	if(file_list.is_open()){

		string file;

		while(getline(file_list, file)){

			files.push_back(file);
		}

		file_list.close();
	}

// Creating Figures directory to print the histograms to

	auto created_new_directory = std::filesystem::create_directory("figures");

// Printing the histogram pdfs

	DrawTH1Multi(files, plots, kOkabelto1);

	DrawTH1MultiLayered(files, plots, kOkabelto1);

	DrawTH1MultiRatio(files, plots, kOkabelto1);

	DrawTH1MultiStacked(files, plots, kOkabelto1);

// Creating and adding the histograms to a .tex file

	string name = "Test";

	string place = "figures/Figures-";

	PDFCreate(place + name);

	using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

	std::string path = ("./figures");

	int i = 0;

	for(const auto& dirEntry : recursive_directory_iterator(path)){

		std::filesystem::path file = dirEntry.path();

		i++;

		if(file.extension() == ".pdf"){
		
			if(i % 8 ==0){

				LatexAdd(place + name, file);

				NewPage(place + name);
			}
			else{
				LatexAdd(place + name, file);
			}
		}
		else{
			cout << "skipped." << endl;

			i--;
		}
	}

	PDFClose(place + name);

}























