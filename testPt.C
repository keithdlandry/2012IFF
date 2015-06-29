/*
 *  testPt.C
 *  2012IFF
 *
 *  Created by Keith Landry on 3/24/14.
 *  UCLA
 *
 */




void testPt(){
	
	
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;	
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;

	//TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_withoutAssert/wihtoutr13053027_69C03ACEBC1EC16349AB760AA5B4A048_0_pionTree.root");
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_3_21/sameSignTestr13053027_32204A082D445322FC7846EED8C2F0F9_0_pionTree.root");

	
	//SET UP TREE TO RECEIVE INPUT
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	
	pairTree->SetBranchAddress("pionPair", &pair1);
	
	cout << pairTree->GetEntries() << endl;

	
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		
			
		pairTree->GetEntry(iPair);
	

		cout << pair1->piPlus()->pt() << " " << pair1->piMinus()->pt() << " " << pair1->phiSR('y')<< endl;
		
		
	}		
	
	
	
}
	
