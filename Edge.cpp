// include libraries and header files
#include "Edge.hpp"

using namespace std;

// define constant member variables
Edge::Edge(const double distance, const double speed, const int vertex, Edge* p_next) : _distance(distance), _speed(speed), _p_next(p_next), _vertex(vertex), _af(1){}

void Edge::set_s_d(const double speed, const double distance) {
    this-> _speed = speed;
    this-> _distance = distance;
}

void Edge::set_af(const double A) { this-> _af = A; }

const double Edge::get_time() {
    if ( !(this-> _af) ) { return -100; }
    return ((this-> _distance) / (this-> _speed * this-> _af));
}

const Edge* Edge::get_next() { return this-> _p_next; }

const int Edge::get_vertex() { return this-> _vertex; }

void Edge::set_next(Edge* p_next) { this-> _p_next = p_next; }