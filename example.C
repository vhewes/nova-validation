// example.C by j hewes <jhewes15@fnal.gov>

#include "TFile.h"

#include "PlotUtils.h"

void example()
{
  // open the input file
  TFile* f = TFile::Open("valid.hist.root", "read");

  // draw example TH1s
  LoadAndDrawTH1(f, "validgenie/Enu", kOkabelto1, "plots/enu");
  LoadAndDrawTH1(f, "validgenie/numu/Enu", kOkabelto2, "plots/enunumu");
  LoadAndDrawTH1(f, "validgenie/nue/Enu", kOkabelto3, "plots/enunue");

  // draw example TH2s
  LoadAndDrawTH2(f, "validgenie/Vxy", kOkabelto1, "plots/Vxy");

  // create and draw TH1 vector
  std::vector<TH1*> hists;
  hists.push_back(LoadTH1(f, "validgenie/Enu"));
  hists.push_back(LoadTH1(f, "validgenie/numu/Enu"));
  hists.push_back(LoadTH1(f, "validgenie/nue/Enu"));
  DrawTH1(hists, kOkabelto1, "plots/enu_multi");

  DrawTHStack(hists, kOkabelto1, "plots/enu_stacked");
  
  // recursively plot everything
  // RecursivePlot(f);

} // macro template

