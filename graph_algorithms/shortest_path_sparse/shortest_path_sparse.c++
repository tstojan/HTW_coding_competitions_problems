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
#include <utility>
#include <limits.h>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");


void dijkstra_shortest_path(int start, vector<vector<pair<int,long> > > gr, vector<long> distance)
{
	for(int i=1; i<gr.size(); ++i)
		distance[i] = LONG_MAX;

	distance[start] = 0;

	priority_queue< pair<long, int>, vector<pair<long, int> >, greater<pair<long, int> > > pq; pq.push(pair<long,int>(0, start));

	while(!pq.empty())
	{
		pair<long, int> n = pq.top(); pq.pop();

		for(int i=0; i<gr[n.second].size(); ++i)
		{
			pair<int, long> neigh = gr[n.second][i];

			if(distance[n.second] + neigh.second < distance[neigh.first])
			{
				distance[neigh.first] = distance[n.second] + neigh.second;
				pq.push(pair<long,int>(distance[neigh.first], neigh.first));
			}
		}
	}

	for(int i=1; i<gr.size()-1; ++i)
		outfile<<distance[i]<<" ";

	outfile<<distance[gr.size()-1];
}


int main()
{
	int N, M, a, b, i;
	long w;
	std::string line;

	infile>>N; infile>>M;

	std::getline (infile, line);
	vector<vector<pair<int,long> > > gr(N+1);
	vector<long> distance(N+1);

	for(i=0; i<M; ++i)
	{
		infile>>a; infile>>b; infile>>w;

		std::getline (infile, line);
		gr[a].push_back(pair<int,long>(b, w));
		gr[b].push_back(pair<int,long>(a, w));
	}

	dijkstra_shortest_path(1, gr, distance);
	return 0;
}