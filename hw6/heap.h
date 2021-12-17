#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <sstream>
#include <vector>
/*
TO DO
  - read bytes on this, it tells of diffferent implementations of member signatures

*/

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;
  void printVecSize(std::ostream& stream);
 private:
  /// Add whatever helper functions and data members you need below
  //holds heap 
  std::vector<T> heap;
  void trickleUp(int index);
  void trickleDown(int index);
  PComparator compare;
  int mary;

};

template <typename T, typename PComparator>
void Heap<T, PComparator>::printVecSize(std::ostream& stream){
  for(unsigned int i=0; i< heap.size(); i++){
    stream << heap[i] << " ";
  }
  stream << std::endl;
}

// Add implementation of member functions here

//Constructor
template<typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  if(m < 2) return;
  mary = m;
  compare = c;
}

//Destructor
template <typename T, typename PComparator>
 Heap<T, PComparator>::~Heap(){
  //MAY NEED TO UPDATE AT SOME POINT
 }

//PUSH 
template<typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){

  heap.push_back(item);
  if(heap.size() > 1){
    trickleUp((int)heap.size()-1);
  }
}
//move node up to correct position after pushing
//looked at slides for implementation
template<typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(int index){

  if(index >= (int)heap.size() or index < 1) return;
  int parent = (index-1)/mary;
  int      i = index;
  while(parent >= 0 and compare(heap[i], heap[parent])){
    //swap
    T temp = heap[i];
    heap[i] = heap[parent];
    heap[parent] = temp;
    //update locations
    i = parent;
    parent = (i-1) / mary;
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T, PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap[0];
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
//looked at slides for implementation
template <typename T, typename PComparator>
void Heap<T, PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  heap[0] = heap.back();
  heap.pop_back();
  trickleDown(0);
}

//TRICKLEDOWN... aka Heapify
template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown(int index){

  if(mary*index+1 >= (int)heap.size()){ return;};

  int smallestChild = index*mary +1;
  //find smallest child
  for(int i = index*mary+1; i<= index*mary+ mary; i++){
    if(i >= (int)heap.size()){
      break;
    }
    else if(compare(heap[i], heap[smallestChild])){
      smallestChild = i;
    }
  }
  if(compare(heap[smallestChild], heap[index])){
    T temp = heap[smallestChild];
    heap[smallestChild] = heap[index];
    heap[index] = temp;
    trickleDown(smallestChild);
  }
}
// empty or not
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
    return (int)heap.size() == 0;
}

#endif

