#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "product.h"

class Book: public Product {
public:
    Book(const std::string category, const std::string name, double price, int qty,
         std::string author, std::string isbn);
    virtual ~Book();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const; //outputs all the info on the screen
    std::string getAuthor();
    std::string getIsbn();
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;
    double getAverage();
    
private:
    std::string AUTHOR;
    std::string ISBN;
    
};

#endif
