/*
 *  triggerRatios2012Data.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/25/15.
 *  UCLA
 *
 */


void triggerRatios2012Data(){


	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
  

  TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_9_9/allPairs_9_9.root");


	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	//______________________________
  
  
  
  int pionStarNumber = 0;
  
  //trigger counts
  int JP0count = 0;
	int JP1count = 0;
  int JP2count = 0;
	int AJPcount = 0;
  
  int BHT0VPDcount = 0;
  int BHT1VPDcount = 0;
  int BHT2BBCcount = 0;
  int BHT2count = 0;
  
  TH1I* hTriggerCounts = new TH1I("hTriggerCounts","hTriggerCounts",141,370501,370641);
  
  
	for (int iPair = pionStarNumber; iPair < pairTree->GetEntries(); iPair++)
  {
		
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		if (iPair == pionStarNumber+10000){break;}
    
		pairTree->GetEntry(iPair);
    
    
		if (pair1->withinRadius(0.05, 0.3))
		{
      StTriggerId trigId = pair1->triggerIds();

      if (trigId.isTrigger(370601))
      {
        JP0count++;
        hTriggerCounts->Fill(370601);
      }
      if (trigId.isTrigger(370611))
      {
        JP1count++;
        hTriggerCounts->Fill(370611);
      }
      if (trigId.isTrigger(370621))
      {
        JP2count++;
        hTriggerCounts->Fill(370621);
      }
      if (trigId.isTrigger(370641))
      {
        AJPcount++;
        hTriggerCounts->Fill(370641);
      }
      if (trigId.isTrigger(370501))
      {
        BHT0VPDcount++;
        hTriggerCounts->Fill(370501);
      }
      if (trigId.isTrigger(370511))
      {
        BHT1VPDcount++;
        hTriggerCounts->Fill(370511);
      }
      if (trigId.isTrigger(370522))
      {
        BHT2BBCcount++;
        hTriggerCounts->Fill(370522);
      }
      if (trigId.isTrigger(370531))
      {
        BHT2count++;
        hTriggerCounts->Fill(370531);
      }
      
      
      
    }
    
    
  }
  
  cout << "JP0count" << JP0count << endl;
  cout << "JP1count" << JP1count << endl;
  cout << "JP2count" << JP2count << endl;

  
  
  TFile* outfile = new TFile("/star/u/klandry/ucladisk/2012IFF/triggerRatiosByPiar.root","recreate");
  hTriggerCounts->Write();
  
  
  
}