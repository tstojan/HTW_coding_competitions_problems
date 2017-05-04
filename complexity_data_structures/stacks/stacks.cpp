#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept> 
#include <queue>          // std::queue
#include <functional> 

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");


int main()
{
	int N, t, elem, min;
	string line;

	infile>>N;
	std::getline (infile, line);
	
	priority_queue<int, std::vector<int>, std::greater<int> > pq;
	
	for(int i=0; i<N; i++)
	{
		infile>>t;

		if((t==0)&&(!pq.empty()))
		{
			elem = pq.top(); pq.pop();
			pq.push(elem+1);
		}
		else
		{
			pq.push(1);
		}
		
	}

	while(pq.size()>1)
		pq.pop();


	outfile<<pq.top();
	return 0;
}