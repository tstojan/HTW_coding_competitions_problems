#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <limits>

#include <map>
using namespace std;
std::ifstream infile("input.txt");
std::ofstream outfile("output.txt");

std::istream& getline(std::istream &in, std::string &str) {
    char chr;
    std::ios_base::fmtflags flags = in.flags();

    str.clear();

    while ((in >> std::noskipws >> chr) && (chr != '\n') && (chr != '\r')) {
        str += chr;
    }

    in.flags(flags);
    return in;
}

int main()
{

	int W, H;
	char a, last_char;
	std::map<char,int> row, column;
	std::string s, s_min, line;
	long sum, sum_min;
	bool is_begin = true;

	infile>>W; infile>>H;

	for(int i=0; i<H; ++i)
		for(int j=0; j<W; ++j)
		{
			infile>>a;
			row[(char) a] = H-i;
			column[(char) a] = j+1;
		}

	getline( infile, line );
	sum_min = numeric_limits<int>::max();
	while (true) 
	{
		getline( infile, s);
		if(s == "")
			break;

		getline( infile, line );
		
		if(line == "%TEMPLATE-START%")
		{
			is_begin = true;
			sum = 0;
		}
		else
			continue;

		while (true)
		{
			getline( infile, line );
			if(line == "%TEMPLATE-END%") 				
				break;

			line.erase(remove(line.begin(),line.end(),' '),line.end());

			if(line.size()==0)
				continue;
			
			if(!is_begin)
				sum += max(abs(row[line[0]]-row[last_char]),abs(column[line[0]]-column[last_char]));

			is_begin = false;

			for(string::size_type i = 0; i < line.size()-1; ++i)
				sum += max(abs(row[line[i]]-row[line[i+1]]),abs(column[line[i]]-column[line[i+1]]));
			
			last_char = line[line.size()-1]; 				
		}

		if (sum<sum_min)
		{
			sum_min = sum;
			s_min = s;
		}

	}

	outfile<<s_min<<endl<<sum_min;
	
	return 0;
}