#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> sparse_table; /// Sparse table for RMQ
vector<int> log_table; /// Logarithm lookup table
vector<int> arr; /// Input vector

/// Function to build the sparse table
void buildSparseTable()
{
    int N = arr.size();
    int logN = log_table[N];

    sparse_table.resize(N, vector<int>(logN + 1));

    /// Initialize the sparse table with the input array values
    for (int i = 0; i < N; i++)
    {
        sparse_table[i][0] = arr[i];
    }

    /// Build the sparse table using dynamic programming
    for (int j = 1; (1 << j) <= N; j++)
    {
        for (int i = 0; i + (1 << j) - 1 < N; i++)
        {
            int l = 1 << (j - 1);
            sparse_table[i][j] = min(sparse_table[i][j - 1], sparse_table[i + l][j - 1]);
        }
    }
}

/// Function to query the minimum element in a given range
int queryMin(int left, int right)
{
    int length = right - left + 1;
    int logLength = log_table[length];

    int minVal = min(sparse_table[left][logLength], sparse_table[right - (1 << logLength) + 1][logLength]);

    return minVal;
}

int main()
{
    int N, M;
    ifstream f1("rmq.in");
    ofstream f2("rmq.out");

    f1 >> N >> M;

    arr.resize(N);
    for (int i = 0; i < N; ++i)
    {
        f1 >> arr[i];
    }

    /// Precompute the logarithm lookup table
    log_table.resize(N + 1);
    log_table[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        log_table[i] = log_table[i / 2] + 1;
    }

    /// Build the sparse table
    buildSparseTable();

    /// Process the queries
    for (int i = 0; i < M; ++i)
    {
        int x, y;
        f1 >> x >> y;

        /// Find the minimum element in the interval [x, y]
        int minVal = queryMin(x - 1, y - 1);
        f2 << minVal << endl;
    }

    f1.close();
    f2.close();
    return 0;
}
