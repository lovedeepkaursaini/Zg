const int    photonID_IsConv[2][3]                = { {0, 0, 0} ,             {0, 0, 0}             };
const double photonID_HoverE[2][3]                = { {0.05, 0.05, 0.05} ,    {0.05, 0.05, 0.05}    };
const double photonID_SigmaIEtaIEta[2][3]         = { {0.0102, 0.0102, 0.0100} , {0.0274,0.0268,0.0268} };
const double photonID_RhoCorrR03ChHadIso[2][3]    = { {3.32,1.37,0.76} ,       {1.97,1.10,0.56}       };
const double photonID_RhoCorrR03NeuHadIso_0[2][3] = { {1.92,1.06,0.97} ,       {11.86,2.69,2.09}       };
const double photonID_RhoCorrR03NeuHadIso_1[2][3] = { {0.014, 0.014, 0.014} ,    {0.0139, 0.0139, 0.0139}    };
const double photonID_RhoCorrR03NeuHadIso_2[2][3] = { {0.000019,0.000019,0.000019} ,    {0.000025,0.000025,0.000025}    };

const double photonID_RhoCorrR03PhoIso_0[2][3]    = { {0.81,0.28,0.08} ,       {0.83,0.39,0.16}       };
const double photonID_RhoCorrR03PhoIso_1[2][3]    = { {0.0053, 0.0053, 0.0053} , {0.0034, 0.0034, 0.0034} };

double anaZgTree::dR(double eta1, double phi1, double eta2, double phi2) {
  double dphi = acos(cos(phi1 - phi2));
  double deta = eta1 - eta2;
  return sqrt(dphi*dphi + deta*deta);
}

bool anaZgTree::fidEtaPass(double Eta){

  double fabsEta = TMath::Abs(Eta);
  if( fabsEta > 2.5) return false;
  if( 1.4442 < fabsEta && fabsEta < 1.566) return false;
  return true;
}

int anaZgTree::phoRegion(double absEta){
  int region = 0;
  if( absEta >= 1.0  ) region++;
  if( absEta >= 1.479) region++;
  if( absEta >= 2.0  ) region++;
  if( absEta >= 2.2  ) region++;
  if( absEta >= 2.3  ) region++;
  if( absEta >= 2.4  ) region++;
  return region;
}
//https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2#SPRING15_selections_bunch_crossi
//// Selection implementation details for SPRING15 
double anaZgTree::phoEffArea03ChHad(double phoEta){
  double eta = TMath::Abs(phoEta);
  static const double area[7] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
  return area[phoRegion(eta)];
}

double anaZgTree::phoEffArea03NeuHad(double phoEta){
  double eta = TMath::Abs(phoEta);
  static const double area[7] = {0.0599,0.0819,0.0696,0.0360,0.0360,0.0462,0.0656};
  return area[phoRegion(eta)];
}

double anaZgTree::phoEffArea03Pho(double phoEta){
  double eta = TMath::Abs(phoEta);
  static const double area[7] = {0.1271,0.1101,0.0756,0.1175,0.1498,0.1857,0.2183};
  return area[phoRegion(eta)];
}

bool anaZgTree::passPhotonID(int phoInd, int pho_ID_ind = 0) {
//cout<<phoInd<<endl;
  // phoInd - index of the photon in the tree
  // pho_ID_ind: 0 -- loose, 1 -- medium, 2 -- tight
  double eta = (*phoSCEta)[phoInd];
  double et = (*phoEt)[phoInd];
  
  // rho corrected isolations
  double Pho03ChHadIso =     (*phoPFChIso)[phoInd]   - rho * phoEffArea03ChHad(eta);
  double Pho03NeuHadIso =    (*phoPFNeuIso)[phoInd]  - rho * phoEffArea03NeuHad(eta);
  double Pho03PhoIso =       (*phoPFPhoIso)[phoInd]  - rho * phoEffArea03Pho(eta);
  
  
  int region = 1; //barrel
  if(TMath::Abs( eta )< 1.4442) region = 0; //endcap
  bool phoPresel = fidEtaPass( eta ) &&
     et > 15 && //  Et cut
     ((*phoHoverE)[phoInd] < photonID_HoverE[region][pho_ID_ind]) &&
     ((*phoSigmaIEtaIEta)[phoInd]<photonID_SigmaIEtaIEta[region][pho_ID_ind]) &&
     (Pho03NeuHadIso < (photonID_RhoCorrR03NeuHadIso_0[region][pho_ID_ind] + photonID_RhoCorrR03NeuHadIso_1[region][pho_ID_ind] * et + (photonID_RhoCorrR03NeuHadIso_2[region][pho_ID_ind]*et*et))) &&
     (Pho03PhoIso < (photonID_RhoCorrR03PhoIso_0[region][pho_ID_ind] + et * photonID_RhoCorrR03PhoIso_1[region][pho_ID_ind])) && 
     (Pho03ChHadIso < photonID_RhoCorrR03ChHadIso[region][pho_ID_ind])   ;
 /*cout<<" phoSCEta: "<< eta
<<", phoEt: "<<et
<<"phoEleVeto: "<<(*phoEleVeto)[phoInd]  
<<", phoHoverE12: "<<(*phoHoverE12)[phoInd]
<<", Pho03NeuHadIso: "<<Pho03NeuHadIso
<<", Pho03PhoIso: "<<Pho03PhoIso
<<endl;
*/
  return phoPresel;
}
