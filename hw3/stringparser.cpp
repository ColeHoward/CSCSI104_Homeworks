#include <iostream> 
#include <string> 
#include <fstream>
#include <sstream>
#include "stackstring.h"
#include <cctype>
using namespace std;

bool checkSyntax(string expression);
int isValidSymbol(char symbol);
int countParentheses(string expression);
void subtract(string& str1, string str2);

void subtract(string& str1, string str2)
{
	int index= str1.find(str2);	
	str1.erase(index, str2.length());
}

bool checkParentheses(string expression){
	int open = 0, close = 0;
	for(int i = 0; i < (int)expression.size(); i++){
		char top = expression[i];
		if((int)top == '('){
			open++;
		}
		else if((int)top == ')'){
			close++;
		}
	}
	if(open == close){
		return true;
	}
	return true;
}

int isValidSymbol(char symbol){
	//if the symbol is a letter
	if(((int)symbol <= 122 && (int)symbol >= 97)){
		return 0;
	}
	//if the symbol is ( or )
	if((int)symbol == 40 || (int)symbol == 41){
		return 1;
	}
	//if the symbol is > or < 
	if((int)symbol == 60 || (int)symbol == 62){
		return 2;
	}
	//if the symbol is + or - 
	if((int)symbol == 45 || (int)symbol == 43){
		return 3;
	}
	//if the symbol isn't valid 
	else{return 4;}
}
int indexOfParenthese(string expression){
	int index = 0; 
	for(int i = 0; i < (int)expression.size(); i++){
		if(expression[i] == '('){
			index = i;
		}
	}
	return index;

}
bool checksyntax(string expression)
{
	int open = 0, close = 0;
	for(size_t i = 0; i < expression.size(); i++){
		//check for whitespace
		char top = expression[(int)i], second = '!';
		if(i != expression.size()-1){
			second = expression[(int)i+1];
		}
		//keep track of number of parentheses
		if((int)top == 40){
			open++;
		}
		if((int)top == 41){
			close++;
		}
		//make sure there's no capitals/ weird characters
		if(isValidSymbol(top) == 4){
			return false;
		}
		//check if there's two operators in a row
		if(isValidSymbol(top) == 3){
			if(isValidSymbol(second) == 3){
				return false;
			}
		}
		if(!checkParentheses(expression)){
			return false;
		}
	}
	if(open != close){
		return false;
	}
//check if the parentheses are in the correct places
	for(size_t i = 0; i < expression.size(); i++){

	}

	return true;

}

int main(int argc, char* argv[]){

if(argc < 3){
        cout << "Incorrect command line arguements" << endl;
        return 1;
    }
    // Complete the rest of main
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    StackString operators; 
    string input;

    if(ifile.fail()){
        ofile << "Error" << endl;
        return 1;
    }
    //get the non-malformed expessions
    StackString evaluate;
    while(getline(ifile, input)){
        if(ifile.fail()){
            ofile << "Error" << endl;
            return 1;
        } 
        stringstream temp(input);
        string noWhiteSpace;
        for(int i = 0; i < (int)input.size(); i++){
        	if(!isspace(input[i])){
        		temp >> noWhiteSpace;
        	}
        }
        StackString operands, operators;
        if(checksyntax(noWhiteSpace) == false || checkParentheses(noWhiteSpace) 
        															== false){
        	ofile << "Malformed" << endl;
        	continue;
        }
        //for this to work, i have to evaluate >< first
        else{
        	string out;
        	//iterate through entire string
     	   for(int i = 0; i < (int)noWhiteSpace.size(); i++){
	     	   	if(noWhiteSpace[i] == ')'){
	     	   		int j = i;
	     	   		//evaluate until I reach an open parentheses
	     	   		while(noWhiteSpace[j] != '('){
	     	   			if((int)noWhiteSpace[j] >= 96 && 
	     	   				(int)noWhiteSpace[j] <= 122)
	     	   			{
	     	   				int iterator = j;
	     	   				string words = "";
	     	   				//gather letters into string
	     	   				while((int)noWhiteSpace[j] >= 96 && 
	     	   					  (int)noWhiteSpace[j] <= 122)
	     	   				{
	     	   					words += noWhiteSpace[iterator];
	     	   					iterator--;
	     	   				} 
	     	   				evaluate.push(words);

	     	   				while(noWhiteSpace[iterator] == '>' || 
	     	   					  noWhiteSpace[iterator] == '<')
	     	   				{
	     	   					if(noWhiteSpace[iterator] == '>'){
	     	   						words.erase(words.begin());
	     	   						evaluate.pop();
	     	   						evaluate.push(words);
	     	   						iterator--;
	     	   					}
	     	   					if(noWhiteSpace[iterator] == '<'){
	     	   						words.erase(words.end());
	     	   						evaluate.pop();
	     	   						evaluate.push(words);
	     	   						iterator--;
	     	   					}
	     	   				}
	     	   				if(noWhiteSpace[iterator] == '+'){
	     	   					string addWords = "";
	     	   					iterator--;
	     	   					while(noWhiteSpace[iterator] == 0){
	     	   						addWords += noWhiteSpace[iterator];
	     	   					}
	     	   					addWords+= words;
	     	   					words = addWords;
	     	   					evaluate.pop();
	     	   					evaluate.push(words);
	     	   				}
	     	   				if(noWhiteSpace[iterator] == '-'){
	     	   					string subtractWords = "";
	     	   					iterator--;
	     	   					while(noWhiteSpace[iterator] == 0){
	     	   						subtractWords += noWhiteSpace[iterator];
	     	   					}
	     	   					subtract(words, subtractWords);
	     	   					evaluate.push(words);
	     	   				}
	     	   			}
	     	   		j++;
	     	   		}
	     	   	}
	     	   	else if(noWhiteSpace[i] == '-' && evaluate.size() > 0){
	     	   		evaluate.push("-");
	     	   	}
				else{
     	   			ofile << "malformed" << endl;
     	   		}
     		}
    	}
    	//check for last subtractions 
    	string keep;
    	for(int i = 0; i < (int)evaluate.size(); i++){
    		if(evaluate.top() == "-"){
    			evaluate.pop();
    			evaluate.pop();
    			string subtraction = evaluate.top();
    			subtract(keep, subtraction);
    			evaluate.push(keep);
    		}
    		keep = evaluate.top();

    	} 
    	//print to file
    	for(int i = 0; i < (int)evaluate.size(); i++){
    		ofile << evaluate.top();
    		evaluate.pop();
    	}
    }
	return 0;
}