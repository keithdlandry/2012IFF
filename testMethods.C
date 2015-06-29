/*
 *  testMethods.C
 *  2012IFF
 *
 *  Created by Keith Landry on 1/22/14.
 *  UCLA
 *
 */



void testMethods(){

	double PI = 3.14159;
	const int nBins = 6;


	double baseUp = 200;
	double baseDwn = 173;

	double NUtot = nBins*baseUp;
	
	double NDtot = nBins*baseDwn;
	
	//double A = (NUtot-nBins*baseline)/6.0;
	
	double Aup = .3*baseUp;
	double Adwn = .3*baseDwn;
	
	
	cout << Aup << "   " << Adwn << endl;
	
	double binW = 2*PI/nBins;
	
	

	double binCenters[nBins];
	
	for (int i=0; i<nBins; i++)
	{
		
		binCenters[i] = -PI + (2*i+1)/2.0 * binW;
		
		//cout << binCenters[i] << endl;
	}


	
	TH1F* hNup  = new TH1F("hNup","hNup",6,-PI,PI);
	TH1F* hNdwn = new TH1F("hNdwn","hNdwn",6,-PI,PI);

	
	for (int iBin=1; iBin<=nBins; iBin++)
	{
		
		
		hNup->SetBinContent(iBin, baseUp + Aup*sin(binCenters[iBin-1]));
		hNdwn->SetBinContent(iBin, baseDwn - Adwn*sin(binCenters[iBin-1]));

		
		
	}
	
	hNup->GetYaxis()->SetRangeUser(110, 270);
	hNup->SetFillStyle(0);
	hNup->Draw();
	hNdwn->SetLineColor(2);
	hNdwn->SetFillStyle(0);
	hNdwn->Draw("same");

	//cout << hNup->Integral() << endl;
	
	
	TH1F* hAl  = new TH1F("hAl","hAl",6,-PI,PI);
	TH1F* hAs  = new TH1F("hAs","hAs",6,-PI,PI);

	for (int iBin=1; iBin<=nBins; iBin++)
	{
		
		double up  = hNup->GetBinContent(iBin);
		double dwn = hNdwn->GetBinContent(iBin);
		
		double Lup  = hNup->GetEntries();
		double Ldwn = hNdwn->GetEntries();
		
		hAl->SetBinContent(iBin, (up/Lup - dwn/Ldwn)/(up/Lup + dwn/Ldwn) );

		if (iBin <= nBins*0.5)
		{
			double upPi = hNup->GetBinContent(iBin+nBins*0.5);
		
			double dwnPi = hNdwn->GetBinContent(iBin+nBins*0.5);
		}
		else
		{
			double upPi = hNup->GetBinContent(iBin-nBins*0.5);
			
			double dwnPi = hNdwn->GetBinContent(iBin-nBins*0.5);
			
		}
		
		
		hAs->SetBinContent(iBin, (sqrt(up*dwnPi) - sqrt(upPi*dwn))/(sqrt(up*dwnPi) + sqrt(upPi*dwn)) );

		
		
	}
	
	TCanvas* cAl = new TCanvas();
	hAl->Draw();
	
	
	TCanvas* cAs = new TCanvas();
	hAs->Draw();
	

	
	
	


}




































