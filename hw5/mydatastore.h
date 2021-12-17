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
#include "review.h"

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
	   /**
    * Creates and adds a review with the given information
    */
    void addReview(const std::string& prodName,
                          	  int rating,
                              const std::string& username,
                              const std::string& date,
                              const std::string& review_text);
    std::vector<Review*> getReviews(std::string prodName);

protected:
	std::vector<std::string> keywords;
	std::set<Product*> products;
	std::set<User*> users;
	std::map< std::string, std::vector<Product*> > cart;
//product name key review vector value
	std::map< std::string, std::vector<Review*> > reviews;
	std::set<Review*> setReview;
};
#endif
