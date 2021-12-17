#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <string>
#include <iostream>
using namespace std;

ULListStr::ULListStr()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

ULListStr::~ULListStr()
{
    clear();
}

bool ULListStr::empty() const
{
    return size_ == 0;
}

size_t ULListStr::size() const
{
    return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
    std::string* ptr = getValAtLoc(loc);
    if(NULL == ptr){
        throw std::invalid_argument("Bad location");
    }
    *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
    std::string* ptr = getValAtLoc(loc);
    if(NULL == ptr){
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
    std::string* ptr = getValAtLoc(loc);
    if(NULL == ptr){
        throw std::invalid_argument("Bad location");
    }
    return *ptr;
}

void ULListStr::clear()
{
    while(head_ != NULL){
        Item *temp = head_->next;
        delete head_;
        head_ = temp;
    }
    tail_ = NULL;
    size_ = 0;
}
// adds new value back of the list
//does this mean add a value to the back of the list or the 
void ULListStr::push_back(const std::string& val){
    
    //if the list is empty
    if(tail_ == NULL and head_ == NULL){
        Item* item = new Item;
        tail_ = item;
        head_ = item;
        item->next = NULL;
        item->prev = NULL;
        item->first = 0;
        item->last = 1;
        item->val[0] += val;
        size_++;
    }
    //if the list is full
    else if(tail_->last == ARRSIZE){
        Item* item = new Item;
        tail_->next = item;
        item->prev = tail_;
        item->next = NULL;
        tail_ = item;
        item->first = 0;
        item->last = 1;
        item->val[0] += val;
        size_++;
    }
    
    //if the list is neither full nor empty
    else{ 
        tail_->val[tail_->last] += val;
        tail_->last++;
        size_++;
    }
}
void ULListStr:: pop_back(){
    
    //if there's no items elements in list
    if(tail_ == NULL and head_ == NULL){
        return;
    }
    else if (size_ == 1){
        delete tail_;
        tail_ = NULL;
        head_ = NULL;
        size_--;
    }
    //if there's one element in the array
    else if((tail_->last-tail_->first)-1 == 0){
        tail_ = tail_->prev;
        delete tail_->next;
        tail_->next = NULL;
        size_--;
    }
    //standard case
    else{
        tail_->val[(tail_->last)-1] = "";
        tail_->last--;
        size_--;
    }
    
    
}
/**
 * Adds a new value to the front of the list.
 * If there is room before the 'first' value in
 * the head node add it there, otherwise,
 * allocate a new head node.
 *   - MUST RUN in O(1)
 */
void ULListStr:: push_front(const std::string& val){
    //if there's no items in the list
    if(head_ == NULL and tail_ == NULL){
        Item* item = new Item;
        item->next = NULL;
        item->prev = NULL;
        head_ = tail_ = item;
        item->val[0] += val;
        item->first = 0;
        item->last = 1;
        size_++;
    }
     //if there's no room in front
    else if(head_->first == 0){
        Item* item = new Item;
        head_->prev = item;
        item->next = head_;
        item->prev = NULL;
        head_ = item;
        item->val[9] += val;
        item->first = 9;
        item->last = 10;
        size_++;
    }
    //if there's room in the front
    else if(head_->first > 0){
        head_->val[(head_->first)-1] += val;
        head_->first--;
        size_++;
    }
    
}
/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front(){
    //if there's no items in list
    if(head_ == NULL and tail_ == NULL){
        return;
    }
    //if there's one item in the list
    else if(size_ == 1){
        delete head_;
        head_ = NULL;
        tail_ = NULL;
        size_--;
    }
    else if((head_->last - head_->first) -1 == 0){
        head_ = head_->next;
        delete head_->prev;
        head_->prev = NULL;
        size_--;
    }
    //standard case
    else{
        head_->val[head_->first] = "";
        head_->first++;
        size_--;
    }
}
/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
 std::string const & ULListStr:: back() const{
         return tail_->val[(tail_->last)-1];
}
/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr:: front() const{
        return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
    //if the location is out of range
    int diff = (int)(head_->last - head_->first);
    if(loc > size_ || loc < 0){
        return NULL;
    }
    //if the location is w/in the first item
    else if((int)loc < diff){
        return &(head_->val[(int)loc+(head_->first)]);
    }
    //standard case
    else{
        Item* item = head_;
        //cout << "3" << endl;
        int count = (int)loc;
        count -= diff;
        count /= 10;
        count++;
        for(int i = 0; i < count; i++){
                item = item->next;
        }
        int x = ((int)loc-diff)%10;
 //       cout << "last one is: " << item->val[x] << endl;
 //       cout << "while x is: " << x << endl;

        return &item->val[x];
    }
    //cout << "6" << endl;
   // return NULL;
}
 /**
   * Copy constructor (initializes list with deep copy of `other`)
   *
   * You don't have to replicate the way the elements of other are arranged inside
   * the Item structs, as long as the actual elements are added to this list
   * in the same order.
   *
   * MUST RUN in O(n) where n is the size of other
   */
ULListStr:: ULListStr(const ULListStr& other){
    tail_ = NULL;
    head_ = NULL;
    size_ = 0;
  for(size_t i=0; i< other.size(); i++){
    this->push_back(other.get(i));
  }
}
  /**
   * Assignment Operator (replace current contents with a deep copy of `other`)
   * 
   * Note: It is fine to delete and recreate this list's internal structure,
   * or you can keep the same Item structs and just change their contents.
   * 
   *  MUST RUN in O(n+m) where n is the size of this list and m the size
   *   of `other` and not O(n^2) or O(m^2)
   */
 ULListStr& ULListStr:: operator= (const ULListStr& other){
    this->clear();
    this->tail_ = other.tail_;
    this->head_ = other.head_;
    this->size_ = other.size_;
    return *this;
  }
  /**
   * Concatenation operator.
   * Returns a separate list consisting of other appended to this.
   * Does not modify this nor other.
   *
   * As before, you may implement this internally however you like, as
   * long as the new list ends up with the correct elements.
   *
   *  MUST RUN in O(n+m) where n is the size of this list and m the size
   *   of `other`
   */
  ULListStr ULListStr:: operator+ (const ULListStr& other) const{
    ULListStr empty;
    size_t num = 0; 
    if(this->size() == num && other.size() == num){
        return empty;
    }
    else if(this->size() == num && other.size() > num){
        empty.appendContents(other);
        return empty;
    }
    else if(this->size() > num && other.size() == num){
        return *this;
    }
    else{
        empty.appendContents(*this);
        empty.appendContents(other);
        return empty;
    }
  }

/**
   * Remove the last 'num' strings from the **back** of this list
   * 
   * Returns a reference to this list.
   *
   *  MUST RUN in O(num)
   */
ULListStr& ULListStr::operator-= (size_t num){
    for(int i = 0; i < (int)num; i++){
        this->pop_back();
    }
    return *this;
  }
  /**
   * Const access Operator of element at location/position: loc
   */
  std::string const & ULListStr:: operator[] (size_t loc) const{
    return this->get(loc);
  }
  /**
   * Non-const access Operator of element at location/position: loc
   */
  std::string & ULListStr:: operator[] (size_t loc){
    return this->get(loc);
  }

    /*
   * Appends the contents of `other` to the end of `this` list
   * allocating new Items and updating pointers and first/last
   * indices of `this` as necessary.
   *
   * Does not modify `other`.
   *
   * Runs in O(m) where m is the size of `other`
   */

 void ULListStr:: appendContents(const ULListStr& other){
    Item* andd = other.head_;
    size_t some = andd->first;
    if(other.size() == 1){
        this->push_back(other.get(some));
    }
    else if(other.size() == 0){
        this->clear();
    }
    else{
    while(andd != NULL){
        if(some == andd->last){
            andd = andd->next;
        }
        else{
            this->push_back(other.get(some));
            some++;
        }
    }
    this->size_ = other.size_;
}
}



