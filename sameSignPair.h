/*
 *  sameSignPair.h
 *  2012IFF
 *
 *  Created by Keith Landry on 3/28/14.
 *  UCLA
 *
 */



#ifndef SAMESIGNPAIR_H
#define SAMESIGNPAIR_H


#include "TObject.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "StEvent/StTriggerId.h"


class sameSignPair : public TObject {
	
public:
	
	sameSignPair();
	sameSignPair(StMuTrack* pion1, StMuTrack* pion2, int spinB);
	~sameSignPair();
	
	
	//GET PARTICLES
	StMuTrack* getPion1()  {return mPion1;}
	StMuTrack* getPion2() {return mPion2;}
	
	TLorentzVector pion1LV()  {return mPion1LV;}
	TLorentzVector pion2LV() {return mPion2LV;}
	
	//GET EVENT VARIABLES
	int         spinBit()    {return mSpinBit;}       //5:dd 6:du 9:ud 10:uu
	StTriggerId triggerIds() {return mTriggerIds;}	
	StRunInfo   runInfo()    {return mRunInfo;}
	int         eventID()    {return mEventID;}
	
	
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
	void setPion1(StMuTrack* pi1)  {mPion1 = pi1;}
	void setPion2(StMuTrack* pi2) {mPion2 = pi2;}
  void setBothPions(StMuTrack* pion1, StMuTrack* pion2, int spinB);
	
	
	void setSpinBit(int spinB);     
	
	void setRunInfo(StRunInfo runInfo) {mRunInfo = runInfo;}
	void setEventID(int eventId)       {mEventID = eventId;}
	
	void setTriggerIds(StTriggerId trigIds) {mTriggerIds = trigIds;}
	
	
	
private:
	
	StMuTrack* mPion1;
	StMuTrack* mPion2;
	StRunInfo mRunInfo;
	
	int	mEventID;
	
	int mSpinBit;
	
	TVector3 mPh;
	TVector3 mRh;
	
	TVector3 mSpinYellow;
	TVector3 mSpinBlue;
	TVector3 mPa;
	TVector3 mPb;
	
	TLorentzVector mPion1LV;
	TLorentzVector mPion2LV;
	
	StTriggerId mTriggerIds;	
	
	
	
	
	ClassDef(sameSignPair,2);
};


//inline const StRunInfo& StChargedPionEvent::runInfo() const { return mRunInfo; }
//inline void StChargedPionEvent::setRunInfo(const StRunInfo& a) { mRunInfo = a; }


#endif