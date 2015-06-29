/*
 *  testFit.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/28/14.
 *  UCLA
 *
 */



void testFit(){


	TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/resultsNew_4_22/pairsFrom4_2Fullrange.root");

	
	TH1D* hEB3 = infile->Get("hAut_Etabin_3");
	
	
	
	double binVal[16];
	double binErr[16];
	double binCen[16];
	
	
	for (int i=1; i<=16; i++)
	{
		binVal[i-1] = hEB3->GetBinContent(i);
		binErr[i-1] = hEB3->GetBinError(i);
		
		binCen[i-1] = hEB3->GetBinCenter(i);
	}
	
	
	TGraphErrors* g1 = new TGraphErrors(16,binCen,binVal,0,binErr);
	
	g1->Draw("AP");
	
	
	

}