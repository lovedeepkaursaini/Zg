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
  
  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("run",1);
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


  TFile* file = TFile::Open(outputName, "RECREATE");
  TTree* MyNewTree = fChain->CloneTree(0);
  MyNewTree->Branch("processCode", &processCode, "processCode/I");
  MyNewTree->Branch("xsScale", &xsScale, "xsScale/F");


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
      if(phoEt->at(ipho)<150.)continue;
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
  
    MyNewTree->Fill();
  }
  MyNewTree->Write();
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
    
    TString outputName = "/eos/uscms/store/user/lovedeep/13TeVZg/";
    for(int ichar = 0; ichar != fileNames[i].Length() - 5; ++ichar)
      outputName += fileNames[i][ichar];
    outputName += "_skimmed_Zg_Jan5.root";
    skimZgamma t(path + "/" + fileNames[i]);
    t.Loop(outputName, xs[i], processes[i]);
  }
  
  return 0;
}

