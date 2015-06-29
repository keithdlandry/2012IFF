/*
 *  drawNSigmaToFplots.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/24/15.
 *  UCLA
 *
 */




void drawNSigmaToFplots(){

  //gStyle->SetPalette(1);
  
//  TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/allK.root");
  TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/dihadron/rootFiles/kaons2.root");
  
  const int nPbins = 11;
  
  
  TH2D* hTofNsigPi[nPbins];
  TH2D* hTofNsigKa[nPbins];
  
  TCanvas* cPi = new TCanvas();
  cPi->Divide(4, 3);
  
  TCanvas* cKa = new TCanvas();
  cKa->Divide(4, 3);

  
  for (int iP = 0; iP < nPbins; iP++)
  {
    
    char namePi[50];
    sprintf(namePi, "hTofNsigPi_pBin_%d", iP);

    char nameKa[50];
    sprintf(nameKa, "hTofNsigKa_pBin_%d", iP);
    
    hTofNsigPi[iP] = (TH2D*)infile->Get(namePi);
    hTofNsigKa[iP] = (TH2D*)infile->Get(nameKa);
    
    
    
    cPi->cd(iP+1);
    hTofNsigPi[iP]->Draw("COLZ");
    
    cKa->cd(iP+1);
    hTofNsigKa[iP]->Draw("COLZ");

    
    
    
  }
  
  

  
  



}