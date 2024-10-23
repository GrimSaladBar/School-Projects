//Student Name: Caleb Ellis
//Student ID: 400014224

#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct clientInfo
{
    int clientID;
    string firstName;
    string surname;
    string destination;
    string payment;
    string booking;
};

class Set
{
    private:
        vector <clientInfo> elements;

    public:
        //Constructors
        Set(void) {elements.resize(0);} //Default Constructor -> Create Empty Set
        Set(int, string, string, string, string, string);

        int getNumElements() {return elements.size();}
        bool findElement(int);
        bool findElement(struct clientInfo);
        void addElement(int, string, string, string, string, string);
        void deleteElement(int);

        void unionSet(Set*, Set*);
        void intersectionSet(Set*, Set*);

        string displaySet();
};

Set::Set(int id, string first, string last, string dst, string pay, string book)
{
    elements.resize(0);
    struct clientInfo client;

    client.clientID = id;
    client.firstName = first;
    client.surname = last;
    client.destination = dst;
    client.payment = pay;
    client.booking = book;

    elements.push_back(client);
}

bool Set::findElement(int id)
{
    for (int i = 0 ; i < elements.size() ; i++)
    {
        if (elements[i].clientID == id)
            return true;
    }

    return false;
}

bool Set::findElement(struct clientInfo clientStruct)
{
    for (int i = 0 ; i < elements.size() ; i++)
    {
        if (clientStruct.clientID == elements[i].clientID && clientStruct.firstName == elements[i].firstName && clientStruct.surname == elements[i].surname && clientStruct.destination == elements[i].destination && clientStruct.payment == elements[i].payment && clientStruct.booking == elements[i].booking)
            return true;
    }

    return false;
}

void Set::addElement(int id, string first, string last, string dst, string pay, string book)
{
    //Check if the element is already in the set
    bool found = findElement(id);

    if (found)
        return;
    else
    {
        struct clientInfo client;

        client.clientID = id;
        client.firstName = first;
        client.surname = last;
        client.destination = dst;
        client.payment = pay;
        client.booking = book;

        elements.push_back(client);
    }

    return;
}

void Set::unionSet(Set* setA, Set* setB)
{
    int y;
    elements.resize(0);

    //Copy contents of setA to the union-set
    elements = setA->elements;
    y = setA->elements.size();

    //Copy contents of setB which are missing from setA to the union-set
    for (int x = 0 ; x < setB->elements.size(); x++)
    {
        if (!findElement(setB->elements[x].clientID))
        {
            elements.push_back(setB->elements[x]);
            y++;
        }
    }
}

void Set::intersectionSet(Set* setA, Set* setB)
{
    elements.resize(0);

    // Insert elements from setA with payment variable "Visa"
    for (int x = 0; x < setA->elements.size(); x++)
    {
        if (setA->elements[x].payment == "Visa")
        {
            elements.push_back(setA->elements[x]);
        }
    }

    // Insert elements from setB with payment variable "Visa"
    for (int y = 0; y < setB->elements.size(); y++)
    {
        if (setB->elements[y].payment == "Visa" && !findElement(setB->elements[y]))
        {
            elements.push_back(setB->elements[y]);
        }
    }
}
void Set::deleteElement(int id)
{
    int x;
    for (x = 0 ; x < elements.size() && elements[x].clientID != id ; x++);

    if (x == elements.size())
        return;
    else
        for (int y = x ; y < elements.size() ; y++)
            elements[y] = elements[y+1];
        elements.resize(elements.size() - 1);
    return;
}

string Set::displaySet()
{
    string str = "";

    for (int x = 0 ; x < elements.size(); x++)
    {
        str.append(to_string(elements[x].clientID));
        str.append("\t");
        str.append(elements[x].firstName);
        str.append("\t");
        str.append(elements[x].surname);
        str.append("\t");
        str.append(elements[x].destination);
        str.append("\t");
        str.append(elements[x].payment);
        str.append("\t");
        str.append(elements[x].booking);
        str.append("\n");
    }
    return str;
}
#endif
