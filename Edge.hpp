// encircle in define conditionals to ensure it is only run once
#ifndef _EDGE_HPP_
#define _EDGE_HPP_

// include libraries
#include <iostream>
#include <limits>

class Edge {
  public:
    Edge(const double distance, const double speed, const int _vertex, Edge* p_next);
 
    void set_s_d(const double speed, const double distance);
    void set_af(const double A);
    const double get_time();
    const int get_vertex();
    const Edge* get_next();
    void set_next(Edge* p_next);

  private:
    double _distance;
    double _speed;
    double _af;
    const int _vertex;
    Edge* _p_next;
};

#endif // end definition