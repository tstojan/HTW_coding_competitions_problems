#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <utility>
#include <random>
#include <functional>
#include <array>
#include <math.h>
#include <iterator>
#include <set>
#include <queue>
#include <list>
#include <limits.h>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	int N,i,j,temp,k,T = 0;
	std::string line;

	infile>>N;
	std::getline (infile, line);

	vector<int> a(N);
	vector<pair<int,int> > operations;

	for(i=0; i<N; ++i)
		infile>>a[i];

	for(k=1; k<N; ++k)
	{
		// selection sort starts here!
		for (j = 0; j<N; j++) 
  		{
    		int iMin = j;
   	
    		for (i = j+1; i < N; i++) {
        	
        		if (a[i] + 1 == a[iMin]) {
            		iMin = i;
            		break;
        		}
    		}

    		if(iMin != j) 
    		{
    			temp = a[j];
    			a[j] = a[iMin];
    			a[iMin] = temp;
    			operations.push_back(pair<int,int>(j+1,iMin+1));
    			++T;
    		}
		}
	}

	outfile<<T<<endl;
    for(i=0; i<T; ++i)
    	outfile<<operations[i].first<<" "<<operations[i].second<<endl;

	return 0;
}