/*
 *  avgPtMass2d.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/6/15.
 *  UCLA
 *
 */

const int nPtBins    = 5;
const int nEtaBins   = 4;
const int nMassBins  = 5;
const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014

//const int nPtBins    = 8;

//double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0, 10, 12,14};
//double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 10, 12, 14, 50.0};  //Anselm used 1000.0 as last point

double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0};
double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 50.0};  //Anselm used 1000.0 as last point

double    massBinStart[nMassBins] = {0.0, 0.4, 0.6, 0.8, 1.0};
double    massBinEnd[nMassBins]   = {0.4, 0.6, 0.8, 1.0, 100.5};

double    etaBinStart[nEtaBins] = {-2,-0.5,0.0,0.5};
double    etaBinEnd[nEtaBins]   = {-0.5,0.0,0.5, 2};


void create2dNMbins(const int nBins, const int mBins, TH2D* hist[nBins][mBins], int histbinsX, double histminX, double histmaxX, int histbinsY, double histminY, double histmaxY, string name){
	
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		for (int jBin = 0; jBin < mBins; jBin++)
		{
			stringstream ss;
			ss << iBin;
			stringstream ss2;
			ss2 << jBin;
			string fullname = name + ss.str() + "_" + ss2.str();
			cout << fullname << endl;
			
			hist[iBin][jBin] = new TH2D(fullname.c_str(),fullname.c_str(),histbinsX,histminX,histmaxX,histbinsY,histminY,histmaxY);
			
			
		}
		
		
	}
}



void avgPtMass2d(){

  
  
  TH2D* hPtMass[nPtBins][nMassBins];
  TH2D* hPtMass_int[1][nMassBins];
  
  create2dNMbins(nPtBins, nMassBins, hPtMass, 500, ptBinStart[0], ptBinEnd[nPtBins-1], 1000, massBinStart[0], massBinEnd[nMassBins-1], "hPtMass_PtMassbin_");
//  create2dNMbins(nPtBins, 1, hPtMass_int, 500, ptBinStart[0], ptBinEnd[nPtBins-1], 1000, massBinStart[0], massBinEnd[nMassBins-1], "hPtMass_PtMassbin_int_");
  create2dNMbins(1, nMassBins, hPtMass_int, 500, ptBinStart[0], ptBinEnd[nPtBins-1], 1000, massBinStart[0], massBinEnd[nMassBins-1], "hPtMass_PtMassbin_int_");
  
  TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/2dbinning_3_26_15_HiEta_JP1JP2.root");

  
  
  for (int iPt = 0; iPt<nPtBins; iPt++)
  {
    for (int iMass = 0; iMass<nMassBins; iMass++)
    {
      
      string name = "hPtMass_PtMassbin_";
      
      stringstream ss;
			ss << iPt;
			stringstream ss2;
			ss2 << iMass;
			string fullname = name + ss.str() + "_" + ss2.str();
      
      cout << fullname << endl;
      
      
      TH2D* temp2d = (TH2D*)infile->Get(fullname.c_str());
      
      
      //cout << "2d hist entries " << temp2d->GetEntries() << endl;
      
      
     // temp2d->Draw("colz");
      
      hPtMass[iPt][iMass]->Add(temp2d, 1);
      
      cout << "2d hist entries " <<  hPtMass[iPt][iMass]->GetEntries() << endl;

      
      hPtMass_int[0][iMass]->Add(hPtMass[iMass][iPt], 1);
      
    }
    
  }
  
  /*
  TH1D* temp1d = (TH1D*)infile->Get("hAut_PtMassbin_3_3");
  
  cout << "1d hist entries " << temp1d->GetEntries() << endl;

  TCanvas* c = new TCanvas();
  temp1d->Draw();
  //*/
  
  
  for (int jPt = 0; jPt < nPtBins; jPt++)
  {
    
    //cout << hPtMass_int[jPt][0]->GetMean(1) << endl;
    //cout << hPtMass_int[jPt][0]->GetEntries() << endl;
    cout << hPtMass_int[0][jPt]->GetMean(1) << endl;
    cout << hPtMass_int[0][jPt]->GetEntries() << endl;

    
    
  }
  
  
  
  
  
  
  
  
  
  
  

  
  
  
  
  


}