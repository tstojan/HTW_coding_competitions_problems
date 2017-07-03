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


/* Dijsktra shortest path for dense graphs using adjacency matrix*/
long long dijkstra_shortest_path_dense(int start, int end, vector<vector<long long> > gr, vector<long long> distance)
{
	int number_nodes = gr.size()-1;

	vector<bool> processed(number_nodes);

	for(int i=1; i<=number_nodes; ++i)
		distance[i] = LLONG_MAX;

	distance[start] = 0;

	for(int v=1; v<=number_nodes; ++v)
	{

		int min_vertex = -1;

		/* First find the minimum in the queue */
		for(int k=1; k<=number_nodes; ++k)
			if(processed[k]) continue;
			else if((min_vertex==-1)||(distance[k]<distance[min_vertex]))
				min_vertex = k;

		if(min_vertex == end) return distance[end];

		/* Now look to relax */
		processed[min_vertex] = true;

		for(int k=1; k<=number_nodes; ++k)
			if((gr[min_vertex][k]!=-1)&&(distance[min_vertex]+gr[min_vertex][k]<distance[k]))
				distance[k] = distance[min_vertex]+gr[min_vertex][k];
	}

	return distance[end];
}


int main()
{
	int N, M, s, d, i, j;
	long long w, dist;
	std::string line;

	infile>>N; infile>>s; infile>>d;
	std::getline (infile, line);
	vector<vector<long long> > gr(N+1, vector<long long>(N+1, LLONG_MAX));
	vector<long long> distance(N+1);

	for(i=1; i<=N; ++i)
	{
		for(j=1; j<=N; ++j)
		{
			infile>>w;
			gr[i][j] = w;
		}

		std::getline (infile, line);
	}


	dist = dijkstra_shortest_path_dense(s, d, gr, distance);
	if(dist==LLONG_MAX) dist = -1;

	outfile<<dist;
	return 0;
}