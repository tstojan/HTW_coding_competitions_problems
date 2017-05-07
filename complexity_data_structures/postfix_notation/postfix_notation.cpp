#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept> 
#include <stack>          // std::queue

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

int main()
{
	int N;
	char c;
	long exp, a, b;
	string line;
	stack<long> s;

	infile>>N;
	std::getline (infile, line);
	std::stack<long>().swap(s);
	
	for(int i=0; i<N; i++)
	{
		infile>>c;

		if((c=='+')||(c=='-')||(c=='*'))
		{
			a = s.top(); s.pop();
			b = s.top(); s.pop();

			if(c=='+')
				s.push(a+b);
			else if(c=='-')
				s.push(b-a);
			else if(c=='*')
				s.push(a*b);
		}
		else
			s.push((long) c - 48);			
	}

	exp = s.top();
	outfile<<exp;
	
	return 0;
}