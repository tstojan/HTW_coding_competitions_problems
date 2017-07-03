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


int main() {
    int W, H, N, i_t, j_t, x0, y0, x1, y1;
    string line;

    infile>>W; W++; infile>>H; H++; infile>>N;
    std::getline (infile, line);

    vector<vector<vector<int> > > prev_x_coord (N+1,vector<vector<int> >(W+1,vector <int>(H+1)));
    vector<vector<vector<int> > > prev_y_coord (N+1,vector<vector<int> >(W+1,vector <int>(H+1)));
    vector<int> final_x(N+1);
    vector<int> final_y(N+1);

    for(int i=1; i<W; ++i)
        for(int j=1; j<H; ++j)
        {
            prev_x_coord[0][i][j] = 1;
            prev_y_coord[0][i][j] = 1;
        }


    for(int step=1; step<=N; ++step)
    {
        for(int i=1; i<W; ++i)
            for(int j=1; j<H; ++j)
            {
                prev_x_coord[step][i][j] = -1;
                prev_y_coord[step][i][j] = -1;
            }

        for(int i=1; i<W; ++i)
            for(int j=1; j<H; ++j)
                if(prev_x_coord[step-1][i][j] != -1)
                {
                    prev_x_coord[step][i+1][j] = i;
                    prev_x_coord[step][i-1][j] = i;
                    prev_x_coord[step][i][j-1] = i;
                    prev_x_coord[step][i][j+1] = i;

                    prev_y_coord[step][i+1][j] = j;
                    prev_y_coord[step][i-1][j] = j;
                    prev_y_coord[step][i][j-1] = j;
                    prev_y_coord[step][i][j+1] = j;
                }

        infile>>x0; infile>>y0; infile>>x1; infile>>y1;
        std::getline (infile, line);

        for(int i=x0; i<=x1; ++i)
            for(int j=y0; j<=y1; ++j)
            {
                prev_x_coord[step][i][j] = -1;
                prev_y_coord[step][i][j] = -1;  
            }
    }


    i_t = j_t = -1;

    for(int i=1; i<W; ++i)
        for(int j=1; j<H; ++j)
            if((prev_x_coord[N][i][j] != -1)&&(prev_y_coord[N][i][j] != -1))
            {
                i_t = i;
                j_t = j;
                break;
            }

    if((i_t==-1)&&(j_t==-1))
    {
        outfile<<"Impossible";
    }
    else
    {
        for (int step = N; step > 0; --step) {
            final_x[N-step] = i_t;
            final_y[N-step] = j_t;
            int temp = i_t;
            i_t = prev_x_coord[step][i_t][j_t];
            j_t = prev_y_coord[step][temp][j_t];
        }

        for (int step = N-1; step >= 0; --step)
            outfile<<final_x[step]<<" "<<final_y[step]<<endl;
    }

    return 0;
}