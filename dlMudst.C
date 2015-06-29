/*
 *  dlMudst.C
 *  2012IFF
 *
 *  Created by Keith Landry on 9/15/14.
 *  UCLA
 *
 */

//#include "StMuBTofHit.h"

//#include "StTofHit.h"
//#include "StTofMuDstReader.h"

void dlMudst(/*string fileList*/){

	string fileList = "./xml/schedB57622DD24C1A0ECDF3F996978585EA7_4.list";
//	string fileList = "./xml/testlist.list";

	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load("StarMagField");
  gSystem->Load("StMagF");
  gSystem->Load("StTpcDb");
	//  gSystem->Load("StDbUtilities");
  gSystem->Load("StDaqLib");
  gSystem->Load("StDbBroker");
  gSystem->Load("StDetectorDbMaker");
  gSystem->Load("StDbUtilities");
  gSystem->Load("St_db_Maker");
	
  gSystem->Load("StEvent");
  gSystem->Load("StEventMaker");
  gSystem->Load("StarMagField");
  gSystem->Load("StTofUtil");   
  gSystem->Load("StTofMaker");  
	
  //gSystem->Load("libtpc_Tables");
  gSystem->Load("libGeom");
  gSystem->Load("St_g2t"); 
  gSystem->Load("geometry");
  gSystem->Load("St_geant_Maker");
	
  gSystem->Load("StTofMuDstReader");
	
	TFile* outfile = new TFile("/star/u/klandry/ucladisk/2012IFF/2012Mudstshort.root","Recreate");

	char* outputname = "testout.root";
	
	StChain* muChain = new StChain();

  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");
  muDstMaker->SetStatus("BTofHeader",1) ;      // Turn on the global track data
	muDstMaker->SetStatus("TofRawData",1);
	muDstMaker->SetStatus("TofData",1);
	muDstMaker->SetStatus("TofHit",1);
	
	//StTofMuDstReader *tofMaker = new StTofMuDstReader("tofMaker",outputname,muDstMaker);

  StMuDst* muDst;
		
	TTree* tree = new TTree("mudst","mudst");
	
	tree->Branch("muDst", &muDst);
	
	
	TH1D* hSigmaPiontof = new TH1D("tofsigmapion","tofsigmapion",100,-10,10);
	TH1D* hSigmaPiontpc = new TH1D("tpcsigmapion","tpcsigmapion",100,-10,10);


	
	int iEvent = 0;
	
	while (muChain->Make(iEvent) == kStOK)
	{
		muDst = muDstMaker->muDst();
		cout << "number of TOF Hits " << muDst->numberOfTofHit() << endl;
		
		for (int iHit=0; iHit<muDst->numberOfTofHit(); iHit++)
		{
			
			StMuTofHit *tof = (StMuTofHit*)muDst->tofHit(iHit);
			//StMuBTofHit* bTofHit = muDst->btofHit(iHit);
			
			if (!muDst->tofHit(iHit))
			{
				cout << "jdflksfjldsfjlsdjf" << endl;
			}
					
			//hSigmaPiontof->Fill(tofHit->sigmaPion());
	
			//cout << "tofFilled" << endl;
			
		}
	
		
		for (int iTrack=0; iTrack<muDst->numberOfPrimaryTracks(); iTrack++)
		{
			
			StMuTrack* track = muDst->primaryTracks(iTrack);
			
			hSigmaPiontpc->Fill(track->nSigmaPion());
			
			//cout << "tpcFilled" << endl;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		//cout << muDstMaker->muDst()->event()->runId() << endl;
		//cout << muDst->event()->runId() << endl;
		
		tree->Fill();

	
		iEvent++;
		
		if (iEvent%1000 == 0)
		{
			cout << iEvent << endl;
			//cout << muDst->event->runId() << endl;
		}
		
		
		if (iEvent == 1000){break;}
		
	}
	
	
	tree->Write();
	hSigmaPiontof->Write();
	hSigmaPiontpc->Write();
	
	outfile->Write();
		
}