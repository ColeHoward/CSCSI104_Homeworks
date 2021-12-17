/*
 CSCI 104: Homework 2 Problem 6
 
 Write a recursive function to split a sorted singly-linked
 list into two sorted linked lists, where one has the even
 numbers and the other contains the odd numbers. Students
 will receive no credit for non-recursive solutions.
 To test your program write a separate .cpp file and #include
 split.h.  **Do NOT add main() to this file**.  When you submit
 the function below should be the only one in this file.
 */

#include <iostream>
#include "split.h"
#include <iostream>
using namespace std;

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
    if(in == NULL){ 
        odds = NULL;
        evens = NULL;
        return;
    }
    else{
        //cout <<"right here" << endl;
        if(in->value % 2 != 0){
            //pass a shallow copy to odd
            Node* node = in;
            odds = node;
            in = in->next;
            split(in, odds->next, evens);
        }
        else if(in->value % 2 == 0){
            //pass a shallow copy to even
            Node* node = in;
            evens = node;
            in = in->next;
            split(in, odds, evens->next);
        }
    }
}




