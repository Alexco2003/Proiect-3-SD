#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    long long N, K;
    ifstream f1("farfurii.in");
    ofstream f2("farfurii.out");
    f1 >> N >> K;

    long long largestPlate = 0;
    while (largestPlate * (largestPlate - 1) / 2 <= K)   /// Find the size of the largest plate that can be placed on the shelf
        largestPlate++;

    vector<long long> plates(N);
    for (int i = 0; i < N; i++)
    {
        plates[i] = i + 1;   /// Fill the vector with plates in increasing order
    }

    /// Output plates before the largest plate
    for (int i = 1; i <= N - largestPlate; i++)
    {
        f2 << plates[i - 1] << " ";
    }

    long long remainingCutlery = N + K - largestPlate * (largestPlate - 1) / 2;

    f2 << remainingCutlery << " ";   /// Output the largest plate

    /// Output plates after the largest plate, excluding the remaining cutlery
    for (int i = N; i >= N - largestPlate + 1; i--)
    {
        if (i != remainingCutlery)
            f2 << plates[i - 1] << " ";
    }

    f1.close();
    f2.close();
    return 0;
}
