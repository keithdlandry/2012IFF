/*
 *  graphSweepAsyms.C
 *  2012IFF
 *
 *  Created by Keith Landry on 4/14/14.
 *  UCLA
 *
 */




void graphSweepAsyms(){






	double massBin0[7]  = {.0034,.001,.004,.0017,.0001,-.0001,.011};
	double massBin0E[7] = {.004,.004,.004,.004,.004,.004,.004}; 
	double massBin1[7]  = {.0023,-.001,-.0038,-.001,.005,-.0075,-.0014};
	double massBin1E[7] = {.0026,.0027,.0027,.0026,.0026,.0027,.0027}; 
	double massBin2[7]  = {-.006,-.0147,.0061,-.0064,-.0094,-.0086,-.016};
	double massBin2E[7] = {.003,.0035,.0036,.0035,.0034,.0036,.0036}; 
	double massBin3[7]  = {-.007,.0044,-.017,-.01,.0002,-.002,.0007};
	double massBin3E[7] = {.006,.006,.006,.006,.006,.006,.006}; 
	double massBin4[7]  = {.019,.0035,.0146,-.023,-.003,-.026,-.023};
	double massBin4E[7] = {.009,.0097,.01,.01,.0097,.01,.0096}; 
	
	double pairStart[7] = {1,3,5,7,9,11,13};
	
	
	TGraphErrors* mb0 = new TGraphErrors(7,pairStart,massBin0,0,massBin0E);
	TGraphErrors* mb1 = new TGraphErrors(7,pairStart,massBin1,0,massBin1E);
	TGraphErrors* mb2 = new TGraphErrors(7,pairStart,massBin2,0,massBin2E);
	TGraphErrors* mb3 = new TGraphErrors(7,pairStart,massBin3,0,massBin3E);
	TGraphErrors* mb4 = new TGraphErrors(7,pairStart,massBin4,0,massBin4E);
	
	
	
	
	TCanvas* cGraphs = new TCanvas();
	cGraphs->Divide(3, 2);
  cGraphs->cd(1);
	mb0->Draw("AP");
	mb0->GetXaxis()->SetTitle("pion pair (M)");
	mb0->GetYaxis()->SetTitle("Aut");
	mb0->SetTitle("Asymmetries for mass bin 0");

	cGraphs->cd(2);
	mb1->Draw("AP");
	mb1->GetXaxis()->SetTitle("pion pair (M)");
	mb1->GetYaxis()->SetTitle("Aut");
	mb1->SetTitle("Asymmetries for mass bin 1");
	
	cGraphs->cd(3);
	mb2->Draw("AP");
	mb2->GetXaxis()->SetTitle("pion pair (M)");
	mb2->GetYaxis()->SetTitle("Aut");
	mb2->SetTitle("Asymmetries for mass bin 2");
	
	cGraphs->cd(4);
	mb3->Draw("AP");
	mb3->GetXaxis()->SetTitle("pion pair (M)");
	mb3->GetYaxis()->SetTitle("Aut");
	mb3->SetTitle("Asymmetries for mass bin 3");
	
	cGraphs->cd(5);
	mb4->Draw("AP");
	mb4->GetXaxis()->SetTitle("pion pair (M)");
	mb4->GetYaxis()->SetTitle("Aut");
	mb4->SetTitle("Asymmetries for mass bin 4");
	
	
	



}

