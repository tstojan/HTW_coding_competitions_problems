#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	int n, k, s, min_dif, max_dif, diff;
	int a[100];

	infile>>n;
	for(int i = 0; i<n; ++i)
		infile>>a[i];

	s = 0;
	min_dif = numeric_limits<int>::max();
	max_dif = numeric_limits<int>::min();

	for(int i=0; i<n; ++i)
	{
		infile>>k;
		s += max(k,a[i]);
		diff = a[i]-k;

		if(diff>max_dif)
			max_dif = diff;

		if(diff<min_dif)
			min_dif = diff;
	}

	if(max_dif*min_dif>0)
		s -= min(abs(max_dif),abs(min_dif));

	outfile << s;
	return 0;
}