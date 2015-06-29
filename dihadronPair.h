/*
 *  dihadronPair.h
 *  2012IFF
 *
 *  Created by Keith Landry on 8/27/14.
 *  UCLA
 *
 */

#ifndef DIHADRONPAIR_H
#define DIHADRONPAIR_H


#include "TObject.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "StEvent/StTriggerId.h"


class dihadronPair : public TObject {
	
public:
	
	dihadronPair();
	dihadronPair(string posName, StMuTrack* posHadron, string negName, StMuTrack* negHadron, int spinB);
	~dihadronPair();
	
	
	//GET PARTICLES
	StMuTrack* posHad()  {return mPosHadron;}
	StMuTrack* negHad() {return mNegHadron;}
	
	TLorentzVector posHadLV()  {return mPosHadLV;}
	TLorentzVector negHadLV() {return mNegHadLV;}
	
	//GET EVENT VARIABLES
	int         spinBit()    {return mSpinBit;}       //spinbit#:YB 5:dd 6:du 9:ud 10:uu 
	StTriggerId triggerIds() {return mTriggerIds;}	
	StRunInfo   runInfo()    {return mRunInfo;}
	int         eventID()    {return mEventID;}
	double      dcaMagPlus() {return mDcaMagPlus;}
	double      dcaMagMinus(){return mDcaMagMinus;} 
  double      tof_m2Pos()  {return mToF_M2Pos;}
  double      tof_m2Neg()  {return mToF_M2Neg;}
  string      posTrackName()    {return mPosName;}
  string      negTrackName()    {return mNegName;}
	
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
	void setPosHad(StMuTrack* posH)  {mPosHadron = posH;}
	void setNegHad(StMuTrack* negH) {mNegHadron = negH;}
  void setPosNegHad(string posName, StMuTrack* plus, string negName, StMuTrack* minus, int spinB);
	
	
	void setSpinBit(int spinB);     
	
	void setRunInfo(StRunInfo runInfo) {mRunInfo = runInfo;}
	void setEventID(int eventId) {mEventID = eventId;}
	void setDcaMagPlus(double dca) {mDcaMagPlus = dca;}
	void setDcaMagMinus(double dca) {mDcaMagMinus = dca;}
	
	void setTriggerIds(StTriggerId trigIds) {mTriggerIds = trigIds;}
	
  void setPosHadID(string posName) {mPosName = posName;}
  void setNegHadID(string negName) {mPosName = negName;}
	
	void setToF_M2Pos(double m2) {mToF_M2Pos = m2;}
  void setToF_M2Neg(double m2) {mToF_M2Neg = m2;}

private:
	
	StMuTrack* mPosHadron;
	StMuTrack* mNegHadron;
	StRunInfo mRunInfo;
	
	int mEventID;
	
	int mSpinBit;
	
	TVector3 mPh;
	TVector3 mRh;
	
	TVector3 mSpinYellow;
	TVector3 mSpinBlue;
	TVector3 mPa;
	TVector3 mPb;
	
	TLorentzVector mPosHadLV;
	TLorentzVector mNegHadLV;
	
	StTriggerId mTriggerIds;	
	
	
	string mPosName;
	string mNegName;
	
	double mDcaMagPlus;
	double mDcaMagMinus;
  
	double mToF_M2Pos;
	double mToF_M2Neg;
	
	
	ClassDef(dihadronPair,2);
};


//inline const StRunInfo& StChargedPionEvent::runInfo() const { return mRunInfo; }
//inline void StChargedPionEvent::setRunInfo(const StRunInfo& a) { mRunInfo = a; }


#endif