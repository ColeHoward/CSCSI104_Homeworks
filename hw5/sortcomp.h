#ifndef SORTCOMP_H
#define SORTCOMP_H


struct Comp2 {
  bool operator()(std::string a, std::string b)
  {
    // Complete the code
    bool ret = a > b;
    return ret;
    
  }
};
struct Comp3 {
  bool operator()(std::string a, std::string b)
  {
    // Complete the code
    bool ret = a > b;
    return ret;
    
  }
};
struct Comp4 {
  bool operator()(std::string a, std::string b)
  {
    // Complete the code
    bool ret = a > b;
    return ret;
  }
};

void outputWords(std::ostream& ostr, const std::vector<std::string>& words)
{
  for(unsigned i = 0; i < words.size()-1; i++){
    ostr << words[i] << ":";
  }
  if(words.size() > 0){
    ostr << words.back();
  }
  ostr << std::endl;
}
#endif