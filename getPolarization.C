/*
 *  getPolarization.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/1/15.
 *  UCLA
 *
 */




void getPolarization(){

	TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/cone03AsymsFullEta_3_26_15_JP1JP2.root");

  
  TH1D* hPol = new TH1D("hPol","hPol",25,0,1);
  
  
  
  
  for (int iEta = 0; iEta<6; iEta++)
  {
    for (int iPhiSR = 8; iPhiSR<24; iPhiSR++)
    {
      stringstream ssEta;
      stringstream ssPhi;
      
      ssEta << iEta;
      ssPhi << iPhiSR;
      
      string name = "hPolOfBin_Etabin_" + ssEta.str() + "_phiSRbin_" + ssPhi.str();
      
      cout << name << endl;
      TH1D* temp = (TH1D*)infile->Get(name.c_str());
      
      
      hPol->Add(temp, 1.0);

      
      
    }
  }
  
  
  hPol->Draw();
  
  TCanvas* c = new TCanvas();
  temp->Draw();
  

  TH1D* test = (TH1D*)infile->Get("hPolOfBin_Etabin_3_phiSRbin_11");
  TCanvas* c2 = new TCanvas();
  test->Draw();
  
  

}
