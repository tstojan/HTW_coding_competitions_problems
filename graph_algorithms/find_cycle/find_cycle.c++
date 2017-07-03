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

bool dfs_cycle(int v,  list<int> *adj_list, int color[], int parent[], int* last_node)
{
    if(color[v] == 0)
    {
        color[v] = 1;

        for(std::list<int>::const_iterator neighbour = adj_list[v].begin(); neighbour != adj_list[v].end(); ++neighbour)
        {
        	parent[*neighbour] = v;

        	if(color[*neighbour] == 0)
        	{        		    	
        		if (dfs_cycle(*neighbour, adj_list, color, parent, last_node) )
        		{
        			return true;
        		}
        	}
            else if (color[*neighbour]==1)
            {
            	*last_node = *neighbour;
                return true;
            }
        }

    }

    color[v] = 2;
    return false;
}


int main()
{
	int N, M, a, b, i, k, v = 0;
	int last_node;
	std::string line;

	infile>>N; infile>>M;
	std::getline (infile, line);

	list<int> *adj_list = new list<int>[N+1];
	int* color = new int[N+1];
	int* parent = new int[N+1];
	int* path = new int[N+1];

	for(i=1; i<=N; ++i)
	{
		color[i] = 0;
		parent[i] = -1;
	}

	for(i=0; i<M; ++i)
	{
		infile>>a; infile>>b;

		std::getline (infile, line);
		adj_list[a].push_back(b);
	}

	for(i=1; i<=N; ++i)
	{
		if(color[i]==0)
			if(dfs_cycle(i,adj_list,color,parent, &last_node))
			{
				v = 0;
				outfile<<"YES"<<endl;
				k = last_node;				
				path[v] = k;

				while(parent[k] != last_node)
				{
					v++;
					k = parent[k];
					path[v] = k;
				}

				while(v>=0)
				{
					outfile<<path[v]<<" ";
					v--;
				}

				return 0;
			}
	}

	outfile<<"NO";
	return 0;
}