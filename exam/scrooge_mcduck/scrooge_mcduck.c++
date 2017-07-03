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

void dijkstra_shortest_path(int start, vector<vector<pair<int,long long> > > &gr, vector<long long> &distance, int val, bool low_or_expensive)
{
	for(int i=1; i<gr.size(); ++i)
		distance[i] = LLONG_MAX;

	distance[start] = 0;

	priority_queue< pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq; pq.push(pair<long long,int>(0, start));

	while(!pq.empty())
	{
		pair<long long, int> n = pq.top(); pq.pop();

		for(int i=0; i<gr[n.second].size(); ++i)
		{
			pair<int, long long> neigh = gr[n.second][i];

			if(((low_or_expensive)&&(neigh.second<=val))||((!low_or_expensive)&&(neigh.second>=val)))
			{
				if(distance[n.second] + neigh.second < distance[neigh.first])
				{
					distance[neigh.first] = distance[n.second] + neigh.second;
					pq.push(pair<long long,int>(distance[neigh.first], neigh.first));
				}
		    }
		}
	}
}


int main()
{
	int N, M, S, T;
	int a, b, A_cost, B_cost;
	long long c, min_cost = LLONG_MAX;
	std::string line;

	infile>>N; infile>>M;
	std::getline (infile, line);
	infile>>S; infile>>T;
	std::getline (infile, line);

	vector<vector<pair<int,long long> > > gr(N+1);
	vector<long long> distance_cheap(N+1), distance_expensive(N+1);

	for(int l=0; l<M; ++l)
	{
		infile>>a; infile>>b; infile>>c;

		std::getline (infile, line);
		gr[a].push_back(pair<int,long>(b, c));
		gr[b].push_back(pair<int,long>(a, c));	
	}

	infile>>A_cost; infile>>B_cost;

	dijkstra_shortest_path(S,gr,distance_cheap,A_cost,true);
	dijkstra_shortest_path(T,gr,distance_expensive,B_cost,false);

	for(int i=1; i<=N; ++i)
	{
		if((distance_cheap[i]!=LLONG_MAX)&&(distance_expensive[i]!=LLONG_MAX))
		{
			if(distance_cheap[i]+distance_expensive[i]<min_cost)
				min_cost = distance_cheap[i]+distance_expensive[i];
		}
	}

	if(min_cost==LLONG_MAX)
		outfile<<-1;
	else
		outfile<<min_cost;

	return 0;
}