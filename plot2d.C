/*
 *  plot2d.C
 *  2012IFF
 *
 *  Created by Keith Landry on 7/21/14.
 *  UCLA
 *
 */
//ANSEML'S BINNING SCHEME========================
//*
const int nPtBins    = 5;
const int nEtaBins   = 4;
const int nMassBins  = 5;
const int nPhisrBins = 32;    //moved from 16 to 32 on 4/29/2014


double    ptBinStart[nPtBins] = {3.0, 4.0, 5.0, 6.5, 8.0};
double    ptBinEnd[nPtBins]   = {4.0, 5.0, 6.5, 8.0, 50.0};  //Anselm used 1000.0 as last point

double    massBinStart[nMassBins] = {0.0, 0.4, 0.6, 0.8, 1.0};
double    massBinEnd[nMassBins]   = {0.4, 0.6, 0.8, 1.0, 100.5};

double    etaBinStart[nEtaBins] = {-2,-0.5,0.0,0.5};
double    etaBinEnd[nEtaBins]   = {-0.5,0.0,0.5, 2};



void plot2d(){


	
	ifstream infile;
	infile.open("/Users/keithlandry/Desktop/Research/2012IFF/rootFiles/asymmetriesOutfile.txt");
  if (!infile)
	{
		cout << "fuck" << endl;
	}
	
	TGraph2DErrors* gPtEta = new TGraph2DErrors();
	TGraph2DErrors* gMassEta = new TGraph2DErrors();
	TGraph2DErrors* gPtMass = new TGraph2DErrors();

	gPtEta->Set(nPtBins*nEtaBins);
	gMassEta->Set(nMassBins*nEtaBins);
	gPtMass->Set(nPtBins*nMassBins);
	
	double x;
	double y;
	double x;
	double z;
	double ex;
	double ey;
	double ez;
	
	double ptbin;
	double etabin;
	double massbin;
	
	double point = 0;
	
	string junk;
	
	infile >> junk;
	
	cout << junk << endl;
	
	for (int i=0; i<nPtBins; i++)
	{
		
		for (int j = 0; j<nEtaBins; j++)
		{
			infile >> ptbin;
			infile >> etabin;
			infile >> x;
			infile >> y;
			infile >> z;
			infile >> ex;
			infile >> ey;
			infile >> ez;
			
			cout << point << " " << x << "  " << y << "  " << z << "  " << ex << "  " << ey << "  " << ez << endl;
			
			
			gPtEta->SetPoint(point,x,y,z);
			gPtEta->SetPointError(point,ex,ey,ez);
			
			point++;
		}
	}
	
	
	
	TCanvas* c1 = new TCanvas();
	gPtEta->Draw("p0 err ");
	
	
	
	infile >> junk;
	
	cout << junk << endl;
	point = 0;	
	
	for (int i=0; i<nMassBins; i++)
	{
		
		for (int j = 0; j<nEtaBins; j++)
		{
			infile >> ptbin;
			infile >> massbin;
			infile >> x;
			infile >> y;
			infile >> z;
			infile >> ex;
			infile >> ey;
			infile >> ez;
			
			cout << point << " " << x << "  " << y << "  " << z << "  " << ex << "  " << ey << "  " << ez << endl;
			
			
			gMassEta->SetPoint(point,x,y,z);
			gMassEta->SetPointError(point,ex,ey,ez);
			
			point++;
		}
	}
	
	TCanvas* c2 = new TCanvas();
	gMassEta->GetYaxis()->SetRangeUser(-0.9,0.9);
	gMassEta->Draw("p0 err ");
	gMassEta->GetYaxis()->SetRangeUser(-0.9,0.9);

	
	infile >> junk;
	
	cout << junk << endl;
	point = 0;	
	
	for (int i=0; i<nPtBins; i++)
	{
		
		for (int j = 0; j<nMassBins; j++)
		{
			infile >> ptbin;
			infile >> massbin;
			infile >> x;
			infile >> y;
			infile >> z;
			infile >> ex;
			infile >> ey;
			infile >> ez;
			
			cout << point << " " << x << "  " << y << "  " << z << "  " << ex << "  " << ey << "  " << ez << endl;
			
			
			gPtMass->SetPoint(point,x,y,z);
			gPtMass->SetPointError(point,ex,ey,ez);
			
			point++;
		}
	}
	
	TCanvas* c3 = new TCanvas();
	gPtMass->GetZaxis()->SetRangeUser(0,0.07);
	gPtMass->Draw("p0 err ");

	

}