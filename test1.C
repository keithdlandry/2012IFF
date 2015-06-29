/*
 *  test1.C
 *  2012IFF
 *
 *  Created by Keith Landry on 6/9/15.
 *  UCLA
 *
 */



test1(){

  //LOAD LIBS_____________________
  cout << "\n";
  gROOT->Macro("~/ucladisk/2012IFF/StRoot/LoadLibs.C");
  gSystem->Load("dihadronPair");
  cout << " loading of dihadronPair library done" << endl;
  //______________________________
  
  //SET UP INPUT FILE_____________
  
  TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/dihadron/test1/run13044126_2E2C40D667C84515B3FF4C762782E57B_1_dihadronTree_testkpi.root");
  //TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/dihadron/diHadOut_smallPbins_5_19/run13044126_1EB01E12B837F6264339FA96428EA940_0_dihadronTree.root");
  
  
  //SET UP TREE TO RECEIVE INPUT__
  dihadronPair* pair1 = new dihadronPair();
  TTree* pairTree = infile->Get("dihadronPairTree");
  pairTree->SetBranchAddress("dihadronPair", &pair1);
  //______________________________
  
  
  
  for (i=0; i<pairTree->GetEntries(); i++)
  {
    pairTree->GetEntry(i);
    
    cout << pair1->negTrackName() << "  " << pair1->posTrackName() << endl;
    
  }
}