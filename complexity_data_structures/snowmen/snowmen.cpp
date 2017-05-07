#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept> 
#include <stack>          // std::queue

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

template <typename T>
struct stack_infos {
    T rest;
    T sum;
    stack_infos *before;
};


int main()
{
	long N, t;
	long c;
	string line;
	long long total_mass = 0;

	infile>>N;
	std::getline (infile, line);
	vector<stack_infos<long> > snowmen(N+1);

	snowmen[0].sum = 0;
	snowmen[0].rest = 0;
	snowmen[0].before = NULL;
	
	for(int i=0; i<N; i++)
	{
		infile>>t;


		infile>>c;

		if(c==0)
		{
			snowmen[i+1].rest = (snowmen[t].before)->rest;
			snowmen[i+1].sum = snowmen[t].rest;
			snowmen[i+1].before = (snowmen[t].before)->before;
		}
		else
		{
			snowmen[i+1].rest = snowmen[t].sum;
			snowmen[i+1].sum = snowmen[t].sum + c;
			snowmen[i+1].before = & snowmen[t];
		}
	}

	for(int i=0; i<=N; i++)
		total_mass += snowmen[i].sum;

	outfile<<total_mass;
	return 0;
}