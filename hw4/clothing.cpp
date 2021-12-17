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
    string cost, quant;
    stringstream priceToString, qtyToString;
    priceToString << price_;
    qtyToString << qty_;
    priceToString >> cost;
    qtyToString >> quant;

    string display = name_ + "\n" + "Size: " + SIZE
                   + " Brand: " + BRAND+" \n" + cost + "  " + quant 
                   + " left." + "\n";
    return display;
}

void Clothing::dump(std::ostream& os) const{
    os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" 
       << SIZE << "\n" << BRAND << endl;
}

bool Clothing:: isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}


