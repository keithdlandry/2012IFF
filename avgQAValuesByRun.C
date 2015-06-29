/*
 *  avgQAValuesByRun.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/7/14.
 *  UCLA
 *
 */



void avgQAValuesByRun(){

	//LOAD LIBS
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;

	
	//LOAD STYLE
	gROOT->Macro("UHBstyle.C");
	gROOT->SetStyle("UHB");
	
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");

	string outFileName = "./resultsNew_4_22/avgQAbyRun.root"; 

	//SET UP TREE TO RECEIVE INPUT
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	
	pairTree->GetEntry(0);
	
	int initialRun = pair1->runInfo().runId();
	int currentRun = initialRun;

	
	//QA histograms
	TH1D* hInvarM    = new TH1D("invarM","invarM",80,0,2);
	TH1D* hEtaTot	   = new TH1D("etaTot","etaTot",60,-1.5,1.5);
	TH1D* hPhiRy     = new TH1D("hPhiRy","hPhiRy",60,-4,4);
	TH1D* hPhiRb     = new TH1D("hPhiRb","hPhiRb",60,-4,4);
	TH1D* hPhiSy     = new TH1D("hPhiSy","hPhiSy",60,-4,4);
	TH1D* hPhiSb     = new TH1D("hPhiSb","hPhiSb",60,-4,4);
	TH1D* hPhiSRy    = new TH1D("hPhiSRy","hPhiSRy",60,-4,4);
	TH1D* hPhiSRb    = new TH1D("hPhiSRb","hPhiSRb",60,-4,4);
	TH1D* hTheta     = new TH1D("hTheta","hTheta",30,-0.85,4);
	TH1D* hCosTheta  = new TH1D("hCosTheta","hCosTheta",80,-1,1);
	TH1D* hZ         = new TH1D("hZ","hZ",80,0,1);
	TH1D* hPtot      = new TH1D("hPtot","hPtot",80,0,20);
	TH1D* hPt        = new TH1D("hPt","hPt",80,0,15);
	TH1D* hPhi       = new TH1D("hPhi","hPhi",60,-3.14159,3.14159);
	
	vector<double> massVec;
	vector<double> ptVec;
	vector<double> etaVec;
	vector<double> phiVec;

	vector<double> phiSyVec;
	vector<double> phiSbVec;
	vector<double> phiRyVec;
	vector<double> phiRbVec;
	vector<double> phiSRyVec;
	vector<double> phiSRbVec;

	vector<double> massVecE;
	vector<double> ptVecE;
	vector<double> etaVecE;
	vector<double> phiVecE;
	
	vector<double> phiSyVecE;
	vector<double> phiSbVecE;
	vector<double> phiRyVecE;
	vector<double> phiRbVecE;
	vector<double> phiSRyVecE;
	vector<double> phiSRbVecE;
	
	
	TLorentzVector sum;

	vector<double> run;
	
	int runIncr = 0;
	
	for (int iPair = 0; iPair < pairTree->GetEntries(); iPair++)
	{
		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		
		//if (iPair == 100000){break;}
		
		
		pairTree->GetEntry(iPair);
	

		if (pair1->withinRadius(0.05, 0.3))
		{
			
			bool triggerFired = false;
			
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
				
				sum = pair1->piPlusLV() + pair1->piMinusLV();

				
				if (pair1->runInfo().runId() != currentRun)
				{
					massVec.push_back(hInvarM->GetMean(1));
					massVecE.push_back(hInvarM->GetRMS(1)/sqrt(hInvarM->GetEntries()));
					ptVec.push_back(hPt->GetMean(1));
					ptVecE.push_back(hPt->GetRMS(1)/sqrt(hPt->GetEntries()));
					etaVec.push_back(hEtaTot->GetMean(1));
					etaVecE.push_back(hEtaTot->GetRMS(1)/sqrt(hEtaTot->GetEntries()));
					phiVec.push_back(hPhi->GetMean(1));
					phiVecE.push_back(hPhi->GetRMS(1)/sqrt(hPhi->GetEntries()));
				
					phiSyVec.push_back(hPhiSy->GetMean(1));
					phiSyVecE.push_back(hPhiSy->GetRMS(1)/sqrt(hPhiSy->GetEntries()));
					phiSbVec.push_back(hPhiSb->GetMean(1));
					phiSbVecE.push_back(hPhiSb->GetRMS(1)/sqrt(hPhiSb->GetEntries()));
					phiRyVec.push_back(hPhiRy->GetMean(1));
					phiRyVecE.push_back(hPhiRy->GetRMS(1)/sqrt(hPhiRy->GetEntries()));
					phiRbVec.push_back(hPhiRb->GetMean(1));
					phiRbVecE.push_back(hPhiRb->GetRMS(1)/sqrt(hPhiRb->GetEntries()));
					phiSRyVec.push_back(hPhiSRy->GetMean(1));
					phiSRyVecE.push_back(hPhiSRy->GetRMS(1)/sqrt(hPhiSRy->GetEntries()));
					phiSRbVec.push_back(hPhiSRb->GetMean(1));
					phiSRbVecE.push_back(hPhiSRb->GetRMS(1)/sqrt(hPhiSRb->GetEntries()));
					
					
					hInvarM->Reset();
					hPt->Reset();
					hEtaTot->Reset();
					hPhi->Reset();
					
					hPhiSy->Reset();
					hPhiSb->Reset();
					hPhiRy->Reset();
					hPhiRb->Reset();
					hPhiSRy->Reset();
					hPhiSRb->Reset();
					
					run.push_back(runIncr);
					runIncr++;
					
					currentRun = pair1->runInfo().runId();

				
				}
				
				hInvarM->Fill(sum.M());
				hPt->Fill(sum.Pt());
				hEtaTot->Fill(sum.Eta());
				hPhi->Fill(sum.Phi());
				hPhiSy->Fill(pair1->phiS('y'));
				hPhiSb->Fill(pair1->phiS('b'));
				hPhiRy->Fill(pair1->phiR('y'));
				hPhiRb->Fill(pair1->phiR('b'));
				hPhiSRy->Fill(pair1->phiSR('y'));
				hPhiSRb->Fill(pair1->phiSR('b'));
				
				
				
				
				
			}
		}
	}		
	cout << massVec.size() << " " << massVecE.size() << endl;

	cout << "Drawing" << endl;

	
	
	//*
	TCanvas* cMass = new TCanvas();
	TGraphErrors* gMass = new TGraphErrors(run.size(),&run[0],&massVec[0],0,&massVecE[0]);
	gMass->Draw("AP");
	gMass->SetLineColor(kAzure-5);
	gMass->SetLineWidth(2);
	gMass->SetTitle("Invariant Mass VS Run");
	gMass->GetXaxis()->SetTitle("run");
	gMass->GetYaxis()->SetTitle("Invariant Mass");
	cMass->SaveAs("massVSrun_4_2.pdf");
	cMass->SaveAs("massVSrun_4_2.png");
	//*/
	gMass->SetName("gMass");
	
	TCanvas* cPt = new TCanvas();
	TGraphErrors* gPt = new TGraphErrors(run.size(),&run[0],&ptVec[0],0,&ptVecE[0]);
	gPt->Draw("AP");
	gPt->SetLineColor(kAzure-5);
	gPt->SetLineWidth(2);
	gPt->SetTitle("Pt VS Run");
	gPt->GetXaxis()->SetTitle("run");
	gPt->GetYaxis()->SetTitle("Pt");
	cPt->SaveAs("ptVSrun_4_2.pdf");
	cPt->SaveAs("ptVSrun_4_2.png");
	gPt->SetName("gPt");

	cout << "2"<< endl;
	
	TCanvas* cEta = new TCanvas();
	TGraphErrors* gEta = new TGraphErrors(run.size(),&run[0],&etaVec[0],0,&etaVecE[0]);
	gEta->Draw("AP");
	gEta->SetLineColor(kAzure-5);
	gEta->SetLineWidth(2);
	gEta->SetTitle("Eta VS Run");
	gEta->GetXaxis()->SetTitle("run");
	gEta->GetYaxis()->SetTitle("Eta");
	cEta->SaveAs("etaVSrun_4_2.pdf");
	cEta->SaveAs("etaVSrun_4_2.png");
	gEta->SetName("gEta");


	cout << "3" << endl;
	
	TCanvas* cPhi = new TCanvas();
	TGraphErrors* gPhi = new TGraphErrors(run.size(),&run[0],&phiVec[0],0,&phiVecE[0]);
	gPhi->Draw("AP");
	gPhi->SetLineColor(kAzure-5);
	gPhi->SetLineWidth(2);
	gPhi->SetTitle("Phi VS Run");
	gPhi->GetXaxis()->SetTitle("run");
	gPhi->GetYaxis()->SetTitle("Phi");
	cPhi->SaveAs("phiVSrun_4_2.pdf");
	cPhi->SaveAs("phiVSrun_4_2.png");
	gPhi->SetName("gPhi");

	//*/
	
	
	TCanvas* cPhiSy = new TCanvas();
	TGraphErrors* gPhiSy = new TGraphErrors(run.size(),&run[0],&phiSyVec[0],0,&phiSyVecE[0]);
	gPhiSy->Draw("AP");
	gPhiSy->SetLineColor(kAzure-5);
	gPhiSy->SetLineWidth(2);
	gPhiSy->SetTitle("PhiS_y VS Run");
	gPhiSy->GetXaxis()->SetTitle("run");
	gPhiSy->GetYaxis()->SetTitle("PhiS_y");
	cPhiSy->SaveAs("phiSyVSrun_4_2.pdf");
	cPhiSy->SaveAs("phiSyVSrun_4_2.png");
	gPhiSy->SetName("gPhiSy");


	TCanvas* cPhiSb = new TCanvas();
	TGraphErrors* gPhiSb = new TGraphErrors(run.size(),&run[0],&phiSbVec[0],0,&phiSbVecE[0]);
	gPhiSb->Draw("AP");
	gPhiSb->SetLineColor(kAzure-5);
	gPhiSb->SetLineWidth(2);
	gPhiSb->SetTitle("PhiS_b VS Run");
	gPhiSb->GetXaxis()->SetTitle("run");
	gPhiSb->GetYaxis()->SetTitle("PhiS_b");
	cPhiSb->SaveAs("phiSbVSrun_4_2.pdf");
	cPhiSb->SaveAs("phiSbVSrun_4_2.png");
	gPhiSb->SetName("gPhiSb");

	TCanvas* cPhiRy = new TCanvas();
	TGraphErrors* gPhiRy = new TGraphErrors(run.size(),&run[0],&phiRyVec[0],0,&phiRyVecE[0]);
	gPhiRy->Draw("AP");
	gPhiRy->SetLineColor(kAzure-5);
	gPhiRy->SetLineWidth(2);
	gPhiRy->SetTitle("PhiR_y VS Run");
	gPhiRy->GetXaxis()->SetTitle("run");
	gPhiRy->GetYaxis()->SetTitle("PhiR_y");
	cPhiRy->SaveAs("phiRyVSrun_4_2.pdf");
	cPhiRy->SaveAs("phiRyVSrun_4_2.png");
	gPhiRy->SetName("gPhiRy");

	TCanvas* cPhiRb = new TCanvas();
	TGraphErrors* gPhiRb = new TGraphErrors(run.size(),&run[0],&phiRbVec[0],0,&phiRbVecE[0]);
	gPhiRb->Draw("AP");
	gPhiRb->SetLineColor(kAzure-5);
	gPhiRb->SetLineWidth(2);
	gPhiRb->SetTitle("PhiR_b VS Run");
	gPhiRb->GetXaxis()->SetTitle("run");
	gPhiRb->GetYaxis()->SetTitle("PhiR_b");
	cPhiRb->SaveAs("phiRbVSrun_4_2.pdf");
	cPhiRb->SaveAs("phiRbVSrun_4_2.png");
	gPhiRb->SetName("gPhiRb");

	
	TCanvas* cPhiSRy = new TCanvas();
	TGraphErrors* gPhiSRy = new TGraphErrors(run.size(),&run[0],&phiSRyVec[0],0,&phiSRyVecE[0]);
	gPhiSRy->Draw("AP");
	gPhiSRy->SetLineColor(kAzure-5);
	gPhiSRy->SetLineWidth(2);
	gPhiSRy->SetTitle("PhiSR_y VS Run");
	gPhiSRy->GetXaxis()->SetTitle("run");
	gPhiSRy->GetYaxis()->SetTitle("PhiSR_y");
	cPhiSRy->SaveAs("phiSRyVSrun_4_2.pdf");
	cPhiSRy->SaveAs("phiSRyVSrun_4_2.png");
	gPhiSRy->SetName("gPhiSRy");

	TCanvas* cPhiSRb = new TCanvas();
	TGraphErrors* gPhiSRb = new TGraphErrors(run.size(),&run[0],&phiSRbVec[0],0,&phiSRbVecE[0]);
	gPhiSRb->Draw("AP");
	gPhiSRb->SetLineColor(kAzure-5);
	gPhiSRb->SetLineWidth(2);
	gPhiSRb->SetTitle("PhiSR_b VS Run");
	gPhiSRb->GetXaxis()->SetTitle("run");
	gPhiSRb->GetYaxis()->SetTitle("PhiSR_b");
	cPhiSRb->SaveAs("phiSRbVSrun_4_2.pdf");
	cPhiSRb->SaveAs("phiSRbVSrun_4_2.png");
	gPhiSRb->SetName("gPhiSRb");

	
	

	TFile* outFile = new TFile(outFileName.c_str(),"recreate");

	
	gMass->Write();
	gPt->Write();
	gEta->Write();
	gPhi->Write();
	gPhiSy->Write();
	gPhiSb->Write();
	gPhiRy->Write();
	gPhiRb->Write();
	gPhiSRy->Write();
	gPhiSRb->Write();


		
	cout << "---END---" << endl;
		
		
		
}