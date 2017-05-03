#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	int s, a;

	infile>>a; s = a;
	infile>>a; s += a;
	infile>>a; s += a;

	outfile.precision(17);
	outfile << (double) s/6.0;
	return 0;
}