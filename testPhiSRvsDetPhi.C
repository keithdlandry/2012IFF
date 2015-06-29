/*
 *  testPhiSRvsDetPhi.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/30/14.
 *  UCLA
 *
 */


void testPhiSRvsDetPhi(){


	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
	
	
	
	TH2D* hPhiSRvPhi_Up = new TH2D("hPhiSRvPhi_Up","hPhiSRvPhi_Up",16,-3.14159,3.14159,16,-3.14159,3.14159);
	TH2D* hPhiSRvPhi_Down = new TH2D("hPhiSRvPhi_Down","hPhiSRvPhi_Down",16,-3.14159,3.14159,16,-3.14159,3.14159);
	
	
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");
	
	string outFileName = "./resultsNew_4_22/yellowEtaGT0_pairs_4_2.root"; 
	
	
	
  //______________________________
	
	
	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	//______________________________
	
	
	TLorentzVector sum;
	TLorentzVector sumY;
	TLorentzVector sumB;
	
	
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		if (iPair == 1000000){break;}
		
		pairTree->GetEntry(iPair);
		
		
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
				sumB = sum; //blue beam.


				if (sumB.Pt() >= 3 && sumB.Pt() <= 50 && sumB.M() >= 0 && sumB.M() <= 100 && sumB.Eta() >= -1.4 && sumB.Eta() <= 1.4)
				{
					passInitialCut_B = true;
				}
			
				if (passInitialCut_B && (pair1->spinBit() == 9 || pair1->spinBit() == 10))
				{
					
					cout << pair1->phiSR('b') << "  " << sumB.Phi() << endl;
					
					hPhiSRvPhi_Up->Fill(pair1->phiSR('b'), sumB.Phi());
					
				}
				
				if (passInitialCut_B && (pair1->spinBit() == 5 || pair1->spinBit() == 6))
				{
					hPhiSRvPhi_Down->Fill(pair1->phiSR('b'), sumB.Phi());
				}
				
				
				
				
			}
				
			
			
			
			
		}
		
		
		
		
	}
	
	
	TCanvas* cUp = new TCanvas();
	hPhiSRvPhi_Up->Draw("colz");
			
	TCanvas* cDown = new TCanvas();
	hPhiSRvPhi_Down->Draw("colz");
			
			
			
}