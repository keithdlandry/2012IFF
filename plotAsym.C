/*
 *  plotAsym.C
 *  2012IFF
 *
 *  Created by Keith Landry on 1/28/14.
 *  UCLA
 *
 */

#include "TGraphErrors.h"
#include "TMultiGraph.h"
void plotAsym(){



/*
	double Am[] = {-.032970,-.012780,-.035850,-.108400,-.053570};
	double Em[] = {.015360,.009790,.013410,.023300,.037620};
	double m[]  = {.36,.50,.69,.88,1.19};
*/
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
	
	double anselmM[]  = {.0054,.0179,.0229,.0695,.0388};
	double anselmMe[] = {.0101,.0068,.0081,.0134,.0198};
	
	double anselmE[]  = {-0.0002,0.0075,0.0131,0.0311};
	double anselmEe[] = {0.0060,0.0061,0.0061,0.0060};
	
	
	
	for (int i=0; i<5; i++)
	{
		Am[i] = -1*Am[i];
		Ap[i] = -1*Ap[i];
		sinAm[i] = -1*sinAm[i];
	
		if (i!=5)
		{
			Ae[i] = -1*Ae[i];
		}
		
	}
	
	
	
	
	
	TGraphErrors* gM = new TGraphErrors(5,m,Am,0,Em);
	TGraphErrors* gP = new TGraphErrors(5,p,Ap,0,Ep);
	TGraphErrors* gE = new TGraphErrors(4,e,Ae,0,Ee);
	
	TGraphErrors* gsin = new TGraphErrors(5,m,sinAm,0,sinEm);
	
	TGraphErrors* gAnM = new TGraphErrors(5,m,anselmM,0,anselmMe);
	TGraphErrors* gAnP = new TGraphErrors(5,p,anselmP,0,anselmPe);
	TGraphErrors* gAnE = new TGraphErrors(4,e,anselmE,0,anselmEe);
	
	TMultiGraph* multiM = new TMultiGraph();
	
	gM->SetMarkerColor(2);
	

	multiM->Add(gM);
	multiM->Add(gAnM);

	TCanvas* cM = new TCanvas();
	multiM->Draw("AP");
	multiM->GetXaxis()->SetTitle("M_{Inv}^{#pi^{+}#pi^{-}}");
	multiM->GetYaxis()->SetTitle("A_{UT}");
	
	gPad->Modified();

	
	gP->SetMarkerColor(2);
	
	TMultiGraph* multiP = new TMultiGraph();

	
	multiP->Add(gP);
	multiP->Add(gAnP);
	
	TCanvas* cP = new TCanvas();
	multiP->Draw("AP");
	multiP->GetXaxis()->SetTitle("P_{T}^{#pi^{+}#pi^{-}}");
	multiP->GetYaxis()->SetTitle("A_{UT}");

	gPad->Modified();
	
	
	
	TMultiGraph* multiE = new TMultiGraph();
	
	gE->SetMarkerColor(2);
	
	multiE->Add(gE);
	multiE->Add(gAnE);
	
	TCanvas* cE = new TCanvas();
	
	
	multiE->Draw("AP");
	multiE->GetXaxis()->SetTitle("#eta^{#pi^{+}#pi^{-}}");
	multiE->GetYaxis()->SetTitle("A_{UT}");
	
	gPad->Modified();
	
	
	TCanvas* cSin = new TCanvas();
	
	TMultiGraph* multiSin = new TMultiGraph();
	
	
	gsin->SetMarkerColor(2);
	
	multiSin->Add(gsin);
	multiSin->Add(gAnM);

	multiSin->Draw("AP");
	multiSin->GetXaxis()->SetTitle("M^{#pi^{+}#pi^{-}}");
	multiSin->GetYaxis()->SetTitle("A_{UT}");
	
	gPad->Modified();

	
	
}