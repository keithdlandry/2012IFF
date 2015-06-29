/*
 *  findingKaons.C
 *  2012IFF
 *
 *  Created by Keith Landry on 1/29/15.
 *  UCLA
 *
 */




const int nPbins = 11;
double pBinStart[nPbins] = {1.5,1.9,2.3,2.7,3.1,3.5,3.9,4.3,4.7,5.1,5.5};
double pBinEnd[nPbins] = {1.9,2.3,2.7,3.1,3.5,3.9,4.3,4.7,5.1,5.5,5.9};



//FUNCTIONS======================================
//creating histograms
void createNbins(const int nBins, TH1D* hist[nBins], int histbins, double histmin, double histmax, string name){
	
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		
		stringstream ss;
		ss << iBin;
		string fullname = name + ss.str();
		cout << fullname << endl;
		
		hist[iBin] = new TH1D(fullname.c_str(),fullname.c_str(),histbins,histmin,histmax);
		
	}
}
//creating histograms
void createNbins(const int nBins, TH2D* hist[nBins], int histbinsX, double histminX, double histmaxX, int histbinsY, double histminY, double histmaxY, string name){
	
	
	for (int iBin = 0; iBin < nBins; iBin++)
	{
		
		stringstream ss;
		ss << iBin;
		string fullname = name + ss.str();
		cout << fullname << endl;
		
		hist[iBin] = new TH2D(fullname.c_str(),fullname.c_str(),histbinsX,histminX,histmaxX,histbinsY,histminY,histmaxY);
		
	}
}

void fillCorrectPbin_2d(TH2D* histo[nPbins], double momentum,double xval, double yval){
  
	for (int iP = 0; iP < nPbins; iP++)
	{
		if (momentum >= pBinStart[iP] && momentum < pBinEnd[iP])
		{

      histo[iP]->Fill(xval,yval);
      
		}
	}
}

void writeNbins_2d(const int nBins, TH2D* hist[nBins]){
	
	for (int i = 0; i < nBins; i++)
	{
		hist[i]->Write();
	}
	
	
}


void findingKaons(string fileList, string jobID){
  
  
  
  
  
  //LOAD LIBRARIES
  cout << "\n";
  gROOT->Macro("/star/u/klandry/ucladisk/2012IFF/StRoot/LoadLibs.C");
  
  cout << "\n";
  cout << "\n";
  
  
  //CHAIN OF MAKERS
  StChain* chain = new StChain; 
  
  //MUDST READER
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",fileList.c_str(),"",100000,"MuDst");
  
  chain->Make(0);
  StMuEvent* MuEvent = muDstMaker->muDst()->event();
  int runID = MuEvent->runId();
  
  stringstream ss;
  ss << runID;
  string runNumber = ss.str();
  
  
  //StarDbMaker
  St_db_Maker* dbMaker = new St_db_Maker("db", "MySQL:StarDb", "$STAR/StarDb");
  
  //SPINDBMAKER
  StSpinDbMaker* spinDbMaker = new StSpinDbMaker("StSpinDbMaker");
  
  cout << "\n";
    
  
  int iEvent = 0;
  
  cout << "\n";
  cout << "\n";
  cout << "Init() ......." << endl;
  cout << "\n";
  cout << "\n";
  
  chain->Init();
  
  cout << "\n";
  cout << "\n";
  cout << "Make() ......." << endl;
  cout << "\n";
  cout << "\n";
  
  //int nEvents = 2;
  //chain->EventLoop(nEvents);
  
  
  
  //histograms 
  
/*
  TH2D* hNSigPiKa = new TH2D("hNSigPiKa","hNSigPiKa",50,-10,10,50,-10,10);
  TH2D* htofdata  = new TH2D("htofdata","htofdata",100,0,2,100,0,5);

  TH1D* hMass2 = new TH1D("hMass2","hmass2",200,-1,1.5);
  
  TH2D* hMnSigPi = new TH2D("hMnSigPi","hMnSigPi",100,-4,4,100,-1,1.5);
  */
  /*
  const int nPbins = 5
  double pBinStart[nPbins] = {1.5,2.5,4.0,5.5,7.0};
  double pBinEnd[nPbins] = {2.5,4.0,5.5,7.0,10};
*/
  
  
  
  
  //HISTOGRAMS TO FIND LIKELYHOOD FUNCTION P(nSigPi,nSigKa,M2|Pion,pt)
  // need to do for differnt pt ranges
  // use ToF M2 cut of < 0 to ensure Pion for nsigPi
  // use nSigPi cut of > 1.5 to ensure Pion for tofM2 plot
  TH1D* hNsigPi_pi[nPbins];
  createNbins(nPbins, hNsigPi_pi, 50, -10, 10, "hNsigPi_pi_pBin_");  
  TH1D* hNsigKa_pi[1];
  hNsigKa_pi[0] = new TH1D("hNsigKa_pi","hNsigKa_pi",50,-10,10);
  TH1D*hMass2_pi[1];
  hMass2_pi[0] = new TH1D("nMass2_pi","hMass2_pi",50,-1,2);
  
  //also need to find likelyhood function P(nSigPi,nSigKa,M2|Kaon,pt)
  // use tof M2 cut of > .25, < .5 
  // use nSigPi cut of < -2 
  //
  TH1D* hNsigPi_ka[1];
  hNsigPi_ka[0] = new TH1D("hNsigPi_ka","hNsigPi_ka",50,-10,10);
  TH1D* hNsigKa_ka[1];
  hNsigKa_ka[0] = new TH1D("hNsigKa_ka","hNsigKa_ka",50,-10,10);
  TH1D*hMass2_ka[1];
  hMass2_ka[0] = new TH1D("nMass2_ka","hMass2_ka",50,-1,2);
  
  

  //HISTOGRAMS TO FIND PRIOR P(nSigPi,nSigKa,M2)
  // (NO CUTS, should only need 1 pt range)
  TH1D* hNsigPiPrior[1];
  hNsigPiPrior[0] = new TH1D("hNsigPiPrior","hNsigPiPrior",50,-10,10);
  TH1D* hNsigKaPrior[1];
  hNsigKaPrior[0] = new TH1D("hNsigKaPrior","hNsigKaPrior",50,-10,10);
  TH1D*hMass2Prior[1];
  hMass2Prior[0] = new TH1D("nMass2Prior","hMass2Prior",50,-1,2);
  
  
  //*/
  
  
  TH2D* hTofNsigPi[nPbins];
  createNbins(nPbins, hTofNsigPi, 100, -5, 5, 100, -1 , 2, "hTofNsigPi_pBin_");
  TH2D* hTofNsigKa[nPbins];
  createNbins(nPbins, hTofNsigKa, 100, -5, 5, 100, -1 , 2, "hTofNsigKa_pBin_");

  
  
  
  
  //*
  while (chain->Make(iEvent) == kStOK)
  {
    iEvent++;
    if (iEvent%10000 == 0) {cout << "processing event number " << iEvent << endl;}    
    //if (iEvent >= 10000){break;}
    
    //get muDst from maker
    StMuDst* muDst = muDstMaker->muDst();	
    assert(muDst);
    if (!muDst)
    {
      cout << "ERROR: MEMORY COULD NOT BE ALLOCATED" << endl;
    }
    
    double highRank = 0;
    int highRankVertIndex = 0;
    
    for (int iVert = 0; iVert < muDst->numberOfPrimaryVertices(); iVert++)
    {
      StMuPrimaryVertex* vertex = muDst->primaryVertex(iVert);
      assert(vertex);
      
      if (fabs(vertex->position().z()) < 60)
      {
        double ranking = vertex->ranking();
        
        
        if (ranking > highRank)
        {
          highRank = ranking;
          highRankVertIndex = iVert;
        }
      }
    }//end vertex loop
    
    //loop over tracks once
    for (int iTrack = 0; iTrack < muDst->numberOfPrimaryTracks()-1; iTrack++)
    {
      
      
    
      
      StMuTrack* track1 = muDst->primaryTracks(iTrack);
      //*
      
      if (track1 == NULL)
      {
        break;
      }
      assert(track1);
     // cout << track1->nSigmaPion() << endl;
      
      //*/		
      int vertOfTrack = track1->vertexIndex();
      
      if (vertOfTrack == highRankVertIndex && highRank > 0)// > 0 To make sure there is at least one usable vertex
      {
        double vertexZ = muDst->primaryVertex(track1->vertexIndex())->position().z();
                
        
        //double dca1 = track1->dca(track1->vertexIndex()).mag();
        bool hitsTrack1 = false;
        
        if ((track1->nHitsFit() >=5 && (double)track1->nHitsFit()/track1->nHitsPoss() >= .5 ) || track1->nHitsFit() >15)
        {
          hitsTrack1 = true;
        }

        
        if (hitsTrack1 && fabs(track1->eta()) < 2 && track1->pt() > 1.5)
        {
          
          StMuBTofHit* bTof = muDst->btofHit(iTrack);
          
          // cout << bTof->trailingEdgeTime() << endl;
          
          // cout << bTof->leadingEdgeTime() << endl;
          
          
          double time = track1->btofPidTraits().timeOfFlight();
          double path = track1->btofPidTraits().pathLength();
          double beta = track1->btofPidTraits().beta();
          double mom  = track1->p().mag();
          double c    = 299792458;
          double nSigPi = track1->nSigmaPion();
          double nSigKa = track1->nSigmaKaon();
          
          
          //double mass2 = mom**2*(time**2*c**2/path**2 - 1);
          double mass2 = mom**2*(1/beta**2 - 1);
          
          //cout << beta**2 << "\t" << mass2 << endl;    
          
          
          //cout << time << path << beta << mom << nSigKa << nSigPi << endl;
         // cout << mass2 << " " << beta << endl;
          
          //*
          if (beta**2 < 100)
          {
            
            
            //2d histos
            
            fillCorrectPbin_2d(hTofNsigPi, mom, nSigPi, mass2);
            fillCorrectPbin_2d(hTofNsigKa, mom, nSigKa, mass2);
            
            
            
            
            //prior
            hNsigPiPrior[0]->Fill(nSigPi);
            hNsigKaPrior[0]->Fill(nSigKa);
            hMass2Prior[0]->Fill(mass2);
            
            //Likelyhood function
            if (nSigPi > 0)
            {
              hMass2_pi[0]->Fill(mass2);
            }
            if (mass2 < 0)
            {
              hNsigPi_pi[0]->Fill(nSigPi);
              hNsigKa_pi[0]->Fill(nSigKa);
            }
            
            if (nSigPi < -3)
            {
              hMass2_ka[0]->Fill(mass2);
            }
            if (mass2 > 0.25 && mass2 < 0.5)
            {
              hNsigPi_ka[0]->Fill(nSigPi);
              hNsigKa_ka[0]->Fill(nSigKa);
            }
            

          }//end beta
          //*/
        }//end track cuts 
      }//end vertex check
    }//end track loop
    
    
  
  }//end while
  
  
  
  chain->Finish();
  
  
  delete chain;
  
  
  /*
  TCanvas* cSig = new TCanvas();
  hNSigPiKa->Draw("colz");
  
  TCanvas* cTof = new TCanvas();
  htofdata->Draw("COLZ");
  
  TCanvas* cMass = new TCanvas();
  hMass2->Draw();
  
  TCanvas* cKa = new TCanvas();
  hNSigKa->Draw();

  TCanvas* cMnSigPi = new TCanvas();
  hMnSigPi->Draw("COLZ");
  */
  
  
  string outname = "findK_" + jobID + ".root";
  TFile* outfile = new TFile(outname.c_str(),"recreate");
  
  if (!outfile)
  {
    cout << "outfile not created" << endl;
  }
  
  
  writeNbins_2d(nPbins, hTofNsigPi);
  writeNbins_2d(nPbins, hTofNsigKa);
  
  
  /*
  TCanvas* cPionLikely = new TCanvas();
  cPionLikely->Divide(2, 2);
  cPionLikely->cd(1);
  hNsigPi_pi[0]->Draw();
  cPionLikely[0]->cd(2);
  hNsigKa_pi[0]->Draw();
  cPionLikely->cd(3);
  hMass2_pi[0]->Draw();
  
  TCanvas* cKaonLikely = new TCanvas();
  cKaonLikely->Divide(2, 2);
  cKaonLikely->cd(1);
  hNsigPi_ka[0]->Draw();
  cKaonLikely[0]->cd(2);
  hNsigKa_ka[0]->Draw();
  cKaonLikely->cd(3);
  hMass2_ka[0]->Draw();
  
  TCanvas* cPrior = new TCanvas();
  cPrior->Divide(2, 2);
  cPrior->cd(1);
  hNsigPiPrior[0]->Draw();
  cPrior[0]->cd(2);
  hNsigKaPrior[0]->Draw();
  cPrior->cd(3);
  hMass2Prior[0]->Draw();
  */
  
  
  cout << "FINISHED " << endl;
}
