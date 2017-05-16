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

void print(vector<int> &a, int s, int e)
{
	for(int k=s; k<e; k++)
		outfile<<a[k]<<" ";

	outfile<<a[e];
}


int main()
{
	int N, i, temp;

	infile>>N;

	vector<int> a(N+1);

	for(i=0; i<N; ++i)
		a[i] = i+1;

	for(i=2; i<N; ++i)
	{
		temp = a[i/2];
		a[i/2] = a[i];
		a[i] = temp;
	}
	
	print(a, 0, N-1);
	return 0;
}