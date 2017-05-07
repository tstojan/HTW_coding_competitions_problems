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
	bool correct;
	string line;
	stack<char> s;

	infile>>N;
	std::getline (infile, line);
	
	for(int i=0; i<N; i++)
	{
		correct = true;
		std::stack<char>().swap(s);
		std::getline (infile, line);
		
		for(int j=0; j<line.size(); j++)
		{

			c = line[j];

			if((c=='(')||(c=='['))
				s.push(c);
			else if(c==')')
			{
				if((!s.empty())&&(s.top()=='('))
					s.pop();
				else
				{
					correct = false; break;
				}
			}
			else if(c==']')
			{
				if((!s.empty())&&(s.top()=='['))
					s.pop();
				else
				{
					correct = false; break;
				}
			}
		}

		if(correct)
			correct = s.empty();

		outfile<<(correct?"YES":"NO")<<endl;
	}
	
	return 0;
}