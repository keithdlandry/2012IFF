/*
 *  testAngleCalc.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/3/14.
 *  UCLA
 *
 */


void testAngleCalc(){



	
	
	
	TVector3 Pa;
	Pa.SetXYZ(0, 0, 1);   //blue is unpolarized beam
	
	TVector3 Pb;
	Pb.SetXYZ(0, 0, -1);  //yellow is polarized beam
	

	TVector3 spinVec;
	TVector3 P1;
	TVector3 P2;
	TVector3 Rh;
	TVector3 Ph;
	
	
	spinVec.SetXYZ(0, 1, 0);
	P1.SetXYZ(1, 2, 2);
	P2.SetXYZ(2, 3, 2);
	
	Ph = P1+P2;
	Rh = (P1-P2)*.5;
	
	double cosPhi_S = Pb.Unit().Cross(Ph).Unit() * Pb.Unit().Cross(spinVec).Unit();
	
	double cosPhi_R = Ph.Unit().Cross(Pa).Unit() * Ph.Unit().Cross(Rh).Unit();
	
	double sinPhi_S = Ph.Cross(spinVec) * Pb.Unit() / (Pb.Unit().Cross(Ph).Mag() * Pb.Unit().Cross(spinVec).Mag());
	
	double sinPhi_R = Pa.Cross(Rh) * Ph.Unit() / (Ph.Unit().Cross(Pa).Mag() * Ph.Unit().Cross(Rh).Mag());
	
	
	
	double sinPhi_S_R = sinPhi_S*cosPhi_R - cosPhi_S*sinPhi_R;
	
	double cosPhi_S_R = cosPhi_S*cosPhi_R + sinPhi_S*sinPhi_R;
	
	
	
	double phi_S_R;
	
	if (cosPhi_S_R >= 0)
	{
		phi_S_R = asin(sinPhi_S_R);
	}
	else if (cosPhi_S_R < 0)
	{
		
		if (sinPhi_S_R >= 0)
		{
			phi_S_R = TMath::Pi() - asin(sinPhi_S_R);
		}
		if (sinPhi_S_R < 0)
		{
			phi_S_R = -TMath::Pi() - asin(sinPhi_S_R);
		}
		
	}
	

	
	cout << "cosPhiS  = " << cosPhi_S << "   sinPhiS  = " << sinPhi_S << endl;
	cout << "cosPhiR  = " << cosPhi_R << "   sinPhiR  = " << sinPhi_R << endl;
	cout << "sinPhiSR = " << sinPhi_S_R << "   cosPhiSR = " << cosPhi_S_R << endl;
	
	cout << "    PhiSR = " << phi_S_R << endl;
	
	
	

}