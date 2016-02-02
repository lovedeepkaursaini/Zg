#include <sstream>
#include <iomanip> 
#include <TMath.h>

int application()
{
  TString histname;
  MyHistoStacknosig("hpho_MVAEB","MVA EB","Events",true);
  MyHistoStacknosig("hpho_MVAEE","MVA EE","Events",true);
  MyHistoStacknosig("hPt_pho","p_{T}(#gamma)","Events",true);
  MyHistoStacknosig("hMass_fatJ","AK8 jet soft-drop mass (JEC applied)","Events",true);
  MyHistoStacknosig("hPt_fatJ","AK8 jet p_{T}","Events",true);
  MyHistoStacknosig("hEta_fatJ","AK8 jet #eta","Events",true);
  MyHistoStacknosig("hPhi_fatJ","AK8 jet #phi","Events",true);
  MyHistoStacknosig("hTau21_fatJ","AK8 jet #tau_{21}","Events",true);
  MyHistoStacknosig("h1Tau21_fatJ","AK8 jet #tau_{21} (SDmass:70-110)","Events",true);
  MyHistoStacknosig("h1Mass_fatJ","AK8 jet SD mass (#tau_{21}<0.5)","Events",true);
  MyHistoStacknosig("h1prdMass_fatJ","AK8 jet pruned mass (#tau_{21}<0.5)","Events",true);

  MyHistoStacknosig("h1Pt_fatJ","AK8 jet p_{T}","Events",true);
  MyHistoStacknosig("h1Eta_fatJ","AK8 jet #eta","Events",true);
  MyHistoStacknosig("h1Phi_fatJ","AK8 jet #phi","Events",true);
  MyHistoStacknosig("hDPhi_fatZg","#Delta#phi(fatJ,#gamma)","Events",true);

  MyHistoStacknosig("hDSVBtag_fatJ","AK8 jet Dble Btagger","Events",true);
  MyHistoStacknosig("h3Mass_fatJ","AK8 jet SD mass (#tau_{21}<0.5, Dbl Btag>0.5)","Events",true);
  MyHistoStacknosig("hMass_fatZgamma","fatZ+#gamma mass","Events",true);
  MyHistoStacknosig("hMass_fatZbbgamma","fatZ(2b)+#gamma mass","Events",true);
  MyHistoStacknosig("hMass_fatZsjbsjbgamma","fatZ(bb)+#gamma mass","Events",true);

  ////resolved jets
  MyHistoStacknosig("hMass_j1j2","j1+j2 AK4 mass","Events",true);
  MyHistoStacknosig("hCSV_j1","j1, CSV Btagger","Events",true);
  MyHistoStacknosig("hCSV_j2","j2, CSV Btagger","Events",true);
  MyHistoStacknosig("h1Mass_j1j2","j1+j2 AK4 mass (j1 CSVv2L)","Events",true);
  MyHistoStacknosig("h2Mass_j1j2","j1+j2 AK4 mass (j1,j2 CSVv2L)","Events",true);
  MyHistoStacknosig("hDPhi_resZg","#Delta#phi(j1+j2,#gamma)","Events",true);
  MyHistoStacknosig("hMass_resZgamma","resZ+#gamma mass","Events",true);
  MyHistoStacknosig("hMass_resZbbgamma","resZbb+#gamma mass","Events",true);

  MyHistoStacknosig("pT_photon_EE","pT_photon","Events",true);



}


TCanvas* MyHistoStacknosig(std::string histname,
			   std::string XTitle="p_{T}",std::string YTitle="Number of Events", bool log)
{
  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumi_13TeV  = "2.26 fb^{-1}"; // default is "19.7 fb^{-1}"
  int iPeriod = 4; int iPos =11;
 int W = 600;
  int H = 600;
 int H_ref = 600; 
  int W_ref = 600; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

 TCanvas* c1= new TCanvas(histname.c_str(),histname.c_str(),50,50,W,H); 
  TPad* pad1=new TPad("pad1","This is pad1",0.0,0.3,1.0,1.0);
  TPad* pad2=new TPad("pad2","This is pad2",0.0,0.0,1.0,0.3);
  if(log){
    pad1->SetLogy();
    }
   pad1->Draw();
  pad2->Draw();
  pad1->cd();
 // TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  // c1->SetTickx(0);
  // c1->SetTicky(0);

  TFile* WJ=new TFile ("histZg_minitree_WJetsToQQ_HT-600ToInf_skimZg_Jan26.root");
  TFile* ZJ=new TFile ("histZg_minitree_DYJetsToQQ_HT180_skimZg_Jan26.root");
  TFile* QCD=new TFile ("histZg_minitree_QCD.root");
  TFile* GJ=new TFile ("histZg_minitree_GJets.root");
  TFile* data=new TFile ("histZg_minitree_SP_Run2015CD.root");
  TFile* sig750=new TFile ("histZg_minitree_ggtree_mcM750GeV_skimZg_Jan26.root");
  TFile* sig2K=new TFile ("histZg_minitree_ggtree_mcM2TeV_skimZg_Jan26.root");

     
   TH1F *hdata=(TH1F*)data->Get(histname.c_str());
   TH1F *hGJ=(TH1F*)GJ->Get(histname.c_str());
   TH1F *hQCD=(TH1F*)QCD->Get(histname.c_str());
   TH1F *hZJ=(TH1F*)ZJ->Get(histname.c_str());
   TH1F *hWJ=(TH1F*)WJ->Get(histname.c_str());
   TH1F *hsig750=(TH1F*)sig750->Get(histname.c_str());
   TH1F *hsig2K=(TH1F*)sig2K->Get(histname.c_str());

   cout<<hdata->GetBinContent(1);

   TH1F* hadd=hGJ->Clone();
   hadd->Add(hQCD);
   hadd->Add(hZJ);
   hadd->Add(hWJ);

    THStack* hs=new THStack(histname.c_str(),histname.c_str());
    //  hsig->SetFillColor(kGreen+2);
    //   hsig->SetLineColor(kBlack);
    hGJ->SetLineColor(kBlack);
    hGJ->SetFillColor(kBlue);
    hQCD->SetLineColor(kBlack);
    hQCD->SetFillColor(kRed+2);
    hZJ->SetLineColor(kBlack);
    hZJ->SetFillColor(kOrange);
    hWJ->SetLineColor(kBlack);
    hWJ->SetFillColor(kGreen-5);

    hsig750->SetLineColor(kCyan);
    hsig750->Scale(1.5);
    hsig2K->SetLineColor(kMagenta);
    hsig2K->Scale(1.5);

    hs->Add(hZJ);
    hs->Add(hWJ);
    hs->Add(hQCD);
    hs->Add(hGJ);
   //hs->Add(hsigp2);
   hdata->GetXaxis()->SetNdivisions(6,5,0);
   hdata->GetYaxis()->SetTitle(YTitle.c_str());
   hdata->GetYaxis()->SetTitleFont(42);
   hdata->GetXaxis()->SetTitleFont(42);
   hdata->GetYaxis()->SetLabelFont(42);
   hdata->GetXaxis()->SetLabelFont(42);
   hdata->GetYaxis()->SetTitleOffset(1.2);
   hdata->GetYaxis()->SetTitleSize(0.06);
   hdata->GetXaxis()->SetTitleOffset(1.0);
   hdata->GetXaxis()->SetTitleSize(0.06);
   hdata->GetXaxis()->SetTitle(XTitle.c_str());
   hdata->GetXaxis()->SetLabelSize(0.05);
   hdata->GetYaxis()->SetLabelSize(0.05);
   //hdata->SetMaximum(1200.);
   hdata->SetMinimum(0.01);
   hdata->SetMaximum(11*TMath::Max(hdata->GetMaximum()+sqrt(hdata->GetMaximum()), hadd->GetBinContent(hadd->GetMaximumBin())));
   //  hdata->SetMaximum(1e6);
   //  hdata->SetMinimum(0.01);
  // hdata->GetYaxis()->SetRangeUser(0.5,40); // Clone one of the histograms
  //   hdata->GetXaxis()->SetRangeUser(40.,80.);
   hdata->Sumw2();
   hdata->Draw();
   hs->Draw("hist,same");
   hsig750->Draw("hist,same");
   hsig2K->Draw("hist,same");

   // hsigp2->Scale(MULT/hsigp2->Integral());
   // hsig->Scale(MULTlow/hsig->Integral());

   //hsig->Draw("same");
   //hdata->Sumw2();
   hdata->SetLineColor(1);
   hdata->SetMarkerStyle(20);
   hdata->Draw("e1same");

   leg = new TLegend(0.7214765,0.7112992,0.9848993,0.9352912,NULL,"brNDC"); //coordinates are fractions
   leg->SetBorderSize(0); 
   leg->SetFillStyle(0);
   leg->SetFillColor(0);
   leg->SetTextFont(42);
   leg->AddEntry(hdata,"Data"); 
   leg->AddEntry(hGJ,"G+Jets","f");  // "l" means line
   leg->AddEntry(hQCD,"QCD","f");  // "l" means line
   leg->AddEntry(hWJ,"W+Jets","f"); 
   leg->AddEntry(hZJ,"Z+Jets","f"); 
   leg->AddEntry(hsig750,"X(750GeV)","l"); 
   leg->AddEntry(hsig2K,"X(2TeV)","l"); 
  // use "f" for a box
   leg->Draw();

  CMS_lumi( pad1, iPeriod, iPos );
  pad1->Update();
  pad1->RedrawAxis();
  pad1->Draw();
  pad1->GetFrame()->Draw();pad1->Modified();


   //For Ratio plot

  pad1->RedrawAxis();
  pad1->Draw();
  pad1->Modified();
  pad2->cd();
  pad2->SetGrid();
  TH1F *rat = hdata->Clone(); 
  rat->SetName("Ratio"); // Clone one of the histograms
  // rat->GetXaxis()->SetLabelSize(0.0); // Clone one of the histograms
  rat->Divide(hadd);
  rat->GetYaxis()->SetRangeUser(0,2); // Clone one of the histograms
  rat->GetYaxis()->SetTitle("data/MC"); // Clone one of the histograms
  rat->GetYaxis()->SetTitleOffset(0.5); // Clone one of the histograms
  rat->GetYaxis()->SetTitleSize(0.08); // Clone one of the histograms
  rat->GetYaxis()->SetLabelSize(0.08); // Clone one of the histograms
  rat->GetXaxis()->SetTitleSize(0.0); // Clone one of the histograms
  rat->GetXaxis()->SetLabelSize(0.0); // Clone one of the histograms
  rat->Draw("p");


  pad2->Draw();
  //histnamep=histname+".png";
  histnamee="png/"+histname+".eps";
  histnameg="png/"+histname+".png";
  // c1->SaveAs(histnamee.c_str());
  //c1->SaveAs(histnamep.c_str());
  c1->SaveAs(histnameg.c_str());
  //c1->Update();
}

