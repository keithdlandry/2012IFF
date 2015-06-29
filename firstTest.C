/*
 *  firstTest.C
 *  2012IFF
 *
 *  Created by Keith Landry on 9/30/13.
 *  UCLA
 *
 */
/*
#include "TFile.h"
#include "TTree.h"
#include "StJetEvent.h"
#include "StJetCandidate.h"
#include "StJet.h"
#include "StJetParticle.h"
#include "TH1D.h"
#include "StJetTrack.h"
 */

 void firstTest(){
	
	gROOT->Macro("StRoot/LoadLibs.C");
	
	TFile* infile = new TFile("sampleFiles/13068057/st_physics_13068057_raw_2020002.jets.root");
	
	StJetEvent* jetEvent = new StJetEvent();

	TTree* inputTree = infile->Get("jet");
	inputTree->SetBranchAddress("AntiKtR070NHits12", &jetEvent);
	
	
	 
	for (int iEntry=0; iEntry<10; iEntry++)
	{
		
		
		
		inputTree->GetEntry(iEntry);
		
		for (int iJet = 0; iJet < jetEvent->numberOfJets(); iJet++)
		{
			StJetCandidate* jet = jetEvent->jet(iJet);
			
			for (int iTrack = 0; iTrack < jet->numberOfTracks(); iTrack++)
			{
				StJetTrack* track = jet->track(iTrack);
				
				
				cout << track->phi() << endl;
				
				
				
				
			}
			
			
		}
		
		
		
		
		

		
		
		
	}
	

	
	
	
	
	
	
	
	
	
	
}



