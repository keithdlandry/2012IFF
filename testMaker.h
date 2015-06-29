/*
 *  testMaker.h
 *  2012IFF
 *
 *  Created by Keith Landry on 11/4/13.
 *  UCLA
 *
 */



#ifndef TESTMAKER_H
#define TESTMAKER_H

#include "TH1D.h"
#include "StMaker.h"
#include "TTree.h"
#include "TFile.h"
//StMuDstMaker
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
//StSpinDb
#include "StSpinPool/StSpinDbMaker/StSpinDbMaker.h"

#include "pionPair/pionPair.h"

class testMaker : public StMaker
{
	
private:
	StMuDstMaker*  mMuDstMaker;
	TH1D*          hPt;
	StSpinDbMaker* mSpinDbMaker;
	TTree*         mTree;
	pionPair*      mPair;
	TFile*         mFile;
	
	string mfilename;
	
	
public:
	testMaker(StMuDstMaker* muDstMaker);
	
	Int_t Init();
	Int_t Make();
	Int_t Finish();
	
	ClassDef(testMaker,1);
	
};

#endif