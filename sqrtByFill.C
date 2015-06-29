/*
 *  sqrtByFill.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/25/14.
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


void calcAsyms(TH1D* hAut, TH1D* hUp, TH1D* hDown, TH1D* hPol[16],double* asym, double* asymE){
	
	int nPhisrBins = 16;
	bool noProblem;
	bool neverProblem = true;
	
	for (int ibin = 1; ibin <= nPhisrBins; ibin++)
	{
		noProblem = false;
		
		if (ibin <= nPhisrBins*0.5)
		{

			int ibinPi = ibin-1+nPhisrBins*0.5;
			
			double nUp     = hUp->GetBinContent(ibin);
			double nUpPi   = hUp->GetBinContent(ibin+nPhisrBins*0.5);
			double nDown   = hDown->GetBinContent(ibin);
			double nDownPi = hDown->GetBinContent(ibin+nPhisrBins*0.5);
		
			if (nUp != 0 && nUpPi != 0 && nDown !=0 && nDownPi != 0)
			{
				double avgPol = ( hPol[ibin-1]->GetMean(1)*(nUp+nDown) + hPol[ibinPi]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
				noProblem = true;
			}
			else
			{
				neverProblem = false;
			}

			

		}
		else
		{
			int ibinPi = ibin-1-nPhisrBins*0.5;

			double nUp     = hUp->GetBinContent(ibin);
			double nUpPi   = hUp->GetBinContent(ibin-nPhisrBins*0.5);
			double nDown   = hDown->GetBinContent(ibin);
			double nDownPi = hDown->GetBinContent(ibin-nPhisrBins*0.5);
			
			if (nUp != 0 && nUpPi != 0 && nDown !=0 && nDownPi != 0)
			{
			  double avgPol = ( hPol[ibin-1]->GetMean(1)*(nUp+nDown) + hPol[ibinPi]->GetMean(1)*(nUpPi+nDownPi) )/( nUp + nUpPi + nDown + nDownPi);
        noProblem = true;	
				
			}
			else
			{
				neverProblem = false;
			}

		}
		//*
		if (nUp != 0 && nUpPi != 0 && nDown !=0 && nDownPi != 0)
		{
			//cout << nUp << "  " << nUpPi << "  " << nDown << "  " << nDownPi << endl;
			//cout << avgPol << endl;
			hAut->SetBinContent(ibin, 1/avgPol * ( sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi) ) / ( sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi) ) );
		}
		//calc bin error also
		if (avgPol*pow(sqrt(nUp*nDownPi)+sqrt(nDown*nUpPi), 2) != 0 && nUp != 0 && nUpPi != 0 && nDown !=0 && nDownPi != 0)
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
		if (nUp != 0 && nUpPi != 0 && nDown !=0 && nDownPi != 0)
		{
			hAut->SetBinError(ibin, binError);
		}
		//*/
	}//end phisrbins
	//*
	//FIT THE HISTOGRAMS
	
	if (neverProblem)
	{
		TF1* fitFunc = new TF1("fitFunc","[0]*sin(x)",-3.14159265359*0.5,3.14159265359*0.5);
		hAut->Fit("fitFunc", "R");
		
		
		TF1* f1 = hAut->GetFunction("fitFunc");
		
		*asym  = f1->GetParameter(0);
		*asymE = f1->GetParError(0);
		
		hAut->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
		
	}
	else
	{
		*asym = 10;
		*asymE = 0;
	}

	
	//*/

}




void sqrtByFill(){


	//OPTIONS AND CUTS______________
	bool useBlueBeam = true;
	bool useYellowBeam = true;
	bool randomizeSpin = false;
	bool fullEta = true;
	
	double PI = 3.14159265359;
	
	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
	
	
	//SET UP INPUT FILE_____________
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");
	
	string outFileName = "./resultsNew_4_22/pairsFrom4_2ByFill.root"; 
	
	
	
  //______________________________
	
	
	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	//______________________________
	
	
	

	
	double histMin = -PI;
	double histMax =  PI;
	const int binNumber = 16;
	
	TH1D * hNumberUp   = new TH1D("hNumberUp","hNumberUp",binNumber,histMin,histMax);
	TH1D * hNumberDown = new TH1D("hNumberDown","hNumberDown",binNumber,histMin,histMax);
	TH1D * hAut = new TH1D("Aut","Aut",binNumber,histMin,histMax);

	
	TH1D* polOfBin[16];
	for (int i = 0; i < 16; i++)
	{
		stringstream ss;
		ss << i;
				
		string fullname = "hPolOfBin_phiSRbin_" + ss.str();
		cout << fullname << endl;
		
		polOfBin[i] = new TH1D(fullname.c_str(),fullname.c_str(),25,0,1);
		
	}
	
	
	
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
	
	
	
	//CUTS__________________________
	double lowLimitPt    = ptBinStart[0];
	double hiLimitPt     = ptBinEnd[4];
	double lowLimitEta   = etaBinStart[3];  //set up do only do eta bin 3
	double hiLimitEta    = etaBinEnd[3];
	double lowLimitMass  = massBinStart[0];
	double hiLimitMass   = massBinEnd[4];
	
	
	
	
	//______________________________
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
	
	
	vector<double> fillAsyms;
	vector<double> fillAsymsE;
	vector<double> fillVec;
	
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
	int runsProcessed = 0;
	
	double currentFillNo = 0;
	double currentRunNo = 0;

	
	for (int iPair = pionStarNumber; iPair < pairTree->GetEntries(); iPair++)
	{
		
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == pionStarNumber+300000){break;}
		
		pairTree->GetEntry(iPair);
		
		//if (runsProcessed > 4){break;} 
		
		
		if (pair1->runInfo().beamFillNumber(1) != currentFillNo && currentFillNo != 0 && currentFillNo != 16427)
		//if (pair1->runInfo().runId() != currentRunNo && currentRunNo != 0)
		{
			runsProcessed++;

			cout << "runsProcessed " << runsProcessed << endl;
			
			double* asym = new double();
			double* asymE = new double();
			calcAsyms(hAut, hNumberUp, hNumberDown, polOfBin, asym, asymE);
						
			fillAsyms.push_back(*asym);
			fillAsymsE.push_back(*asymE);
			fillVec.push_back(runsProcessed);
			
			hNumberUp->Reset();
			hNumberDown->Reset();
			hAut->Reset();
			
			for (int i=0; i<binNumber; i++)
			{
				polOfBin[i]->Reset();
			}
			
			
		}
		else if (currentRunNo == 16427)
		{
			//fillAsyms.push_back(*asym);
			//fillAsymsE.push_back(*asymE);
			//fillVec.push_back(runsProcessed);
			
			hNumberUp->Reset();
			hNumberDown->Reset();
			hAut->Reset();
			
			for (int i=0; i<binNumber; i++)
			{
				polOfBin[i]->Reset();
			}
			
		
		}
		
		
		currentRunNo = pair1->runInfo().runId();
		currentFillNo = pair1->runInfo().beamFillNumber(1);
		
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
				
				sum = pair1->piPlusLV() + pair1->piMinusLV();
				sumB = sum; //blue beam.
				
				
				//yellow beam must rotate around y axis by pi so the eta cut can be the same for both beams. 				
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
						hNumberUp->Fill(pair1->phiSR('b'));
						phiSRbin = hNumberUp->FindBin(pair1->phiSR('b'));
						
						polOfBin[phiSRbin-1]->Fill(polarizationOfFill_B[blueFillNo]);
						/*if (iPair > 39000)
						{
							cout << "polarization = " << polarizationOfFill_B[blueFillNo] << "  " << blueFillNo << endl;
						}*/
						
						
					}
					
					//BLUE BEAM SPIN DOWN: spin bin 5 and 6
					if (pair1->spinBit() == 5 || pair1->spinBit() == 6)
					{
						hNumberDown->Fill(pair1->phiSR('b'));
						phiSRbin = hNumberDown->FindBin(pair1->phiSR('b'));
						
						polOfBin[phiSRbin-1]->Fill(polarizationOfFill_B[blueFillNo]);
						
					}
				}//done with blue beam
				
				if (passInitialCut_Y && useYellowBeam)
				{
					//YELLOW BEAM SPIN UP: spin bin 6 and 10
					if (pair1->spinBit() == 6 || pair1->spinBit() == 10)
					{
						hNumberUp->Fill(pair1->phiSR('y'));
						phiSRbin = hNumberUp->FindBin(pair1->phiSR('y'));
						
						polOfBin[phiSRbin-1]->Fill(polarizationOfFill_Y[yellowFillNo]);
						
					}						
					
					//YELLOW BEAM SPIN DOWN: spin bit 5 and 9
					if (pair1->spinBit() == 5 || pair1->spinBit() == 9)
					{
						hNumberDown->Fill(pair1->phiSR('y'));
						phiSRbin = hNumberDown->FindBin(pair1->phiSR('y'));
						
						polOfBin[phiSRbin-1]->Fill(polarizationOfFill_Y[yellowFillNo]);
					}
				}//done with yellow beam
			}//end trigger check
		}//end radius check
		
		
	}//end pion tree loop
	
	
	cout << "out of tree loop" << endl;
	
	
	cout << fillAsyms.size() << endl;
	
	
	TGraphErrors* gAsymVsFill = new TGraphErrors(fillAsyms.size(), &fillVec[0], &fillAsyms[0], 0, &fillAsymsE[0]);
	
	gAsymVsFill->Draw("AP");
	
	TFile* outFile = new TFile(outFileName.c_str(),"recreate");

	gAsymVsFill->Write();

}





























