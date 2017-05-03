#include <iostream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{

	int n, k;
	std::vector<int> t;
	long s = 0;

	infile>>n;

	/* Read, sort the vector and start from the beginning until problems can be added up to 300 minutes. */
	for(int i=0; i<n; ++i)
	{
		infile>>k;
		t.push_back(k);
	}

	std::sort (t.begin(),t.begin() + n);

	k = 0;
	while(k<n)
	{

		if(s+t[k]>18000) break;
		else
			s += t[k++];
	}


	outfile << k;
	return 0;
}