#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef std::map<int, Rectangle> InputMapType;
typedef std::map<int, std::pair<int, int> > OutputMapType;
bool backtrack(InputMapType &input, OutputMapType &output,vector<vector<bool> >
                                             &grid, InputMapType::iterator it);
int isValid(vector<vector<bool> > &grid, int height, int length, int x, int y);

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << p.first << "," << p.second;
    return os;
}



void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}

//input:  map<int, Rectangle> InputMapType;
//output: map<int, std::pair<int, int> > OutputMapType;
//Rectangle: int ID; int length; int height;

// TODO: Write your backtracking search function here

int isValid(vector<vector<bool> > &grid, int height, int length, int x, int y){
    int count = 0;
    if(length+x > n){
        return 0;
    }
    if(height+y > m){
        return 0;
    }
    for(int i = x; i < length+x; i++){
        for(int j = y; j < height+y; j++){
            if(grid[i][j] == false){
                count++;
            }
        }
    }
    if(count == length*height){
        return 1;
    }
    else return 0;

}
// CHANGE GAHIEOAHFAWOIEFHAOI1!!!!!!fJEWAOIFJAWEDIOS'FLJWEAO'SIDLFNKCVODISL/KNVCO'SELD/K.
bool backtrack(InputMapType &input, OutputMapType &output, vector<vector<bool> >
                                             &grid, InputMapType::iterator it){
    if(it == input.end()) return true; //base case
    int i = 0;
    while(i < (int)grid.size()){
        int j = 0;
        while(j < (int)grid[i].size()){
            int height = it->second.height;
            int length = it->second.length;
            InputMapType::iterator itll = it;
            int ID     = it->second.ID;
            switch(isValid(grid, height, length, i, j)){
                case 1:
                    flip(i, j, it->second, grid);
                    itll++;
                    if(backtrack(input, output, grid, itll)){
                        pair<int, int> out;
                        out.first = i;
                        out.second = j;
                        output[ID] = out;
                        return true;
                    }
                    //revert
                    else{
                        flip(i, j, it->second, grid);
                    }
                case 0:
                    //check other orientation
                    int temp = it->second.length;
                    it->second.length = it->second.height;
                    it->second.height = temp;
                    if(isValid(grid, it->second.height, it->second.length, i, j)){
                        flip(i, j, it->second, grid);
                        itll++;
                        if(backtrack(input, output, grid, itll)){
                            pair<int, int> outs;
                            outs.first = i;
                            outs.second = j;
                            output[ID] = outs;
                            return true;
                        }
                        //revert
                        else{
                            flip(i, j, it->second, grid);
                        }
                    }
            }
            j++;
        }
        i++;
    }
    return false;
}




int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here
    solution_exists = backtrack(input, output, grid, it);


    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}