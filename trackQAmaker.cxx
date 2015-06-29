/*
 *  trackQAmaker.cxx
 *  2012IFF
 *
 *  Created by Keith Landry on 3/7/14.
 *  UCLA
 *
 */

#include "trackQAmaker.h"

ClassImp(trackQAmaker)


//______________________________________________________________________________
trackQAmaker::trackQAmaker(StMuDstMaker* muDstMaker) : StMaker()
{
	mMuDstMaker = muDstMaker;
	
	string defaultName = "/star/u/klandry/ucladisk/2012IFF/defaultOutput.root";

	mOutFileName = defaultName;

}
//______________________________________________________________________________
Int_t trackQAmaker::Init()
{	
	mOutputFile = new TFile(mOutFileName.c_str(),"RECREATE");
		
	mH_Eta        = new TH1D("hEta","hEta",100,-3,3);
	mH_Pt         = new TH1D("hPt","hPt",80,0,20);
	mH_VertexZ    = new TH1D("hVertexZ","hVertexZ",100,-100,100);
	mH_nSigmaPion = new TH1D("hnSigmaPion","hnSigmaPion",50,-10,10);
	mH_nHitsFit   = new TH1D("hnHitsFit","hnHitsFit",50,0,50);

	mH_Eta_trig        = new TH1D("hEta_trig","hEta_trig",100,-3,3);
	mH_Pt_trig         = new TH1D("hPt_trig","hPt_trig",80,0,20);
	mH_VertexZ_trig    = new TH1D("hVertexZ_trig","hVertexZ_trig",100,-100,100);
	mH_nSigmaPion_trig = new TH1D("hnSigmaPion_trig","hnSigmaPion_trig",50,-10,10);
	mH_nHitsFit_trig   = new TH1D("hnHitsFit_trig","hnHitsFit_trig",50,0,50);

	
	mH_Eta_cut        = new TH1D("hEta__cut","hEta__cut",100,-3,3);
	mH_Pt_cut         = new TH1D("hPt_cut","hPt__cut",80,0,20);
	mH_VertexZ_cut    = new TH1D("hVertexZ_cut","hVertexZ__cut",100,-100,100);
	mH_nSigmaPion_cut = new TH1D("hnSigmaPion_cut","hnSigmaPion__cut",50,-10,10);
	mH_nHitsFit_cut   = new TH1D("hnHitsFit_cut","hnHitsFit__cut",50,0,50);
	
	mH_Events_total = new TH1I("hEventsTotal","hEventsTotal",5,0,5);
	mH_JP0 = new TH1I("hJP0","hJP0",5,0,5);
	mH_JP1 = new TH1I("hJP1","hJP1",5,0,5);
	mH_JP2 = new TH1I("hJP2","hJP2",5,0,5);
	mH_AJP = new TH1I("hAJP","hAJP",5,0,5);
  mH_BHT0VPDmb = new TH1I("hBHT0VPDmb","hBHT0VPDmb",5,0,5);
	mH_BHT1VPDmb = new TH1I("hBHT1VPDmb","hBHT1VPDmb",5,0,5);
	mH_BHT2BBCmb = new TH1I("hBHT2BBCmb","hBHT2BBCmb",5,0,5);
	mH_BHT2 = new TH1I("hBHT2","hBHT2",5,0,5);
	
	
	return kStOK;
}
//______________________________________________________________________________
Int_t trackQAmaker::Finish()
{
	
	mH_Eta->Write();
	mH_Pt->Write();
	mH_VertexZ->Write();
	mH_nSigmaPion->Write();
	mH_nHitsFit->Write();
	
	mH_Eta_cut->Write();
	mH_Pt_cut->Write();
	mH_VertexZ_cut->Write();
	mH_nSigmaPion_cut->Write();
	mH_nHitsFit_cut->Write();
	
	mH_Events_total->Write();
	mH_JP0->Write();
	mH_JP1->Write();
	mH_JP2->Write();
	mH_AJP->Write();
	mH_BHT0VPDmb->Write();
	mH_BHT1VPDmb->Write();
	mH_BHT2BBCmb->Write();
	mH_BHT2->Write();

	
	mOutputFile->Write();
	cout << "finished" << endl;
	return kStOK;
}

//==============================================================================

Int_t trackQAmaker::Make()
{
	StMuDst* muDst = mMuDstMaker->muDst();
	assert(muDst);
	
	mH_Events_total->Fill(1);

	StMuTriggerIdCollection trigIdCol = muDst->event()->triggerIdCollection();
	
	StTriggerId triggerVal = trigIdCol.nominal();

	bool triggerFired = false;

	
	if (triggerVal.isTrigger(370601))
	{
		mH_JP0->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370611))
	{
		mH_JP1->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370621))
	{
		mH_JP2->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370641))
	{
		mH_AJP->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370501))
	{
		mH_BHT0VPDmb->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370511))
	{
		mH_BHT1VPDmb->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370522))
	{
		mH_BHT2BBCmb->Fill(1);
		triggerFired = true;
	}
	if (triggerVal.isTrigger(370531))
	{
		mH_BHT2->Fill(1);
		triggerFired = true;
	}
	
	
	
	
	if (triggerFired)
	{
		
		
		int nTracks = 0;
		for (int iTrack = 0; iTrack < muDst->numberOfPrimaryTracks(); iTrack++)
		{
			
			
			StMuTrack* track1 = muDst->primaryTracks(iTrack);
			int vertOfTrack = track1->vertexIndex(); //want index to be 0 => highest ranking vertex
			
			if (vertOfTrack == 0 && muDst->primaryVertex(vertOfTrack)->ranking() > 0)// > 0 To make sure there is at least one usable vertex
			{
				double vertexZ = muDst->primaryVertex(track1->vertexIndex())->position().z();
				
				
				mH_Eta->Fill(track1->eta());
				mH_Pt->Fill(track1->pt());
				mH_VertexZ->Fill(vertexZ);
				mH_nSigmaPion->Fill(track1->nSigmaPion());
				mH_nHitsFit->Fill(track1->nHitsFit());
				
				
				if (fabs(vertexZ) < 60 && track1->pt() > 1.5 && track1->nHitsFit() > 15 && fabs(track1->nSigmaPion()) < 2 && fabs(track1->eta()) < 1.4)
				{
					mH_Eta_cut->Fill(track1->eta());
					mH_Pt_cut->Fill(track1->pt());
					mH_VertexZ_cut->Fill(vertexZ);
					mH_nSigmaPion_cut->Fill(track1->nSigmaPion());
					mH_nHitsFit_cut->Fill(track1->nHitsFit());
				}						
				
				
			}
			
			//delete track1;
		}//end track loop
	}//end trigger check
	
	//delete muDst;
	
	return kStOK;	
}
