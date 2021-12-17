#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "product.h"

class Movie: public Product{
public:
    Movie(const std::string category, const std::string name, double price, int qty,
         std::string genre, std::string rating);
    ~Movie();
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const; //outputs all the info on the screen
    bool isMatch(std::vector<std::string>& searchTerms) const;
    
private:
    std::string GENRE;
    std::string RATING;
    
};
#endif
