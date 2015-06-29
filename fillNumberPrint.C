/*
 *  fillNumberPrint.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/7/14.
 *  UCLA
 *
 */

#include <iostream>

void fillNumberPrint(){


	//LOAD LIBRARIES
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	gSystem->Load("pionPairTreeMaker");
	cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";
	
	
	//LOAD STYLE
	gROOT->Macro("UHBstyle.C");
	gROOT->SetStyle("UHB");
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");
	
	ofstream outfile;
	outfile.open("runsAndFills.txt");
	
	
	pionPair* pair1 = new pionPair();	
	TTree* t = (TTree*)infile->Get("pionPairTree");
	t->SetBranchAddress("pionPair", &pair1);
	cout <<t->GetEntries()<<endl;

	t->GetEntry(0);
	
	
	int initialFillNumber = pair1->runInfo().beamFillNumber(0);
	int currentFillNumber = initialFillNumber;
	
	int initialRunNumber = pair1->runInfo().runId();
	int currentRunNumber = initialRunNumber;
	
	assert(initialFillNumber = pair1->runInfo().beamFillNumber(1));
	
	outfile << "Fill Number " << currentFillNumber << endl;
	outfile << currentRunNumber << endl;
	
	
	for (int iPair=0; iPair<t->GetEntries(); iPair++)
	{
		
		//if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == 100000) {break;}
		
		
		t->GetEntry(iPair);
		
		if (pair1->runInfo().runId() == currentRunNumber)
		{
			continue;
		}
		else
		{
			if (pair1->runInfo().beamFillNumber(0) == currentFillNumber)
			{
				outfile << currentRunNumber << endl;
				currentRunNumber = pair1->runInfo().runId();
			}
			else
			{
				outfile << "\n";
				outfile << "FullNumber " << currentFillNumber << "   Starting at pair # " << iPair-1 << endl;
				outfile << currentRunNumber << endl;
				
				currentFillNumber = pair1->runInfo().beamFillNumber(0);
				currentRunNumber = pair1->runInfo().runId();
			}

			
		}

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}		
	
	




}