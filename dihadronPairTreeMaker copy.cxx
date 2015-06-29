/*
 *  dihadronPairTreeMaker.cxx
 *  2012IFF
 *
 *  Created by Keith Landry on 1/29/15.
 *  UCLA
 *
 */

#include "dihadronPairTreeMaker.h"

ClassImp(dihadronPairTreeMaker)

//______________________________________________________________________________
dihadronPairTreeMaker::dihadronPairTreeMaker(StMuDstMaker* muDstMaker) : StMaker()
{
	mMuDstMaker       = muDstMaker;
	
	string defaultName = "/star/u/klandry/ucladisk/2012IFF/defaultOutput.root";
	mOutFileName = defaultName;
}
//______________________________________________________________________________
Int_t dihadronPairTreeMaker::Init()
{	
	mOutputFile = new TFile(mOutFileName.c_str(),"RECREATE");
  
	mDihadronPairTree = new TTree("dihadronPairTree","dihadronPairTree");
	mDihadronPairTree->Branch("dihadronPair", "dihadronPair", &mDihadronPair);
	
	//QA HISTOGRAMS
	mH_Eta             = new TH1D("hEta","hEta",100,-3,3);
	mH_Pt              = new TH1D("hPt","hPt",80,0,20);
	mH_VertexZ         = new TH1D("hVertexZ","hVertexZ",100,-100,100);
	mH_nSigmaPion      = new TH1D("hnSigmaPion","hnSigmaPion",50,-10,10);
	mH_nSigmaKaon      = new TH1D("hnSigmaKaon","hnSigmaKaon",50,-10,10);
	mH_nHitsFit        = new TH1D("hnHitsFit","hnHitsFit",50,0,50);
	
	mH_Eta_trig        = new TH1D("hEta_trig","hEta_trig",100,-3,3);
	mH_Pt_trig         = new TH1D("hPt_trig","hPt_trig",80,0,20);
	mH_VertexZ_trig    = new TH1D("hVertexZ_trig","hVertexZ_trig",100,-100,100);
	mH_nSigmaPion_trig = new TH1D("hnSigmaPion_trig","hnSigmaPion_trig",50,-10,10);
	mH_nSigmaKaon_trig = new TH1D("hnSigmaKaon_trig","hnSigmaKaon_trig",50,-10,10);
	mH_nHitsFit_trig   = new TH1D("hnHitsFit_trig","hnHitsFit_trig",50,0,50);
	
	mH_Eta_cut         = new TH1D("hEta_cut","hEta_cut",100,-3,3);
	mH_Pt_cut          = new TH1D("hPt_cut","hPt_cut",80,0,20);
	mH_VertexZ_cut     = new TH1D("hVertexZ_cut","hVertexZ_cut",100,-100,100);
	mH_nSigmaPion_cut  = new TH1D("hnSigmaPion_cut","hnSigmaPion_cut",50,-10,10);
	mH_nSigmaKaon_cut  = new TH1D("hnSigmaKaon_cut","hnSigmaKaon_cut",50,-10,10);
	mH_nHitsFit_cut    = new TH1D("hnHitsFit_cut","hnHitsFit_cut",50,0,50);
	
	mH_Events_total    = new TH1I("hEventsTotal","hEventsTotal",5,0,5);
	mH_JP0             = new TH1I("hJP0","hJP0",5,0,5);
	mH_JP1             = new TH1I("hJP1","hJP1",5,0,5);
	mH_JP2             = new TH1I("hJP2","hJP2",5,0,5);
	mH_AJP             = new TH1I("hAJP","hAJP",5,0,5);
  mH_BHT0VPDmb       = new TH1I("hBHT0VPDmb","hBHT0VPDmb",5,0,5);
	mH_BHT1VPDmb       = new TH1I("hBHT1VPDmb","hBHT1VPDmb",5,0,5);
	mH_BHT2BBCmb       = new TH1I("hBHT2BBCmb","hBHT2BBCmb",5,0,5);
	mH_BHT2            = new TH1I("hBHT2","hBHT2",5,0,5);
	
	return kStOK;
}
//______________________________________________________________________________
Int_t dihadronPairTreeMaker::Finish()
{
	//WRITE QA HISTOGRAMS
	mH_Eta->Write();
	mH_Pt->Write();
	mH_VertexZ->Write();
	mH_nSigmaPion->Write();
	mH_nSigmaKaon->Write();
	mH_nHitsFit->Write();
	
	mH_Eta_cut->Write();
	mH_Pt_cut->Write();
	mH_VertexZ_cut->Write();
	mH_nSigmaPion_cut->Write();
	mH_nSigmaKaon_cut->Write();
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
	cout << "\n";
	cout << "\n";
	cout << "finished" << endl;
	cout << "\n";
	cout << "\n";
	return kStOK;
}

//==============================================================================
Int_t dihadronPairTreeMaker::Make()
{
 	assert(mMuDstMaker);
	
	StMuDst* muDst = mMuDstMaker->muDst();	
	assert(muDst);
	if (muDst == nullptr)
	{
		cout << "ERROR: MEMORY COULD NOT BE ALLOCATED" << endl;
	}
	
	
	
	mH_Events_total->Fill(1);

  //triggerInfo
	StMuTriggerIdCollection trigIdCol = muDst->event()->triggerIdCollection();
	
	StTriggerId triggerVal = trigIdCol.nominal();
	
	if (triggerVal.isTrigger(370601)){mH_JP0->Fill(1);}
	if (triggerVal.isTrigger(370611)){mH_JP1->Fill(1);}
	if (triggerVal.isTrigger(370621)){mH_JP2->Fill(1);}
	if (triggerVal.isTrigger(370641)){mH_AJP->Fill(1);}
	if (triggerVal.isTrigger(370501)){mH_BHT0VPDmb->Fill(1);}
	if (triggerVal.isTrigger(370511)){mH_BHT1VPDmb->Fill(1);}
	if (triggerVal.isTrigger(370522)){mH_BHT2BBCmb->Fill(1);}
	if (triggerVal.isTrigger(370531)){mH_BHT2->Fill(1);}
	
	
	//spinInfo
	int bx7 = muDst->event()->l0Trigger().bunchCrossingId7bit(muDst->event()->runId());
  
	StSpinDbMaker* spDbMaker = dynamic_cast<StSpinDbMaker*>(GetMakerInheritsFrom("StSpinDbMaker"));
	assert(spDbMaker);
	int spinBit = spDbMaker->spin4usingBX7(bx7);
	
	//find highest ranking vertex
	double highRank = 0;
	int highRankVertIndex = 0;
  
	for (int iVert = 0; iVert < muDst->numberOfPrimaryVertices(); iVert++)
	{
		StMuPrimaryVertex* vertex = muDst->primaryVertex(iVert);
		assert(vertex);
		
		if (fabs(vertex->position().z()) < 60)
		{
			double ranking = vertex->ranking();
			
			
			if (ranking > highRank)
			{
				highRank = ranking;
				highRankVertIndex = iVert;
			}
		}
	}//end vertex loop
	
  //loop over tracks once
	for (int iTrack = 0; iTrack < muDst->numberOfPrimaryTracks()-1; iTrack++)
	{

		StMuTrack* track1 = muDst->primaryTracks(iTrack);
		//*
		if (track1 == NULL)
		{
			break;
		}
		assert(track1);
		//*/		
		int vertOfTrack = track1->vertexIndex();
		
		if (vertOfTrack == highRankVertIndex && highRank > 0)// > 0 To make sure there is at least one usable vertex
		{
			double vertexZ = muDst->primaryVertex(track1->vertexIndex())->position().z();
			
      //FILL QA HISTOGRAMS
			mH_Eta->Fill(track1->eta());
			mH_Pt->Fill(track1->pt());
			mH_VertexZ->Fill(vertexZ);
			mH_nSigmaPion->Fill(track1->nSigmaPion());
			mH_nSigmaPion->Fill(track1->nSigmaKaon());
			mH_nHitsFit->Fill(track1->nHitsFit());
			
      //double dca1 = track1->dca(track1->vertexIndex()).mag();
			bool hitsTrack1 = false;
			
			if ((track1->nHitsFit() >=5 && (double)track1->nHitsFit()/track1->nHitsPoss() >= .5 ))
			{
				hitsTrack1 = true;
			}
			
			//track cuts
			if (track1->pt() > 1.5 && fabs(track1->eta()) < 2 && hitsTrack1 && fabs(vertexZ) < 60 && hitsTrack1)
			{
				//FILL QA HISTOGRAMS WITH CUT
				mH_Eta_cut->Fill(track1->eta());
				mH_Pt_cut->Fill(track1->pt());
				mH_VertexZ_cut->Fill(vertexZ);
				mH_nSigmaPion_cut->Fill(track1->nSigmaPion());
				mH_nSigmaKaon_cut->Fill(track1->nSigmaKaon());
				mH_nHitsFit_cut->Fill(track1->nHitsFit());
        
        bool track1_IsPiPlus   = false;
        bool track1_IsPiMinus  = false;
        bool track1_IsKaPlus   = false;
        bool track1_IsKaMinus  = false;
        
        
        //PARTICLE ID
        StMuBTofHit* bTofI = muDst->btofHit(iTrack);
        double betaI   = track1->btofPidTraits().beta();
        double momI    = track1->p().mag();
//        double mass2I  = momI**2*(1/betaI**2 - 1);
        double mass2I  = pow(momI,2)*(1/pow(betaI,2) - 1);
        double nSigPiI = track1->nSigmaPion();
        
        //2 Momentum bins
        /*
        //low pt condition
        if (track1->p().mag() <= 2.5 && pow(betaI,2) < 100 && mass2I < .18*nSigPiI+.388 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsPiPlus  = true;}
          if (track1->charge() == -1){track1_IsPiMinus = true;}
        }
        if (track1->p().mag() <= 2.5 && pow(betaI,2) < 100 && mass2I > .18*nSigPiI+.388 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsKaPlus  = true;}
          if (track1->charge() == -1){track1_IsKaMinus = true;}
        }
        
        //hi pt condition
        if (track1->p().mag() > 2.5 && track1->p().mag() < 4.0 && pow(betaI,2) < 100 && mass2I < .296*nSigPiI+.63 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsPiPlus  = true;}
          if (track1->charge() == -1){track1_IsPiMinus = true;}
        }
        if (track1->p().mag() > 2.5 && track1->p().mag() < 4.0 && pow(betaI,2) < 100 && mass2I > .296*nSigPiI+.63 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsKaPlus  = true;}
          if (track1->charge() == -1){track1_IsKaMinus = true;}
        }
        //*/
        if (track1->p().mag() <= 1.9 && pow(betaI,2) < 100 && mass2I < .098*nSigPiI+.202 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsPiPlus  = true;}
          if (track1->charge() == -1){track1_IsPiMinus = true;}
        }
        if (track1->p().mag() <= 1.9 && pow(betaI,2) < 100 && mass2I > .092*nSigPiI+.287 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsKaPlus  = true;}
          if (track1->charge() == -1){track1_IsKaMinus = true;}
        }
        if (track1->p().mag() > 1.9 && track1->p().mag() <= 2.3 && pow(betaI,2) < 100 && mass2I < .139*nSigPiI+.306 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsPiPlus  = true;}
          if (track1->charge() == -1){track1_IsPiMinus = true;}
        }
        if (track1->p().mag() > 1.9 && track1->p().mag() <= 2.3 && pow(betaI,2) < 100 && mass2I > .135*nSigPiI+.414 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsKaPlus  = true;}
          if (track1->charge() == -1){track1_IsKaMinus = true;}
        }
        if (track1->p().mag() > 2.3 && track1->p().mag() <= 2.7 && pow(betaI,2) < 100 && mass2I < .231*nSigPiI+.485 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsPiPlus  = true;}
          if (track1->charge() == -1){track1_IsPiMinus = true;}
        }
        if (track1->p().mag() > 2.3 && track1->p().mag() <= 2.7 && pow(betaI,2) < 100 && mass2I > .230*nSigPiI+.585 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsKaPlus  = true;}
          if (track1->charge() == -1){track1_IsKaMinus = true;}
        }
        if (track1->p().mag() > 2.7 && track1->p().mag() <= 3.1 && pow(betaI,2) < 100 && mass2I < .324*nSigPiI+.694 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsPiPlus  = true;}
          if (track1->charge() == -1){track1_IsPiMinus = true;}
        }
        if (track1->p().mag() > 2.7 && track1->p().mag() <= 3.1 && pow(betaI,2) < 100 && mass2I > .322*nSigPiI+.870 && nSigPiI < 2.5 && mass2I < 0.5)
        {
          if (track1->charge() == 1) {track1_IsKaPlus  = true;}
          if (track1->charge() == -1){track1_IsKaMinus = true;}
        }
        
        
        
        
        
        
        
        //loop over tracks a second time
				for (int jTrack = iTrack + 1; jTrack < muDst->numberOfPrimaryTracks(); jTrack++)
				{
					StMuTrack* track2 = muDst->primaryTracks(jTrack);
					//assert(track2);
          
          
          
          
          if (track1->vertexIndex() == track2->vertexIndex())
					{
						//GET THE LAST TRACK WE MISSED ON THE FIRST TRACK LOOP
						if (jTrack == muDst->numberOfPrimaryTracks())
						{
							mH_Eta->Fill(track1->eta());
							mH_Pt->Fill(track1->pt());
							mH_VertexZ->Fill(vertexZ);
							mH_nSigmaPion->Fill(track1->nSigmaPion());
							mH_nSigmaKaon->Fill(track1->nSigmaKaon());
							mH_nHitsFit->Fill(track1->nHitsFit());
						}
            
            double dca2 = track2->dca(track2->vertexIndex()).mag();
            
            bool hitsTrack2 = false;
						
						if ((track2->nHitsFit() >=5 && (double)track2->nHitsFit()/track2->nHitsPoss() >= .5 ))
						{
							hitsTrack2 = true;
						}
            
            if (track2->pt() > 1.5 && fabs(track2->eta()) < 2 && hitsTrack2)
						{
              if (jTrack == muDst->numberOfPrimaryTracks())
							{
								mH_Eta_cut->Fill(track1->eta());
								mH_Pt_cut->Fill(track1->pt());
								mH_VertexZ_cut->Fill(vertexZ);
								mH_nSigmaPion_cut->Fill(track1->nSigmaPion());
								mH_nSigmaKaon_cut->Fill(track1->nSigmaKaon());
								mH_nHitsFit_cut->Fill(track1->nHitsFit());								
							}
              
              
              bool track2_IsPiPlus   = false;
              bool track2_IsPiMinus  = false;
              bool track2_IsKaPlus   = false;
              bool track2_IsKaMinus  = false;
              
              StMuBTofHit* bTofJ = muDst->btofHit(jTrack);
              double betaJ   = track2->btofPidTraits().beta();
              double momJ    = track2->p().mag();
//              double mass2J  = momJ**2*(1/betaJ**2 - 1);
              double mass2J  = pow(momJ,2)*(1/pow(betaJ,2) - 1);
              double nSigPiJ = track2->nSigmaPion();
              
              
              //2momentum bins
              /*
              //low pt condition
              if (track2->p().mag() <= 2.5 && pow(betaJ,2) < 100 && mass2J < .18*nSigPiJ+.388 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsPiPlus  = true;}
                if (track2->charge() == -1){track2_IsPiMinus = true;}
              }
              if (track2->p().mag() <= 2.5 && pow(betaJ,2) < 100 && mass2J > .18*nSigPiJ+.388 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsKaPlus  = true;}
                if (track2->charge() == -1){track2_IsKaMinus = true;}
              }
              
              //hi pt condition
              if (track2->p().mag() > 2.5 && track2->p().mag() < 4.0 && pow(betaJ,2) < 100 && mass2J < .296*nSigPiJ+.63 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsPiPlus  = true;}
                if (track2->charge() == -1){track2_IsPiMinus = true;}
                
              }
              if (track2->p().mag() > 2.5 && track2->p().mag() < 4.0 && pow(betaJ,2) < 100 && mass2J > .296*nSigPiJ+.63 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsKaPlus  = true;}
                if (track2->charge() == -1){track2_IsKaMinus = true;}
              }
              //*/       

              if (track2->p().mag() <= 1.9 && pow(betaJ,2) < 100 && mass2J < .098*nSigPiJ+.202 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsPiPlus  = true;}
                if (track2->charge() == -1){track2_IsPiMinus = true;}
              }
              if (track2->p().mag() <= 1.9 && pow(betaJ,2) < 100 && mass2J > .092*nSigPiJ+.287 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsKaPlus  = true;}
                if (track2->charge() == -1){track2_IsKaMinus = true;}
              }
              if (track2->p().mag() > 1.9 && track2->p().mag() <= 2.3 && pow(betaJ,2) < 100 && mass2J < .139*nSigPiJ+.306 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsPiPlus  = true;}
                if (track2->charge() == -1){track2_IsPiMinus = true;}
              }
              if (track2->p().mag() > 1.9 && track2->p().mag() <= 2.3 && pow(betaJ,2) < 100 && mass2J > .135*nSigPiJ+.414 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsKaPlus  = true;}
                if (track2->charge() == -1){track2_IsKaMinus = true;}
              }
              if (track2->p().mag() > 2.3 && track2->p().mag() <= 2.7 && pow(betaJ,2) < 100 && mass2J < .231*nSigPiJ+.485 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsPiPlus  = true;}
                if (track2->charge() == -1){track2_IsPiMinus = true;}
              }
              if (track2->p().mag() > 2.3 && track2->p().mag() <= 2.7 && pow(betaJ,2) < 100 && mass2J > .230*nSigPiJ+.585 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsKaPlus  = true;}
                if (track2->charge() == -1){track2_IsKaMinus = true;}
              }
              if (track2->p().mag() > 2.7 && track2->p().mag() <= 3.1 && pow(betaJ,2) < 100 && mass2J < .324*nSigPiJ+.694 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsPiPlus  = true;}
                if (track2->charge() == -1){track2_IsPiMinus = true;}
              }
              if (track2->p().mag() > 2.7 && track2->p().mag() <= 3.1 && pow(betaJ,2) < 100 && mass2J > .322*nSigPiJ+.870 && nSigPiJ < 2.5 && mass2J < 0.5)
              {
                if (track2->charge() == 1) {track2_IsKaPlus  = true;}
                if (track2->charge() == -1){track2_IsKaMinus = true;}
              }
              
              
              							
              
              //*
							// opposite sign check
              bool haveOppoSign = false;
							bool haveSameSign = false;
              
                
                
                
              //Pion Pion
              /*
							if (track1_IsPiPlus && track2_IsPiMinus)
							{
								haveOppoSign = true;
								
								mDihadronPair->setDcaMagPlus(track1->dca(track1->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track2->dca(track2->vertexIndex()).mag());
                
								mDihadronPair->setPosNegHad("pion", track1, "pion", track2, spinBit);
							}
              
              else if (track1_IsPiMinus && track2_IsPiPlus)
							{
								haveOppoSign = true;
								
								mDihadronPair->setDcaMagPlus(track2->dca(track2->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track1->dca(track1->vertexIndex()).mag());
                
								mDihadronPair->setPosNegHad("pion", track2, "pion", track1, spinBit);
							}
              */
              
              //Kaon Kaon
              /*
              if (track1_IsKaPlus && track2_IsKaMinus)
							{
								haveOppoSign = true;
								
								mDihadronPair->setDcaMagPlus(track1->dca(track1->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track2->dca(track2->vertexIndex()).mag());
                
								mDihadronPair->setPosNegHad("kaon", track1, "kaon", track2, spinBit);
							}
              
              else if (track1_IsKaMinus && track2_IsKaPlus)
							{
								haveOppoSign = true;
								
								mDihadronPair->setDcaMagPlus(track2->dca(track2->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track1->dca(track1->vertexIndex()).mag());
                
								mDihadronPair->setPosNegHad("kaon", track2, "kaon", track1, spinBit);
							}
              */
              
              
              
              //Kaon Pion
              if (track1_IsPiPlus && track2_IsKaMinus)
              {
                haveOppoSign = true;
                
                mDihadronPair->setDcaMagPlus(track1->dca(track1->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track2->dca(track2->vertexIndex()).mag());
                mDihadronPair->setToF_M2Pos(mass2I);
                mDihadronPair->setToF_M2Neg(mass2J);

								mDihadronPair->setPosNegHad("pion", track1, "kaon", track2, spinBit);
                
              }

              if (track1_IsPiMinus && track2_IsKaPlus)
              {
                haveOppoSign = true;
                
                mDihadronPair->setDcaMagPlus(track2->dca(track2->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track1->dca(track1->vertexIndex()).mag());
                mDihadronPair->setToF_M2Pos(mass2J);
                mDihadronPair->setToF_M2Neg(mass2I);

								mDihadronPair->setPosNegHad("kaon", track2, "pion", track1, spinBit);
                
              }
              
              if (track1_IsKaPlus && track2_IsPiMinus)
              {
                haveOppoSign = true;
                
                mDihadronPair->setDcaMagPlus(track1->dca(track1->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track2->dca(track2->vertexIndex()).mag());
                mDihadronPair->setToF_M2Pos(mass2I);
                mDihadronPair->setToF_M2Neg(mass2J);

								mDihadronPair->setPosNegHad("kaon", track1, "pion", track2, spinBit);
                
              }

              if (track1_IsKaMinus && track2_IsPiPlus)
              {
                haveOppoSign = true;
                
                mDihadronPair->setDcaMagPlus(track1->dca(track1->vertexIndex()).mag());
								mDihadronPair->setDcaMagMinus(track2->dca(track2->vertexIndex()).mag());
                mDihadronPair->setToF_M2Pos(mass2J);
                mDihadronPair->setToF_M2Neg(mass2I);

								mDihadronPair->setPosNegHad("pion", track2, "kaon", track1, spinBit);
                
              }
              
              if (haveOppoSign)
							{								
								mDihadronPair->setRunInfo(muDst->event()->runInfo());
								mDihadronPair->setEventID(muDst->event()->eventId());
								mDihadronPair->setTriggerIds(triggerVal);
                
								if (mDihadronPair->withinRadius(0.05,1.5)) {mDihadronPairTree->Fill();}
                
							}
              
              
              
              
              
              
              
              
              
            }//end track2 cut
          }//same vertex check
        }//end jTrack loop
      }//end track1 cut
    }//end vertex rank check
  }//end iTrack loop
  
  return kStOK;
}







