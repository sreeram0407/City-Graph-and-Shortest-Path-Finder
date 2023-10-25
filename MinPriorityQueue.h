//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author: Sreeram Kondapalli
// ASU ID: 1221440298
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
//----
#include "ArrivalCityList.h"
#include <string>
#include <iostream>

using namespace std;

// Each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    int d;
    string pi;
    ArrivalCityList* arrCityList;
};

// class MinPriorityQueue represents a Min-heap that contains DepCity objects.
// The key of each DepCity is its d value.
class MinPriorityQueue
{
    private:
        struct DepCity* depCityArr;      // a DepCity array
        int capacity, size;

    public:
        MinPriorityQueue(int capacity);
        ~MinPriorityQueue();

        DepCity* getDepCityArr();
        int getSize();
        void setSize(int newSize);
        int getCapacity();
        int isFound(string oneDepCityName);
        bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);
        bool insert(DepCity oneDepCity);
        void heapify(int index);
        DepCity getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();
        void build_min_heap();
};

// This function prints the heap
void MinPriorityQueue::printHeap()
{
    cout << "\nHeap size = " << getSize() << "\n" << endl;

    cout << left;
    cout << setw(15) << "Dep. City"
         << setw(12) << "d Value"
         << setw(15) << "PI"
         << "Arrival City List" << endl;

    for(int i = 0; i < size; i++)
    {
        if(depCityArr[i].pi == "0")
        {
            cout << left;
            cout << setw(15) << depCityArr[i].depCityName << setw(12) << depCityArr[i].d << setw(15) << "No Parent";
            depCityArr[i].arrCityList->printArrCityList();
            cout << endl;
        }
        else
        {
            cout << left;
            cout << setw(15) << depCityArr[i].depCityName << setw(12) << depCityArr[i].d << setw(15) << depCityArr[i].pi;
            depCityArr[i].arrCityList->printArrCityList();
            cout << endl;
        }
    }
}

// When you create the dummy node, initialize its d value to be
// 30000 which represents infinite
bool MinPriorityQueue::insert(DepCity oneDepCity)
{
    size++;
    depCityArr[size-1].d = 35000;
    if(decreaseKey(size - 1, oneDepCity))
    {
        return true;
    }
    return false;
}

// Constructor for MinPriorityQueue
MinPriorityQueue::MinPriorityQueue(int capacity)
{
    size = 0;
    this->capacity = capacity;
    depCityArr = new DepCity[this->capacity];
}

// Destructor for MinPriorityQueue
MinPriorityQueue::~MinPriorityQueue()
{
    delete[] depCityArr;
}

// Getter for depCityArr
DepCity* MinPriorityQueue::getDepCityArr()
{
    return depCityArr;
}

// Getter for size
int MinPriorityQueue::getSize()
{
    return size;
}

// Setter for size
void MinPriorityQueue::setSize(int newSize)
{
    this->size = newSize;
}

// Getter for capacity
int MinPriorityQueue::getCapacity()
{
    return capacity;
}

// Check if a city exists in the heap
int MinPriorityQueue::isFound(string oneDepCityName)
{
    for (int i = 0; i < size; i++)
    {
        if (depCityArr[i].depCityName == oneDepCityName)
        {
            return i;
        }
    }
    return -1;
}

// Decrease the key of a DepCity object in the min-heap
bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue)
{   
    DepCity temp;                                
    depCityArr[index] = oneDepCityWithNewDValue; 
    int parentIndex = parent(index);                 

    while (index > 0 && (depCityArr[parentIndex].d > depCityArr[index].d))
    {
        swap(depCityArr[index], depCityArr[parentIndex]);
        index = parentIndex;
        parentIndex = parent(index);
    }
    return true;
}

// Maintain the min-heap property by moving the element at the given index down the heap
void MinPriorityQueue::heapify(int index)
{
    int index1 = index;
    int l = leftChild(index);
    int r = rightChild(index);
    if(l < size && depCityArr[l].d < depCityArr[index].d)
        index1 = l;
    if( r < size && depCityArr[r].d < depCityArr[index1].d)
        index1 = r;
    if(index1 != index){       
        swap(depCityArr[index], depCityArr[index1]);
        heapify(index1);
    }
}

// Get the minimum element from the heap
DepCity MinPriorityQueue::getHeapMin()
{
    return depCityArr[0];
}

// Remove the minimum element from the heap
void MinPriorityQueue::extractHeapMin()
{
    depCityArr[0] = depCityArr[size-1];
    size--;
    heapify(0);
}

// Get the index of the left child of the element at the given index
int MinPriorityQueue::leftChild(int parentIndex)
{
    return ((2*parentIndex) + 1);
}

// Get the index of the right child of the element at the given index
int MinPriorityQueue::rightChild(int parentIndex)
{
    return ((2 * parentIndex) + 2);
}

// Get the index of the parent of the element at the given index
int MinPriorityQueue::parent(int childIndex)
{
    return (int)(childIndex-1)/2;
}

// Build the min-heap from the given array of DepCity objects
void MinPriorityQueue::build_min_heap()
{
    for(int i = (size/2) - 1; i >= 0; i--)
    {
        heapify(i);
    }
}
