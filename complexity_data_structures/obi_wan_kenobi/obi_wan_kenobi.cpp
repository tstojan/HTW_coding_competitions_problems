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

template<class T>
struct Node
{
  Node *next;
  Node *previous;
  T content;

  Node(T cont)
  {
      content = cont;
      next = previous = NULL;
  }
};

template <typename T>
class double_linked_list
{
  Node<T> *front_ptr;
  Node<T> *back_ptr;
  Node<T> *medium_ptr;

  public:
  int count;

  double_linked_list()
  {  	
  	front_ptr = NULL; 
  	back_ptr = NULL;
  	medium_ptr = NULL;
  	count = 0;
  }

  ~double_linked_list()
  {
  	Node<T> *temp = front_ptr;

    while(temp != NULL)
    {
        Node<T> *temp2 = temp;
        temp = temp->next;
        delete temp2;
    }

    count = 0;
    front_ptr = NULL;
    back_ptr = NULL;
    medium_ptr = NULL;
  }


  void add_back(double val)
  {
  		Node<T> *new_elem = new Node<T>(val);

        if(back_ptr == NULL)
        {
            front_ptr = new_elem;
            back_ptr = new_elem;
            medium_ptr = new_elem;
            count=1;
        }
        else
        {
            back_ptr->next = new_elem;
            new_elem->previous = back_ptr;
            back_ptr = new_elem;
            count++;
            if(count%2==0)
            	medium_ptr = medium_ptr->next;

        }
  }

  void remove_back()
  {
  		Node<T> *tmp;
  		if(count==0)
  			throw "empty list";
        else if(count ==1)
        {
            front_ptr = NULL;
            back_ptr = NULL;
            medium_ptr = NULL;
            count=0;
        }
        else
        {
        	tmp = back_ptr;
        	back_ptr = back_ptr->previous;
            back_ptr->next = NULL;
            delete tmp;
            count--;

            if(count%2==1)
            	medium_ptr = medium_ptr->previous;
        }
  }

  void put_front_back()
  {
  		Node<T> *tmp;

  		if(count>1)
  		{
  			front_ptr->previous = back_ptr;
  			back_ptr->next = front_ptr;
  			tmp = medium_ptr->previous;
  			front_ptr = medium_ptr;
  			if(count%2==1)
  				medium_ptr = back_ptr;
  			else
  				medium_ptr = back_ptr->next;

  			back_ptr = tmp;
  			front_ptr->previous = NULL;
  			back_ptr->next = NULL;
  		}
  }

  void print_list()
  {
  	  Node<T> *tmp = front_ptr;
  	  if(tmp != NULL)
  	  {
  	  	 outfile<<(tmp->content);
         tmp = tmp->next;
  	  }

      while(tmp != NULL)
      {
      	 outfile<<" "<<(tmp->content);
         tmp = tmp->next;
      }
  }
};


int main()
{

	int N, x;
	std::string line;
	double_linked_list<int> dl_list;

	infile>>N;
	std::getline (infile, line);

	for(int i=0; i<N; i++)
	{
		std::getline (infile, line);
		if(line.substr(0,3)=="add")
		{
			x = std::stoi(line.substr(4,line.length()));
			dl_list.add_back(x);
		}
		else if(line=="take")
		{
			dl_list.remove_back();
		}
		else if(line=="mum!")
		{
			dl_list.put_front_back();
		}
	}

	outfile<<dl_list.count<<"\n";
	dl_list.print_list();

	return 0;
}