// include header files
#include "Graph.hpp"

using namespace std;

// declare pointers for dynamic memory allocation of objects
Graph graph;

int main() {

  string command;

  // Handle user inputted commands through function calls
  while (cin >> command){
    
    if (command == "LOAD") { 
      string filename;
      cin >> filename;

      graph.load(filename);
    }

    else if (command == "INSERT") {
        
      int a, b;
      double d, s;

      cin >> a >> b >> d >> s;

      graph.insert(a, b, d, s, false);
    }
    
    else if (command == "PRINT") {
      int a;
      cin >> a;

      graph.print(a);
    }

    else if (command == "DELETE") {
      int a;
      cin >> a;

      graph.del(a);
    }

    else if (command == "PATH") {
      int a, b;
      cin >> a >> b;

      graph.path(a, b);
    }

    else if (command == "TRAFFIC") {

      int a, b;
      double A;
      cin >> a >> b >> A;

      graph.traffic(a, b, A, false);
        
    }

    else if (command == "UPDATE") { 
      string filename;
      cin >> filename;

      graph.update(filename);
    }

    else if (command == "LOWEST") {
      int a, b;
      cin >> a >> b;

      graph.lowest(a, b);
    }

    // deallocate memory and exit the program  
    else if (command == "END") {
      return 0 ;
    }
  }
}