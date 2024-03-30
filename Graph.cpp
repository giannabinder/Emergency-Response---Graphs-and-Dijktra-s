// include header files
#include "Graph.hpp"
#include "MinHeap.hpp"
#include "illegal_exception.hpp"

using namespace std;

Graph::Graph() : _size(0) {}

// delete all dynamically allocated memory by calling the destructor of each object associated with the array
Graph::~Graph() {}

const bool Graph::_valid(const int a, const int b, const double d, const double s) {
    
    try {
        if ( (a <= 0) || (a > 500000) || (b <= 0) || (b > 500000) || (s <= 0) || (d <= 0)) { throw illegal_exception(); }
        else { return true; }
    } 
    
    catch (illegal_exception& exception) {
        cout << exception.invalid_bound();
        return false;
    }
}


// CITATION: use of fstream to parse external text files inspired by Mike's video "parsing_input_files" 
bool Graph::insert(const int a, const int b, const double d, const double s, const bool load) {

    // if an illegal argument is not thrown, add both vertices to each other's adjacency list and the edge information as well
    if (_valid(a, b, d, s) || load) {

        // ensure the vertices exists
        if (!(this-> _array[a].get_exists()) ) { 
            this-> _array[a].set_exists(true); 
            this-> _size++;
        }
        if (!(this-> _array[b].get_exists()) ) { 
            this-> _array[b].set_exists(true); 
            this-> _size++;
        }

        this-> _array[a].add_adjacent(b, d, s);
        this-> _array[b].add_adjacent(a, d, s);
        
        if (!load) { cout << "success\n"; }
        return true;
    }

    return false;
}

void Graph::load(const string& filename) {

    fstream fin(filename.c_str()); // open and prepare the file to be read

    int a, b;
    double d, s;

    // call insert for each command
    while (fin >> a && fin >> b && fin >> d && fin >> s ) { insert(a, b, d, s, true); }

    fin.close(); // Close the file

    cout << "success\n";
}

bool Graph::traffic(const int a, const int b, const double A, const bool valid) {

    // validate the vertices and ensure they exist, and validate A
    if ((valid || _valid(a, b, 1, 1)) && A >= 0 && A <= 1) {
        if ( (this-> _array[a].get_exists()) && (this-> _array[b].get_exists()) ) {

            // check if the adjustment factor is valid
            if ((A < 0) || (A > 1)) { return false; }

            // update the adjustment factors found in both adjacency lists
            this-> _array[a].v_traffic(b, A);
            this-> _array[b].v_traffic(a, A);

            if (!valid) { cout << "success\n"; }
            return true;
        }

        if (!valid) { cout << "failure\n"; }
    }

    return false;
}

// CITATION: use of fstream to parse external text files inspired by Mike's video "parsing_input_files" 
void Graph::update(const string& filename) {

    fstream fin(filename.c_str()); // open and prepare the file to be read

    int a, b;
    double A;
    bool updated = false;

    // call insert for each command, and update the status of "updated" if needed
    while ( fin >> a && fin >> b && fin >> A ) { if ( traffic(a, b, A, true) && !updated) { updated = true; }; }

    fin.close(); // Close the file

    if ( updated ) { cout << "success\n"; }
    else { cout << "failure\n"; }
}

void Graph::del(const int a) {

    // validate the vertex
    if (_valid(a, 1, 1, 1)) {

        // check if the vertex has adjacent vertices and it exists in the graph
        if ((this-> _array[a].get_empty()) && (this-> _array[a].get_exists()) ) {
        
            // go through the adjacency list and delete the edges in the adjacent vertices lists
            while ( (this-> _array[a].get_empty()) ) { this-> _array[this-> _array[a].pop()].v_del(a); }

            this-> _array[a].set_exists(false);
            this-> _size--;
            cout << "success\n";
        }

        else { 
            cout << "failure\n"; 
            return;
        }
    }
}

void Graph::print(const int a) {

    // validate the vertex
    if (_valid(a, 1, 1, 1)) {

        // if the vertex exists, call the function to print all its adjacent vertices
        if (this-> _array[a].get_exists()) { this-> _array[a].v_print(); }
        else { cout << "failure\n"; }
    }
}

/* 
CITATION [3]:
The following Dijkstra's function was inspired by "Wikipedia - Dijkstra's algorithm, Pseudocode - Using a priority" queue at 
https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm, as suggested by Mike Cooper-Stachowsky during the lab sessions.
*/
void Graph::_dijkstra(const int start, const int end, double distance[], int prev[]) {

    // cout << "DIJKSTRA'S STARTING\n";

    MinHeap pq(this-> _size);

    for (int i = 1; i <= 500000; i++) {
        if (i != start) {
            distance[i] = -1;
            prev[i] = 0;
        }
    }

    distance[start] = 0;
    prev[start] = start;

    pq.enqueue(start, 0);
    int vertex_from;
    double time_from;

    while (pq.get_populated()) {

        // visit the vertex with the shortest path so far
        pq.extract_min(vertex_from, time_from); 

        // if we have reached our destination, return
        if (vertex_from == end) { return; }

        // initialize a pointer to start going through the vertex's adjacency list
        Edge* p_edge = _array[vertex_from].get_p_head();

        // visit all the adjacent vertices
        while(p_edge) {

            // get the time to get to this vertex with the current path
            const double time_test = time_from + p_edge-> get_time();

            // get the vertex we are going to
            const int vertex_to = p_edge-> get_vertex();
   
            // push the edge in the min heap if the time is less than the shortest we have found so far, and the edge's A != 0 (time = -100)
            if ((p_edge-> get_time() != -100)  && ((time_test < distance[vertex_to]) || distance[vertex_to] == -1)) {
                
                // update the arrays
                distance[p_edge-> get_vertex()] = time_test; // set the shortest time
                prev[p_edge-> get_vertex()] = vertex_from; // set the vertex it came from

                // push the vertex to the min heap
                pq.enqueue(vertex_to, time_test);
            }

            // visit the next adjacent vertex
            p_edge = const_cast<Edge*>(p_edge-> get_next());
        }
    }
}

void Graph::lowest(const int start, const int end) {

    // ensure the vertices are valid
    if (_valid(start, end, 1, 1)) {

        // initialize the arrays
        double distance[500001];
        int prev[500001];

        // call dijstra's
        _dijkstra(start, end, distance, prev);

        // ensure the vertices are connected, if they aren't prev = 0
        if (prev[end]) { cout << "lowest is " << distance[end] << endl; }
        else { cout << "failure\n"; }
    }
}

/* 
CITATION:
The following path function was inspired by "Wikipedia - Dijkstra's algorithm, Pseudocode" at 
https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm, as suggested by Mike Cooper-Stachowsky during the lab sessions.
*/
void Graph::path(const int start, const int end) {

    // ensure the vertices are valid
    if (_valid(start, end, 1, 1)) {

        // check if the graph is populated and that the vertices exists
        if ((this-> _size) && (this-> _array[start].get_exists()) && (this-> _array[end].get_exists())) {

            // initialize the arrays
            double distance[500001];
            int prev[500001];
            
            // run dijstra's
            _dijkstra(start, end, distance, prev);

            // get the vertex which led to the end
            int from = prev[end];

            // ensure the vertices are connected, if they aren't prev = 0
            if (from) {

                cout << end << " ";

                // continue to backtrack our path until we reach the start
                while (from!= start) {
                    cout << from << " "; // print the path
                    from = prev[from];
                }

                cout << start << endl;
                return;
            }

            else { cout << "failure\n"; }
        }

        else { cout << "failure\n"; }
    }
}