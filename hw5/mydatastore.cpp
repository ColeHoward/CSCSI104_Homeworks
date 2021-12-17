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
	set<Review*>::iterator isnt;
	for(isnt = setReview.begin(); isnt != setReview.end(); isnt++){
		delete *isnt;
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
	if(cart.find(yoozer) == cart.end()){
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
		cout << "Invalid request" << endl;
		return;
	}
	(cart[yoozer]).push_back(product);
}

void MyDataStore:: purchase(string yoozer){
	set<User*>::iterator itu;
	string buyer;
	double balance;
	if(cart.find(yoozer) == cart.end()){
		cout << "Invalid username" << endl;
		return;
	}
	for(itu = users.begin(); itu != users.end(); ++itu){
		if((*itu)->getName() == yoozer){
			balance = (*itu)->getBalance();
			break;
		}
	}
	//examine and remove necessary items from cart
	vector<Product*>::iterator itv, itv2; 
	itv2 = cart[yoozer].end();
	vector<Product*> tooExpensive;
	int count = 0;
	for(itv = cart[yoozer].begin(); itv != itv2; ++itv){
		double cost = (*itv)->getPrice();
		balance = (*itu)->getBalance(); 
		if(cost <= balance and (*itv)->getQty() > 0)
		{
			(*itu)->deductAmount(cost);
			(*itv)->subtractQty(1);

			if(cart[yoozer].begin()+count != cart[yoozer].end()){
				cart[yoozer].erase(cart[yoozer].begin()+ count);
			}
		}
		count++;
	}
}
vector<Product*> MyDataStore::search(vector<string>& terms, int type){
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
	set<Product*>::iterator it = products.begin();
	for( ;it != products.end(); ++it){
		(*it)->dump(ofile);
	}
	ofile << "</products>" << "\n" << "<users>" << "\n";
	for(set<User*>::iterator its = users.begin(); its != users.end(); ++its){
		(*its)->dump(ofile);
	}
	ofile << "</users>" << "\n" << "<reviews>" << "\n";
	set<Review*>::const_iterator isnt;
	for(isnt = setReview.begin(); isnt != setReview.end(); ++isnt){
		(*isnt)->dump(ofile);
	}
	ofile << "</reviews>" << "\n";

}
   /**
    * Creates and adds a review with the given information
 */

void MyDataStore::addReview(const std::string& prodName,
                                       int     rating,
                            const std::string& username,
                            const std::string& date,
                            const std::string& review_text){

	//make sure theyre reviewing a product that exists
	bool productExists = false;
	set<Product*>::const_iterator it;
	for(it = products.begin(); it != products.end(); ++it){
		if((*it)->getName() == prodName){
			productExists = true;
		}
	}

	bool userExists = false;
	set<User*>::const_iterator it3;
	for(it3 = users.begin(); it3 != users.end(); ++it3){
		if((*it3)->getName() == username){
			userExists = true;
		}
	}
	if(!productExists || !userExists){
		return;
	}

	Review* rev = new Review(rating, username, date, review_text, prodName);
	reviews[prodName].push_back(rev);
	setReview.insert(rev);
	//update average rating
	//find correct product
	set<Product*>::iterator its;
	for(its = products.begin(); its != products.end(); ++its){
		if((*its)->getName() == prodName){
			(*its)->updateAverageRating((double)rating);
		}
	}

}

std::vector<Review*> MyDataStore:: getReviews(string prodName){
	return reviews[prodName];
}