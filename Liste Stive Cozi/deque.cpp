#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f1("deque.in");
    ofstream f2("deque.out");

    int N, K;
    f1 >> N >> K;

    int A[N], d[N], front = 0, back = 0;
    long long S = 0;

    for (int i = 0; i < N; i++)
    {
        f1 >> A[i];

        /// Remove elements from the back of the deque that are greater than or equal to A[i]
        while (back > front && A[d[back-1]] >= A[i])
        {
            back--;
        }

        /// Add current index to the back of the deque
        d[back++] = i;

        /// Remove the front element if it no longer belongs to the current sequence
        if (d[front] <= i-K)
        {
            front++;
        }

        /// Add the minimum to the solution if we have K elements in the deque
        if (i >= K-1)
        {
            S += A[d[front]];
        }
    }

    f2 << S;

    f1.close();
    f2.close();
    return 0;
}
