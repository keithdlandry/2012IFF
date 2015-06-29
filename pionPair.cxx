/*
 *  pionPair.cxx
 *  IFF
 *
 *  Created by Keith Landry on 8/16/13.
 *  UCLA
 *
 */

#include "pionPair.h"



ClassImp(pionPair)
//______________________________________________________________________________
pionPair::pionPair(){
	
}
//______________________________________________________________________________
pionPair::pionPair(StMuTrack* positivePion, StMuTrack* negativePion, int spinB){
	
	mPiPlus  = positivePion;
	mPiMinus = negativePion;
	
	
	mPiPlusLV.SetPtEtaPhiM(mPiPlus->pt(), mPiPlus->eta(), mPiPlus->phi(), 0.13957);
	mPiMinusLV.SetPtEtaPhiM(mPiMinus->pt(), mPiMinus->eta(), mPiMinus->phi(), 0.13957);

	
	
	mPh = mPiPlusLV.Vect() + mPiMinusLV.Vect();
	mRh = (mPiPlusLV.Vect() - mPiMinusLV.Vect())*0.5;
	
	
	this->setSpinBit(spinB);
	
	
}
//______________________________________________________________________________
pionPair::~pionPair(){
	
}
//SETTERS-----------------------------------------------------------------------
//______________________________________________________________________________
void pionPair::setPiPlusPiMinus(StMuTrack* plus, StMuTrack* minus, int spinB){
	
	mPiPlus  = plus;
	mPiMinus = minus;
	
	
	mPiPlusLV.SetPtEtaPhiM(mPiPlus->pt(), mPiPlus->eta(), mPiPlus->phi(), 0.13957);
	mPiMinusLV.SetPtEtaPhiM(mPiMinus->pt(), mPiMinus->eta(), mPiMinus->phi(), 0.13957);
	
	
	mPh = mPiPlusLV.Vect() + mPiMinusLV.Vect();
	mRh = (mPiPlusLV.Vect() - mPiMinusLV.Vect())*0.5;
	
		
	this->setSpinBit(spinB);
	
}
//______________________________________________________________________________
void pionPair::setSpinBit(int spinB){
	
	mSpinBit = spinB;
	
	bool yellowUp   = false;
	bool yellowDown = false;
	bool blueUp     = false;
	bool blueDown   = false;
	
	if (spinB == 5)
	{
		blueDown   = true;
		yellowDown = true;
	}
	else if (spinB == 6)
	{
		blueDown = true;
		yellowUp = true;
	}
	else if (spinB == 9)
	{
		blueUp     = true;
		yellowDown = true;
	}
	else if (spinB == 10)
	{
		blueUp   = true;
		yellowUp = true;
	}
	
	if (yellowUp){mSpinYellow.SetXYZ(0, 1, 0);}
	if (yellowDown){mSpinYellow.SetXYZ(0, -1, 0);}
	if (blueUp){mSpinBlue.SetXYZ(0, 1, 0);}
	if (blueDown){mSpinBlue.SetXYZ(0, -1, 0);}
	
	
}	
//COMPUTERS---------------------------------------------------------------------
//______________________________________________________________________________
double pionPair::invarientMass(){
	
	TLorentzVector sum = mPiPlusLV + mPiMinusLV;
	double invarMass = sum.M();
	
	return invarMass;
}
//______________________________________________________________________________
bool pionPair::withinRadius(double minR, double maxR){
	
	double radius = sqrt( pow(mPiPlus->eta() - mPiMinus->eta(), 2) + pow(mPiPlus->phi() - mPiMinus->phi(), 2) );
	
	if (radius >= minR && radius <= maxR) {return true;}
	else {return false;}
	
}
//______________________________________________________________________________
double pionPair::theta(){
	
	TLorentzVector sum = mPiPlusLV + mPiMinusLV;
	TLorentzVector lorentzVect = mPiPlusLV;
	
	lorentzVect.Boost(-sum.BoostVector());
	
	double Theta = lorentzVect.Vect().Angle(mPh);
	
	return Theta;
}
//______________________________________________________________________________
double pionPair::cosPhiS(char beamToTreatPol){
	
	TVector3 spinVec;
	
	if (beamToTreatPol == 'y' || beamToTreatPol == 'Y')
	{
		mPb.SetXYZ(0, 0, -1); //Pb (polarized beam) is yellow
		mPa.SetXYZ(0, 0, 1);  //blue beam is unpolarized beam
		
		spinVec = mSpinYellow;
	}
	if (beamToTreatPol == 'b' || beamToTreatPol == 'B')
	{
		mPb.SetXYZ(0, 0, 1);
		mPa.SetXYZ(0, 0, -1);
		
	  spinVec = mSpinBlue;
	}
	spinVec.SetXYZ(0, 1, 0); //spin vector always taken to be in the pos y directon

	double cosPhi_S = mPb.Unit().Cross(mPh).Unit() * mPb.Unit().Cross(spinVec).Unit();      //From equation 7 in arXiv:hep-ph/0412141v1
	
	return cosPhi_S;
}
//______________________________________________________________________________
double pionPair::cosPhiR(char beamToTreatPol){
	
	TVector3 spinVec;
	
	if (beamToTreatPol == 'y' || beamToTreatPol == 'Y')
	{
		mPb.SetXYZ(0, 0, -1); //Pb (polarized beam) is yellow
		mPa.SetXYZ(0, 0, 1);  //blue beam is unpolarized beam
		
		spinVec = mSpinYellow;
	}
	if (beamToTreatPol == 'b' || beamToTreatPol == 'B')
	{
		mPb.SetXYZ(0, 0, 1);
		mPa.SetXYZ(0, 0, -1);
		
	  spinVec = mSpinBlue;
	}
	spinVec.SetXYZ(0, 1, 0);
	
	double cosPhi_R = mPh.Unit().Cross(mPa).Unit() * mPh.Unit().Cross(mRh).Unit();
	
	return cosPhi_R;
}
//______________________________________________________________________________
double pionPair::sinPhiS(char beamToTreatPol){
	
	TVector3 spinVec;
	
	if (beamToTreatPol == 'y' || beamToTreatPol == 'Y')
	{
		mPb.SetXYZ(0, 0, -1); //Pb (polarized beam) is yellow
		mPa.SetXYZ(0, 0, 1);  //blue beam is unpolarized beam
		
		//spinVec = mSpinYellow;
		spinVec.SetXYZ(0, 1, 0);
	}
	if (beamToTreatPol == 'b' || beamToTreatPol == 'B')
	{
		mPb.SetXYZ(0, 0, 1);
		mPa.SetXYZ(0, 0, -1);
		
	  spinVec = mSpinBlue;
	}
	spinVec.SetXYZ(0, 1, 0);
	double sinPhi_S = mPh.Cross(spinVec) * mPb.Unit() / (mPb.Unit().Cross(mPh).Mag() * mPb.Unit().Cross(spinVec).Mag());
	
	return sinPhi_S;
}
//______________________________________________________________________________
double pionPair::sinPhiR(char beamToTreatPol){
	
	TVector3 spinVec;
	
	if (beamToTreatPol == 'y' || beamToTreatPol == 'Y')
	{
		mPb.SetXYZ(0, 0, -1); //Pb (polarized beam) is yellow
		mPa.SetXYZ(0, 0, 1);  //blue beam is unpolarized beam
		
		spinVec = mSpinYellow;
	}
	if (beamToTreatPol == 'b' || beamToTreatPol == 'B')
	{
		mPb.SetXYZ(0, 0, 1);
		mPa.SetXYZ(0, 0, -1);
		
	  spinVec = mSpinBlue;
	}
	
	spinVec.SetXYZ(0, 1, 0);
	double sinPhi_R = mPa.Cross(mRh) * mPh.Unit() / (mPh.Unit().Cross(mPa).Mag() * mPh.Unit().Cross(mRh).Mag());
	
	return sinPhi_R;
}
//______________________________________________________________________________
double pionPair::sinPhiSR(char beamToTreatPol){
	
	double sinPhi_S_R = this->sinPhiS(beamToTreatPol)*this->cosPhiR(beamToTreatPol) - this->cosPhiS(beamToTreatPol)*this->sinPhiR(beamToTreatPol);
	
	return sinPhi_S_R;
}
//______________________________________________________________________________
double pionPair::cosPhiSR(char beamToTreatPol){
	
	double cosPhi_S_R = this->cosPhiS(beamToTreatPol)*this->cosPhiR(beamToTreatPol) + this->sinPhiS(beamToTreatPol)*this->sinPhiR(beamToTreatPol);
	
	return cosPhi_S_R;	
}
//______________________________________________________________________________
double pionPair::phiR(char beamToTreatPol){
	
	double phi_R;
	
	if (this->sinPhiR(beamToTreatPol) >= 0)
	{
		phi_R = acos(this->cosPhiR(beamToTreatPol));
	}
	if (this->sinPhiR(beamToTreatPol) < 0)
	{
		phi_R = -acos(this->cosPhiR(beamToTreatPol));
	}
	
	
	return phi_R;	
}
//______________________________________________________________________________
double pionPair::phiS(char beamToTreatPol){
	
	double phi_S;
	
	if (this->sinPhiS(beamToTreatPol) >= 0)
	{
		phi_S = acos(this->cosPhiS(beamToTreatPol));
	}
	if (this->sinPhiS(beamToTreatPol) < 0)
	{
		phi_S = -acos(this->cosPhiS(beamToTreatPol));
	}
	
	return phi_S;
	
}
//______________________________________________________________________________
double pionPair::phiSR(char beamToTreatPol){
	
	double pi = 3.14159265359;
	
	double phi_S_R;
	
	if (this->cosPhiSR(beamToTreatPol) >= 0){phi_S_R = asin(this->sinPhiSR(beamToTreatPol));}
	
	else if (this->cosPhiSR(beamToTreatPol) < 0)
	{
		if (this->sinPhiSR(beamToTreatPol) >= 0)
		{
			phi_S_R = pi - asin(this->sinPhiSR(beamToTreatPol));
		}
		if (this->sinPhiSR(beamToTreatPol) < 0)
		{
			phi_S_R = -pi - asin(this->sinPhiSR(beamToTreatPol));
			
		}
	}
	
	return phi_S_R;
}
