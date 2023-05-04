#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

int main()
{

    ifstream f1 ("vila2.in");
    ofstream f2 ("vila2.out");
    int n, k;
    f1 >> n >> k;
    k=k+1;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        f1 >> v[i];
    }

    int maxDiff = 0;
    deque<int> dmax, dmin;

    /// Initialize the queues with the first k elements
    for (int i = 0; i < k; i++)
    {
        while (!dmax.empty() && v[i] >= v[dmax.back()])
        {
            dmax.pop_back();
        }
        dmax.push_back(i);
        while (!dmin.empty() && v[i] <= v[dmin.back()])
        {
            dmin.pop_back();
        }
        dmin.push_back(i);
    }

    /// Process the remaining elements
    for (int i = k; i < n; i++)
    {
        /// Compute the maximum and minimum of the current subsequence
        int diff = v[dmax.front()] - v[dmin.front()];
        if (diff > maxDiff)
        {
            maxDiff = diff;
        }

        /// Remove elements outside the current subsequence
        if (!dmax.empty() && dmax.front() <= i - k)
        {
            dmax.pop_front();
        }
        if (!dmin.empty() && dmin.front() <= i - k)
        {
            dmin.pop_front();
        }

        /// Update the maximum and minimum queues with the current element
        while (!dmax.empty() && v[i] >= v[dmax.back()])
        {
            dmax.pop_back();
        }
        dmax.push_back(i);
        while (!dmin.empty() && v[i] <= v[dmin.back()])
        {
            dmin.pop_back();
        }
        dmin.push_back(i);
    }

    /// Compute the maximum and minimum of the last subsequence
    int diff = v[dmax.front()] - v[dmin.front()];
    if (diff > maxDiff)
    {
        maxDiff = diff;
    }

    f2 << maxDiff << endl;

    return 0;
}
