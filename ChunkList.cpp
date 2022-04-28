
//Default constructor
template<class T>
ChunkList<T>::ChunkList() {
    head = nullptr;
    tail = nullptr;

    iterNode = head;
    arrPos = -1;

    listLen = 0;
    numChunks = 0;
}

template<class T>
int ChunkList<T>::GetLength() {
    cout<<"\n listLen in GetLength"<<listLen;
    return listLen;
}

//Parameterized constructor
template<class T>
ChunkList<T>::ChunkList(T *arr, int arrLen) {
    cout<<"\n Inside parameterized constructor of length"<< arrLen;
    if(arrLen<0) {
        throw InvalidArrayLength();
    }

    head = nullptr;
    tail = nullptr;

    iterNode = head;
    arrPos = -1;

    listLen = 0;
    numChunks = 0;

    //access each element of array arr
    for (int i = 0; i < arrLen; i++)
    {
        Append(arr[i]);
    }
}

//Deconstructor
template<class T>
ChunkList<T>::~ChunkList() {
    Node *temp = head;

    while (temp != nullptr)
    {
        Node *toDelete = temp;
        temp = temp->next;

        if (toDelete != nullptr)
            delete toDelete;
    }
}

template<class T>
void ChunkList<T>::Append(T value) {
    cout<<"Inside append "<< value;
    if (head == nullptr)
    {
        cout<<"\n inside new node creation";
        //create a new Node
        Node *newNode = new Node();

        newNode->next = nullptr;
        newNode->len = 1;
        newNode->values[0] = value;

        head = newNode;
        tail = newNode;

        iterNode = head;
        arrPos = 0;

        listLen = 1;
        numChunks = 1;
        return;
    }

    // tail points to the last node
    //check if the last node is full ?
    if (tail->len >= ARRAY_SIZE)
    {
        cout<<"\n creating a new node since currnode is full";
        //if last node is full then create a new node
        Node *newNode = new Node();

        newNode->next = nullptr;
        newNode->len = 1;

        tail->next = newNode;
        tail = newNode;
        tail->values[0] = value;

        numChunks++;
        listLen++;
        return;
    }

    //otherwise append the value to the last position of last node
    tail->values[tail->len] = value;
    tail->len++;
    listLen++;
    cout<<"\n len value in append"<<listLen;
}

template<class T>
void ChunkList<T>::Remove(T value) {
    cout<<"\n Inside Remove "<<value;

    //throwing an exception if value is not present
    if (!Contains(value)) throw ("The chunk list does not contain");
    cout<< "\n length before remove" << listLen;
    Node *currNode = head;
    Node *prev = nullptr;

    //iterating through the nodes
    while (currNode != nullptr)
    {
        //iterating through the elements in current node
        for (int i = 0; i < currNode->len; i++)
        {
            if (currNode->values[i] == value)
            {
                cout<<"\n deleting this value"<<value;
                //upshifting the elements in the current node
                for (int j = i; j < currNode->len - 1; j++)
                {
                    currNode->values[j] = currNode->values[j + 1];
                }
                currNode->len--;
                listLen--;

                //there are no elements left in current chunk after remove hence deleting this chunk
                //all elements in a particular node is removed, map connection from previous node to next node
                if (currNode->len == 0)
                {
                    //first node deletion
                    if(currNode == head) {
                        cout<<"inside first node deletion";
                        head = currNode->next;
                        numChunks--;
                        delete currNode;
                    } else {
                        cout<<"inside middle node deletion";
                        cout<<"\n prev before linking"<<prev->next;
                        cout<<"\n curr before linking"<<currNode;
                        cout<<"\n curr->next before linking"<<currNode->next;
                        prev->next = currNode->next;
                        cout<<"\n prev after linking"<<prev->next;
                        cout<<"\n curr after linking"<<currNode;
                        cout<<"\n curr->next before linking"<<currNode->next;
                        // tail check
                        if(currNode->next==tail) {
                            tail = nullptr;
                        }
                        numChunks--;
                        delete currNode;
                    }
                }
                return;
            }
        }
        //iterating through next chunkNode in the chunkList
//        cout<<"\n prev before iteration"<<prev;
//        cout<<"\n curr before iteration"<<currNode;
        prev = currNode;
        currNode = currNode->next;
    }
}

template<class T>
double ChunkList<T>::LoadFactor() {
    cout<<"\n Inside loadFactor";
    cout<<"\n listLen"<<listLen;
    cout<<"\n numChunks"<<numChunks;
    if (numChunks == 0)
        return 0;
    return (double)listLen / (double)(numChunks * ARRAY_SIZE);
}

template<class T>
bool ChunkList<T>::Contains(T value) {
    Node *temp = head;

    while (temp != nullptr)
    {
        for (int i = 0; i < temp->len; i++)
        {
            if (temp->values[i] == value)
            {
                return true;
            }
        }
        temp = temp->next;
    }
    return false; //otherwise
}

template<class T>
T ChunkList<T>::GetIndex(int i) {
    cout<<"\n Inside getIndex method";
    if (IsEmpty()) throw EmptyList();
    if (i >= listLen || i < 0) throw "Bad argument Error ...";

    //otherwise find the element
    Node *temp = head;
    int passedElement = 0;
    while (temp != nullptr)
    {
        if (i >= passedElement && i < passedElement + temp->len)
        {
            return temp->values[i - passedElement];
        }
        passedElement = passedElement + temp->len;
        temp = temp->next;
    }
    return passedElement;
}

template<class T>
void ChunkList<T>::ResetIterator() {
    cout<<"\n Inside reset iterator";
    iterNode = head; //now iterator points to the head node
    arrPos = 0;      //array position is now 0
}

template<class T>
T ChunkList<T>::GetNextItem() {
    cout<<"\n inside get next item "<<iterNode;
    //if (!Contains(iterNode->values[arrPos])) throw IteratorOutOfBounds();
    if (iterNode == nullptr)
    {
        cout<<"\n iterNode is nullptr";
        throw IteratorOutOfBounds();
    }

    T val = iterNode->values[arrPos];

    //updating the iterator
    arrPos++;

    if (arrPos >= iterNode->len)
    {
        iterNode = iterNode->next;
        arrPos = 0;
    }
    cout<<"\n val"<<val;
    return val;
}

template<class T>
bool ChunkList<T>::IsEmpty() {
    return (head == nullptr);
}

#include "ChunkList.h"


