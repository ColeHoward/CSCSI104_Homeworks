#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <cctype>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"

class MyDataStore: public DataStore {
public: 
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* product);
	void addToCart(std::string yoozer, Product*product);
	void addUser(User* yoozer);
	void viewCart(std::string yoozer);
	void purchase(std::string yoozer);
	void dump(std::ostream& ofile);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);

protected:
	std::vector<std::string> keywords;
	std::set<Product*> products;
	std::set<User*> users;
	std::map< std::string, std::vector<Product*> > cart;
};
#endif
