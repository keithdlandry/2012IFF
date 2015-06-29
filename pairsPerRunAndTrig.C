/*
 *  pairsPerRunAndTrig.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/1/14.
 *  UCLA
 *
 */


void pairsPerRunAndTrig(){
	
	//LOAD LIBRARIES
	cout << "\n";
	gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	gSystem->Load("pionPairTreeMaker");
	cout << " loading of pionPairTreeMaker library done" << endl;
	cout << "\n";
	cout << "\n";
	
	
	//LOAD STYLE
	gROOT->Macro("UHBstyle.C");
	gROOT->SetStyle("UHB");
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");

	
	pionPair* pair1 = new pionPair();	
	TTree* t = (TTree*)infile->Get("pionPairTree");
	t->SetBranchAddress("pionPair", &pair1);
	cout <<t->GetEntries()<<endl;
	

		
	int pairsWithFiredTrig = 0;
	
	//# of pairs in the whole run for each trigger
	int runJP0 = 0;
	int runJP1 = 0;
	int runJP2 = 0;
	int runAJP = 0;
	int runBHT0VPD = 0;
	int runBHT1VPD = 0;
	int runBHT2BBC = 0;
	int runBHT2 = 0;
	
	//# of pairs in each event where a specific trigger fired
	int pairJP0 = 0;
	int pairJP1 = 0;
	int pairJP2 = 0;
	int pairAJP = 0;
	int pairBHT0VPD = 0;
	int pairBHT1VPD = 0;
	int pairBHT2BBC = 0;
	int pairBHT2 = 0;
	
	//# of events in which each trigger fired
	int evntJP0 = 0;
	int evntJP1 = 0;
	int evntJP2 = 0;
	int evntAJP = 0;
	int evntBHT0VPD = 0;
	int evntBHT1VPD = 0;
	int evntBHT2BBC = 0;
	int evntBHT2 = 0;
	
	
	int totEventsForRun = 0;
	
	int totalPairsForRun = 0;
	
	
	//vectors to hold stuff to plot
	vector<double> numbOfPairPerEvent;
	
	vector<double> numbOfPairPerJP0;
  vector<double> numbOfPairPerJP1;
  vector<double> numbOfPairPerJP2;
  vector<double> numbOfPairPerAJP;
	
  vector<double> numbOfPairPerBHT0VPD;
  vector<double> numbOfPairPerBHT1VPD;
  vector<double> numbOfPairPerBHT2BBC;
	vector<double> numbOfPairPerBHT2;
	
	vector<double> errOfPairPerJP0;
  vector<double> errOfPairPerJP1;
  vector<double> errOfPairPerJP2;
  vector<double> errOfPairPerAJP;
	
  vector<double> errOfPairPerBHT0VPD;
  vector<double> errOfPairPerBHT1VPD;
  vector<double> errOfPairPerBHT2BBC;
	vector<double> errOfPairPerBHT2;
	
	/*
	vector<double> eventNumbOfPairPerJP0;
  vector<double> eventNumbOfPairPerJP1;
  vector<double> eventNumbOfPairPerJP2;
  vector<double> eventNumbOfPairPerAJP;
	
  vector<double> eventNumbOfPairPerBHT0VPD;
  vector<double> eventNumbOfPairPerBHT1VPD;
  vector<double> eventNumbOfPairPerBHT2BBC;
	vector<double> eventNumbOfPairPerBHT2;
	*/
	
	TH1I* hEvntPairsJP0 = new TH1I("hEvntPairsJP0","hEvntPairsJP0",100,0,100);
	TH1I* hEvntPairsJP1 = new TH1I("hEvntPairsJP1","hEvntPairsJP1",100,0,100);
	TH1I* hEvntPairsJP2 = new TH1I("hEvntPairsJP2","hEvntPairsJP2",100,0,100);
	TH1I* hEvntPairsAJP = new TH1I("hEvntPairsAJP","hEvntPairsAJP",100,0,100);
	TH1I* hEvntPairsBHT0VPD = new TH1I("hEvntPairsBHT0VPD","hEvntPairsBHT0VPD",100,0,100);
	TH1I* hEvntPairsBHT1VPD = new TH1I("hEvntPairsBHT0VPD","hEvntPairsBHT0VPD",100,0,100);
	TH1I* hEvntPairsBHT2BBC = new TH1I("hEvntPairsBHT2BBC","hEvntPairsBHT2BBC",100,0,100);
	TH1I* hEvntPairsBHT2 = new TH1I("hEvntPairsBHT2","hEvntPairsBHT2",100,0,100);

	TCanvas* cJP0 = new TCanvas();
	TCanvas* cJP1 = new TCanvas();
	TCanvas* cJP2 = new TCanvas();
	TCanvas* cAJP = new TCanvas();
	TCanvas* cBHT0VPD = new TCanvas();
	TCanvas* cBHT1VPD = new TCanvas();
	TCanvas* cBHT2BBC = new TCanvas();
	TCanvas* cBHT2 = new TCanvas();

	
	
	
	vector<double> run;
	
	int runIncr;
	
	t->GetEntry(0);
	
	int initialRun = pair1->runInfo().runId();
	int currentRun = initialRun;
	
	int initialEvent = pair1->eventID();
	int currentEvent = initialRun;
	
	cout << "  Initial Run : " << initialRun << endl;
	cout << "Initial Event : " << initialEvent << endl;
	
	for (int iPair=0; iPair<t->GetEntries(); iPair++)
	{

		if (iPair%10000 == 0) {cout << "processing pair number " << iPair << endl;}
		//if (iPair == 100000) {break;}
		
		
		t->GetEntry(iPair);

		
		//put run values into vectors at end of run
		//and reset everything
		if (pair1->runInfo().runId() != currentRun)
		{
			
			
			if (totEventsForRun != 0)
			{
				numbOfPairPerEvent.push_back((double)totalPairsForRun/totEventsForRun);
			}
			else {numbOfPairPerEvent.push_back(-1);}
			
			if (evntJP0 != 0)
			{
				numbOfPairPerJP0.push_back((double)runJP0/evntJP0);
				errOfPairPerJP0.push_back((double)hEvntPairsJP0->GetRMS(1)/hEvntPairsJP0->GetEntries());
			}
			else 
			{
				numbOfPairPerJP0.push_back(-1);
				errOfPairPerJP0.push_back(0);
			}
      
			if (evntJP1 != 0)
			{
				numbOfPairPerJP1.push_back((double)runJP1/evntJP1);
				errOfPairPerJP1.push_back((double)hEvntPairsJP1->GetRMS(1)/hEvntPairsJP1->GetEntries());
			}
			else 
			{
				numbOfPairPerJP1.push_back(-1);
				errOfPairPerJP1.push_back(0);
			}
			
			if (evntJP2 != 0)
			{
				numbOfPairPerJP2.push_back((double)runJP2/evntJP2);
				errOfPairPerJP2.push_back((double)hEvntPairsJP2->GetRMS(1)/hEvntPairsJP2->GetEntries());
			}
			else 
			{
				numbOfPairPerJP2.push_back(-1);
				errOfPairPerJP2.push_back(0);
			}
			
			if (evntAJP != 0)
			{
				numbOfPairPerAJP.push_back((double)runAJP/evntAJP);
				errOfPairPerAJP.push_back((double)hEvntPairsAJP->GetRMS(1)/hEvntPairsAJP->GetEntries());
			}
			else 
			{
				numbOfPairPerAJP.push_back(-1);
				errOfPairPerAJP.push_back(0);
			}
			
			if (evntBHT0VPD != 0)
			{
				numbOfPairPerBHT0VPD.push_back((double)runBHT0VPD/evntBHT0VPD);
				errOfPairPerBHT0VPD.push_back((double)hEvntPairsBHT0VPD->GetRMS(1)/hEvntPairsBHT0VPD->GetEntries());
			}
			else
			{
				numbOfPairPerBHT0VPD.push_back(-1);
				errOfPairPerBHT0VPD.push_back(0);
			}
			
			if (evntBHT1VPD != 0)
			{
				numbOfPairPerBHT1VPD.push_back((double)runBHT1VPD/evntBHT1VPD);
				errOfPairPerBHT1VPD.push_back((double)hEvntPairsBHT1VPD->GetRMS(1)/hEvntPairsBHT1VPD->GetEntries());
			}
			else
			{
				numbOfPairPerBHT1VPD.push_back(-1);
				errOfPairPerBHT1VPD.push_back(0);
			}
			
			if (evntBHT2BBC != 0)
			{
				numbOfPairPerBHT2BBC.push_back((double)runBHT2BBC/evntBHT2BBC);
				errOfPairPerBHT2BBC.push_back((double)hEvntPairsBHT2BBC->GetRMS(1)/hEvntPairsBHT2BBC->GetEntries());
			}
			else
			{
				numbOfPairPerBHT2BBC.push_back(-1);
				errOfPairPerBHT2BBC.push_back(0);
			}
			
			if (evntBHT2 != 0)
			{
				numbOfPairPerBHT2.push_back((double)runBHT2/evntBHT2);
				errOfPairPerBHT2.push_back((double)hEvntPairsBHT2->GetRMS(1)/hEvntPairsBHT2->GetEntries());
			}
			else
			{
				numbOfPairPerBHT2.push_back(-1);
				errOfPairPerBHT2.push_back(0);
			}


			
			run.push_back(runIncr);
			runIncr++;

			
			runJP0 = 0;
			runJP1 = 0;
			runJP2 = 0;
			runAJP = 0;
			runBHT0VPD = 0;
			runBHT1VPD = 0;
			runBHT2BBC = 0;
			runBHT2 = 0;

			
			pairJP0 = 0;
			pairJP1 = 0;
			pairJP2 = 0;
			pairAJP = 0;
			pairBHT0VPD = 0;
			pairBHT1VPD = 0;
			pairBHT2BBC = 0;
			pairBHT2 = 0;
			
			
			evntJP0 = 0;
		  evntJP1 = 0;
			evntJP2 = 0;
			evntAJP = 0;
			evntBHT0VPD = 0;
			evntBHT1VPD = 0;
			evntBHT2BBC = 0;
			evntBHT2 = 0;
			
			
			
			
			totEventsForRun = 0;
			
			//*
			cJP0->cd();
			hEvntPairsJP0->DrawCopy();
			cJP1->cd();
			hEvntPairsJP1->DrawCopy();
			cJP2->cd();
			hEvntPairsJP2->DrawCopy();
			cAJP->cd();
      hEvntPairsAJP->DrawCopy();
			cBHT0VPD->cd();
			hEvntPairsBHT0VPD->DrawCopy();
			cBHT1VPD->cd();
			hEvntPairsBHT1VPD->DrawCopy();
			cBHT2BBC->cd();
			hEvntPairsBHT2BBC->DrawCopy();
			cBHT2->cd();
			hEvntPairsBHT2->DrawCopy();
			//*/
			
			hEvntPairsJP0->Reset();
			hEvntPairsJP1->Reset();
			hEvntPairsJP2->Reset();
			hEvntPairsAJP->Reset();
			hEvntPairsBHT0VPD->Reset();
			hEvntPairsBHT1VPD->Reset();
			hEvntPairsBHT2BBC->Reset();
			hEvntPairsBHT2->Reset();
			
			
			currentRun = pair1->runInfo().runId();
		}
		
		if (pair1->eventID() == currentEvent)
		{
			StTriggerId trigId = pair1->triggerIds();
			
			totalPairsForRun++;
			
			if (trigId.isTrigger(370601))
			{
				runJP0++;
				pairJP0++;
			}
			if (trigId.isTrigger(370611))
			{
				runJP1++;
				pairJP1++;
			}
			if (trigId.isTrigger(370621))
			{
				runJP2++;
				pairJP2++;
			}
			if (trigId.isTrigger(370641))
			{
				runAJP++;
				pairAJP++;
			}
			if (trigId.isTrigger(370501))
			{
				runBHT0VPD++;
				pairBHT0VPD++;
			}
			if (trigId.isTrigger(370511))
			{
				runBHT1VPD++;
				pairBHT1VPD++;
			}
			if (trigId.isTrigger(370522))
			{
				runBHT2BBC++;
				pairBHT2BBC++;
			}
			if (trigId.isTrigger(370531))
			{
				runBHT2++;
				pairBHT2++;
			}
		}

		
		//If we move to a new event 
		if (pair1->eventID() != currentEvent)
		{
			StTriggerId trigId = pair1->triggerIds();
			
			totEventsForRun++;
			totalPairsForRun++;
			
			//only fill if the corresponding trigger was fired for the event 
			//cut out pairs from events which didn't fire a specific trigger
			if (pairJP0 > 0) {hEvntPairsJP0->Fill(pairJP0);}
			if (pairJP1 > 0) {hEvntPairsJP1->Fill(pairJP1);}
			if (pairJP2 > 0) {hEvntPairsJP2->Fill(pairJP2);}
			if (pairAJP > 0) {hEvntPairsAJP->Fill(pairAJP);}
			if (pairBHT0VPD > 0) {hEvntPairsBHT0VPD->Fill(pairBHT0VPD);}
			if (pairBHT1VPD > 0) {hEvntPairsBHT1VPD->Fill(pairBHT1VPD);}
			if (pairBHT2BBC > 0) {hEvntPairsBHT2BBC->Fill(pairBHT2BBC);}
			if (pairBHT2 > 0) {hEvntPairsBHT2->Fill(pairBHT2);}

			
			
			
			
			pairJP0 = 0;
			pairJP1 = 0;
			pairJP2 = 0;
			pairAJP = 0;
			pairBHT0VPD = 0;
			pairBHT1VPD = 0;
			pairBHT2BBC = 0;
			pairBHT2 = 0;
			
			
			
			
			if (trigId.isTrigger(370601))
			{
				runJP0++;
				pairJP0++;
				evntJP0++;
			}
			if (trigId.isTrigger(370611))
			{
				runJP1++;
				pairJP1++;
				evntJP1++;
      }
			if (trigId.isTrigger(370621))
			{
				runJP2++;
				pairJP2++;
				evntJP2++;
			}
			if (trigId.isTrigger(370641))
			{
				runAJP++;
				pairAJP++;
				evntAJP++;
			}
			if (trigId.isTrigger(370501))
			{
				runBHT0VPD++;
				pairBHT0VPD++;
				evntBHT0VPD++;
			}
			if (trigId.isTrigger(370511))
			{
				runBHT1VPD++;
				pairBHT1VPD++;
				evntBHT1VPD++;
			}
			if (trigId.isTrigger(370522))
			{
				runBHT2BBC++;
				pairBHT2BBC++;
				evntBHT2BBC++;
			}
			if (trigId.isTrigger(370531))
			{
				runBHT2++;
				pairBHT2++;
				evntBHT2++;
      }
			
			currentEvent = pair1->eventID();
			
		}//end new event
		
	}//finished looping through pion pair tree
	
	
	TCanvas* cJP0 = new TCanvas();
	TGraphErrors* gJP0 = new TGraphErrors(run.size(),&run[0],&numbOfPairPerJP0[0],0,&errOfPairPerJP0[0]);
	gJP0->Draw("AP");	
	gJP0->SetTitle("JP0");
	gJP0->GetXaxis()->SetTitle("run");
	gJP0->GetYaxis()->SetTitle("pairs/trigger");
	cJP0->SaveAs("pairsJP0.pdf");
	cJP0->SaveAs("pairsJP0.png");

	TCanvas* cJP1 = new TCanvas();
	TGraphErrors* gJP1 = new TGraphErrors(run.size(),&run[0],&numbOfPairPerJP1[0],0,&errOfPairPerJP1[0]);
	gJP1->Draw("AP");
	gJP1->SetTitle("JP1");
	gJP1->GetXaxis()->SetTitle("run");
	gJP1->GetYaxis()->SetTitle("pairs/trigger");
	cJP1->SaveAs("pairsJP1.pdf");
	cJP1->SaveAs("pairsJP1.png");

	
	TCanvas* cJP2 = new TCanvas();
	TGraphErrors* gJP2 = new TGraphErrors(run.size(),&run[0],&numbOfPairPerJP2[0],0,&errOfPairPerJP2[0]);
	gJP2->Draw("AP");
	gJP2->SetTitle("JP2");
	gJP2->GetXaxis()->SetTitle("run");
	gJP2->GetYaxis()->SetTitle("pairs/trigger");
	cJP2->SaveAs("pairsJP2.pdf");
	cJP2->SaveAs("pairsJP2.png");

	TCanvas* cAJP = new TCanvas();
	TGraphErrors* gAJP = new TGraphErrors(run.size(),&run[0],&numbOfPairPerAJP[0],0,&errOfPairPerAJP[0]);
	gAJP->Draw("AP");
	gAJP->SetTitle("AJP");
	gAJP->GetXaxis()->SetTitle("run");
	gAJP->GetYaxis()->SetTitle("pairs/trigger");
	cAJP->SaveAs("pairsAJP.pdf");
	cAJP->SaveAs("pairsAJP.png");

	TCanvas* cBHT0VPD = new TCanvas();
	TGraphErrors* gBHT0VPD = new TGraphErrors(run.size(),&run[0],&numbOfPairPerBHT0VPD[0],0,&errOfPairPerBHT0VPD[0]);
	gBHT0VPD->Draw("AP");
	gBHT0VPD->SetTitle("BHT0VPD");
	gBHT0VPD->GetXaxis()->SetTitle("run");
	gBHT0VPD->GetYaxis()->SetTitle("pairs/trigger");
	cBHT0VPD->SaveAs("pairsBHT0VPD.pdf");
	cBHT0VPD->SaveAs("pairsBHT0VPD.png");

	TCanvas* cBHT1VPD = new TCanvas();
	TGraphErrors* gBHT1VPD = new TGraphErrors(run.size(),&run[0],&numbOfPairPerBHT1VPD[0],0,&errOfPairPerBHT1VPD[0]);
	gBHT1VPD->Draw("AP");
	gBHT1VPD->SetTitle("BHT1VPD");
	gBHT1VPD->GetXaxis()->SetTitle("run");
	gBHT1VPD->GetYaxis()->SetTitle("pairs/trigger");
	cBHT1VPD->SaveAs("pairsBHT1VPD.pdf");
	cBHT1VPD->SaveAs("pairsBHT1VPD.png");

	TCanvas* cBHT2BBC = new TCanvas();
	TGraphErrors* gBHT2BBC = new TGraphErrors(run.size(),&run[0],&numbOfPairPerBHT2BBC[0],0,&errOfPairPerBHT2BBC[0]);
	gBHT2BBC->Draw("AP");	
	gBHT2BBC->SetTitle("BHT2BBC");
	gBHT2BBC->GetXaxis()->SetTitle("run");
	gBHT2BBC->GetYaxis()->SetTitle("pairs/trigger");
	cBHT2BBC->SaveAs("pairsBHT2BBC.pdf");
	cBHT2BBC->SaveAs("pairsBHT2BBC.png");

	TCanvas* cBHT2 = new TCanvas();
	TGraphErrors* gBHT2 = new TGraphErrors(run.size(),&run[0],&numbOfPairPerBHT2[0],0,&errOfPairPerBHT2[0]);
	gBHT2->Draw("AP");	
	gBHT2->SetTitle("BHT2");
	gBHT2->GetXaxis()->SetTitle("run");
	gBHT2->GetYaxis()->SetTitle("pairs/trigger");
	cBHT2->SaveAs("pairsBHT2.pdf");
	cBHT2->SaveAs("pairsBHT2.png");



}