// encircle in define conditionals to ensure it is only run once
#ifndef _MINHEAP_HPP_
#define _MINHEAP_HPP_

// include libraries and header files
#include <iostream>
#include <cmath>
#include "Pair.hpp"

using namespace std;

class MinHeap {
    
  public:
    MinHeap(const int size);
    ~MinHeap();
    void extract_min(int& vertex, double& time);
    void enqueue(const int vertex, const double time);
    const bool get_populated();

  private:
    Pair* _heap;
    int _size;
    void _min_heapify(const int i);
};

#endif // end definition