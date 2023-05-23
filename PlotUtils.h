#pragma once

#include "TCanvas.h"
#include "vector"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"

#include "TFile.h"
#include "Okabelto.h"

//-----------------------------------------------------------------------------
//Loading 1D histograms
TH1F* LoadTH1(TFile* f, std::string const& path)
{
  // call Get to fetch from file, and check the pointer is not null
  TH1F* h = (TH1F*)f->Get(path.c_str());
  if (!h) {
     std::cerr << path << " not found! exiting" <<std::endl;
     exit(1);
  }
  return h;
}
//-----------------------------------------------------------------------------
TH2F* LoadTH2(TFile* f, std::string const& path)
{
 TH2F* g = (TH2F*)f->Get(path.c_str());
 if (!g) {
    std::cerr << path << " not found! exiting" <<std::endl;
    exit(1);
 }
 return g;
}
//-----------------------------------------------------------------------------
//Drawing 1D hist
void DrawTH1(TH1* h, int color, std::string const& name)
{
  TCanvas c("c", "c", 1600, 900);
  h->SetLineColor(kBlack);
  h->SetFillColor(color);
  h->SetLineWidth(1);
  h->Draw("hist");
<<<<<<< HEAD
  c.SaveAs(("plots/"+name+".png").c_str());
  c.SaveAs(("plots/"+name+".pdf").c_str());

  return c; 
}
// function DrawTH1
//-----------------------------------------------------------------------------
//Drawing Layered Histograms
=======
  c.SaveAs((name+".png").c_str());
  c.SaveAs((name+".pdf").c_str());
}
// function DrawTH1
//-----------------------------------------------------------------------------
//Drawing multiple graphs on same canvas
>>>>>>> 32ad2897efb97a3dafc68a475693b99364c6cfa7
void DrawTH1(std::vector<TH1*> hists,std::vector<string> files, int color, std:: string const& name)
{
  int nHists = hists.size();
    
  TCanvas c("c", "c", 1600, 900);
  auto legend = new TLegend(0.6, 0.775, 0.78, 0.9); //(x1, y1, x2, y2) should  put in top right corner
  legend->SetHeader(name.c_str(), "C");

  for (size_t i=0; i < nHists; ++i){

	hists[i]->SetLineColor(color++);
	legend->AddEntry(hists[i],files[i].c_str(),"l"); 
		
	if (i==0){
		hists[i]->Draw();
		legend->Draw();
	} else {
		hists[i]->Draw("same");
		legend->Draw("same");
	}
  }

  c.SaveAs((name+".png").c_str());
  c.SaveAs((name+".pdf").c_str());
  // save the plot
} // function DrawTH1
//---------------------------------------------------------------------------
//Drawing Stacked Histograms
void DrawTHStack(std::vector<TH1*> hists, std::vector<string> files, int color, std:: string const& name)
{
   int nHists = hists.size();

   TCanvas c("c","c", 1600, 900);
   THStack *hs = new THStack("hs", "");
   auto legend = new TLegend(0.6,0.775, 0.78, 0.9);
   legend->SetHeader(name.c_str(), "C");
   
   for (size_t i=0; i < nHists; ++i){
	hists[i]->SetFillColor(color++);
	hs->Add(hists[i]);
	legend->AddEntry(hists[i], files[i].c_str(), "f");
   }

   hs->Draw();
   legend->Draw();

   c.SaveAs((name+".png").c_str());
   c.SaveAs((name+".pdf").c_str());
}
//----------------------------------------------------------------------------
//Drawing Ratio histograms
void DrawTHRatio(std::vector<TH1*> hists, int color, std:: string const& name)
{
   int nHists = hists.size();
  
   TCanvas c("c", "c", 1600, 900);

   for (size_t i=1; i < nHists; ++i){
     
	 hists[i]->SetLineColor(color++);

	if (i==0){
       		hists[i]->Draw();
	} else { 
		hists[i]->Draw("same");
		TH1* hRatio = (TH1*)hists[0]->Clone("hRatio");
		hRatio->Divide(hists[i]);
		hRatio->Draw();
	}		  
   }
   
   c.SaveAs((name+".png").c_str());
   c.SaveAs((name+".pdf").c_str());
}
//----------------------------------------------------------------------------
<<<<<<< HEAD
//Drawing Layered Ratio histograms
void DrawLayeredRatio(std::vector<TH1*> hists, int color, std:: string const& name)
{
   int nHists = hists.size();

   TCanvas c("c", "c", 1600, 900);
   auto legend = new TLegend(0.6, 0.775, 0.78, 0.9);

   for (size_t i=1; i < nHists; ++i){
	   hists[i]->SetLineColor(color++);

	   if (i==0){
		   hists[i]->Draw("same");
	   } else {
		   hists[i]->Draw("same");
	   }

   
   }
}
//----------------------------------------------------------------------------
=======
>>>>>>> 32ad2897efb97a3dafc68a475693b99364c6cfa7
//Drawing 2D hist
void DrawTH2(TH2* g, int color, std::string const& name)
{
  TCanvas c("c", "c", 1600, 900);
  g->SetLineColor(kBlack);
  g->SetFillColor(color);
  g->SetLineWidth(1);
  g->Draw("colz");
  c.SaveAs((name+".png").c_str());
  c.SaveAs((name+".pdf").c_str());
}
//-----------------------------------------------------------------------------
void LoadAndDrawTH1(TFile* f, std::string path, int color, std::string const& name)
{ 
  TH1F* h = LoadTH1(f, path); // calling LoadTH1
  DrawTH1(h, color, name); // calling DrawTH1
  
  delete h;
}
//-----------------------------------------------------------------------------
//Load and Draw 2D hist
void LoadAndDrawTH2(TFile* f, std::string path, int color, std::string const& name)
{
  TH2F* g = LoadTH2(f, path);

  DrawTH2(g, color, name);

  delete g;
}
//-----------------------------------------------------------------------------
void RecursivePlot(TDirectory* dir, std::string const& name="")
{
  // get keys in current directory
  TIter next(dir->GetListOfKeys());
  TKey* k;

  // add prefix if we're in a nested directory
  std::string prefix = name;
  if(!prefix.empty()) prefix += "_";

  // loop over keys
  while ((k = (TKey*)next())) {

    // tag that includes prefixes for nested subdirectories
    std::string tag = prefix + std::string(k->GetName());

    // cast this key as a directory and a histogram
    auto d = dynamic_cast<TDirectory*>(k->ReadObj());
    auto h = dynamic_cast<TH1*>(k->ReadObj());

    // if the key is a directory, call this function again inside
    if (d) RecursivePlot(d, tag);
    // if the key is a histogram, draw it!
    else if (h) DrawTH1(h, kOkabelto1, "plots/"+tag);
    // otherwise just print a warning
    else std::cout << "object " << k->GetName() << " is not a directory or 1D histogram, skipping..." << std::endl;

  } // for key

} // function RecursivePlot

