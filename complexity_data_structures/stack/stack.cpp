#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept>  

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

template <class T>
class Stack
{
private:
	vector<T> elements;
public:
void push(T const&);
T pop();
T top() const;
bool is_empty() const;	
};

template <class T>
void Stack<T>::push (T const& el)
{
	elements.push_back(el);
}

template <class T>
T Stack<T>::top() const
{
	if(is_empty())
		throw std::out_of_range("The stack is empty!");

	return elements.back();
}

template <class T>
T Stack<T>::pop()
{
	
	T k = top();
	elements.pop_back();
	return k;
}

template <class T>
bool Stack<T>::is_empty() const
{
	
	return elements.empty();
}


int main()
{

	int N;
	long el;
	char c;

	Stack<long> st;

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
			el = st.pop();
			outfile<<el<<"\n";
		}
	}
	
	return 0;
}