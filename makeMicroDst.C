/*
 *  makeMicroDst.C
 *  2012IFF
 *
 *  Created by Keith Landry on 10/22/13.
 *  UCLA
 *
 */

/*
#include "StJetSkimEvent.h"
#include "StJetVertex.h"

//*/



void makeMicroDst(string jetName){

//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;

	
//SET UP JET AND SKIM INPUT FILES		
	size_t posOfFind = jetName.find("jets");
	
	string skimName = jetName;
	skimName.replace(posOfFind,4, "skim");
	
	
	TFile* jetfile  = new TFile(jetName.c_str());
	TFile* skimfile = new TFile(skimName.c_str());

	
//SET UP TREE TO RECEIVE INPUT
	StJetEvent*      jetEvent = new StJetEvent();
	StJetSkimEvent* skimEvent = new StJetSkimEvent();
	
	
	TTree* jetsTree = jetfile->Get("jet");
	jetsTree->SetBranchAddress("AntiKtR070NHits12", &jetEvent);
	
	
	TTree* skimTree = skimfile->Get("jetSkimTree");
	skimTree->SetBranchAddress("skimEventBranch", &skimEvent);
	
	
//SET UP OUTPUT FILE TO WRITE TO	
	string outName = jetName;
	
	size_t posOfDir = outName.find("sampleFiles") + 12;
	
	outName.replace(posOfDir, 8, "output");
	
	size_t posOfjets = outName.find("jets");
	
	outName.replace(posOfjets, 4, "pionPairs");
	
	TFile* outfile = new TFile(outName.c_str(),"RECREATE");
	
//SET UP TREE TO RECEIVE OUTPUT
	TTree* outTree = new TTree("pionPairTree","pionPairTree");
	
	pionPair* piPair;
	
	outTree->Branch("pionPair", "pionPair", &piPair);
	
	
	
//PRINT FILE NAMES AND TOTAL NUMBER OF EVENTS
	int nEntries    = jetsTree->GetEntries();
	int skimEntries = skimTree->GetEntries();

	cout << "\n\n";
	cout << "Jets Input File: " << jetName  << "   Total Events: " << nEntries    << endl;
	cout << "Skim Input File: " << skimName << "   Total Events: " << skimEntries << endl;
	cout << "\n";
	cout << "    output File: " << outName << endl;
	cout << "\n\n";


	
	
	//   ======================================================================
	//============================================================================
	//START ANALYSIS==============================================================
	//============================================================================
	//   ======================================================================
	
	
	 
	
	
	for (int iEntry = 0; iEntry < nEntries; iEntry++)
	{
		
		
		jetsTree->GetEntry(iEntry);
		skimTree->GetEntry(iEntry);
		
		
		//LOOP OVER VERTICIES
		for (int iVert = 0; iVert < jetEvent->numberOfVertices(); iVert++)
		{
			
			StJetVertex* vertex = jetEvent->vertex(iVert);
			
			double vertexZ = vertex->position().Z();
			
			if (fabs(vertexZ) < 60)
			{

				
				for (int iJet = 0; iJet < vertex->numberOfJets(); iJet++)
				{
					
					StJetCandidate* jet = vertex->jet(iJet);
					
					if (fabs(jet->eta()) < 1.4 && jet->pt() > 1.5)
					{
						
						
						for (int iTrack = 0; iTrack < jet->numberOfTracks(); iTrack++)
						{
							
							StJetTrack* track1 = jet->track(iTrack);
																					
							//cuts on track 1
							if (track1->pt() > 1.5 && fabs(track1->eta()) < 1.4 && track1->nHitsFit() > 15 && vertexZ*track1->eta() >= 0 && track1->nSigmaPion() < 2 && track1->nSigmaPion() > -2)
							{
								
								
								//LOOP THROUGH TRACKS AGAIN TO GET A PION PAIR
								for (int jTrack = iTrack+1; jTrack < jet->numberOfTracks(); jTrack++)
								{
									
									
									StJetTrack* track2 = jet->track(jTrack);
									
									bool passesPart2Cuts = false;
									bool part1ISPiPlus   = false;
									bool part1ISPiMinus  = false;
									bool part2ISPiPlus   = false;
									bool part2ISPiMinus  = false;
									

									//cuts on track 2
									if (track2->pt() > 1.5 && fabs(track2->eta()) < 1.4 && track2->nHitsFit() > 15 && vertexZ*track2->eta() >= 0 && track2->nSigmaPion() < 2 && track2->nSigmaPion() > -2)
									{
										//CHECK CHARGES
										if (track1->charge() == 1) {part1ISPiPlus  = true;}
										if (track2->charge() == -1){part1ISPiMinus = true;}
										if (track1->charge() == 1) {part2ISPiPlus  = true;}
										if (track2->charge() == -1){part2ISPiMinus = true;}
										
										
							
										// pi+ pi- check
										bool havePiPlusPiMinus = false;
										bool haveSamePi = false;
										
										if (part1ISPiPlus && part2ISPiMinus)
										{
											havePiPlusPiMinus = true;
											piPair->setPiPlusPiMinus(track1, track2, skimEvent);
											
										}
										if (part1ISPiMinus && part2ISPiPlus)
										{
											havePiPlusPiMinus = true;
											piPair->setPiPlusPiMinus(track2, track1, skimEvent);
										}										
										if (havePiPlusPiMinus)
										{
											outTree->Fill();
										}
										
										
										
									}//track2 cuts 
								}//2nd track loop
							}//track1 cuts
						}//1st track loop
					}//jet cuts
				}//jet loop
			}//vertex Z cut
		}//vertex loop
	}//entry loop
	

	
	outfile->Write();
	cout << "output file written" << endl;
	cout << "End--------"<<endl;

}//end