/*
 *  dihadronPair.cxx
 *  2012IFF
 *
 *  Created by Keith Landry on 8/27/14.
 *  UCLA
 *
 */

#include "dihadronPair.h"

ClassImp(dihadronPair)
//______________________________________________________________________________
dihadronPair::dihadronPair(){
	
}
//______________________________________________________________________________
dihadronPair::dihadronPair(string posName, StMuTrack* posHadron, string negName, StMuTrack* negHadron, int spinB){
	
	mPosHadron  = posHadron;
	mNegHadron  = negHadron;
	mPosName    = posName;
	mNegName    = negName;
	
	
	
	if (posName == "pion"){mPosHadLV.SetPtEtaPhiM(mPosHadron->pt(), mPosHadron->eta(), mPosHadron->phi(), 0.13957);}
	else if (posName == "kaon"){mPosHadLV.SetPtEtaPhiM(mPosHadron->pt(), mPosHadron->eta(), mPosHadron->phi(), 0.49367);}
	else {cout << "unknown particle name" << endl;}
	
	if (negName == "pion"){mNegHadLV.SetPtEtaPhiM(mNegHadron->pt(), mNegHadron->eta(), mNegHadron->phi(), 0.13957);}
	else if (negName == "kaon"){mNegHadLV.SetPtEtaPhiM(mNegHadron->pt(), mNegHadron->eta(), mNegHadron->phi(), 0.49367);}
  else {cout << "unknown particle name" << endl;}

	
	mPh = mPosHadLV.Vect() + mNegHadLV.Vect();
	mRh = (mPosHadLV.Vect() - mNegHadLV.Vect())*0.5;
	
	
	this->setSpinBit(spinB);
	
	
}
//______________________________________________________________________________
dihadronPair::~dihadronPair(){
	
}
//SETTERS-----------------------------------------------------------------------
//______________________________________________________________________________
void dihadronPair::setPosNegHad(string posName, StMuTrack* plus,string negName, StMuTrack* minus, int spinB){
	
	mPosHadron  = plus;
	mNegHadron  = minus;
	mPosName    = posName;
	mNegName    = negName;
	
	
	if (posName == "pion"){mPosHadLV.SetPtEtaPhiM(mPosHadron->pt(), mPosHadron->eta(), mPosHadron->phi(), 0.13957);}
	else if (posName == "kaon"){mPosHadLV.SetPtEtaPhiM(mPosHadron->pt(), mPosHadron->eta(), mPosHadron->phi(), 0.49367);}
  else {cout << "unknown particle name" << endl;}

	
	if (negName == "pion"){mNegHadLV.SetPtEtaPhiM(mNegHadron->pt(), mNegHadron->eta(), mNegHadron->phi(), 0.13957);}
	else if (negName == "kaon"){mNegHadLV.SetPtEtaPhiM(mNegHadron->pt(), mNegHadron->eta(), mNegHadron->phi(), 0.49367);}
  else {cout << "unknown particle name" << endl;}

	
	mPh = mPosHadLV.Vect() + mNegHadLV.Vect();
	mRh = (mPosHadLV.Vect() - mNegHadLV.Vect())*0.5;
	
	
	this->setSpinBit(spinB);
	
}
//______________________________________________________________________________
void dihadronPair::setSpinBit(int spinB){
	
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
double dihadronPair::invarientMass(){
	
	TLorentzVector sum = mPosHadLV + mNegHadLV;
	double invarMass = sum.M();
	
	return invarMass;
}
//______________________________________________________________________________
bool dihadronPair::withinRadius(double minR, double maxR){
	
	double radius = sqrt( pow(mPosHadron->eta() - mNegHadron->eta(), 2) + pow(mPosHadron->phi() - mNegHadron->phi(), 2) );
	
	if (radius >= minR && radius <= maxR) {return true;}
	else {return false;}
	
}
//______________________________________________________________________________
double dihadronPair::theta(){
	
	TLorentzVector sum = mPosHadLV + mNegHadLV;
	TLorentzVector lorentzVect = mPosHadLV;
	
	lorentzVect.Boost(-sum.BoostVector());

	double Theta = lorentzVect.Vect().Angle(mPh);
	
	return Theta;
}
//______________________________________________________________________________
double dihadronPair::cosPhiS(char beamToTreatPol){
	
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
	
	double cosPhi_S = mPb.Unit().Cross(mPh).Unit() * mPb.Unit().Cross(spinVec).Unit();      //From equation 7 in arXiv:hep-ph/0412141v1
	
	return cosPhi_S;
}
//______________________________________________________________________________
double dihadronPair::cosPhiR(char beamToTreatPol){
	
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
double dihadronPair::sinPhiS(char beamToTreatPol){
	
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
double dihadronPair::sinPhiR(char beamToTreatPol){
	
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
double dihadronPair::sinPhiSR(char beamToTreatPol){
	
	double sinPhi_S_R = this->sinPhiS(beamToTreatPol)*this->cosPhiR(beamToTreatPol) - this->cosPhiS(beamToTreatPol)*this->sinPhiR(beamToTreatPol);
	
	return sinPhi_S_R;
}
//______________________________________________________________________________
double dihadronPair::cosPhiSR(char beamToTreatPol){
	
	double cosPhi_S_R = this->cosPhiS(beamToTreatPol)*this->cosPhiR(beamToTreatPol) + this->sinPhiS(beamToTreatPol)*this->sinPhiR(beamToTreatPol);
	
	return cosPhi_S_R;	
}
//______________________________________________________________________________
double dihadronPair::phiR(char beamToTreatPol){
	
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
double dihadronPair::phiS(char beamToTreatPol){
	
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
double dihadronPair::phiSR(char beamToTreatPol){
	
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
