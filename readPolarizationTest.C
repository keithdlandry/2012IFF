/*
 *  readPolarizationTest.C
 *  2012IFF
 *
 *  Created by Keith Landry on 1/14/14.
 *  UCLA
 *
 */

#include <fstream>
#include <map>

void readPolarizationTest(){


	ifstream polFile;
	
	polFile.open("/Users/keithlandry/Documents/BeamPolarization2012.txt");
	
	string header;
	
	for (int i=0; i<19; i++)
	{
		polFile >> header;
		
		//cout << header << endl;
	}
	
	
	map<int, double> polarizationOfFill_Y;
	map<int, double> polErrOfFill_Y;
	
	map<int, double> polarizationOfFill_B;
	map<int, double> polErrOfFill_B;

	
	
	int    fill;
	string beamE;
	string startT;
	string plusminus;
	
	double pAvrgBlue;
	double pErrAvrgBlue;
	
	string pInitialBlue;
	string pErrInitialBlue;
	string dPdTBlue;
	string dPdTErrBlue;
	
	double pAvrgYellow;
	double pErrAvrgYellow;
	
	string pInitialYellow;
	string pErrInitialYellow;
	string dPdTYellow;
	string dPdTErrYellow;
	
	
	while (!polFile.eof())
	{
		
		polFile >> fill;
		polFile >> beamE;
		polFile >> startT;
		
		polFile >> pAvrgBlue;
		polFile >> plusminus;
		polFile >> pErrAvrgBlue;
		
		polFile >> pInitialBlue;
		polFile >> plusminus;
		polFile >> pErrInitialBlue;
		
		polFile >> dPdTBlue;
		polFile >> plusminus;
		polFile >> dPdTErrBlue;
		
		polFile >> pAvrgYellow;
		polFile >> plusminus;
		polFile >> pErrAvrgYellow;
		
		polFile >> pInitialYellow;
		polFile >> plusminus;
		polFile >> pErrInitialYellow;
		
		polFile >> dPdTYellow;
		polFile >> plusminus;
		polFile >> dPdTErrYellow;
		
		cout << fill << "  " << pAvrgBlue << "  " << pErrAvrgBlue << "  " << pAvrgYellow << "  " << pErrAvrgYellow << endl;

		
		polarizationOfFill_B[fill] = pAvrgBlue/100.;
		polErrOfFill_B[fill] = pErrAvrgBlue/100.;
		
		polarizationOfFill_Y[fill] = pAvrgYellow/100.;
		polErrOfFill_Y[fill] = pErrAvrgYellow/100.;
		
		
		
	}
	
	
	
	cout << polarizationOfFill_B[16632] << "  " << polErrOfFill_B[16632] << "    " << polarizationOfFill_Y[16632] << "  " << polErrOfFill_Y[16632] << endl;	
	


}