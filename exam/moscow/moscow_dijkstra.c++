/**

*Caution!* Very uneffcient solution using Dijkstra algorithm. See moscow.c++ for an efficient O(N) solution, where N is the number of circular parts. 

It gives TL and probably memory limits for bigger N and M. It is also uncorrect as it assumes the radii of the circular parts and the angles of the 
radial parts are both given in an increasingly sorted order. Hence, for a correct solution (it will be still unefficient) a sorting in both parts and 
keeping the indeces is needed. 

*Details*
It is given as an alternative way of thinking. We form a sparse graph with all the intersections of circular N and M radial segments hence, 
having N*M nodes. All the nodes in this graph are connected with the neighboring at most 2 nodes on the radial segments and at most 2 nodes 
on the circular segments. Hence, each node has at most 4 neighbors, hence the number of links is strictly less than 4*N*M. Then, we do Dijkstra 
for sparse graphs where the start node is ((j_s-1)*N+i_s) and the end node is ((j_t-1)*N+i_t-1), because we use 0-indexing.

**/

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
#include <float.h>


using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

double pi = 3.14159265358979;


double dijkstra_shortest_path(long start, long end, vector<vector<pair<long,double> > > &gr, vector<double> &distance)
{
	for(long i=0; i<gr.size(); ++i)
		distance[i] = DBL_MAX;

	distance[start] = 0.0;

	priority_queue< pair<long, long>, vector<pair<long, long> >, greater<pair<long, long> > > pq; pq.push(pair<double,long>(0.0, start));

	while(!pq.empty())
	{
		pair<double, long> n = pq.top(); pq.pop();

		if(n.second==end)
			return distance[end];

		for(long i=0; i<gr[n.second].size(); ++i)
		{
			pair<long, double> neigh = gr[n.second][i];

			if(distance[n.second] + neigh.second < distance[neigh.first])
			{
				distance[neigh.first] = distance[n.second] + neigh.second;
				pq.push(pair<double,long>(distance[neigh.first], neigh.first));
			}
		}
	}

	return distance[end];
}


int main()
{
	long N, M, rad, dir, A, num_nodes, i_s, j_s, i_t, j_t;
	double dist;

	outfile.precision(17);
	
	std::string line;

	infile>>N; infile>>M;
	num_nodes = N*M;

	vector<long> circular_radius;
	vector<long> circular_direction;
	vector<long > radial;
	vector<vector<pair<long,double> > >  gr(num_nodes);
	vector<double> distance(num_nodes);

	std::getline (infile, line);

	for(long i=0; i<N; ++i)
	{
		infile>>rad; infile>>dir;
		circular_radius.push_back(rad);
		circular_direction.push_back(dir);
	}

	for(long j=0; j<M; ++j)
	{
		infile>>A;
		radial.push_back(A);
	}

	for(long j=0; j<M; ++j)
	{
		for(long i=0; i<N; ++i)
		{
			if(i<N-1)
				gr[j*N+i].push_back(pair<long,double>(j*N+i+1, 1.0*(circular_radius[i+1]-circular_radius[i])));

			if(i>0)
				gr[j*N+i].push_back(pair<long,double>(j*N+i-1, 1.0*(circular_radius[i]-circular_radius[i-1])));

			if(circular_direction[i]>=0)
			{
				if(j<M-1)
					gr[j*N+i].push_back(pair<long,double>((j+1)*N+i, 2.0*pi*circular_radius[i]*((radial[j+1]-radial[j])/360000000.0)));
				else
					gr[j*N+i].push_back(pair<long,double>(i, 2.0*pi*circular_radius[i]*((radial[M-1]-radial[0])/360000000.0)));
			}

			if(circular_direction[i]<=0)
			{
				if(j>0)
					gr[j*N+i].push_back(pair<long,double>((j-1)*N+i, 2.0*pi*circular_radius[i]*((radial[j]-radial[j-1])/360000000.0)));
				else
					gr[j*N+i].push_back(pair<long,double>((M-1)*N+i, 2.0*pi*circular_radius[i]*((radial[M-1]-radial[0])/360000000.0)));
			}
		}
	}

	infile>>i_s; infile>>j_s;
	std::getline (infile, line);
	infile>>i_t; infile>>j_t;

	dist = dijkstra_shortest_path((j_s-1)*N+i_s-1, (j_t-1)*N+i_t-1, gr, distance);
	outfile<<dist;
	return 0;
}
