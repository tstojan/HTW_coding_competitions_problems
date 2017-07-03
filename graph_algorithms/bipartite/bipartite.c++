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

bool dfs_bipartite(int v,  list<int> *adj_list, int visited[], int color[], int current_col)
{
    visited[v] = 1;
    color[v] = current_col;
    //cout<<"node: "<<v<<"; color: "<<color[v]<<endl;

    for(std::list<int>::const_iterator neighbour = adj_list[v].begin(); neighbour != adj_list[v].end(); ++neighbour)
    {
    	//cout<<"node: "<<v<<"; neighbor: "<<(*neighbour)<<endl;
    	if(visited[*neighbour] == 0)
        {
        	visited[*neighbour]=1;
        	color[*neighbour] = current_col;

        	if (!dfs_bipartite(*neighbour, adj_list, visited, color, 1 - current_col)) return false;
        }
    	else if (visited[*neighbour]==1)
        {
        	if(color[*neighbour]==color[v]) return false;
        }
        
        
        
     }

    visited[v] = 2;
    return true;
}


int main()
{
	int N, M, a, b, i, k, v = 0;
	int last_node;
	int current_color = 0;
	std::string line;

	infile>>N; infile>>M;
	std::getline (infile, line);

	list<int> *adj_list = new list<int>[N+1];
	int* visited = new int[N+1];
	int* color = new int[N+1];

	for(i=1; i<=N; ++i)
	{
		visited[i] = 0;
		color[i] = 2;
	}

	for(i=0; i<M; ++i)
	{
		infile>>a; infile>>b;
		std::getline (infile, line);
		adj_list[a].push_back(b);
		adj_list[b].push_back(a);
	}

	for(i=1; i<=N; ++i)
	{
		if(visited[i]==0)
		{
			current_color = 0;

			if (!dfs_bipartite(i,adj_list,visited,color,current_color))
			{
				outfile<<"NO";
				return 0;
			}
		}
	}

	outfile<<"YES";
	return 0;
}