#ifndef MSORT_H
#define MSORT_H
#include <iostream>
#include <vector>
#include <string> 

//took implementation from lecture slides

template <class T, class Comparator>
  void mergeSort (std::vector<T>& myArray, Comparator comp){

   // std::vector<T> other(myArray);

    sort(myArray, comp, 0, (int)myArray.size()-1); 
  }
template <class T, class Comparator>
  	void sort (std::vector<T>& myList, Comparator comp, int left, int right){
  		//copied from the slides
  		if(left < right){
        int mid = (left+right)/2;
  			sort(myList, comp, left, mid);
  			sort(myList, comp, mid+1, right);
  			merge(myList, comp, mid, left, right);
  		}
  		return;
  	}
 template<class T, class Comparator>
  	void merge (std::vector<T>& myList, Comparator comp, int mid, int left, 
  															                                  int right){
      std::vector<T> sorted(right+1-left, 0);
  		int i = left, j = mid+1, k = 0;
      while(i <= mid or j <= right){
        if(i <= mid and (j > right or comp(myList[i], myList[j]))){
          sorted[k] = myList[i];
          i++;
          k++;
        }
        else{
          sorted[k] = myList[j];
          j++;
          k++;
        }
      }
      for(k = 0; k < right+1-left; k++){
        myList[k+left] = sorted[k];
      }

  	}
#endif

    /*
      std::vector<T> sorted(right+1-left, 0);

      while(L <= mid and M <= right){
        if( comp(myArray[L], myArray[M]) ){
          sorted.emplace_back(myArray[M++]);
        }
        else{
          sorted.emplace_back(myArray[L++]);
        }
      }
      while(L <= mid){
        sorted.emplace_back(myArray[L++]);
      }
      while(R <= right){
        sorted.emplace_back(myArray[M++]);
      }
      myArray = sorted;

*/
/*
      //doubles
      if(right-left == 1){
        for(int j = 0; j < right; j++){
          if(myArray[L] > myArray[L+j]){
            int temp = myArray[L];
            myArray[L] = myArray[L+j];
            myArray[L+j] = temp;
            L += j;
          }
        }
        return;
    L }
      // > doubles
      int j = 0;
      while(M+j < R){
        if(myArray[L] > myArray[M+j]){
          int temp = myArray[R+j];
          myArray[R+j] = myArray[L];
          myArray[L] = temp;
          L++;
          continue;
        }
        j++;
      }


*/