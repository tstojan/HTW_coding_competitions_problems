#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept> 
#include <queue>          // std::queue

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");


int main()
{

	int N;
	long el;
	char c;

	queue<long> st;

	infile>>N;

	for(int i=0; i<N; i++)
	{
		infile>>c;

		if(c=='+')
		{
			infile>>el;
			st.push(el);
		}
		else if(c=='-')
		{
			el = st.front();
			st.pop();
			outfile<<el<<"\n";
		}
	}
	
	return 0;
}