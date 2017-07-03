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


const int MAXN = 25;
int g[MAXN];
int g_reverse[MAXN];
int dp[1<<(MAXN-1)];
int dp_reverse[1<<(MAXN-1)];
int N;
int lim;
int processed[MAXN];
bool paths_existing = false;

void dyn_prog_hamilton(int *dp, int *g) {

  dp[0] = 1;
  for (int mask = 0; mask < lim; ++mask)
  {
    for (int v = 1; v < N; ++v)
    {
      int bit = 1 << (v - 1);
      if ((mask & bit) == 0)
        continue;

      int prev = mask ^ bit;
      if ((g[v] & dp[prev]) != 0)
        dp[mask] |= 1 << v;
    }
  }
}

vector<int> find_path(int v, int mask, int* dp, int* g) {

  vector<int> path_vec;

  while (mask > 0) 
  {
    path_vec.push_back(v);
    mask = mask ^ (1<<(v-1));
    for(int u = 1; u<N; ++u)
    {
      if (g[v] & dp[mask] & (1 << u)) {
        v = u;
        break;
      }
    }
  }

  return path_vec;
}

void print_path(const vector<int>& start, const vector<int>& end) {

  paths_existing = true;
  vector<int> res;

  res.insert(res.end(), start.begin(), start.end());
  res.push_back(0);
  res.insert(res.end(), end.rbegin(), end.rend());

  outfile<<(res[0] + 1);
  for(int i = 1; i<res.size(); ++i)
        outfile<<" -> "<<(res[i] + 1);

  outfile<<endl;
}

int main() {

  std::string line;
  infile>>N;
  std::getline (infile, line);

  for(int i = 0; i<N; ++i){
    std::getline (infile, line);
    for(int j = 0; j<N; ++j)
        if(line[j] == '1')
        {
            g[j] |= (1<<i);
            g_reverse[i] |= (1<<j);
        }
  }

  lim = 1<<(N-1);
  dyn_prog_hamilton(dp, g);
  dyn_prog_hamilton(dp_reverse, g_reverse);

  int full = lim-1;

  for(int mask = 0; mask<lim; ++mask)
  {
    int other = full ^ mask;
    int starts = dp_reverse[mask], ends = dp[other];

    for(int u = 0; u<N; ++u)
    {
      if ((starts & (1<<u)) && (~processed[u] & ends)) 
      {  
        vector<int> start = find_path(u, mask, dp_reverse, g_reverse);

        for(int v = 0; v<N; ++v)
        {
          if (~processed[u] & (1<<v) & ends) 
          {
            vector<int> end = find_path(v, other, dp, g);
            processed[u] |= (1<<v);
            print_path(start, end);
          }
        }
      }
    }
  }

  if (!paths_existing)
    outfile<<"No paths";

  return 0;
}