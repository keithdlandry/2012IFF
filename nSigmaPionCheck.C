/*
 *  nSigmaPionCheck.C
 *  2012IFF
 *
 *  Created by Keith Landry on 3/4/14.
 *  UCLA
 *
 */




void nSigmaPionCheck(string fileList, string jobID){
	
	
	
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//gSystem->Load("pionPairTreeMaker");
	//cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";
	
	
	StChain* muChain = new StChain();
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");
	
	
	
	
	string outName = "nSigCheck_" + jobID + ".root";
	TFile* outFile = new TFile(outName.c_str(),"recreate");
	
	
	
	
	TH1D* hnSigmaPion = new TH1D("hnSigmaPion","hnSigmaPion",50,-10,10);
	
	int iEvent = 0;
	
	while (muChain->Make(iEvent) == kStOK)
	{
		
		if (iEvent%1000 == 0)
		{
			cout << iEvent << endl;
		}
		
		
		if (iEvent == 10000)
		{
			break;
		}
		
		iEvent++;
		
		StMuDst* muDst = muDstMaker->muDst();
		assert(muDst);
		
		StMuEvent* MuEvent = muDstMaker->muDst()->event();
		assert(MuEvent);
		
		
		bool triggerFired = false;
		
		
		
		StMuTriggerIdCollection trigIdCol = MuEvent->triggerIdCollection();
		
		
		StTriggerId triggerVal = trigIdCol.nominal();
		
		
		if (triggerVal.isTrigger(370601) || triggerVal.isTrigger(370611) || triggerVal.isTrigger(370621))
		{
			triggerFired = true;
		}
		
		if (triggerVal.isTrigger(370501) || triggerVal.isTrigger(370511) || triggerVal.isTrigger(370522) || triggerVal.isTrigger(370531))
		{
			triggerFired = true;
		}
		
		if (triggerFired)
		{
			
			for (int iTrack = 0; iTrack < muDst->numberOfPrimaryTracks(); iTrack++)
			{
				
				
				StMuTrack* track1 = muDst->primaryTracks(iTrack);
				int vertOfTrack = track1->vertexIndex();
				
				if (vertOfTrack == 0 && muDst->primaryVertex(vertOfTrack)->ranking() >0)// > 0 To make sure there is at least one usable vertex
				{
					double vertexZ = muDst->primaryVertex(track1->vertexIndex())->position().z();
					
					
					
					hnSigmaPion->Fill(track1->nSigmaPion());
					
					
					
				}					
			}
		}
	}

	
	hnSigmaPion->Draw();
	hnSigmaPion->Write();
	
	double nSigmaMean  = hnSigmaPion->GetMean(1);
	double nSigmaError = hnSigmaPion->GetMeanError(1);
	
	
	cout << nSigmaMean << endl;
	
	
	
	
	
	
}