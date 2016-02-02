{
   gROOT->ProcessLine(".L anaZg.C++");
   gROOT->ProcessLine("anaZg  data(\"MiniTree/minitree_SP_Run2015CD\",1)");
   gROOT->ProcessLine("data.Loop()");

   gROOT->ProcessLine("anaZg  DY(\"MiniTree/minitree_DYJetsToQQ_HT180_skimZg_Jan26\",2.26e3*1187/1.277790e+07)");
   gROOT->ProcessLine("DY.Loop()");
  
   gROOT->ProcessLine("anaZg  WJ(\"MiniTree/minitree_WJetsToQQ_HT-600ToInf_skimZg_Jan26\",2.26e3*95.14/1.008034e+06)");
   gROOT->ProcessLine("WJ.Loop()");

   gROOT->ProcessLine("anaZg  GJ1(\"MiniTree/minitree_GJets_HT-40To100_skimZg_Jan26\",2.26e3*20790/4.816232e+06)");
   gROOT->ProcessLine("GJ1.Loop()");

   gROOT->ProcessLine("anaZg  GJ2(\"MiniTree/minitree_GJets_HT-100To200_skimZg_Jan26\",2.26e3*9238/4.944252e+06)");
   gROOT->ProcessLine("GJ2.Loop()");

   gROOT->ProcessLine("anaZg  GJ3(\"MiniTree/minitree_GJets_HT-200To400_skimZg_Jan26\",2.26e3*2305/1.040519e+07)");
   gROOT->ProcessLine("GJ3.Loop()");

   gROOT->ProcessLine("anaZg  GJ4(\"MiniTree/minitree_GJets_HT-400To600_skimZg_Jan26\",2.26e3*274.4/2.476770e+06)");
   gROOT->ProcessLine("GJ4.Loop()");

   gROOT->ProcessLine("anaZg  GJ5(\"MiniTree/minitree_GJets_HT-600ToInf_skimZg_Jan26\",2.26e3*93.46/2.550765e+06)");
   gROOT->ProcessLine("GJ5.Loop()");

   gROOT->ProcessLine("anaZg  QCD1(\"MiniTree/minitree_QCD_HT200to300_skimZg_Jan26\",2.26e3*1712000/1.871890e+07)");
   gROOT->ProcessLine("QCD1.Loop()");

   gROOT->ProcessLine("anaZg  QCD2(\"MiniTree/minitree_QCD_HT300to500_skimZg_Jan26\",2.26e3*347700/1.982620e+07)");
   gROOT->ProcessLine("QCD2.Loop()");

   gROOT->ProcessLine("anaZg  QCD3(\"MiniTree/minitree_QCD_HT500to700_skimZg_Jan26\",2.26e3*32100/1.966416e+07)");
   gROOT->ProcessLine("QCD3.Loop()");

   gROOT->ProcessLine("anaZg  QCD4(\"MiniTree/minitree_QCD_HT700to1000_skimZg_Jan26\",2.26e3*6831/1.535225e+07)");
   gROOT->ProcessLine("QCD4.Loop()");

   gROOT->ProcessLine("anaZg  QCD5(\"MiniTree/minitree_QCD_HT1000to1500_skimZg_Jan26\",2.26e3*1207/4.955030e+06)");
   gROOT->ProcessLine("QCD5.Loop()");

   gROOT->ProcessLine("anaZg  QCD6(\"MiniTree/minitree_QCD_HT1500to2000_skimZg_Jan26\",2.26e3*119.9/3.865044e+06)");
   gROOT->ProcessLine("QCD6.Loop()");

   gROOT->ProcessLine("anaZg  QCD7(\"MiniTree/minitree_QCD_HT2000toInf_skimZg_Jan26\",2.26e3*25.24/1.912529e+06)");
   gROOT->ProcessLine("QCD7.Loop()");

   gROOT->ProcessLine("anaZg  m750(\"MiniTree/minitree_ggtree_mcM750GeV_skimZg_Jan26\",2)");
   gROOT->ProcessLine("m750.Loop()");

   gROOT->ProcessLine("anaZg  m2000(\"MiniTree/minitree_ggtree_mcM2TeV_skimZg_Jan26\",1)");
   gROOT->ProcessLine("m2000.Loop()");



}
