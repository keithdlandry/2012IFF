/*
 *  ptOfPairs.C
 *  2012IFF
 *
 *  Created by Keith Landry on 3/28/14.
 *  UCLA
 *
 */



void ptOfPairs(){
	
	
	//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	gSystem->Load("sameSignPair");
	cout << " Loading of sameSignPair library done" << endl;
	
	
	TFile* opPairFile = new TFile("");
	TFile* samePairFile = new TFile("");

	
	
	TH1D* hSameSignPt = new TH1D("sameSignPt","sameSignPt", 80,0,15);
	TH1D* hOpSignPt = new TH1D("opSignPt","opSignPt",80,0,15);
	
	
	pionPair* pair1 = new pionPair();
	TTree* pairTree = opPairFile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	
	
	sameSignPair* samePair1 = new sameSignPair();
	TTree* samePairTree = samePairFile->Get("sameSignPairTree");
	samePairTree->SetBranchAddress("sameSignPair", &samePair1);
	
	
	int highNumber;
	if (samePairTree->GetEntries() > pairTree->GetEntries())
	{
		highNumber = samePairTree->GetEntries();
	}
	else
	{
		highNumber = pairTree->GetEntries();
	}

	
	for (int iPair = 0; iPair < highNumber; iPair++)
	{
	
		samePairTree->GetEntry(iPair);
		pairTree->GetEntry(iPair);
		
		if (samePair1 != NULL)
		{
			
			double samePt = samePair1->getPion1()->pt() + samePair1->getPion2()->pt();
			hSameSignPt->Fill(smaePt);
			
		}
		if (pair1 != NULL)
		{
			
			double opPt = pair1->piPlus()->pt() + pair1->piMinus()->pt();
			hSameSignPt->Fill(opPt);

			
		}
		
		
		
	}
	
	
	
	TCanvas* cSame = new TCanvas();
	hSameSignPt->Draw();
	
	TCanvas* cOp = new TCanvas();
	hOpSignPt->Draw();
	
	
	
	
	
	
}
