/*
 *  readTrig.C
 *  2012IFF
 *
 *  Created by Keith Landry on 12/16/13.
 *  UCLA
 *
 */




void readTrig(){

	//LOAD LIBRARIES
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	gSystem->Load("pionPairTreeMaker");
	cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutput/all2012data.root");

	pionPair* pair1 = new pionPair();
	
	TTree* t = (TTree*)infile->Get("pionPairTree");
	
	
	t->SetBranchAddress("pionPair", &pair1);
	cout <<t->GetEntries()<<endl;
	
	int pairsWithFiredTrig = 0;
	
	int noJP0 = 0;
	int noJP1 = 0;
	int noJP2 = 0;
	int noAJP = 0;
	
	int noBHT0VPD = 0;
	int noBHT1VPD = 0;
	int noBHT2BBC = 0;
	
	int noBHT2 = 0;
	
	for (int iPair=0; iPair<t->GetEntries(); iPair++)
	{
		
		t->GetEntry(iPair);
		
		//*
		
		cout << "runID : " << pair1->runInfo().runId() << endl;
		
		int trigsFiredForPair = 0;

		
		StTriggerId trigId = pair1->triggerIds();
		
		
		vector<unsigned int> trigvect;
		
		trigvect = trigId.triggerIds();
		
		vector<unsigned int>::iterator iter;
		
		//cout << "pair " << iPair << " triggers " << trigvect.size() << endl;
		
		
		for (iter = trigvect.begin(); iter != trigvect.end(); iter++)
		{
			
			//cout << "trigger id " << *iter << endl;
			
		}
		//*
		
		if (trigId.isTrigger(370601))
		{ 
			noJP0++;
		}
		if (trigId.isTrigger(370611))
		{ 
			noJP1++;
		}
		if (trigId.isTrigger(370621))
		{ 
			noJP2++;
		}
		if (trigId.isTrigger(370641))
		{ 
			noAJP++;
		}
		if (trigId.isTrigger(370501))
		{ 
			noBHT0VPD++;
		}
		if (trigId.isTrigger(370511))
		{ 
			noBHT1VPD++;
		}
		if (trigId.isTrigger(370522))
		{ 
			noBHT2BBC++;
		}
		if (trigId.isTrigger(370531))
		{ 
			noBHT2++;
		}
		
		//*/
		
		
		/*if (trigId.isTrigger(370641) || trigId.isTrigger(370021) || trigId.isTrigger(370022) || trigId.isTrigger(370011) || trigId.isTrigger(370601) ||trigId.isTrigger(370611) || trigId.isTrigger(370621))
		{
			trigsFiredForPair++;
		}
	
		
		//cout << "pion Pair " << iPair << " has " << trigsFiredForPair << " fired" << endl;
	
		if (trigsFiredForPair>0)
		{
			pairsWithFiredTrig++;
		}
		 //*/
	}
	
	cout << "    JPO: " << noJP0 << endl;
	cout << "    JP1: " << noJP1 << endl;
	cout << "    JP2: " << noJP2 << endl;
	cout << "    AJP: " << noAJP << endl;
	cout << "   BHT2: " << noBHT2 << endl;
	cout << "BHT0VPD: " << noBHT0VPD << endl;
	cout << "BHT1VPD: " << noBHT1VPD << endl;
	cout << "BHT2BBC: " << noBHT2BBC << endl;


	
	//cout << "pion pairs from an event with a fired trigger " << pairsWithFiredTrig << endl;
//*/
	
}