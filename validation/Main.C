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
using rdi = std::filesystem::recursive_directory_iterator;

//----------------------------------------
//Template to call for generating code for creating a PDF document with Latex
template <class P> void PDFGen(std::string outputDest)
{
	std::string namepdf = outputDest + "/PDF-" + outputDest;

	PDFCreate(namepdf);

	std::string path = ("./" + outputDest);

	int i = 0;

	for(const auto& dirEntry : rdi(path)){

		std::filesystem::path file = dirEntry.path();

		i++;

		if(file.extension() == ".pdf"){  //to only select the graph vector images
		
			if(i % 8 == 0){

				LatexAdd(namepdf, file);
				NewPage(namepdf);
			}
			else{
				LatexAdd(namepdf, file);
			}
		}
		else{
			cout << "skipped." << endl;

			i--;
		}
	}

	PDFClose(namepdf);

	std::string PDFPrint = "pdflatex -halt-on-error -output-directory " + outputDest + " " + namepdf + ".tex";

	system(PDFPrint.c_str());
	
// add command to auto run "pdflatex -halt-on-error -output-directory 'outputdest' namepdf"
}
//-------------------------------------------
// Template to call to generate Subfigure doc for Latex document
template <class S> void SubfigureGen(std::string outputDest)
{
	std::string nameSub = outputDest + "/SubFigure-" + outputDest;

	LatexCreate(nameSub);

	std::string path = ("./" + outputDest);

	int i = 0;

	for(const auto& dirEntry : rdi(path)){

		std::filesystem::path file = dirEntry.path();

		i++;

		if(file.extension() == ".pdf"){

			if(i % 8 == 0){

				LatexAdd(nameSub, file);
				NewPage(nameSub);
			}
			else{
				LatexAdd(nameSub, file);
			}
		}
		else{
			cout << "skipped." <<endl;

			i--;
		}
	}
		
	LatexClose(nameSub);
}
//-------------------------------------------
// Main program to run
void Main()
{
	ifstream plot_list;
	ifstream file_list;

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

	if(files.empty()){

		cout << "No ROOT File specified, closing." << endl;

		return 0;
	}

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

	if(plots.empty()){

// plots vector is empty, recursively plot everything in the ROOT file.

		for(int k = 0; k < files.size(); k++){

			std::string fileName = files[k];
		
			TFile* f = TFile::Open(fileName.c_str(), "read");

			int namePostion = fileName.rfind("/");

			int nameEnd = fileName.rfind(".");

			std::string fileDestination;

			fileDestination = fileName.substr(namePostion+1, nameEnd-6);

			if(fileDestination.find('.') != string::npos){

				std::replace(fileDestination.begin(), fileDestination.end(), '.', '-');
			}

		auto created_new_directory = std::filesystem::create_directory(fileDestination);

		RecursivePlot(f, fileDestination);
	
		PDFGen<string>(fileDestination);
	
		}
	}
	else{

// Creating output directory to print the histograms to

		cout << "Where would you like the output destination to be? \n" ;
		cout << "\n";
	
		string outputDest; 
		cin >> outputDest;

		auto created_new_directory = std::filesystem::create_directory(outputDest);

// Determining what format of .tex file to create

		cout << "\n";
		cout << "How would you like this compiled? \n";
		cout << " \n";
		cout << "    1) Full PDF \n";
		cout << "    2) Subfigure Latex File \n";
		cout << "    3) Both \n";
		cout << " \n";
		cout << "NOTE: any numeric input greater than 4 will just output the histogram images. \n";
		cout << "\n";

		int choice;
		cin >> choice;

// Printing the histogram images as pdf (this is where you would call your draw functions)

		DrawTH1Multi(files, plots, kOkabelto1, outputDest);

		DrawTH1MultiLayered(files, plots, kOkabelto1, outputDest);

		DrawTH1MultiRatio(files, plots, kOkabelto1, outputDest);

		DrawTH1MultiStacked(files, plots, kOkabelto1, outputDest);

// Creating and adding the histograms to the correct .tex file format

		if(choice == 1){
	
			PDFGen<string>(outputDest);
		
		}
		else if(choice == 2){
	
			SubfigureGen<string>(outputDest);
		
		}
		else if(choice == 3){
		
			SubfigureGen<string>(outputDest);
	
			PDFGen<string>(outputDest);
		
		}
		else{
			cout << "Histograms have been printed, closing." << endl;
		
			return 0;
		}

	} //From the else statement from checking LoP has stuff in it
} //Main




















