#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

bool punctuation(char letter);
//check if the charactrer is punctuation or not
bool punctuation(char letter){
    string punc =  "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 26; i++){
        if(punc[i] == letter){
            return false;
        }
    }
    return true;
}

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
 to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> words;
    string readWord, palabra;
    stringstream frase(convToLower(rawWords));

    while(frase >> readWord){
        palabra.clear();
        if(readWord.size()<2){
            readWord.clear();
        }
        //keep all words (size>1) w/out punctuation
        unsigned int i = 0;
        while(i < readWord.size()){
            if(punctuation(readWord[i]) and palabra.size() > 1) {
                words.insert(palabra);
                palabra.clear();
            }
            else if(punctuation(readWord[i]) and palabra.size() <= 1){
                palabra.clear();
            }
            else{
                palabra += readWord[i];
            }
            i++;
        }
        if(palabra.size()>1){
            words.insert(palabra);
            palabra.clear();
        }
        palabra.clear();
    }
    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
            std::find_if(s.rbegin(),
                         s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
            s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}



