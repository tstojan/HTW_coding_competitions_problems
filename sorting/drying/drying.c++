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


bool which_half(int arr[], int mid, int k, int N) {

        int total_water = mid;

        if (k == 1) return (arr[N-1] <= mid);

        for (int i = N-1; i >= 0; --i) {
            
            int elem = arr[i];
			if (elem <= mid) return true;

            int portion_at_once = (elem - mid) / (k - 1);

            if ((elem - mid) % (k - 1) != 0) portion_at_once++;
            
            if (total_water >= portion_at_once) total_water -= portion_at_once;
            else return false;
        }

        return true;
}


bool desc(int i, int j) { return i > j; }

int main()
{
	int N, i;
	int mid, start = 0, end = 1000000000;
	int k;
	std::string line;

	infile>>N;

	int* ar = new int[N];

	for(i=0; i<N; ++i)
		infile>>ar[i];

	sort(ar, ar + N);

	std::getline (infile, line);
	infile>>k;

	// look for binary search
    while (start <= end) 
    {
        mid = (start + end)/2;

        if (which_half(ar, mid, k, N)) end = mid - 1; 
        else start = mid + 1;
    }

	outfile<<start;
	return 0;
}