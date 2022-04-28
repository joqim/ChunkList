//
// Created by Varick Erickson 2/3/2021.
//

#ifndef CHUNKLIST_H
#define CHUNKLIST_H

#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

// These error classes are done. No modifications are required.
// See ChunkList_driver.cpp for an example of how they are used.
class InvalidArrayLength{
public:
    string Msg() {
        return "Invalid array length used for constructor.";
    }
};

class IndexOutOfBounds {
public:
    string Msg() {
        return "Index is out of bounds";
    }
};

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

class EmptyList {
public:
    string Msg() {
        return "List is empty";
    }
};

// Put your pre/post conditions here.

template<class T>
class ChunkList {
public:
    // Constructors
    //Default constructor
    ChunkList();

    //Parameterized constructor
    ChunkList(T arr[], int arrLen);

    // Deconstructor
    ~ChunkList();

    // Add/remove elements
    // Function: Inserting an element into a chunk
    // Pre: the chunkList is declared and consists of head
    // Post: Appends element into existing chunk else creates a new chunk and inserts the element
    void Append(T value);

    // Function: Removes an element from the chunk
    // Pre: The chunkList contains the element passed as parameter
    // Post: Removes the element and adjusts the remaining elements or chunks respectively
    void Remove(T value);

    // Stuff to find out about the ChunkList
    // Function: Returns the length of the chunk list.
    // Pre: The listLen variable is declared and initialized
    // Post: Returns the current value of listLen variable
    int GetLength();

    // Function: Returns the ratio of number of elements in the chunkList by the total space available in the chunkList
    // Pre: listLen, ARRAY_SIZE and numChunks variable to be defined
    // Post: returns the calculated fraction
    double LoadFactor();

    // Function: Returns a boolean denoting if the passed value is present in the chunkList
    // Pre: chunkList is defined
    // Post: returns true if element is present and false if absent
    bool Contains(T value);

    // Accessing elements
    // Function: Returns the index of the element in the chunkList
    // Pre: chunkList is defined
    // Post: returns the element position calculated by iterating over the chunkList
    T GetIndex(int i);

    // Function: Resets the iterator to the beginning
    // Pre: chunkList is defined
    // Post: resets the iterNode to head and arrPos to 0
    void ResetIterator();

    // Function: Returns the next item present in the chunkList
    // Pre: chunkList is defined
    // Post: returns the successive element in the chunkList while iterating over the list
    T GetNextItem();

    // Function: Returns a boolean denoting if chunkList is empty
    // Pre: chunkList is defined
    // Post: returns true if the chunkList is empty and false if there is atleast an element present in the list
    bool IsEmpty();
private:

    // Note we did not need to make this a template
    // since this struct is part of a template class.
    struct Node {
        Node* next;
        int len;
        T values[ARRAY_SIZE];
    };

    Node* head;
    Node* tail;

    // iterator
    Node* iterNode;     // What node are were currently on?
    int arrPos;         // Within the node, what element are we looking at?

    int listLen;        // Total elements
    int numChunks;      // Total chunks/nodes
};

#include "ChunkList.cpp"

#endif //CHUNKLIST_H
