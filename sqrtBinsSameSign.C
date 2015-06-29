/*
 *  sqrtBinsSameSign.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/24/14.
 *  UCLA
 *
 */


#include <map>
#include "TF1.h"
#include "TRandom3.h"



//ANSEML'S BINNING SCHEME========================
const int nPtBins = 5;
const int nEtaBins = 4;
const int nMassBins =5;
const int nPhisrBins = 16;

double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0};
double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 50.0};  //Anselm used 1000.0 as last point

double    massBinStart[nMassBins] = {0.0, 0.4, 0.6, 0.8, 1.0};
double    massBinEnd[nMassBins]   = {0.4, 0.6, 0.8, 1.0, 100.5};

double    etaBinStart[nEtaBins] = {-1.4,-0.5,0.0,0.5};
double    etaBinEnd[nEtaBins]   = {-0.5,0.0,0.5, 1.4};
//===============================================


//FUNCTIONS======================================
//creating histograms
void createFiveBins(TH1D* hist[5], int histbins, double histmin, double histmax,string name){
	
	
	for (int iBin = 0; iBin < 5; iBin++)
	{
		
		stringstream ss;
		ss << iBin;
		string fullname = name + ss.str();
		cout << fullname << " nbins " << histbins << " min " << histmin << " max " << histmax << endl;
		
		
		hist[iBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
		
	}
}
void createFourBins(TH1D* hist[4], int histbins, double histmin, double histmax,string name){
	
	
	for (int iBin = 0; iBin < 4; iBin++)
	{
		
		stringstream ss;
		ss << iBin;
		string fullname = name + ss.str();
		cout << fullname << endl;
		
		hist[iBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
		
	}
}
void createPolHists(TH1D* hist[5][nPhisrBins], int histbins, double histmin, double histmax,string name){
	
	for (int i = 0; i < 5; i++)
	{
		
		for (int iBin = 0; iBin < nPhisrBins; iBin++)
		{
			
			stringstream ss;
			ss << iBin;
			
			stringstream ss2;
			ss2 << i;
			
			string fullname = name + ss2.str() + "_phiSRbin_" + ss.str();
			cout << fullname << endl;
			
			hist[i][iBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
			
		}
	}
}

void createPolHistsEta(TH1D* hist[4][nPhisrBins], int histbins, double histmin, double histmax,string name){
	
	for (int i = 0; i < 4; i++)
	{
		
		for (int iBin = 0; iBin < nPhisrBins; iBin++)
		{
			
			stringstream ss;
			ss << iBin;
			
			stringstream ss2;
			ss2 << i;
			
			string fullname = name + ss2.str() + "_phiSRbin_" + ss.str();
			cout << fullname << endl;
			
			hist[i][iBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
			
		}
	}
}


//filling histograms
void fillCorrectPtBin(TH1D* numhist[nPtBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nPtBins][nPhisrBins], double polarization, TH1D* ptHist[nPtBins]){
	
	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
		if (sumVect.Pt() >= ptBinStart[iPt] && sumVect.Pt() < ptBinEnd[iPt])
		{
			numhist[iPt]->Fill(phiSR);
			ptHist[iPt]->Fill(sumVect.Pt());
			
			int phiSRbin = numhist[iPt]->FindBin(phiSR);
			polHist[iPt][phiSRbin-1]->Fill(polarization); //minus 1 because zero is underflow bin
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

//drawing histograms
void drawFiveBins(TH1D* hist[5], TCanvas* can){
	
	
	can->Divide(3, 2);
	
	for (int i = 0; i < 5; i++)
	{
		can->cd(i+1);
		hist[i]->Draw();
	}
	
	
}

void drawFourBins(TH1D* hist[4], TCanvas* can){
	
	
	can->Divide(2, 2);
	
	for (int i = 0; i < 4; i++)
	{
		can->cd(i+1);
		hist[i]->Draw();
	}
	
	
}

void writeFiveBins(TH1D* hist[5]){
	
	for (int i = 0; i < 5; i++)
	{
		hist[i]->Write();
	}
	
	
}

void writeFourBins(TH1D* hist[4]){
	
	for (int i = 0; i < 4; i++)
	{
		hist[i]->Write();
	}
	
	
}


void calcAsym(TH1D* hAut[5], TH1D* hUp[5], TH1D* hDown[5], TH1D* hPol[5][nPhisrBins], double* asym, double* asymE){
	
	for (int i = 0; i < 5; i++)
	{
		
		for (int ibin = 1; ibin <= nPhisrBins; ibin++)
		{
			
			if (ibin <= nPhisrBins*0.5)
			{
				double nUp     = hUp[i]->GetBinContent(ibin);
				double nUpPi   = hUp[i]->GetBinContent(ibin+nPhisrBins*0.5);
				double nDown   = hDown[i]->GetBinContent(ibin);
				double nDownPi = hDown[i]->GetBinContent(ibin+nPhisrBins*0.5);
				
				double avgPol = ( hPol[i][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][ibin-1+nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
				
			}
			else
			{
				
				double nUp     = hUp[i]->GetBinContent(ibin);
				double nUpPi   = hUp[i]->GetBinContent(ibin-nPhisrBins*0.5);
				double nDown   = hDown[i]->GetBinContent(ibin);
				double nDownPi = hDown[i]->GetBinContent(ibin-nPhisrBins*0.5);
				
				double avgPol = ( hPol[i][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][ibin-1-nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
				
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
		
		asym[i]  = f1->GetParameter(0);
		asymE[i] = f1->GetParError(0);
		
		hAut[i]->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
		
	}//end mass or pt bins
}

void calcAsymEta(TH1D* hAut[4], TH1D* hUp[4], TH1D* hDown[4], TH1D* hPol[4][nPhisrBins], double* asym, double* asymE){
	
	for (int i = 0; i < 4; i++)
	{
		
		for (int ibin = 1; ibin <= nPhisrBins; ibin++)
		{
			
			if (ibin <= nPhisrBins*0.5)
			{
				double nUp     = hUp[i]->GetBinContent(ibin);
				double nUpPi   = hUp[i]->GetBinContent(ibin+nPhisrBins*0.5);
				double nDown   = hDown[i]->GetBinContent(ibin);
				double nDownPi = hDown[i]->GetBinContent(ibin+nPhisrBins*0.5);
				
				double avgPol = ( hPol[i][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][ibin-1+nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
				
			}
			else
			{
				
				double nUp     = hUp[i]->GetBinContent(ibin);
				double nUpPi   = hUp[i]->GetBinContent(ibin-nPhisrBins*0.5);
				double nDown   = hDown[i]->GetBinContent(ibin);
				double nDownPi = hDown[i]->GetBinContent(ibin-nPhisrBins*0.5);
				
				double avgPol = ( hPol[i][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][ibin-1-nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
				
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
		
		asym[i]  = f1->GetParameter(0);
		asymE[i] = f1->GetParError(0);
		
		hAut[i]->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
		
	}//end eta bins
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






//MAIN===========================================
//MAIN===========================================
//MAIN===========================================
//MAIN===========================================
//MAIN===========================================


void sqrtBinsSameSign(){
	
	
	//OPTIONS AND CUTS______________
	bool useBlueBeam = true;
	bool useYellowBeam = true;
	bool randomizeSpin = false;
	bool fullEta = true;
	double PI = 3.14159265359;
	
	
	
	
	cout << "\n";
	if (useBlueBeam && useYellowBeam){cout << "using both beams-----" << endl;}
	if (useBlueBeam && !useYellowBeam){cout << "using blue beam------" << endl;}
	if (!useBlueBeam && useYellowBeam){cout << "using yellow beam----" << endl;}
	cout << "\n";
	if (randomizeSpin){cout << "randomizing spin-----" << endl;}
	//______________________________
	
	
  
	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("sameSignPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
	
	
	//SET UP INPUT FILE_____________
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_samesign_4_14/allSameSign_4_14.root");
	
	string outFileName = "./resultsNew_4_22/sameSignFrom4_25Fullrange.root"; 
	
	
	
  //______________________________
	
	
	//SET UP TREE TO RECEIVE INPUT__
	sameSignPair* pair1 = new sameSignPair();
	TTree* pairTree = infile->Get("sameSignTree");
	pairTree->SetBranchAddress("sameSignPair", &pair1);
	//______________________________
	
	
	//SET UP HISTOGRAMS_____________
	//event variable histograms
	/*
	 TH1D* hInvarM    = new TH1D("invarM","invarM",80,0,2);
	 TH1D* hEtaTot	   = new TH1D("etaTot","etaTot",60,-1.5,1.5);
	 TH1D* hPhiR      = new TH1D("hPhiR","hPhiR",60,-4,4);
	 TH1D* hPhiS      = new TH1D("hPhiS","hPhiS",60,-4,4);
	 TH1D* hPhiSR     = new TH1D("hPhiSR","hPhiSR",60,-4,4);
	 TH1D* hTheta     = new TH1D("hTheta","hTheta",30,-0.85,4);
	 TH1D* hCosTheta  = new TH1D("hCosTheta","hCosTheta",80,-1,1);
	 TH1D* hZ         = new TH1D("hZ","hZ",80,0,1);
	 TH1D* hPtot      = new TH1D("hPtot","hPtot",80,0,20);
	 TH1D* hPtTOT     = new TH1D("hPt","hPt",80,0,15);
	 */
	
	//histos for asym analysis	
	double histMin = -PI;
	double histMax =  PI;
	const int binNumber = 16;
	
	TH1D * hNumberUp   = new TH1D("hNumberUp","hNumberUp",binNumber,histMin,histMax);
	TH1D * hNumberDown = new TH1D("hNumberDown","hNumberDown",binNumber,histMin,histMax);
	
	TH1D * hNumberUp_Pt[nPtBins];
	TH1D * hNumberDown_Pt[nPtBins];
	
	TH1D * hNumberUp_Mass[nMassBins]; 
	TH1D * hNumberDown_Mass[nMassBins];
	
	TH1D * hNumberUp_Eta[nEtaBins];   
	TH1D * hNumberDown_Eta[nEtaBins];
	
	createFiveBins(hNumberUp_Pt,binNumber,histMin,histMax,"hNumUp_Ptbin_");
	createFiveBins(hNumberDown_Pt,binNumber,histMin,histMax,"hNumDwn_Ptbin_");
	createFiveBins(hNumberUp_Mass,binNumber,histMin,histMax,"hNumUp_Massbin_");
	createFiveBins(hNumberDown_Mass,binNumber,histMin,histMax,"hNumDwn_Massbin_");
	createFourBins(hNumberUp_Eta,binNumber,histMin,histMax,"hNumUp_Etabin_");
	createFourBins(hNumberDown_Eta,binNumber,histMin,histMax,"hNumDwn_Etabin_");
	
	TH1D* hAut_Pt[nPtBins];
	TH1D* hAut_Mass[nMassBins];
	TH1D* hAut_Eta[nEtaBins];
	
	createFiveBins(hAut_Pt, binNumber, histMin, histMax, "hAut_Ptbin_");
	createFiveBins(hAut_Mass, binNumber, histMin, histMax, "hAut_Massbin_");
	createFourBins(hAut_Eta, binNumber, histMin, histMax, "hAut_Etabin_");
	
	
	/*
	 TH1D* polOfBinUp_Pt[nPtBins][binNumber];
	 TH1D* polOfBinDown_Pt[nPtBins][binNumber];
	 TH1D* polOfBinUp_Mass[nMassBins][binNumber];
	 TH1D* polOfBinDown_Mass[nMassBins][binNumber];
	 TH1D* polOfBinUp_Eta[nEtaBins][binNumber];
	 TH1D* polOfBinDown_Eta[nEtaBins][binNumber];
	 createPolHists(polOfBinUp_Pt, 25, 0, 1, "hPolOfBinUp_Ptbin_");
	 createPolHists(polOfBinDown_Pt, 25, 0, 1, "hPolOfBinDown_Ptbin_");
	 createPolHists(polOfBinUp_Mass, 25, 0, 1, "hPolOfBinUp_Massbin_");
	 createPolHists(polOfBinDown_Mass, 25, 0, 1, "hPolOfBinDown_Massbin_");
	 createPolHists(polOfBinUp_Eta, 25, 0, 1, "hPolOfBinUp_Etabin_");
	 createPolHists(polOfBinDown_Eta, 25, 0, 1, "hPolOfBinDown_Etabin_");
	 */
	
	TH1D* polOfBin_Pt[nPtBins][binNumber];
	TH1D* polOfBin_Mass[nMassBins][binNumber];
	TH1D* polOfBin_Eta[nEtaBins][binNumber];
	createPolHists(polOfBin_Pt, 25, 0, 1, "hPolOfBin_Ptbin_");
	createPolHists(polOfBin_Mass, 25, 0, 1, "hPolOfBin_Massbin_");
	createPolHistsEta(polOfBin_Eta, 25, 0, 1, "hPolOfBin_Etabin_");
	
	
	//HISTOGRAMS TO HOLD PT MASS AND ETA VALES
	TH1D* hPt[nPtBins];
	TH1D* hMass[nMassBins];
	TH1D* hEta[nEtaBins];
	createFiveBins(hPt, 500, 3.0, 50, "hPt_Ptbin_");
	createFiveBins(hMass, 1000, 0.0, 100, "hMass_Massbin_");
	createFourBins(hEta, 20, -1.4, 1.4, "hEta_Etabin_");
	
	
	//TH1D * hDiff  = new TH1D("hNumberSum","hNumberSum",binNumber,histMin,histMax);
	//TH1D * hAut = new TH1D("Aut","Aut",binNumber,histMin,histMax);
	//______________________________
	
	
	
	//BEAM POLARIZATION_____________
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
	
	double avgPolOfBinUp[binNumber];
	double polOfBinSumUp[binNumber];
	
	double avgPerrorOfBinUp[binNumber];
	double pErrorOfBinUp[binNumber];
	
	double avgPolOfBinDown[binNumber];
	double polOfBinSumDown[binNumber];
	
	double avgPerrorOfBinDown[binNumber];
	double pErrorOfBinDown[binNumber];
	
	for (int i=0; i<binNumber; i++)
	{
		avgPolOfBinUp[i] = 0;
		polOfBinSumUp[i] = 0;
		
		avgPerrorOfBinUp[i] = 0;
		pErrorOfBinUp[i] = 0;
		
		avgPolOfBinDown[i] = 0;
		polOfBinSumDown[i] = 0;
		
		avgPerrorOfBinDown[i] = 0;
		pErrorOfBinDown[i] = 0;
		
	}
	//______________________________
	
	
	
	//CUTS__________________________
	double lowLimitPt    = ptBinStart[0];
	double hiLimitPt     = ptBinEnd[4];
	double lowLimitEta   = etaBinStart[0];
	double hiLimitEta    = etaBinEnd[3];
	double lowLimitMass  = massBinStart[0];
	double hiLimitMass   = massBinEnd[4];
	
	//hiLimitEta = 0;
	
	if (fullEta)
	{
		assert(hiLimitEta > 0);
		assert(lowLimitEta < 0);
	}
	
	
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
	
	//random number for randomizing spin.
	//set seed to zero to gaurenty unique numbers each time.
	TRandom3 r;
	r.SetSeed(0);
	
	int rand5 = 0;
	int rand6 = 0;
	int rand9 = 0;
	int rand10 = 0;
	
	
	int totalPairsFinal = 0;
	int blueD = 0;
	int blueU = 0;
	int yellowD = 0;
	int yellowU = 0;
	
	int pionStarNumber = 0;
	int test = 0;
	
	for (int iPair = pionStarNumber; iPair < pairTree->GetEntries(); iPair++)
	{
		
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == pionStarNumber+10000){break;}
		
		pairTree->GetEntry(iPair);
		
		
		if (pair1->withinRadius(0.05, 0.3))
		{
			
			bool triggerFired = false;
			bool fromKaon = false;
			bool passInitialCut_B = false;
			bool passInitialCut_Y = false;
			bool passDCAcut = false;
			
			StTriggerId trigId = pair1->triggerIds();
			
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
			
			
			if (triggerFired)
			{
				
				blueFillNo   = pair1->runInfo().beamFillNumber(1); //1 = blue beam
				yellowFillNo = pair1->runInfo().beamFillNumber(0); //0 = yellow beam 
				
				sum = pair1->pion1LV() + pair1->pion2LV();
				sumB = sum; //blue beam.
				
				
				//yellow beam must rotate around y axis by pi so the eta cut can be the same for both beams. 				
				sumY = sum;
				sumY.RotateY(PI);
				
				/*
				double dcaPlus  = pair1->getPion1()->dca((pair1->getPion1()->vertexIndex())).mag();
				double dcaMinus = pair1->getPion2()->dca((pair1->getPion2()->vertexIndex())).mag();
				
				if (dcaPlus < 1 && dcaMinus < 1)
				{
					passDCAcut = true;
				}
				*/
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
						fillCorrectPtBin(hNumberUp_Pt, sumY, pair1->phiSR('y'), polOfBin_Pt, polarizationOfFill_Y[yellowFillNo],hPt);
						fillCorrectMassBin(hNumberUp_Mass, sumY, pair1->phiSR('y'), polOfBin_Mass, polarizationOfFill_Y[yellowFillNo],hMass);
						if(fullEta){fillCorrectEtaBin(hNumberUp_Eta, sumY, pair1->phiSR('y'), polOfBin_Eta, polarizationOfFill_Y[yellowFillNo],hEta);}
						
					}						
					
					//YELLOW BEAM SPIN DOWN: spin bit 5 and 9
					if (pair1->spinBit() == 5 || pair1->spinBit() == 9)
					{
						fillCorrectPtBin(hNumberDown_Pt, sumY, pair1->phiSR('y'), polOfBin_Pt, polarizationOfFill_Y[yellowFillNo],hPt);
						fillCorrectMassBin(hNumberDown_Mass, sumY, pair1->phiSR('y'), polOfBin_Mass, polarizationOfFill_Y[yellowFillNo],hMass);
						if(fullEta){fillCorrectEtaBin(hNumberDown_Eta, sumY, pair1->phiSR('y'), polOfBin_Eta, polarizationOfFill_Y[yellowFillNo],hEta);}
					}
				}//done with yellow beam
			}//end trigger check
		}//end radius check
	}//end pion tree loop
	
	
	
	
	//CALCULATE ASYMMETRY BIN BY BIN
	cout << "\n";
	cout << "<----CALCULATING ASYMMETRY---->" << endl;
	cout << "\n";
	
	
	
	double asymsPt[5]; 
	double asymsMass[5];
	double asymsEta[4];
	
	double asymsPtE[5];
	double asymsMassE[5];
	double asymsEtaE[4];
	
	cout << "\n";
	cout << "\n";
	
	cout << "\n \n calcing pt asym " << endl;
	calcAsym(hAut_Pt, hNumberUp_Pt, hNumberDown_Pt, polOfBin_Pt, asymsPt, asymsPtE);
	cout << "\n";
	cout << "\n";
	cout << "\n \n calcing mass asym " << endl;
	calcAsym(hAut_Mass, hNumberUp_Mass, hNumberDown_Mass, polOfBin_Mass, asymsMass, asymsMassE);
	cout << "\n";
	cout << "\n";
	if (fullEta)
	{
		cout << "\n \n calcing eta asym " << endl;	
		calcAsymEta(hAut_Eta, hNumberUp_Eta, hNumberDown_Eta, polOfBin_Eta, asymsEta, asymsEtaE);
	}
	
	
	
	
	//PLOT ASYMMETRIES
	cout << "\n";
	cout << "<----PLOTTING ASYMMETRIES---->" << endl;
	cout << "\n";
	
	double ptPoints[5];
	double ptPointsErr[5];
	double massPoints[5];
	double massPointsErr[5];
	double etaPoints[5];
	double etaPointsErr[5];
	
	
	getPtPoints(hPt, ptPoints, ptPointsErr);
	getMassPoints(hMass, massPoints, massPointsErr);
	if(fullEta){getEtaPoints(hEta, etaPoints, etaPointsErr);}
	
	
	TCanvas* cAsymPt = new TCanvas();
	TGraphErrors* gAsymPt = new TGraphErrors(nPtBins,ptPoints,asymsPt,ptPointsErr,asymsPtE);
	
	gAsymPt->Draw("AP");
	
	TCanvas* cAsymMass = new TCanvas();	
	TGraphErrors* gAsymMass = new TGraphErrors(nMassBins,massPoints,asymsMass,massPointsErr,asymsMassE);
	
	gAsymMass->Draw("AP");
	
	if (fullEta)
	{
		TCanvas* cAsymEta = new TCanvas();
		TGraphErrors* gAsymEta = new TGraphErrors(nEtaBins,etaPoints,asymsEta,etaPointsErr,asymsEtaE);
		gAsymEta->Draw("AP");
		
	}
	
	
	
	
	//DRAW HISTOGRAMS
	cout << "\n";
	cout << "<----DRAWING HISTOGRAMS---->" << endl;
	cout << "\n";
	
	
	
	
	TCanvas* cPt   = new TCanvas("cPt","cPt",1200,600);
	TCanvas* cMass = new TCanvas("cMass","cMass",1200,600);
	if(fullEta){TCanvas* cEta  = new TCanvas("cEta","cEta",800,600);}
	
	//drawAllBins(hPt, cPt);
	//drawAllBins(hMass, cMass);
	
	
	
	//polOfBin_Pt[3][8]->Draw();
	
	drawFiveBins(hAut_Pt, cPt);
	drawFiveBins(hAut_Mass, cMass);
  if(fullEta){drawFourBins(hAut_Eta, cEta);}
	
	TFile* outFile = new TFile(outFileName.c_str(),"recreate");
	
	writeFiveBins(hPt);
	writeFiveBins(hMass);
	writeFourBins(hEta);
	writeFiveBins(hAut_Pt);
	writeFiveBins(hAut_Mass);
	if(fullEta){writeFourBins(hAut_Eta);}
	gAsymPt->Write();
	gAsymMass->Write();
	if(fullEta){gAsymEta->Write();}
	
	/*
	cPt->SaveAs("./resultsNew_4_22/ptCanvasFullrangeLoEta.png");
	cPt->SaveAs("./resultsNew_4_22/ptCanvasFullrangeLoEta.pdf");
	cMass->SaveAs("./resultsNew_4_22/massCanvasFullrangeLoEta.png");
	cMass->SaveAs("./resultsNew_4_22/massCanvasFullrangeLoEta.pdf");
	if(fullEta)
	{
		cEta->SaveAs("./resultsNew_4_22/etaCanvasFullrangeHiEta.png");
		cEta->SaveAs("./resultsNew_4_22/etaCanvasFullrangeHiEta.pdf");
	}
	*/
	
	cout << "<----END---->" << endl; 
	
	
}