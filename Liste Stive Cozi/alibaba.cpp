#include <iostream>
#include <fstream>
#include <deque>
#include <string>

using namespace std;

int main()
{
    ifstream f1("alibaba.in");
    ofstream f2("alibaba.out");

    int n, k;
    string s;
    f1 >> n >> k;
    f1 >> s;

    deque<int> dq;

    for (int i=0; i<n; i++)
    {
        /// While the deque is not empty and the last element is less than the current digit
        while(!dq.empty() && dq.back()<(s[i]-'0') && k!=0)
        {
            /// Remove the last element from the deque and decrement k
            dq.pop_back();
            k--;
        }

        /// Add the current digit to the deque
        dq.push_back((s[i]-'0'));
    }

    /// If k is not zero, remove k elements from the end of the deque
    while (k!=0)
    {
        dq.pop_back();
        k--;
    }

    while (!dq.empty())
    {
        f2<<dq.front();
        dq.pop_front();
    }

    f1.close();
    f2.close();

    return 0;
}
