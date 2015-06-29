/*
 *  testIntegration.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/28/14.
 *  UCLA
 *
 */



void testIntegration(){
	
	
	
	TFile* infile = new TFile("/Users/keithlandry/Desktop/testPtHist.root");

	TH1D * h = infile->Get("Pt");
	
	
	int bmin = 751;
	int bmax = bmin+1;
	
  double binval = 0;
	int numberOfPairs = 0;
	
	cout << "starting at bmin = " << bmin << "  bmax = " << bmax << endl;
	
	cout << (double)h->GetEntries()/9.0 << endl;
	
	for (int i=0; i < h->GetNbinsX()-bmin; i++)
	{
		bmax++;

		cout << " i = " << i << " bmax = " << bmax << endl;
		
		int integ = h->Integral(bmin,bmax);
		
		cout << bmax << "   " << integ << endl;
		
		binval += h->GetBinContent(bmax)*h->GetBinCenter(bmax);
		numberOfPairs += h->GetBinContent(bmax);

		if (integ > (double)h->GetEntries()/9.0)
		{
			cout << bmax << "   " << integ << endl;
			lastI = i;
			break;
		}
		
		if (bmax == 1000)
		{
			break;
		}
		
		
	}
	
	
	cout << "avg val of bin " << (double)binval/numberOfPairs << endl;
	
	cout << " Pt = " << h->GetBinCenter(bmax) << endl;
	
	
	
}


