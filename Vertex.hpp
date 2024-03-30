// encircle in define conditionals to ensure it is only run once
#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

// include libraries and header files
#include "Edge.hpp"

class Vertex {
    
  public:
    Vertex();
    ~Vertex();
    void add_adjacent(const int b, const double d, const double s);
    void v_print();
    int pop();
    bool v_traffic(const int b, const double A);
    void v_del(const int a);

    // getters
    const bool get_exists();
    bool get_empty();
    Edge* get_p_head();

    // setters
    void set_exists(const bool status);

  private:
    Edge* _p_head; // address to first child object
    bool _exists;  
};

#endif // end definition