#include "stackstring.h"

    StackString:: StackString(){}
    StackString::~StackString(){
    }

/**
     * Returns true if the stack is empty, false otherwise
     */
    bool StackString:: empty() const{
        return this->list_.empty();
    }

    /**
     * Returns the number of elements on the stack
     */
    size_t StackString:: size() const{
        return this->list_.size();
    }

    /**
     * Pushes a new value, val, onto the top of the stack
     */
    void StackString:: push(const std::string& val){
        this->list_.push_front(val);
    }

    /**
     * Returns the top value on the stack.
     * If the stack is empty, the correct behavior is to throw
     * an exception: use ULListStr::get to achieve this rather
     * than calling ULListStr::back() or ULListStr::front().
     */
    const std::string& StackString:: top() const{
        if(this->list_.size() == 0){
            return NULL; 
        }
        return this->list_.get(0);
    }

    /**
     * Removes the top element on the stack.
     * Should do nothing if the stack is empty.
     */
    void StackString:: pop(){
        this->list_.pop_front();
    }