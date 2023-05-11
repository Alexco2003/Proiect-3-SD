#include <iostream>
#include <fstream>
using namespace std;

const int MAX_N = 100001;

/// Structure to represent a node in the interval tree
struct Node
{
    int maximum;  /// Maximum grade in the range represented by the node
    int value;   /// Value to update the element at position a
};

Node tree[4 * MAX_N];  /// Interval tree
int elements[MAX_N];    /// Array to store the elements

/// Function to build the interval tree
void buildTree(int node, int start, int end)
{
    if (start == end)
    {
        /// Leaf node, store the element value
        tree[node].maximum = elements[start];
        tree[node].value = -1; /// No update value
        return;
    }

    int mid = (start + end) / 2;

    /// Recursively build the left and right subtrees
    buildTree(2 * node, start, mid);
    buildTree(2 * node + 1, mid + 1, end);

    /// Update the current node with the maximum element of its children
    tree[node].maximum = max(tree[2 * node].maximum, tree[2 * node + 1].maximum);
    tree[node].value = -1;  /// No update value
}

/// Function to propagate the update value
void propagateUpdate(int node)
{
    if (tree[node].value != -1)
    {
        /// Update the element value
        tree[node].maximum = tree[node].value;

        if (2 * node < 4 * MAX_N)
        {
            /// Propagate the update value to the children nodes
            tree[2 * node].value = tree[node].value;
            tree[2 * node + 1].value = tree[node].value;
        }

        /// Reset the update value of the current node
        tree[node].value = -1;
    }
}

/// Function to update the element at position a
void updateElement(int node, int start, int end, int a, int b)
{
    propagateUpdate(node);

    if (start == end)
    {
        /// Leaf node, update the element value
        tree[node].maximum = b;
        return;
    }

    int mid = (start + end) / 2;

    if (a <= mid)
    {
        /// Update the element in the left subtree
        updateElement(2 * node, start, mid, a, b);
    }
    else
    {
        /// Update the element in the right subtree
        updateElement(2 * node + 1, mid + 1, end, a, b);
    }

    /// Update the current node with the maximum element of its children
    tree[node].maximum = max(tree[2 * node].maximum, tree[2 * node + 1].maximum);
}

/// Function to query the maximum element in a given range
int queryMaxElement(int node, int start, int end, int l, int r)
{
    propagateUpdate(node);

    if (start > r || end < l)
        return -1;

    if (start >= l && end <= r)
        return tree[node].maximum;

    int mid = (start + end) / 2;
    /// Partial overlap, query the maximum element from the left and right subtrees
    int left = queryMaxElement(2 * node, start, mid, l, r);
    int right = queryMaxElement(2 * node + 1, mid + 1, end, l, r);

    /// Return the maximum element
    if (left == -1)
        return right;
    if (right == -1)
        return left;
    return max(left, right);
}

int main()
{
    int N, M;
    ifstream f1("arbint.in");
    ofstream f2("arbint.out");
    f1 >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        f1 >> elements[i];
    }

    /// Build the interval tree
    buildTree(1, 1, N);

    while (M--)
    {
        int op, a, b;
        f1 >> op >> a >> b;

        if (op == 0)
        {
            /// Find the maximum element in the interval [a, b]
            int maxElement = queryMaxElement(1, 1, N, a, b);
            f2 << maxElement << endl;
        }
        else if (op == 1)
        {
            /// Update the element at position a with value b
            updateElement(1, 1, N, a, b);
        }
    }

    f1.close();
    f2.close();
    return 0;
}

