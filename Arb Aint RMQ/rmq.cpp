#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

const int MAX_N = 100001;

/// Structure to represent a node in the interval tree
struct Node
{
    int min_val;  /// Minimum value in the range represented by the node
};

Node tree[4 * MAX_N];  /// Interval tree
int elements[MAX_N];  /// Array to store the elements

/// Function to build the interval tree
void buildTree(int node, int start, int end)
{
    if (start == end)
    {
        /// Leaf node, store the element
        tree[node].min_val = elements[start];
        return;
    }

    int mid = (start + end) / 2;

    /// Recursively build the left and right subtrees
    buildTree(2 * node, start, mid);
    buildTree(2 * node + 1, mid + 1, end);

    /// Update the current node with the minimum value of its children
    tree[node].min_val = min(tree[2 * node].min_val, tree[2 * node + 1].min_val);
}

/// Function to query the minimum element in a given range
int queryMin(int node, int start, int end, int l, int r)
{

    if (start > r || end < l)
        return INT_MAX;

    if (start >= l && end <= r)
        return tree[node].min_val;

    int mid = (start + end) / 2;
    /// Partial overlap, query the minimum element from the left and right subtrees
    int left = queryMin(2 * node, start, mid, l, r);
    int right = queryMin(2 * node + 1, mid + 1, end, l, r);

    return min(left, right);
}

int main()
{
    int N, M;
    ifstream f1("rmq.in");
    ofstream f2("rmq.out");
    f1 >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        f1 >> elements[i];
    }

    /// Build the interval tree
    buildTree(1, 1, N);

    while (M--)
    {
        int x, y;
        f1 >> x >> y;

        /// Find the minimum element in the interval [x, y]
        int min_val = queryMin(1, 1, N, x, y);
        f2 << min_val << endl;
    }

    f1.close();
    f2.close();
    return 0;
}
