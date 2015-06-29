/*
 *  numberInRad.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/18/14.
 *  UCLA
 *
 */


void numberInRad(){

	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	gSystem->Load("pionPairTreeMaker");
	cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";

	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutTesting/E3199C90857D273F2C874251C5D9C1ED_010kTest_pionTree.root");

	
	
	int numberPassRad = 0;
	
	
	TTree* pairTree = infile->Get("pionPairTree");
	
	pionPair* pair1 = new pionPair();
	
	pairTree->SetBranchAddress("pionPair", "pionPair", &pair1);
	
	
	for (int i = 0; i < pairTree->GetEntries(); i++)
	{
		
		pairTree->GetEntry(i);
		
		
		if (pair1->withinRadius(0.05, 0.3))
		{
			numberInRad++;
		}
		
		
		
	}
	
	cout << numberInRad << endl;
	

}