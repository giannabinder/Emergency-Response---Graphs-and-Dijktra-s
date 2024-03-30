/* 
CITATION [4][5]:
The following MinHeap class was created by referencing ECE 250: Algorithms and Data Structures Lecture 18 and 19: Heaps 
*/

// include header files
#include "MinHeap.hpp"

using namespace std;

MinHeap::MinHeap(const int size) : _heap(new Pair[size + 1]), _size(1) { }

MinHeap::~MinHeap() { 
    delete[] this-> _heap;
    this-> _heap = nullptr;
}

void MinHeap::_min_heapify(const int i) {
    int left = 2*i;
    int right = 2*i + 1;
    int smallest = i;

    if ((left < this-> _size) && (this-> _heap[left].get_time() < this-> _heap[smallest].get_time())) { smallest = left; }
    if ((right < this-> _size) && (this-> _heap[right].get_time() < this-> _heap[smallest].get_time())) { smallest = right; }
    if (smallest != i) {

        // swap the vertices they store
        double temp_time = this-> _heap[smallest].get_time();
        int temp_vertex = this-> _heap[smallest].get_vertex();
        this-> _heap[smallest].set_vt(this-> _heap[i].get_vertex(), this-> _heap[i].get_time());
        this-> _heap[i].set_vt(temp_vertex, temp_time);

        // heapify the subheap which was modified
        this-> _min_heapify(smallest);
    }
}

void MinHeap::enqueue(const int vertex, const double time) {

    bool update_size = true;

    // if this is the first item, push it onto the heap directly
    if (this-> _size == 1) { 
        this-> _heap[this-> _size].set_vt(vertex, time); 
    }

    else {

        int i = this-> _size;

        // look for the vertex in the PQ
        for (int j = 1; j < this-> _size; j++) {
            if (this-> _heap[j].get_vertex() == vertex) { 
                i = j; 
                update_size = false;
                break;
            }
        }

        // check if the "parent" is greater than the vertex to enqueue, swap them if they are and check the new parent
        while ((i > 1) && (this-> _heap[i/2].get_time() > time)) {
            this-> _heap[i].set_vt(this-> _heap[i/2].get_vertex(), this-> _heap[i/2].get_time());
            i /= 2;
        }

        this-> _heap[i].set_vt(vertex, time); // once the while loop finishes, we have found the spot to put the vertex to enqueue
    }

    if (update_size) { this-> _size++; } // increase the size of the vertices stored in the heap if a new vertex was added
}

void MinHeap::extract_min(int& vertex, double& time) {

    // get the  min's information
    time = this-> _heap[1].get_time(); // store the time
    vertex = this-> _heap[1].get_vertex(); // store the vertex

    this-> _heap[1].set_vt(this-> _heap[this-> _size - 1].get_vertex(), this-> _heap[this-> _size - 1].get_time()); // replace the min time with the vertex the furthest away
    this-> _size--; // decrease the size of the heap

    // heapify to restore the heap properties
    _min_heapify(1);
}

// return if the heap has any vertices stored in it
const bool MinHeap::get_populated() {
    if (!(this-> _size)) { return false; }
    else { return true; }
}