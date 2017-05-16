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

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

struct elem{
	int v; 
	int w;
	int orig_order;
	double val; 
};

bool comparator(elem a, elem b){ return a.val > b.val;}

bool approach_closer(elem arr[], double picked, int K, int N)
{
  for(int i=0; i<N; ++i)
    arr[i].val = arr[i].v - picked*arr[i].w;

  partial_sort(arr, arr + K, arr + N, comparator);
  
  double s = 0;

  for(int i=0; i<=K-1; ++i)
    s += arr[i].val;

  return (s>=0);
}

void print(elem arr[], int s, int e)
{
	for(int k=s; k<e; k++)
		outfile<<(arr[k].orig_order + 1)<<" ";
}


int main()
{
	int N, K, s = 0;
	double picked;
	std::string line;

	infile>>N; infile>>K;
	std::getline (infile, line);

	elem* arr = new elem[N];

	for(int i=0; i<N; ++i)
	{
		infile>>arr[i].v; s += arr[i].v; infile>>arr[i].w; arr[i].orig_order = i; 
	}

	
    double lower_bound = 0.0, upper_bound = s*1.0;

    while(fabs(upper_bound - lower_bound)>1e-9)//fabs(ub-lb)>eps)
    {

      double picked = (lower_bound + upper_bound)/2;
      (approach_closer(arr, picked, K, N))?(lower_bound = picked):(upper_bound = picked);
    }

    print(arr, 0, K);
	return 0;
}