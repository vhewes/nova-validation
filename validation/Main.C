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

		cout << "Recursively Plotting" << endl;

		return 0;
	
	}

// Creating Figures directory to print the histograms to

	cout << "Where would you like the output destination to be? \n" ;
	cout << "\n";
	
	string outputDest;
	cin >> outputDest;

	auto created_new_directory = std::filesystem::create_directory(outputDest);

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

// Printing the histogram images as pdf

	DrawTH1Multi(files, plots, kOkabelto1, outputDest);

	DrawTH1MultiLayered(files, plots, kOkabelto1, outputDest);

	DrawTH1MultiRatio(files, plots, kOkabelto1, outputDest);

	DrawTH1MultiStacked(files, plots, kOkabelto1, outputDest);

// Creating and adding the histograms to a .tex file

	if(choice == 1){
	
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
	}
	else if(choice == 2){
	
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
	else if(choice == 3){
		
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
	
		
		std::string namepdf = outputDest + "/PDF-" + outputDest;

		PDFCreate(namepdf);

		int j = 0;

		for(const auto& dirEntry : rdi(path)){

			std::filesystem::path file = dirEntry.path();

			j++;

			if(file.extension() == ".pdf"){  //to only select the graph vector images
		
				if(j % 8 ==0){

					LatexAdd(namepdf, file);
					NewPage(namepdf);
				}
				else{
					LatexAdd(namepdf, file);
				}
			}
			else{
				cout << "skipped." << endl;

				j--;
			}
		}

		PDFClose(namepdf);
	}
	else{
		cout << "Histograms have been printed, closing." << endl;
		
		return 0;
	}
}





















