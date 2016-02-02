//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  6 17:22:33 2016 by ROOT version 6.02/05
// from TTree miniTree/miniTree
// found on file: minitree_job_SinglePho_Run2015.root
//////////////////////////////////////////////////////////

#ifndef anaZg_h
#define anaZg_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
// Header file for the classes stored in the TTree if any.

class anaZg {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        event;
   Int_t           run;
   Float_t         pho_Pt;
   Float_t         pho_Eta;
   Float_t         pho_Phi;
   Float_t         pho_SCEta;
   Int_t           pho_HasPixelSeed;
   Int_t           pho_EleVeto;
   Int_t           pho_Loose;
   Int_t           pho_Tight;
   Int_t           pho_Medium;
   Float_t         pho_MVA;
   Float_t         fatJ_Pt;
   Float_t         fatJ_Eta;
   Float_t         fatJ_Phi;
   Float_t         fatJ_En;
   Float_t         fatJ_Mass;
   Float_t         fatJ_SDMass;
   Float_t         fatJ_SDMassCorr;
   Float_t         fatJ_prdMass;
   Float_t         fatJ_prdMassCorr;
   Float_t         fatJ_Tau21;
   Int_t           fatJ_Ztag;
   Float_t         fatJ_DSVBtag;
   Float_t         SDSJ0_Pt;
   Float_t         SDSJ0_Eta;
   Float_t         SDSJ0_Phi;
   Float_t         SDSJ0_Mass;
   Float_t         SDSJ0_En;
   Float_t         SDSJ0_CSV;
   Float_t         SDSJ1_Pt;
   Float_t         SDSJ1_Eta;
   Float_t         SDSJ1_Phi;
   Float_t         SDSJ1_Mass;
   Float_t         SDSJ1_En;
   Float_t         SDSJ1_CSV;
   Float_t         J1_Pt;
   Float_t         J1_Eta;
   Float_t         J1_Phi;
   Float_t         J1_CSVBtag;
   Float_t         J1_En;
   Float_t         J2_Pt;
   Float_t         J2_Eta;
   Float_t         J2_Phi;
   Float_t         J2_CSVBtag;
   Float_t         J2_En;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   TBranch        *b_pho_Pt;   //!
   TBranch        *b_pho_Eta;   //!
   TBranch        *b_pho_Phi;   //!
   TBranch        *b_pho_SCEta;   //!
   TBranch        *b_pho_HasPixelSeed;   //!
   TBranch        *b_pho_EleVeto;   //!
   TBranch        *b_pho_Loose;   //!
   TBranch        *b_pho_Tight;   //!
   TBranch        *b_pho_Medium;   //!
   TBranch        *b_pho_MVA;   //!
   TBranch        *b_fatJ_Pt;   //!
   TBranch        *b_fatJ_Eta;   //!
   TBranch        *b_fatJ_Phi;   //!
   TBranch        *b_fatJ_En;
   TBranch        *b_fatJ_SDMass;   //!
   TBranch        *b_fatJ_SDMassCorr;   //!
   TBranch        *b_fatJ_prdMass;   //!
   TBranch        *b_fatJ_prdMassCorr;   //!
   TBranch        *b_fatJ_Mass;   //!
   TBranch        *b_fatJ_Tau21;   //!
   TBranch        *b_fatJ_Ztag;   //!
   TBranch        *b_fatJ_DSVBtag;   //!
   TBranch        *b_SDSJ0_Pt;   //!
   TBranch        *b_SDSJ0_Eta;   //!
   TBranch        *b_SDSJ0_Phi;   //!
   TBranch        *b_SDSJ0_Mass;   //!
   TBranch        *b_SDSJ0_En;   //!
   TBranch        *b_SDSJ0_CSV;   //!
   TBranch        *b_SDSJ1_Pt;   //!
   TBranch        *b_SDSJ1_Eta;   //!
   TBranch        *b_SDSJ1_Phi;   //!
   TBranch        *b_SDSJ1_Mass;   //!
   TBranch        *b_SDSJ1_En;   //!
   TBranch        *b_SDSJ1_CSV;   //!
   TBranch        *b_J1_Pt;   //!
   TBranch        *b_J1_Eta;   //!
   TBranch        *b_J1_Phi;   //!
   TBranch        *b_J1_CSVBtag;   //!
   TBranch        *b_J1_En;   //!
   TBranch        *b_J2_Pt;   //!
   TBranch        *b_J2_Eta;   //!
   TBranch        *b_J2_Phi;   //!
   TBranch        *b_J2_CSVBtag;   //!
   TBranch        *b_J2_En;   //!

   anaZg(std::string filename_,double wt_,TTree *tree=0);
   std::string filenam;
   double wt;

   virtual ~anaZg();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef anaZg_cxx
anaZg::anaZg(std::string filenam_,double wt_,TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     std::string nam = filenam_+".root";
     std::cout<<nam<<std::endl;
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(nam.c_str());
      if (!f) {
         f = new TFile(nam.c_str());
      }
   tree = (TTree*)gDirectory->Get("miniTree");
   }
   Init(tree);
   wt  = wt_;
   filenam_ = filenam_.erase(0,9);
   filenam = filenam_;
}

anaZg::~anaZg()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t anaZg::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t anaZg::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void anaZg::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("pho_Pt", &pho_Pt, &b_pho_Pt);
   fChain->SetBranchAddress("pho_Eta", &pho_Eta, &b_pho_Eta);
   fChain->SetBranchAddress("pho_Phi", &pho_Phi, &b_pho_Phi);
   fChain->SetBranchAddress("pho_SCEta", &pho_SCEta, &b_pho_SCEta);
   fChain->SetBranchAddress("pho_HasPixelSeed", &pho_HasPixelSeed, &b_pho_HasPixelSeed);
   fChain->SetBranchAddress("pho_EleVeto", &pho_EleVeto, &b_pho_EleVeto);
   fChain->SetBranchAddress("pho_Loose", &pho_Loose, &b_pho_Loose);
   fChain->SetBranchAddress("pho_Tight", &pho_Tight, &b_pho_Tight);
   fChain->SetBranchAddress("pho_Medium", &pho_Medium, &b_pho_Medium);
   fChain->SetBranchAddress("pho_MVA", &pho_MVA, &b_pho_MVA);
   fChain->SetBranchAddress("fatJ_Pt", &fatJ_Pt, &b_fatJ_Pt);
   fChain->SetBranchAddress("fatJ_Eta", &fatJ_Eta, &b_fatJ_Eta);
   fChain->SetBranchAddress("fatJ_Phi", &fatJ_Phi, &b_fatJ_Phi);
   fChain->SetBranchAddress("fatJ_En", &fatJ_En, &b_fatJ_En);
   fChain->SetBranchAddress("fatJ_Mass", &fatJ_Mass, &b_fatJ_Mass);
   fChain->SetBranchAddress("fatJ_SDMass", &fatJ_SDMass, &b_fatJ_SDMass);
   fChain->SetBranchAddress("fatJ_SDMassCorr", &fatJ_SDMassCorr, &b_fatJ_SDMassCorr);
   fChain->SetBranchAddress("fatJ_prdMass", &fatJ_prdMass, &b_fatJ_prdMass);
   fChain->SetBranchAddress("fatJ_prdMassCorr", &fatJ_prdMassCorr, &b_fatJ_prdMassCorr);
   fChain->SetBranchAddress("fatJ_Tau21", &fatJ_Tau21, &b_fatJ_Tau21);
   fChain->SetBranchAddress("fatJ_Ztag", &fatJ_Ztag, &b_fatJ_Ztag);
   fChain->SetBranchAddress("fatJ_DSVBtag", &fatJ_DSVBtag, &b_fatJ_DSVBtag);
   fChain->SetBranchAddress("SDSJ0_Pt", &SDSJ0_Pt, &b_SDSJ0_Pt);
   fChain->SetBranchAddress("SDSJ0_Eta", &SDSJ0_Eta, &b_SDSJ0_Eta);
   fChain->SetBranchAddress("SDSJ0_Phi", &SDSJ0_Phi, &b_SDSJ0_Phi);
   fChain->SetBranchAddress("SDSJ0_Mass", &SDSJ0_Mass, &b_SDSJ0_Mass);
   fChain->SetBranchAddress("SDSJ0_En", &SDSJ0_En, &b_SDSJ0_En);
   fChain->SetBranchAddress("SDSJ0_CSV", &SDSJ0_CSV, &b_SDSJ0_CSV);
   fChain->SetBranchAddress("SDSJ1_Pt", &SDSJ1_Pt, &b_SDSJ1_Pt);
   fChain->SetBranchAddress("SDSJ1_Eta", &SDSJ1_Eta, &b_SDSJ1_Eta);
   fChain->SetBranchAddress("SDSJ1_Phi", &SDSJ1_Phi, &b_SDSJ1_Phi);
   fChain->SetBranchAddress("SDSJ1_Mass", &SDSJ1_Mass, &b_SDSJ1_Mass);
   fChain->SetBranchAddress("SDSJ1_En", &SDSJ1_En, &b_SDSJ1_En);
   fChain->SetBranchAddress("SDSJ1_CSV", &SDSJ1_CSV, &b_SDSJ1_CSV);
   fChain->SetBranchAddress("J1_Pt", &J1_Pt, &b_J1_Pt);
   fChain->SetBranchAddress("J1_Eta", &J1_Eta, &b_J1_Eta);
   fChain->SetBranchAddress("J1_Phi", &J1_Phi, &b_J1_Phi);
   fChain->SetBranchAddress("J1_CSVBtag", &J1_CSVBtag, &b_J1_CSVBtag);
   fChain->SetBranchAddress("J1_En", &J1_En, &b_J1_En);
   fChain->SetBranchAddress("J2_Pt", &J2_Pt, &b_J2_Pt);
   fChain->SetBranchAddress("J2_Eta", &J2_Eta, &b_J2_Eta);
   fChain->SetBranchAddress("J2_Phi", &J2_Phi, &b_J2_Phi);
   fChain->SetBranchAddress("J2_CSVBtag", &J2_CSVBtag, &b_J2_CSVBtag);
   fChain->SetBranchAddress("J2_En", &J2_En, &b_J2_En);
   Notify();
}

Bool_t anaZg::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void anaZg::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t anaZg::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef anaZg_cxx
