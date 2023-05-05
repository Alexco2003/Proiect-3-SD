#include <iostream>
#include <fstream>

using namespace std;

const int maxN = 2e5+1;
int heap[maxN], pos[maxN], order[maxN];
int n, sz = 0, ord=0;

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

/// Sift up the node at the given index until its parent is smaller
void siftUp(int index)
{
    while (heap[index] < heap[father(index)] && index > 1)
    {
        /// Swap the node with its parent if the parent is smaller
        swap(heap[index], heap[father(index)]);
        /// Update the positions of the swapped nodes in the pos array
        pos[heap[father(index)]] = father(index);
        pos[heap[index]] = index;
        /// Move up to the parent node
        index /= 2;
    }
}

/// Sift down the node at the given index until both of its children are larger
void siftDown(int index)
{
    while (leftSon(index) <= sz)
    {
        int left = leftSon(index), right = rightSon(index);
        int child = left;
        /// If the right child is smaller, use that instead
        if (right <= sz && heap[right] < heap[left])
            child = right;
        /// If the child is smaller than the parent, swap them
        if (heap[child] < heap[index])
        {
            swap(heap[index], heap[child]);
            /// Update the positions of the swapped nodes in the pos array
            pos[heap[child]] = child;
            pos[heap[index]] = index;
            /// Move down to the child node
            index = child;
        }
        else
            break;
    }
}

/// Remove the node with the given value from the heap
void remove(int x)
{
    /// Get the index of the node to remove from the pos array
    int index = pos[x];
    /// Swap the node with the last node in the heap
    swap(heap[index], heap[sz]);
    /// Update the position of the node that was swapped into the index
    pos[heap[index]] = index;
    /// Decrease the size of the heap
    sz--;
    /// Sift the swapped node down to its correct position
    siftDown(index);
}

/// Insert the given value into the heap
void insert(int x)
{
    /// Increase the size of the heap
    sz++;
    /// Insert the value at the end of the heap
    heap[sz] = x;
    /// Store the position of the value in the pos array
    pos[x] = sz;
    /// Increase the order counter
    ord++;
    /// Store the order in which the value was inserted in the order array
    order[ord] = x;
    /// Sift the inserted node up to its correct position
    siftUp(sz);
}

/// Get the minimum value in the heap (the root node)
int getMin()
{
    return heap[1];
}

int main()
{
    ifstream f1 ("heapuri.in");
    ofstream f2 ("heapuri.out");
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
        if (op==2)
        {
            /// Remove the xth inserted element from the heap
            f1>>x;
            remove(order[x]);
        }
        if (op==3)
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
