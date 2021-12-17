#include <iostream>
#include <sstream>
#include "util.h"
#include "clothing.h"


using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
                   std::string size, std::string brand): Product(category, name, price, qty), 
                                                                SIZE(size), BRAND(brand)
{
}
Clothing::~Clothing(){}

set<string> Clothing:: keywords() const{
    set<string> branding;
    set<string> nombre;
    set<string> keys;
    
    branding = parseStringToWords(BRAND);
    nombre = parseStringToWords(name_);
    keys = setUnion(branding, nombre);
    
    return keys;
}

std::string Clothing:: displayString() const{
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

    string display = name_      + "\n" + "Size: " + SIZE  + " Brand: " + BRAND
                   + "\n"       + cost + "  "     + quant + " left."   + "\n"       
                   + "rating: " + rating          + "\n";
    return display;
}

void Clothing::dump(std::ostream& os) const{
    os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
       << SIZE << "\n" << BRAND << endl;
}

bool Clothing:: isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}


