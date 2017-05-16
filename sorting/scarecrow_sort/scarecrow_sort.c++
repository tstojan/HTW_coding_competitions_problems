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

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	long N, K, i;
	long MAX_VAL = 1000000000;
	bool sorted = true;
	std::string line;

	infile>>N; infile>>K;
	std::getline (infile, line);

	if(K==1)
	{
		outfile<<"YES";
		return 0;
	}

	long d = N/K;
    if (N % K != 0) d++;

    vector< vector<long> > arr(K, vector<long> (d));

	for(i=0; i<K; ++i)
		for(long j=0; j<d; ++j)
			arr[i][j] = MAX_VAL;

	for(i=0; i<N; ++i)
		infile>>arr[i%K][i/K];

	for(i=0; i<K; ++i)
		sort(arr[i].begin(),arr[i].end());

	for(long j=0; j<d; ++j)
	{
		for(long i=0; i<K-1; ++i)
			if((arr[i][j]>arr[i+1][j])||((j>0)&&(arr[i][j]<arr[i+1][j-1])))
			{
				sorted = false;
				outfile<<"NO";
				return 0;
			}
	}

	outfile<<"YES";
	return 0;
}