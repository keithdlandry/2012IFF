/*
 *  addPolarizationHists.C
 *  2012IFF
 *
 *  Created by Keith Landry on 6/30/14.
 *  UCLA
 *
 */



void addPolarizationHists(){
	
	
	

	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/results_5_19/5_19Full.root");
	
	
	TH1D* polHist = new TH1D("polHist","polHist",25,0,1);
	
	
	
	for (int i=0; i<5; i++)
	{
		for (int j=0; j<32; j++)
		{
			
			char name[50];
			sprintf(name, "hPolOfBin_Ptbin_%d_phiSRbin_%d",i,j);
			
			cout << name << endl;
			
			TH1D* tempHist = infile->Get(name);
			
			cout << tempHist->GetEntries() << endl;
			
			polHist->Add(tempHist, 1);
			
			
		}
	}
	
	
	
	polHist->Draw();
	
	
	
	
	
	
}
