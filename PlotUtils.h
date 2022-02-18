#pragma once

#include "TCanvas.h"
#include "TH1.h"

#include "Okabelto.h"

//-----------------------------------------------------------------------------
void DrawTH1(TH1* h, int color, std::string const& name)
{
  TCanvas c("c", "c", 1600, 900);
  h->SetLineColor(kBlack);
  h->SetFillColor(color);
  h->SetLineWidth(1);
  h->Draw("hist");
  c.SaveAs((name+".png").c_str());
  c.SaveAs((name+".pdf").c_str());
} // function DrawTH1

//-----------------------------------------------------------------------------
void LoadAndDrawTH1(std::string path, int color, std::string const& name)
{
  // unimplemented
} // function LoadAndDrawTH1

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
