#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	long m,n,p;
	int a[3][3];

	for(int i = 0; i<3; ++i)
		for(int j = 0; j<3; ++j)
			infile>>a[i][j];

	m = a[0][0]*a[0][0] + max(a[1][1]*a[1][1] + a[2][2]*a[2][2], a[1][2]*a[1][2] + a[2][1]*a[2][1]);
	n = a[0][1]*a[0][1] + max(a[1][0]*a[1][0] + a[2][2]*a[2][2], a[2][0]*a[2][0] + a[1][2]*a[1][2]);
	p = a[0][2]*a[0][2] + max(a[1][0]*a[1][0] + a[2][1]*a[2][1], a[1][1]*a[1][1] + a[2][0]*a[2][0]);

	outfile.precision(17);
	outfile << sqrt((long double) max(m,max(n,p)));
	return 0;
}