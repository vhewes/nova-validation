// example.C by j hewes <jhewes15@fnal.gov>

#include "TFile.h"

#include "PlotUtils.h"

void example()
{
  // open the input file
  TFile* f = TFile::Open("valid.hist.root", "read");
<<<<<<< HEAD
 // TFile* b = TFile::Open("prod5.root", "read");
 // TFile* s = TFile::Open("prod5p1.root", "read");

  // draw example TH1s
  LoadAndDrawTH1(f, "validgenie/Enu", kOkabelto1, "enu");
=======
  TFile* b = TFile::Open("prod5.root", "read");
  TFile* s = TFile::Open("prod5p1.root", "read");

  // draw example TH1s
//  LoadAndDrawTH1(f, "validgenie/Enu", kOkabelto1, "plots/enu");
>>>>>>> 32ad2897efb97a3dafc68a475693b99364c6cfa7
//  LoadAndDrawTH1(f, "validgenie/numu/Enu", kOkabelto2, "plots/enunumu");
//  LoadAndDrawTH1(f, "validgenie/nue/Enu", kOkabelto3, "plots/enunue");

  // draw example TH2s
<<<<<<< HEAD
  LoadAndDrawTH2(f, "validgenie/Vxy", kOkabelto1, "plots/Vxy");

  // create and draw TH1 vector
  std::vector<TH1*> hists;
  hists.push_back(LoadTH1(f, "validgenie/Enu"));
  hists.push_back(LoadTH1(f, "validgenie/numu/Enu"));
  hists.push_back(LoadTH1(f, "validgenie/nue/Enu"));
  //DrawTH1(hists, kOkabelto1, "plots/enu_multi");

 // DrawTHStack(hists, kOkabelto1, "plots/enu_stacked");

  
  std::vector<TH1*> hists12;
  hists12.push_back(LoadTH1(f, "validgenie/Enu"));
  hists12.push_back(LoadTH1(f, "validgenie/numu/Enu"));

  std::vector<TH1*> hists13;
  hists13.push_back(LoadTH1(f, "validgenie/Enu"));
  hists13.push_back(LoadTH1(f, "validgenie/nue/Enu"));

  std::vector<TH1*> hists23;
  hists23.push_back(LoadTH1(f, "validgenie/numu/Enu"));
  hists23.push_back(LoadTH1(f, "validgenie/nue/Enu"));

  DrawTHRatio(hists12, kOkabelto4, "plots/enu_ratio_12");
  DrawTHRatio(hists13, kOkabelto5, "plots/enu_ratio_13");
  DrawTHRatio(hists23, kOkabelto6, "plots/enu_ratio_23");

  // recursively plot everything
 // RecursivePlot(s);
=======
//  LoadAndDrawTH2(f, "validgenie/Vxy", kOkabelto1, "plots/Vxy");

  // create and draw TH1 vector
//  std::vector<TH1*> hists;
//  hists.push_back(LoadTH1(f, "validgenie/Enu"));
//  hists.push_back(LoadTH1(f, "validgenie/numu/Enu"));
//  hists.push_back(LoadTH1(f, "validgenie/nue/Enu"));
//  DrawTH1(hists, kOkabelto1, "plots/enu_multi");

//  DrawTHStack(hists, kOkabelto1, "plots/enu_stacked");


//  std::vector<TH1*> hists12;
//  hists12.push_back(LoadTH1(f, "validgenie/Enu"));
//  hists12.push_back(LoadTH1(f, "validgenie/numu/Enu"));

//  std::vector<TH1*> hists13;
//  hists13.push_back(LoadTH1(f, "validgenie/Enu"));
//  hists13.push_back(LoadTH1(f, "validgenie/nue/Enu"));

//  std::vector<TH1*> hists23;
//  hists23.push_back(LoadTH1(f, "validgenie/numu/Enu"));
//  hists23.push_back(LoadTH1(f, "validgenie/nue/Enu"));

//  DrawTHRatio(hists12, kOkabelto4, "plots/enu_ratio_12");
//  DrawTHRatio(hists13, kOkabelto5, "plots/enu_ratio_13");
//  DrawTHRatio(hists23, kOkabelto6, "plots/enu_ratio_23");

  // recursively plot everything
  RecursivePlot(s);
>>>>>>> 32ad2897efb97a3dafc68a475693b99364c6cfa7

} // macro template

