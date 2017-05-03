#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	/* We first initialized highly composite numbers: http://oeis.org/A002182 . They can be computed with the algorithm of Siano & Siano for instance. */
	int highly_composite_numbers [46] =  {2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,
		166320,221760,277200,332640,498960,554400,665280,720720,1081080,1441440,2162160,2882880,3603600,4324320,6486480,7207200,8648640};


	int K;

	infile>>K;

	int start = 0, end = 45;
	int i;

	if(K>highly_composite_numbers[45])
	{
		outfile << (K-highly_composite_numbers[45]+1);
		return 0;
	}


	while (true)
	{
		i = (start+end)/2;
		if((highly_composite_numbers[i]<=K)&&(highly_composite_numbers[i+1]>K)) break;
		else if(highly_composite_numbers[i]>K)
			end = i;
		else
			start = i;
	}

	outfile << (K-highly_composite_numbers[i]+1);
	return 0;
}