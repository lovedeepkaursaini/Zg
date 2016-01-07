#define anaZg_cxx
#include "anaZg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TFile.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include <TMath.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

void anaZg::Loop()
{
  if (fChain == 0) return;
  
  TFile* tmp = TFile::Open("histZgamma.root", "RECREATE");
  TH1::SetDefaultSumw2();
  
  TH1F* hCounter=new TH1F("hCounter","hCounter",20,0.,20);
  TH1D*  hMass_Zgamma =new TH1D("hMass_Zgamma","hMass_Zgamma", 50,200,2200);
  TH1D*  hMass_fatZgamma =new TH1D("hMass_fatZgamma","hMass_fatZgamma", 50,200,2200);
  TH1D*  hMass_resZgamma =new TH1D("hMass_resZgamma","hMass_resZgamma", 50,200,2200);
  TH1D*  hMass_j1j2 =new TH1D("hMass_j1j2","hMass_j1j2", 50,20,220);
  TH1D*  hMass_fatJ =new TH1D("hMass_fatJ","hMass_fatJ", 50,20,220);

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    hCounter->Fill(1);
    if(pho_Medium !=1) continue;
    TLorentzVector pho;
    pho.SetPtEtaPhiM(pho_Pt,pho_Eta,pho_Phi, 0);
    hCounter->Fill(2);
    
    //fat jet
    TLorentzVector Z;
    int foundZ = 0;

    TLorentzVector fatZ;
    TLorentzVector fatZgamma;

    if (fatJ_SDMass>0){ //it is -9 where there is no fat jet.   
      hMass_fatJ->Fill(fatJ_SDMass);
      fatZ.SetPtEtaPhiM(fatJ_Pt,fatJ_Eta,fatJ_Phi,fatJ_SDMass);
      if(fatJ_Ztag==1){
	hCounter->Fill(3);
	foundZ =1 ;
	Z = fatZ;
      }
    }
    
    //resolved jets
    if (foundZ == 0){
      TLorentzVector jet1;
      jet1.SetPtEtaPhiE(J1_Pt,J1_Eta,J1_Phi,J1_En);
      TLorentzVector jet2;
      jet2.SetPtEtaPhiE(J2_Pt,J2_Eta,J2_Phi,J2_En);
      hMass_j1j2->Fill((jet1+jet2).M());
      hCounter->Fill(4);
      if((jet1+jet2).M()<70 || (jet1+jet2).M()>110)continue;
      hCounter->Fill(5);
      foundZ = 2;
      Z = jet1+jet2;
    }

    if(foundZ == 0) continue;
    TLorentzVector zGamma;
    zGamma = Z+pho;
    if(foundZ ==1)
      hMass_fatZgamma->Fill(zGamma.M());
    else if(foundZ ==2)
      hMass_resZgamma->Fill(zGamma.M());
    hMass_Zgamma->Fill(zGamma.M());
  }
  
  
  tmp->Write();
  tmp->Close();
}





