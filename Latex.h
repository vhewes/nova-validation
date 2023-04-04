
// Latex.h by William Barrett
//
// This code is used to generate the markup necessary to create 
// Latex sub-figure document
//

#include "iostream"
#include "fstream"
#include "string"

using namespace std;

//-----------------------------------------------------------------
void LatexCreate(std::string const& name)
{
	fstream my_file;

	my_file.open(name + ".tex", ios::out);

	if (!my_file){
		cout << "File not created!" << endl;
	}
	else {
		cout << name + ".tex created successsfully!" << endl;

		my_file << "\\begin{figure}[htbp]" << endl;

		my_file.close();
	}

}
//-----------------------------------------------------------------
void LatexAdd(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", ios::app);

	if (!my_file){

		cout << "File not found!" << endl;
	}
	else {

		cout << "Added to " + name + ".tex" << endl;

		my_file << "  \\begin{subfigure}{0.49\\textwidth}" << endl;
		my_file << "   \\centering" << endl;
		my_file << "   \\includegraphics[width=0.95\\linewidth,height=5cm]{}" << endl;
		my_file << "   \\caption{}" << endl;
		my_file << "   \\label{}" << endl;
		my_file << "  \\end{subfigure}" << endl;

		my_file.close();
	}

}
//-----------------------------------------------------------------
void LatexClose(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", ios::app);

	if (!my_file){

		cout << "File not found!" << endl;
	}
	else {

		cout << "File " + name + ".tex is ready!" << endl;

		my_file << "\\end{figure}" << endl;

		my_file.close();
	}

}
//-----------------------------------------------------------------
