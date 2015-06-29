/*
 *  plotAsyms2.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/20/14.
 *  UCLA
 *
 */




void plotAsyms2(){

	
	
	TF1* fitFunc = new TF1("fitFunc","[0]*cos(x)+[1]");
	
	double randAp[5];
	double randEp[5];
	double randp[5];  

	double randAe[4];
	double randEe[4];
	double rande[4];
	
	double randAm[5];
	double randEm[5];
	double randm[5];

	
	double Ap[] = {-.003491,-.031570,-.038070,-.047040,-.047310};
	double Ep[] = {.013732,.012990,.013090,.018540,.018930};
	double p[]  = {3.61,4.49,5.68,7.17,10.32};
	
	double Ae[] = {-.053180,-.034850,0.002469,-.045090};
	double Ee[] = {.014070,.012530,.012603,.014110};
	double e[]  = {-0.75,-0.26,0.26,0.75};

	double Am[] = {-.03557,-.012780,-.033850,-.111,-.05469};
	double Em[] = {.01533,.01096,.01339,.023,.03744};
	double m[]  = {.36,.50,.69,.88,1.19};
	
	
	double sinAm[] = {-.0228,-.0148,-.007613,-.02693,-.02456};
	double sinEm[] = {.0152,.0097,.013258,.02322,.03670};
	

	
	
	double anselmP[]  = {.0092,.0106,.0289,.0071,.0533};
	double anselmPe[] = {.0103,.0086,.0082,.0110,.0106};
	double anselmp[5];
	
	double anselmM[]  = {.0054,.0179,.0229,.0695,.0388};
	double anselmMe[] = {.0101,.0068,.0081,.0134,.0198};
	double anselmm[5];
	
	double anselmE[]  = {-0.0002,0.0075,0.0131,0.0311};
	double anselmEe[] = {0.0060,0.0061,0.0061,0.0060};
	double anselme[4];

	
	
	string randomSpinMassFileList[] = {"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBin0_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBin1_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBin2_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBin3_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBin4_etaBinAll.root"};
	
	
	string randomSpinPtFileList[] = {"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBin0_massBinAll_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBin1_massBinAll_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBin2_massBinAll_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBin3_massBinAll_etaBinAll.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBin4_massBinAll_etaBinAll.root"};
	
	
	string randomSpinEtaFileList[] = {"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBinAll_etaBin0.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBinAll_etaBin1.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBinAll_etaBin2.root",
		"/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/randomSpin_ptBinAll_massBinAll_etaBin3.root"};
	
	
	for (int i = 0; i < 5; i++)
	{
		
		
		cout << "____OPENNING FILE " << randomSpinMassFileList[i] << "_____" << endl;
		
		TFile* randomSpinMassFile = new TFile(randomSpinMassFileList[i].c_str());
		
		TH1D* hAut = randomSpinMassFile->Get("Aut");
		
		hAut->Fit("fitFunc");
		
		
		
		double asym  = hAut->GetFunction("fitFunc")->GetParameter(0);
		double asymE = hAut->GetFunction("fitFunc")->GetParError(0);
		

		randAm[i] = -1*asym;
		randEm[i] = asymE;
		
		
		Am[i] = -1*Am[i];
		
		randm[i]   = m[i] + 0.01;
		anselmm[i] = m[i] - 0.01;
		

	
		randomSpinMassFile->Close();
		//delete hAut;
		
	}

	
	
	for (int i = 0; i < 5; i++)
	{
		
		
		cout << "____OPENNING FILE " << randomSpinPtFileList[i] << "_____" << endl;
		
		TFile* randomSpinPtFile = new TFile(randomSpinPtFileList[i].c_str());
		
		TH1D* hAut2 = randomSpinPtFile->Get("Aut");
		
		hAut2->Fit("fitFunc");
		
		
		
		double asym  = hAut2->GetFunction("fitFunc")->GetParameter(0);
		double asymE = hAut2->GetFunction("fitFunc")->GetParError(0);
		
		
		randAp[i] = -1*asym;
		randEp[i] = asymE;
		
		
		Ap[i] = -1*Ap[i];
		
		randp[i]   = p[i] + 0.1;
		anselmp[i] = p[i] - 0.1;

		
		
		randomSpinPtFile->Close();
		//delete hAut;
	}
	
	for (int i = 0; i < 4; i++)
	{
		
		
		cout << "____OPENNING FILE " << randomSpinEtaFileList[i] << "_____" << endl;
		
		TFile* randomSpinEtaFile = new TFile(randomSpinEtaFileList[i].c_str());
		
		TH1D* hAut3 = randomSpinEtaFile->Get("Aut");
		
		hAut3->Fit("fitFunc");
		
		
		
		double asym  = hAut3->GetFunction("fitFunc")->GetParameter(0);
		double asymE = hAut3->GetFunction("fitFunc")->GetParError(0);
		
		
		randAe[i] = -1*asym;
		randEe[i] = asymE;
		
		
		Ae[i] = -1*Ae[i];
		
		rande[i]   = e[i] + 0.01;
		anselme[i] = e[i] - 0.01;

		
		
		randomSpinPtFile->Close();
		//delete hAut;
	}
	
	
	
	
	TGraphErrors* grandM = new TGraphErrors(5,randm,randAm,0,randEm);
	TGraphErrors* grandP = new TGraphErrors(5,randp,randAp,0,randEp);
	TGraphErrors* grandE = new TGraphErrors(4,rande,randAe,0,randEe);


	TGraphErrors* gM = new TGraphErrors(5,m,Am,0,Em);
	TGraphErrors* gP = new TGraphErrors(5,p,Ap,0,Ep);
	TGraphErrors* gE = new TGraphErrors(4,e,Ae,0,Ee);
	
	TGraphErrors* gAnM = new TGraphErrors(5,anselmm,anselmM,0,anselmMe);
	TGraphErrors* gAnP = new TGraphErrors(5,anselmp,anselmP,0,anselmPe);
	TGraphErrors* gAnE = new TGraphErrors(4,anselme,anselmE,0,anselmEe);

	TMultiGraph* multiM = new TMultiGraph();
	
	gM->SetMarkerColor(2);
	grandM->SetMarkerColor(3);
	
	
	multiM->Add(gM);
	multiM->Add(gAnM);
	multiM->Add(grandM);
	
	TCanvas* cM = new TCanvas();
	multiM->Draw("AP");
	multiM->GetXaxis()->SetTitle("M_{Inv}^{#pi^{+}#pi^{-}}");
	multiM->GetYaxis()->SetTitle("A_{UT}");
	
	gPad->Modified();
	
	
	TMultiGraph* multiP = new TMultiGraph();
	
	gP->SetMarkerColor(2);
	grandP->SetMarkerColor(3);

	
	
	multiP->Add(gP);
	multiP->Add(gAnP);
	multiP->Add(grandP);
	
	TCanvas* cP = new TCanvas();
	multiP->Draw("AP");
	multiP->GetXaxis()->SetTitle("P_{T}^{#pi^{+}#pi^{-}}");
	multiP->GetYaxis()->SetTitle("A_{UT}");
	
	gPad->Modified();
	
	
	
	
	TMultiGraph* multiE = new TMultiGraph();
	
	gE->SetMarkerColor(2);
	grandE->SetMarkerColor(3);
	
	multiE->Add(gE);
	multiE->Add(gAnE);
	multiE->Add(grandE);
	
	TCanvas* cE = new TCanvas();
	
	
	multiE->Draw("AP");
	multiE->GetXaxis()->SetTitle("#eta^{#pi^{+}#pi^{-}}");
	multiE->GetYaxis()->SetTitle("A_{UT}");
	
	gPad->Modified();
	
	

	







}