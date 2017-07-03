#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <utility>
#include <random>
#include <functional>
#include <array>
#include <math.h>
#include <iterator>
#include <set>
#include <queue>
#include <list>
#include <limits.h>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");


int solve(vector<vector<long> > &table, vector<vector<long> > &max_chain_val, int current_x, int current_y, int N, int M, int &current_max_chain)
{
	if(max_chain_val[current_x][current_y] > 0) return max_chain_val[current_x][current_y];
	int x, y, k, max_chain = 1;

	// right
	x = current_x+1; y = current_y;

	if((x < N) && (table[x][y] == table[current_x][current_y]-1))
	{
		k = solve(table,max_chain_val,x,y,N,M,current_max_chain);
		if(k+1>max_chain) max_chain = k+1;
	}

	// left
	x = current_x-1; y = current_y;

	if((x > -1) && (table[x][y] == table[current_x][current_y]-1))
	{
		k = solve(table,max_chain_val,x,y,N,M,current_max_chain);
		if(k+1>max_chain) max_chain = k+1;
	}

	// up
	x = current_x; y = current_y + 1;

	if((y < M) && (table[x][y] == table[current_x][current_y]-1))
	{
		k = solve(table,max_chain_val,x,y,N,M,current_max_chain);
		if(k+1>max_chain) max_chain = k+1;
	}

	// down
	x = current_x; y = current_y - 1;

	if((y > -1) && (table[x][y] == table[current_x][current_y]-1))
	{
		k = solve(table,max_chain_val,x,y,N,M,current_max_chain);
		if(k+1>max_chain) max_chain = k+1;
	}

	
	max_chain_val[current_x][current_y] = max_chain;
	if(max_chain>current_max_chain) current_max_chain = max_chain;
	
	return max_chain;
}

int main()
{
	int N, M, current_max_chain = 1;
	
	std::string line;

	infile>>N; infile>>M;
	std::getline (infile, line);

	vector<vector<long> > a(N, vector<long> (M));
	vector<vector<long> > max_chain_val(N, vector<long> (M));

	for(int i=0; i<N; ++i)
		for(int j=0; j<M; ++j)
		{
			infile>>a[i][j];
			max_chain_val[i][j] = 0;
		}

	for(int i=0; i<N; ++i)
		for(int j=0; j<M; ++j)
			if(max_chain_val[i][j]==0)
				solve(a,max_chain_val,i,j,N,M,current_max_chain);

	outfile<<current_max_chain;
	return 0;
}