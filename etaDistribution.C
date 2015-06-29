/*
 *  etaDistribution.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/23/14.
 *  UCLA
 *
 */


void etaDistribution(){
	
	
	
	
	
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	
	
	
	//SET UP INPUT FILE_____________
	//TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_5_19_5Hits/allPairs_5_19.root");
	
	TH1D* hEtaTot	   = new TH1D("etaTot","etaTot",60,-2,2);
	TH1D* hMass	   = new TH1D("Mass","Mass",1000,0,2);
	TH1D* hPt	   = new TH1D("Pt","Pt",1000,0,20);
	
	
	
	
	
	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	//______________________________
	
	TLorentzVector sum;
	
	
	int pionStarNumber = 0;
	int test = 0;
	int breakNum = 500000;
	int numberInRadius = 0;
	
	for (int iPair = pionStarNumber; iPair < pairTree->GetEntries(); iPair++)
	{
		
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		if (iPair == pionStarNumber+breakNum){break;}
		
		pairTree->GetEntry(iPair);
		
		
		//fill number 16427 didn't have any polarization data available
		if (pair1->runInfo().beamFillNumber(1) == 16427 && pair1->runInfo().beamFillNumber(0) == 16427)
		{
			continue;
		}
		
		//if (pair1->withinRadius(.3, 1.5)){breakNum++;}
		
		if (pair1->withinRadius(0.05, 0.3))
		{
			
			
			bool triggerFired = false;
			bool fromKaon = false;
			bool passInitialCut_B = false;
			bool passInitialCut_Y = false;
			bool passDCAcut = false;
			
			StTriggerId trigId = pair1->triggerIds();
			
			//JP0,JP1,JP2,AJP
			if (trigId.isTrigger(370601) || trigId.isTrigger(370611) || trigId.isTrigger(370621) || trigId.isTrigger(370641))
			{
				triggerFired = true;
			}
			
			//BHT0VPD,BHT1VPD,BHT2BBC,BHT2
			if (trigId.isTrigger(370501) || trigId.isTrigger(370511) || trigId.isTrigger(370522) || trigId.isTrigger(370531))
			{
				triggerFired = true;
			}
			
			if (triggerFired)
			{
				sum = pair1->piPlusLV() + pair1->piMinusLV();
				
				
				hEtaTot->Fill(sum.Eta());
				hMass->Fill(sum.M());
				hPt->Fill(sum.Pt());
				numberInRadius++;

				
			}	
		}
		if (numberInRadius == 151947)
		{
			break;
		}

	}

	cout << "number in radius " << numberInRadius << endl;

	hEtaTot->Draw();
	TCanvas *c2 = new TCanvas();
	hMass->Draw();
	TCanvas* c3 = new TCanvas();
	hPt->Draw();
	
	



}