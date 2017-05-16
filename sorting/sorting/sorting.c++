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
void merge(T a[], T copy[], int s, int e, int m)
{
	for(int k=s; k<e; k++)
		copy[k] = a[k];

	int i = s;
	int j = m;

	for(int k=s; k<e; k++)
		if(i>=m) a[k] = copy[j++];
		else if (j>=e) a[k] = copy[i++];
		else if (copy[j]<copy[i]) a[k] = copy[j++];
		else a[k] = copy[i++];
}

template<typename T>
void merge_sort(T a[], int s, int e)
{
	if(s+1==e)
		return;

	T copy[e];
	 
	 int m = (s+e)/2;
	 merge_sort(a, s, m);	 
	 merge_sort(a, m, e);

	 merge(a, copy, s, e, m);

	 outfile<<(s+1)<<" "<<e<<" "<<a[s]<<" "<<a[e-1]<<"\n";
}

template<typename T >
void print(T a[], int s, int e)
{
	for(int k=s; k<e-1; k++)
		outfile<<a[k]<<" ";

	outfile<<a[e-1];
}


int main()
{

	int N;
	std::string line;

	infile>>N;
	long a[N];

	std::getline (infile, line);

	for(int i=0; i<N; i++)
		infile>>a[i];

	merge_sort(a, 0, N);
	print(a, 0, N);
	
	return 0;
}