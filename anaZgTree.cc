#define anaZgTree_cxx
#include "anaZgTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include <TMath.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "SPRING15_25ns.cc"
#include <fstream>
#include <string>
using namespace std;
float pho_Pt;
float pho_Phi;
float pho_Eta;
float pho_SCEta;
int pho_HasPixelSeed ;
int pho_EleVeto ;
int pho_Loose;
int pho_Tight;
int pho_Medium;
float pho_MVA;
float fatJ_Pt;
float fatJ_Eta;
float fatJ_Phi;
float fatJ_En;
float fatJ_Mass;
float fatJ_SDMass;
float fatJ_SDMassCorr;
float fatJ_prdMass;
float fatJ_prdMassCorr;
float fatJ_Tau21;
int fatJ_Ztag;
float fatJ_DSVBtag;
float SDSJ0_Pt;
float SDSJ0_Eta;
float SDSJ0_Phi;
float SDSJ0_Mass;
float SDSJ0_En;
float SDSJ0_CSV;
float SDSJ1_Pt;
float SDSJ1_Eta;
float SDSJ1_Phi;
float SDSJ1_Mass;
float SDSJ1_En;
float SDSJ1_CSV;

float J1_Pt;
float J1_Eta;
float J1_Phi;
float J1_CSVBtag;
float J1_En;
float J2_Pt;
float J2_Eta;
float J2_Phi;
float J2_CSVBtag;
float J2_En;

void anaZgTree::clearVariables(){
  pho_Pt = -9;
  pho_Phi = -9;
  pho_Eta = -9;
  pho_SCEta = -9;
  pho_HasPixelSeed = -9;
  pho_EleVeto = -9;
  pho_Loose = 0;
  pho_Tight = 0;
  pho_Medium = 0;
  pho_MVA = -9;
  fatJ_Pt = -9; 
  fatJ_Eta = -9;
  fatJ_Phi = -9;
  fatJ_En = -9;
  fatJ_Mass = -9;
  fatJ_SDMass = -9;
  fatJ_SDMassCorr = -9;
  fatJ_prdMass = -9;
  fatJ_prdMassCorr = -9;
  fatJ_Tau21 = -9;
  fatJ_Ztag = 0;
  fatJ_DSVBtag = -9;
  SDSJ0_Pt = -9;
  SDSJ0_Eta = -9;
  SDSJ0_Phi = -9;
  SDSJ0_Mass = -9;
  SDSJ0_En = -9;
  SDSJ0_CSV = -9;
  SDSJ1_Pt = -9;
  SDSJ1_Eta = -9;
  SDSJ1_Phi = -9;
  SDSJ1_Mass = -9;
  SDSJ1_En = -9;
  SDSJ1_CSV = -9;

  J1_Pt = -9;
  J1_Eta = -9;
  J1_Phi = -9;
  J1_CSVBtag = -9;
  J1_En = -9;
  J2_Pt = -9;
  J2_Eta = -9;
  J2_Phi = -9;
  J2_CSVBtag = -9;
  J2_En = -9;
}


void anaZgTree::Loop(TString name)
{
  //
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  TFile* tmp = TFile::Open(name, "RECREATE");
  TH1::SetDefaultSumw2();
  TTree* miniTree = new TTree("miniTree", "miniTree");
  miniTree->Branch("event", &event);
  miniTree->Branch("run", &run);
  miniTree->Branch("pho_Pt", &pho_Pt, "pho_Pt/F");
  miniTree->Branch("pho_Eta", &pho_Eta, "pho_Eta/F");
  miniTree->Branch("pho_Phi", &pho_Phi, "pho_Phi/F");
  miniTree->Branch("pho_SCEta", &pho_SCEta, "pho_SCEta/F");
  miniTree->Branch("pho_HasPixelSeed",&pho_HasPixelSeed,"pho_HasPixelSeed/I");
  miniTree->Branch("pho_EleVeto",&pho_EleVeto,"pho_EleVeto/I");
  miniTree->Branch("pho_Loose",&pho_Loose,"pho_Loose/I");
  miniTree->Branch("pho_Tight",&pho_Tight,"pho_Tight/I");
  miniTree->Branch("pho_Medium",&pho_Medium,"pho_Medium/I");
  miniTree->Branch("pho_MVA", &pho_MVA, "pho_MVA/F");
  miniTree->Branch("fatJ_Pt", &fatJ_Pt, "fatJ_Pt/F");
  miniTree->Branch("fatJ_Eta", &fatJ_Eta, "fatJ_Eta/F");
  miniTree->Branch("fatJ_Phi", &fatJ_Phi, "fatJ_Phi/F");
  miniTree->Branch("fatJ_En", &fatJ_En, "fatJ_En/F");
  miniTree->Branch("fatJ_Mass", &fatJ_Mass, "fatJ_Mass/F");
  miniTree->Branch("fatJ_SDMass", &fatJ_SDMass, "fatJ_SDMass/F");
  miniTree->Branch("fatJ_SDMassCorr", &fatJ_SDMassCorr, "fatJ_SDMassCorr/F");
  miniTree->Branch("fatJ_prdMass", &fatJ_prdMass, "fatJ_prdMass/F");
  miniTree->Branch("fatJ_prdMassCorr", &fatJ_prdMassCorr, "fatJ_prdMassCorr/F");
  miniTree->Branch("fatJ_Tau21", &fatJ_Tau21, "fatJ_Tau21/F");
  miniTree->Branch("fatJ_Ztag", &fatJ_Ztag, "fatJ_Ztag/I");
  miniTree->Branch("fatJ_DSVBtag", &fatJ_DSVBtag, "fatJ_DSVBtag/F");
  miniTree->Branch("SDSJ0_Pt",&SDSJ0_Pt,"SDSJ0_Pt/F");
  miniTree->Branch("SDSJ0_Eta",&SDSJ0_Eta,"SDSJ0_Eta/F");
  miniTree->Branch("SDSJ0_Phi",&SDSJ0_Phi,"SDSJ0_Phi/F");
  miniTree->Branch("SDSJ0_Mass",&SDSJ0_Mass,"SDSJ0_Mass/F");
  miniTree->Branch("SDSJ0_En",&SDSJ0_En,"SDSJ0_En/F");
  miniTree->Branch("SDSJ0_CSV",&SDSJ0_CSV,"SDSJ0_CSV/F");
  miniTree->Branch("SDSJ1_Pt",&SDSJ1_Pt,"SDSJ1_Pt/F");
  miniTree->Branch("SDSJ1_Eta",&SDSJ1_Eta,"SDSJ1_Eta/F");
  miniTree->Branch("SDSJ1_Phi",&SDSJ1_Phi,"SDSJ1_Phi/F");
  miniTree->Branch("SDSJ1_Mass",&SDSJ1_Mass,"SDSJ1_Mass/F");
  miniTree->Branch("SDSJ1_En",&SDSJ1_En,"SDSJ1_En/F");
  miniTree->Branch("SDSJ1_CSV",&SDSJ1_CSV,"SDSJ1_CSV/F");

  miniTree->Branch("J1_Pt", &J1_Pt, "J1_Pt/F");
  miniTree->Branch("J1_Eta", &J1_Eta, "J1_Eta/F");
  miniTree->Branch("J1_Phi", &J1_Phi, "J1_Phi/F");
  miniTree->Branch("J1_CSVBtag", &J1_CSVBtag, "J1_CSVBtag/F");
  miniTree->Branch("J1_En", &J1_En, "J1_En/F");
  miniTree->Branch("J2_Pt", &J2_Pt, "J2_Pt/F");
  miniTree->Branch("J2_Eta", &J2_Eta, "J2_Eta/F");
  miniTree->Branch("J2_Phi", &J2_Phi, "J2_Phi/F");
  miniTree->Branch("J2_CSVBtag", &J2_CSVBtag, "J2_CSVBtag/F");
  miniTree->Branch("J2_En", &J2_En, "J2_En/F");


  TH1F* hCounter=new TH1F("hCounter","hCounter",20,0.,20);
  TH1D* hEvents_ = new TH1D("hEvents", "total processed", 2, 0, 2);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    hEvents_->Fill(1);
    if(jentry % 1000 == 0) cout << "Processed " << jentry
                                << " events out of " <<nentries<< endl;
    clearVariables();
    event = event;
    run = run;
    hCounter->Fill(0);
    if(!((HLTPho>>  7 & 1) == 1))continue;
    hCounter->Fill(1);
    if(nPho<1)continue;
    hCounter->Fill(2);
    vector <int> iphotons;
    for (int ipho = 0; ipho < nPho; ++ipho){
      // PRE-PHOTON SELECTION
      if((*phoEt)[ipho] < 190) continue;
      if( fabs((*phoSCEta)[ipho])>2.5) continue;
      if( fabs((*phoSCEta)[ipho])<1.566 && fabs((*phoSCEta)[ipho])>1.4442) continue;
      //if (!passPhotonID(ipho, 1)) continue;
      iphotons.push_back(ipho);
    }
    if(iphotons.size() < 1 ) continue;
    hCounter->Fill(3);
    
    TLorentzVector pho;
    int j = iphotons[0];
    pho.SetPtEtaPhiM((*phoEt)[j], (*phoEta)[j], (*phoPhi)[j], 0);
    
    pho_Pt = pho.Pt();
    pho_Eta = pho.Eta();
    pho_Phi = pho.Phi();
    pho_SCEta = phoSCEta->at(j);
    pho_HasPixelSeed = phohasPixelSeed->at(j);
    pho_EleVeto = phoEleVeto->at(j);
    pho_Loose = passPhotonID(j, 0);
    pho_Medium = passPhotonID(j, 1);
    pho_Tight = passPhotonID(j, 2);
    pho_MVA = phoIDMVA->at(j);

    //Fatjet
    vector <int> iak8jets;
    for (int ijet = 0; ijet < nAK8Jet; ++ijet){
     if(AK8JetPt->at(ijet)<50. )continue;
     if(fabs(AK8JetEta->at(ijet))>2.5) continue;
     if(AK8JetPFLooseId==false)continue;
     double drjetgamma = dR((*AK8JetEta)[ijet],(*AK8JetPhi)[ijet],pho.Eta(),pho.Phi());
     if(drjetgamma<0.5)continue;
     iak8jets.push_back(ijet);
    }
    
    if (iak8jets.size()>0)  {
      fatJ_Mass = AK8JetMass->at(iak8jets[0]);
      fatJ_SDMass = AK8CHSSoftDropJetMass->at(iak8jets[0]);
      fatJ_SDMassCorr = AK8CHSSoftDropJetMassCorr->at(iak8jets[0]);
      fatJ_prdMass = AK8CHSPrunedJetMass->at(iak8jets[0]);
      fatJ_prdMassCorr = AK8CHSPrunedJetMassCorr->at(iak8jets[0]);
      fatJ_Tau21 = AK8Jet_tau2->at(iak8jets[0])/AK8Jet_tau1->at(iak8jets[0]);
      if(fatJ_SDMass>70 && fatJ_SDMass<110 && fatJ_Tau21<0.5 )fatJ_Ztag = 1;
      fatJ_Pt = AK8JetPt->at(iak8jets[0]);
      fatJ_Eta = AK8JetEta->at(iak8jets[0]);
      fatJ_Phi = AK8JetPhi->at(iak8jets[0]);
      fatJ_En =  AK8JetEn->at(iak8jets[0]);
      fatJ_DSVBtag = AK8JetpfBoostedDSVBTag->at(iak8jets[0]);
      //cout<<"subjets: "<<nAK8softdropSubjet->at(iak8jets[0])<<endl;
      if(nAK8softdropSubjet->at(iak8jets[0])>1){
    //   cout<<"fJ mass: "<<fatJ_Mass<<", sujet pt: "<<(*AK8softdropSubjetPt)[iak8jets[0]][0]<<'\t'<<(*AK8softdropSubjetPt)[iak8jets[0]][1]<<endl;  
       //lead SJ
       SDSJ0_Pt = (*AK8softdropSubjetPt)[iak8jets[0]][0];
       SDSJ0_Eta = (*AK8softdropSubjetEta)[iak8jets[0]][0];
       SDSJ0_Phi = (*AK8softdropSubjetPhi)[iak8jets[0]][0];
       SDSJ0_Mass = (*AK8softdropSubjetMass)[iak8jets[0]][0];
       SDSJ0_En = (*AK8softdropSubjetE)[iak8jets[0]][0];
       SDSJ0_CSV = (*AK8softdropSubjetCSV)[iak8jets[0]][0];
       //sublead SJ
       SDSJ1_Pt = (*AK8softdropSubjetPt)[iak8jets[0]][1];
       SDSJ1_Eta = (*AK8softdropSubjetEta)[iak8jets[0]][1];
       SDSJ1_Phi = (*AK8softdropSubjetPhi)[iak8jets[0]][1];
       SDSJ1_Mass = (*AK8softdropSubjetMass)[iak8jets[0]][1];
       SDSJ1_En = (*AK8softdropSubjetE)[iak8jets[0]][1];
       SDSJ1_CSV = (*AK8softdropSubjetCSV)[iak8jets[0]][1];
      } 
    }    
    
    //resolved jets
    vector <int> ijets;
    for (int ijet = 0; ijet < nJet; ++ijet){
      if(jetPt->at(ijet)<30. )continue;
      if(fabs(jetEta->at(ijet))>2.5) continue;
      if(jetPFLooseId==false)continue;
      double drjetgamma = dR((*jetEta)[ijet],(*jetPhi)[ijet],pho.Eta(),pho.Phi());
      if(drjetgamma<0.5)continue;
      ijets.push_back(ijet);
    }
    if(ijets.size()<2) continue;
    hCounter->Fill(7);
    
    TLorentzVector jet1;
    int q1 = ijets[0];
    jet1.SetPtEtaPhiE((*jetPt)[q1], (*jetEta)[q1], (*jetPhi)[q1], (*jetEn)[q1]);
    
    TLorentzVector jet2;
    int q2 = ijets[1];
    jet2.SetPtEtaPhiE((*jetPt)[q2], (*jetEta)[q2], (*jetPhi)[q2], (*jetEn)[q2]);
    
    J1_Pt = (*jetPt)[q1];
    J1_Eta = (*jetEta)[q1];
    J1_Phi = (*jetPhi)[q1];
    J1_CSVBtag = (*jetpfCombinedInclusiveSecondaryVertexV2BJetTags)[q1];
    J1_En = (*jetEn)[q1];
    J2_Pt = (*jetPt)[q2];
    J2_Eta = (*jetEta)[q2];
    J2_Phi = (*jetPhi)[q2];
    J2_CSVBtag = (*jetpfCombinedInclusiveSecondaryVertexV2BJetTags)[q2];
    J2_En = (*jetEn)[q2];
    miniTree->Fill();
    
  }	
  miniTree->Write();
  hEvents_->Write();
  
  tmp->Write();
  tmp->Close();
}


int main(int argc, char* argv[]) {
  std::string fName = argv[1];
  
  anaZgTree t(fName);
  fName = fName.erase(0,5);
  cout<<fName<<endl;
  t.Loop("MiniTree/minitree_"+fName+".root");
  return 0;
}


