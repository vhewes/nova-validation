#pragma once

#include "iostream"
#include "fstream"
#include "string"
#include "vector"

using namespace std;

//-----------------------------------------------------
//
//
//
//----------------------------------------------------
//Creating the Latex Document
void LatexCreate(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", ios::out);

	if (!my_file){
		cout << "File not created!";
	}
	else{
		cout << "File " + name + ".tex was created!" <<endl;

		my_file << "\\begin{figure}[htbp]" <<endl;
		my_file << "  \\centering" <<endl;

		my_file.close();
	}
}
//
//---------------------------------------------------
//Filling the document with the figures
void LatexAdd(std::string const& name, std::string const& plot)
{
	fstream my_file;

	my_file.open(name+".tex", std::ios::app);

	if (!my_file){
		cout << "File not found!";
	}
	else{
		cout << "Stuff was added to " + name + ".tex!" <<endl;

		my_file << "    \\begin{subfigure}{0.49\\textwidth}" <<endl;
		my_file << "	  \\centering" <<endl;
		my_file << "	  \\includegraphics[width=0.95\\linewidth,height=5cm]{" + plot + "}" <<endl;
		my_file << "	  \\caption{}" <<endl;
		my_file << "	  \\label{}" <<endl;
		my_file << "	\\end{subfigure}" <<endl;

		my_file.close();
	}
}
//--------------------------------------------------
//Closing the Latex Document
void LatexClose(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", std::ios::app);

	if (!my_file){
		cout << "File not found!";
	}
	else{
		cout << name + ".tex is closed and ready!" <<endl;

		my_file << "\\end{figure}";

		my_file.close();
	}
}
//--------------------------------------------------






