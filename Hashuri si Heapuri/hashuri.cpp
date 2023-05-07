#include <iostream>
#include <fstream>

using namespace std;

/// Structure for linked list node
struct Node
{
    int data;
    Node* next;
};

/// Class for hash table
class HashTable
{
    int P; /// Number of linked lists
    Node** table; /// Array of linked lists

public:
    HashTable(int p);

    /// Function to calculate hash value
    int hash(int x);


    /// Function to insert element into hash table
    void insert(int x);


    /// Function to delete element from hash table
    void remove(int x);


    /// Function to search for an element in the hash table
    bool search(int x);

    ~HashTable() {};
};

HashTable::HashTable(int p)
{
    this->P = p;
    this->table = new Node*[this->P]; /// Allocate memory for linked lists

    /// Initialize each linked list as empty
    for (int i = 0; i < this->P; i++)
        this->table[i] = nullptr;
}

int HashTable::hash(int x)
{
    return x % this->P;
}

void HashTable::insert(int x)
{
    int index = this->hash(x);
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = nullptr;

    if (this->table[index] == nullptr)
    {
        /// If the linked list is empty, insert the element as the first node
        this->table[index] = newNode;
    }
    else
    {
        /// If the linked list is not empty, insert the element at the end
        Node* curr = this->table[index];
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode;
    }
}

void HashTable::remove(int x)
{
    int index = this->hash(x);
    Node* curr = this->table[index];
    Node* prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->data == x)
        {
            /// If the element is found, delete it from the linked list
            if (prev == nullptr)
            {
                /// If it's the first node, update the head of the list
                this->table[index] = curr->next;
            }
            else
            {
                /// If it's not the first node, skip the current node
                prev->next = curr->next;
            }

            delete curr;
            break;
        }

        prev = curr;
        curr = curr->next;
    }
}

bool HashTable::search(int x)
{
    int index = this->hash(x);
    Node* curr = this->table[index];

    while (curr != nullptr)
    {
        if (curr->data == x)
            return true;
        curr = curr->next;
    }

    return false;
}


int main()
{
    ifstream f1("hashuri.in");
    ofstream f2("hashuri.out");

    int N;
    f1 >> N;

    HashTable hashTable(N); /// Create hash table with N linked lists

    for (int i = 0; i < N; i++)
    {
        int op, x;
        f1 >> op >> x;

        switch (op)
        {
        case 1:
            hashTable.insert(x);
            break;
        case 2:
            hashTable.remove(x);
            break;
        case 3:
            f2 << hashTable.search(x) << endl;
            break;
        }
    }

    f1.close();
    f2.close();

    return 0;
}
