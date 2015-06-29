/*
 *  pairQA.C
 *  2012IFF
 *
 *  Created by Keith Landry on 1/24/14.
 *  UCLA
 *
 */
//*
//#include "TProfile.h"
const int nPtBins = 9;
const int nEtaBins = 6;
const int nMassBins =9;
const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014

//double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0};
//double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 50.0};  //Anselm used 1000.0 as last point

//double    massBinStart[nMassBins] = {0.0, 0.4, 0.6, 0.8, 1.0};
//double    massBinEnd[nMassBins]   = {0.4, 0.6, 0.8, 1.0, 100.5};

double    etaBinStart[nEtaBins] = {-2, -0.6, -0.3, 0.0, 0.4, 0.75};
double    etaBinEnd[nEtaBins]   = {-0.6, -0.3, 0.0, 0.4, 0.75, 2};
//*/

double    massBinStart[nMassBins] = {0.0, 0.38, 0.44, 0.50, 0.56, 0.62, 0.72, 0.86, 1.1};
double    massBinEnd[nMassBins]   = {0.38, 0.44, 0.50, 0.56, 0.62, 0.72, 0.86, 1.1, 100.5};

double    ptBinStart[nPtBins] = {3.0, 3.7, 4.15, 4.63, 5.19, 5.87, 6.80, 7.80, 10.0};
double    ptBinEnd[nPtBins]   = {3.7, 4.15, 4.63, 5.19, 5.87, 6.80, 7.8, 10.0, 50.0};  //Anselm used 1000.0 as last point

void pairQA(){
	
	
	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
	
	
	//SET UP INPUT FILE_____________
	
//	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/noSigmaCut2/noSigmaCut2All.root");
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_9_9/allPairs_9_9.root");
	

	
	
	
  //______________________________
	
	
	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	//______________________________
	
	
	cout << pairTree->GetEntries() << endl;
	pairTree->GetEntry(0);
	
	
	/*
	TH1D* hNsigma1 = new TH1D("hNsigma1","hNsigma1",300,-10,10);
	TH1D* hNsigma2 = new TH1D("hNsigma2","hNsigma2",300,-10,10);
	TH1D* hNsigma3 = new TH1D("hNsigma3","hNsigma3",300,-10,10);
	TH1D* hNsigma4 = new TH1D("hNsigma4","hNsigma4",300,-10,10);
	TH1D* hNsigma4 = new TH1D("hNsigma4","hNsigma4",300,-10,10);
	TH1D* hNsigma4 = new TH1D("hNsigma4","hNsigma4",300,-10,10);

	TH1D* hNsigmaHi = new TH1D("hNsigmaHi","hNsigmaHi",300,-10,10);
//*/
	
	
	
	TH1D* hNsigma[20];
	double etastart[20];
	double etaend[20];
	
	for (int i=0; i<20; i++)
	{
		stringstream ss;
		ss << i;
		
		string histname = "nSigmaPionBin_" + ss.str();
		
		hNsigma[i] = new TH1D(histname.c_str(),histname.c_str(),300,-10,10);
		
		etastart[i] = -2+i*0.2;
		etaend[i] = -2+(i+1)*0.2;
		
		cout << etastart[i] << "  " << etaend[i] << endl;
		
	}
	
	
	
	TH1D* hPtofMass[nMassBins];
	
	for (int i=0; i<nMassBins; i++)
	{
		stringstream ss;
		ss << i;
		
		string histnamept = "hPtofMass_" + ss.str();

		hPtofMass[i] = new TH1D(histnamept.c_str(),histnamept.c_str(),300,0,25);
	}
	
	
	TH1D* hMassofPt[nPtBins];
	
	for (int i=0; i<nPtBins; i++)
	{
		stringstream ss;
		ss << i;
		
		string histnamemass = "hMassofPt_" + ss.str();
		
		hMassofPt[i] = new TH1D(histnamemass.c_str(),histnamemass.c_str(),300,0,2);
	}
	
	
	
	
	
	//*
	TH1D* hPtinMassBin1 = new TH1D("hPtinMassBin1","hPtinMassBin1",500,0,50);
	TH1D* hPtinMassBin2 = new TH1D("hPtinMassBin2","hPtinMassBin2",500,0,50);
	TH1D* hPtinMassBin3 = new TH1D("hPtinMassBin3","hPtinMassBin3",500,0,50);
	TH1D* hPtinMassBin4 = new TH1D("hPtinMassBin4","hPtinMassBin4",500,0,50);
	TH1D* hPtinMassBin5 = new TH1D("hPtinMassBin5","hPtinMassBin5",500,0,50);
	//*/
	
	TH2D* hPtEta = new TH2D("","",100,0,12,100,-2,2);
	
	TH1D* hTheta = new TH1D("","",100,-7,7);
	
//*
	TH1D* hInvarM    = new TH1D("invarM","invarM",800,0,5);
	TH1D* hEtaTot	   = new TH1D("etaTot","etaTot",60,-2,2);
	TH1D* hPhiRy      = new TH1D("hPhiRy","hPhiRy",60,-4,4);
	TH1D* hPhiSy      = new TH1D("hPhiSy","hPhiSy",60,-4,4);
	TH1D* hPhiSRy     = new TH1D("hPhiSRy","hPhiSRy",60,-4,4);
	TH1D* hPhiRb      = new TH1D("hPhiRb","hPhiRb",60,-4,4);
	TH1D* hPhiSb      = new TH1D("hPhiSb","hPhiSb",60,-4,4);
	TH1D* hPhiSRb     = new TH1D("hPhiSRb","hPhiSRb",60,-4,4);
	TH1D* hTheta     = new TH1D("hTheta","hTheta",30,-0.85,4);
	TH1D* hCosTheta  = new TH1D("hCosTheta","hCosTheta",80,-1,1);
	TH1D* hZ         = new TH1D("hZ","hZ",80,0,1);
	TH1D* hPtot      = new TH1D("hPtot","hPtot",80,0,20);
	TH1D* hPtTOT     = new TH1D("hPt","hPt",80,0,30);
	TH1D* hPhi = new TH1D("hPhi","hPhi",60,-3.14159,3.14159);
	
	TH2D* hMPt = new TH2D("hMPt","hMPt",80,0,15,80,0,5);

	
	TH1D* hInvarM_B    = new TH1D("invarM_B","invarM_B",80,0,2);
	TH1D* hEtaTot_B	   = new TH1D("etaTot_B","etaTot_B",60,-2,2);
	TH1D* hPhiRy_B      = new TH1D("hPhiRy_B","hPhiRy_B",60,-4,4);
	TH1D* hPhiSy_B      = new TH1D("hPhiSy_B","hPhiSy_B",60,-4,4);
	TH1D* hPhiSRy_B     = new TH1D("hPhiSRy_B","hPhiSRy_B",60,-4,4);
	TH1D* hPhiRb_B      = new TH1D("hPhiRb_B","hPhiRb_B",60,-4,4);
	TH1D* hPhiSb_B      = new TH1D("hPhiSb_B","hPhiSb_B",60,-4,4);
	TH1D* hPhiSRb_B     = new TH1D("hPhiSRb_B","hPhiSRb_B",60,-4,4);
	TH1D* hTheta_B     = new TH1D("hTheta_B","hTheta_B",30,-0.85,4);
	TH1D* hCosTheta_B  = new TH1D("hCosTheta_B","hCosTheta_B",80,-1,1);
	TH1D* hZ_B         = new TH1D("hZ_B","hZ_B",80,0,1);
	TH1D* hPtot_B      = new TH1D("hPtot_B","hPtot_B",80,0,20);
	TH1D* hPtTOT_B     = new TH1D("hPt_B","hPt_B",80,0,15);
	TH1D* hPhi_B = new TH1D("hPhi_B","hPhi_B",60,-3.14159,3.14159);

	TH1D* hInvarM_Y    = new TH1D("invarM_Y","invarM_Y",80,0,2);
	TH1D* hEtaTot_Y	   = new TH1D("etaTot_Y","etaTot_Y",60,-2,2);
	TH1D* hPhiRy_Y      = new TH1D("hPhiRy_Y","hPhiRy_Y",60,-4,4);
	TH1D* hPhiSy_Y      = new TH1D("hPhiSy_Y","hPhiSy_Y",60,-4,4);
	TH1D* hPhiSRy_Y     = new TH1D("hPhiSRy_Y","hPhiSRy_Y",60,-4,4);
	TH1D* hPhiRb_Y      = new TH1D("hPhiRb_Y","hPhiRb_Y",60,-4,4);
	TH1D* hPhiSb_Y      = new TH1D("hPhiSb_Y","hPhiSb_Y",60,-4,4);
	TH1D* hPhiSRb_Y     = new TH1D("hPhiSRb_Y","hPhiSRb_Y",60,-4,4);
	TH1D* hTheta_Y     = new TH1D("hTheta_Y","hTheta_Y",30,-0.85,4);
	TH1D* hCosTheta_Y  = new TH1D("hCosTheta_Y","hCosTheta_Y",80,-1,1);
	TH1D* hZ_Y         = new TH1D("hZ_Y","hZ_Y",80,0,1);
	TH1D* hPtot_Y      = new TH1D("hPtot_Y","hPtot_Y",80,0,20);
	TH1D* hPtTOT_Y     = new TH1D("hPt_Y","hPt_Y",80,0,15);
	TH1D* hPhi_Y = new TH1D("hPhi_Y","hPhi_Y",60,-3.14159,3.14159);
	
	TH1D* hSPhAngle = new TH1D("hSPhAngle","hSPhAngle",60,-6,6);

  
  TH1D* hPt_JP0 = new TH1D("hPt_JP0","hPt_JP0",50,0,15);
  TH1D* hPt_JP1 = new TH1D("hPt_JP1","hPt_JP1",50,0,15);
  TH1D* hPt_JP2 = new TH1D("hPt_JP2","hPt_JP2",50,0,15);
  
  TH1D* hEta_JP0 = new TH1D("hEta_JP0","hEta_JP0",25,-2,2);
  TH1D* hEta_JP1 = new TH1D("hEta_JP1","hEta_JP1",25,-2,2);
  TH1D* hEta_JP2 = new TH1D("hEta_JP2","hEta_JP2",25,-2,2);
  
  TH1D* hPhi_JP0 = new TH1D("hPhi_JP0","hPhi_JP0",50,-7,7);
  TH1D* hPhi_JP1 = new TH1D("hPhi_JP1","hPhi_JP1",50,-7,7);
  TH1D* hPhi_JP2 = new TH1D("hPhi_JP2","hPhi_JP2",50,-7,7);
  
  TH1D* hM_JP0 = new TH1D("hM_JP0","hM_JP0",20,0,2);
  TH1D* hM_JP1 = new TH1D("hM_JP1","hM_JP1",20,0,2);
  TH1D* hM_JP2 = new TH1D("hM_JP2","hM_JP2",20,0,2);
  
	
	//*/
	/*
	
	TH1D* hDcaP = new TH1D("hDcaP","hDcaP", 80, 0, 10);
	TH1D* hDcaM = new TH1D("hDcaM","hDcaM", 80, 0, 10);
	*/

	TH2D* hThetaPt = new TH2D("hThetaPt","hThetaPt",40,0,3.14159,20,0,20);
	
	double PI = 3.14159265359;
	
	double lowLimitPt    = ptBinStart[0];
	double hiLimitPt     = ptBinEnd[4];
	double lowLimitEta   = etaBinStart[0];
	double hiLimitEta    = etaBinEnd[3];
	double lowLimitMass  = massBinStart[0];
	double hiLimitMass   = massBinEnd[4];
	
	
	TLorentzVector sum;
	TLorentzVector sumY;
	TLorentzVector sumB;
	
	
  
  
  int otherThanJP12 = 0;
  int withJP12 = 0;
  
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == 1000000){break;}

		
		pairTree->GetEntry(iPair);
		
		
		if (pair1->withinRadius(0.05, 0.3))
		{
			
			bool triggerFired = false;
			bool JP0Fired = false;
      bool JP1Fired = false;
      bool JP2Fired = false;
      
			StTriggerId trigId = pair1->triggerIds();
      
      if (trigId.isTrigger(370611) || trigId.isTrigger(370621))
      {
        withJP12++;
      }
      else if (trigId.isTrigger(370601) || trigId.isTrigger(370641) || trigId.isTrigger(370501) || trigId.isTrigger(370511) || trigId.isTrigger(370522) || trigId.isTrigger(370531))
      {
        otherThanJP12++;
      }
      
      
			
      /*cout << "\n";			
      if (trigId.isTrigger(370601)){cout << "JP0" << endl;}
      if (trigId.isTrigger(370611)){cout << "JP1" << endl;}
      if (trigId.isTrigger(370621)){cout << "JP2" << endl;}
			cout << "\n";
      */
      //TRIGGERS: 370601[JPO] 370611[JP1] 370621[JP2] 370641[AJP]
			if (trigId.isTrigger(370601) || trigId.isTrigger(370611) || trigId.isTrigger(370621) || trigId.isTrigger(370641))
			{
				triggerFired = true;
        
        if      (trigId.isTrigger(370621)){JP2Fired = true;}
        else if (trigId.isTrigger(370611)){JP1Fired = true;}
        else if (trigId.isTrigger(370601)){JP0Fired = true;}
        
        
			}
      //BHT0VPD,BHT1VPD,BHT2BBC,BHT2
			if (trigId.isTrigger(370501) || trigId.isTrigger(370511) || trigId.isTrigger(370522) || trigId.isTrigger(370531))
			{
				triggerFired = true;
			}
			
			
			if (triggerFired)
			{
				
				
				sum = pair1->piPlusLV() + pair1->piMinusLV();
				sumY; //for yellow beam 
				sumB; //for blue beam 
				
				sumB = sum; //blue beam.
				
				sumY = sum;
				sumY.RotateY(PI);
        
        
        if (JP2Fired)
        {
          hPt_JP2->Fill(sum.Pt());
          hEta_JP2->Fill(sum.Eta());
          hPhi_JP2->Fill(sum.Phi());
          hM_JP2->Fill(sum.M());
        }        
        else if (JP1Fired)
        {
          hPt_JP1->Fill(sum.Pt());
          hEta_JP1->Fill(sum.Eta());
          hPhi_JP1->Fill(sum.Phi());
          hM_JP1->Fill(sum.M());
        }
        else if (JP0Fired)
        {
          hPt_JP0->Fill(sum.Pt());
          hEta_JP0->Fill(sum.Eta());
          hPhi_JP0->Fill(sum.Phi());
          hM_JP0->Fill(sum.M());
        }
        
        
				/*
				cout << "\n";
				cout << "  Blue: x = " << sumB.X() << "  y  = " << sumB.Y() << "  z = " << sumB.Z() << endl;
				cout << "Yellow: x = " << sumY.X() << "  y  = " << sumY.Y() << "  z = " << sumY.Z() << endl;
				*/
				/*
				if (sum.Eta() > -2 && sum.Eta() <= -0.5)
				{
					hNsigma1->Fill(pair1->piPlus()->nSigmaPion());
					hNsigma1->Fill(pair1->piMinus()->nSigmaPion());
					
				}
				
				if (sum.Eta() > -0.5 && sum.Eta() <= 0.0)
				{
					hNsigma2->Fill(pair1->piPlus()->nSigmaPion());
					hNsigma2->Fill(pair1->piMinus()->nSigmaPion());
					
				}
				
				if (sum.Eta() > 0.0 && sum.Eta() <= 0.5)
				{
					hNsigma3->Fill(pair1->piPlus()->nSigmaPion());
					hNsigma3->Fill(pair1->piMinus()->nSigmaPion());
					
				}
				
				if (sum.Eta() > 0.5 && sum.Eta() <= 2)
				{
					hNsigma4->Fill(pair1->piPlus()->nSigmaPion());
					hNsigma4->Fill(pair1->piMinus()->nSigmaPion());
					
				}
				
				if (sum.Eta() > 0.5 && sum.Eta() <= 1)
				{
					hNsigmaHi->Fill(pair1->piPlus()->nSigmaPion());
					hNsigmaHi->Fill(pair1->piMinus()->nSigmaPion());
					
				}
				//*/
				
				//*
				for (int ieta=0; ieta<20; ieta++)
				{
					
				
					if (sum.Eta() > etastart[ieta] && sum.Eta() < etaend[ieta])
					{
						
						hNsigma[ieta]->Fill(pair1->piPlus()->nSigmaPion());
						hNsigma[ieta]->Fill(pair1->piMinus()->nSigmaPion());
						
					}
					
				}
				//*/
				
				/*
				if (sum.Eta()>0)
				{
					for (int imass=0; imass<nMassBins; imass++)
					{
						if (pair1->invarientMass() > massBinStart[imass] && pair1->invarientMass() <= massBinEnd[imass])
						{
							hPtofMass[imass]->Fill(sum.Pt());
						}
					}
				}
				 //*/
				/*
				if (sum.Eta()>0)
				{
					for (int ipt=0; ipt<nPtBins; ipt++)
					{
						if (sum.Pt() > ptBinStart[ipt] && sum.Pt() <= ptBinEnd[ipt])
						{
							hMassofPt[ipt]->Fill(pair1->invarientMass());
						}
					}
				}
				
				//*/
				
				hTheta->Fill(pair1->theta());
				
				
				
				hThetaPt->Fill(pair1->theta(), sum.Pt());
				
				//*/
				///////////////
				/*
				if (sum.M() > 0  && sum.M() <= 0.4)
				{
					hPtinMassBin1->Fill(sum.Pt());
					hPtinMassBin1->Fill(sum.Pt());
					
				}
				//*
				
				if (sum.M() > 0.4 && sum.M() <= 0.6)
				{
					hPtinMassBin2->Fill(sum.Pt());
					hPtinMassBin2->Fill(sum.Pt());
					
				}
				
				if (sum.M() > 0.6 && sum.M() <= 0.8)
				{
					hPtinMassBin3->Fill(sum.Pt());
					hPtinMassBin3->Fill(sum.Pt());
					
				}
				
				if (sum.M() > 0.8 && sum.M() <= 1)
				{
					hPtinMassBin4->Fill(sum.Pt());
					hPtinMassBin4->Fill(sum.Pt());
					
				}
				
				if (sum.M() > 1 && sum.M() <= 100)
				{
					hPtinMassBin5->Fill(sum.Pt());
					hPtinMassBin5->Fill(sum.Pt());
					
				}
				
				
				//*/
				
				//hPtEta->Fill(sum.Pt(),sum.Eta());
				//hPtEta->Fill(pair1->piPlus()->pt(),pair1->piPlus()->eta());
				//hPtEta->Fill(pair1->piMinus()->pt(),pair1->piMinus()->eta());
				
				
				
        //hInvarM->Fill(pair1->invarientMass());
				if (sum.Eta() > -2 && sum.Eta() < 2)
				{
          hInvarM->Fill(pair1->invarientMass());
				}
				/*
				if (sum.Eta() > -3)
				{
					hEtaTot->Fill(sum.Eta());
					hPhiRb->Fill(pair1->phiR('b'));
					hPhiSb->Fill(pair1->phiS('b'));
					hPhiSRb->Fill(pair1->phiSR('b'));
					hPhiRy->Fill(pair1->phiR('y'));
					hPhiSy->Fill(pair1->phiS('y'));
					hPhiSRy->Fill(pair1->phiSR('y'));
					hTheta->Fill(pair1->theta());
					hPhi->Fill(sum.Phi());
					hPtTOT->Fill(sum.Pt());
					
					hMPt->Fill(sum.Pt(), sum.M());
					//hInvarM->Fill(pair1->invarientMass());

					
				}
				
				
				if (sumB.Pt() >= lowLimitPt && sumB.Pt() <= hiLimitPt && sumB.M() >= lowLimitMass && sumB.M() <= hiLimitMass && sumB.Eta() >= lowLimitEta && sumB.Eta() <= hiLimitEta)
				{
					hEtaTot_B->Fill(sumB.Eta());
					hPhiRb_B->Fill(pair1->phiR('b'));
					hPhiSb_B->Fill(pair1->phiS('b'));
					hPhiSRb_B->Fill(pair1->phiSR('b'));
					hPhiRy_B->Fill(pair1->phiR('y'));
					hPhiSy_B->Fill(pair1->phiS('y'));
					hPhiSRy_B->Fill(pair1->phiSR('y'));
					hTheta_B->Fill(pair1->theta());
					hPhi_B->Fill(sumB.Phi());
					hPtTOT_B->Fill(sumB.Pt());
					
				}
				if (sumY.Pt() >= lowLimitPt && sumY.Pt() <= hiLimitPt && sumY.M() >= lowLimitMass && sumY.M() <= hiLimitMass && sumY.Eta() >= lowLimitEta && sumY.Eta() <= hiLimitEta)
				{
					hEtaTot_Y->Fill(sumY.Eta());
					hPhiRb_Y->Fill(pair1->phiR('b'));
					hPhiSb_Y->Fill(pair1->phiS('b'));
					hPhiSRb_Y->Fill(pair1->phiSR('b'));
					hPhiRy_Y->Fill(pair1->phiR('y'));
					hPhiSy_Y->Fill(pair1->phiS('y'));
					hPhiSRy_Y->Fill(pair1->phiSR('y'));
					hTheta_Y->Fill(pair1->theta());
					hPhi_Y->Fill(sumY.Phi());
					hPtTOT_Y->Fill(sumY.Pt());
				
				}
				//*/
				
				
				
			}//end trigger
			
			
			
		}//end radius
		
		
	}//end pairTree loop
	
	///*
	TCanvas* c1 = new TCanvas();
	hEtaTot->Draw();
/*
	TCanvas* c2 = new TCanvas();
	hPhi->Draw();
	
	TCanvas* c3 = new TCanvas();
	hPhiRy->Draw();
	
	TCanvas* c4 = new TCanvas();
	hPhiSy->Draw();
	
	TCanvas* c5 = new TCanvas();
	hPhiSRy->Draw();
	
	TCanvas* c10 = new TCanvas();
	hPhiRb->Draw();
	
	TCanvas* c11 = new TCanvas();
	hPhiSb->Draw();
	
	TCanvas* c12 = new TCanvas();
	hPhiSRb->Draw();	
	
	TCanvas* c6 = new TCanvas();
	hTheta->Draw();
	
	TCanvas* c7 = new TCanvas();
	hPtTOT->Draw();
*/
	//TCanvas* c8 = new TCanvas();
	//hDcaP->Draw();

	//TCanvas* c9 = new TCanvas();
	//hDcaM->Draw();

	/*
	
	TCanvas* c13 = new TCanvas();
	hPtTOT_B->Draw();

	TCanvas* c14 = new TCanvas();
	hPtTOT_Y->Draw();

	TCanvas* c15 = new TCanvas();
	hEtaTot_B->Draw();

	TCanvas* c16 = new TCanvas();
	hEtaTot_Y->Draw();
*/
	
	
	
	
	
	//*/
	
	//hDcaP->Write();
	//hDcaM->Write();

	/*
	hNsigma1->Write();
	hNsigma2->Write();
	hNsigma3->Write();
	hNsigma4->Write();
	hNsigmaHi->Write();
	//*/
	//*
	
	for (int i=0; i<20; i++)
	{
		//hNsigma[i]->Write();
	}

	for (int i=0; i<nMassBins; i++)
	{
		//hPtofMass[i]->Write();
	}
	for (int i=0; i<nPtBins; i++)
	{
		//hMassofPt[i]->Write();
	}
	
	//hPtEta->Draw("COLZ");
	
	/*hPtinMassBin1->Write();
	hPtinMassBin2->Write();
	hPtinMassBin3->Write();
	hPtinMassBin4->Write();
	hPtinMassBin5->Write();
	//*/
	
	//hTheta->Draw();
	
  
  //TFile* outFile = new TFile("/star/u/klandry/ucladisk/2012IFF/pairQA/indivTrigQAFullData.root","recreate");
	//TFile* outFile = new TFile("/star/u/klandry/ucladisk/2012IFF/pairQA/avgPtOfMassBins_rad2.root","recreate");

  
//  TFile* outFile = new TFile("/star/u/klandry/ucladisk/2012IFF/pairQA/nSigPionJP1JP2_9_9_Rad03.root","recreate");
  TFile* outFile = new TFile("/star/u/klandry/ucladisk/2012IFF/pairQA/qa_9_9_invMass.root","recreate");

  for (int ieta=0; ieta<20; ieta++)
  {
    
    
    if (sum.Eta() > etastart[ieta] && sum.Eta() < etaend[ieta])
    {
      
     // hNsigma[ieta]->write():
      
    }
    
  }
  
  
  
  
  /*
  
  hPt_JP2->Write();
  hEta_JP2->Write();
  hPhi_JP2->Write();
  hM_JP2->Write();

  hPt_JP1->Write();
  hEta_JP1->Write();
  hPhi_JP1->Write();
  hM_JP1->Write();

  hPt_JP0->Write();
  hEta_JP0->Write();
  hPhi_JP0->Write();
  hM_JP0->Write();
  
  hEtaTot->Write();
	hPhiRy->Write();
	hPhiSy->Write();
	hPhiSRy->Write();
	hPhiRb->Write();
	hPhiSb->Write();
	hPhiSRb->Write();
	hTheta->Write();
	
	hPhi->Write();
	hPtTOT->Write();
	hInvarM->Write();
	
	
	hEtaTot_B->Write();
	hPhiRy_B->Write();
	hPhiSy_B->Write();
	hPhiSRy_B->Write();
	hPhiRb_B->Write();
	hPhiSb_B->Write();
	hPhiSRb_B->Write();
	hTheta_B->Write();
	
	hPhi_B->Write();
	hPtTOT_B->Write();
	hInvarM_B->Write();
	
	hEtaTot_Y->Write();
	hPhiRy_Y->Write();
	hPhiSy_Y->Write();
	hPhiSRy_Y->Write();
	hPhiRb_Y->Write();
	hPhiSb_Y->Write();
	hPhiSRb_Y->Write();
	hTheta_Y->Write();
	
	hPhi_Y->Write();
	hPtTOT_Y->Write();
	hInvarM_Y->Write();
	hMPt->Write();
  
  
	
	
	TCanvas* cthetapt = new TCanvas();
	hThetaPt->Draw("COLZ");
	
	
	TCanvas* cprof = new TCanvas();

	TProfile* prof = hThetaPt->ProfileX("avgPt", 1, 20);
	
	prof->Draw();
	*/
  
  hInvarM->Write();

  cout << "withJP12" << withJP12 << endl;
  cout << "otherThanJP12" << otherThanJP12 << endl;
}
























