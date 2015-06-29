/*
 *  makeKaKaTrees.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/27/15.
 *  UCLA
 *
 */



/*
 #include "StJetSkimEventMaker.h"
 #include "StMuDstMaker.h"
 #include "StChain.h"
 #include "StMuEvent.h"
 #include "StMuDst.h"
 #include "StMuPrimaryVertex.h"
 #include "StMuTrack.h"
 #include "StSpinDbMaker.h"
 #include "St_db_Maker.h"
 #include "pionPairTreeMaker.h"
 #include "pionPairTreeMaker.h"
 #include "StTriggerFilterMaker.h"
 #include "StTriggerSimuMaker.h"
 #include "StEmcADCtoEMaker.h"
 #include "dihadronPair.h"
 #include "dihadronPairTreeMaker.h"
 
 //*/
/*make picoDst files containing pion piars from MuDst files
 */

void makeKaKaTrees(string fileList, string jobID){
  
  bool makePairs = true;
	bool makeTrackQA = false;
	
  //cout << "im a test" << endl;
	
  //LOAD LIBRARIES
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	if (makePairs)
	{
	  gSystem->Load("dihadronPair");
	  cout << " loading of dihadronPair library done" << endl;
	  gSystem->Load("dihadronPairTreeMaker");
	  cout << " loading of dihadronPairTreeMaker library done" << endl;
	}
	if (makeTrackQA)
	{
	  gSystem->Load("trackQAmaker");
	  cout << " loading of trackQAmaker library done" << endl;
	}
	
	cout << "\n";
	cout << "\n";
  
	
  //CHAIN OF MAKERS
  StChain* chain = new StChain; 
	
  //MUDST READER
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");
  
	chain->Make(0);
	StMuEvent* MuEvent = muDstMaker->muDst()->event();
	int runID = MuEvent->runId();
  
	stringstream ss;
	ss << runID;
	string runNumber = ss.str();
	
  
  //StarDbMaker
	St_db_Maker* dbMaker = new St_db_Maker("db", "MySQL:StarDb", "$STAR/StarDb");
  
  //SPINDBMAKER
	StSpinDbMaker* spinDbMaker = new StSpinDbMaker("StSpinDbMaker");
	
	cout << "\n";
	
  //pionPairTreemaker
	if (makePairs)
	{
    dihadronPairTreeMaker* kkTreemaker = new dihadronPairTreeMaker(muDstMaker);
		string outFileName;
		outFileName  = "run";
		outFileName += runNumber;
		outFileName += "_";
		outFileName += jobID;
		outFileName += "_dihadronTree_testkk.root";
		
		kkTreemaker->setOutputFile(outFileName.c_str());
    cout << "KaKaTree file name: " << outFileName << endl;	

    kkTreemaker->deselectAllPairs();
    //kkTreemaker->makeKaPiPairs();
	}
	
  //trackQAmaker
	if (makeTrackQA)
	{
		trackQAmaker* trkQAmaker = new trackQAmaker(muDstMaker);
		string trackOutFileName;
		trackOutFileName  = "run";
		trackOutFileName += runNumber;
		trackOutFileName += "_";
		trackOutFileName += jobID;
		trackOutFileName += "_trackQA.root";
		
		trkQAmaker->setOutputFile(trackOutFileName.c_str());
		cout << "track QA file name: " << trackOutFileName << endl;
	}
  
	
	int iEvent = 0;
	
	cout << "\n";
	cout << "\n";
	cout << "Init() ......." << endl;
	cout << "\n";
	cout << "\n";
  
	chain->Init();
  
	cout << "\n";
	cout << "\n";
	cout << "Make() ......." << endl;
	cout << "\n";
	cout << "\n";
	
	//int nEvents = 2;
	//chain->EventLoop(nEvents);
  
	//*
	while (chain->Make(iEvent) == kStOK)
	{
		iEvent++;
	  if (iEvent%100000 == 0) {cout << "processing event number " << iEvent << endl;}
		//if (iEvent >= 10){break;}
		
	}//end while
	//*/
	
  //*
	chain->Finish();
	
	
	delete chain;
	
	
  
  
}


