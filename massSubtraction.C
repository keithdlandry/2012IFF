/*
 *  massSubtraction.C
 *  2012IFF
 *
 *  Created by Keith Landry on 5/14/15.
 *  UCLA
 *
 */




void massSubtraction(){



  //TFile* opFile = new TFile("./pairQA/qa_9_9_invMass.root");
  TFile* opFile = new TFile("~/Desktop/Research/2012IFF/rootFiles/qa_9_9_invMass.root");
  
  TH1D* hOpMass = (TH1D*)opFile->Get("invarM");
  
//  double opInt = hOpMass->GetIntegral();
    double opInt = hOpMass->GetEntries();
  
  cout << hOpMass->GetEntries() << "  " << hOpMass->GetIntegral() << endl;
  
  
  //TFile* sameFile = new TFile("./pairQA/sameSign_4_14_InvarMassRad03.root");
  TFile* sameFile = new TFile("~/Desktop/Research/2012IFF/rootFiles/sameSign_4_14_InvarMassRad03.root");

  TH1D* hSameMass = (TH1D*)sameFile->Get("invarM");

//  double sameInt = hSameMass->GetIntegral();
    double sameInt = hSameMass->GetEntries();
  
  cout << hSameMass->GetEntries() << "  " << hSameMass->GetIntegral() << endl;
  
  
  /*
  hOpMass->DrawNormalized();
  hSameMass->DrawNormalized("Same");
  hSameMass->SetLineColor(kRed);
  //*/
  
  
  TH1D* hdiff = new TH1D("hdiff","hdiff",800,0,5);

  //hdiff->Add(hSameMass, hOpMass, -1/sameInt, 1/opInt);
  //hdiff->Add(hSameMass, -1/sameInt);
  hdiff->Add(hOpMass, 1/opInt);
  hdiff->Add(hSameMass, -1/sameInt);

  //hOpMass->Add(hSameMass, -1*opInt/sameInt);
  
  //hOpMass->Draw();
  hdiff->Draw();

  TCanvas* c2 = new TCanvas();
  hOpMass->SetLineColor(1);
  hOpMass->DrawNormalized();
  hSameMass->SetLineColor(2);
  hSameMass->DrawNormalized("same");
  
  


  
  
  
  
  
  
  
  
  
  
  
  

}