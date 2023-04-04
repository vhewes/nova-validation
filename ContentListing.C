#pragma once

#include "iostream"
#include "fstream"
#include "string"
#include "vector"

#include "TFile.h"
#include "Listing.h"

using namespace std;
//--------------------------------------------------------------
void ContentListing()
{
	std::string name = "valid.hist.root";

	TFile* f = TFile::Open("valid.hist.root", "read");

	fstream my_file;

	my_file.open("Contents-" +name+".txt", ios::out);

	if (!my_file) {
		cout << "File aint there chief";
	}
	else {
		cout << "file be there homeskillet";
	}

	my_file.close();

	Lister(f);

}






