#include <iostream>
#include <fstream>
using namespace std;

const int MAX_N = 100001;

/// Structure to represent a node in the interval tree
struct Node
{
    int grade;  /// Maximum grade in the range represented by the node
    int lazy;   /// Lazy propagation value
};

Node tree[4 * MAX_N];  /// Interval tree
int grades[MAX_N];    /// Array to store the grades

/// Function to build the interval tree
void buildTree(int node, int start, int end)
{
    if (start == end)
    {
        /// Leaf node, store the grade and initialize lazy propagation value
        tree[node].grade = grades[start];
        tree[node].lazy = 0;
        return;
    }

    int mid = (start + end) / 2;

    /// Recursively build the left and right subtrees
    buildTree(2 * node, start, mid);
    buildTree(2 * node + 1, mid + 1, end);

    /// Update the current node with the maximum grade of its children
    tree[node].grade = max(tree[2 * node].grade, tree[2 * node + 1].grade);
    tree[node].lazy = 0;  /// Initialize lazy propagation value
}

/// Function to propagate the lazy propagation value
void propagateLazy(int node, int start, int end)
{
    if (tree[node].lazy != 0)
    {
        /// Update the grade of the current node with the lazy value
        tree[node].grade += tree[node].lazy;

        if (start != end)
        {
            /// Propagate the lazy value to the children nodes
            tree[2 * node].lazy += tree[node].lazy;
            tree[2 * node + 1].lazy += tree[node].lazy;
        }

        /// Reset the lazy value of the current node
        tree[node].lazy = 0;
    }

}

/// Function to update the grades in a given range
void updateRange(int node, int start, int end, int l, int r, int bonus)
{
    propagateLazy(node, start, end);

    if (start > r || end < l)
        return;

    if (start >= l && end <= r)
    {
        /// The current node's range is completely within the update range
        /// Update the grade and propagate the bonus value to the children nodes
        tree[node].grade += bonus;

        if (start != end)
        {
            tree[2 * node].lazy += bonus;
            tree[2 * node + 1].lazy += bonus;
        }
        return;
    }

    int mid = (start + end) / 2;
    /// Partial overlap, update the left and right subtrees
    updateRange(2 * node, start, mid, l, r, bonus);
    updateRange(2 * node + 1, mid + 1, end, l, r, bonus);

    /// Update the current node with the maximum grade of its children
    tree[node].grade = max(tree[2 * node].grade, tree[2 * node + 1].grade);
}

/// Function to query the maximum grade in a given range
int queryMaxGrade(int node, int start, int end, int l, int r)
{

    propagateLazy(node, start, end);

    if (start > r || end < l)
        return 0;

    if (start >= l && end <= r)
        return tree[node].grade;

    int mid = (start + end) / 2;
    /// Partial overlap, query the maximum grade from the left and right subtrees
    int left = queryMaxGrade(2 * node, start, mid, l, r);
    int right = queryMaxGrade(2 * node + 1, mid + 1, end, l, r);

    return max(left, right);
}

int main()
{
    int N, T;
    ifstream f1("mit.in");
    ofstream f2("mit.out");
    f1 >> N >> T;

    for (int i = 1; i <= N; i++)
    {
        f1 >> grades[i];
    }

    /// Build the interval tree
    buildTree(1, 1, N);

    while (T--)
    {
        int op, A, B;
        f1 >> op >> A >> B;

        if (op == 1)
        {
            int maxGrade = queryMaxGrade(1, 1, N, A, B);
            f2 << maxGrade << endl;
        }
        else if (op == 2)
        {
            int X;
            f1 >> X;
            updateRange(1, 1, N, A, B, X);
        }
    }

    f1.close();
    f2.close();
    return 0;
}
