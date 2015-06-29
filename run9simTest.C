/*
 *  run9simTest.C
 *  2012IFF
 *
 *  Created by Keith Landry on 10/27/14.
 *  UCLA
 *
 */
//#include "St_pythia_maker.h"
//#include "StPythiaEvent.h"
void run9simTest(){
	

	//copied over to RCF
	string mudstfilename  = "/star/u/klandry/ucladisk/2012IFF/run9sim/pt9_11_10165049_1.MuDst.root";
	string pythiafilename = "/star/u/klandry/ucladisk/2012IFF/run9sim/pt9_11_10165049_1.pythia.root";
	
	TFile* pythiafile = new TFile(pythiafilename.c_str());
	
	//on pdsf
	//string mudstfile  = "/eliza14/star/starprod/embedding/production2009_200GeV/Jet_pp200_2009/SL11d_embed/10170053/pt2_3_10170053_7.MuDst.root";
	//string pythiafile = "/eliza14/star/starprod/embedding/production2009_200GeV/Jet_pp200_2009/SL11d_embed/10170053/pt2_3_10170053_7.pythia.root";
	
	

  gROOT->Macro("loadMuDst.C");
  gROOT->Macro("LoadLogger.C");
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");

	gSystem->Load("StEEmcA2EMaker");
	
	 
	 
	// Create chain
  StChain* chain = new StChain;
	
  // Instantiate MuDst maker
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",mudstfilename.c_str(),".",1000,"MuDst");
  StMuDbReader* muDB = StMuDbReader::instance();
	
  // star database
  St_db_Maker* starDb = new St_db_Maker("StarDb","MySQL:StarDb");
	
  // Endcap database
  StEEmcDbMaker* eemcDb = new StEEmcDbMaker;
	
  // Spin database
  StSpinDbMaker* spinDb = new StSpinDbMaker;
	
  // Barrel ADC to energy maker
  StEmcADCtoEMaker* adc = new StEmcADCtoEMaker;
  adc->saveAllStEvent(true);
	
  // Trigger simulator
  StTriggerSimuMaker* simuTrig = new StTriggerSimuMaker;
  simuTrig->useOnlineDB();
  //  simuTrig->setMC(false); // Must be before individual detectors, to be passed
  simuTrig->setMC(2); // Must be before individual detectors, to be passed
  // BBC was not used in Run 9
  //simuTrig->useBbc();
  simuTrig->useBemc();
  simuTrig->useEemc();
  simuTrig->bemc->setConfig(StBemcTriggerSimu::kOnline);
	//*/
  StEEmcA2EMaker *a2EMakerPtr = new StEEmcA2EMaker("EEmcA2EMaker");
  a2EMakerPtr->database("eemcDb");          // sets db connection
  a2EMakerPtr->source("MuDst",1);           // sets mudst as input
	
  // Instantiate your makers here
  //StAnalysisMaker* maker = new StAnalysisMaker;
  //  fms->SetPrintLevel(0);
	// maker->SetFile(ofile);
	
	
	
	//FOR READING PYTHIA FILE
	//TChain* pythiaChain->Add(pythiafile);
	

	TTree* pythiaTree = pythiafile->Get("PythiaTree");
	
	
	StPythiaEvent* pythiaEvent = new StPythiaEvent();
	
	//pythiaChain->SetBranchAddress("pythiaBranch", &pythiaEvent);	
	
	
	pythiaTree->SetBranchAddress("PythiaBranch", &pythiaEvent);
	
	
	
	
	
	
	for (int i=0; i<3; i++)
	{
		pythiaTree->GetEvent(i);
		
		cout << pythiaEvent->numberOfParticles() << endl;
		
	}
	
	
	/*
	
	
  // Initialize chain
  chain->Init();
	
	
	
	
  // Event loop
	int nevents = 10;
  cout << "Prepare to process " << nevents << " events.\n";
	
	
	
	for (int iEvent = 1; iEvent <= nevents; ++iEvent) {
    
		if (iEvent%1000==1) cout << "iEvent = " << iEvent << "\n";
    
		chain->Clear();
    
		int status = chain->Make(iEvent);
		
		cout << iEvent << endl;
		
		vector<unsigned int> triggerIds = StMuDst::event()->triggerIdCollection().nominal().triggerIds();
    printf("TRIGGERS = ");
    for (int i = 0; i < triggerIds.size(); ++i){printf("%d ",triggerIds[i]);}
    printf("\n");
		
		
		vector<int> trigvect = simuTrig->triggerIds();
		
		cout << "trigvect size = " << trigvect.size() << endl;
		
		for (int j = 0; j<trigvect.size(); j++)
		{
			cout << trigvect[j] << endl;
		}
		
		
		
		
		
		/*
		for (int k=0; k<18; k++)
		{
			if (simuTrig->isTrigger(trigIdList[k]))
			{
				cout << "trigger " << trigIdList[k] << " fired" << endl;
			}
		}		
		
		 */
		
		

		
		
		
		
		
		
		
	/*	
    if (status % 10 == kStEOF || status % 10 == kStFatal) break;
  }
	
	
	
	*/
	
	
	
}
