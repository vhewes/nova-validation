// example.C by j hewes <jhewes15@fnal.gov>

#include "TFile.h"

#include "PlotUtils.h"

void example()
{
  // open the input file
  TFile* f = TFile::Open("valid.hist.root", "read");

   //the Get function returns a TObject pointer, so we have to cast it
   //to the type it actually is
  TH1F* hEnu = (TH1F*)f->Get("validgenie/Enu");
  if (!hEnu) {
    std::cerr << "hEnu not found! exiting" << std::endl;
    exit(1);
  }
  TH1F* hEnuNumu = (TH1F*)f->Get("validgenie/numu/Enu");
  if (!hEnuNumu) {
    std::cerr << "hEnuNumu not found! exiting" << std::endl;
    exit(1);
  }

  // draw the histograms in different configurations, and save images
  //DrawTH1(hEnu, kOkabelto1, "plots/enu");
  //DrawTH1(hEnuNumu, kOkabelto2, "plots/enunumu");

  LoadAndDrawTH1(f, "validgenie/Enu", kOkabelto1, "plots/enu");
  LoadAndDrawTH1(f, "validgenie/numu/Enu", kOkabelto2, "plots/enunumu");

  // recursively plot everything
  // RecursivePlot(f);

} // macro template
