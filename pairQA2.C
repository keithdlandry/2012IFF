/*
 *  pairQA2.C
 *  2012IFF
 *
 *  Created by Keith Landry on 7/17/14.
 *  UCLA
 *
 */



void pairQA2(){


	//LOAD LIBS_____________________
	cout << "\n";
	gROOT->Macro("StRoot/LoadLibs.C");
	gSystem->Load("pionPair");
	cout << " loading of pionPair library done" << endl;
	//______________________________
	
	
	//SET UP INPUT FILE_____________
	//TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_Full_4_2/allPairs_4_2.root");
	
	TFile* infile = new TFile("/star/u/klandry/ucladisk/2012IFF/schedOut_5_19_5Hits/allPairs_5_19.root");
	
	
	
	
  //______________________________
	
	
	//SET UP TREE TO RECEIVE INPUT__
	pionPair* pair1 = new pionPair();
	TTree* pairTree = infile->Get("pionPairTree");
	pairTree->SetBranchAddress("pionPair", &pair1);
	//______________________________
	
	

	pairTree->GetEntry(0);

	
	
	cout << pair1->piPlusLV().X() << "   " << pair1->piMinusLV().X() <<endl;

	cout << pair1->theta() << endl;

	cout << pair1->piPlusLV().X() << "   " << pair1->piMinusLV().X() <<endl;
	
	cout << pair1->theta() << endl;


}