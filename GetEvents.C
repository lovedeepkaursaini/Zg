float GetEvents(TString fName)
{
  TFile *f=new TFile(fName,"READ");
  TH1F* hist = (TH1F*)f->Get("ggNtuplizer/hEvents");
  return hist->GetBinContent(1);
}
