#include <iostream>
#include <fstream>
using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	long a, b;
	infile >> a >> b;
	outfile << (a+b);
	return 0;
}