/*
 *  dihadronPairQA.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/5/15.
 *  UCLA
 *
 */


void dihadronPairQA(){





	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("dihadronPair");
	cout << " loading of dihadronPair library done" << endl;
	//______________________________
	
	
	//SET UP INPUT FILE_____________
	
  TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/dihadron/diHadOut_5_7/allKPi_5_7.root");

	
	//SET UP TREE TO RECEIVE INPUT__
	dihadronPair* pair1 = new dihadronPair();
	TTree* pairTree = infile->Get("dihadronPairTree");
	pairTree->SetBranchAddress("dihadronPair", &pair1);
	//______________________________
  
  
  TLorentzVector sum;
	TLorentzVector sumY;
	TLorentzVector sumB;
	
  double PI = 3.14159265359;

  TH1D* hInvarM = new TH1D("hInvarM","hInvarM",800,0,5);
  TH2D* hToFNsig = new TH2D("hToFNsig","hToFNsig",100, -5, 5, 100, -1 , 2);
  TH2D* hKToFNsig = new TH2D("hKToFNsig","hKToFNsig",100, -5, 5, 100, -1 , 2);
  TH2D* hPiToFNsig = new TH2D("hPiToFNsig","hPiToFNsig",100, -5, 5, 100, -1 , 2);
  
  for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == 100000){break;}
    
		
		pairTree->GetEntry(iPair);

    if (pair1->withinRadius(0.05, 0.3))
		{
			
      bool triggerFired = false;

      StTriggerId trigId = pair1->triggerIds();
    
    
      //TRIGGERS: 370601[JPO] 370611[JP1] 370621[JP2] 370641[AJP]
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
				
        double posToFM = pair1->tof_m2Pos();
        double negToFM = pair1->tof_m2Neg();
        StMuTrack* posTrack = pair1->posHad();
        StMuTrack* negTrack = pair1->negHad();
        
				sum = pair1->posHadLV() + pair1->negHadLV();
				sumY; //for yellow beam 
				sumB; //for blue beam 
				
				sumB = sum; //blue beam.
				
				sumY = sum;
				sumY.RotateY(PI);
        
        hInvarM->Fill(sum.M());
        
        
        
        hToFNsig->Fill(posTrack->nSigmaPion(), posToFM);
        hToFNsig->Fill(negTrack->nSigmaPion(), negToFM);
        
        
        
        if (pair1->posTrackName() == "pion")
        {
          hPiToFNsig->Fill(posTrack->nSigmaPion(), posToFM);
        }
        if (pair1->negTrackName() == "pion")
        {
          hPiToFNsig->Fill(negTrack->nSigmaPion(), negToFM);
        }
        if (pair1->posTrackName() == "kaon")
        {
          hKToFNsig->Fill(posTrack->nSigmaPion(), posToFM);
        }
        if (pair1->negTrackName() == "kaon")
        {
          hKToFNsig->Fill(negTrack->nSigmaPion(), negToFM);
        }
        
        
        
        
        
        
      } 
  
    }
  }
      
  //hInvarM->Draw();
  
  hToFNsig->Draw("COLZ");
  
  TCanvas* c2 = new TCanvas();
  c2->Divide(2, 1);
  c2->cd(1);
  hPiToFNsig->Draw("COLZ");
  c2->cd(2);
  hKToFNsig->Draw("COLZ");
  
  TCanvas* cMass = new TCanvas();
  hInvarM->Draw();
  
  
}
