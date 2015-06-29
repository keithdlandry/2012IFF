/*
 *  makeSameSignTrees.C
 *  2012IFF
 *
 *  Created by Keith Landry on 3/28/14.
 *  UCLA
 *
 */


void makeSameSignTrees(string fileList, string jobID){
	
  bool makePairs = true;
	bool makeTrackQA = false;
	
	
	//LOAD LIBRARIES
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	if (makePairs)
	{
	  gSystem->Load("sameSignPair");
	  cout << " loading of sameSignPair library done" << endl;
	  gSystem->Load("sameSignPairTreeMaker");
	  cout << " loading of sameSignPairTreeMaker library done" << endl;
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
		sameSignPairTreeMaker* sameSignPiTreeMaker = new sameSignPairTreeMaker(muDstMaker);
		string outFileName;
		outFileName  = "r";
		outFileName += runNumber;
		outFileName += "_";
		outFileName += jobID;
		outFileName += "_SameSignPionTree.root";
		
		sameSignPiTreeMaker->setOutputFile(outFileName.c_str());
    cout << "sameSignPairTree file name: " << outFileName << endl;	
	}
	
	//trackQAmaker
	if (makeTrackQA)
	{
		trackQAmaker* trkQAmaker = new trackQAmaker(muDstMaker);
		string trackOutFileName;
		trackOutFileName  = "TESTr";
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
		//if (iEvent >= 10000){break;}
		
	}//end while
	//*/
	
	
	chain->Finish();
	
	
	delete chain;
	
	
	
}