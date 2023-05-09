#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream f1 ("pariuri.in");
    ofstream f2 ("pariuri.out");

    /// Read the number of test cases
    int N;
    f1 >> N;

    /// Create an unordered_map to store the key-value pairs
    unordered_map<int, int> dict;

    /// Process each test case
    for (int i = 1; i <= N; i++)
    {
        /// Read the number of pairs for the current test case
        int M;
        f1 >> M;

        /// Process each pair
        for (int j = 1; j <= M; j++)
        {
            /// Read the key and value of the pair
            int key, value;
            f1 >> key;
            f1 >> value;

            /// Update the value of the key in the unordered_map
            if (dict.count(key) != 0)
            {
                dict[key] = dict[key] + value;
            }
            else
            {
                dict[key] = value;
            }
        }
    }

    /// Output the size of the unordered_map (number of unique keys)
    f2 << dict.size() << endl;

    /// Output the key-value pairs in the unordered_map
    for (auto i : dict)
    {
        f2 << i.first << " " << i.second << " ";
    }

    f1.close();
    f2.close();
    return 0;
}
