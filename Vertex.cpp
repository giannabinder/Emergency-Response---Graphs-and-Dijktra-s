// include libraries and header files
#include "Vertex.hpp"

using namespace std;

// define constant member variables
Vertex::Vertex() : _p_head(nullptr), _exists(false) {}

Vertex::~Vertex() {
    Edge *p_temp = this-> _p_head;

    // go through the list and delete all nodes
    while (p_temp) {
        _p_head = const_cast<Edge*>(this-> _p_head-> get_next());
        delete p_temp;
        p_temp = _p_head;
    }

    // set pointers to null to avoid dangling pointers
    _p_head = nullptr;
    p_temp = nullptr;
}

void Vertex::add_adjacent(const int b, const double d, const double s) {

    // if the list is empty, make this child the head of the list
    // initialize their pointer to null as there are no other children
    if ( _p_head == nullptr) { _p_head = new Edge(d, s, b, nullptr); }

    else {
        Edge* p_traverse = this-> _p_head;

        // check if the edge already exists
        while (p_traverse) {
            if (p_traverse-> get_vertex() == b) { 
                p_traverse-> set_s_d(s, d);  
                return;
            }

            // check the next node
            p_traverse = const_cast<Edge*>(p_traverse-> get_next());
        }

        // if the list is populated, push them to the front of the list
        Edge *p_new_edge = new Edge(d, s, b, _p_head);
        _p_head = p_new_edge;

        // set pointers to null to avoid dangling pointers
        p_new_edge = nullptr;
    }
}

void Vertex::v_print() {

    Edge* p_traverse = this-> _p_head;

    //traverse through list and print the adjacent vertices
    while (p_traverse) {
        cout << p_traverse-> get_vertex() << " ";

        // go to the next node
        p_traverse = const_cast<Edge*>(p_traverse-> get_next());
    }

    cout << endl;
}

bool Vertex::v_traffic(const int b, const double A) {

    Edge* p_traverse = this-> _p_head;

    // look for the edge
    while (p_traverse) {
        if (p_traverse-> get_vertex() == b) { 
            p_traverse-> set_af(A); // update the traffic 
            return true;
        }

        // check the next node
        p_traverse = const_cast<Edge*>(p_traverse-> get_next());
    }

    return false;
}

// deletes the edge at the front of the list and returns the vertex it led to
int Vertex::pop() {
    Edge* p_temp = this-> _p_head;
    _p_head = const_cast<Edge*>(this-> _p_head-> get_next()); // move the head to point to the next node
    int adjacent_vertex = p_temp-> get_vertex(); // get the adjacent vertex 
    delete p_temp; // delete the node
    p_temp = nullptr;
    return adjacent_vertex;
}

// deletes the specified edge
void Vertex::v_del(const int a) {

    Edge* p_traverse = this-> _p_head;
    Edge* p_trail = this-> _p_head;

    // go through the list to find the adjacent vertex
    while(p_traverse) {

        // if we've found the edge, delete it
        if (p_traverse-> get_vertex() == a) {
            
            // if we are deleting the head
            if (p_traverse == this-> _p_head) {
                this-> _p_head = const_cast<Edge*>(this-> _p_head-> get_next()); // move the head to the next node
                delete p_traverse; // delete the edge
                return;
            }

            else {
                p_trail-> set_next( const_cast<Edge*>(p_traverse-> get_next()) ); // have the previous node point to the node after the one to be deleted
                delete p_traverse; // delete the edge
                return;
            }
        }

        p_traverse = const_cast<Edge*>(p_traverse -> get_next()); // go to the next node
    }
}

bool Vertex::get_empty() {
    if ( this-> _p_head ) { return true; }
    else { return false; }
}

const bool Vertex::get_exists() { return ( this-> _exists); }
Edge* Vertex::get_p_head() { return this-> _p_head; }

void Vertex::set_exists(const bool status) {  this-> _exists = status; }