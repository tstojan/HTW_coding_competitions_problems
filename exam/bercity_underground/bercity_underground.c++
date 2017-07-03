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
#include <unordered_map>
#include <list>
#include <limits.h>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

void dfs_conncomponent(int v, unordered_map<int, vector<int> >  &adj_list, unordered_map<int, bool> &vis)
{
    vis[v] = true;
 	
 	for(int it=0; it<adj_list[v].size(); ++it)
		if(!vis[adj_list[v][it]])
    		dfs_conncomponent(adj_list[v][it], adj_list, vis);	
}

int main()
{
	int N, M, K;
	int a, b, c, res;

	infile>>N; infile>>M; infile>>K;

	vector<unordered_map<int, vector<int> > > adjacencies(K+1);
	vector<unordered_map<int, bool> > visited(K);

	for(int l=0; l<M; ++l)
	{
		infile>>a; infile>>b; infile>>c;

		adjacencies[c-1][a].push_back(b);
		visited[c-1][a] = false;

		adjacencies[c-1][b].push_back(a);
		visited[c-1][b] = false;
	}

	for(int i=0; i<K; ++i)
	{
		res = 0;
	
		for (auto it : visited[i])
		{
			if(!visited[i][it.first])
			{
				dfs_conncomponent(it.first,adjacencies[i],visited[i]);
				res++;
			}
		}

		outfile<<res<<endl;
	}

	return 0;
}