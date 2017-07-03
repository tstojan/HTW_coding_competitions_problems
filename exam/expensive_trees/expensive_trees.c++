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
 
int main()
{
    unsigned long long N, res;

    infile>>N;
    
    if(N%2==0)
        res = (N/2)*(N/2);
    else
        res = ((N-1)/2)*((N+1)/2);

    outfile<<res;
    return 0;
}