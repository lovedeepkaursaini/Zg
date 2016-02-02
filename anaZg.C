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
  
  TFile* tmp = TFile::Open(("histZg_"+filenam+".root").c_str(), "RECREATE");
  TH1::SetDefaultSumw2();
  
  TH1F* hCounter=new TH1F("hCounter","hCounter",20,0.,20);

  TH1D* hpho_MVAEB=new TH1D("hpho_MVAEB","hpho_MVAEB",100,0,1);
  TH1D* hpho_MVAEE=new TH1D("hpho_MVAEE","hpho_MVAEE",100,0,1);
  TH1D*  hPt_pho =new TH1D("hPt_pho","hPt_pho", 40,180,580);

  TH1D*  hMass_fatJ =new TH1D("hMass_fatJ","hMass_fatJ", 50,20,220);
  TH1D*  hPt_fatJ =new TH1D("hPt_fatJ","hPt_fatJ", 50,50,550);
  TH1D*  hEta_fatJ =new TH1D("hEta_fatJ","hEta_fatJ", 50,-3.,3);
  TH1D*  hPhi_fatJ =new TH1D("hPhi_fatJ","hPhi_fatJ", 50,-3.5,3.5);
  TH1D*  hTau21_fatJ =new TH1D("hTau21_fatJ","hTau21_fatJ", 10,0,1);

  TH1D*  h1Pt_fatJ =new TH1D("h1Pt_fatJ","h1Pt_fatJ", 50,50,550);
  TH1D*  h1Eta_fatJ =new TH1D("h1Eta_fatJ","h1Eta_fatJ", 50,-3.,3);
  TH1D*  h1Phi_fatJ =new TH1D("h1Phi_fatJ","h1Phi_fatJ", 50,-3.5,3.5);
  TH1D*  h1Tau21_fatJ =new TH1D("h1Tau21_fatJ","h1Tau21_fatJ", 10,0,1);

  TH1D*  h1prdMass_fatJ =new TH1D("h1prdMass_fatJ","h1prdMass_fatJ", 50,20,220);
  TH1D*  h1Mass_fatJ =new TH1D("h1Mass_fatJ","h1Mass_fatJ", 50,20,220);
  TH1D*  h2Mass_fatJ =new TH1D("h2Mass_fatJ","h2Mass_fatJ", 50,20,220);
  TH1D*  h3Mass_fatJ =new TH1D("h3Mass_fatJ","h3Mass_fatJ", 50,20,220);
  TH1D*  h4Mass_fatJ =new TH1D("h4Mass_fatJ","h4Mass_fatJ", 50,20,220);
  TH1D*  hDSVBtag_fatJ=new TH1D("hDSVBtag_fatJ","hDSVBtag_fatJ",50,-1,1);
  TH1D*  hDPhi_fatZg=new TH1D("hDPhi_fatZg","hDPhi_fatZg",50,0,3.5);
  TH1D*  hCSV_sj0=new TH1D("hCSV_sj0","hCSV_sj0",50,0,1);
  TH1D*  hCSV_sj1=new TH1D("hCSV_sj1","hCSV_sj1",50,0,1);

  TH1D*  hMass_j1j2 =new TH1D("hMass_j1j2","hMass_j1j2", 50,20,220);
  TH1D*  h1Mass_j1j2 =new TH1D("h1Mass_j1j2","h1Mass_j1j2", 50,20,220);
  TH1D*  h2Mass_j1j2 =new TH1D("h2Mass_j1j2","h2Mass_j1j2", 50,20,220);
  TH1D*  hCSV_j1=new TH1D("hCSV_j1","hCSV_j1",50,0,1);
  TH1D*  hCSV_j2=new TH1D("hCSV_j2","hCSV_j2",50,0,1);
  TH1D*  hDPhi_resZg=new TH1D("hDPhi_resZg","hDPhi_resZg",50,0,3.5);

  TH1D*  hMass_fatZgamma =new TH1D("hMass_fatZgamma","hMass_fatZgamma", 47,300,5000);
  TH1D*  hMass_fatZbbgamma =new TH1D("hMass_fatZbbgamma","hMass_fatZbbgamma", 47,300,5000);
  TH1D*  hMass_fatZsjbsjbgamma =new TH1D("hMass_fatZsjbsjbgamma","hMass_fatZsjbsjbgamma", 47,300,5000);

  TH1D*  hMass_resZgamma =new TH1D("hMass_resZgamma","hMass_resZgamma", 47,300,5000);
  TH1D*  hMass_resZbbgamma =new TH1D("hMass_resZbbgamma","hMass_resZbbgamma", 47,300,5000);

  TH1D*  hMass_Zgamma =new TH1D("hMass_Zgamma","hMass_Zgamma", 50,0,2200);

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(jentry % 10000 == 0) cout << "Processed " << jentry
                                << " events out of " <<nentries<< endl;

    hCounter->Fill(1);
    // if(pho_Medium !=1) continue;
    //    if(fabs(pho_Eta)>1.4442)continue; //photon in EB only
    //https://twiki.cern.ch/twiki/bin/view/CMS/MultivariatePhotonIdentificationRun2
    if(fabs(pho_Eta)>2.4)continue; //photon in EB+EE only
    if(fabs(fatJ_Eta)>2.4)continue; //photon in EB+EE only
    bool phoId = false;
    if((fabs(pho_Eta)<1.4442))hpho_MVAEB->Fill(pho_MVA,wt);
    if((fabs(pho_Eta)>1.566))hpho_MVAEE->Fill(pho_MVA,wt);
    if((fabs(pho_Eta)<1.4442) && (pho_MVA> 0.374))phoId=true;
    else if((fabs(pho_Eta)>1.566) && (pho_MVA> 0.336))phoId=true;
    if(phoId==false )continue; //for 90% efficiency WP, the cut is > 0.374 for EB and >0.336 for EE
    TLorentzVector pho;
    pho.SetPtEtaPhiM(pho_Pt,pho_Eta,pho_Phi, 0);
    hCounter->Fill(2);
    hPt_pho->Fill(pho_Pt,wt);

    //fat jet
    TLorentzVector Z; //Z later on can be from fatZ or jet1+jet2
    int foundZ = 0;

    TLorentzVector fatZ;

    if (fatJ_prdMassCorr>0){ //it is -9 where there is no fat jet.   
      hMass_fatJ->Fill(fatJ_SDMassCorr,wt);
      hPt_fatJ->Fill(fatJ_Pt,wt);
      hEta_fatJ->Fill(fatJ_Eta,wt);
      hPhi_fatJ->Fill(fatJ_Phi,wt);
      hTau21_fatJ->Fill(fatJ_Tau21,wt);
      if (fatJ_SDMassCorr>70&&fatJ_SDMassCorr<110)
	{
	  h1Tau21_fatJ->Fill(fatJ_Tau21,wt);
	}
      if(fatJ_Tau21<0.5)
	{
	  h1Mass_fatJ->Fill(fatJ_SDMassCorr,wt);
	  h1prdMass_fatJ->Fill(fatJ_prdMassCorr,wt);
	  if(fatJ_Pt>200) h2Mass_fatJ->Fill(fatJ_SDMassCorr,wt);
	  if(fatJ_Pt>200 && fatJ_DSVBtag>0.5)h3Mass_fatJ->Fill(fatJ_SDMassCorr,wt);
	  if(fatJ_Pt>200 && SDSJ0_CSV>0.605 && SDSJ1_CSV>0.605)h4Mass_fatJ->Fill(fatJ_SDMassCorr,wt);
	}    
      fatZ.SetPtEtaPhiE(fatJ_Pt,fatJ_Eta,fatJ_Phi,fatJ_En);
      
      //      if(fatJ_Ztag==1){
      if(fatJ_Tau21<0.5 && fatJ_prdMassCorr>70&&fatJ_prdMassCorr<110){
	h1Pt_fatJ->Fill(fatJ_Pt,wt);
	h1Eta_fatJ->Fill(fatJ_Eta,wt);
	h1Phi_fatJ->Fill(fatJ_Phi,wt);
	hCounter->Fill(3);
	foundZ =1 ;
	Z = fatZ;
	hDSVBtag_fatJ->Fill(fatJ_DSVBtag,wt);
	float dphiZg =  acos(cos(fatJ_Phi-pho_Phi));
	hDPhi_fatZg->Fill(dphiZg,wt);
        //subjets
	hCSV_sj0->Fill(SDSJ0_CSV,wt);
	hCSV_sj1->Fill(SDSJ1_CSV,wt);
      }
    }
     
    //resolved jets
    /*    if (foundZ == 0){
      TLorentzVector jet1;
      jet1.SetPtEtaPhiE(J1_Pt,J1_Eta,J1_Phi,J1_En);
      TLorentzVector jet2;
      jet2.SetPtEtaPhiE(J2_Pt,J2_Eta,J2_Phi,J2_En);
      hMass_j1j2->Fill((jet1+jet2).M(),wt);
      if(J1_CSVBtag>0.605)h1Mass_j1j2->Fill((jet1+jet2).M());
      if(J1_CSVBtag>0.605 && J2_CSVBtag>0.605)h2Mass_j1j2->Fill((jet1+jet2).M());
      hCounter->Fill(4);
      if((jet1+jet2).M()<70 || (jet1+jet2).M()>110)continue;
      hCounter->Fill(5);
      foundZ = 2;
      Z = jet1+jet2;
      float dphiZg =  acos(cos(Z.Phi()-pho_Phi));
      hDPhi_resZg->Fill(dphiZg,wt);

      hCSV_j1->Fill(J1_CSVBtag,wt);
      hCSV_j2->Fill(J2_CSVBtag,wt);
      if(J1_CSVBtag>0.605 && J2_CSVBtag>0.605)hCounter->Fill(6);
      //https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation74X
    }
    */
    if(foundZ == 0) continue;
      hCounter->Fill(4);

    TLorentzVector zGamma;
    zGamma = Z+pho;
    
    if(foundZ ==1)
      {
	hCounter->Fill(5);
	hMass_Zgamma->Fill(zGamma.M(),wt);
	hMass_fatZgamma->Fill(zGamma.M(),wt);
	if(fatJ_DSVBtag>0.5)hMass_fatZbbgamma->Fill(zGamma.M(),wt);
	if(fatJ_DSVBtag>0.5)hCounter->Fill(6);
        if(SDSJ0_CSV>0.605 && SDSJ0_CSV>0.605 )hMass_fatZsjbsjbgamma->Fill(zGamma.M(),wt);
	if(SDSJ0_CSV>0.605 && SDSJ0_CSV>0.605 )hCounter->Fill(7);
	if(SDSJ0_CSV>0.89 && SDSJ0_CSV>0.89  )hCounter->Fill(8);
	if(SDSJ0_CSV>0.97 && SDSJ0_CSV>0.97 )hCounter->Fill(9);
      }
    /*  else if(foundZ ==2)
      {
	hMass_Zgamma->Fill(zGamma.M(),wt);
	hMass_resZgamma->Fill(zGamma.M(),wt);
	if(J1_CSVBtag>0.605 && J2_CSVBtag>0.605)hMass_resZbbgamma->Fill(zGamma.M(),wt);
	}*/
  }
  
  
  tmp->Write();
  tmp->Close();
}





