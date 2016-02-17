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
  
  ofstream File("RunCevents.txt");
  TFile* tmp = TFile::Open(("histZg_"+filenam+".root").c_str(), "RECREATE");
  TH1::SetDefaultSumw2();
  
  TH1F* hCounter=new TH1F("hCounter","hCounter",20,0.,20);
  TH1F* hCounterWt=new TH1F("hCounterWt","hCounterWt",20,0.,20);

  TH1D* hpho_MVAEB=new TH1D("hpho_MVAEB","hpho_MVAEB",100,-1,1);
  TH1D*  hPt_phoEB_pre =new TH1D("hPt_phoEB_pre","hPt_phoEB_pre", 100,0,2000);
  TH1D*  hEta_phoEB_pre =new TH1D("hEta_phoEB_pre","hEta_phoEB_pre", 30,-1.5,1.5);

  TH1D*  hPt_fatJ_pre =new TH1D("hPt_fatJ_pre","hPt_fatJ_pre", 100,0,2000);
  TH1D*  hEta_fatJ_pre =new TH1D("hEta_fatJ_pre","hEta_fatJ_pre", 50,-2.5,2.5);
  TH1D*  hPhi_fatJ_pre =new TH1D("hPhi_fatJ_pre","hPhi_fatJ_pre", 70,-3.5,3.5);
  TH1D*  hTau21_fatJ_pre =new TH1D("hTau21_fatJ_pre","hTau21_fatJ_pre", 20,0,1);
  TH1D*  hTau31_fatJ_pre =new TH1D("hTau31_fatJ_pre","hTau31_fatJ_pre", 20,0,1);
  TH1D*  hMass_fatJ_pre =new TH1D("hMass_fatJ_pre","hMass_fatJ_pre", 50,0,250);
  TH1D*  hMass_fatJ_tau_pre =new TH1D("hMass_fatJ_tau_pre","hMass_fatJ_tau_pre", 50,0,250);
  TH1D*  hMass_fatJ_2b_pre =new TH1D("hMass_fatJ_2b_pre","hMass_fatJ_2b_pre", 50,0,250);
  TH1D*  hMass_fatJ_bb_pre =new TH1D("hMass_fatJ_bb_pre","hMass_fatJ_bb_pre", 50,0,250);

  TH1D*  hDSVBtag_fatJ_pre=new TH1D("hDSVBtag_fatJ_pre","hDSVBtag_fatJ_pre",20,-1,1);
  TH1D*  hDPhi_Zg_pre=new TH1D("hDPhi_Zg_pre","hDPhi_Zg_pre",50,0,3.5);
  TH1D*  hDEta_Zg_pre=new TH1D("hDEta_Zg_pre","hDEta_Zg_pre",50,0,5.0);
  TH1D*  hdR_Zg_pre=new TH1D("hdR_Zg_pre","hdR_Zg_pre",50,0,5.0);
  TH1D*  hCTS_Zg_pre=new TH1D("hCTS_Zg_pre","hCTS_Zg_pre",20,0,1.0);
  TH1D*  hCSV_sj0_pre=new TH1D("hCSV_sj0_pre","hCSV_sj0_pre",10,0,1);
  TH1D*  hCSV_sj1_pre=new TH1D("hCSV_sj1_pre","hCSV_sj1_pre",10,0,1);
  TH1D*  hCSV_sjmin_pre=new TH1D("hCSV_sjmin_pre","hCSV_sjmin_pre",10,0,1);
  TH1D*  hMass_Zg_pre =new TH1D("hMass_Zg_pre","hMass_Zg_pre", 30,0,3000);
  TH1D*  hPt_Zg_pre =new TH1D("hPt_Zg_pre","hPt_Zg_pre", 15,0,1500);


  TH1D*  hTau21_fatJ_zm =new TH1D("hTau21_fatJ_zm","hTau21_fatJ_zm", 20,0,1);
  TH1D*  hDSVBtag_fatJ_zm=new TH1D("hDSVBtag_fatJ_zm","hDSVBtag_fatJ_zm",20,-1,1);
  TH1D*  hDSVBtag_fatJ_zm_pId=new TH1D("hDSVBtag_fatJ_zm_pId","hDSVBtag_fatJ_zm_pId",20,-1,1);
  TH1D*  hCSV_sjmin_zm=new TH1D("hCSV_sjmin_zm","hCSV_sjmin_zm",20,-1,1);
  TH1D*  hCSV_sjmin_zm_pId=new TH1D("hCSV_sjmin_zm_pId","hCSV_sjmin_zm_pId",20,-1,1);
  TH1D*  hMass_Zg_zm =new TH1D("hMass_Zg_zm","hMass_Zg_zm", 30,0,3000);
  TH1D*  hPt_Zg_zm =new TH1D("hPt_Zg_zm","hPt_Zg_zm", 15,0,1500);
  TH1D*  hMass_Zg_SRtau =new TH1D("hMass_Zg_SRtau","hMass_Zg_SRtau", 30,0,3000);
  TH1D*  hPt_Zg_SRtau =new TH1D("hPt_Zg_SRtau","hPt_Zg_SRtau", 15,0,1500);
  TH1D*  hMass_Zg_SR2b =new TH1D("hMass_Zg_SR2b","hMass_Zg_SR2b", 30,0,3000);
  TH1D*  hPt_Zg_SR2b =new TH1D("hPt_Zg_SR2b","hPt_Zg_SR2b", 15,0,1500);
  TH1D*  hMass_Zg_SRbb =new TH1D("hMass_Zg_SRbb","hMass_Zg_SRbb", 30,0,3000);
  TH1D*  hPt_Zg_SRbb =new TH1D("hPt_Zg_SRbb","hPt_Zg_SRbb", 15,0,1500);

  TH1D*  hDSVBtag_fatJ_zgm2=new TH1D("hDSVBtag_fatJ_zgm2","hDSVBtag_fatJ_zgm2",20,-1,1);
  TH1D*  hCSV_sjmin_zgm2=new TH1D("hCSV_sjmin_zgm2","hCSV_sjmin_zgm2",20,-1,1);
  TH1D*  hDSVBtag_fatJ_zgm7=new TH1D("hDSVBtag_fatJ_zgm7","hDSVBtag_fatJ_zgm7",20,-1,1);
  TH1D*  hCSV_sjmin_zgm7=new TH1D("hCSV_sjmin_zgm7","hCSV_sjmin_zgm7",10,0,1);
  TH1D*  hDSVBtag_fatJ_SBzgm7=new TH1D("hDSVBtag_fatJ_SBzgm7","hDSVBtag_fatJ_SBzgm7",20,-1,1);
  TH1D*  hCSV_sjmin_SBzgm7=new TH1D("hCSV_sjmin_SBzgm7","hCSV_sjmin_SBzgm7",10,0,1);

  TH1D*  hDSVBtag_fatJ_zgm2_pId=new TH1D("hDSVBtag_fatJ_zgm2_pId","hDSVBtag_fatJ_zgm2_pId",20,-1,1);
  TH1D*  hCSV_sjmin_zgm2_pId=new TH1D("hCSV_sjmin_zgm2_pId","hCSV_sjmin_zgm2_pId",20,-1,1);
  TH1D*  hDSVBtag_fatJ_zgm7_pId=new TH1D("hDSVBtag_fatJ_zgm7_pId","hDSVBtag_fatJ_zgm7_pId",20,-1,1);
  TH1D*  hCSV_sjmin_zgm7_pId=new TH1D("hCSV_sjmin_zgm7_pId","hCSV_sjmin_zgm7_pId",10,0,1);

  TH1D*  hMass_Zg_SB =new TH1D("hMass_Zg_SB","hMass_Zg_SB", 30,0,3000);
  TH1D*  hPt_Zg_SB =new TH1D("hPt_Zg_SB","hPt_Zg_SB", 15,0,1500);
  TH1D*  hMass_Zg_SBtau =new TH1D("hMass_Zg_SBtau","hMass_Zg_SBtau", 30,0,3000);
  TH1D*  hPt_Zg_SBtau =new TH1D("hPt_Zg_SBtau","hPt_Zg_SBtau", 15,0,1500);
  TH1D*  hMass_Zg_SB2b =new TH1D("hMass_Zg_SB2b","hMass_Zg_SB2b", 30,0,3000);
  TH1D*  hPt_Zg_SB2b =new TH1D("hPt_Zg_SB2b","hPt_Zg_SB2b", 15,0,1500);

  TH1D* hnumPU=new TH1D("hnumPU","hnumPU",50,0,50);
  TH1D* hnumPURW=new TH1D("hnumPURW","hnumPURW",50,0,50);

  TH1D* hdR_subjets=new TH1D("hdR_subjets","hdR_subjets",20,0,1.0);
  TH1D* hCorrFact=new TH1D("hCorrFact","JEC corrections",20,0.8,1.2);

  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(jentry % 10000 == 0) cout << "Processed " << jentry
                                << " events out of " <<nentries<< endl;

    //apply PU weights
    float wgt=1;
    if((filenam.find("Run2015") != string::npos) || (filenam.find("ggtree_mcM") != string::npos)) wgt =1;
    else wgt=wt*puWtp5;

    //check PU Rw
    hnumPU->Fill(n_Vtx);
    hnumPURW->Fill(n_Vtx,wgt);

    //photon+jet pre-selections
    if(fabs(pho_Eta)>1.4442)continue; //photon in EB only
    if(fabs(pho_Pt)<180.)continue;//pho pt>180
    if(fabs(fatJ_Eta)>2.0)continue; //jet, to avoid spillover to HF
    if(fatJ_Pt<200)continue; //fatjet pt
    if (fatJ_prdMassCorr<30)continue;//it is -9 where there is no fat jet.   
    if(!(fatJ_Id==1))continue;//tightLepVetoJetID

    //ele veto
    if(pho_EleVeto==0)continue;
    //phoID
    hpho_MVAEB->Fill(pho_MVA,wgt);
    if(pho_MVA< 0.374)continue;
    hCounter->Fill(1);
    hCounterWt->Fill(1,wt);
    TLorentzVector pho;
    pho.SetPtEtaPhiM(pho_Pt,pho_Eta,pho_Phi, 0);
    TLorentzVector fatJ;
    fatJ.SetPtEtaPhiE(fatJ_Pt,fatJ_Eta,fatJ_Phi,fatJ_En);
    //create fatJet+gamma candidates
    TLorentzVector zGamma;
    zGamma = fatJ+pho;

    //fill pre-selection level histos
    //photons
    hPt_phoEB_pre->Fill(pho_Pt,wgt);
    hEta_phoEB_pre->Fill(pho_Eta,wgt);
    //jets
    hMass_fatJ_pre->Fill(fatJ_prdMassCorr,wgt);
    hPt_fatJ_pre->Fill(fatJ_Pt,wgt);
    hEta_fatJ_pre->Fill(fatJ_Eta,wgt);
    hPhi_fatJ_pre->Fill(fatJ_Phi,wgt);
    hTau21_fatJ_pre->Fill(fatJ_Tau21,wgt);
    hTau31_fatJ_pre->Fill(fatJ_Tau31,wgt);
    if(fatJ_Tau21<0.5)hMass_fatJ_tau_pre->Fill(fatJ_prdMassCorr,wgt);
    if(fatJ_DSVBtag>0.4)hMass_fatJ_2b_pre->Fill(fatJ_prdMassCorr,wgt);
    if(SDSJ0_CSV>0.605 && SDSJ1_CSV>0.605)hMass_fatJ_bb_pre->Fill(fatJ_prdMassCorr,wgt);
    //CSVv2L 	0.605, CSVv2M 	0.89 
    //zgamma    
    hPt_Zg_pre->Fill(zGamma.Pt(),wgt);
    hMass_Zg_pre->Fill(zGamma.M(),wgt);
    //b-tag
    hDSVBtag_fatJ_pre->Fill(fatJ_DSVBtag,wgt);
    double min = SDSJ0_CSV;
    if(SDSJ0_CSV<SDSJ1_CSV)min = SDSJ0_CSV;
    else min = SDSJ1_CSV;
    hCSV_sjmin_pre->Fill(min,wgt);
    hCSV_sj0_pre->Fill(SDSJ0_CSV,wgt);
    hCSV_sj1_pre->Fill(SDSJ1_CSV,wgt);
    
    //get dPhi(jet,pho)
    float dphiZg =  acos(cos(fatJ_Phi-pho_Phi));
    hDPhi_Zg_pre->Fill(dphiZg,wgt);
    
    //get dEta(jet,pho)
    float detaZg =  fabs(fatJ_Eta-pho_Eta);
    hDEta_Zg_pre->Fill(detaZg,wgt);
    
    //get dR(jet,pho)
    float dRZg = fatJ.DeltaR(pho);
    hdR_Zg_pre->Fill(dRZg,wgt);

    //get cos theta star
    TLorentzVector boostedJet = fatJ;
    TLorentzVector boostedPho = pho;
    TLorentzVector sumVector = pho + fatJ;
    boostedPho.Boost(-(sumVector.BoostVector()));
    boostedJet.Boost(-(sumVector.BoostVector()));
    float cosThetaStar = std::abs(boostedPho.Pz()/boostedPho.P());
    hCTS_Zg_pre->Fill(cosThetaStar,wgt);
    if(cosThetaStar>0.6)continue;
	hCounter->Fill(2);
	hCounterWt->Fill(2,wgt);
    
    //Define SR
    
    if(fatJ_prdMassCorr>75&&fatJ_prdMassCorr<105)
      {
	hCounter->Fill(3);
	hCounterWt->Fill(3,wgt);
	hTau21_fatJ_zm->Fill(fatJ_Tau21,wgt);
	hDSVBtag_fatJ_zm->Fill(fatJ_DSVBtag,wgt);
	hCSV_sjmin_zm->Fill(min,wgt);
	hPt_Zg_zm->Fill(zGamma.Pt(),wgt);
	hMass_Zg_zm->Fill(zGamma.M(),wgt);
	if(filenam.find("ggtree_mcM") != string::npos)
	  {
	    if(abs(fatJ_partonId)==5)
	      {
		hDSVBtag_fatJ_zm_pId->Fill(fatJ_DSVBtag,wgt);
		hCSV_sjmin_zm_pId->Fill(min,wgt);
	      }
	  }
	if(zGamma.M()>1850 && zGamma.M()<2150) 
	  {
	    hDSVBtag_fatJ_zgm2->Fill(fatJ_DSVBtag,wgt);
	    hCSV_sjmin_zgm2->Fill(min,wgt);
	    if(filenam.find("ggtree_mcM") != string::npos)
	      {
		if(abs(fatJ_partonId)==5)
		  {
		    hDSVBtag_fatJ_zgm2_pId->Fill(fatJ_DSVBtag,wgt);
		    hCSV_sjmin_zgm2_pId->Fill(min,wgt);
		  }
	      }
	  }
	if(zGamma.M()>710 && zGamma.M()<790) 
	  {
	    hCounter->Fill(4);
	    hCounterWt->Fill(4,wgt);
	    hDSVBtag_fatJ_zgm7->Fill(fatJ_DSVBtag,wgt);
	    hCSV_sjmin_zgm7->Fill(min,wgt);
	    if(filenam.find("ggtree_mcM") != string::npos)
	      {
		if(abs(fatJ_partonId)==5)
		  {
		    hCounter->Fill(5);
		    hCounterWt->Fill(5,wgt);
		    hDSVBtag_fatJ_zgm7_pId->Fill(fatJ_DSVBtag,wgt);
		    hCSV_sjmin_zgm7_pId->Fill(min,wgt);
		  }
	      }
	  }
	
	if(fatJ_Tau21<0.5){
	  hCounter->Fill(6);
	  hCounterWt->Fill(6,wt);
	  hPt_Zg_SBtau->Fill(zGamma.Pt(),wgt);
	  hMass_Zg_SBtau->Fill(zGamma.M(),wgt);
	  double corrFact = fatJ_Pt/fatJ_rawPt;
	  hCorrFact->Fill(corrFact,wgt);
	  //  double corrPer = (fatJ_Pt-fatJ_rawPt)/fatJ_rawPt;
	  File<<run<<'\t'<<event<<'\t'<<pho_Pt<<'\t'<<fatJ_Pt<<'\t'<<
	    //fatJ_rawPt<<" ( corrFact: ) "<<corrFact<<corrPer<<
	    '\t'<<fatJ_prdMassCorr<<endl;
	}
	if(fatJ_DSVBtag>0.4)
	  {
	    hMass_Zg_SR2b->Fill(zGamma.M(),wgt);
	    hPt_Zg_SR2b->Fill(zGamma.Pt(),wgt);
	    hCounter->Fill(8);
	    hCounterWt->Fill(8,wt);
	    if(zGamma.M()>710 && zGamma.M()<790){
	    hCounter->Fill(9);
	    hCounterWt->Fill(9,wt);
	    }
	  }
	if(SDSJ0_CSV>0.605 && SDSJ1_CSV>0.605)
	  {
	    hMass_Zg_SRbb->Fill(zGamma.M(),wgt);
	    hPt_Zg_SRbb->Fill(zGamma.Pt(),wgt);
	    if(zGamma.M()>710 && zGamma.M()<790)
	      {
		hCounter->Fill(10);
		hCounterWt->Fill(10,wt);
	      }
	  }
	if(min>0.605)
	  {
	    if(zGamma.M()>710 && zGamma.M()<790)
	      {
		hCounter->Fill(11);
		hCounterWt->Fill(11,wt);
	      }
	  }
      }
    
    TLorentzVector SJ0;
    SJ0.SetPtEtaPhiE(SDSJ0_Pt,SDSJ0_Eta,SDSJ0_Phi,SDSJ0_En);
    TLorentzVector SJ1;
    SJ1.SetPtEtaPhiE(SDSJ1_Pt,SDSJ1_Eta,SDSJ1_Phi,SDSJ1_En);
    
    double dRsj = SJ0.DeltaR(SJ1);
    hdR_subjets->Fill(dRsj,wgt);
    
    if(fatJ_prdMassCorr>50&&fatJ_prdMassCorr<70)
      {
	    hCounter->Fill(14);
	    hCounterWt->Fill(14,wt);
	hMass_Zg_SB->Fill(zGamma.M(),wgt);
	hPt_Zg_SB->Fill(zGamma.Pt(),wgt);
	if(zGamma.M()>710 && zGamma.M()<790)
	  {
	    hCounter->Fill(15);
	    hCounterWt->Fill(15,wt);
	    hDSVBtag_fatJ_SBzgm7->Fill(fatJ_DSVBtag,wgt);
	    hCSV_sjmin_SBzgm7->Fill(min,wgt);
	    if(fatJ_DSVBtag>0.4)
	      {
		hCounter->Fill(16);
		hCounterWt->Fill(16,wt);
	      }
	  }
	if(fatJ_DSVBtag<0.4)
	  {
	    hMass_Zg_SB2b->Fill(zGamma.M(),wgt);
	    hPt_Zg_SB2b->Fill(zGamma.Pt(),wgt);
	  }
	if(fatJ_Tau21>0.5)
	  {
	    hMass_Zg_SBtau->Fill(zGamma.M(),wgt);
	    hPt_Zg_SBtau->Fill(zGamma.Pt(),wgt);
	  }
      }
  }
  tmp->Write();
  tmp->Close();
}







