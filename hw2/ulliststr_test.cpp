

#include "ulliststr.h"
#include <iostream>
#include <string>


using namespace std;

int main(){
    ULListStr linked;

//testing push_back
   // standard test
    linked.push_back("please");
    if(linked.get(0) == "please"){
    cout << "test1 passed" << endl;
    }
    else{
    	cout <<"test1 failed" << endl;
    }
    linked.clear();
    //overload an item
    int count = 0;
    for(int i = 0; i < 11; i++){
    	linked.push_back("please");
    	if(linked.get(i) == "please"){
    		count++;
    	}
    }
    if((unsigned)count == linked.size()){
    	cout << "test2 passed" << endl;
    }
    else{
   		cout << "test2 failed" << endl;
    }
    linked.clear();
//testing push_front
    //standard test
    linked.push_front("thanks");
   	if(linked.get(0) == "thanks"){
   		cout << "test3 passed" << endl;
   	}
   	linked.clear();

   	//no room in front
   	int count1 = 0;
   	for(int i = 0; i < 2; i++){
   		linked.push_front("please");
   		if(linked.get(0) == "please"){
   			count1++;
   		}
   	}
   	
   	if(count1 == 2){
   		cout << "test4 passed" << endl;
   	}
   	else if(count1 != 2){
   		cout << "test4 failed" << endl;
   	}
   	linked.clear();

 //testing pop_front
   	//program will need to create new item
   	linked.pop_front();
   	linked.push_front("works");
   	linked.push_front("test");
   	linked.push_front("this");

   	if(linked.get(0) == "this" and linked.get(1) == "test" 
   		and linked.get(2) == "works"){
   		cout << "test5 passed" << endl;
   	}
   	else{
   		cout << "test5 failed" << endl;
   	}
   	if(linked.front() == "this"){
   		cout << "test6 passed" << endl;
   	}
   
linked.clear();
//test 7
//push front/back will both need to make a new item
	for(int i = 0; i < 21; i++){
		if(i%2 == 0){
			linked.push_back("THERE");
		}
		else{
			linked.push_front("HERE");
		}
	}
	//pop front/back will need to delete an item
	for(int i = 0; i < 21; i++){
		if(i%2 == 0){
			linked.pop_front();
		}
		else{
			linked.pop_back();
		}
	}
	if(linked.size() == 0){
		cout << "test7 passed" << endl;
	}
	else{
		cout << "test7 failed" << endl;
		cout << "size_: " << linked.size() << endl;
	}

	linked.clear();

	//test8
	//remove last value that isn't in the first array
	linked.push_front("pine");
	linked.push_back("back");
	linked.pop_front();
	linked.pop_back();
	if(linked.size() == 0){
		cout << "test9 passed" << endl;
	}
	else{
		cout << " test9 failed" << endl;
	}
/* Write your test code for the ULListStr in this file */
 return 0;
} 