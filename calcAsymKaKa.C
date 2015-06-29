/*
 *  calcAsymKaKa.C
 *  2012IFF
 *
 *  Created by Keith Landry on 6/16/15.
 *  UCLA
 *
 */



#include <map>
#include "TF1.h"
#include "TRandom3.h"

const int nPtBins    = 4;
const int nEtaBins   = 6;
const int nMassBins  = 2;

//const int nCosThetaBins = 7;
const int nCosThetaBins = 5;

const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014

double    ptBinStart[nPtBins] = {3.0, 3.7, 4.15, 4.63};
double    ptBinEnd[nPtBins]   = {3.7, 4.15, 4.63, 6};  //Anselm used 1000.0 as last point

double    massBinStart[nMassBins] = {0.86, 1.1};
double    massBinEnd[nMassBins]   = {1.1, 1.5};

double    etaBinStart[nEtaBins] = {-2, -0.6, -0.3, 0.0, 0.4, 0.75};
double    etaBinEnd[nEtaBins]   = {-0.6, -0.3, 0.0, 0.4, 0.75, 2};

double    cosThetaBinStart[nCosThetaBins] = {0,1.257,1.6,1.8,2};
double    cosThetaBinEnd[nCosThetaBins]   = {1.257,1.6,1.8,2,3.14159};

const int nS_Ph_angleBins = 6;
double s_Ph_angleBinStart[nS_Ph_angleBins] = {0, .5, 1, 1.5, 2, 2.5};
double s_Ph_angleBinEnd[nS_Ph_angleBins] = {.5, 1, 1.5, 2, 2.5, 3.15};

//FUNCTIONS======================================
//creating histograms
void createNbins(const int nBins, TH1D* hist[nBins], int histbins, double histmin, double histmax, string name){
	
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		
		stringstream ss;
		ss << iBin;
		string fullname = name + ss.str();
		cout << fullname << endl;
		
		hist[iBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
		
	}
}
void createPolHistsNbins(const int nBins, TH1D* hist[nBins][nPhisrBins], int histbins, double histmin, double histmax, string name){
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		
		for (int iPhisrBin = 0; iPhisrBin < nPhisrBins; iPhisrBin++)
		{
			
			stringstream ss;
			ss << iPhisrBin;
			
			stringstream ss2;
			ss2 << iBin;
			
			string fullname = name + ss2.str() + "_phiSRbin_" + ss.str();
			cout << fullname << endl;
			
			hist[iBin][iPhisrBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
			
		}
	}
}

//drawing and saving histograms
void drawNbins(const int nBins, TH1D* hist[nBins], TCanvas* can){
	
	int xSide;
	int ySide;
	int maxSide;
	
	
	if (sqrt(nBins) != floor(sqrt(nBins)))
	{
		xSide = floor(sqrt(nBins)) + 1;
		ySide = nBins/xSide + 1;	
	}
	else
	{
		xSide = sqrt(nBins);
		ySide = xSide;
	}
	
	can->Divide(xSide, ySide);
	
	for (int i = 0; i < nBins; i++)
	{
		can->cd(i+1);
		hist[i]->Draw();
	}
	
}
void writeNbins(const int nBins, TH1D* hist[nBins]){
	
	for (int i = 0; i < nBins; i++)
	{
		hist[i]->Write();
	}
	
	
}
void writePolHistsNbins(const int nBins, TH1D* hist[nBins][nPhisrBins]){
	
	for (int i = 0; i < nBins; i++)
	{
		for (int iPhisr = 0; iPhisr < nPhisrBins; iPhisr++)
		{
			hist[i][iPhisr]->Write();
		}
	}
}




//filling histograms
void fillCorrectPtBin(TH1D* numhist[nPtBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nPtBins][nPhisrBins], double polarization, TH1D* ptHist[nPtBins]){
  
  bool filled = false;
  
	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
    
    if (filled){break;}
    
		if (sumVect.Pt() >= ptBinStart[iPt] && sumVect.Pt() < ptBinEnd[iPt])
		{
			numhist[iPt]->Fill(phiSR);
			ptHist[iPt]->Fill(sumVect.Pt());
      
			int phiSRbin = numhist[iPt]->FindBin(phiSR);
			polHist[iPt][phiSRbin-1]->Fill(polarization); //minus 1 because zero is underflow bin and we want it to start at 0
      filled = true;
      
    }
	}
}


void fillCorrectMassBin(TH1D* numhist[nMassBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nMassBins][nPhisrBins], double polarization, TH1D* massHist[nMassBins]){
	
	for (int iMass = 0; iMass < nMassBins; iMass++)
	{
		if (sumVect.M() >= massBinStart[iMass] && sumVect.M() < massBinEnd[iMass])
		{
			numhist[iMass]->Fill(phiSR);
			massHist[iMass]->Fill(sumVect.M());
      
			int phiSRbin = numhist[iMass]->FindBin(phiSR);
			polHist[iMass][phiSRbin-1]->Fill(polarization);
		}
	}
}


void fillCorrectEtaBin(TH1D* hist[nEtaBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nEtaBins][nPhisrBins], double polarization, TH1D* etaHist[nEtaBins]){
	
	for (int iEta = 0; iEta < nEtaBins; iEta++)
	{
		if (sumVect.Eta() >= etaBinStart[iEta] && sumVect.Eta() < etaBinEnd[iEta])
		{
			hist[iEta]->Fill(phiSR);
			etaHist[iEta]->Fill(sumVect.Eta());
      
			int phiSRbin = hist[iEta]->FindBin(phiSR);			
			polHist[iEta][phiSRbin-1]->Fill(polarization);
		}
	}
}

void fillCorrectCosThetaBin(TH1D* hist[nCosThetaBins],  double cosTheta, double phiSR, TH1D* polHist[nCosThetaBins][nPhisrBins], double polarization, TH1D* cosThetaHist[nCosThetaBins]){
	
	for (int iCosTheta = 0; iCosTheta < nCosThetaBins; iCosTheta++)
	{
		if (cosTheta >= cosThetaBinStart[iCosTheta] && cosTheta < cosThetaBinEnd[iCosTheta])
		{
			hist[iCosTheta]->Fill(phiSR);
			cosThetaHist[iCosTheta]->Fill(cosTheta);
			
			int phiSRbin = hist[iCosTheta]->FindBin(phiSR);			
			polHist[iCosTheta][phiSRbin-1]->Fill(polarization);
		}
	}
}


void fillCorrectSPhAngleBin(TH1D* hist[nS_Ph_angleBins], double angle, double phiSR, TH1D* polHist[nS_Ph_angleBins][nPhisrBins], double polarization, TH1D* sPhAngleHist[nS_Ph_angleBins]){
	
	
	for (int iSPhAngle = 0; iSPhAngle < nS_Ph_angleBins; iSPhAngle++)
	{
		if (angle >= s_Ph_angleBinStart[iSPhAngle] && angle < s_Ph_angleBinEnd[iSPhAngle])
		{
			hist[iSPhAngle]->Fill(phiSR);
			sPhAngleHist[iSPhAngle]->Fill(angle);
      
			int phiSRbin = hist[iSPhAngle]->FindBin(phiSR);			
			polHist[iSPhAngle][phiSRbin-1]->Fill(polarization);
		}
	}
}


//getting average values
void getPtPoints(TH1D* ptHist[nPtBins], double* ptPoints, double* ptPointsErr){
	
	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
		
    ptPoints[iPt] = ptHist[iPt]->GetMean(1);
		ptPointsErr[iPt] = ptHist[iPt]->GetRMS(1)/(sqrt(ptHist[iPt]->GetEntries()));
		
	}
}

void getMassPoints(TH1D* massHist[nMassBins], double* massPoints, double* massPointsErr){
	
	for (int iMass = 0; iMass < nMassBins; iMass++)
	{
		
    massPoints[iMass] = massHist[iMass]->GetMean(1);
		massPointsErr[iMass] = massHist[iMass]->GetRMS(1)/(sqrt(massHist[iMass]->GetEntries()));
		
	}
}

void getEtaPoints(TH1D* etaHist[nEtaBins], double* etaPoints, double* etaPointsErr){
	
	for (int iEta = 0; iEta < nEtaBins; iEta++)
	{
		
    
		etaPoints[iEta] = etaHist[iEta]->GetMean(1);
		etaPointsErr[iEta] = etaHist[iEta]->GetRMS(1)/(sqrt(etaHist[iEta]->GetEntries()));
		
	}
}

void getCosThetaPoints(TH1D* cosThetaHist[nCosThetaBins], double* cosThetaPions, double* cosThetaPointsErr){
	
	for (int iCosTheta = 0; iCosTheta < nCosThetaBins; iCosTheta++)
	{
		
		cosThetaPoints[iCosTheta] = cosThetaHist[iCosTheta]->GetMean(1);
	  cosThetaPointsErr[iCosTheta] = cosThetaHist[iCosTheta]->GetRMS(1)/(sqrt(cosThetaHist[iCosTheta]->GetEntries()));
		
	}
}

void getSPhAnglePoints(TH1D* sPhAngleHist[nS_Ph_angleBins], double* sPhAnglePoints, double* sPhAnglePointsErr){
	
	for (int iSPhAngle = 0; iSPhAngle < nS_Ph_angleBins; iSPhAngle++)
	{
		
		sPhAnglePoints[iSPhAngle] = sPhAngleHist[iSPhAngle]->GetMean(1);
		sPhAnglePointsErr[iSPhAngle] = sPhAngleHist[iSPhAngle]->GetRMS(1)/(sqrt(sPhAngleHist[iSPhAngle]->GetEntries()));
		
	}
}


//asymmetry calculation
void calcAsym(const int nBins, TH1D* hAut[nBins], TH1D* hUp[nBins], TH1D* hDown[nBins], TH1D* hPol[nBins][nPhisrBins], double* asym, double* asymE){
	
	for (int i = 0; i < nBins; i++)
	{
		
		for (int ibin = 1; ibin <= nPhisrBins; ibin++)
		{
			
			if (ibin <= nPhisrBins*0.5)
			{
				double nUp     = hUp[i]->GetBinContent(ibin);
				double nUpPi   = hUp[i]->GetBinContent(ibin+nPhisrBins*0.5);
				double nDown   = hDown[i]->GetBinContent(ibin);
				double nDownPi = hDown[i]->GetBinContent(ibin+nPhisrBins*0.5);
				
				double avgPol  = ( hPol[i][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][ibin-1+nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
			}
			else
			{
				
				double nUp     = hUp[i]->GetBinContent(ibin);
				double nUpPi   = hUp[i]->GetBinContent(ibin-nPhisrBins*0.5);
				double nDown   = hDown[i]->GetBinContent(ibin);
				double nDownPi = hDown[i]->GetBinContent(ibin-nPhisrBins*0.5);
				
				double avgPol  = ( hPol[i][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][ibin-1-nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
			}
      
			hAut[i]->SetBinContent(ibin, 1/avgPol * ( sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi) ) / ( sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi) ) );
			
			//calc bin error also
			if (avgPol*pow(sqrt(nUp*nDownPi)+sqrt(nDown*nUpPi), 2) != 0)
			{
				double a = sqrt(nUp*nDownPi);
				double b = sqrt(nDown*nUpPi);
				
				double firstTerm = avgPol**2 * (nUpPi*nDown*(nUp+nDownPi) + nDownPi*nUp*(nUpPi+nDown));
				
				//double secondTerm = ((nUp*nDownPi)**2 +(nUpPi*nDown)**2 - 2*nUp*nDown*nUpPi*nDownPi)*realAvgPolE**2;
				double secondTerm = 0;
				
				double binError = 1/avgPol**2 * 1/(a+b)**2 * sqrt(firstTerm + secondTerm);
			}
			else
			{
				binError = .01;
				cout << "bin " << ibin << " has problem with error " << endl;
			}
			hAut[i]->SetBinError(ibin, binError);
			
		}//end phisrbins
		
		//FIT THE HISTOGRAMS
		TF1* fitFunc = new TF1("fitFunc","[0]*sin(x)",-3.14159265359*.5,3.14159265359*.5);
		hAut[i]->Fit("fitFunc", "R");
		
		
		TF1* f1 = hAut[i]->GetFunction("fitFunc");
		
		//fill asym and asymE to plot the value of the fit and error later. 
		asym[i]  = f1->GetParameter(0);
		asymE[i] = f1->GetParError(0);
		
		hAut[i]->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
		
	}//end mass,Pt, or Eta bins
	
}


//MAIN===========================================
//MAIN===========================================
//MAIN===========================================
//MAIN===========================================
//MAIN===========================================


void calcAsymKaKa(){
  
	
	
	//OPTIONS AND CUTS______________
	bool useBlueBeam = true;
	bool useYellowBeam = true;
	bool randomizeSpin = false;
  bool randomizePiAssignment = false;
	bool fullEta = false;
  
	double PI = 3.14159265359;
	
	
	
	
  
  
  
	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("dihadronPair");
	cout << " loading of dihadronPair library done" << endl;
	//______________________________
  
  
  //TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/dihadron/diHadOut_5_7/allKPi_5_7.root");
  TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/dihadron/test1/allTestKK.root");
  
	string outFileName = "./resDiHad_kk_test/cone03AsymsHiEta_kk.root"; 
  
	
  //______________________________
  
	
	//SET UP TREE TO RECEIVE INPUT__
	dihadronPair* pair1 = new dihadronPair();
	TTree* pairTree = infile->Get("dihadronPairTree");
	pairTree->SetBranchAddress("dihadronPair", &pair1);
	//______________________________
  
  
  double histMin = -PI;
	double histMax =  PI;
  
  // -- PT -- //
	TH1D * hNumberUp_Pt[nPtBins];
	TH1D * hNumberDown_Pt[nPtBins];
	createNbins(nPtBins, hNumberUp_Pt, nPhisrBins, histMin, histMax, "hNumUp_Ptbin_");
	createNbins(nPtBins, hNumberDown_Pt, nPhisrBins, histMin, histMax, "hNumDown_Ptbin_");
	TH1D* hAut_Pt[nPtBins];
	createNbins(nPtBins, hAut_Pt, nPhisrBins, histMin, histMax, "hAut_Ptbin_");
	TH1D* polOfBin_Pt[nPtBins][nPhisrBins];
	createPolHistsNbins(nPtBins, polOfBin_Pt, 25, 0, 1, "hPolOfBin_Ptbin_");
	TH1D* hPt[nPtBins];
	createNbins(nPtBins, hPt, 500, ptBinStart[0], ptBinEnd[nPtBins-1], "hPt_Ptbin_");
  
	
  // -- MASS -- //
	TH1D * hNumberUp_Mass[nMassBins]; 
	TH1D * hNumberDown_Mass[nMassBins];
	createNbins(nMassBins, hNumberUp_Mass, nPhisrBins, histMin, histMax, "hNumUp_Massbin_");
	createNbins(nMassBins, hNumberDown_Mass, nPhisrBins, histMin, histMax, "hNumDown_Massbin_");
	TH1D* hAut_Mass[nMassBins];
	createNbins(nMassBins, hAut_Mass, nPhisrBins, histMin, histMax, "hAut_Massbin_");
	TH1D* polOfBin_Mass[nMassBins][nPhisrBins];
	createPolHistsNbins(nMassBins, polOfBin_Mass, 25, 0, 1, "hPolOfBin_Massbin_");
	TH1D* hMass[nMassBins];
	createNbins(nMassBins, hMass, 1000, massBinStart[0], massBinEnd[nMassBins-1], "hMass_Massbin_");
  
	
	// -- ETA -- //
	TH1D * hNumberUp_Eta[nEtaBins];   
	TH1D * hNumberDown_Eta[nEtaBins];
	createNbins(nEtaBins, hNumberUp_Eta, nPhisrBins, histMin, histMax, "hNumUp_Etabin_");
	createNbins(nEtaBins, hNumberDown_Eta, nPhisrBins, histMin, histMax, "hNumDown_Etabin_");
	TH1D* hAut_Eta[nEtaBins];
	createNbins(nEtaBins, hAut_Eta, nPhisrBins, histMin, histMax, "hAut_Etabin_");
	TH1D* polOfBin_Eta[nEtaBins][nPhisrBins];
	createPolHistsNbins(nEtaBins, polOfBin_Eta, 25, 0, 1, "hPolOfBin_Etabin_");
	TH1D* hEta[nEtaBins];
	createNbins(nEtaBins, hEta, 20, etaBinStart[0], etaBinEnd[nEtaBins-1], "hEta_Etabin_");
  
	
	// -- THETA (labeled CosTheta) -- //
	TH1D * hNumberUp_CosTheta[nCosThetaBins];   
	TH1D * hNumberDown_CosTheta[nCosThetaBins];
	createNbins(nCosThetaBins, hNumberUp_CosTheta, nPhisrBins, histMin, histMax, "hNumUp_CosThetabin_");
	createNbins(nCosThetaBins, hNumberDown_CosTheta, nPhisrBins, histMin, histMax, "hNumDown_CosThetabin_");
	TH1D* hAut_CosTheta[nCosThetaBins];
	createNbins(nCosThetaBins, hAut_CosTheta, nPhisrBins, histMin, histMax, "hAut_CosThetabin_");
	TH1D* polOfBin_CosTheta[nCosThetaBins][nPhisrBins];
	createPolHistsNbins(nCosThetaBins, polOfBin_CosTheta, 25, 0, 1, "hPolOfBin_CosThetabin_");
	TH1D* hCosTheta[nCosThetaBins];
	createNbins(nCosThetaBins, hCosTheta, 20, cosThetaBinStart[0], cosThetaBinEnd[nCosThetaBins-1], "hCosTheta_CosThetabin_");
  
  
	// -- ANGLE BETWEEN SPIN AND Ph -- //
	TH1D * hNumberUp_sPhAngle[nS_Ph_angleBins];
	TH1D * hNumberDown_sPhAngle[nS_Ph_angleBins];
	createNbins(nS_Ph_angleBins, hNumberUp_sPhAngle, nPhisrBins, histMin, histMax, "hNumUp_sPhAnglebin_");
	createNbins(nS_Ph_angleBins, hNumberDown_sPhAngle, nPhisrBins, histMin, histMax, "hNumDown_sPhAnglebin_");
	TH1D* hAut_sPhAngle[nS_Ph_angleBins];
	createNbins(nS_Ph_angleBins, hAut_sPhAngle, nPhisrBins, histMin, histMax, "hAut_sPhAnglebin_");
	TH1D* polOfBin_sPhAngle[nS_Ph_angleBins][nPhisrBins];
	createPolHistsNbins(nS_Ph_angleBins, polOfBin_sPhAngle, 25, 0, 1, "hPolOfBin_sPhAnglebin_");
	TH1D* hSPhAngle[nS_Ph_angleBins];
	createNbins(nS_Ph_angleBins, hSPhAngle, 50, s_Ph_angleBinStart[0], s_Ph_angleBinEnd[nS_Ph_angleBins-1], "hSPhAngle_sPhAnglebin_");
  
  
  //______________________________
	
	
	
	//BEAM POLARIZATION_____________
	//The beam polarization is read in from a text file and stored in maps.
	ifstream polFile;
	polFile.open("/star/u/klandry/ucladisk/2012IFF/BeamPolarization2012.txt");
	
  
	map<int, double> polarizationOfFill_Y;
	map<int, double> polErrOfFill_Y;
	
	map<int, double> polarizationOfFill_B;
	map<int, double> polErrOfFill_B;
	
	
	
	int    fill;
	int    beamE;
	int    startT;
	string plusminus;
	
	double pAvrgBlue;
	double pErrAvrgBlue;
	
	double pInitialBlue;
	double pErrInitialBlue;
	double dPdTBlue;
	double dPdTErrBlue;
	
	double pAvrgYellow;
	double pErrAvrgYellow;
	
	double pInitialYellow;
	double pErrInitialYellow;
	double dPdTYellow;
	double dPdTErrYellow;
	
	string header;
	
	for (int i=0; i<19; i++){polFile >> header;}
	
	while (!polFile.eof())
	{
		
		polFile >> fill;
		polFile >> beamE;
		polFile >> startT;
		
		polFile >> pAvrgBlue;
		polFile >> plusminus;
		polFile >> pErrAvrgBlue;
		
		polFile >> pInitialBlue;
		polFile >> plusminus;
		polFile >> pErrInitialBlue;
		
		polFile >> dPdTBlue;
		polFile >> plusminus;
		polFile >> dPdTErrBlue;
		
		polFile >> pAvrgYellow;
		polFile >> plusminus;
		polFile >> pErrAvrgYellow;
		
		polFile >> pInitialYellow;
		polFile >> plusminus;
		polFile >> pErrInitialYellow;
		
		polFile >> dPdTYellow;
		polFile >> plusminus;
		polFile >> dPdTErrYellow;
		
		
		polarizationOfFill_B[fill] = pAvrgBlue/100.;
		polErrOfFill_B[fill] = pErrAvrgBlue/100.;
		
		polarizationOfFill_Y[fill] = pAvrgYellow/100.;
		polErrOfFill_Y[fill] = pErrAvrgYellow/100.;
		
	}
  //______________________________
  
  
  
  //CUTS__________________________
	double lowLimitPt    = ptBinStart[0];
	double hiLimitPt     = ptBinEnd[nPtBins-1];
	double lowLimitMass  = massBinStart[0];
	double hiLimitMass   = massBinEnd[nMassBins-1];
	double lowLimitEta   = etaBinStart[0];
	double hiLimitEta    = etaBinEnd[nEtaBins-1];
  
  lowLimitEta = 0;
  
  if (fullEta)
	{
		assert(hiLimitEta > 0);
		assert(lowLimitEta < 0);
	}
	
  
  cout << "\n";
	if (useBlueBeam && useYellowBeam){cout << "using both beams-----" << endl;}
	if (useBlueBeam && !useYellowBeam){cout << "using blue beam------" << endl;}
	if (!useBlueBeam && useYellowBeam){cout << "using yellow beam----" << endl;}
	cout << "\n";
	if (randomizeSpin){cout << "randomizing spin-----" << endl;}
	cout << "\n";
	if (randomizePiAssignment){cout << "randomizing pion assignment-----" << endl;}
	//______________________________
  
  
	cout << "\n";
	cout << "Pt  between " << lowLimitPt << " and " << hiLimitPt << endl;
	cout << "M   between " << lowLimitMass << " and " << hiLimitMass << endl;
	cout << "Eta between " << lowLimitEta << " and " << hiLimitEta << endl;
	//______________________________
	
	//*
	
	//   ======================================================================
	//============================================================================
	//START ANALYSIS==============================================================
	//============================================================================
	//   ======================================================================
  //*
	cout << "\n";
	cout << "<----STARTING ANALYSIS---->" << endl;
  cout << "\n";
	cout << pairTree->GetEntries() << " pairs to analyze" << endl;
  
  int blueFillNo;
	int yellowFillNo;
	
	int phiSRbin;
	
  TLorentzVector sum;
	TLorentzVector sumY;
	TLorentzVector sumB;
  
  
  int pionStarNumber = 0;   //if we want to do a small sample but not start on the first pair in file
  
	for (int iPair = pionStarNumber; iPair < pairTree->GetEntries(); iPair++)
	{
		
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == pionStarNumber+10000){break;}
    
		pairTree->GetEntry(iPair);
		
    //selectonly poitive kaons/pions
    //*
     if (pair1->posTrackName() == "pion" || pair1->negTrackName() == "pion")
     {
     continue;
     }
     //*/
    
		//fill number 16427 didn't have any polarization data available so we skip
		if (pair1->runInfo().beamFillNumber(1) == 16427 && pair1->runInfo().beamFillNumber(0) == 16427)
		{
			continue;
		}
    
		
		if (pair1->withinRadius(0.05, 0.3))
		{
      bool triggerFired = false;
			bool fromKaon = false;
			bool passInitialCut_B = false;
			bool passInitialCut_Y = false;
			bool passDCAcut = false;
      
      StTriggerId trigId = pair1->triggerIds();
      
      
      //just JP1 and JP2
      if (trigId.isTrigger(370611) || trigId.isTrigger(370621))
      {
        triggerFired = true;
      }
      
      ///*
			//JP0,JP1,JP2,AJP
			if (trigId.isTrigger(370601) || trigId.isTrigger(370611) || trigId.isTrigger(370621) || trigId.isTrigger(370641))
			{
				triggerFired = true;
			}
			
			//BHT0VPD,BHT1VPD,BHT2BBC,BHT2
			if (trigId.isTrigger(370501) || trigId.isTrigger(370511) || trigId.isTrigger(370522) || trigId.isTrigger(370531))
			{
				triggerFired = true;
			}
			//*/
			
      
      if (triggerFired)
			{
        
        blueFillNo   = pair1->runInfo().beamFillNumber(1); //1 = blue beam
				yellowFillNo = pair1->runInfo().beamFillNumber(0); //0 = yellow beam 
        
				sum = pair1->posHadLV() + pair1->negHadLV();
				sumB = sum; //blue beam.
        
				//yellow beam must rotate around y axis by pi so the eta regions can be equivalent for both beams. 				
				sumY = sum;
				sumY.RotateY(PI);
        
        if (sumB.Pt() >= lowLimitPt && sumB.Pt() <= hiLimitPt && sumB.M() >= lowLimitMass && sumB.M() <= hiLimitMass && sumB.Eta() >= lowLimitEta && sumB.Eta() <= hiLimitEta)
				{
					passInitialCut_B = true;
				}
				if (sumY.Pt() >= lowLimitPt && sumY.Pt() <= hiLimitPt && sumY.M() >= lowLimitMass && sumY.M() <= hiLimitMass && sumY.Eta() >= lowLimitEta && sumY.Eta() <= hiLimitEta)
				{
					passInitialCut_Y = true;
				}
        
        if (passInitialCut_B && useBlueBeam)
				{
					//BLUE BEAM SPIN UP: spin bin 9 and 10
					if (pair1->spinBit() == 9 || pair1->spinBit() == 10)
					{						
            
						fillCorrectPtBin(hNumberUp_Pt, sumB, pair1->phiSR('b'), polOfBin_Pt, polarizationOfFill_B[blueFillNo],hPt);
						fillCorrectMassBin(hNumberUp_Mass, sumB, pair1->phiSR('b'), polOfBin_Mass, polarizationOfFill_B[blueFillNo],hMass);
						if(fullEta){fillCorrectEtaBin(hNumberUp_Eta, sumB, pair1->phiSR('b'), polOfBin_Eta, polarizationOfFill_B[blueFillNo],hEta);}
            
          }
          //BLUE BEAM SPIN DOWN: spin bin 5 and 6
					if (pair1->spinBit() == 5 || pair1->spinBit() == 6)
					{						
            
						fillCorrectPtBin(hNumberDown_Pt, sumB, pair1->phiSR('b'), polOfBin_Pt, polarizationOfFill_B[blueFillNo],hPt);
						fillCorrectMassBin(hNumberDown_Mass, sumB, pair1->phiSR('b'), polOfBin_Mass, polarizationOfFill_B[blueFillNo],hMass);
						if(fullEta){fillCorrectEtaBin(hNumberDown_Eta, sumB, pair1->phiSR('b'), polOfBin_Eta, polarizationOfFill_B[blueFillNo],hEta);}
            
					}
				}//done with blue beam
        
        if (passInitialCut_Y && useYellowBeam)
				{
					//YELLOW BEAM SPIN UP: spin bin 6 and 10
					if (pair1->spinBit() == 6 || pair1->spinBit() == 10)
					{
            
						//TVector3 spinVect;
						//spinVect.SetXYZ(0, 1, 0);
            
						fillCorrectPtBin(hNumberUp_Pt, sumY, pair1->phiSR('y'), polOfBin_Pt, polarizationOfFill_Y[yellowFillNo],hPt);
						fillCorrectMassBin(hNumberUp_Mass, sumY, pair1->phiSR('y'), polOfBin_Mass, polarizationOfFill_Y[yellowFillNo],hMass);
						if(fullEta){fillCorrectEtaBin(hNumberUp_Eta, sumY, pair1->phiSR('y'), polOfBin_Eta, polarizationOfFill_Y[yellowFillNo],hEta);}
						//fillCorrectCosThetaBin(hNumberUp_CosTheta, pair1->theta(), pair1->phiSR('y'), polOfBin_CosTheta, polarizationOfFill_Y[yellowFillNo], hCosTheta);
					  //fillCorrectSPhAngleBin(hNumberUp_sPhAngle, spinVect.Angle(sumY.Vect()), pair1->phiSR('y'), polOfBin_sPhAngle, polarizationOfFill_Y[yellowFillNo], hSPhAngle);
            
					}						
					
					//YELLOW BEAM SPIN DOWN: spin bit 5 and 9
					if (pair1->spinBit() == 5 || pair1->spinBit() == 9)
					{
            
						fillCorrectPtBin(hNumberDown_Pt, sumY, pair1->phiSR('y'), polOfBin_Pt, polarizationOfFill_Y[yellowFillNo],hPt);
						fillCorrectMassBin(hNumberDown_Mass, sumY, pair1->phiSR('y'), polOfBin_Mass, polarizationOfFill_Y[yellowFillNo],hMass);
						if(fullEta){fillCorrectEtaBin(hNumberDown_Eta, sumY, pair1->phiSR('y'), polOfBin_Eta, polarizationOfFill_Y[yellowFillNo],hEta);}
            
					}
				}//done with yellow beam
      }// end trigger
		}//end radius check
	}//end pair tree loop
  
  //CALCULATE ASYMMETRY BIN BY BIN
	cout << "\n";
	cout << "<----CALCULATING ASYMMETRY---->" << endl;
	cout << "\n";
	
	
	//Create arrays for the asymmetry sine fit values to be stored and then plotted.
	double asymsPt[nPtBins]; 
	double asymsMass[nMassBins];
	double asymsEta[nEtaBins];
	double asymsCosTheta[nCosThetaBins];
	double asymsSPhAngle[nS_Ph_angleBins];
	
	double asymsPtE[nPtBins];
	double asymsMassE[nMassBins];
	double asymsEtaE[nEtaBins];
	double asymsCosThetaE[nCosThetaBins];
	double asymsSPhAngleE[nS_Ph_angleBins];
	
	cout << "\n";
	cout << "\n";
  
  for (int i=0; i< nMassBins; i++)
  {
    cout << hNumberUp_Mass[i]->GetEntries() << "  " << hNumberDown_Mass[i]->GetEntries() << endl;
  }
  
	cout << "\n \n calculating pt asymmetry " << endl;
	//calcAsym(nPtBins, hAut_Pt, hNumberUp_Pt, hNumberDown_Pt, polOfBin_Pt, asymsPt, asymsPtE);
	cout << "\n";
	cout << "\n";
	cout << "\n \n calculating mass asymmetry " << endl;
	calcAsym(nMassBins, hAut_Mass, hNumberUp_Mass, hNumberDown_Mass, polOfBin_Mass, asymsMass, asymsMassE);
	cout << "\n";
	cout << "\n";
	cout << "\n \n calculating cosTheta asymmetry " << endl;
	//calcAsym(nCosThetaBins, hAut_CosTheta, hNumberUp_CosTheta, hNumberDown_CosTheta, polOfBin_CosTheta, asymsCosTheta, asymsCosThetaE);
	cout << "\n";
	cout << "\n";
	if (fullEta)
	{
		cout << "\n \n calculating eta asymmetry " << endl;	
		calcAsym(nEtaBins, hAut_Eta, hNumberUp_Eta, hNumberDown_Eta, polOfBin_Eta, asymsEta, asymsEtaE);
	}
	cout << "\n";
	cout << "\n";
	cout << "\n \n calulating sPhAngle asymmetry " << endl;
	//calcAsym(nS_Ph_angleBins, hAut_sPhAngle, hNumberUp_sPhAngle, hNumberDown_sPhAngle, polOfBin_sPhAngle, asymsSPhAngle, asymsSPhAngleE);
	
  //PLOT ASYMMETRIES
	cout << "\n";
	cout << "<----PLOTTING ASYMMETRIES---->" << endl;
	cout << "\n";
	
	
	//create arrays to hold the average values to be plotted against the asymmetry
	double ptPoints[nPtBins];
	double ptPointsErr[nPtBins];
	double massPoints[nMassBins];
	double massPointsErr[nMassBins];
	double etaPoints[nEtaBins];
	double etaPointsErr[nEtaBins];
	double cosThetaPoints[nCosThetaBins];
	double cosThetaPointsErr[nCosThetaBins];
	double sPhAnglePoints[nS_Ph_angleBins];
	double sPhAnglePointsErr[nS_Ph_angleBins];
  
	TCanvas * c1 = new TCanvas();
	hCosTheta[1]->Draw();
	
	
	getPtPoints(hPt, ptPoints, ptPointsErr);
	getMassPoints(hMass, massPoints, massPointsErr);
	if(fullEta){getEtaPoints(hEta, etaPoints, etaPointsErr);}
	//getCosThetaPoints(hCosTheta, cosThetaPoints, cosThetaPointsErr);
	//getSPhAnglePoints(hSPhAngle, sPhAnglePoints, sPhAnglePointsErr);
	
	
	//DRAW ASYMS
	//TCanvas* cAsymPt = new TCanvas();
	TGraphErrors* gAsymPt = new TGraphErrors(nPtBins,ptPoints,asymsPt,ptPointsErr,asymsPtE);
	gAsymPt->SetName("gAsymPt");
	//gAsymPt->Draw("AP");
	
	//TCanvas* cAsymMass = new TCanvas();	
	TGraphErrors* gAsymMass = new TGraphErrors(nMassBins,massPoints,asymsMass,massPointsErr,asymsMassE);
	gAsymMass->SetName("gAsymMass");
	//gAsymMass->Draw("AP");
	
	if (fullEta)
	{
		//TCanvas* cAsymEta = new TCanvas();
		TGraphErrors* gAsymEta = new TGraphErrors(nEtaBins,etaPoints,asymsEta,etaPointsErr,asymsEtaE);
		gAsymEta->SetName("gAsymEta");
		//gAsymEta->Draw("AP");
		
	}
	
	//TCanvas* cAsymCosTheta = new TCanvas();
	//TGraphErrors* gAsymCosTheta = new TGraphErrors(nCosThetaBins,cosThetaPoints,asymsCosTheta,cosThetaPointsErr,asymsCosThetaE);
	//gAsymCosTheta->SetName("gAsymCosTheta");
	//gAsymCosTheta->Draw("AP");
	
	//TCanvas* cAsymsSPhAngle = new TCanvas();
	//TGraphErrors* gAsymsSPhAngle = new TGraphErrors(nS_Ph_angleBins,sPhAnglePoints,asymsSPhAngle,sPhAnglePointsErr,asymsSPhAngleE);
	//gAsymsSPhAngle->SetName("gAsymSPhAngle");
	//gAsymsSPhAngle->Draw("AP");
	
	
	
	
	//DRAW HISTOGRAMS
	cout << "\n";
	cout << "<----DRAWING HISTOGRAMS---->" << endl;
	cout << "\n";
	
  
	//TCanvas* cPt   = new TCanvas("cPt","cPt",1200,600);
	//TCanvas* cMass = new TCanvas("cMass","cMass",1200,600);
	//if(fullEta){TCanvas* cEta  = new TCanvas("cEta","cEta",800,600);}
	//TCanvas* cCosTheta = new TCanvas("cCosTheta","cCosTheta",1200,600);
	//TCanvas* cSPhAngle = new TCanvas("cSPhAngle","cSPhAngle",1200,600);
  
	//drawNbins(nPtBins, hAut_Pt, cPt);
	//drawNbins(nMassBins, hAut_Mass, cMass);
	//if(fullEta){drawNbins(nEtaBins, hAut_Eta, cEta);}
	//drawNbins(nCosThetaBins, hAut_CosTheta, cCosTheta);
	//drawNbins(nS_Ph_angleBins, hAut_sPhAngle, cSPhAngle);
	
	TFile* outFile = new TFile(outFileName.c_str(),"recreate");
	
	writeNbins(nPtBins, hPt);
	writeNbins(nMassBins, hMass);
	writeNbins(nEtaBins, hEta);
	//writeNbins(nCosThetaBins, hCosTheta);
	//writeNbins(nS_Ph_angleBins, hSPhAngle);
	
	writeNbins(nPtBins, hAut_Pt);
	writeNbins(nMassBins, hAut_Mass);
	if(fullEta)writeNbins(nEtaBins, hAut_Eta);
	//writeNbins(nCosThetaBins, hAut_CosTheta);
	//writeNbins(nS_Ph_angleBins, hAut_sPhAngle);
  
	gAsymPt->Write();
	gAsymMass->Write();
  if(fullEta){gAsymEta->Write();}
	//gAsymCosTheta->Write();
	//gAsymsSPhAngle->Write();
	
	writePolHistsNbins(nPtBins, polOfBin_Pt);
	writePolHistsNbins(nMassBins, polOfBin_Mass);
	writePolHistsNbins(nEtaBins, polOfBin_Eta);
	//writePolHistsNbins(nCosThetaBins, polOfBin_CosTheta);
	//writePolHistsNbins(nS_Ph_angleBins, polOfBin_sPhAngle);
  
	
	//hNumberUp_Mass[7]->Write();
	//hNumberDown_Mass[7]->Write();
  
	
	cout << "File " << outFileName << " written..." << endl;
	
  
	
	
  
	cout << "<----END---->" << endl; 
  
}





