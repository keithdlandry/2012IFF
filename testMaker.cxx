/*
 *  testMaker.cxx
 *  2012IFF
 *
 *  Created by Keith Landry on 11/4/13.
 *  UCLA
 *
 */

#include "testMaker.h"

ClassImp(testMaker)


testMaker::testMaker(StMuDstMaker* muDstMaker) : StMaker()
{
	mMuDstMaker = muDstMaker;

	mfilename = "testfile.root";
	
}



Int_t testMaker::Init()
{
	hPt = new TH1D("pt","pt",50,0,5);

	mFile = new TFile(mfilename.c_str(),"RECREATE");
	
	mTree = new TTree("tree","tree");
	mTree->Branch("pionPair", "pionPair", &mPair);
	
	
	
	
	return kStOK;



}

Int_t testMaker::Finish()
{
	hPt->Draw();
	
	return kStOK;
}


Int_t testMaker::Make()
{
	StMuDst* muDst = mMuDstMaker->muDst();
	int bx48 = muDst->event()->l0Trigger().bunchCrossingId();
	int bx7 = muDst->event()->l0Trigger().bunchCrossingId7bit(muDst->event()->runId());
	//StSpinDbMaker* spDbMaker = new StSpinDbMaker("StSpinDbMaker");

	StSpinDbMaker* spDbMaker = dynamic_cast<StSpinDbMaker*>(GetMakerInheritsFrom("StSpinDbMaker"));

	
	assert(spDbMaker);

	cout << "spin info " << spDbMaker->spin8usingBX48(bx48) << endl;
	cout << "other spin " << spDbMaker->spin4usingBX7(bx7) << endl;
	
	/*
	//FIND HIGHEST RANKING VERTEX	
	double highRank = 0;
	int highRankVertIndex = 0;
	
	cout << "number of verticies " << muDst->numberOfPrimaryVertices() << endl;
	
	for (int iVert = 0; iVert < muDst->numberOfPrimaryVertices(); iVert++)
	{
		StMuPrimaryVertex* vertex = muDst->primaryVertex(iVert);
		
		if (fabs(vertex->position().z()) < 60)
		{
			double ranking = vertex->ranking();
			
			cout << "previouse high rank " << highRank << " current rank " << ranking << endl;
			
			if (ranking > highRank)
			{
				highRank = ranking;
				highRankVertIndex = iVert;
			}
		}
	}//end vertex loop
	 */
	
	
	
	return kStOK;
	
}

