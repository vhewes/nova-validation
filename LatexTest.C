
#include "Latex.h"

#include "filesystem"
#include "string"

using namespace std;

//---------------------------------------------------------------
void  LatexTest()
{

	std::string name = "PDFtest";

	PDFCreate("figures-" + name);

	using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

	std::string path = ("./figures");

	int i = 0;

	for (const auto& dirEntry : recursive_directory_iterator(path)){

		std::filesystem::path file = dirEntry.path();

		i++;

		if (i % 8 == 0){

			LatexAdd("figures-" + name, file);

			NewPage("figures-" + name);
		}
		else{
			LatexAdd("figures-" + name, file);

		}
	}
		
	PDFClose("figures-" + name);

}



