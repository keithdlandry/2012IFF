/*
 *  sqrtMethod.C
 *  2012IFF
 *
 *  Created by Keith Landry on 10/22/13.
 *  UCLA
 *
 */

#include <map>


void sqrtMethod(){

//OPTIONS
	bool useBlueBeam = true;
	bool useYellowBeam = false;
	double PI = 3.14159265359;

	
	

//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;

	
//SET UP INPUT FILE
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOutput/all2012data.root");
	

	
	
	
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
	
		
	
	//   ======================================================================
	//============================================================================
	//START ANALYSIS==============================================================
	//============================================================================
	//   ======================================================================
 
	cout << "\n";
	cout << "<----STARTING ANALYSIS---->" << endl;
  cout << "\n";
	
	
	double blueFillNo;
	double yellowFillNo;
	
	//PION PAIR CUTS:
	double ptCutLo = 0;
	double ptCutHi = 1000;
	double mCutLo = 0;
	double mCutHi = 100;
	double etaCutLo = -1.4;
	double etaCutHi = 1.4;
	//double phiCutLo = -.5;
	//double phiCutHi = .5;
	
	int bin;
	
	TLorentzVector sum;
	TLorentzVector sumY;
	TLorentzVector sumB;
	

	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%1 == 0) {cout << "processing pair number " << iPair << endl;}
	
		
		//if (iPair == 661){continue;}
		
		pairTree->GetEntry(iPair);
		

		
		if (pair1->withinRadius(0.05, 0.3))
		{
			
			bool triggerFired = false;
			
			StTriggerId trigId = pair1->triggerIds();

		
			if (trigId.isTrigger(370601) || trigId.isTrigger(370611) || trigId.isTrigger(370621))
			{
				triggerFired = true;
			}
			
			if (trigId.isTrigger(370501) || trigId.isTrigger(370511) || trigId.isTrigger(370522) || trigId.isTrigger(370531))
			{
				triggerFired = true;
			}
			
			
			if (triggerFired)
			{
				
				
				blueFillNo   = pair1->runInfo().beamFillNumber(1); //1 = blue beam
				yellowFillNo = pair1->runInfo().beamFillNumber(0); //0 = yellow beam 
				
				//cout << blueFillNo << "  " << yellowFillNo << endl;
				

				if (polarizationOfFill_B[blueFillNo] == 0 || polarizationOfFill_Y[yellowFillNo] == 0)
				{
					continue;
				}
				
				
				hInvarM->Fill(pair1->invarientMass());
				
				
				sum = pair1->piPlusLV() + pair1->piMinusLV();
				sumY; //for yellow beam 
				sumB; //for blue beam 
				
				sumB = sum; //blue beam.
				
				sumY.SetPtEtaPhiE(sum.Pt(), -sum.Eta(), sum.Phi(), sum.E()); 
				//yellow beam must reverse direction so the eta cut can be the same for both beams. 
				
				
								
				//CHECK CUTS
				if (sumB.Pt() > ptCutLo && sumB.Pt() < ptCutHi && sumB.M() > mCutLo && sumB.M() < mCutHi && sumB.Eta() > etaCutLo && sumB.Eta() < etaCutHi && useBlueBeam == true)
				{
				
					//BLUE BEAM SPIN UP: spin bin 9 and 10
					if (pair1->spinBit() == 9 || pair1->spinBit() == 10)
					{
						cout << pair1->phiSR('b') << endl;
						if (abs(pair1->phiSR('b')) > PI)
						{
							cout << "------warning-------" << endl;
						}
						
						//bin = hNumberUp->FindBin(1);
						bin = hNumberUp->FindBin(pair1->phiSR('b'));
						hNumberUp->Fill(pair1->phiSR('b'));
						
						cout << "bin= " << bin << endl;

						polOfBinSumUp[bin] += polarizationOfFill_B[blueFillNo];
						pErrorOfBinUp[bin] += polErrOfFill_B[blueFillNo];						
					}
					
					//BLUE BEAM SPIN DOWN: spin bin 5 and 6
					if (pair1->spinBit() == 5 || pair1->spinBit() == 6)
					{
						cout << pair1->phiSR('b') << endl;
						
						if (abs(pair1->phiSR('b')) > PI)
						{
							cout << "------warning-------" << endl;
						}
						

						bin = hNumberDown->FindBin(1);

						bin = hNumberDown->FindBin(pair1->phiSR('b'));
						hNumberDown->Fill(pair1->phiSR('b'));
						
						cout << "bin= " << bin << endl;
						
						polOfBinSumDown[bin] += polarizationOfFill_B[blueFillNo];
						pErrorOfBinDown[bin] += polErrOfFill_B[blueFillNo];						
					}
					
				}//end blue cuts

				
				
				if (sumY.Pt()>ptCutLo && sumY.Pt() < ptCutHi && sumY.M() > mCutLo && sumY.M() < mCutHi && sumY.Eta() > etaCutLo && sumY.Eta() < etaCutHi && useYellowBeam == true)
				{
					
					//YELLOW BEAM SPIN UP: spin bin 6 and 10
					if (pair1->spinBit() == 6 || pair1->spinBit() == 10)
					{
						bin = hNumberUp->FindBin(pair1->phiSR('y'));
						hNumberUp->Fill(pair1->phiSR('y'));
						
						polOfBinSumUp[bin] += polarizationOfFill_Y[yellowFillNo];
						pErrorOfBinUp[bin] += polErrOfFill_Y[yellowFillNo];
					}	
					//YELLOW BEAM SPIN DOWN: spin bit 5 and 9
					if (pair1->spinBit() == 5 || pair1->spinBit() == 9)
					{
						bin = hNumberDown->FindBin(pair1->phiSR('y'));
						hNumberDown->Fill(pair1->phiSR('y'));
					
						polOfBinSumDown[bin] += polarizationOfFill_Y[yellowFillNo];
						pErrorOfBinDown[bin] += polErrOfFill_Y[yellowFillNo];
					}
				}//end yellow cuts
			}//end triger check
		}//end radius check
	}//end pairTree loop
	
	
//CALCULATE ASYMMETRY BIN BY BIN
	cout << "\n";
	cout << "<----CALCULATING ASYMMETRY---->" << endl;
	cout << "\n";
	
	for (int ibin=1; ibin<=binNumber; ibin++)
	{
	
		if (ibin <= binNumber*0.5)
		{
			double nUp   = hNumberUp->GetBinContent(ibin);
			double nUpPi = hNumberUp->GetBinContent(ibin+binNumber*0.5);
			
			double nDown   = hNumberDown->GetBinContent(ibin);
			double nDownPi = hNumberDown->GetBinContent(ibin+binNumber*0.5);
			
			double avgPolA = (polOfBinSumUp[ibin]+polOfBinSumDown[ibin+binNumber*0.5])/(nUp+nDownPi);
			double avgPolB = (polOfBinSumUp[ibin+binNumber*0.5]+polOfBinSumDown[ibin])/(nUpPi+nDown);

		}
		else
		{
			double nUp   = hNumberUp->GetBinContent(ibin);
			double nUpPi = hNumberUp->GetBinContent(ibin-binNumber*0.5);
			
			double nDown   = hNumberDown->GetBinContent(ibin);
			double nDownPi = hNumberDown->GetBinContent(ibin-binNumber*0.5);
			
			double avgPolA = (polOfBinSumUp[ibin]+polOfBinSumDown[ibin-binNumber*0.5])/(nUp+nDownPi);
			double avgPolB = (polOfBinSumUp[ibin-binNumber*0.5]+polOfBinSumDown[ibin])/(nUpPi+nDown);

		}
		

		
		
		
		
		
		hDiff->SetBinContent(ibin, sqrt(nUp*nDownPi) - sqrt(nDown*nUpPi));

		hAut->SetBinContent(ibin, (1/avgPolA * sqrt(nUp*nDownPi) - 1/avgPolB * sqrt(nDown*nUpPi)) / (sqrt(nUp*nDownPi) + sqrt(nDown*nUpPi))    );

		
		
	}//end Asym calc
	
	
	
//DRAW HISTOGRAMS
	
	hInvarM->Draw();
	
	TCanvas* cNup = new TCanvas();
	hNumberUp->Draw();

	TCanvas* cNdown = new TCanvas();
	hNumberDown->Draw();

	TCanvas* cAut = new TCanvas();
	hAut->Draw();
	
	hAut->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
	
	char title[150];
	sprintf(title, "%.1f < P_{T}^{#pi^{+}#pi^{-}} < %.1f  %.1f < M_{inv}^{#pi^{+}#pi^{-}} < %.1f  %.1f < #eta^{#pi^{+}#pi^{-}} < %.1f", ptCutLo, ptCutHi, mCutLo, mCutHi, etaCutLo, etaCutHi);
	
	hAut->SetTitle(title);
	
	
	
	
	cout << "---END---" << endl; 
}