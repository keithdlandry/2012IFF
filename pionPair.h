/*
 *  pionPair.h
 *  IFF
 *
 *  Created by Keith Landry on 8/16/13.
 *  UCLA
 *
 */

#ifndef PIONPAIR_H
#define PIONPAIR_H


#include "TObject.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "StEvent/StTriggerId.h"


class pionPair : public TObject {
	
public:
	
	pionPair();
	pionPair(StMuTrack* positivePion, StMuTrack* negativePion, int spinB);
	~pionPair();
	
	
	//GET PARTICLES
	StMuTrack* piPlus()  {return mPiPlus;}
	StMuTrack* piMinus() {return mPiMinus;}
	
	TLorentzVector piPlusLV()  {return mPiPlusLV;}
	TLorentzVector piMinusLV() {return mPiMinusLV;}
	
	//GET EVENT VARIABLES
	int         spinBit()    {return mSpinBit;}       //5:dd 6:du 9:ud 10:uu
	StTriggerId triggerIds() {return mTriggerIds;}	
	StRunInfo   runInfo()    {return mRunInfo;}
	int         eventID()    {return mEventID;}
	double      dcaMagPlus() {return mDcaMagPlus;}
	double      dcaMagMinus(){return mDcaMagMinus;} 
	
	//COMPUTERS
	double invarientMass();
	double theta();
	
	double cosPhiS(char beamToTreatPol);
	double cosPhiR(char beamToTreatPol);
	double sinPhiS(char beamToTreatPol);
	double sinPhiR(char beamToTreatPol);
	double sinPhiSR(char beamToTreatPol);   //sin(PhiS-PhiR)
	double cosPhiSR(char beamToTreatPol);   //cos(PhiS-PhiR)
	double phiR(char beamToTreatPol);
	double phiS(char beamToTreatPol);
	double phiSR(char beamToTreatPol);
	
	bool   withinRadius(double minRadius, double maxRadius);
	
	
	//SETTERS
	void setPiPlus(StMuTrack* piP)  {mPiPlus = piP;}
	void setPiMinus(StMuTrack* piM) {mPiMinus = piM;}
  void setPiPlusPiMinus(StMuTrack* plus, StMuTrack* minus, int spinB);
	
	
	void setSpinBit(int spinB);     
	
	void setRunInfo(StRunInfo runInfo) {mRunInfo = runInfo;}
	void setEventID(int eventId) {mEventID = eventId;}
	void setDcaMagPlus(double dca) {mDcaMagPlus = dca;}
	void setDcaMagMinus(double dca) {mDcaMagMinus = dca;}
	
	void setTriggerIds(StTriggerId trigIds) {mTriggerIds = trigIds;}
	
	
	
private:
	
	StMuTrack* mPiPlus;
	StMuTrack* mPiMinus;
	StRunInfo mRunInfo;
	
	int mEventID;
	
	int mSpinBit;
	
	TVector3 mPh;
	TVector3 mRh;
	
	TVector3 mSpinYellow;
	TVector3 mSpinBlue;
	TVector3 mPa;
	TVector3 mPb;
	
	TLorentzVector mPiPlusLV;
	TLorentzVector mPiMinusLV;
	
	StTriggerId mTriggerIds;	
	
	double mDcaMagPlus;
	double mDcaMagMinus;
	
	
	
	ClassDef(pionPair,2);
};


//inline const StRunInfo& StChargedPionEvent::runInfo() const { return mRunInfo; }
//inline void StChargedPionEvent::setRunInfo(const StRunInfo& a) { mRunInfo = a; }


#endif