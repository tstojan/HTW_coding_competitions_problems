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

int main()
{
	long N, M, rad, dir, A, i_s, j_s, i_t, j_t;
	double dist, current_dist, angle_factor;
	vector<long> circular_radius;
	vector<long> circular_direction;
	vector<long> radial;
	std::string line;
	
	outfile.precision(17);

	infile>>N; infile>>M;

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

	infile>>i_s; infile>>j_s;
	std::getline (infile, line);
	infile>>i_t; infile>>j_t;

	dist = DBL_MAX;

	if(j_s==j_t)
	{
		dist = abs(circular_radius[i_s-1]-circular_radius[i_t-1]);
	}
	else
	{
		angle_factor = abs(radial[j_s-1]-radial[j_t-1])/180000000.0;

		for(long i=0; i<N; ++i)
		{
			if(circular_direction[i]>=0)
			{
				if(radial[j_s-1]<=radial[j_t-1])
				{
					current_dist = abs(circular_radius[i_s-1]-circular_radius[i]) + abs(circular_radius[i_t-1]-circular_radius[i]) 
								+ pi*circular_radius[i]*angle_factor;

					if(current_dist<dist)
						dist = current_dist;
				}
				else
				{
					current_dist = abs(circular_radius[i_s-1]-circular_radius[i]) + abs(circular_radius[i_t-1]-circular_radius[i]) 
								+ pi*circular_radius[i]*(2.0 - angle_factor);

					if(current_dist<dist)
						dist = current_dist;
				}
			}
		
			if(circular_direction[i]<=0)
			{

				if(radial[j_s-1]>=radial[j_t-1])
				{
					current_dist = abs(circular_radius[i_s-1]-circular_radius[i]) + abs(circular_radius[i_t-1]-circular_radius[i]) 
								+ pi*circular_radius[i]*angle_factor;

					if(current_dist<dist)
						dist = current_dist;
				}
				else
				{
					current_dist = abs(circular_radius[i_s-1]-circular_radius[i]) + abs(circular_radius[i_t-1]-circular_radius[i]) 
								+ pi*circular_radius[i]*(2.0 - angle_factor);

					if(current_dist<dist)
						dist = current_dist;
				}
			}
		}
	}

	outfile<<dist;
	return 0;
}
