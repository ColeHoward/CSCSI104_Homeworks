#include "mydatastore.h"
#include <string>
#include <sstream> 
#include <set>
#include <vector> 
#include <map>
#include <iostream>
using namespace std;

MyDataStore:: MyDataStore(){

}
MyDataStore:: ~MyDataStore(){
	set<Product*>::iterator it;
	for(it = products.begin(); it!= products.end(); ++it){
		delete *it;
	}
	for(set<User*>::iterator its = users.begin(); its!= users.end(); ++its){
		delete *its;
	}
}

void MyDataStore:: addProduct(Product* product){
	products.insert(product);
}
void MyDataStore:: addUser(User* yoozer){
	users.insert(yoozer);
	//initialize cart
	vector<Product*> initial;
	cart[yoozer->getName()] = initial;
}
void MyDataStore:: viewCart(std::string yoozer){
	int count = 0;
	for(set<User*>::iterator it = users.begin(); it!= users.end(); ++it){
		if((*it)->getName() == yoozer){
			count++;
			break;
		}
	}
	if(count != 1){
		cout << "Invalid username" << endl;
		return;
	}
	vector<Product*> print = cart[yoozer];
	for(int i = 0; i < (int)print.size(); i++){
		cout << "Item " << i+1 << endl;
		cout << print[i]->displayString();
	}
}
void MyDataStore:: addToCart(string yoozer, Product*product){
	if(cart.find(yoozer) == cart.end()){
		cout << "Invalid username" << endl;
		return;
	}
	(cart[yoozer]).push_back(product);
}

void MyDataStore:: purchase(string yoozer){
	set<User*>::iterator itu;
	string buyer;
	double balance;

	for(itu = users.begin(); itu != users.end(); ++itu){
		if((*itu)->getName() == yoozer){
			balance = (*itu)->getBalance();
			break;
		}
	}
	//examine and remove necessary items from cart
	vector<Product*>::iterator itv, itv2; 
	itv2 = cart[yoozer].end();
	for(itv = cart[yoozer].begin(); itv != itv2; ++itv){
		double cost = (*itv)->getPrice();
		balance = (*itu)->getBalance(); 
		if((*itv)->getPrice() < balance and (*itv)->getQty()   > 0)
		{
				(*itu)->deductAmount(cost);
				(*itv)->subtractQty(1);
				cart[yoozer].erase(itv);
		}
	}
}
vector<Product*> MyDataStore:: search(vector<string>& terms, int type){
	vector<Product*> results;
	set<string>  terminologies; 
	//change vector to set
	for(int i= 0 ; i < (int)terms.size(); i++){
		terminologies.insert(terms[i]);
	}
	//AND search
	if(!type){
		set<Product*>::iterator it = products.begin();
		while(it != products.end())
		{
			set<string> productKeys = (*it)->keywords();
			set<string> temp = setIntersection(productKeys, terminologies);
			//if intersection has all search terms, store product
			if(terminologies.size() == temp.size()){
				results.push_back(*it);
			}
			++it;
		}
	}
	//OR search
	else{
		set<Product*>::iterator it = products.begin();
		while(it != products.end())
		{
			set<string> productKeys = (*it)->keywords();
			set<string> temp = setUnion(productKeys, terminologies);
			//will be equal unless keywords hit products
			if(temp.size() != (productKeys.size() + terminologies.size())) {
				results.push_back(*it);
			}
			++it;
		}
	}
	return results;
}
void MyDataStore:: dump(std::ostream& ofile){
	ofile << "<products>" << "\n";
	for(set<Product*>::iterator it = products.begin(); it != products.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</products>" << "\n" << "<users>" << "\n";
	for(set<User*>::iterator its = users.begin(); its != users.end(); ++its){
		(*its)->dump(ofile);
	}
	ofile << "</users>" << "\n";
}
