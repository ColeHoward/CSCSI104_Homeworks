#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm> 
#include <functional>
#include <cctype>
#include <locale>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "msort.h"
#include "review.h"

using namespace std;

struct ComparatorViewRev{  
    bool operator()(Review* a, Review* b){
        return a->getDate() > b->getDate();
    }
};
struct ComparatorR{
    bool operator()(Product* a, Product* b){
        double avgA = a->getAverageRating(), 
               avgB = b->getAverageRating();
        return avgA > avgB;
    }
};

struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);
void displayReviews(vector<Review*>& reviews);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;
    ReviewSectionParser* reviewSectionParser = new ReviewSectionParser;
    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);
    parser.addSectionParser("reviews", reviewSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "====================================="             << endl;
    cout << "Menu: "                                            << endl;
    cout << "  LOGIN username                     "             << endl;
    cout << "  LOGOUT                             "             << endl;
    cout << "  AND r/n term term ...              "             << endl;
    cout << "  OR r/n term term ...               "             << endl;
    cout << "  ADD username search_hit_number     "             << endl;
    cout << "  VIEWCART                           "             << endl;
    cout << "  BUYCART                            "             << endl;
    cout << "  ADDREV seach_hit_number rating date review_text" << endl;
    cout << "  VIEWREV search_hit_number          "             << endl;
    cout << "  QUIT new_db_filename               "             << endl;
    cout << "===================================="              << endl;

    vector<Product*> hits;
    bool done = false;
    bool signedIn = false;
    string username;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if(cmd == "LOGIN"){
                username.clear();
                ss >> username;
                signedIn = true;

            }
            else if(cmd == "LOGOUT"){
                signedIn = false;
            }
            else if( cmd == "AND") {
                string term, sortTerm;
                vector<string> terms;

                ss >> sortTerm;

                if(sortTerm != "n" and sortTerm != "r"){
                    continue;
                }

                while(ss >> term){
                    term = convToLower(term);
                    terms.push_back(term);
                }

                hits = ds.search(terms, 0);

                if(sortTerm == "r"){
                    //ComparatorR comp;
                    mergeSort(hits, ComparatorR());
                }
                else{
                    mergeSort(hits, ProdNameSorter());
                }

                displayProducts(hits);
            }
            else if ( cmd == "OR" ){
                string term, sortTerm;
                vector<string> terms;

                ss >> sortTerm;

                if(sortTerm != "n" and sortTerm != "r"){
                    continue;
                }
                while(ss >> term){
                    term = convToLower(term);
                    terms.push_back(term);
                }
                
                hits = ds.search(terms, 1);

                if(sortTerm == "r"){
                    mergeSort(hits, ComparatorR());
                    displayProducts(hits);
                }
                else{
                    ProdNameSorter comp;
                    mergeSort(hits, comp);
                    displayProducts(hits);
                }
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if(cmd == "ADD"){
                string user; 
                int searchNum;
                if(signedIn){
                    user = username;
                    ss >> searchNum;
                    if(searchNum < 1 || searchNum > (int)hits.size()){
                        cout << "Invalid request" << endl;
                        continue;
                    }
                    Product* prod = hits[searchNum-1];
                    ds.addToCart(user, prod);
                }
                else{
                    cout << "No current user" << endl;
                    continue;
                }
            }
            else if (cmd == "BUYCART"){
                string user;
                if(signedIn){
                    user = username;
                    ds.purchase(user);
                }
                else{
                    cout << "No current user" << endl;
                    continue;
                }
            }
            else if(cmd == "VIEWCART"){
                string user;
                if(signedIn){
                    user = username;
                    ds.viewCart(user);
                }
                else{
                    cout << "No current user" << endl;
                    continue;
                }
            }
            else if(cmd == "ADDREV"){
                if(!signedIn){
                    cout << "No current user" << endl;
                    continue;
                }
                unsigned int searchNum = 0;
                unsigned int rating = 0;
                string date, text, checkRatingInt;
                //insert stuff
                //eliminate any unwanted data entries
                ss >> searchNum;
                ss >> rating;
                ss >> date;
                getline(ss, text);
                trim(text);

                stringstream checkInt;
                checkInt << searchNum;
                checkInt >> searchNum;

                stringstream checkRating;
                checkRating << rating;
                checkRating >> rating;

                if(searchNum < 1 or searchNum > hits.size() 
                                 or checkInt.eof() == false){
                                        //or !isdigit(searchNum)){
                    cout << "Invalid hit number" << endl;
                    continue;
                }
                if(rating > 5 || rating < 1 or checkRating.eof() == false){
                    cout << "Invalid rating" << endl;
                    continue;
                }
                if((int)date.size() != 10){
                    cout << "Invalid date" << endl;
                    continue;
                }

                //ensure there are only numbers in the date
                for(int i = 0; i < 10; i++){
                    if( ( (int)date[i] < 48 or (int)date[i] > 57 ) 
                                            and i != 4 and i != 7){
                        cout << "Invalid date" << endl;
                        continue;
                    }
                }

                string Y  = date.substr(0,4), 
                       M  = date.substr(5,2),
                       D  = date.substr(8,2);

                if((int)Y.size() != 4 or(int)M.size() !=2 or(int)D.size() !=2){
                    cout << "Invalid date" << endl;
                    continue;
                }
                //ensure that the date uses dashes
                if(date[4] != '-' or date[7] != '-'){
                    cout << "Invalid date" << endl;
                    continue;
                }
                //ensure month has correct number of days
                stringstream monthToNum, dayToNum;
                int month, day;

                monthToNum << M; 
                dayToNum   << D;

                monthToNum >> month;
                dayToNum   >> day;

                //month between 1 and 12
                if(month < 1 or month > 12){
                    continue;
                }
                //months that must bbe less than 31
                if( (month % 2 != 0 and month != 9 and month != 11) or 
                     month     == 12 or month == 10 or month == 8 ){
                    if(day > 31){
                        continue;
                    }
                }
                //february
                if(month == 2 and day > 28){
                    continue;
                }
                //rest
                if( (month == 11 or month == 9 or month == 6 or month == 4)
                                                             and day > 30){
                    continue;
                }

                //add the review
                Product* prod = hits[searchNum-1];
                ds.addReview(prod->getName(), rating, username, date, text);

            }
            else if(cmd == "VIEWREV"){
                int searchNum;
                ss >> searchNum;
                if(searchNum < 1 || searchNum > (int)hits.size()){
                    continue;
                }
                
                string name = hits[searchNum-1]->getName();
                vector<Review*> revs = ds.getReviews(name);

                mergeSort(revs, ComparatorViewRev());

                displayReviews(revs);
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
void displayReviews(vector<Review*>& reviews){
    vector<Review*>::iterator it;
    for(it = reviews.begin(); it!= reviews.end(); ++it){
        cout << (*it)->date << " " << (*it)->username << " " 
             << (*it)->reviewText << endl;
    }
}
