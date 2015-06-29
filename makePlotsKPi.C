/*
 *  makePlotsKPi.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/12/15.
 *  UCLA
 *
 */



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
	
	can->Divide(xSide, ySide,0,0);
	
	for (int i = 0; i < nBins; i++)
	{
		can->cd(i+1);
    can->SetGridx(0);
    can->SetGridy(0);
    /*
     gPad->SetBottomMargin(0);
     gPad->SetRightMargin(0);
     gPad->SetLeftMargin(0)
     gPad->SetFrameFillColor(0);
     gPad->SetFrameBorderMode(0); //*/
    gPad->SetGridx(0);
    gPad->SetGridy(0);
    if (i >= 0 && i <6)
    {
      gPad->SetBottomMargin(0);
    }
    
    if (i != 0 || i != 1 || i != 2)
    {
      gPad->SetTopMargin(0);
    }
    if (i != 0 || i != 3 || i != 6)
    {
      //gPad->SetLeftMargin(0);
    }
    if (i != 2 || i != 5 || i != 8)
    {
      gPad->SetRightMargin(0);
    }
    
    
    
    hist[i]->SetBinContent(8, -20);
    hist[i]->SetBinContent(25, -20);
    
		hist[i]->Draw();
    hist[i]->GetXaxis()->SetRange(9, 24);
    hist[i]->GetXaxis()->SetTitle("#phi_{R} - #phi_{S}");
    hist[i]->GetYaxis()->SetRangeUser(-0.11, 0.11);
    hist[i]->GetXaxis()->SetRangeUser(-1.6, 1.6);
    hist[i]->GetXaxis()->SetTitleSize(0.8);
    hist[i]->GetXaxis()->SetTitleOffset(.8);
    hist[i]->GetXaxis()->SetLabelSize(0.07);
    hist[i]->GetYaxis()->SetLabelSize(0.08);
    hist[i]->SetLineColor(kRed-3);
    hist[i]->SetMarkerColor(kRed-3);
    hist[i]->SetLineWidth(2);
    
    //*
    TF1* zero = new TF1("zero","0",-2,2);
    zero->SetLineColor(kGray + 1);
    zero->SetLineWidth(1);
    zero->SetLineStyle(2);
    zero->Draw("same");
    //*/
    
    
    
    
    
    
	}
	
}



void makePlotsKPi(){
	
	
	bool drawIndividual = false;
	bool halfRange = false;
	
	bool hiEta = true;
	bool loEta = false;
	bool vsEta;
	
	if (hiEta || loEta)
	{
		vsEta = false;
		//halfRange = true;
	}
	else{vsEta = true;}
	
	if (hiEta && loEta)
	{
		cout << "can't have high eta and low eta at same time" << endl;
	}
  
  const int nPtBins    = 4;
  const int nEtaBins   = 6;
  const int nMassBins  = 3;
  
  //const int nCosThetaBins = 7;
  const int nCosThetaBins = 5;
  
  const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014
  
  double    ptBinStart[nPtBins] = {3.0, 3.7, 4.15, 4.63};
  double    ptBinEnd[nPtBins]   = {3.7, 4.15, 4.63, 6};  //Anselm used 1000.0 as last point
  
  double    massBinStart[nMassBins] = {0.62, 0.72, 0.86};
  double    massBinEnd[nMassBins]   = {0.72, 0.86, 1.1};
  
  double    etaBinStart[nEtaBins] = {-2, -0.6, -0.3, 0.0, 0.4, 0.75};
  double    etaBinEnd[nEtaBins]   = {-0.6, -0.3, 0.0, 0.4, 0.75, 2};
  
  double    cosThetaBinStart[nCosThetaBins] = {0,1.257,1.6,1.8,2};
  double    cosThetaBinEnd[nCosThetaBins]   = {1.257,1.6,1.8,2,3.14159};
  
  const int nS_Ph_angleBins = 6;
  double s_Ph_angleBinStart[nS_Ph_angleBins] = {0, .5, 1, 1.5, 2, 2.5};
  double s_Ph_angleBinEnd[nS_Ph_angleBins] = {.5, 1, 1.5, 2, 2.5, 3.15};
  
	double lowLimitPt    = ptBinStart[0];
	double hiLimitPt     = ptBinEnd[nPtBins-1];
	double lowLimitEta   = etaBinStart[0];
	double hiLimitEta    = etaBinEnd[nEtaBins-1];
	double lowLimitMass  = massBinStart[0];
	double hiLimitMass   = massBinEnd[nMassBins-1];
	
	if (hiEta){lowLimitEta = 0;}
	if (loEta){hiLimitEta = 0;}
	
	
	double PI = 3.14159265359;
	
  TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/dihadron/rootFiles/cone03AsymsHiEta_5_19_smallPbins.root");
	
	//TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/dihadron/rootFiles/cone03AsymsHiEta_5_7.root");
//	TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/dihadron/rootFiles/cone03AsymsFullEta_5_4.root");
//	TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/dihadron/rootFiles/cone03AsymsHiEta_5_7_posKaon.root");
  
	
	TF1* fitFunc = new TF1("fitFunc","[0]*sin(x)",-PI/2,PI/2);
	
	fitFunc->SetParName(0, "A_{UT}");
	fitFunc->SetLineColor(kAzure+1);
	fitFunc->SetLineWidth(2);
	
	
	TH1D* hAMass[nMassBins];
	TH1D* hAPt[nPtBins];
	TH1D* hAEta[nEtaBins];
	TH1D* hMass[nMassBins];
	TH1D* hPt[nPtBins];
	TH1D* hEta[nEtaBins];
	
	TH1D* hATheta[nCosThetaBins];
	TH1D* hTheta[nCosThetaBins];
	double asymsTheta[nCosThetaBins];
	double asymsThetaE[nCosThetaBins];
	double thetaPoints[nCosThetaBins];
	double thetaPointsErr[nCosThetaBins];
	
	
	double asymsPt[nPtBins]; 
	double asymsMass[nMassBins];
	double asymsEta[nEtaBins];
	
	double asymsPtE[nPtBins];
	double asymsMassE[nMassBins];
	double asymsEtaE[nEtaBins];
	
	
	double ptPoints[nPtBins];
	double ptPointsErr[nPtBins];
	double massPoints[nMassBins];
	double massPointsErr[nMassBins];
	double etaPoints[nEtaBins];
	double etaPointsErr[nEtaBins];
	
	
	double chi2Pt[nPtBins];
	double chi2Mass[nMassBins];
	double chi2Eta[nEtaBins];
	
	//*
	for (int i=0; i<nMassBins; i++)
	{
		
		char nameMass[50];
		sprintf(nameMass, "hAut_Massbin_%d",i);
		hAMass[i] = (TH1D*)infile->Get(nameMass);
		hAMass[i]->Fit("fitFunc", "R");
		
    
		TF1* f1 = hAMass[i]->GetFunction("fitFunc");
		
		asymsMass[i]  = f1->GetParameter(0);
		asymsMassE[i] = f1->GetParError(0);
		chi2Mass[i]   = f1->GetChisquare()/f1->GetNDF();
		
		char nameAvgMass[50];
		sprintf(nameAvgMass, "hMass_Massbin_%d",i);
		
		hMass[i] = (TH1D*)infile->Get(nameAvgMass);
		
		massPoints[i] = hMass[i]->GetMean(1);
		massPointsErr[i] = hMass[i]->GetRMS(1)/(sqrt(hMass[i]->GetEntries()));
		
		
		char titleMass[150];
		sprintf(titleMass, "%.1f < P_{T}^{K#pi} < %.1f | %.1f < M_{inv}^{K#pi} < %.1f | %.1f < #eta^{K#pi} < %.1f", lowLimitPt, hiLimitPt, massBinStart[i], massBinEnd[i], lowLimitEta, hiLimitEta);
		hAMass[i]->SetTitle(titleMass);
		
		
	}
	
	for (int i=0; i<nPtBins; i++)
	{
		char namePt[50];
		sprintf(namePt, "hAut_Ptbin_%d",i);
		hAPt[i] = (TH1D*)infile->Get(namePt);		
		hAPt[i]->Fit("fitFunc", "R");
		
		
		TF1* f1 = hAPt[i]->GetFunction("fitFunc");
		
		asymsPt[i]  = f1->GetParameter(0);
		asymsPtE[i] = f1->GetParError(0);
		chi2Pt[i]   = f1->GetChisquare()/f1->GetNDF();
    
		char titlePt[150];
		sprintf(titlePt, "%.1f < P_{T}^{K#pi} < %.1f  %.1f < M_{inv}^{K#pi} < %.1f  %.1f < #eta^{K#pi} < %.1f", ptBinStart[i], ptBinEnd[i], lowLimitMass, hiLimitMass, lowLimitEta, hiLimitEta);
		hAPt[i]->SetTitle(titlePt);
		
		char nameAvgPt[50];
		sprintf(nameAvgPt, "hPt_Ptbin_%d",i);
		
		hPt[i] = (TH1D*)infile->Get(nameAvgPt);
		
		ptPoints[i] = hPt[i]->GetMean(1);
		ptPointsErr[i] = hPt[i]->GetRMS(1)/(sqrt(hPt[i]->GetEntries()));
		
	}
	//*/
	/*
   for (int i=0; i<nCosThetaBins; i++)
   {
   char nameCosTheta[50];
   sprintf(nameCosTheta, "hAut_CosThetabin_%d",i);
   cout << "fuck this dumb ass shit" << endl;
   hATheta[i] = (TH1D*)infile->Get(nameCosTheta);		
   hATheta[i]->Fit("fitFunc", "R");
   
   
   TF1* f1 = hATheta[i]->GetFunction("fitFunc");
   
   asymsTheta[i]  = f1->GetParameter(0);
   asymsThetaE[i] = f1->GetParError(0);
   //chi2CosTheta[i]   = f1->GetChisquare()/f1->GetNDF();
   
   char titleCosTheta[150];
   sprintf(titleCosTheta, "%.1f < P_{T}^{K#pi} < %.1f  %.1f < M_{inv}^{K#pi} < %.1f  %.1f < #eta^{K#pi} < %.1f", cosThetaBinStart[i], cosThetaBinEnd[i], lowLimitMass, hiLimitMass, lowLimitEta, hiLimitEta);
   hATheta[i]->SetTitle(titleCosTheta);
   
   char nameAvgCosTheta[50];
   sprintf(nameAvgCosTheta, "hCosTheta_CosThetabin_%d",i);
   
   hTheta[i] = (TH1D*)infile->Get(nameAvgCosTheta);
   
   thetaPoints[i] = hTheta[i]->GetMean(1);
   thetaPointsErr[i] = hTheta[i]->GetRMS(1)/(sqrt(hTheta[i]->GetEntries()));
   
   }
   */
	
	if (vsEta)
	{
		for (int i=0; i<nEtaBins; i++)
		{
			char nameEta[50];
			sprintf(nameEta, "hAut_Etabin_%d",i);
			hAEta[i] = (TH1D*)infile->Get(nameEta);
			hAEta[i]->Fit("fitFunc", "R");
			
			TF1* f1 = hAEta[i]->GetFunction("fitFunc");
			
			asymsEta[i]  = f1->GetParameter(0);
			asymsEtaE[i] = f1->GetParError(0);
			chi2Eta[i]   = f1->GetChisquare()/f1->GetNDF();
			
			
			char titleEta[150];
			sprintf(titleEta, "%.1f < P_{T}^{K#pi} < %.1f  %.1f < M_{inv}^{K#pi} < %.1f  %.1f < #eta^{K#pi} < %.1f", lowLimitPt, hiLimitPt, lowLimitMass, hiLimitMass, etaBinStart[i], etaBinEnd[i]);
			hAEta[i]->SetTitle(titleEta);
			
			
			char nameAvgEta[50];
			sprintf(nameAvgEta, "hEta_Etabin_%d",i);
			
			hEta[i] = (TH1D*)infile->Get(nameAvgEta);
			
			etaPoints[i] = hEta[i]->GetMean(1);
			etaPointsErr[i] = hEta[i]->GetRMS(1)/(sqrt(hEta[i]->GetEntries()));
      
		}
		
	}
  
  
  
	
	TCanvas* cPt   = new TCanvas("cPt","cPt",1000,700);
	TCanvas* cMass = new TCanvas("cMass","cMass",1200,800);
	TCanvas* cEta  = new TCanvas("cEta","cEta",800,600);
	
	TCanvas* cTheta = new TCanvas("cTheta","cTheta",1200,600);
	drawNbins(nMassBins, hAMass, cMass);
	drawNbins(nPtBins, hAPt, cPt);
	//drawNbins(nEtaBins, hAEta, cEta);
	
	TCanvas* cAsymCosTheta = new TCanvas();
	TGraphErrors* gAsymCosTheta = new TGraphErrors(nCosThetaBins,thetaPoints,asymsTheta,thetaPointsErr,asymsThetaE);
	
	gAsymCosTheta->Draw("AP");
	gAsymCosTheta->GetXaxis()->SetTitle("#theta_{K#pi}");
	gAsymCosTheta->GetYaxis()->SetTitle("A_{UT}");
	
	char asymCosThetaTitle[150];
	sprintf(asymCosThetaTitle, "Asymmetry VS P_{T}^{K#pi}        (%.1f < M_{inv}^{K#pi} < %.1f , %.1f < #eta^{K#pi} < %.1f)", lowLimitMass, hiLimitMass, lowLimitEta, hiLimitEta);
	gAsymCosTheta->SetTitle(asymCosThetaTitle);
	
	
	
	TCanvas* cAsymPt = new TCanvas();
	TGraphErrors* gAsymPt = new TGraphErrors(nPtBins,ptPoints,asymsPt,ptPointsErr,asymsPtE);
	
	gAsymPt->Draw("AP");
	gAsymPt->GetXaxis()->SetTitle("P_{T}^{K#pi}");
	gAsymPt->GetYaxis()->SetTitle("A_{UT}");
	
  TF1* zero = new TF1("zero","0",-2,2);
  zero->SetLineColor(kGray + 1);
  zero->SetLineWidth(1);
  zero->SetLineStyle(2);
  zero->Draw("same");
  
	char asymPtTitle[150];
	sprintf(asymPtTitle, "Asymmetry VS P_{T}^{K#pi}        (%.1f < M_{inv}^{K#pi} < %.1f , %.1f < #eta^{K#pi} < %.1f)", lowLimitMass, hiLimitMass, lowLimitEta, hiLimitEta);
	gAsymPt->SetTitle(asymPtTitle);
  
  
	
	TCanvas* cAsymMass = new TCanvas();	
	TGraphErrors* gAsymMass = new TGraphErrors(nMassBins,massPoints,asymsMass,massPointsErr,asymsMassE);
	
	gAsymMass->Draw("AP");
	gAsymMass->GetXaxis()->SetTitle("M_{inv}^{K#pi}");
	gAsymMass->GetYaxis()->SetTitle("A_{UT}");

  TF1* zero2 = new TF1("zero2","0",-2,2);
  zero2->SetLineColor(kGray + 1);
  zero2->SetLineWidth(1);
  zero2->SetLineStyle(2);
  zero2->Draw("same");
  
	char asymMassTitle[150];
	sprintf(asymMassTitle, "Asymmetry VS M_{inv}^{K#pi}        (%.1f < P_{T}^{K#pi} < %.1f , %.1f < #eta^{K#pi} < %.1f)", lowLimitPt,hiLimitPt,lowLimitEta,hiLimitEta);
	gAsymMass->SetTitle(asymMassTitle);
	
  
	if (vsEta)
	{
		TCanvas* cAsymEta = new TCanvas();
		TGraphErrors* gAsymEta = new TGraphErrors(nEtaBins,etaPoints,asymsEta,etaPointsErr,asymsEtaE);
		
		gAsymEta->Draw("AP");
		gAsymEta->GetXaxis()->SetTitle("#eta^{K#pi}");
		gAsymEta->GetYaxis()->SetTitle("A_{UT}");
		
		char asymMassTitle[150];
		sprintf(asymMassTitle, "Asymmetry VS #eta^{K#pi}        (%.1f < P_{T}^{K#pi} < %.1f , %.1f < M_{inv}^{K#pi} < %.1f)", lowLimitPt,hiLimitPt,lowLimitMass,hiLimitMass);
		gAsymEta->SetTitle();		
	}
	
	
	
	if (drawIndividual)
	{
		
		
		for (int i=0; i<nPtBins; i++)
		{
			TCanvas* c1 = new TCanvas();
			hAPt[i]->Draw();
			hAPt[i]->GetXaxis()->SetRange(nPhisrBins/4+1, 3*nPhisrBins/4); //set to -pi/2 to pi/2 instead of -pi to pi 
		}
		
		for (int i=0; i<nMassBins; i++)
		{
			TCanvas* c2 = new TCanvas();
			hAMass[i]->Draw();
			hAMass[i]->GetXaxis()->SetRange(nPhisrBins/4+1, 3*nPhisrBins/4);
		}
		
		if (vsEta)
		{
			for (int i=0; i<nEtaBins; i++)
			{
				TCanvas* c3 = new TCanvas();
				hAEta[i]->Draw();
				hAEta[i]->GetXaxis()->SetRange(nPhisrBins/4+1, 3*nPhisrBins/4);
			}
			
		}
	}
	
	
	
	TCanvas* cChi2Mass = new TCanvas("cChi2Mass","cChi2Mass",350,350); 
	TGraph* gChi2Mass  = new TGraph(nMassBins,massPoints,chi2Mass);
	gChi2Mass->Draw("AP");
	gChi2Mass->GetYaxis()->SetTitle("#chi^{2}/DoF");
	gChi2Mass->GetXaxis()->SetTitle("M_{inv}^{K#pi}");
	
	TCanvas* cChi2Pt = new TCanvas("cChi2Pt","cChi2Pt",350,350); 
	TGraph* gChi2Pt  = new TGraph(nPtBins,ptPoints,chi2Pt);
	gChi2Pt->Draw("AP");
	gChi2Pt->GetYaxis()->SetTitle("#chi^{2}/DoF");
	gChi2Pt->GetXaxis()->SetTitle("P_{T}^{K#pi}");
  
	if (vsEta)
	{
		TCanvas* cChi2Eta = new TCanvas("cChi2Eta","cChi2Eta",350,350); 
		TGraph* gChi2Eta  = new TGraph(nEtaBins,etaPoints,chi2Eta);
		gChi2Eta->Draw("AP");
		gChi2Eta->GetYaxis()->SetTitle("#chi^{2}/DoF");
		gChi2Eta->GetXaxis()->SetTitle("#eta^{K#pi}");
		
	}
  
	
	
  
	
	
  
	
	//PRINT OUT VALUES 
	string suffix = "5_7_hiEta_KPi";
	
	
	
	cout << "\n";
	cout << "\n";
  
	cout << "double ptPoints" << suffix << "[" << nPtBins << "] = {"; 
	for (int i = 0; i<nPtBins; i++)
	{
		cout <<ptPoints[i];
		if (i!=nPtBins-1){cout << ", ";}
	}
	cout << "};";
	
	cout << "\n";
	
	cout << "double ptPointsErr" << suffix << "[" << nPtBins << "] = {"; 
	for (int i = 0; i<nPtBins; i++)
	{
		cout <<ptPointsErr[i];
		if (i!=nPtBins-1){cout << ", ";}
    
	}
	cout << "};";
  
	cout << "\n";
	
	cout << "double asymsPt" << suffix << "[" << nPtBins << "] = {"; 
	for (int i = 0; i<nPtBins; i++)
	{
		cout <<asymsPt[i];
		if (i!=nPtBins-1){cout << ", ";}
	}
	cout << "};";
	
	cout << "\n";
	
	cout << "double asymsPtE" << suffix << "[" << nPtBins << "] = {"; 
	for (int i = 0; i<nPtBins; i++)
	{
		cout <<asymsPtE[i];
		if (i!=nPtBins-1){cout << ", ";}
	}
	cout << "};";
	
	cout << "\n";
	
	cout << "double massPoints" << suffix << "[" << nMassBins << "] = {"; 
	for (int i = 0; i<nMassBins; i++)
	{
		cout <<massPoints[i];
		if (i!=nMassBins-1){cout << ", ";}
	}
	cout << "};";
	
	cout << "\n";
	
	cout << "double massPointsErr" << suffix << "[" << nMassBins << "] = {"; 
	for (int i = 0; i<nMassBins; i++)
	{
		cout <<massPointsErr[i];
		if (i!=nMassBins-1){cout << ", ";}
	}
	cout << "};";
	
	cout << "\n";
	
	cout << "double asymsMass" << suffix << "[" << nMassBins << "] = {"; 
	for (int i = 0; i<nMassBins; i++)
	{
		cout <<asymsMass[i];
		if (i!=nMassBins-1){cout << ", ";}
	}
	cout << "};";
	
	cout << "\n";
	
	cout << "double asymsMassE" << suffix << "[" << nMassBins << "] = {"; 
	for (int i = 0; i<nMassBins; i++)
	{
		cout <<asymsMassE[i];
		if (i!=nMassBins-1){cout << ", ";}
	}
	cout << "};";
	
	
	if (vsEta)
	{
		cout << "\n";
		
		cout << "double etaPoints" << suffix << "[" << nEtaBins << "] = {"; 
		for (int i = 0; i<nEtaBins; i++)
		{
			cout <<etaPoints[i];
			if (i!=nEtaBins-1){cout << ", ";}
		}
		cout << "};";
    
		cout << "\n";
		
		cout << "double etaPointsErr" << suffix << "[" << nEtaBins << "] = {"; 
		for (int i = 0; i<nEtaBins; i++)
		{
			cout <<etaPointsErr[i];
			if (i!=nEtaBins-1){cout << ", ";}
		}
		cout << "};";
		
		cout << "\n";
		
		cout << "double asymsEta" << suffix << "[" << nEtaBins << "] = {"; 
		for (int i = 0; i<nEtaBins; i++)
		{
			cout <<asymsEta[i];
			if (i!=nEtaBins-1){cout << ", ";}
		}
		cout << "};";
		
		cout << "\n";
		
		cout << "double asymsEtaE" << suffix << "[" << nEtaBins << "] = {"; 
		for (int i = 0; i<nEtaBins; i++)
		{
			cout <<asymsEtaE[i];
			if (i!=nEtaBins-1){cout << ", ";}
		}
		cout << "};";
	}
	
  cout << "\n";
	
	
	cout << "<----END---->" << endl;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}