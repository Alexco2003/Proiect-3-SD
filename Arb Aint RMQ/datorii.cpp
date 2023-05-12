#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int N = 15000;
vector<int> tree(4 * N + 1);  /// Interval tree array
vector<int> debts(N + 1); /// Input array

/// Function to build the interval tree
void buildTree(int node, int start, int end)
{
    if (start == end)
    {
        /// Leaf node, store the value in the input array
        tree[node] = debts[start];
        return;
    }

    int mid = (start + end) / 2;

    /// Recursively build left and right subtrees
    buildTree(2 * node, start, mid);
    buildTree(2 * node + 1, mid + 1, end);

    /// Update the current node with the sum of its children
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

/// Function to update a range of values in the interval tree
void updateRange(int node, int start, int end, int l, int r, int value)
{
    if (start > r || end < l)
        return;

    if (start >= l && end <= r)
    {
        /// The current node is completely within the update range
        /// Update the node value by subtracting the range sum
        tree[node] -= (end - start + 1) * value;
        return;
    }

    int mid = (start + end) / 2;

    /// Recursively update left and right subtrees
    updateRange(2 * node, start, mid, l, r, value);
    updateRange(2 * node + 1, mid + 1, end, l, r, value);

    /// Update the current node with the sum of its children
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

/// Function to query the sum in a given range
int querySum(int node, int start, int end, int l, int r)
{
    if (start > r || end < l)
        return 0;

    if (start >= l && end <= r)
        return tree[node];

    int mid = (start + end) / 2;

    /// Recursively query left and right subtrees
    int left = querySum(2 * node, start, mid, l, r);
    int right = querySum(2 * node + 1, mid + 1, end, l, r);

    /// Return the sum of the left and right subtree queries
    return left + right;
}

int main()
{
    ifstream f1("datorii.in");
    ofstream f2("datorii.out");

    int N, M;
    f1 >> N >> M;

    for (int i = 1; i <= N; i++)
        f1 >> debts[i];

    buildTree(1, 1, N);

    while (M--)
    {
        int op;
        f1 >> op;

        if (op == 0)
        {
            /// Update operation
            int T, V;
            f1 >> T >> V;
            updateRange(1, 1, N, T, T, V);
        }
        else
        {
            /// Query operation
            int P, Q;
            f1 >> P >> Q;
            f2 << querySum(1, 1, N, P, Q) << endl;
        }
    }

    f1.close();
    f2.close();
    return 0;
}


