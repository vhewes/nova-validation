#pragma once

#include "TCanvas.h"
#include "TH1.h"

void DrawTH1(TH1* h, int color, std::string name)
{
  TCanvas c("c", "c", 1600, 900);
  h->SetLineColor(kBlack);
  h->SetFillColor(color);
  h->SetLineWidth(1);
  h->Draw("hist");
  c.SaveAs((name+".png").c_str());
  c.SaveAs((name+".pdf").c_str());
}

void LoadAndDrawTH1(std::string path, int color, std::string name)
{
  // unimplemented
}

