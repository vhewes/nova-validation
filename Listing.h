#pragma once

#include "TFile.h"

//--------------------------------------------------------

void Lister(TDirectory* dir, std::string const& name="")
{
	fstream my_file;

	my_file.open("Contents.txt", ios::app);

	TIter next(dir->GetListOfKeys());
	TKey* k;

	std::string prefix = name;
	if(!prefix.empty()) prefix += "_";

	while ((k = (TKey*)next())){
		std::string tag = prefix + std::string(k->GetName());

		auto d = dynamic_cast<TDirectory*>(k->ReadObj());
		auto h = dynamic_cast<TH1*>(k->ReadObj());
		
		// if its a directory, call function again to go inside
		if (d){
		       	Lister(d, tag);
		}
		else if (h){
		       my_file << name <<endl;
		}	       
		else {
			my_file << k << " - just and object" <<endl;
	}

	my_file.close();

	}
}

