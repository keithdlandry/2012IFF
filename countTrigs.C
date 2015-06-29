/*
 *  count.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/5/14.
 *  UCLA
 *
 */



void countTrigs(string fileList, string jobID){


	cout << "start" << endl;
	//*
	
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	gSystem->Load("pionPairTreeMaker");
	cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";
	
	
	StChain* muChain = new StChain();
	
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");

	ofstream outfile;
	string outname = "trigs" + jobID + ".txt";
	
	outfile.open(outname.c_str(),ios::app);

	int runID;
	int fillNo; 
	
	int numberEvents = 0;
	int nEvents = 1e6;
	//int nEvents = muDstMaker->muDst()->GetEntries();
	int iEvent = 0;
	
	int JP0 = 0;
	int JP1 = 0;
	int JP2 = 0;
	int AJP = 0; //NOT USING AJP IN sqrtMethod.C?
	
	int BHT0VPDmb = 0;
	int BHT1VPDmb = 0;
	int BHT2BBCmb = 0;
	int BHT2 = 0;

	while (muChain->Make(iEvent) == kStOK)
	{
		iEvent++;
		
		StMuEvent* MuEvent = muDstMaker->muDst()->event();
		
		runID = MuEvent->runId();
		fillNo = MuEvent->runInfo().beamFillNumber(1);
		numberEvents++;
		
		
		StMuTriggerIdCollection trigIdCol = MuEvent->triggerIdCollection();

		StTriggerId triggerVal = trigIdCol.nominal();

		
		if (triggerVal.isTrigger(370601)){JP0++;}
		if (triggerVal.isTrigger(370611)){JP1++;}
		if (triggerVal.isTrigger(370621)){JP2++;}
		if (triggerVal.isTrigger(370641)){AJP++;}

		
		if (triggerVal.isTrigger(370501)){BHT0VPDmb++;}
		if (triggerVal.isTrigger(370511)){BHT1VPDmb++;}
		if (triggerVal.isTrigger(370522)){BHT2BBCmb++;}
		if (triggerVal.isTrigger(370531)){BHT2++;}
		
		
		
		

	}
		
	cout << "fillNumber " << fillNo << endl;
	cout << "runID " << runID << end;
	cout << "totEvents " << numberEvents << endl;
	
	cout << "JP0 " << JP0 << endl;	
	cout << "JP1 " << JP1 << endl;	
	cout << "JP2 " << JP2 << endl;	
	cout << "AJP " << AJP << endl;	

	cout << "\n";
	
	cout << "BHT0*VPDmb " << BHT0VPDmb << endl;	
	cout << "BHT1*VPDmb " << BHT1VPDmb << endl;	
	cout << "BHT2*BBCmb " << BHT2BBCmb << endl;	
	cout << "      BHT2 " << BHT2      << endl;	

	outfile << "fillNumber" << fillNo << endl;
	outfile << "runID " << runID << endl;
	outfile << "totEvents " << numberEvents << endl;
	
	outfile << "JP0 " << JP0 << endl;	
	outfile << "JP1 " << JP1 << endl;	
	outfile << "JP2 " << JP2 << endl;	
	outfile << "AJP " << AJP << endl;	
	
	outfile << "\n";
	
	outfile << "BHT0*VPDmb " << BHT0VPDmb << endl;	
	outfile << "BHT1*VPDmb " << BHT1VPDmb << endl;	
	outfile << "BHT2*BBCmb " << BHT2BBCmb << endl;	
	outfile << "      BHT2 " << BHT2      << endl;	
	
	
	
	
//*/

}