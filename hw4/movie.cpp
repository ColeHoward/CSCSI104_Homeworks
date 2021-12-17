#include <iostream>
#include <sstream>
#include "movie.h"
#include "util.h"


using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, 
                              int qty, std::string genre, std::string rating): 
    Product(category, name, price, qty),GENRE(genre), RATING(rating)
{
}
Movie::~Movie(){}

set<string> Movie:: keywords() const{
    set<string> genres;
    set<string> title;
    set<string> keys;
    
    genres = parseStringToWords(GENRE);
    title  = parseStringToWords(name_);
    keys   = setUnion(genres, title);
    
    return keys;
}

std::string Movie:: displayString() const{
    string cost, quant;
    stringstream priceToString, qtyToString;

    priceToString << price_;
    qtyToString   << qty_;

    priceToString >> cost;
    qtyToString   >> quant;

    string display = name_ + "\n" + "Genre: " + GENRE + " Rating: "  + RATING
                   + " \n" + cost + "  "      + quant + " left."     + "\n";
    return display;
}

void Movie::dump(std::ostream& os) const{
    os << "movie << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
       << GENRE << "\n" << RATING << endl;
}

bool Movie:: isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}

