// encircle in define conditionals to ensure it is only run once
#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

// include libraries and header files
#include <fstream>
#include <string>
#include "Vertex.hpp"
#include "Pair.hpp"

using namespace std;

class Graph {
    
  public:
    Graph();
    ~Graph();
    bool insert(const int a, const int b, const double d, const double s, const bool load);
    void load(const string& filename);
    void print(const int a);
    void del(const int a);
    bool traffic(const int a, const int b, const double A, const bool valid);
    void update(const string& filename);
    void path(const int start, const int end);
    void lowest(const int start, const int end);

  private:
    const bool _valid(const int a, const int b, const double d, const double s);
    Vertex _array[500001];
    void _dijkstra(const int start, const int end, double distance[], int prev[]);
    int _time;
    int _from;
    int _size; 
};

#endif // end definition