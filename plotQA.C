/*
 *  plotQA.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/11/14.
 *  UCLA
 *
 */




void plotQA(){

	
	//TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/pairQABlue.root");
  TFile* infile = new TFile("/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/variableswithallcuts.root");
	
	
	
	/*
	TH1D* hInvarM    = (TH1D*)infile->Get("invarM");
	TH1D* hEtaTot	   = infile->Get("etaTot");
	TH1D* hPhiR      = infile->Get("hPhiR");
	TH1D* hPhiS      = infile->Get("hPhiS");
	TH1D* hPhiSR     = infile->Get("hPhiSR");
	TH1D* hTheta     = infile->Get("hTheta");
	TH1D* hCosTheta  = infile->Get("hCosTheta");
	TH1D* hZ         = infile->Get("hZ");
	TH1D* hPtTOT     = infile->Get("hPt");
	
	
	
	
	TH1D* hPhi       = infile->Get("hPhi");
		
	TCanvas* c3 = new TCanvas();
	hPhiR->GetXaxis()->SetTitle("#phi_{R}");
	hPhiR->Draw();
	
	TCanvas* c4 = new TCanvas();
	hPhiS->GetXaxis()->SetTitle("#phi_{S}");
	hPhiS->Draw();
	
	TCanvas* c5 = new TCanvas();
	hPhiSR->GetXaxis()->SetTitle("#phi_{S} - #phi_{R}");
	hPhiSR->Draw();
	

	TCanvas *cPhi = new TCanvas();
	hPhi->GetXaxis()->SetTitle("#phi^{#pi^{+}#pi^{-}}");
	hPhi->Draw();

	/*

	TCanvas* c6 = new TCanvas();
	hTheta->GetXaxis()->SetTitle("#theta");
	hTheta->Draw();
	
	TCanvas* c7 = new TCanvas();
	hPtTOT->GetXaxis()->SetTitle("P_{T}^{#pi^{+}#pi^{-}}");
	hPtTOT->Draw();
	

	TCanvas* c1 = new TCanvas();
	hInvarM->GetXaxis()->SetTitle("M_{Inv}^{#pi^{+}#pi^{-}}");
	hInvarM->Draw();
	
	TCanvas* c2 = new TCanvas();
	hEtaTot->GetXaxis()->SetTitle("#eta^{#pi^{+}#pi^{-}}");
	hEtaTot->Draw();
	*/
	
	string title = "All Cuts";
	string cut = "allCuts"; 	

	
	TH1D* hEta	      = infile->Get("hEta");
	TH1D* hPt         = infile->Get("hPt");
	TH1D* hnSigmaPion = infile->Get("hnSigmaPion");
	TH1D* hnHitsFit   = infile->Get("hnHitsFit");
	TH1D* hVertexZ    = infile->Get("hVertexZ");
	
	
	TCanvas* c11 = new TCanvas();
	hEta->SetTitle(title.c_str());
	hEta->GetXaxis()->SetTitle("track #eta");
	hEta->Draw();
	
	TCanvas* c12 = new TCanvas();
	hPt->SetTitle(title.c_str());
	hPt->GetXaxis()->SetTitle("track P_{T}");
	hPt->Draw();
	
	TCanvas* c13 = new TCanvas();
	hnSigmaPion->SetTitle(title.c_str());
	hnSigmaPion->GetXaxis()->SetTitle("n_{#sigma}(#pi)");
	hnSigmaPion->Draw();
	
	TCanvas* c14 = new TCanvas();
	hVertexZ->SetTitle(title.c_str());
	hVertexZ->GetXaxis()->SetTitle("vertex Z");
	hVertexZ->Draw();
	
	TCanvas* c15 = new TCanvas();
	hnHitsFit->SetTitle(title.c_str());
	hnHitsFit->GetXaxis()->SetTitle("nHitsFit");
	hnHitsFit->Draw();
	
	
	
	string path = "/Users/keithlandry/Desktop/Research/2012IFF/trackQAplots/";
	
	
	string pdf = ".pdf";
	string png = ".png";
	
	string etanamePDF = path + "trackEta" + cut + pdf;
	string etanamePNG = path + "trackEta" + cut + png;
	
	
	string ptnamePDF = path + "trackPt" + cut + pdf;
	string ptnamePNG = path + "trackPt" + cut + png;

	string nsigmanamePDF = path + "nSigmaPion" + cut + pdf;
	string nsigmanamePNG = path + "nSigmaPion" + cut + png;

	string nhitsnamePDF = path + "nHitsFit" + cut + pdf;
	string nhitsnamePNG = path + "nHitsFit" + cut + png;

	string vertnamePDF = path + "vertexZ" + cut + pdf;
	string vertnamePNG = path + "vertexZ" + cut + png;

	
	
	//*
	c11->SaveAs(etanamePDF.c_str());
	c11->SaveAs(etanamePNG.c_str());
	
	c12->SaveAs(ptnamePDF.c_str());
	c12->SaveAs(ptnamePNG.c_str());

	c13->SaveAs(nsigmanamePDF.c_str());
	c13->SaveAs(nsigmanamePNG.c_str());

	c14->SaveAs(vertnamePDF.c_str());
	c14->SaveAs(vertnamePNG.c_str());

	c15->SaveAs(nhitsnamePDF.c_str());
	c15->SaveAs(nhitsnamePNG.c_str());

	//*/
	
	
	


}