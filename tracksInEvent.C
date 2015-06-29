/*
 *  tracksInEvent.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/11/14.
 *  UCLA
 *
 */


void tracksInEvent(string fileList, string jobID){
	
	
	
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//gSystem->Load("pionPairTreeMaker");
	//cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";
	
	
	//TFile* outFile = new TFile("/star/u/klandry/ucladisk/2012IFF/tracksOutput.root","recreate");
	TFile* outFile = new TFile("variableswithetacut.root","recreate");
	
	
	
	//*
	TH1D* hTracks = new TH1D("hTracks","hTracks",50,0,50);
	
	//TH1D* hInvarM    = new TH1D("invarM","invarM",80,0,2);
	//TH1D* hEtaTot	   = new TH1D("etaTot","etaTot",60,-1.5,1.5);
	//TH1D* hPhiR      = new TH1D("hPhiR","hPhiR",60,-4,4);
	//TH1D* hPhiS      = new TH1D("hPhiS","hPhiS",60,-4,4);
	//TH1D* hPhiSR     = new TH1D("hPhiSR","hPhiSR",60,-4,4);
	//TH1D* hTheta     = new TH1D("hTheta","hTheta",30,-0.85,4);
	//TH1D* hCosTheta  = new TH1D("hCosTheta","hCosTheta",80,-1,1);
	//TH1D* hZ         = new TH1D("hZ","hZ",80,0,1);
	TH1D* hPtot      = new TH1D("hPtot","hPtot",80,0,20);
	TH1D* hPtTOT     = new TH1D("hPt","hPt",80,0,15);
	
	TH1D* hEta = new TH1D("hEta","hEta",100,-3,3);
	TH1D* hPt  = new TH1D("hPt","hPt",80,0,20);
	TH1D* hVertexZ = new TH1D("hVertexZ","hVertexZ",100,-100,100);
	TH1D* hnSigmaPion = new TH1D("hnSigmaPion","hnSigmaPion",50,-10,10);
	TH1D* hnHitsFit = new TH1D("hnHitsFit","hnHitsFit",50,0,50);
	
	
	
	TH1D* hPhi = new TH1D("hPhi","hPhi",60,-3.14159,3.14159);
	
	
	StChain* muChain = new StChain();
	
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");
	
	//ofstream outfile;
	//outfile.open("/star/u/klandry/ucladisk/2012IFF/eventsInRun.txt");
	
	//string outname = "eventsInRun" + jobID + ".txt";
	
	//outfile.open(outname.c_str(),ios::app);
	
	int runID;
	
	int numberEvents = 0;
	int nEvents = 10000;
	//int nEvents = muDstMaker->muDst()->GetEntries();
	
	
	int maxPairs = 0;
	
	for (int iEvent = 0; iEvent<nEvents; iEvent++)
	{
		
		if (muChain->Make(iEvent) == kStOK)
		{
			
			StMuDst* muDst = muDstMaker->muDst();
			assert(muDst);
			
			StMuEvent* MuEvent = muDstMaker->muDst()->event();
			
			assert(MuEvent);
			
			
			bool triggerFired = false;
			
			//		StMuTriggerIdCollection trigIdCol = muDst->event()->triggerIdCollection();
			
			
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
			
			//triggerFired = true;
			
			if (iEvent%1000 == 0)
			{
				cout << iEvent << endl;
			}
			
			if (triggerFired)
			{
				int nTracks = 0;
				for (int iTrack = 0; iTrack < muDst->numberOfPrimaryTracks(); iTrack++)
				{
					
					
					StMuTrack* track1 = muDst->primaryTracks(iTrack);
					int vertOfTrack = track1->vertexIndex();
					
					if (vertOfTrack == 0 && muDst->primaryVertex(vertOfTrack)->ranking() >0)// > 0 To make sure there is at least one usable vertex
					{
						double vertexZ = muDst->primaryVertex(track1->vertexIndex())->position().z();
						
						
						StMuEvent* MuEvent = muDstMaker->muDst()->event();
						
						
						
						
						int tracks = muDst->numberOfPrimaryTracks();
						/*
						if (fabs(vertexZ) < 60)
						{
							hEta->Fill(track1->eta());
							hPt->Fill(track1->pt());
							hVertexZ->Fill(vertexZ);
							hnSigmaPion->Fill(track1->nSigmaPion());
							hnHitsFit->Fill(track1->nHitsFit());
						}
						//*/
						/*
						if (track1->pt() > 1.5)
						{
							hEta->Fill(track1->eta());
							hPt->Fill(track1->pt());
							hVertexZ->Fill(vertexZ);
							hnSigmaPion->Fill(track1->nSigmaPion());
							hnHitsFit->Fill(track1->nHitsFit());
						}
						//*/
						/*
						if (track1->nHitsFit() > 15)
						{
							hEta->Fill(track1->eta());
							hPt->Fill(track1->pt());
							hVertexZ->Fill(vertexZ);
							hnSigmaPion->Fill(track1->nSigmaPion());
							hnHitsFit->Fill(track1->nHitsFit());
						}
            //*/
						/*
						if (fabs(track1->nSigmaPion()) < 2)
						{
							hEta->Fill(track1->eta());
							hPt->Fill(track1->pt());
							hVertexZ->Fill(vertexZ);
							hnSigmaPion->Fill(track1->nSigmaPion());
							hnHitsFit->Fill(track1->nHitsFit());
						}
						//*/
						//*/
						if (fabs(track1->eta()) < 1.4)
						{
							hEta->Fill(track1->eta());
							hPt->Fill(track1->pt());
							hVertexZ->Fill(vertexZ);
							hnSigmaPion->Fill(track1->nSigmaPion());
							hnHitsFit->Fill(track1->nHitsFit());
						}
						//*/
						/*
						if (fabs(vertexZ) < 60 && track1->pt() > 1.5 && track1->nHitsFit() > 15 && fabs(track1->nSigmaPion()) < 2 && fabs(track1->eta()) < 1.4)
						{
							hEta->Fill(track1->eta());
							hPt->Fill(track1->pt());
							hVertexZ->Fill(vertexZ);
							hnSigmaPion->Fill(track1->nSigmaPion());
							hnHitsFit->Fill(track1->nHitsFit());
						}						
						//*/
						
						
						/*
						if (abs(vertexZ) < 60)
						{
							nTracks++;
						}
						*/
						
						//nTracks++;

					/*
						if (track1->pt()>1.5)
						{
							nTracks++;
						}
						//*/	
						
					/*
						if (abs(track1->nSigmaPion())<2)
						{
							nTracks++;
						}
						//*/
						
						if (fabs(vertexZ) < 60 && track1->pt()>1.5 && fabs(track1->nSigmaPion())<2 && fabs(track1->eta()) < 1.4)
						{
							nTracks++;
						}
						
						
					}
					
				}
				
				hTracks->Fill(nTracks);
				
				
				
				
				if (nTracks == 2){maxPairs+=1;}
				if (nTracks == 3){maxPairs+=2;}
				if (nTracks == 4){maxPairs+=4;}
				if (nTracks == 5){maxPairs+=6;}
				if (nTracks == 6){maxPairs+=9;}
				if (nTracks == 7){maxPairs+=12;}
				if (nTracks == 8){maxPairs+=16;}
				if (nTracks == 9){maxPairs+=20;}
				if (nTracks == 10){maxPairs+=25;}

		
						
				
				

			}
		}
	}
	
	//outfile << runID << "   " << numberEvents << endl;
	
	
	//*/
	
	//hTracks->Draw();
	
	//hTracks->Write();
	
	TCanvas* c1 = new TCanvas();
	hEta->Draw();
	TCanvas* c2 = new TCanvas();
	hPt->Draw();
	TCanvas* c3 = new TCanvas();
	hVertexZ->Draw();
	TCanvas* c4 = new TCanvas();
	hnSigmaPion->Draw();
	TCanvas* c5 = new TCanvas();
	hnHitsFit->Draw();
	
	hEta->Write();
	hPt->Write();
	hVertexZ->Write();
	hnSigmaPion->Write();
	hnHitsFit->Write();
	
	
	
	cout << maxPairs << endl;
	
	cout << "end" << endl;
	
	
	
}