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

void check_possibility (vector<long long> &arr, long long n, long long M){
    
    long long max = arr[0];
        
    for (long long i = 1; i < n; ++i){

        if(arr[i]<max)
        {
            if(arr[i]+max>M)
            {
                outfile<<"No";
                return;
            }
        }
        else
            max = arr[i];
    }

    outfile<<"Yes";
    return;
}

int main()
{
	long long N,M;
	std::string line;

	infile>>N; infile>>M;
	std::getline (infile, line);

	vector<long long> a(N);

	for(int i=0; i<N; ++i)
		infile>>a[i];

    check_possibility(a,N,M);
	return 0;
}