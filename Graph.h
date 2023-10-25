//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author: Sreeram Kondapalli
// ASU ID: 1221440298
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
#include "MinPriorityQueue.h"
#include <string>
#include <iostream>

using namespace std;

// Define the Graph class
class Graph
{
   private:
   int numOfNode;                 //number of vertices in the graph
   MinPriorityQueue* cityHeap;    //adjacency list of the graph, it is a min-heap
                                  //of departure city objects

   public:
   // Constructor and destructor
   Graph(int numOfNode, MinPriorityQueue* cityHeap);
   ~Graph();

   // Graph methods
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(DepCity u, DepCity v);
   int findOneCity(string aCityName);
   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
   string printPath(string sourceCityName, DepCity* aCity, int index);

   // You can add any auxiliary functions here if needed
};

// Constructor for the Graph class
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

// Destructor for the Graph class
Graph::~Graph()
{
   delete [] cityHeap;
   cityHeap = nullptr;
   numOfNode = 0;
}

// This function prints the graph by calling the printHeap method on cityHeap
void Graph::printGraph()
{
   cityHeap->printHeap();
}

// Finds the index of a city in the cityHeap by its name, returns -1 if not found
int Graph::findOneCity(string aCityName)
{
   int result = cityHeap->isFound(aCityName);
   return result;
}

// Initializes the single source shortest path problem by setting the source city's distance to 0 and all others to a large value
void Graph::initialize_single_source(string sourceCityName)
{
   if(cityHeap->isFound(sourceCityName) != -1){   
      for(int i = 0; i < numOfNode; i++){
         if(i == cityHeap->isFound(sourceCityName))
            cityHeap->getDepCityArr()[i].d = 0;
         else
            cityHeap->getDepCityArr()[i].d = 30000+i;
         cityHeap->getDepCityArr()[i].pi = "0";
         cityHeap->decreaseKey(i, cityHeap->getDepCityArr()[i]);
      }
   }
}

// Update the distance of v from the source if the path through u is shorter
void Graph::relax(DepCity u, DepCity v)
{
   ArrCity* arrCity = u.arrCityList->findArrCity(v.depCityName);
   if (arrCity && v.d > u.d + arrCity->distance) {
      v.d = u.d + arrCity->distance;
      v.pi = u.depCityName;
      cityHeap->decreaseKey(findOneCity(v.depCityName), v);
   }
}

// Implementation of Dijkstra's algorithm for single source shortest path
void Graph::dijkstra(string sourceCityName)
{  
   initialize_single_source(sourceCityName);
   MinPriorityQueue* Set = new MinPriorityQueue(numOfNode);
   MinPriorityQueue* Q = cityHeap;
  
   Q->build_min_heap(); // Build the min-heap of cities
   while (Q->getSize() > 0) // Continue until all cities have been processed
   {
      DepCity u = Q->getHeapMin(); // Get the city with the smallest distance from the source
      Q->extractHeapMin(); // Remove the city from the heap
      Set->insert(u); // Add the city to the set of processed cities

      struct ArrCity* current = u.arrCityList->getHead(); // Get the head of the adjacency list for city u
      while (current != nullptr) // Iterate through all adjacent cities
      {
         if (findOneCity(current->arrCityName) != -1)
         {
            DepCity v = Q->getDepCityArr()[findOneCity(current->arrCityName)];
            relax(u, v); // Update the distance of v from the source if the path through u is shorter
         }
         current = current->next; // Move to the next adjacent city
      }
   }
   cityHeap = Set; // Update the cityHeap with the processed cities
}

// Print the shortest path from the source city to all other cities using Dijkstra's algorithm
void Graph::printDijkstraPath(string sourceCityName)
{
   cout << "Source City: " << sourceCityName << endl;
   cout << left;
   cout << setw(14) << "Arrival City" << setw(15) << "Shortest Dist." << setw(15) << "Shortest Path" << endl;

   DepCity *S = cityHeap->getDepCityArr();

   for (int i = 0; i < numOfNode; i++) // Iterate through all cities
   {
      cout << left;
      if (S[i].d >= 30000) // If the distance to the city is too large, print "None exist" for distance and path
      {
         cout << setw(15) << S[i].depCityName << setw(15) << "None exist" << setw(15) << "None exist" << endl;
      }
      else
      {
         cout << setw(15) << S[i].depCityName << setw(15) << S[i].d << printPath(sourceCityName, S, i);
      }
   }
   cout << "\n";
}

// Print the path from the source city to a specified city
string Graph::printPath(string sourceCityName, DepCity* aCity, int index)
{
    string output = ""; // Initialize the output string

    // Build the path string by traversing the predecessors (pi) of each city
    while (aCity[index].depCityName != sourceCityName && index >= 0)
    {
      output = "->" + aCity[index].depCityName + output; // Add the city to the path string
      int parent = cityHeap->isFound(aCity[index].pi); // Find the index of the city's predecessor
      index = parent; // Update the index to the predecessor's index
    }
    return sourceCityName + output + "\n"; // Return the full path string
}
