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

struct Edge {
    long long to;
    long long index;
    long long label;
};
 
void DFS(vector<vector<Edge> > &edges, vector<bool> &used_links, long long v, vector<long long> &visited, long long &mark)
{
    if(visited[v]!=2)
    {
        visited[v] = 1;
        
        for(long long i=0; i<edges[v].size(); ++i)
        {
            if(!used_links[edges[v][i].index])
            {
                edges[v][i].label=mark++;
                used_links[edges[v][i].index] = true;

                if (visited[edges[v][i].to] != 1)
                    DFS(edges, used_links, edges[v][i].to, visited, mark);
            }
        }

        visited[v] = 2;
    }

    return;
}

void solve(vector<vector<Edge> > &edges, vector<bool> &used_links, vector<long long> &visited, long long &mark, long long N, long long M, long long start_vertex)
{
    vector<long long> links(M);

    DFS(edges, used_links, start_vertex, visited, mark);

    for (long long i = 1; i <= N; i++)
        if(visited[i] != 2)
            DFS(edges, used_links, i, visited, mark);

    for(long long v=1; v<=N; ++v)
    {
        for(long long i=0; i<edges[v].size(); ++i)
            if(edges[v][i].label>0)
                links[edges[v][i].index] = edges[v][i].label;
    }

    for(long long i=0; i<M; ++i)
         outfile<<links[i]<<endl;
}
 
int main()
{
    long long N, a, b, i, k, v = 0;
    long long M;
    long long mark = 1;
    long long start_vertex = 1;
    vector<long long> deg1_nodes;
    std::string line;

    infile>>N; infile>>M;
    std::getline (infile, line);

    vector<vector<Edge> > edges(N+1);
    vector<long long> count_degree(N+1);
    vector<bool> used_links(M, false);
    vector<long long> visited(N+1,0);

    for(long long i=0; i<M; ++i)
    {
        infile>>a; infile>>b;
        Edge newEdge, newEdge1;
        newEdge.to = b; newEdge.index = i; newEdge.label = 0;
        newEdge1.to = a; newEdge1.index = i; newEdge1.label = 0;

        count_degree[a]++; count_degree[b]++;

        std::getline (infile, line);
        edges[a].push_back(newEdge);
        edges[b].push_back(newEdge1);
    }

    for(long long i=1; i<=N; ++i)
    {
        if(count_degree[i]==1)
        {
            deg1_nodes.push_back(i);
        }
    }

    if(deg1_nodes.size()>2)
    {
        outfile<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    else if(deg1_nodes.size()==2)
    {
        if(edges[deg1_nodes[0]][0].to != deg1_nodes[1])
        {
            outfile<<"IMPOSSIBLE"<<endl;
            return 0;
        }
        else
        {
            edges[deg1_nodes[0]][0].label=mark++;
            used_links[edges[deg1_nodes[0]][0].index] = true;
            visited[deg1_nodes[0]] = 2; visited[deg1_nodes[1]] = 2;
        }
    }
    else if(deg1_nodes.size()==1)
    {
        edges[deg1_nodes[0]][0].label=mark++;
        used_links[edges[deg1_nodes[0]][0].index] = true;
        visited[deg1_nodes[0]] = 2; visited[edges[deg1_nodes[0]][0].to] = 1;
        start_vertex = edges[deg1_nodes[0]][0].to;
    }

    solve(edges, used_links, visited, mark, N, M, start_vertex);   
    return 0;
}