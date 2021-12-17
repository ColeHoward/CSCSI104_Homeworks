#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <iostream>

// NOTE: You may add any data members or functions you deem useful

struct Review
{
    Review() :  rating(0), username(), date(), reviewText(), productName()
    { }
    Review(int rate,
           const std::string& u,
           const std::string& d,
           const std::string& review_text, 
           const std::string& ProdName) :

        rating(rate),
        username(u),
        date(d),
        reviewText(review_text),
        productName(ProdName)
    { }
/*
    std::string getUsername();
    std::string getDate();
    std::string getReview();
*/
    std::string getDate() const{
        return date;
    }

    void dump(std::ostream& os) const{
        os << productName << "\n" <<   rating   <<    " "     << username
           <<     " "     << date <<    " "     << reviewText <<   "\n";
    };
    std::string displayString() const{
        if(rating < 0 || rating > 5 || date.size() != 10 || reviewText.size() < 1){
            return "";
        }

        std::string display = rating + " " + username + " " + date + " " + reviewText;
        return display;
    };
    int rating;
    std::string username;
    std::string date;
    std::string reviewText;
    std::string productName;
};

#endif

