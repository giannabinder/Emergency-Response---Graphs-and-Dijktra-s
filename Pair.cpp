// include header files
#include "Pair.hpp"

using namespace std;

Pair::Pair() : _vertex(0), _time(-1){ }

void Pair::set_vt(const int vertex, const double time) {
    this-> _vertex = vertex;
    this-> _time = time;
}

const double Pair::get_time() { return this-> _time; }
const int Pair::get_vertex() { return this-> _vertex; }