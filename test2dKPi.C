/*
 *  test2dKPi.C
 *  2012IFF
 *
 *  Created by Keith Landry on 6/15/15.
 *  UCLA
 *
 */




void test2dKPi(){


  TFile* infile = new TFile("./resDiHad_smallPbins_5_19/2Dcone03AsymsHiEta_5_19_smallPbins.root");

  
  TH1D* test_0 = infile->Get("hAut_PtMassbin_0_0");
  TH1D* test_1 = infile->Get("hAut_PtMassbin_1_0");
  TH1D* test_2 = infile->Get("hAut_PtMassbin_2_0");
  TH1D* test_3 = infile->Get("hAut_PtMassbin_3_0");
  
  
  
  test_0->Add(test_1, 1);
  test_0->Add(test_2, 1);
  test_0->Add(test_3, 1);

  
  test_0->Draw();
  
  
  TFile* infile2 = new TFile("./resDiHad_smallPbins_5_19/cone03AsymsHiEta_5_19_smallPbins.root");

  TH1D* test_1d = infile2->Get("hAut_Massbin_3");
  
  TCanvas* c2 = new TCanvas();
  
  test_1d ->Draw();

}