/*
 *  tracknHitsTest.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/8/14.
 *  UCLA
 *
 */





void tracknHitsTest(string fileList,string jobID){


	
	
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");

	StChain* muChain = new StChain();
	
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");
	
	
	
	
	TFile* outfile = new TFile("./tracknHitsTest.root","recreate");
	
	
	
	
	
	TH2D* etaVsPossHits = new TH2D("etaVsPossHits","etaVsPossHits",15,-2,2,15,0,50);
	TH2D* etaVsFitHits = new TH2D("etaVsFitHits","etaVsFitHits",15,-2,2,15,0,50);

	TH1D* hNhits5 = new TH1D("hNhits5","hNhits5",15,-2,2);
	TH1D* hNhits15 = new TH1D("hNhits15","hNhits15",15,-2,2);
	TH1D* hNhitsFP = new TH1D("hNhitsFP","hNhitsFP",15,-2,2);
	TH2D* hNhitsFP2 = new TH2D("hNhitsFP2","hNhitsFP2",15,-2,2,15,0,1);
	TH2D* hNhitsFP3 = new TH2D("hNhitsFP3","hNhitsFP3",15,-2,2,15,0,50);

	TH2D* hNhits152D = new TH2D("hNhits152D","hNhits152D",15,-2,2,15,0,50);
	TH2D* hNhits152D_2 = new TH2D("hNhits152D_2","hNhits152D_2",15,-2,2,15,0,1);

	
	
	
	TH1D* hDCA = new TH1D("hDCA","hDCA",100,0,.1);
	
	
	
	TH1D* hPt5 = new TH1D("hPt_5","hPt_5",100,0,.000000001);
	TH1D* hPt15 = new TH1D("hPt_15","hPt_15",100,0,.000000001);
	
	
	
	
	for (int iEvent = 0; iEvent<5000; iEvent++)
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
			
			if (iEvent%1000 == 0)
			{
				cout << iEvent << endl;
			}
			 
			//triggerFired = true;
			if (triggerFired)
			{
				for (int iTrack = 0; iTrack < muDst->numberOfPrimaryTracks(); iTrack++)
				{
					
					

					
					StMuTrack* track1 = muDst->primaryTracks(iTrack);
					
					int vertOfTrack = track1->vertexIndex();

					StMuPrimaryVertex* vert1 = muDst->primaryVertex(vertOfTrack);
					
					
					
					//cout << "TEST"<<endl;
					
					hDCA->Fill(track1->dca(track1->vertexIndex()).mag());
					
					//cout << "way 1 " << track1->dca(track1->vertexIndex()).mag() << endl;
					//cout << "way 2 " << track1->dca(track1, vert1).mag() << endl;
					
					
					
					if (vertOfTrack == 0 && muDst->primaryVertex(vertOfTrack)->ranking() >0)// > 0 To make sure there is at least one usable vertex
					{
						double vertexZ = muDst->primaryVertex(track1->vertexIndex())->position().z();
						
						

						if (fabs(vertexZ) < 60 && track1->dca(track1->vertexIndex()).mag() < 2 && fabs(track1->nSigmaPion()) < 2)
						{
							//cout << track1->nHitsFit() << " " << track1->nHitsPoss() << " " << track1->eta() << endl;						
						
							etaVsPossHits->Fill( track1->eta(), track1->nHitsPoss());
							etaVsFitHits->Fill(track1->eta(), track1->nHitsFit());
						
							
							if (track1->nHitsFit() >= 5 && track1->nHitsFit() < 15) {hNhits5->Fill(track1->eta());}
							if (track1->nHitsFit() > 15) {hNhits15->Fill(track1->eta());}
							if (track1->nHitsFit() >=5 && ( (double)track1->nHitsFit()/track1->nHitsPoss() >= .5 || track1->nHitsFit() >15)) {hNhitsFP->Fill(track1->eta());}
							
							if ( (track1->nHitsFit() >=5 && (double)track1->nHitsFit()/track1->nHitsPoss() >= .5 ) || track1->nHitsFit() >15) 
							{
								hNhitsFP3->Fill(track1->eta(), track1->nHitsFit());
								hNhitsFP2->Fill(track1->eta(), (double)track1->nHitsFit()/track1->nHitsPoss());
								//hPt5->Fill(track1->pt());
							
							}
							cout << "way 1 " << track1->dca(track1->vertexIndex()).mag() << endl;

						
							if (track1->nHitsFit() > 15)
							{
								hNhits152D->Fill( track1->eta(), track1->nHitsFit());
							}
							if (track1->nHitsFit() > 15)
							{
								hNhits152D_2->Fill( track1->eta(), (double)track1->nHitsFit()/track1->nHitsPoss());
								hPt15->Fill(track1->dca(track1->vertexIndex()).mag());
							}
							if (track1->nHitsFit() >=5 /*&& (double)track1->nHitsFit()/track1->nHitsPoss() >= .5*/ )
							{
								hPt5->Fill(track1->dca(track1->vertexIndex()).mag());
							}
							
							
							
							
							
							
							//cout << (double)track1->nHitsFit()/track1->nHitsPoss() << "  " << track1->nHitsPoss() << endl;
						}
					
						
						
						
						
						
						
						
						
						
						
						
					}
					
					
				}//end track loop
				
				
				
				
			}//end trig check
		}//end make ok
	}//end event loop
	
	TH1D* hDiff = new TH1D("hDiff","hDiff",15,-2,2);
	TH1D* hPercIncr = new TH1D("hPercIncr","hPercIncr",15,-2,2);
	
	
	for (int i = 1; i<=15; i++)
	{
		cout << hNhitsFP->GetBinContent(i) << "   " <<  hNhits15->GetBinContent(i) << "   " << hNhitsFP->GetBinContent(i) - hNhits15->GetBinContent(i) << endl;

		hDiff->SetBinContent(i, hNhitsFP->GetBinContent(i) - hNhits15->GetBinContent(i));
		if (hNhits15->GetBinContent(i) != 0){hPercIncr->SetBinContent(i, (double)(hNhitsFP->GetBinContent(i) - hNhits15->GetBinContent(i))/hNhits15->GetBinContent(i)*100);}
	
	}
	
	//*
	etaVsPossHits->Draw("colz");
	/*
	TCanvas* c2 = new TCanvas();
	hNhits5->Draw();
	
	TCanvas* c3 = new TCanvas();
	hNhits15->Draw();
	
	TCanvas* c4 = new TCanvas();
	hNhitsFP->Draw();

	TCanvas* c5 = new TCanvas();
	hNhitsFP2->Draw("colz");

	TCanvas* c6 = new TCanvas();
	etaVsFitHits->Draw("colz");
	

	TCanvas* c7 = new TCanvas();

	TH1D* hproj = hNhitsFP2->ProjectionX();
	hproj->Draw();
	
	TCanvas* c8 = new TCanvas();
	
	hNhits152D->Draw("colz");
	
	TCanvas* c9 = new TCanvas();
	
	hNhits152D_2->Draw("colz");
	
	TCanvas* c10 = new TCanvas();
	hNhitsFP3->Draw("colz");
	
	TCanvas* c11 = new TCanvas();
	hDiff->Draw();

	TCanvas* c12 = new TCanvas();
	hPercIncr->Draw();
	*/
	TCanvas* c13 = new TCanvas();
	hDCA->Draw();
	//*/
	
	
	
	TCanvas* cPt5 = new TCanvas();
	hPt5->Draw();
	TCanvas* cPt15 = new TCanvas();
	hPt15->Draw();
	
	
}