#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <utility>
#include <random>
#include <functional>
#include <array>

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");


void quick_sort_range(int a[], int left, int right, int l, int u)
{
	int m = left + (right-left)/2;// left + (rand() + rand())% ((right-left+1)/2);
    int key = a[m];
    int i = left;
    int j = right;
    int buf;

    while (i <= j)
    {
        while (a[i] < key)
        {
            i++;
        }
        while (key < a[j])
        {
        	j--;
        }

        if (i <= j)
        {
            buf = a[i];
            a[i] = a[j];
            a[j] = buf;
            i++;
            j--;
        }
    }

    if ((left < j)&&(l<=j))
    { 
    	if(u>j)
    		quick_sort_range(a, left, j, l, j);
    	else
    		quick_sort_range(a, left, j, l, u);
    }

    if ((i < right)&&(i<=u))
    {
    	if(l<i)
    		quick_sort_range(a, i, right, i, u);
    	else
    		quick_sort_range(a, i, right, l, u);
    }
}


int main()
{
	int N;
	int k1, k2;
	int A, B, C;//, first, second;
	//bool all_equal;
	infile>>N; infile>>k1; infile>>k2;

	int* ar = new int[N];

	infile>>A; infile>>B; infile>>C; 
	infile>>ar[0]; infile>>ar[1];

	for(int i=2; i<N; i++)
	{
		ar[i] = B*ar[i-1] + A*ar[i-2] + C;
	}

	quick_sort_range(ar, 0, N-1, k1-1, k2-1);

	for(int i=k1-1; i<k2-1; i++)
		outfile<<ar[i]<<" ";

	outfile<<ar[k2-1];

	return 0;
}