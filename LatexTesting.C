
#include "Latex.h"
#include "filesystem"
#include "iostream"
#include "fstream"
#include "vector"
#include "string"
#include "sstream"

using namespace std;
using std::filesystem::recursive_directory_iterator;

void LatexTesting()
{
	std::string name = "Testing";

	LatexCreate(name);

	std::string filepath = ".//multi";

	filesystem::path p(filepath);

	for (const auto& dirEntry : recursive_directory_iterator(filepath)){

		auto h =  dirEntry; 
		
		LatexAdd(name, h);

	}

	LatexClose(name);
}

