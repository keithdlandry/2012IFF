/*
 *  sinFittingTest.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/30/14.
 *  UCLA
 *
 */




void sinFittingTest(){


	double PI = 3.14159265359;
	int bins = 16;
	
	TH1D* hSin = new TH1D("hSin","hSin",bins,-PI,PI);
	
	
	TF1* func = new TF1("func","[0]*sin(x)",-PI*.5,PI*.5);
	
	
	
	

	double amp = 1.5;
	
	
	
	for (int i=0; i<bins; i++)
	{
		
		double binCenter = hSin->GetBinCenter(i+1);
		
		double val = amp*sin(binCenter);
		
		hSin->SetBinContent(i+1, val);
		
	}
		
	
	hSin->Draw();
	
	
	hSin->Fit("func", "R");



}