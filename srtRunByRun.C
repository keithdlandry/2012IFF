/*
 *  srtRunByRun.C
 *  2012IFF
 *
 *  Created by Keith Landry on 3/28/14.
 *  UCLA
 *
 */


#include <map>
#include "TF1.h"
#include "TRandom3.h"

void srtRunByRun(){

//OPTIONS AND CUTS------------
	bool useBlueBeam = true;
	bool useYellowBeam = true;
	bool randomizeSpin = false;
	
	double PI = 3.14159265359;
	
	cout << "\n";
	if (useBlueBeam && useYellowBeam){cout << "using both beams-----" << endl;}
	if (useBlueBeam && !useYellowBeam){cout << "using blue beam------" << endl;}
	if (!useBlueBeam && useYellowBeam){cout << "using yellow beam----" << endl;}
	cout << "\n";
	if (randomizeSpin){cout << "randomizing spin-----" << endl;}

	
//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;

//SET UP INPUT FILE
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/tests/schedOut_originalSetup/allOrig.root");

	
//SET UP TREE TO RECEIVE INPUT
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	
	
	
	
	
	//SET UP HISTOGRAMS
	
	//event variable histograms
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
	
	//histos for asym analysis	
	double histMin = -PI;
	double histMax =  PI;
	const int binNumber = 16;
	
	TH1D * hNumberUp   = new TH1D("hNumberUp","hNumberUp",binNumber,histMin,histMax);
	TH1D * hNumberDown = new TH1D("hNumberDown","hNumberDown",binNumber,histMin,histMax);
	
	TH1D * hDiff  = new TH1D("hNumberSum","hNumberSum",binNumber,histMin,histMax);
	TH1D * hAut = new TH1D("Aut","Aut",binNumber,histMin,histMax);
	
	
	//BEAM POLARIZATION
	
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
	

	//   ======================================================================
	//============================================================================
	//START ANALYSIS==============================================================
	//============================================================================
	//   ======================================================================
	
	cout << pairTree->GetEntries() << endl;
	
	cout << "\n";
	cout << "<----STARTING ANALYSIS---->" << endl;
  cout << "\n";
	
	
	double blueFillNo;
	double yellowFillNo;
	
	int bin;
	
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
	
	
	vector<double> runAsym;
	vector<double> runAsymErr;
	vector<double> runNum;
	
	
	pairTree->GetEntry(0);
	
	int initialRunID = pair1->runInfo().runId();
	int currentRunID = initialRunID;
	
	
	int irun = 0;
	
	
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//cout << "processing pair number " << iPair << endl;
		
		
		//if (iPair == 80000){break;}
		
		pairTree->GetEntry(iPair);

		
		if (pair1->runInfo().runId() != currentRunID)
		{
			//calc asym for run and clear variables
			
			for (int ibin=1; ibin<=binNumber; ibin++)
			{
				
				if (ibin <= binNumber*0.5)
				{
					double nUp   = hNumberUp->GetBinContent(ibin);
					double nUpPi = hNumberUp->GetBinContent(ibin+binNumber*0.5);
					
					double nDown   = hNumberDown->GetBinContent(ibin);
					double nDownPi = hNumberDown->GetBinContent(ibin+binNumber*0.5);
					
					
					int binIndexPi = ibin+binNumber*0.5;
					
					double avgPolA = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi])/(nUp+nDownPi);
					double avgPolB = (polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUpPi+nDown);
					
					double realAvgPol = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi]+polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUp+nUpPi+nDown+nDownPi);
					
				}
				else
				{
					double nUp   = hNumberUp->GetBinContent(ibin);
					double nUpPi = hNumberUp->GetBinContent(ibin-binNumber*0.5);
					
					double nDown   = hNumberDown->GetBinContent(ibin);
					double nDownPi = hNumberDown->GetBinContent(ibin-binNumber*0.5);
					
					int binIndexPi = ibin-binNumber*0.5;
					
					double avgPolA = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi])/(nUp+nDownPi);
					double avgPolB = (polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUpPi+nDown);
					
					double realAvgPol = (polOfBinSumUp[ibin]+polOfBinSumDown[binIndexPi]+polOfBinSumUp[binIndexPi]+polOfBinSumDown[ibin])/(nUp+nUpPi+nDown+nDownPi);
					
					double realAvgPolE = (pErrorOfBinUp[ibin]+pErrorOfBinDown[binIndexPi]+pErrorOfBinUp[binIndexPi]+pErrorOfBinDown[ibin])/(nUp+nUpPi+nDown+nDownPi);
					
				}
				
				
				cout << avgPolA << "   " << avgPolB << endl;
				
				
				
				
				hDiff->SetBinContent(ibin, sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi));
							
				
				hAut->SetBinContent(ibin, 1/realAvgPol * (sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi)) / (sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi))    );
				
				
				
				
				//error
				if (realAvgPol*pow(sqrt(nUp*nDownPi)+sqrt(nDown*nUpPi), 2) != 0)
				{
					
					double a = sqrt(nUp*nDownPi);
					double b = sqrt(nUpPi*nDown);
					
					
					double firstTerm = realAvgPol**2 * (nUpPi*nDown*(nUp+nDownPi) + nDownPi*nUp*(nUpPi+nDown));
					
					//double secondTerm = ((nUp*nDownPi)**2 +(nUpPi*nDown)**2 - 2*nUp*nDown*nUpPi*nDownPi)*realAvgPolE**2;
					
					double secondTerm = 0;
					
					
					double binError = 1/realAvgPol**2 * 1/(a+b)**2 * sqrt(firstTerm + secondTerm);
					
					
				}	
				else
				{
					double binError = 0.01;
					cout << "bin " << ibin << " Has problem with error" << endl;
				}
				
				hAut->SetBinError(ibin, binError);
				
			}//end Asym calc
			
			
			
			TF1* fitFunc = new TF1("fitFunc","[0]*cos(x)+[1]",-PI,PI);
			hAut->Fit("fitFunc","R");

			
			runAsym.push_back(hAut->GetFunction("fitFunc")->GetParameter(0));
			runAsymErr.push_back(hAut->GetFunction("fitFunc")->GetParError(0));
			
			runNum.push_back(irun);
			
			irun++;
			
			
			hNumberUp->Clear();
			hNumberDown->Clear();
			hDiff->Clear();
			hAut->Clear();
			
			blueU = 0;
			blueD = 0;
			yellowU = 0;
			yellowD = 0;
			
			for (int i = 1; i<=binNumber; i++)
			{
				polOfBinSumDown[i] = 0;
				polOfBinSumUp[i]   = 0;
			}
			
			
			currentRunID = pair1->runInfo().runId();
			
		}//end current run check
		
		
		
		if (pair1->withinRadius(0.05, 0.3))
		{
			
			bool triggerFired = false;
			bool fromKaon = false;
			
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
			
			
			if (pair1->invarientMass() > .4921 && pair1->invarientMass() < .4990)
			{
				fromKaon = true;
			}
			
			
			
			if (triggerFired)
			{
				
				
				blueFillNo   = pair1->runInfo().beamFillNumber(1); //1 = blue beam
				yellowFillNo = pair1->runInfo().beamFillNumber(0); //0 = yellow beam 
				
				//cout << blueFillNo << "  " << yellowFillNo << endl;
				
				
				if (polarizationOfFill_B[blueFillNo] == 0 || polarizationOfFill_Y[yellowFillNo] == 0) //0 is gap
				{
					continue;
				}
				
				
				hInvarM->Fill(pair1->invarientMass());
				
				
				sum = pair1->piPlusLV() + pair1->piMinusLV();
				sumB = sum; //blue beam.
				
				
				//yellow beam must rotate around y axis by pi so the eta cut can be the same for both beams. 				
				sumY = sum;
				sumY.RotateY(PI);
				
				//cout << pair1->phiS('y')-pair1->phiR('y') << "   " << pair1->phiSR('y') << endl;
				
				//option for randomizing spin
				if (randomizeSpin)
				{
					
					int origSpinBit = pair1->spinBit();
					
					double randomSpin = r.Uniform(0, 1);
					
					int randomSpinBit;
					
					if (randomSpin >=0 && randomSpin <0.25)  {randomSpinBit = 5; rand5++;}
					if (randomSpin >=0.25 && randomSpin <0.5){randomSpinBit = 6; rand6++;}
					if (randomSpin >=0.5 && randomSpin <0.75){randomSpinBit = 9; rand9++;}
					if (randomSpin >=0.75 && randomSpin <1.0){randomSpinBit = 10; rand10++;}
					
					
					
					pair1->setSpinBit(randomSpinBit);
					
					
					
				}
				
				
				//cout << pair1->sinPhiSR('b') << "   " << pair1->cosPhiSR('b') << "   " << pair1->phiSR('b') << endl;
				
				
				//MANUALLY ALTER ANGLES FOR TESTING-----
				/*
				 double testPhiS_y = -pair1->phiS('y');
				 double testPhiR_y = pair1->phiR('y');
				 
				 double testPhiS_b = -pair1->phiS('b');
				 double testPhiR_b = pair1->phiR('b');
				 
				 
				 
				 double testPhiSR_y = testPhiS_y - testPhiR_y;
				 
				 double testPhiSR_b = testPhiS_b - testPhiR_b;
				 
				 //cout << testPhiS_b << " " << testPhiR_b << "  " << testPhiS_y << " " << testPhiR_y << endl;
				 
				 
				 if (testPhiSR_y > PI)
				 {
				 testPhiSR_y -= 2*PI;
				 }
				 
				 if (testPhiSR_y < -PI)
				 {
				 testPhiSR_y += 2*PI;
				 }
				 
				 if (testPhiSR_b > PI)
				 {
				 testPhiSR_b -= 2*PI;
				 }
				 
				 if (testPhiSR_b < -PI)
				 {
				 testPhiSR_b += 2*PI;
				 }
				 
				 //cout << testPhiSR_b << "   " << testPhiSR_y << endl;
				 //*/
				
				//CHECK CUTS
				if (sumB.Pt() > ptCutLo && sumB.Pt() < ptCutHi && sumB.M() > mCutLo && sumB.M() < mCutHi && sumB.Eta() > etaCutLo && sumB.Eta() < etaCutHi && useBlueBeam == true)
				{
					
					//BLUE BEAM SPIN UP: spin bin 9 and 10
					if (pair1->spinBit() == 9 || pair1->spinBit() == 10)
					{
						blueU++;
						
						
						//make sure to set it back if you randomized it for up/down.
						//still need origional spin bit to calc anlge.
						if (randomizeSpin){pair1->setSpinBit(origSpinBit);}
						
						bin = hNumberUp->FindBin(pair1->phiSR('b'));
						hNumberUp->Fill(pair1->phiSR('b'));
						
						//bin = hNumberUp->FindBin(testPhiSR_b);
						//hNumberUp->Fill(testPhiSR_b);
						
						
						
						polOfBinSumUp[bin] += polarizationOfFill_B[blueFillNo];
						pErrorOfBinUp[bin] += polErrOfFill_B[blueFillNo];
						
						
						//If rondomized spin, have to set the spin bit back to random
						//for next spin bit check
						if (randomizeSpin){pair1->setSpinBit(randomSpinBit);}
					}
					
					//BLUE BEAM SPIN DOWN: spin bin 5 and 6
					if (pair1->spinBit() == 5 || pair1->spinBit() == 6)
					{
						blueD++;
						
						if (randomizeSpin){pair1->setSpinBit(origSpinBit);}
						
						bin = hNumberDown->FindBin(pair1->phiSR('b'));
						hNumberDown->Fill(pair1->phiSR('b'));
						
						//bin = hNumberDown->FindBin(testPhiSR_b);
						//hNumberDown->Fill(testPhiSR_b);
						
						
						polOfBinSumDown[bin] += polarizationOfFill_B[blueFillNo];
						pErrorOfBinDown[bin] += polErrOfFill_B[blueFillNo];		
						
						if (randomizeSpin){pair1->setSpinBit(randomSpinBit);}
					}
					
				}//end blue cuts
				
				
				
				if (sumY.Pt()>ptCutLo && sumY.Pt() < ptCutHi && sumY.M() > mCutLo && sumY.M() < mCutHi && sumY.Eta() > etaCutLo && sumY.Eta() < etaCutHi && useYellowBeam == true)
				{
					
					//YELLOW BEAM SPIN UP: spin bin 6 and 10
					if (pair1->spinBit() == 6 || pair1->spinBit() == 10)
					{
						
						yellowU++;
						
						if (randomizeSpin){pair1->setSpinBit(origSpinBit);}
						
						bin = hNumberUp->FindBin(pair1->phiSR('y'));
						hNumberUp->Fill(pair1->phiSR('y'));
						
						
						//bin = hNumberUp->FindBin(testPhiSR_y);
						//hNumberUp->Fill(testPhiSR_y);
						
						
						
						polOfBinSumUp[bin] += polarizationOfFill_Y[yellowFillNo];
						pErrorOfBinUp[bin] += polErrOfFill_Y[yellowFillNo];
						
						if (randomizeSpin){pair1->setSpinBit(randomSpinBit);}
					}	
					//YELLOW BEAM SPIN DOWN: spin bit 5 and 9
					if (pair1->spinBit() == 5 || pair1->spinBit() == 9)
					{
						
						yellowD++;
						
						if (randomizeSpin){pair1->setSpinBit(origSpinBit);}
						
						bin = hNumberDown->FindBin(pair1->phiSR('y'));
						hNumberDown->Fill(pair1->phiSR('y'));
						
						//bin = hNumberDown->FindBin(testPhiSR_y);
						//hNumberDown->Fill(testPhiSR_y);
						
						
						polOfBinSumDown[bin] += polarizationOfFill_Y[yellowFillNo];
						pErrorOfBinDown[bin] += polErrOfFill_Y[yellowFillNo];
						
						if (randomizeSpin){pair1->setSpinBit(randomSpinBit);}
					}
				}//end yellow cuts
			}//end triger check
		}//end radius check
	}//end pairTree loop
	
	
	
	//Draw plot of run asym vs run number(time)
	
	
	TGraphErrors* gRunAsym = new TGraphErrors(runAsym.size(),runNum,0,runAsym,runAsymErr);
	

	gRunAsym->Draw();
	
	
	string outFileName = "./results_/runbyrunAsym.root";
	TFile* outFile = new TFile(outFileName.c_str(),"Recreate");

	gRunAsym->Write();
	
	


}