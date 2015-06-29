/*
 *  testSched.C
 *  2012IFF
 *
 *  Created by Keith Landry on 11/25/13.
 *  UCLA
 *
 */


void testSched(string infileName, string jobID){

	cout << infileName << endl;
	cout << jobID << endl;
	
	
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");

	
	
	string outfileName = jobID + "testout.root";
	
	
	
//	TFile* inFile = new TFile(infileName.c_str());
	TFile* outFile = new TFile(outfileName.c_str(),"recreate");
	
	
	TH1D* hist = new TH1D("hist","hist",100,0,100);
	
	
	StChain* chain = new StChain; 

	StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",infileName.c_str(),"",100000,"MuDst");

	
	
	for (int iEvent = 0; iEvent <100; iEvent++)
	{
		
		
		chain->Make(iEvent);
		
		
		
		StMuDst* muDst = muDstMaker->muDst();
		
		StMuEvent* muevent = muDst->event();
		
		hist->Fill(muevent->numberOfVpdEastHits());
		
		
	}
	
	
	/*
	TTree* tree = inFile->Get("MuDst");
	
	TH1I* testHist = new TH1I("test","test",0,10000);
	
	testHist->Fill(tree->GetEntries());
	*/
//	testHist->Write();
	outFile->Write();



}