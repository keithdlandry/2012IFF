/*
 *  printRuns.C
 *  2012IFF
 *
 *  Created by Keith Landry on 1/27/14.
 *  UCLA
 *
 */




void printRuns(){


	
	
	//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	
	
	//SET UP INPUT FILE
	//	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/all2012dataAll.root");
	//TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutputWithinRad/allWithRadcut.root");
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutAllDataTry1/allDataTry1.root");
	
	//SET UP TREE TO RECEIVE INPUT
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	
	
	ofstream outfile;
	outfile.open("runsInData_AllDataTry1.txt");
	
	outfile << "run number  number of pairs" << endl; 
	
	int runNumber;
	int previousRunNumber = 0;
	
	
	int numberOfPairsInRun = 0;
	
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		
		pairTree->GetEntry(iPair);
		
		runNumber = pair1->runInfo().runId();
		
		
		
		if (runNumber != previousRunNumber)
		{
			outfile << runNumber << "    " << numberOfPairsInRun << endl;
			
			numberOfPairsInRun = 1;
		}
		else
		{
			numberOfPairsInRun++;
		}

		
		
		previousRunNumber = runNumber;
	
		
		
		
	}
	
	
	
	
	
	
	
	


}