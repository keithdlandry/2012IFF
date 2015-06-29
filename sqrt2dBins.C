/*
 *  sqrt2dBins.C
 *  2012IFF
 *
 *  Created by Keith Landry on 7/9/14.
 *  UCLA
 *
 */





#include <map>
#include "TF1.h"
#include "TRandom3.h"

/*
//BINING SCHEME FROM Wednesday, June 25, 2014 1:56:23 PM
const int nPtBins    = 9;
const int nEtaBins   = 6;
const int nMassBins  = 9;
const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014

double    ptBinStart[nPtBins] = {3.0, 3.7, 4.15, 4.63, 5.19, 5.87, 6.80, 7.80, 10.0};
double    ptBinEnd[nPtBins]   = {3.7, 4.15, 4.63, 5.19, 5.87, 6.80, 7.8, 10.0, 50.0};  //Anselm used 1000.0 as last point

double    massBinStart[nMassBins] = {0.0, 0.38, 0.44, 0.50, 0.56, 0.62, 0.72, 0.86, 1.1};
double    massBinEnd[nMassBins]   = {0.38, 0.44, 0.50, 0.56, 0.62, 0.72, 0.86, 1.1, 100.5};

double    etaBinStart[nEtaBins] = {-2, -0.6, -0.3, 0.0, 0.4, 0.75};
double    etaBinEnd[nEtaBins]   = {-0.6, -0.3, 0.0, 0.4, 0.75, 2};
//*/

//ANSEML'S BINNING SCHEME========================
//*
 const int nPtBins    = 5;
 const int nEtaBins   = 4;
 const int nMassBins  = 5;
 const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014

//const int nPtBins    = 8;

//double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0, 10, 12,14};
//double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 10, 12, 14, 50.0};  //Anselm used 1000.0 as last point

 double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0};
 double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 50.0};  //Anselm used 1000.0 as last point
 
 double    massBinStart[nMassBins] = {0.0, 0.4, 0.6, 0.8, 1.0};
 double    massBinEnd[nMassBins]   = {0.4, 0.6, 0.8, 1.0, 100.5};
 
 double    etaBinStart[nEtaBins] = {-2,-0.5,0.0,0.5};
 double    etaBinEnd[nEtaBins]   = {-0.5,0.0,0.5, 2};
  
// */

/*
//TEST
const int nPtBins    = 9;
const int nEtaBins   = 2;
const int nMassBins  = 1;
const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014

 double    ptBinStart[nPtBins] = {3.0, 3.7, 4.15, 4.63, 5.19, 5.87, 6.80, 7.80, 10.0};
 double    ptBinEnd[nPtBins]   = {3.7, 4.15, 4.63, 5.19, 5.87, 6.80, 7.8, 10.0, 50.0};  //Anselm used 1000.0 as last point

double    massBinStart[nMassBins] = {0.0};
double    massBinEnd[nMassBins]   = {100.5};

double    etaBinStart[nEtaBins] = {-2,0};
double    etaBinEnd[nEtaBins]   = {0,2};
//*/



//FUNCTIONS======================================
//creating histograms
void create2dNMbins(const int nBins, const int mBins, TH2D* hist[nBins][mBins], int histbinsX, double histminX, double histmaxX, int histbinsY, double histminY, double histmaxY, string name){
	
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		for (int jBin = 0; jBin < mBins; jBin++)
		{
			stringstream ss;
			ss << iBin;
			stringstream ss2;
			ss2 << jBin;
			string fullname = name + ss.str() + "_" + ss2.str();
			cout << fullname << endl;
			
			hist[iBin][jBin] = new TH2D(fullname.c_str(),fullname.c_str(),histbinsX,histminX,histmaxX,histbinsY,histminY,histmaxY);
			
			
		}
		
		
	}
}

void createNMbins(const int nBins, const int mBins, TH1D* hist[nBins][mBins], int histbins, double histmin, double histmax, string name){

	
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		for (int jBin = 0; jBin < mBins; jBin++)
		{
		
			stringstream ss;
			ss << iBin;
			stringstream ss2;
			ss2 << jBin;
			
			string fullname = name + ss.str() + "_" + ss2.str();
			cout << fullname << endl;
			
			hist[iBin][jBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
			
		}
	}
}

void createPolHistsNMbins(const int nBins, const int mBins, TH1D* hist[nBins][mBins][nPhisrBins], int histbins, double histmin, double histmax, string name){

	for (int iBin = 0 ; iBin < nBins; iBin++)
	{
		for (int jBin = 0; jBin < mBins; jBin++)
		{
			for (int iPhisrBin = 0; iPhisrBin < nPhisrBins; iPhisrBin++)
			{
				
				stringstream ss;
				ss << iBin;
				stringstream ss2;
				ss2 << jBin;
				stringstream ss3;
				ss3 << iPhisrBin;
				
				string fullname = name + ss.str() + "_" + ss2.str() + "_phiSRbin_" + ss3.str();
				cout << fullname << endl;
				
				hist[iBin][jBin][iPhisrBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
				
			}
		}
	}	
}

//writing histograms
void writeNMbins(const int nBins, const int mBins, TH1D* hist[nBins][mBins]){
	
	for (int i=0; i<nBins; i++)
	{
		for (int j=0; j<mBins; j++)
		{
			hist[i][j]->Write();
		}
	}	
}
void writeNMbins(const int nBins, const int mBins, TH2D* hist[nBins][mBins]){
	
	for (int i=0; i<nBins; i++)
	{
		for (int j=0; j<mBins; j++)
		{
			hist[i][j]->Write();
		}
	}	
}


//filling histograms
void fillCorrectPtEtaBin(TH1D* numhist[nPtBins][nEtaBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nPtBins][nEtaBins][nPhisrBins], double polarization, TH2D* ptEtaHist[nPtBins][nEtaBins]){

	bool filled = false;

	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
		if (filled){break;}

		for (int iEta = 0; iEta < nEtaBins; iEta++)
		{
			if (sumVect.Pt() >= ptBinStart[iPt] && sumVect.Pt() < ptBinEnd[iPt] && sumVect.Eta() >= etaBinStart[iEta] && sumVect.Eta() < etaBinEnd[iEta])
			{

				numhist[iPt][iEta]->Fill(phiSR);
				ptEtaHist[iPt][iEta]->Fill(sumVect.Pt(), sumVect.Eta());
				
				
				int phiSRbin = numhist[iPt][iEta]->FindBin(phiSR);
				polHist[iPt][iEta][phiSRbin-1]->Fill(polarization);
			
				filled = true;
			}	
		}
	}
}
	
void fillCorrectPtMassBin(TH1D* numhist[nPtBins][nMassBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nPtBins][nMassBins][nPhisrBins], double polarization, TH2D* ptMassHist[nPtBins][nMassBins]){
	
	
	bool filled = false;
	
	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
		if (filled){break;}
		
		for (int iMass = 0; iMass < nMassBins; iMass++)
		{			
			if (sumVect.Pt() >= ptBinStart[iPt] && sumVect.Pt() < ptBinEnd[iPt] && sumVect.M() >= massBinStart[iMass] && sumVect.M() < massBinEnd[iMass])
			{
				
				numhist[iPt][iMass]->Fill(phiSR);
				ptMassHist[iPt][iMass]->Fill(sumVect.Pt(),sumVect.M());
								
				int phiSRbin = numhist[iPt][iMass]->FindBin(phiSR);				
				polHist[iPt][iMass][phiSRbin-1]->Fill(polarization);
				
				filled = true;
			}	
		}
	}
}

void fillCorrectMassEtaBin(TH1D* numhist[nMassBins][nEtaBins], TLorentzVector sumVect, double phiSR, TH1D* polHist[nMassBins][nEtaBins][nPhisrBins], double polarization, TH2D* massEtaHist[nMassBins][nEtaBins]){
	
	bool filled = false;

	for (int iMass = 0; iMass < nMassBins; iMass++)
	{
		if (filled){break;}

		for (int iEta = 0; iEta < nEtaBins; iEta++)
		{
			if (sumVect.M() >= massBinStart[iMass] && sumVect.M() < massBinEnd[iMass] && sumVect.Eta() >= etaBinStart[iEta] && sumVect.Eta() < etaBinEnd[iEta])
			{
				
				numhist[iMass][iEta]->Fill(phiSR);
				massEtaHist[iMass][iEta]->Fill(sumVect.M(),sumVect.Eta());
				
				int phiSRbin = numhist[iMass][iEta]->FindBin(phiSR);
				polHist[iMass][iEta][phiSRbin-1]->Fill(polarization);
				
				filled = true;
      }	
		}
	}
}

//getting average values
void getPtEtaPoints(TH2D* ptEtaHist[nPtBins][nEtaBins], double ptEtaPoints_Pt[nPtBins][nEtaBins], double ptEtaPoints_PtErr[nPtBins][nEtaBins], double ptEtaPoints_Eta[nPtBins][nEtaBins], double ptEtaPoints_EtaErr[nPtBins][nEtaBins]){
	
	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
		for (int iEta = 0; iEta < nEtaBins; iEta++)
		{
			if (ptEtaHist[iPt][iEta]->GetEntries() != 0)
			{

				ptEtaPoints_Pt[iPt][iEta] = ptEtaHist[iPt][iEta]->GetMean(1);
				ptEtaPoints_PtErr[iPt][iEta] = ptEtaHist[iPt][iEta]->GetRMS(1)/(sqrt(ptEtaHist[iPt][iEta]->GetEntries()));
				
				ptEtaPoints_Eta[iPt][iEta] = ptEtaHist[iPt][iEta]->GetMean(2);
				ptEtaPoints_EtaErr[iPt][iEta] = ptEtaHist[iPt][iEta]->GetRMS(2)/(sqrt(ptEtaHist[iPt][iEta]->GetEntries()));
			}
			else
			{
				ptEtaPoints_Pt[iPt][iEta] = -10;
				ptEtaPoints_Eta[iPt][iEta]= -10;
				ptEtaPoints_PtErr[iPt][iEta] = 0;
				ptEtaPoints_EtaErr[iPt][iEta] = 0;
			}

		
		}
	}
}

void getPtMassPoints(TH2D* ptMassHist[nPtBins][nMassBins], double ptMassPoints_Pt[nPtBins][nMassBins], double ptMassPoints_PtErr[nPtBins][nMassBins], double ptMassPoints_Mass[nPtBins][nMassBins], double ptMassPoints_MassErr[nPtBins][nMassBins]){
	
	for (int iPt = 0; iPt < nPtBins; iPt++)
	{
		for (int iMass = 0; iMass < nMassBins; iMass++)
		{

			if (ptMassHist[iPt][iMass]->GetEntries() != 0)
			{
				ptMassPoints_Pt[iPt][iMass] = ptMassHist[iPt][iMass]->GetMean(1);
				ptMassPoints_PtErr[iPt][iMass] = ptMassHist[iPt][iMass]->GetRMS(1)/(sqrt(ptMassHist[iPt][iMass]->GetEntries()));
				
				ptMassPoints_Mass[iPt][iMass] = ptMassHist[iPt][iMass]->GetMean(2);
 				ptMassPoints_MassErr[iPt][iMass] = ptMassHist[iPt][iMass]->GetRMS(2)/(sqrt(ptMassHist[iPt][iMass]->GetEntries()));
				
			}
			else
			{
				ptMassPoints_Pt[iPt][iMass] = -10;
				ptMassPoints_Mass[iPt][iMass]= -10;
				ptMassPoints_PtErr[iPt][iMass] = 0;
				ptMassPoints_MassErr[iPt][iMass] = 0;
			}

			
			
		}
	}
}

void getMassEtaPoints(TH2D* massEtaHist[nMassBins][nEtaBins], double massEtaPoints_Mass[nMassBins][nEtaBins], double massEtaPoints_MassErr[nMassBins][nEtaBins], double massEtaPoints_Eta[nMassBins][nEtaBins], double massEtaPoints_EtaErr[nMassBins][nEtaBins]){
	
	for (int iMass = 0; iMass < nMassBins; iMass++)
	{
		for (int iEta = 0; iEta < nEtaBins; iEta++)
		{
						
			if (massEtaHist[iMass][iEta]->GetEntries() != 0)
			{
				massEtaPoints_Mass[iMass][iEta] = massEtaHist[iMass][iEta]->GetMean(1);
				massEtaPoints_MassErr[iMass][iEta] = massEtaHist[iMass][iEta]->GetRMS(1)/(sqrt(massEtaHist[iMass][iEta]->GetEntries()));
				
				massEtaPoints_Eta[iMass][iEta] = massEtaHist[iMass][iEta]->GetMean(2);
				massEtaPoints_EtaErr[iMass][iEta] = massEtaHist[iMass][iEta]->GetRMS(2)/(sqrt(massEtaHist[iMass][iEta]->GetEntries()));
			}
			else
			{
				massEtaPoints_Mass[iMass][iEta] = -10;
				massEtaPoints_Eta[iMass][iEta]= -10;
				massEtaPoints_MassErr[iMass][iEta] = 0;
				massEtaPoints_EtaErr[iMass][iEta] = 0;
			}
			
			
		}
	}
}



//asymmetry calculation
void calcAsym(const int nBins, const int mBins, TH1D* hAut[nBins][mBins], TH1D* hUp[nBins][mBins], TH1D* hDown[nBins][mBins], TH1D* hPol[nBins][mBins][nPhisrBins], double asym[nBins][mBins], double asymE[nBins][mBins]){
	
	for (int i = 0; i < nBins; i++)
	{
		for (int j = 0; j < mBins; j++)
		{
						
			cout << "ibin " << i << "  jbin " << j << endl;
			
			for (int ibin = 1; ibin <= nPhisrBins; ibin++)
			{
				
				if (ibin <= nPhisrBins*0.5)
				{
					double nUp     = hUp[i][j]->GetBinContent(ibin);
					double nUpPi   = hUp[i][j]->GetBinContent(ibin+nPhisrBins*0.5);
					double nDown   = hDown[i][j]->GetBinContent(ibin);
					double nDownPi = hDown[i][j]->GetBinContent(ibin+nPhisrBins*0.5);
					
					if ((nUp + nUpPi + nDown + nDownPi) !=0)
					{
						double avgPol = ( hPol[i][j][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][j][ibin-1+nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);

					}
				}
				else
				{
					
					double nUp     = hUp[i][j]->GetBinContent(ibin);
					double nUpPi   = hUp[i][j]->GetBinContent(ibin-nPhisrBins*0.5);
					double nDown   = hDown[i][j]->GetBinContent(ibin);
					double nDownPi = hDown[i][j]->GetBinContent(ibin-nPhisrBins*0.5);
					if (nUp + nUpPi + nDown + nDownPi !=0)
					{

					  double avgPol = ( hPol[i][j][ibin-1]->GetMean(1)*(nUp+nDown) + hPol[i][j][ibin-1-nPhisrBins*0.5]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
					}
				}
				
				if ((sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi)) !=0)
				{
				  hAut[i][j]->SetBinContent(ibin, 1/avgPol * ( sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi) ) / ( sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi) ) );
				}
				else
				{
					//hAut[i][j]->SetBinContent(ibin, -10);
				}
				//cout << "111111111" << endl;

				//calc bin error also
				if (avgPol*pow(sqrt(nUp*nDownPi)+sqrt(nDown*nUpPi), 2) != 0)
				{
					double a = sqrt(nUp*nDownPi);
					double b = sqrt(nDown*nUpPi);
					
					double firstTerm = avgPol**2 * (nUpPi*nDown*(nUp+nDownPi) + nDownPi*nUp*(nUpPi+nDown));
					
					//double secondTerm = ((nUp*nDownPi)**2 +(nUpPi*nDown)**2 - 2*nUp*nDown*nUpPi*nDownPi)*realAvgPolE**2;
					double secondTerm = 0;
					
					double binError = 1/avgPol**2 * 1/(a+b)**2 * sqrt(firstTerm + secondTerm);
					
					hAut[i][j]->SetBinError(ibin, binError);

				}
				else
				{
					binError = .01;
					cout << "bin " << ibin << " has problem with error " << endl;
				}
				hAut[i][j]->SetBinError(ibin, binError);
				//cout << "222222222    " << ibin << endl;
			}//end phisrbins
			
			//FIT THE HISTOGRAMS
			TF1* fitFunc = new TF1("fitFunc","[0]*sin(x)",-3.14159265359*.5,3.14159265359*.5);
			
			//cout << "**********" << endl;
			hAut[i][j]->Draw();
			//cout << "+++++++++++" << endl;
			

			hAut[i][j]->Fit("fitFunc", "R");
			//cout << "3333333333" << endl;

			
			TF1* f1 = hAut[i][j]->GetFunction("fitFunc");
			//cout << "444444444444" << endl;

			asym[i][j]  = f1->GetParameter(0);
//			cout << "5555555" << endl;

			asymE[i][j] = f1->GetParError(0);
	//		cout << "66666666" << endl;

			
			hAut[i][j]->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
		//	cout << "77777777777" << endl;	
		}
	}//end mass,Pt, or Eta bins
	
}

	


//MAIN===========================================
//MAIN===========================================
//MAIN===========================================
//MAIN===========================================
//MAIN===========================================


void sqrt2dBins(){
	
	
	
	//OPTIONS AND CUTS______________
	bool useBlueBeam = true;
	bool useYellowBeam = true;
	bool randomizeSpin = false;
	bool fullEta = false;
	
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
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
	
	
	//SET UP INPUT FILE_____________
	//TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");
	
//	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_5_19_5Hits/allPairs_5_19.root");
//	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_8_20_v2/allPairs_8_20.root");
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_3_26_15/allPairs_3_26_15.root");
	
	string outFileName = "./results_3_26_15/2dbinning_3_26_15_HiEta_JP1JP2.root"; 
	
	//string outFileName = "/star/u/klandry/junk.root"; 

	
  //______________________________
	
	
	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
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


	TH1D* hNumberUp_Pt_Eta[nPtBins][nEtaBins];
	TH1D* hNumberDown_Pt_Eta[nPtBins][nEtaBins];
	
	TH1D* hNumberUp_Pt_Mass[nPtBins][nMassBins];
	TH1D* hNumberDown_Pt_Mass[nPtBins][nMassBins];

	TH1D* hNumberUp_Mass_Eta[nMassBins][nEtaBins];
	TH1D* hNumberDown_Mass_Eta[nMassBins][nEtaBins];


	createNMbins(nPtBins, nEtaBins, hNumberUp_Pt_Eta, nPhisrBins, histMin, histMax, "hNumUp_PtEtabin_");	
	createNMbins(nPtBins, nEtaBins, hNumberDown_Pt_Eta, nPhisrBins, histMin, histMax, "hNumDown_PtEtabin_");	

	createNMbins(nPtBins, nMassBins, hNumberUp_Pt_Mass, nPhisrBins, histMin, histMax, "hNumUp_PtMassbin_");
	createNMbins(nPtBins, nMassBins, hNumberDown_Pt_Mass, nPhisrBins, histMin, histMax, "hNumDown_PtMassbin_");
	
	createNMbins(nMassBins, nEtaBins, hNumberUp_Mass_Eta, nPhisrBins, histMin, histMax, "hNumUp_MassEtabin_");
	createNMbins(nMassBins, nEtaBins, hNumberDown_Mass_Eta, nPhisrBins, histMin, histMax, "hNumDown_MassEtabin_");
	
	
	
	TH1D* hAut_Pt_Eta[nPtBins][nEtaBins];
	TH1D* hAut_Mass_Eta[nMassBins][nEtaBins];
	TH1D* hAut_Pt_Mass[nPtBins][nEtaBins];
	
	
	createNMbins(nPtBins, nEtaBins, hAut_Pt_Eta, nPhisrBins, histMin, histMax, "hAut_PtEtabin_");
	createNMbins(nMassBins, nEtaBins, hAut_Mass_Eta, nPhisrBins, histMin, histMax, "hAut_MassEtabin_");
	createNMbins(nPtBins, nMassBins, hAut_Pt_Mass, nPhisrBins, histMin, histMax, "hAut_PtMassbin_");
	
	
	//histos for polarization 
	
	TH1D* polOfBin_Pt_Eta[nPtBins][nEtaBins][nPhisrBins];
	TH1D* polOfBin_Mass_Eta[nMassBins][nEtaBins][nPhisrBins];
	TH1D* polOfBin_Pt_Mass[nPtBins][nMassBins][nPhisrBins];
	
	createPolHistsNMbins(nPtBins, nEtaBins, polOfBin_Pt_Eta, 25, 0, 1, "hPolOfBin_PtEtabin_");
	createPolHistsNMbins(nMassBins, nEtaBins, polOfBin_Mass_Eta, 25, 0, 1, "hPolOfBin_MassEtabin_");
	createPolHistsNMbins(nPtBins, nMassBins, polOfBin_Pt_Mass, 25, 0, 1, "hPolOfBin_PtMassbin_");
	
	//HISTOGRAMS TO HOLD PT MASS AND ETA VALES FOR AVERAGE VALUES AND FIT POINTS	
	TH2D* hPtMass[nPtBins][nMassBins];
	TH2D* hPtEta[nPtBins][nEtaBins];
	TH2D* hMassEta[nMassBins][nEtaBins];
	
	create2dNMbins(nPtBins, nMassBins, hPtMass, 500, ptBinStart[0], ptBinEnd[nPtBins-1], 1000, massBinStart[0], massBinEnd[nMassBins-1], "hPtMass_PtMassbin_");
	create2dNMbins(nPtBins, nEtaBins, hPtEta, 500, ptBinStart[0], ptBinEnd[nPtBins-1], 20, etaBinStart[0], etaBinEnd[nEtaBins-1], "hPtEta_PtEtabin_");
	create2dNMbins(nMassBins, nEtaBins, hMassEta, 1000, massBinStart[0], massBinEnd[nMassBins-1], 20, etaBinStart[0], etaBinEnd[nEtaBins-1], "hMassEta_MassEtabin_");

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
	
	//______________________________
	
	
	//CUTS__________________________
	double lowLimitPt    = ptBinStart[0];
	double hiLimitPt     = ptBinEnd[nPtBins-1];
	double lowLimitMass  = massBinStart[0];
	double hiLimitMass   = massBinEnd[nMassBins-1];
	double lowLimitEta   = etaBinStart[0];
	double hiLimitEta    = etaBinEnd[nEtaBins-1];
	
	
	//double blueLowLimitEta  = 0;
	//double yellowLowLimitEta = 0;  //this is for testing individual beams
	
  lowLimitEta = 0;
	
	if (fullEta)
	{
		assert(hiLimitEta > 0);
		assert(lowLimitEta < 0);
	}
	
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
	
	//random number for randomizing spin.
	//set seed to zero to guaranty unique numbers each time.
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
		//if (iPair == pionStarNumber+1000){break;}
		
		pairTree->GetEntry(iPair);
		
		//fill number 16427 didn't have any polarization data available
		if (pair1->runInfo().beamFillNumber(1) == 16427 && pair1->runInfo().beamFillNumber(0) == 16427)
		{
			continue;
		}
		
		
		if (pair1->withinRadius(0.05, 0.7))
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
      
      /*
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
			*/
			
			if (triggerFired)
			{
				
				blueFillNo   = pair1->runInfo().beamFillNumber(1); //1 = blue beam
				yellowFillNo = pair1->runInfo().beamFillNumber(0); //0 = yellow beam 
				
				sum = pair1->piPlusLV() + pair1->piMinusLV();
				sumB = sum; //blue beam.
				
				
				//yellow beam must rotate around y axis by pi so the eta cut can be the same for both beams. 				
				sumY = sum;
				sumY.RotateY(PI);
				
				
				//blue low limit eta is 0 yellow high limit eta is 0 this is a test
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
						fillCorrectPtEtaBin(hNumberUp_Pt_Eta, sumB, pair1->phiSR('b'), polOfBin_Pt_Eta, polarizationOfFill_B[blueFillNo], hPtEta);					
						fillCorrectPtMassBin(hNumberUp_Pt_Mass, sumB, pair1->phiSR('b'), polOfBin_Pt_Mass, polarizationOfFill_B[blueFillNo], hPtMass);					
						fillCorrectMassEtaBin(hNumberUp_Mass_Eta, sumB, pair1->phiSR('b'), polOfBin_Mass_Eta, polarizationOfFill_B[blueFillNo], hMassEta);					

					}
					
					//BLUE BEAM SPIN DOWN: spin bin 5 and 6
					if (pair1->spinBit() == 5 || pair1->spinBit() == 6)
					{
						fillCorrectPtEtaBin(hNumberDown_Pt_Eta, sumB, pair1->phiSR('b'), polOfBin_Pt_Eta, polarizationOfFill_B[blueFillNo], hPtEta);					
						fillCorrectPtMassBin(hNumberDown_Pt_Mass, sumB, pair1->phiSR('b'), polOfBin_Pt_Mass, polarizationOfFill_B[blueFillNo], hPtMass);					
						fillCorrectMassEtaBin(hNumberDown_Mass_Eta, sumB, pair1->phiSR('b'), polOfBin_Mass_Eta, polarizationOfFill_B[blueFillNo], hMassEta);					

					}
				}//done with blue beam
				
				if (passInitialCut_Y && useYellowBeam)
				{
					//YELLOW BEAM SPIN UP: spin bin 6 and 10
					if (pair1->spinBit() == 6 || pair1->spinBit() == 10)
					{
						fillCorrectPtEtaBin(hNumberUp_Pt_Eta, sumY, pair1->phiSR('y'), polOfBin_Pt_Eta, polarizationOfFill_Y[yellowFillNo], hPtEta);					
						fillCorrectPtMassBin(hNumberUp_Pt_Mass, sumY, pair1->phiSR('y'), polOfBin_Pt_Mass, polarizationOfFill_Y[yellowFillNo], hPtMass);					
						fillCorrectMassEtaBin(hNumberUp_Mass_Eta, sumY, pair1->phiSR('y'), polOfBin_Mass_Eta, polarizationOfFill_Y[yellowFillNo], hMassEta);					

					}						
					
					//YELLOW BEAM SPIN DOWN: spin bit 5 and 9
					if (pair1->spinBit() == 5 || pair1->spinBit() == 9)
					{
						fillCorrectPtEtaBin(hNumberDown_Pt_Eta, sumY, pair1->phiSR('y'), polOfBin_Pt_Eta, polarizationOfFill_Y[yellowFillNo], hPtEta);					
						fillCorrectPtMassBin(hNumberDown_Pt_Mass, sumY, pair1->phiSR('y'), polOfBin_Pt_Mass, polarizationOfFill_Y[yellowFillNo], hPtMass);					
						fillCorrectMassEtaBin(hNumberDown_Mass_Eta, sumY, pair1->phiSR('y'), polOfBin_Mass_Eta, polarizationOfFill_Y[yellowFillNo], hMassEta);					
					}
				}//done with yellow beam
				
				
				
			}//end trigger fired
		}//end within radius
	}//end pair loop
	
	
	
	
	//CALCULATE ASYMMETRY BIN BY BIN
	cout << "\n";
	cout << "<----CALCULATING ASYMMETRY---->" << endl;
	cout << "\n";
	
		
	double asymsPtEta[nPtBins][nEtaBins]; 
	double asymsPtMass[nPtBins][nMassBins];
	double asymsMassEta[nMassBins][nEtaBins];
	
	double asymsPtEtaE[nPtBins][nEtaBins];
	double asymsPtMassE[nPtBins][nMassBins];
	double asymsMassEtaE[nMassBins][nEtaBins];
	
	cout << "\n";
	cout << "\n";
	
	cout << "\n \n calcing Pt/Eta asym " << endl;
	if (fullEta){calcAsym(nPtBins, nEtaBins, hAut_Pt_Eta, hNumberUp_Pt_Eta, hNumberDown_Pt_Eta, polOfBin_Pt_Eta, asymsPtEta, asymsPtEtaE)};	
	cout << "\n";
	cout << "\n";
	cout << "\n \n calcing Pt/Mass asym " << endl;
	calcAsym(nPtBins, nMassBins, hAut_Pt_Mass, hNumberUp_Pt_Mass, hNumberDown_Pt_Mass, polOfBin_Pt_Mass, asymsPtMass, asymsPtMassE);	
	cout << "\n";
	cout << "\n";
	cout << "\n \n calcing Mass/Eta asym " << endl;
	if (fullEta){calcAsym(nMassBins, nEtaBins, hAut_Mass_Eta, hNumberUp_Mass_Eta, hNumberDown_Mass_Eta, polOfBin_Mass_Eta, asymsMassEta, asymsMassEtaE);}	
/*
	for (int i=0; i<nPtBins; i++)
	{
		for (int  j=0; j<nEtaBins; j++)
		{
			cout << i << "   " << j << "   " << asymsPtEta[i][j] << "   " << asymsPtEtaE[i][j] << endl;
		}
	}
	//*/
	
	
	//PLOT ASYMMETRIES
	cout << "\n";
	cout << "<----PLOTTING ASYMMETRIES---->" << endl;
	cout << "\n";
	
	double ptMassPoints_Pt[nPtBins][nMassBins];
	double ptMassPoints_Mass[nPtBins][nMassBins];
	
	double ptMassPoints_PtErr[nPtBins][nMassBins];
	double ptMassPoints_MassErr[nPtBins][nMassBins];

	double massEtaPoints_Mass[nMassBins][nEtaBins];
	double massEtaPoints_Eta[nMassBins][nEtaBins];

	double massEtaPoints_MassErr[nMassBins][nEtaBins];
	double massEtaPoints_EtaErr[nMassBins][nEtaBins];

	double ptEtaPoints_Pt[nPtBins][nEtaBins];
	double ptEtaPoints_Eta[nPtBins][nEtaBins];

	double ptEtaPoints_PtErr[nPtBins][nEtaBins];
	double ptEtaPoints_EtaErr[nPtBins][nEtaBins];
	
	
	getPtEtaPoints(hPtEta, ptEtaPoints_Pt, ptEtaPoints_PtErr, ptEtaPoints_Eta, ptEtaPoints_EtaErr);
	getPtMassPoints(hPtMass, ptMassPoints_Pt, ptMassPoints_PtErr, ptMassPoints_Mass, ptMassPoints_MassErr);
	getMassEtaPoints(hMassEta, massEtaPoints_Mass, massEtaPoints_MassErr, massEtaPoints_Eta, massEtaPoints_EtaErr);

	
	ofstream outputfile;
	outputfile.open("/star/u/klandry/ucladisk/2012IFF/results_3_26_15/2dbinning_3_26_15_HiEta_JP1JP2_test.txt");
	
	
	outputfile << "ptetabins" << endl;
	for (int i=0; i<nPtBins; i++)
	{
		for (int  j=0; j<nEtaBins; j++)
		{
			outputfile << i << "  " << j << "  " << ptEtaPoints_Pt[i][j] << "   " << ptEtaPoints_Eta[i][j] << "  " << asymsPtEta[i][j] << "  " << ptEtaPoints_PtErr[i][j] << "  " << ptEtaPoints_EtaErr[i][j] << "  " << asymsPtEtaE[i][j] << endl;
		}
	}
	outputfile << "massetabins" << endl;
	for (int i=0; i<nMassBins; i++)
	{
		for (int  j=0; j<nEtaBins; j++)
		{
			outputfile << i << "  " << j << "  " << massEtaPoints_Mass[i][j] << "   " << massEtaPoints_Eta[i][j] << "  " << asymsMassEta[i][j] << "  " << massEtaPoints_MassErr[i][j] << "  " << massEtaPoints_EtaErr[i][j] << "  " << asymsMassEtaE[i][j] << endl;
		}
	}
	outputfile << "ptmassbins" << endl;
	for (int i=0; i<nPtBins; i++)
	{
		for (int  j=0; j<nMassBins; j++)
		{
			outputfile << i << "  " << j << "  " << ptMassPoints_Pt[i][j] << "   " << ptMassPoints_Mass[i][j] << "  " << asymsPtMass[i][j] << "  " << ptMassPoints_PtErr[i][j] << "  " << ptMassPoints_MassErr[i][j] << "  " << asymsPtMassE[i][j] << endl;
		}
	}
	
	
	
	//DONT PLOT BECAUSE IT LOOKS LIKE SHIT
	
	/*
	
	TGraph2DErrors* gPtEta = new TGraph2DErrors();
	TGraph2DErrors* gPtMass = new TGraph2DErrors();
	TGraph2DErrors* gMassEta = new TGraph2DErrors();

	gPtEta->SetName("PtEta");
	gPtMass->SetName("PtMass");
	gMassEta->SetName("MassEta");
	
	//gPtEta->Set(nPtBins*nEtaBins);
	//gPtMass->Set(nPtBins*nMassBins);
	//gMassEta->Set(nMassBins*nEtaBins);
	/*
	int ipoint = 0;
	int pointsForPtEta = 0;
	int pointsForPtMass = 0;
	int pointsForMassEta = 0;
	
	
	for (int i=0; i<nPtBins; i++)
	{
		for (int j=0; j<nEtaBins; j++)
		{
			if (asymsPtEta[i][j] != -10 && ptEtaPoints_Pt[i][j] != -10 && ptEtaPoints_Eta[i][j] != -10)  //values set to -10 if there are no pairs in that particular bin
			{
				//gPtEta->SetPoint(ipoint,ptEtaPoints_Pt[i][j],ptEtaPoints_Eta[i][j],asymsPtEta[i][j]);
				//gPtEta->SetPointError(ipoint,ptEtaPoints_PtErr[i][j],ptEtaPoints_EtaErr[i][j],asymsPtEtaE[i][j]);
				ipoint++;
			}
		}
	}
	
	ipoint = 0;
	
	for (int i=0; i<nMassBins; i++)
	{
		for (int j=0; j<nEtaBins; j++)
		{
			if (asymsMassEta[i][j] != -10 && massEtaPoints_Mass[i][j] != -10 && massEtaPoints_Eta[i][j] != -10)
			{
				//gMassEta->SetPoint(ipoint,massEtaPoints_Mass[i][j],massEtaPoints_Eta[i][j],asymsMassEta[i][j]);
				//gMassEta->SetPointError(ipoint,massEtaPoints_MassErr[i][j],massEtaPoints_EtaErr[i][j],asymsMassEtaE[i][j]);
				ipoint++;				
			}
			
		}
	}
	
	  ipoint = 0;
  for (int i=0; i<nPtBins; i++)
	{
		for (int j=0; j<nMassBins; j++)
		{
			if (asymsPtMass[i][j] != -10 && ptMassPoints_Pt[i][j] != -10 && ptMassPoints_Mass[i][j] != -10)
			{
				gPtMass->SetPoint(ipoint,ptMassPoints_Pt[i][j],ptMassPoints_Mass[i][j],asymsPtMass[i][j]);
				gPtMass->SetPointError(ipoint,ptMassPoints_PtErr[i][j],ptMassPoints_MassErr[i][j],asymsPtMassE[i][j]);
				ipoint++;				
			}
		}
	}
	//*/

	TFile* outFile = new TFile(outFileName.c_str(),"recreate");

	
	//gPtEta->Write();	
	//gPtMass->Write();	
	//gMassEta->Write();
	
	//writeNMbins(nPtBins, nEtaBins, hAut_Pt_Eta);
	writeNMbins(nPtBins, nMassBins, hAut_Pt_Mass);
  writeNMbins(nPtBins, nMassBins, hPtMass);
	//writeNMbins(nMassBins, nEtaBins, hAut_Mass_Eta);
	
	
	/*
	hPtMass[0][3]->Write();
	hPtMass[0][4]->Write();
	hPtMass[1][4]->Write();
	hPtMass[2][4]->Write();
	hPtMass[3][4]->Write();
	hPtMass[4][4]->Write();
//*/
	
	
	outFile->Close();

	cout << "<----END---->" << endl; 
}