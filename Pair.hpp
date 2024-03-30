// encircle in define conditionals to ensure it is only run once
#ifndef _PAIR_HPP_
#define _PAIR_HPP_

// include libraries and header files
#include <iostream>

using namespace std;

class Pair {
    
  public:
    Pair();
    void set_vt(const int vertex, const double time);
    const double get_time();
    const int get_vertex();

  private:
    int _vertex;
    double _time; 
};

#endif // end definition