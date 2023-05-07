#include <iostream>
#include <fstream>

using namespace std;

const int maxN = 2e5 + 1;
pair<int, int> heap[maxN]; /// The heap will be a collection of pairs of (value, order index in which it was inserted)
int pos[maxN]; /// To keep the position from the heap of the xth inserted element
int n, sz = 0, ord = 0;

/// Function to get the index of the parent node of a given node
int father(int index)
{
    return index / 2;
}

/// Function to get the index of the left child node of a given node
int leftSon(int index)
{
    return index * 2;
}

/// Function to get the index of the right child node of a given node
int rightSon(int index)
{
    return index * 2 + 1;
}

/// SiftUp operation of the heap
void siftUp(int index)
{
    while (index > 1 && heap[index].first < heap[father(index)].first)
    {
        swap(heap[index], heap[father(index)]);
        pos[heap[index].second] = index;  /// Update the position of the swapped node
        pos[heap[father(index)].second] = father(index);  /// Update the position of the parent node
        index = father(index);
    }
}

/// SiftDown operation of the heap
void siftDown(int index)
{
    while (leftSon(index) <= sz)
    {
        int left = leftSon(index), right = rightSon(index);
        int child = left;
        if (right <= sz && heap[right].first < heap[left].first)
            child = right;
        if (heap[child].first < heap[index].first)
        {
            swap(heap[index], heap[child]);
            pos[heap[index].second] = index;  /// Update the position of the swapped node
            pos[heap[child].second] = child;  /// Update the position of the child node
            index = child;
        }
        else
            break;
    }
}


/// Remove the node with the given order from the heap
void remove(int order)
{
    /// Get the index of the node to remove from the pos array
    int index = pos[order];
    /// Swap the node with the last node in the heap
    swap(heap[index], heap[sz]);
    /// Update the position of the swapped node with the order of the removed node
    pos[heap[index].second] = index;
    /// Decrease the size of the heap
    sz--;
    /// Sift the swapped node down to its correct position
    siftDown(index);
}

/// Insert the given value into the heap
void insert(int x)
{
    ///Increase the size of the heap
    sz++;
    /// Increase the order counter
    ord++;
    /// Insert the value at the end of the heap
    heap[sz] = make_pair(x, ord);
    pos[ord] = sz;
    /// Sift the inserted node up to its correct position
    siftUp(sz);
}

/// Get the minimum value in the heap (the root node)
int getMin()
{
    return heap[1].first;
}

int main()
{
    ifstream f1("heapuri.in");
    ofstream f2("heapuri.out");
    f1 >> n;
    for (int i = 1; i <= n; i++)
    {
        int op, x;
        f1 >> op;
        if (op == 1)
        {
            /// Insert a new element into the heap
            f1 >> x;
            insert(x);
            continue;
        }
        if (op == 2)
        {
            /// Remove the xth inserted element from the heap
            f1 >> x;
            remove(x);
            continue;
        }
        if (op == 3)
        {
            /// Print the minimum element from the heap
            f2 << getMin() << endl;
            continue;
        }
    }

    f1.close();
    f2.close();
    return 0;
}
