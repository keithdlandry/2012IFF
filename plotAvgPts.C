/*
 *  plotAvgPts.C
 *  2012IFF
 *
 *  Created by Keith Landry on 8/13/14.
 *  UCLA
 *
 */




void plotAvgPts(){

	char hist  [100];
	char hfile [100];
	
	double avgPt2[9];
	double avgPtE2[9];

	double avgPt3[9];
	double avgPtE3[9];

	double avgPt4[9];
	double avgPtE4[9];

	
	double massbin[] = {1,2,3,4,5,6,7,8,9};
	
	double massPoints5_19_binning_6_25rad4HiEta[9] = {0.34464, 0.409933, 0.470963, 0.528955, 0.589736, 0.66957, 0.782231, 0.954088, 1.31387};
	double massPointsErr5_19_binning_6_25rad4HiEta[9] = {3.80708e-05, 2.91162e-05, 2.79463e-05, 2.78612e-05, 2.90598e-05, 3.85227e-05, 5.02955e-05, 0.000104299, 0.000543504};
	
	double massPoints5_19_binning_6_25HiEta[9] = {0.34464, 0.409933, 0.470963, 0.52882, 0.588747, 0.666938, 0.77988, 0.948972, 1.2884};
	double massPointsErr5_19_binning_6_25HiEta[9] = {3.80708e-05, 2.91162e-05, 2.79463e-05, 2.78685e-05, 3.08316e-05, 4.68857e-05, 6.88323e-05, 0.000158, 0.000873323};
	
	double massPoints5_19_binning_6_25rad2HiEta[9] = {0.34464, 0.409565, 0.469023, 0.526799, 0.587561, 0.665328, 0.777463, 0.942446, 1.26473};
	double massPointsErr5_19_binning_6_25rad2HiEta[9] = {3.80708e-05, 2.91709e-05, 3.19018e-05, 3.81942e-05, 5.03001e-05, 8.50081e-05, 0.000135501, 0.000354785, 0.00200707};
	

	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/avgPtOfMassBins_rad2.root");  
	
	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
	for (int ihist=0; ihist<9; ihist++)
	{
	
		sprintf(hist,"hPtofMass_%i",ihist);
		cout << hist << endl;
		
		TH1F *hPthist = (TH1F*) file->Get(hist);
	  assert(hPthist);
		
		avgPt2[ihist] = hPthist->GetMean();
		avgPtE2[ihist] = hPthist->GetMeanError();

		cout << avgPt2[ihist] << " +/- " << avgPtE2[ihist] << endl;
		
	
	}
	
	
	
	

	
	
	file->Close();
	
	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/avgPtOfMassBins_rad3.root");  

	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
	for (int ihist=0; ihist<9; ihist++)
	{
		
		sprintf(hist,"hPtofMass_%i",ihist);
		cout << hist << endl;
		
		TH1F *hPthist = (TH1F*) file->Get(hist);
	  assert(hPthist);
		
		avgPt3[ihist] = hPthist->GetMean();
		avgPtE3[ihist] = hPthist->GetMeanError();
		
		cout << avgPt3[ihist] << " +/- " << avgPtE3[ihist] << endl;
		
		
	}
	
	file->Close();
	
	sprintf(hfile,"~/Desktop/Research/2012IFF/rootFiles/avgPtOfMassBins_rad4.root");  
	
	TFile* file = TFile::Open(hfile,"read");
	assert(file);
	
	
	for (int ihist=0; ihist<9; ihist++)
	{
		
		sprintf(hist,"hPtofMass_%i",ihist);
		cout << hist << endl;
		
		TH1F *hPthist = (TH1F*) file->Get(hist);
	  assert(hPthist);
		
		avgPt4[ihist] = hPthist->GetMean();
		avgPtE4[ihist] = hPthist->GetMeanError();
		
		cout << avgPt4[ihist] << " +/- " << avgPtE4[ihist] << endl;
		
		
	}
	
	
	TGraphErrors* gAvgPt2 = new TGraphErrors(9,massPoints5_19_binning_6_25rad2HiEta,avgPt2,massPointsErr5_19_binning_6_25rad2HiEta,avgPtE2);
	TGraphErrors* gAvgPt3 = new TGraphErrors(9,massPoints5_19_binning_6_25HiEta,avgPt3,massPointsErr5_19_binning_6_25HiEta,avgPtE3);
	TGraphErrors* gAvgPt4 = new TGraphErrors(9,massPoints5_19_binning_6_25rad4HiEta,avgPt4,massPointsErr5_19_binning_6_25rad4HiEta,avgPtE4);

	gAvgPt2->SetMarkerColor(kRed);
	gAvgPt3->SetMarkerColor(kOrange);
	gAvgPt4->SetMarkerColor(kBlue);
	
	TMultiGraph* multi = new TMultiGraph();
	
	multi->Add(gAvgPt2);
	multi->Add(gAvgPt3);
	multi->Add(gAvgPt4);
	

	multi->Draw("AP");
	
	multi->GetXaxis()->SetTitle("M_{inv}^{#pi^{+}#pi^{-}}");
	multi->GetYaxis()->SetTitle("Avg P_{T}^{#pi^{+}#pi^{-}}");
	gPad->Modified();
	
	
	TLegend* leg = new TLegend(0.52,0.17,0.89,0.30);
	leg->AddEntry(gAvgPt2,"cone 0.2","P");
	leg->AddEntry(gAvgPt3,"cone 0.3","P");
	leg->AddEntry(gAvgPt4,"cone 0.4","P");
	
	leg->Draw();
	
	
	
	
	
	
	
	
	

}