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

    string display = name_ + "\n" + "Genre: " + GENRE + " Rating: "  + RATING
                   + " \n" + cost + "  "      + quant + " left."     + "\n"
                   + "rating:"    + " "       + rating               + "\n";
    return display;
}

void Movie::dump(std::ostream& os) const{
    os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
       << GENRE << "\n" << RATING << endl;
}

bool Movie:: isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}

