/*
 *  testDCA.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/25/14.
 *  UCLA
 *
 */




void testDCA(){


	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	

	//TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/st_physics_13044126_raw_3020001.MuDst.root");


	StChain* chain = new StChain();
	StMuDstMaker* mudstMaker = new StMuDstMaker(0,0,"","/star/u/klandry/ucladisk/2012IFF/st_physics_13044126_raw_3020001.MuDst.root");
	


	for (int i = 0; i < 10; i++)
	{
	
		chain->Make(i);
		
		StMuDst* mudst = mudstMaker->muDst();
		
		if (mudst->numberOfPrimaryTracks() != 0)
		{
			StMuTrack* track = mudst->primaryTracks(0);
			
			cout << track->dca(track->vertexIndex()).mag() << endl;
			

		}
		

	
	
	
	}
	
	
	
	
}
































