/*
 *  plotAvgMass.C
 *  2012IFF
 *
 *  Created by Keith Landry on 8/13/14.
 *  UCLA
 *
 */



void plotAvgMass(){
	
	char hist  [100];
	char hfile [100];
	
	double avgMass2[9];
	double avgMassE2[9];
	
	double avgMass3[9];
	double avgMassE3[9];
	
	double avgMass4[9];
	double avgMassE4[9];
	
	
	//double massbin[] = {1,2,3,4,5,6,7,8,9};
	
	double ptPoints5_19_binning_6_25rad4HiEta[9] = {3.42649, 3.92463, 4.38398, 4.89909, 5.51145, 6.29922, 7.2592, 8.70378, 12.4737};
	double ptPointsErr5_19_binning_6_25rad4HiEta[9] = {0.00023969, 0.000181033, 0.000195846, 0.000232986, 0.000294996, 0.000418059, 0.000548649, 0.00116364, 0.00748337};

	double ptPoints5_19_binning_6_25HiEta[9] = {3.43092, 3.92566, 4.38554, 4.90152, 5.5136, 6.30225, 7.26139, 8.71256, 12.4973};
	double ptPointsErr5_19_binning_6_25HiEta[9] = {0.00029133, 0.000217519, 0.000231328, 0.0002694, 0.000332522, 0.000462408, 0.000598435, 0.00124935, 0.00786287};

	double ptPoints5_19_binning_6_25rad2HiEta[9] = {3.43441, 3.92762, 4.38712, 4.90181, 5.51537, 6.3054, 7.26821, 8.73261, 12.5816};
	double ptPointsErr5_19_binning_6_25rad2HiEta[9] = {0.000415112, 0.000304736, 0.000313663, 0.000362253, 0.000442194, 0.000604562, 0.00075526, 0.00150712, 0.00897495};

	
	
	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/avgMassOfPtBins_rad2.root");  
	
	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
	for (int ihist=0; ihist<9; ihist++)
	{
		
		sprintf(hist,"hMassofPt_%i",ihist);
		cout << hist << endl;
		
		TH1F *hMasshist = (TH1F*) file->Get(hist);
	  assert(hMasshist);
		
		avgMass2[ihist] = hMasshist->GetMean();
		avgMassE2[ihist] = hMasshist->GetMeanError();
		
		cout << avgMass2[ihist] << " +/- " << avgMassE2[ihist] << endl;
		
		
	}
	
	
	
	
	
	
	
	file->Close();
	
	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/avgMassOfPtBins_rad3.root");  
	
	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
	for (int ihist=0; ihist<9; ihist++)
	{
		
		sprintf(hist,"hMassofPt_%i",ihist);
		cout << hist << endl;
		
		TH1F *hMasshist = (TH1F*) file->Get(hist);
	  assert(hMasshist);
		
		avgMass3[ihist] = hMasshist->GetMean();
		avgMassE3[ihist] = hMasshist->GetMeanError();
		
		cout << avgMass3[ihist] << " +/- " << avgMassE3[ihist] << endl;
		
		
	}
	
	file->Close();
	
	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/avgMassOfPtBins_rad4.root");  
	
	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
	for (int ihist=0; ihist<9; ihist++)
	{
		
		sprintf(hist,"hMassofPt_%i",ihist);
		cout << hist << endl;
		
		TH1F *hMasshist = (TH1F*) file->Get(hist);
	  assert(hMasshist);
		
		avgMass4[ihist] = hMasshist->GetMean();
		avgMassE4[ihist] = hMasshist->GetMeanError();
		
		cout << avgMass4[ihist] << " +/- " << avgMassE4[ihist] << endl;
		
		
	}
	
	
	TGraphErrors* gAvgMass2 = new TGraphErrors(9,ptPoints5_19_binning_6_25rad2HiEta,avgMass2,ptPointsErr5_19_binning_6_25rad2HiEta,avgMassE2);
	TGraphErrors* gAvgMass3 = new TGraphErrors(9,ptPoints5_19_binning_6_25HiEta,avgMass3,ptPointsErr5_19_binning_6_25HiEta,avgMassE3);
	TGraphErrors* gAvgMass4 = new TGraphErrors(9,ptPoints5_19_binning_6_25rad4HiEta,avgMass4,ptPointsErr5_19_binning_6_25rad4HiEta,avgMassE4);
	
	gAvgMass2->SetMarkerColor(kRed);
	gAvgMass3->SetMarkerColor(kOrange);
	gAvgMass4->SetMarkerColor(kBlue);
	
	TMultiGraph* multi = new TMultiGraph();
	
	multi->Add(gAvgMass2);
	multi->Add(gAvgMass3);
	multi->Add(gAvgMass4);
	
	
	multi->Draw("AP");
	multi->GetXaxis()->SetTitle("P_{T}^{#pi^{+}#pi^{-}}");
	multi->GetYaxis()->SetTitle("Avg M_{inv}^{#pi^{+}#pi^{-}}");


	gPad->Modified();
	
	TLegend* leg = new TLegend(0.52,0.17,0.89,0.30);
	leg->AddEntry(gAvgMass2,"cone 0.2","P");
	leg->AddEntry(gAvgMass3,"cone 0.3","P");
	leg->AddEntry(gAvgMass4,"cone 0.4","P");
	

  leg->Draw();




















}