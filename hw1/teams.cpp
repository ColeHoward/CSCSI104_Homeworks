#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
/*
hw1/hw1.txt
hw1/wsearch.cpp
hw1/teams.cpp
hw1/README.md
*/
// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void swapPlayers(string* team1, string* team2, int spot1, int spot2);
void combinations(string* team1, string* team2, string* players, 
                        int teamSize, int current, int i, int j);
void printSolution(const string* team1,
                   const string* team2,
                   int len)
{
    cout << "\nCombination " << combo++ << endl;
    cout << "T1: ";
    for(int i=0; i < len; i++){
        cout << team1[i] << " ";
    }
    cout << endl;
    cout << "T2: ";
    for(int i=0; i < len; i++){
        cout << team2[i] << " ";
    }
    cout << endl;
}
void combinations(string* team1, string* team2, string* players, 
                    int teamSize, int current, int i, int j){
    //base case when each team is filled
    if(i == teamSize and j == teamSize){
        printSolution(team1, team2, teamSize);
    }
        //fill in teams while not full, increment relevant variables
    if(j < teamSize){
        team2[j] = players[current];
        combinations(team1, team2, players, teamSize, current+1, i, j+1);
    }
    if(i < teamSize){
        team1[i] = players[current];
        combinations(team1, team2, players, teamSize, current+1, i+1, j);
    }
}
int main(int argc, char* argv[])
{
    if(argc < 2){
        cerr << "Please provide a file of names" << endl;
        return 1;
    }
    // Complete the rest of main
    ifstream ifile(argv[1]);
    if(ifile.fail()){
        cout << "Error1" << endl;
        return 1;
    }
    //make sure number is positive
    int num;
    ifile >> num;
    if(num < 0){
        return 1;
    }

    string* team1   = new string[num/2];
    string* team2   = new string[num/2];
    string* players = new string[num];

    //ensure the correct amount of names are present
    //also insert playernames into players
    int i = 0;
    string names;
    while(getline(ifile, names)){
        if(ifile.fail()){
            cout << "Error2" << endl;
            return 1;
        }
        stringstream out(names);
        while(out >> players[i]){
            i++;
        }
    }
    if(i != num){
        cout << "Error3" << endl;
        return 1;
    }
    
    string str;
    int count1    = 0,
        count2    = 0, 
        current   = 0,
        teamSize  = num/2;

    combinations(team1, team2, players, teamSize, current, count1, count2);

    //delete allocated memory
    delete [] team1;
    delete [] team2;
    delete [] players;
    
    return 0;
}
