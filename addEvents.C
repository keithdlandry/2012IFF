/*
 *  addEvents.C
 *  2012IFF
 *
 *  Created by Keith Landry on 2/7/14.
 *  UCLA
 *
 */

#include <map>
#include <algorithm> // std::sort
void addEvents(){

	
	
	ifstream infile;
	infile.open("/star/u/klandry/ucladisk/2012IFF/schedOutCountFull2/test.txt");
	
	ofstream outfile;
	outfile.open("/star/u/klandry/ucladisk/2012IFF/schedOutCountFull/eventsAllOrder.txt");
	
	int run;
	int events;
	
	int totEvents=0;
	//*
	map <int,int> nEventsInRun;
	
	
	vector <int> runList;
	
	
	
	while (!infile.eof())
	{
		infile >> run;
		infile >> events;
		
		
		
		if (runList.size() == 0)
		{
			runList.push_back(run);
		}
		else if (runList.back() != run)
		{
			runList.push_back(run);
		}
		
		
		nEventsInRun[run] += events;

		totEvents += events;
		
	}
	
	
	
	
	
	for (map<int,int>::iterator iter = nEventsInRun.begin(); iter != nEventsInRun.end() ; iter++)
	{
		cout << iter->first << " => " << iter->second << endl;

	}
	
		
  cout << "total events " << totEvents << endl;

}