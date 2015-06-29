/*
 *  sameSignPair.C
 *  2012IFF
 *
 *  Created by Keith Landry on 3/28/14.
 *  UCLA
 *
 */

#include "sameSignPair.h"

ClassImp(sameSignPair)

//______________________________________________________________________________
sameSignPair::sameSignPair(){
	
}
//______________________________________________________________________________
sameSignPair::sameSignPair(StMuTrack* pion1, StMuTrack* pion2, int spinB){
	
	mPion1  = pion1;
	mPion2 = pion2;
	
	
	mPion1LV.SetPtEtaPhiM(mPion1->pt(), mPion1->eta(), mPion1->phi(), 0.13957);
	mPion2LV.SetPtEtaPhiM(mPion2->pt(), mPion2->eta(), mPion2->phi(), 0.13957);
	
	
	
	mPh = mPion1LV.Vect() + mPion2LV.Vect();
	mRh = (mPion1LV.Vect() - mPion2LV.Vect())*0.5;
	
	
	this->setSpinBit(spinB);
	
	
}
//______________________________________________________________________________
sameSignPair::~sameSignPair(){
	
}
//SETTERS-----------------------------------------------------------------------
//______________________________________________________________________________
void sameSignPair::setBothPions(StMuTrack* pion1, StMuTrack* pion2, int spinB){
	
	mPion1 = pion1;
	mPion2 = pion2;
	
	
	mPion1LV.SetPtEtaPhiM(mPion1->pt(), mPion1->eta(), mPion1->phi(), 0.13957);
	mPion2LV.SetPtEtaPhiM(mPion2->pt(), mPion2->eta(), mPion2->phi(), 0.13957);
	
	
	mPh = mPion1LV.Vect() + mPion2LV.Vect();
	mRh = (mPion1LV.Vect() - mPion2LV.Vect())*0.5;
	
	
	this->setSpinBit(spinB);
	
}
//______________________________________________________________________________
void sameSignPair::setSpinBit(int spinB){
	
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
double sameSignPair::invarientMass(){
	
	TLorentzVector sum = mPion1LV + mPion2LV;
	double invarMass = sum.M();
	
	return invarMass;
}
//______________________________________________________________________________
bool sameSignPair::withinRadius(double minR, double maxR){
	
	double radius = sqrt( pow(mPion1->eta() - mPion2->eta(), 2) + pow(mPion1->phi() - mPion2->phi(), 2) );
	
	if (radius >= minR && radius <= maxR) {return true;}
	else {return false;}
	
}
//______________________________________________________________________________
double sameSignPair::theta(){
	
	TLorentzVector sum = mPion1LV + mPion2LV;
	
	mPion1LV.Boost(-sum.BoostVector());
	double Theta = mPion1LV.Vect().Angle(mPh);
	
	return Theta;
}
//______________________________________________________________________________
double sameSignPair::cosPhiS(char beamToTreatPol){
	
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
double sameSignPair::cosPhiR(char beamToTreatPol){
	
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
double sameSignPair::sinPhiS(char beamToTreatPol){
	
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

	double sinPhi_S = mPh.Cross(spinVec) * mPb.Unit() / (mPb.Unit().Cross(mPh).Mag() * mPb.Unit().Cross(spinVec).Mag());
	
	return sinPhi_S;
}
//______________________________________________________________________________
double sameSignPair::sinPhiR(char beamToTreatPol){
	
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
double sameSignPair::sinPhiSR(char beamToTreatPol){
	
	double sinPhi_S_R = this->sinPhiS(beamToTreatPol)*this->cosPhiR(beamToTreatPol) - this->cosPhiS(beamToTreatPol)*this->sinPhiR(beamToTreatPol);
	
	return sinPhi_S_R;
}
//______________________________________________________________________________
double sameSignPair::cosPhiSR(char beamToTreatPol){
	
	double cosPhi_S_R = this->cosPhiS(beamToTreatPol)*this->cosPhiR(beamToTreatPol) + this->sinPhiS(beamToTreatPol)*this->sinPhiR(beamToTreatPol);
	
	return cosPhi_S_R;	
}
//______________________________________________________________________________
double sameSignPair::phiR(char beamToTreatPol){
	
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
double sameSignPair::phiS(char beamToTreatPol){
	
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
double sameSignPair::phiSR(char beamToTreatPol){
	
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


