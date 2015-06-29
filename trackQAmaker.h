/*
 *  trackQAmaker.h
 *  2012IFF
 *
 *  Created by Keith Landry on 3/7/14.
 *  UCLA
 *
 */



#ifndef TRACKQAMAKER_H
#define TRACKQAMAKER_H

//root
#include "TTree.h"
#include "TFile.h"


#include "StMaker.h"

//StMuDstMaker
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"


//Trigger
#include "StMuDSTMaker/COMMON/StMuTriggerIdCollection.h"
#include "StEvent/StTriggerId.h"

#include <string>



class trackQAmaker : public StMaker
{

	
	
private:
	
	StMuDstMaker* mMuDstMaker;
	TFile* mOutputFile;
	string mOutFileName;
	
	TH1D* mH_Pt;
	TH1D* mH_VertexZ;
	TH1D* mH_Eta;
	TH1D* mH_nSigmaPion;
	TH1D* mH_nHitsFit;
	
	TH1D* mH_Pt_cut;
	TH1D* mH_VertexZ_cut;
	TH1D* mH_Eta_cut;
	TH1D* mH_nSigmaPion_cut;
	TH1D* mH_nHitsFit_cut;

	TH1D* mH_Pt_trig;
	TH1D* mH_VertexZ_trig;
	TH1D* mH_Eta_trig;
	TH1D* mH_nSigmaPion_trig;
	TH1D* mH_nHitsFit_trig;
	
	
	TH1I* mH_Events_total;
	TH1I* mH_JP0;
	TH1I* mH_JP1;
	TH1I* mH_JP2;
	TH1I* mH_AJP;
	TH1I* mH_BHT0VPDmb;
	TH1I* mH_BHT1VPDmb;
	TH1I* mH_BHT2BBCmb;
	TH1I* mH_BHT2;

	
	
	
public:
	
	trackQAmaker(StMuDstMaker* muDstMaker);
	
	Int_t Init();
	Int_t Make();
	Int_t Finish();
	
	
	void setOutputFile(string outputName) {mOutFileName = outputName;}
	
	
	
	
	
	
	ClassDef(trackQAmaker,1);

	
};

#endif