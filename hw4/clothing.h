#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "product.h"

class Clothing: public Product{
public:
    Clothing(const std::string category, const std::string name, double price, int qty,
         std::string size, std::string brand);
    ~Clothing();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const; //outputs all the info on the screen
    bool isMatch(std::vector<std::string>& searchTerms) const;
    
private:
    std::string SIZE;
    std::string BRAND;
};
#endif