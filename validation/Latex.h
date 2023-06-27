
// Latex.h by William Barrett
//
// This code is used to generate the markup necessary to create 
// Latex sub-figure document as well as PDF document
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
void LatexAdd(std::string const& name, std::string const& plot)
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
		my_file << "   \\includegraphics[width=\\textwidth,height=5cm]{" << plot << "}" << endl;

		int namePostion = plot.rfind("/");

		int nameEnd = plot.rfind(".");

		std::string plot_name;

		plot_name = plot.substr(namePostion+1, nameEnd-7);

		std::replace(plot_name.begin(), plot_name.end(), '_', ' ');  

		my_file << "   \\caption{" + plot_name + "}" << endl;
		my_file << "   \\label{}" << endl;
		my_file << "  \\end{subfigure}" << endl;
		my_file << "\\hfill" << endl;

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
void PDFCreate(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", ios::out);

	if (!my_file){
		cout << "File not created." << endl;
	}
	else{
		cout << name + ".tex has been created" << endl;

// loading all of the packages necessary for the document

		my_file << "\\documentclass[12pt]{article}" << endl;
		my_file << "\\usepackage{graphicx}" << endl;
		my_file << "\\usepackage{subcaption}" << endl;
		my_file << "\\usepackage[dvipsnames,table]{xcolor}" << endl;
		my_file << "\\usepackage[a4paper, margin=2cm,includehead]{geometry}" << endl;
		my_file << "\\usepackage{fancyhdr}" << endl;
		my_file << "\\usepackage{hyperref}" << endl;
		my_file << "\\usepackage{pdfpages}" << endl;
		my_file << "\\usepackage{caption}" << endl;
		my_file << "\\usepackage{subcaption}" << endl;
//		my_file << "\\usepackage{float}" << endl;
		my_file << "\\usepackage{bookmark}" << endl;
		my_file << endl;
		
// beging the actual document

		my_file << "\\begin{document}" << endl;
		my_file << endl;
		my_file << "\\begin{figure}[ht]" <<endl;	

		my_file.close();
	}
}
//------------------------------------------------------------------
void PDFClose(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", ios::app);

	if(!my_file){
		cout << "file not found" << endl;
	}
	else{
//		cout << name + ".tex is ready" << endl;

		my_file << "\\end{figure}" << endl;
		my_file << endl;
		my_file << "\\end{document}" << endl;

		my_file.close();
	}
}
//-----------------------------------------------------------------
void NewPage(std::string const& name)
{
	fstream my_file;

	my_file.open(name+".tex", ios::app);

	if(!my_file){
		cout << "file not found" << endl;
	}
	else{
		my_file << "\\end{figure}" << endl;
		my_file << "\\clearpage" << endl;
		my_file << "\\begin{figure}[htbp]" << endl;
		my_file << "\\ContinuedFloat" << endl;

		my_file.close();
	}
}
//-------------------------------------------------------------------













