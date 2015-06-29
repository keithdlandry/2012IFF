/*
 *  pionContaminationVeta.C
 *  2012IFF
 *
 *  Created by Keith Landry on 8/13/14.
 *  UCLA
 *
 *
 *  Most of this code is taken from Jim Drachenberg's PionCont.C 
 *  I just modified it to fit several different nSigmaPion histograms 
 *  simultaneously and plot the results.
 */




#include <stdio.h>



void pionContaminationVeta(){
  
  
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	gStyle->SetPalette(1);
	
	char hist  [100];
	char hfile [100];
  
	
	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/nsigma20bintest35mil.root");  
  
	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
  double totalYieldWhole = 0;
  double pionYieldWhole = 0;
  double kpYieldWhole = 0;
  double electYieldWhile = 0;
	
	
	double pionFrac  [20];
	double kpFrac    [20];
	double electFrac [20];
	
	double pionCent  [20];
	double kpCent    [20];
	double electCent [20];
	
	double pionMax  [20];
	double kpMax    [20];
	double electMax [20];
	
	double pionSig  [20];
	double kpSig    [20];
	double electSig [20];
	
	
	double etastart[20];
	double etaend[20];
  
	double eta[20];
	
	
	double piYield[20];
	double highestYield = 0;
	
  double totalYeild[20];
	
	
	
  TH1F* hTotal = new TH1F("hTotal","hTotal",300,-10,10);

  
	for (int ihist=0; ihist<20; ihist++)
	{
		/*
     if (ihist != 0 || ihist != 1 || ihist != 2 || ihist != 3 ||)
     {
     cou
     }
     */
		sprintf(hist,"nSigmaPionBin_%i",ihist);
		cout << hist << endl;
		
		TH1F *hNsigma = (TH1F*) file->Get(hist);
	  assert(hNsigma);
    
    hTotal->Add(hNsigma, 1);
    cout << hTotal->GetEntries() << endl;
		
		TF1 *fitFunc = new TF1("fitFunc","gaus(0)+gaus(3)+gaus(6)",-10,10);
    TF1 *piFunc = new TF1("piFunc","gaus(0)",-10,10);
    TF1 *kpFunc = new TF1("kpFunc","gaus(0)",-10,10);
    TF1  *eFunc = new TF1( "eFunc","gaus(0)",-10,10);
    fitFunc->SetParName(0, "A_{#pi}");
    fitFunc->SetParName(1, "#LTn_{#pi}#GT");
    fitFunc->SetParName(2, "#sigma_{#pi}");
    fitFunc->SetParName(3, "A_{K/p}");
    fitFunc->SetParName(4, "#LTn_{K/p}#GT");
    fitFunc->SetParName(5, "#sigma_{K/p}");
    fitFunc->SetParName(6, "A_{e}");
    fitFunc->SetParName(7, "#LTn_{e}#GT");
    fitFunc->SetParName(8, "#sigma_{e}");
		
    fitFunc->SetParameter(0, hNsigma->GetMaximum());
    fitFunc->SetParameter(1, 0.);
    fitFunc->SetParameter(2, 1.);
		
    fitFunc->SetParameter(3, 0.05*hNsigma->GetMaximum());
    fitFunc->SetParameter(4,-3.);
    fitFunc->SetParameter(5, 1.5);
		
    fitFunc->SetParameter(6, 0.05*hNsigma->GetMaximum());
    fitFunc->SetParameter(7, 4.); //was at 5. but it seems like 4. works better
    fitFunc->SetParameter(8, 3.);
		
		hNsigma->Fit("fitFunc");
    
    float  ampPi = fitFunc->GetParameter(0);
    float centPi = fitFunc->GetParameter(1);
    float  sigPi = fitFunc->GetParameter(2);
    piFunc->SetParameters(ampPi,centPi,sigPi);
    piFunc->SetLineColor(kViolet+1);
    
    float  ampKP = fitFunc->GetParameter(3);
    float centKP = fitFunc->GetParameter(4);
    float  sigKP = fitFunc->GetParameter(5);
    kpFunc->SetParameters(ampKP,centKP,sigKP);
    kpFunc->SetLineColor(kGreen+2);
    
    float  ampE  = fitFunc->GetParameter(6);
    float centE  = fitFunc->GetParameter(7);
    float  sigE  = fitFunc->GetParameter(8);
    eFunc->SetParameters(ampE,centE,sigE);
    eFunc->SetLineColor(kBlue);
    
    piFunc->Draw("same");
    kpFunc->Draw("same");
    eFunc->Draw("same");
    
    TLine *l1 = new TLine( 2.5,0, 2.5,0.9*hNsigma->GetMaximum());
    TLine *l2 = new TLine(-1.0,0,-1.0,0.9*hNsigma->GetMaximum());
    l1->SetLineColor(kOrange+2);
    l2->SetLineColor(kOrange+2);
    l1->SetLineWidth(2);
    l2->SetLineWidth(2);
    
    l1->Draw();
    l2->Draw();
		
		//*
    float  totYield = fitFunc->Integral(-1.,2.5);
    float pionYield =  piFunc->Integral(-1.,2.5);
    float   kpYield =  kpFunc->Integral(-1.,2.5);
    float    eYield =   eFunc->Integral(-1.,2.5);
		//*/
		/*
     float  totYield = fitFunc->Integral(-2.,2.);
     float pionYield =  piFunc->Integral(-2.,2.);
     float   kpYield =  kpFunc->Integral(-2.,2.);
     float    eYield =   eFunc->Integral(-2.,2.);
     //*/
    
    
    
    totalYieldWhole += totYield;
    pionYieldWhole += pionYield;
    kpYieldWhole += kpYield;
    electYieldWhile += eYield;
    
    
    printf("\nTotal Yield\tPion Yield\tK/p Yield\tElect Yield\n");
    printf("%e\t%e\t%e\t%e\n",totYield,pionYield,kpYield,eYield);
    printf("Pion Fraction = %e\n",(pionYield/totYield));
    
		
		totalYeild[ihist] = totYield;
		
		pionFrac[ihist]  = pionYield/totYield;
		kpFrac[ihist]    = kpYield/totYield;
		electFrac[ihist] = eYield/totYield;
		
		etastart[ihist] = -2+ihist*0.2;
		etaend[ihist] = -2+(ihist+1)*0.2;
    
		eta[ihist] = (etastart[ihist]+etaend[ihist])*.5;
		
		piYield[ihist] = pionYield;
		
		if (highestYield < pionYield){highestYield = pionYield;}
		
		
	}
	
	
	double normlzd_PiYield[20];
	
	double sumPiYield = 0;
  
	for (int i=0; i<20; i++)
	{
		if (pionFrac[i] != pionFrac[i])
		{
			cout << i << "  " << eta[i] << "  testFailed" << " highyeild " << highestYield << endl;
			pionFrac[i] = -.2;
		}
		else
		{
			cout << i << "  " << eta[i] << "  " << pionFrac[i] << " highyeild " << highestYield << endl;
			
		}
		
		normlzd_PiYield[i] = piYield[i]/highestYield; 
		
    
		sumPiYield += piYield[i];
		
	}
	
  double pionFracErr[20];
  double kpFracErr[20];
  double electFracErr[20];
  
  for (int i=0; i<20; i++)
  {
    pionFracErr[i] = sqrt((1-pionFrac[i])*pionFrac[i]/totalYeild[i]);
    kpFracErr[i] = sqrt((1-kpFrac[i])*kpFrac[i]/totalYeild[i]);
    electFracErr[i] = sqrt((1-electFrac[i])*electFrac[i]/totalYeild[i]);
    
  }  
  
  
  
	
	cout << "total Pion Yield = " << sumPiYield << endl;
	
	
	TGraphErrors* gPionYield = new TGraphErrors(20,eta,normlzd_PiYield,0,0);
	gPionYield->SetMarkerColor(kRed+2);
	gPionYield->SetMarkerStyle(24);
	
	TGraphErrors* gPionFrac = new TGraphErrors(20,eta,pionFrac,0,pionFracErr);
	TGraphErrors* gKpFrac   = new TGraphErrors(20,eta,kpFrac,0,kpFracErr);	
	TGraphErrors* gElecFrac = new TGraphErrors(20,eta,electFrac,0,electFracErr);
	
	
	
	
	gPionFrac->SetMarkerColor(kViolet+1);
  gPionFrac->SetLineColor(kViolet+1);
  gPionFrac->SetLineWidth(2);
	gKpFrac->SetMarkerColor(kGreen+2);
  gKpFrac->SetLineColor(kGreen+2);
  gKpFrac->SetLineWidth(2);
	gKpFrac->SetMarkerStyle(22);	
	gElecFrac->SetMarkerColor(kBlue);
	gElecFrac->SetLineColor(kBlue);
	gElecFrac->SetLineWidth(2);
	gElecFrac->SetMarkerStyle(20);
	
	
	TMultiGraph* multiFracs = new TMultiGraph();
	multiFracs->Add(gPionFrac);
	multiFracs->Add(gKpFrac);
	multiFracs->Add(gElecFrac);
	//multiFracs->Add(gPionYield);
  
	TCanvas* cMultiG = new TCanvas();
	multiFracs->Draw("AP");
	multiFracs->GetXaxis()->SetTitle("#eta^{#pi^{+}#pi^{-}}");
	multiFracs->GetYaxis()->SetTitle("particle Fractions");
	gPad->Modified();
	
	TLegend* leg = new TLegend(0.52,0.17,0.89,0.30);
	leg->AddEntry(gPionFrac,"Pion","P");
	leg->AddEntry(gKpFrac,"K/P","P");
	leg->AddEntry(gElecFrac,"Electron","P");
	//  leg->Draw();
	
	TCanvas* cPiYeild = new TCanvas();
	TGraphErrors* gPionYield = new TGraphErrors(20,eta,piYield,0,0);
	
	
	gPionYield->Draw("AP");
	gPionYield->SetMarkerColor(kRed+2);
	gPionYield->SetMarkerStyle(24);
	gPionYield->GetXaxis()->SetTitle("#eta^{#pi^{+}#pi^{-}}");
	gPionYield->GetYaxis()->SetTitle("Pion Yield");
	
	
	
	
	
	cout << pionYieldWhole/totalYieldWhole << endl;
	
	
	
	
	hTotal->Draw();
	
  TF1 *fitFunc = new TF1("fitFunc","gaus(0)+gaus(3)+gaus(6)",-10,10);
  TF1 *piFunc = new TF1("piFunc","gaus(0)",-10,10);
  TF1 *kpFunc = new TF1("kpFunc","gaus(0)",-10,10);
  TF1  *eFunc = new TF1( "eFunc","gaus(0)",-10,10);
  fitFunc->SetParName(0, "A_{#pi}");
  fitFunc->SetParName(1, "#LTn_{#pi}#GT");
  fitFunc->SetParName(2, "#sigma_{#pi}");
  fitFunc->SetParName(3, "A_{K/p}");
  fitFunc->SetParName(4, "#LTn_{K/p}#GT");
  fitFunc->SetParName(5, "#sigma_{K/p}");
  fitFunc->SetParName(6, "A_{e}");
  fitFunc->SetParName(7, "#LTn_{e}#GT");
  fitFunc->SetParName(8, "#sigma_{e}");
  
  fitFunc->SetParameter(0, hTotal->GetMaximum());
  fitFunc->SetParameter(1, 0.);
  fitFunc->SetParameter(2, 1.);
  
  fitFunc->SetParameter(3, 0.05*hTotal->GetMaximum());
  fitFunc->SetParameter(4,-3.);
  fitFunc->SetParameter(5, 1.5);
  
  fitFunc->SetParameter(6, 0.05*hTotal->GetMaximum());
  fitFunc->SetParameter(7, 4.); //was at 5. but it seems like 4. works better
  fitFunc->SetParameter(8, 3.);
  
	
	
	
  hTotal->Fit("fitFunc");
  
  float  ampPi = fitFunc->GetParameter(0);
  float centPi = fitFunc->GetParameter(1);
  float  sigPi = fitFunc->GetParameter(2);
  piFunc->SetParameters(ampPi,centPi,sigPi);
  piFunc->SetLineColor(kViolet+1);
  
  float  ampKP = fitFunc->GetParameter(3);
  float centKP = fitFunc->GetParameter(4);
  float  sigKP = fitFunc->GetParameter(5);
  kpFunc->SetParameters(ampKP,centKP,sigKP);
  kpFunc->SetLineColor(kGreen+2);
  
  float  ampE  = fitFunc->GetParameter(6);
  float centE  = fitFunc->GetParameter(7);
  float  sigE  = fitFunc->GetParameter(8);
  eFunc->SetParameters(ampE,centE,sigE);
  eFunc->SetLineColor(kBlue);
  
  piFunc->Draw("same");
  kpFunc->Draw("same");
  eFunc->Draw("same");
  
  TLine *l1 = new TLine( 2.5,0, 2.5,0.9*hNsigma->GetMaximum());
  TLine *l2 = new TLine(-1.0,0,-1.0,0.9*hNsigma->GetMaximum());
  l1->SetLineColor(kOrange+2);
  l2->SetLineColor(kOrange+2);
  l1->SetLineWidth(2);
  l2->SetLineWidth(2);
  
  l1->Draw();
  l2->Draw();
  
  //*
  float  totYield = fitFunc->Integral(-1.,2.5);
  float pionYield =  piFunc->Integral(-1.,2.5);
  float   kpYield =  kpFunc->Integral(-1.,2.5);
  float    eYield =   eFunc->Integral(-1.,2.5);
  
  double pionerr = sqrt((1-pionYield/totYield)*pionYield/totYield/totalYeild);

  
	cout << pionYield/totYield << " " << pionerr << endl;
	
	
	
	
	
	
	
	
	
	
	
  
  
  
  
}