//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author: Sreeram Kondapalli
// ASU ID: 1221440298
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    int distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;

    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, int distance);
        void printArrCityList();
};

//According to above class definition, define all functions accordingly
//----
//----
ArrivalCityList::ArrivalCityList()
{
    head = nullptr;
}

ArrivalCityList::~ArrivalCityList()
{
    struct ArrCity* current = new ArrCity();
    current = head;

    while(current != nullptr)
    {
        delete current;
        current = current->next;
    }
    head = nullptr;
}

ArrCity* ArrivalCityList::getHead()
{
    return this->head;
}

//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL
ArrCity* ArrivalCityList::findArrCity(string oneCity)
{
    struct ArrCity* current = new ArrCity();
    current = head;
    while(current != nullptr)
    {
        if(current->arrCityName == oneCity)
        {
            return current;
        }
        current = current->next;
    }
}


//*******************************************************************
//bool addArrCity(string oneCity, int distance);
//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities while inserting
//it into the list. Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.
bool ArrivalCityList::addArrCity(string oneCity, int distance)
{
    ArrCity* newArrCity = new ArrCity();
    newArrCity->arrCityName = oneCity;
    newArrCity->distance = distance;
    
    if(head == nullptr)
    {
        head = newArrCity;
        return true;
    }

    struct ArrCity* current = head;
    struct ArrCity* prev = nullptr;
    while(current != nullptr)
    {
        if(current->arrCityName > newArrCity->arrCityName)
        {
            if(current == head)
            {
                newArrCity->next = head;
                head = newArrCity;
                return true;
            }
            else
            {
                prev->next = newArrCity;
                newArrCity->next = current;
                return true;
            }
        }
        else if(current->arrCityName < newArrCity->arrCityName)
        {
            if(current->next == nullptr)
            {
                current->next = newArrCity;
                return true;
            }
            else if(current->next->arrCityName > newArrCity->arrCityName)
            {
                newArrCity->next = current->next;
                current->next = newArrCity;
                return true;
            }
        }
        prev = current;
        current = current->next;
    }
}

void ArrivalCityList::printArrCityList()
{
    if(head != nullptr)
    {
        struct ArrCity* current = head;
        while(current != nullptr)
        {
            cout << current->arrCityName << "(" << current->distance << ")" << ",";
            current = current->next;
        }
    }
    else{
        cout << "Arrival city list is empty";
    }
}
