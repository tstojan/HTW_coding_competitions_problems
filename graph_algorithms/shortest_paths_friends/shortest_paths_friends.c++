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
#include <list>
#include <limits.h>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

struct Link
{
	int first;
	int second;
	long long weight;
};

void bellman_ford(int start, struct Link* links, long long distance[], int number_nodes, int number_links)
{
	for(int i=1; i<=number_nodes; ++i)
		distance[i] = LLONG_MAX;

	distance[start] = 0;

	for(int i=0; i<2*number_nodes-1; ++i)
	{
		for(int j=0; j<number_links; ++j)
		{
			int fir = links[j].first; 
			int sec = links[j].second;
			long long weight = links[j].weight;

			if ((distance[fir]!=LLONG_MAX))
			{
				if((i<number_nodes-1)&&(distance[fir] + weight<distance[sec]))
					distance[sec] = distance[fir] + weight;
				else // look for negative cycles and nodes reachable from negative cycles [number_nodes.. 2*number_nodes-1 iteration]
				{
					if((distance[fir] + weight<distance[sec])||((weight<0)&&(distance[fir] < LLONG_MIN - weight)))
						distance[sec]=LLONG_MIN;
				}
			}
		}
	}
}


int main()
{
	int N, M, s, a, b, i;
	long long w;
	std::string line;

	infile>>N; infile>>M; infile>>s;
	std::getline (infile, line);

	struct Link* links = (struct Link*) malloc( sizeof( struct Link )*M );

	long long* distance = new long long[N+1];
	bool* has_path = new bool[N+1];

	for(i=0; i<M; ++i)
	{
		infile>>a; infile>>b; infile>>w;
		std::getline (infile, line);
		links[i].first = a; links[i].second = b; links[i].weight = w;
	}

	bellman_ford(s, links, distance, N, M);

	for(i=1; i<=N; ++i)
	{		
		if(distance[i]==LLONG_MIN)
			outfile<<"-"<<endl;
		else if(distance[i]==LLONG_MAX)
			outfile<<"*"<<endl;
		else
			outfile<<distance[i]<<endl;
	}

	return 0;
}