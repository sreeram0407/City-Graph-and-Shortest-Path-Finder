//********************************************************************
// Author: Sreeram Kondapalli
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
//----
#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);     //**optional

int main()
{
   int count;       //a variable for number of nodes
   string oneLine, sourceCityName;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times

   //cout << "Enter number of cities: ";
   cin >> count;
   cin.ignore(20, '\n');

   //For each line of the file, we will create an ArrivalCityList(which is a linked list)
   //for a specific departure city. It represents all its reachable arrival cities with distance info.
   //Here we use an array of DepCity to store them
   DepCity* depCityArr = new DepCity[count];

   //Initialize depCityArr. Set each node's d value to be very large 10000
   //initialize each arrival city list
   for(int i = 0; i< count; i++)
   {
      depCityArr[i].d = 10000 + i;      //***this is to make sure each node has different d value
      //----
      //----
      depCityArr[i].pi = "0";
      depCityArr[i].arrCityList = new ArrivalCityList();
   }

   MinPriorityQueue* Q = new MinPriorityQueue(count);
   //get input line by line and create the depCityArr
   for(int i = 0; i< count; i++)
   {
      string name = "";
      getline(cin, oneLine);
      //----
      //----
      ArrivalCityList* arrList = new ArrivalCityList;
      getCityInfo(oneLine, name, arrList);
      depCityArr[i].depCityName = name;
		depCityArr[i].d = 10000 + i;
      depCityArr[i].pi = "0";
      depCityArr[i].arrCityList = arrList;
      Q->insert(depCityArr[i]);
   }

  //create a Graph object
  //----
  Graph* graph1 = new Graph(count, Q);

   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
  //----
  graph1->printGraph();

   //Next you need to design a sentinel value controlled while loop base on answer
   //If user answer is 'yes', get source city name, run Dijkstra algorithm, print
   //shortest path, then ask whether user want to continue or not...
   cout << "\nEnter source city name: " << endl;
   getline(cin, sourceCityName);
   if(graph1->findOneCity(sourceCityName) == -1)
   {
      cout << sourceCityName << " does NOT exist\n" << endl;
   }
   else
   {
      graph1->dijkstra(sourceCityName);
      cout << "\nPrint the Dijkstra algorithm running result\n" << endl;\
      graph1->printDijkstraPath(sourceCityName);
   }

   cout << "Find shortest path for another departure city(yes or no): " << endl;
   getline(cin, answer);

   while(answer == "yes")
   {
      cout << "Enter source city name: " << endl;
      getline(cin, sourceCityName);
      if(graph1->findOneCity(sourceCityName) == -1)
      {
         cout << sourceCityName << " does NOT exist\n" << endl;
      }
      else
      {
         graph1->dijkstra(sourceCityName);
         cout << "\nPrint the Dijkstra algorithm running result\n" << endl;\
         graph1->printDijkstraPath(sourceCityName);
      }
      cout << "Find shortest path for another departure city(yes or no): " << endl;
      getline(cin, answer); 
   }
   cout << "Program terminate" << endl;
}

//************************************************************************
//Give one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
   //----
   //----
   string delimiter = ",";
   int count = 0;
   string arrCityName;
   int distance;

   int pos = oneLine.find(delimiter);
   string token = oneLine.substr(0, pos);
   depCityName = token;
   oneLine.erase(0, pos + delimiter.length());

   while (token != "")
   {
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      oneLine.erase(0, pos + delimiter.length());

      if (token == "")
      {
         arrCityName = "";
         distance = 0;
         break;
      }
      getArrCityInfo(token, arrCityName, distance);
      arrCityList->addArrCity(arrCityName, distance);
      count++;
   }
}

//****************************************************************************
//Given one arrival city info. format of, such as Z(60), this function
//extract arrival city name 'Z' and distance 60 from it.
//this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
   //----
   //----
   string delimiterLeft = "(";
   string delimiterRight = ")";

   
   int pos = oneArrCityInfo.find(delimiterLeft);
   string token = oneArrCityInfo.substr(0, pos);
   arrCityName = token;
   oneArrCityInfo.erase(0, pos + delimiterLeft.length());

   pos = oneArrCityInfo.find(delimiterRight);
   token = oneArrCityInfo.substr(0, pos);
   distance = stod(token);
   
   oneArrCityInfo.erase(0, pos + delimiterRight.length());
}
