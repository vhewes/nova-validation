#pragma once

#include "TCanvas.h"
#include "TH2.h"
#include "TH1.h"
#include "TH2.h"

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

  // call Get to fetch from file, and check the pointer is not null
  // function LoadTH1

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
// Loading 2D histograms
TH2F* LoadTH2(TFile* f, std::string const& path)
{
  TH2F* g = (TH2F*)f->Get(path.c_str());
  if (!g){
	  std::cerr << path << "not found! exiting" << std::endl;
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
  c.SaveAs((name+".png").c_str());
  c.SaveAs((name+".pdf").c_str());
}
  // function DrawTH1

//----------------------------------------------------------------------------
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
void DrawTH2(TH2* g, int color, std::string const& name)
=======
//Load and Draw 1D hist
void LoadAndDrawTH1(TFile* f, std::string path, int color, std::string const& name)
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
void LoadAndDrawTH2(TFile* f, std::string path, int color, std::string const& name)
{
  TH2F* g = LoadTH2(f, path); 
  DrawTH2(g, color, name);

  delete g;
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

