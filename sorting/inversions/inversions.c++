#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept> 
#include <queue>          // std::queue

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

template<typename T >
void merge(T a[], T copy[], long s, long e, long m, long long& inv)
{
	for(long k=s; k<e; k++)
		copy[k] = a[k];

	long i = s;
	long j = m;

	for(long k=s; k<e; k++)
		if(i>=m) a[k] = copy[j++];
		else if (j>=e) a[k] = copy[i++];
		else if (copy[j]<copy[i]){ a[k] = copy[j++]; inv = inv + (m-i);}
		else a[k] = copy[i++];
}

template<typename T>
void merge_sort(T a[], long s, long e, long long& inv)
{
	if(s+1==e)
		return;

	T copy[e];
	 
	 long m = (s+e)/2;
	 merge_sort(a, s, m, inv);	 
	 merge_sort(a, m, e, inv);

	 merge(a, copy, s, e, m, inv);
}


int main()
{
	long N;
	long long inv;

	inv = 0;

	std::string line;

	infile>>N;
	long a[N];

	std::getline (infile, line);

	for(long i=0; i<N; i++)
		infile>>a[i];

	merge_sort(a, 0, N, inv);
	outfile<<(inv);

	return 0;
}