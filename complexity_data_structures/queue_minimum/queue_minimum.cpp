#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <stdexcept> 
#include <stack>          // std::queue
#include <queue>          // std::queue

using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

// Idea taken from here: https://gist.githubusercontent.com/kartikkukreja/5d9b72ce3588afc4ed47474bfe4bbd74/raw/40f41a46ece4c7eb15c917195dff8b480a90d92b/queue-with-min.cpp
template <typename T>
class queue_min {
private:
    stack< pair<T, T> > S1, S2;
public:
    void enqueue(T& x) {
        S2.push(pair<T, T>(x, S2.empty() ? x : min(x, S2.top().second)));
    }

    T dequeue() {
        if (S1.empty()) {
            while (!S2.empty()) {
                pair<T, T> top = S2.top(); S2.pop();
                top.second = S1.empty() ? top.first : min(top.first, S1.top().second);
                S1.push(top);
            }
        }

        if (S1.empty())
            throw "empty queue";
        pair<T, T> top = S1.top(); S1.pop();
        return top.first;
    }

    T get_min() {
        if (empty())
            throw "empty queue";
        return S1.empty() ? S2.top().second : (S2.empty() ? S1.top().second : min(S1.top().second, S2.top().second));
    }

    bool empty() {
        return S1.empty() && S2.empty();
    }

    int size() {
        return S1.size() + S2.size();
    }
};


int main()
{

	int N;
	long el;
	char c;

	queue_min<long> st;

	infile>>N;

	for(int i=0; i<N; i++)
	{
		infile>>c;

		if(c=='+')
		{
			infile>>el;
			st.enqueue(el);
		}
		else if(c=='-')
			st.dequeue();
		else if(c=='?')
		{
			el = st.get_min();
			outfile<<el<<"\n";
		}
	}
	
	return 0;
}