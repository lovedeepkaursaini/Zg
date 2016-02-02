#define skimZgamma_cxx
#include "skimZgamma.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <TMath.h>
using namespace std;

void skimZgamma::Loop(TString outputName, float xsScale, int processCode)
{
  
  TH1F* hEvents = (TH1F*)gDirectory->Get("hEvents");
  float nEvents = hEvents->GetBinContent(1);
  
  //TH1F* hPU = (TH1F*)gDirectory->Get("hPU");
  //TH1F* hPUTrue = (TH1F*)gDirectory->Get("hPUTrue");

  // Get reference histogram
  
 // TFile* fpuData = TFile::Open("Pileup_Observed_69300.root", "READ");
 // TFile* fpuData_m5 = TFile::Open("Pileup_observed_69300_m5.root", "READ");
 // TFile* fpuData_p5 = TFile::Open("Pileup_observed_69300_p5.root", "READ");
 // TH1F* hDataPU_ = (TH1F*)fpuData->Get("pileup");
 // TH1F* hDataPU_m5 = (TH1F*)fpuData_m5->Get("pileup");
 // TH1F* hDataPU_p5 = (TH1F*)fpuData_p5->Get("pileup");
  // PU Reweighting 
 /* double npu_probs[101];
  double s = 0;
  vector<double> result(101);
  for(int npu = 0; npu < 101; ++npu)
    npu_probs[npu] = hPU->GetBinContent(npu+1)/hPU->GetEntries();
  for(int npu = 0; npu < 101; ++npu) {
    double npu_estimated = hDataPU_->GetBinContent(hDataPU_->GetXaxis()->FindBin(npu));
    if ( npu_probs[npu] != 0 ) result[npu] = npu_estimated / npu_probs[npu];
    else result[npu] = 0;
    s += npu_estimated;
  }
  for (int npu = 0; npu < 101; ++npu) {
    result[npu] /= s;
  }
  
  //+5%
  double s_p5 = 0;
  vector<double> result_p5(101);
  for(int npu = 0; npu < 101; ++npu) {
    double npu_estimated = hDataPU_p5->GetBinContent(hDataPU_p5->GetXaxis()->FindBin(npu));
    if ( npu_probs[npu] != 0 ) result_p5[npu] = npu_estimated / npu_probs[npu];
    else result_p5[npu] = 0;
    s_p5 += npu_estimated;
  }
  for (int npu = 0; npu < 101; ++npu) result_p5[npu] /= s_p5;
  
  //-5%
  double s_m5 = 0;
  vector<double> result_m5(101);
  for(int npu = 0; npu < 101; ++npu) {
    double npu_estimated = hDataPU_m5->GetBinContent(hDataPU_m5->GetXaxis()->FindBin(npu));
    if ( npu_probs[npu] != 0 ) result_m5[npu] = npu_estimated / npu_probs[npu];
    else result_m5[npu] = 0;
    s_m5 += npu_estimated;
  }
  for (int npu = 0; npu < 101; ++npu) result_m5[npu] /= s_m5;
  
  */
  fChain->SetBranchStatus("*",1);
  /*  fChain->SetBranchStatus("run",1);
      fChain->SetBranchStatus("event",1);
      fChain->SetBranchStatus("lumis",1);
      fChain->SetBranchStatus("isData",1);
      fChain->SetBranchStatus("HLT*",1);
      fChain->SetBranchStatus("rho*",1);
      fChain->SetBranchStatus("nVtx",1);
      fChain->SetBranchStatus("nTrksPV",1);
      fChain->SetBranchStatus("vt*",1);
      fChain->SetBranchStatus("nPho",1);
      fChain->SetBranchStatus("pho*",1);
      fChain->SetBranchStatus("nJet",1);
      fChain->SetBranchStatus("jet*",1);
      fChain->SetBranchStatus("nAK8*",1);
      fChain->SetBranchStatus("AK8*",1);
  */
  
  TFile* file = new TFile(outputName, "RECREATE");
  TTree* MyNewTree = fChain->CloneTree(0);
  MyNewTree->Branch("processCode", &processCode, "processCode/I");
  MyNewTree->Branch("xsScale", &xsScale, "xsScale/F");
 // float puWeight, totalWeight;
 // float puWeight_p5, totalWeight_p5;
 // float puWeight_m5, totalWeight_m5;
  // PLEASE CHECK THE LUMI NUMBER!
  float xsWeight = 2.26*xsScale/hEvents->GetBinContent(1);
  MyNewTree->Branch("xsWeight", &xsWeight, "xsWeight/F");
 // MyNewTree->Branch("puWeight", &puWeight, "puWeight/F");
 // MyNewTree->Branch("puWeight_m5", &puWeight_m5, "puWeight_m5/F");
 // MyNewTree->Branch("puWeight_p5", &puWeight_p5, "puWeight_p5/F");
 // MyNewTree->Branch("totalWeight", &totalWeight, "totalWeight/F");
 // MyNewTree->Branch("totalWeight_p5", &totalWeight_p5, "totalWeight_p5/F");
 // MyNewTree->Branch("totalWeight_m5", &totalWeight_m5, "totalWeight_m5/F");
  
  
  TH1F* hcount = new TH1F("hcount", "", 10, 1, 10);
  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  int selectedEvents = 0;
  int nTotalEvents = 0;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    ++nTotalEvents;

    //    if ( jentry%1000 == 0 && jentry != 0 )
    //    cout << "Processed " << nTotalEvents << " events, selected = " << selectedEvents
    //       << "\t" << (float)selectedEvents/nTotalEvents << " selection efficiency" << endl;
    if(jentry % 10000 == 0) cout << "Processed " << jentry
				 << " events out of " <<nentries<< endl;
    
    hcount->Fill(1);
    
    if(nPho<1)continue;
    hcount->Fill(3);
    
    
    vector <int> iphotons;
    for (int ipho = 0; ipho < nPho; ++ipho){
      if(phoEt->at(ipho)<100.)continue;
      double eta = (*phoSCEta)[ipho];
      if( fabs( eta )> 2.5) continue;
      if( 1.4442 < fabs( eta ) && fabs( eta )< 1.566) continue;
      
      iphotons.push_back(ipho);
    }
    if(iphotons.size()<1) continue;
    
    hcount->Fill(4);
    
    if(!(nJet>1 || nAK8Jet>1 ))continue;
    hcount->Fill(5);
    /*vector <int> ijets;
      for (int ijet = 0; ijet < nJet; ++ijet){
     if(jetPt->at(ijet)<30. )continue;
     if(fabs(jetEta->at(ijet))>2.5) continue;
     ijets.push_back(ijet);
     }
     if(ijets.size()<1) continue;
     hcount->Fill(6);
    */
    ++selectedEvents;
  /*  
    if ( processCode != 0 ) {
      puWeight = result[(*nPU)[1]];
      puWeight_p5 = result_p5[(*nPU)[1]];
      puWeight_m5 = result_m5[(*nPU)[1]];
      totalWeight = puWeight*xsWeight;
      totalWeight_p5 = puWeight_p5*xsWeight;
      totalWeight_m5 = puWeight_m5*xsWeight;
    } else {
      puWeight = 1.0;
      totalWeight = 1.0;
      puWeight_p5 = 1.0;
      totalWeight_p5 = 1.0;
      puWeight_m5 = 1.0;
      totalWeight_m5 = 1.0;
    }
*/
    MyNewTree->Fill();
  }
  MyNewTree->Write();
 // hPU->Write();
 // hPUTrue->Write();
  hEvents->Write();
  hcount->Write();
  file->Close();
}

int main(int argc, char* argv[]) {
  
  TString path = argv[1];
  TString listOfFiles = argv[2];
  
  std::vector<TString> fileNames;
  std::vector<double> nevents;
  std::vector<double> xs;
  std::vector<int> processes;

  TString fileName;
  double xSection;
  long nEvents;
  int processCode;
  // get files to skimmer
  ifstream InputStream(listOfFiles);
  while(!InputStream.eof()) {
    if ( !(InputStream >> fileName) ) break;
    if ( fileName[0] == '#' ) continue;
    if ( !(InputStream >> nEvents) ) break;
    if ( !(InputStream >> xSection) ) break;
    if ( !(InputStream >> processCode) ) break;
    
    fileNames.push_back(fileName);
    if ( nEvents != 1.0 ) {
      xs.push_back(xSection);
      nevents.push_back(nEvents);
      processes.push_back(processCode);
    } else {
      xs.push_back(1);
      nevents.push_back(1);
      processes.push_back(0);
    }
  }
  for(unsigned int i = 0; i != fileNames.size(); ++i) {
    
    cout << fileNames[i] << '\t' << xs[i] << '\t' << nevents[i] << '\t' << processes[i] << endl;
  TString outputName="SKIM/" ;//= "root://cmseos.fnal.gov//store/user/lovedeep/skimZg13TeV/";  
//    TString outputName = "/store/user/lovedeep/skimZg13TeV/";
//    TString outputName = "root://cmsxrootd.fnal.gov//store/user/lovedeep/skimZg13TeV/";
    for(int ichar = 0; ichar != fileNames[i].Length() - 5; ++ichar)
      outputName += fileNames[i][ichar];
    outputName += "_skimZg_Jan26.root";
    skimZgamma t(path + "/" + fileNames[i]);
    t.Loop(outputName, xs[i], processes[i]);
  }
  
  return 0;
}

