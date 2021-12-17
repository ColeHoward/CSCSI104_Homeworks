#include <iostream>
#include <sstream>
#include "book.h"
#include "util.h"


using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
           string author, string isbn): Product(category, name, price, qty),
                                        AUTHOR(author), ISBN(isbn)
{
}
Book::~Book(){}

set<string> Book:: keywords() const{
    set<string> writer;
    set<string> title;
    set<string> keys;
    
    writer = parseStringToWords(AUTHOR);
    title  = parseStringToWords(name_);
    keys   = setUnion(title, writer);

    keys.insert(ISBN);
    
    return keys;
}

string Book:: displayString() const{
    string cost, quant, rating;
    stringstream priceToString, qtyToString, ratingToString;

    priceToString.precision(2); 
    qtyToString.precision(2);
    ratingToString.precision(2);

    priceToString  << fixed << price_;
    qtyToString    << fixed << qty_;
    ratingToString << fixed << getAverageRating();

    priceToString  >> cost;
    qtyToString    >> quant;
    ratingToString >> rating;

//print
    string display = name_    + "\n" + "Author: " + AUTHOR     + " ISBN: " 
                   + ISBN     + "\n" + cost       + "  "       + quant 
                   + " left." + "\n"              + "rating: " + rating
                   + "\n"; 
    return display;
}

void Book::dump(std::ostream& os) const{
    os << "book" << "\n" << name_ << "\n" << price_ << "\n" 
       << qty_   << "\n" << ISBN   << "\n" << AUTHOR << endl;
}

string Book:: getAuthor(){
    return AUTHOR;
}
string Book:: getIsbn(){
    return ISBN;
}
bool Book:: isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}
