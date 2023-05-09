#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int main()
{
    ifstream f1("muzica.in");
    ofstream f2("muzica.out");

    long long N, M, A, B, C, D, E, cnt = 0;

    /// Read input values
    f1 >> N >> M;
    f1 >> A >> B >> C >> D >> E;

    /// Create an unordered set to store Vasile's songs
    unordered_set<long long> vasileSongs;

    /// Process Vasile's playlist
    for (int i = 0; i < N; i++)
    {
        long long song;
        f1 >> song;
        vasileSongs.insert(song);
    }

    if (vasileSongs.count(A) > 0)
    {
        cnt++;
        vasileSongs.erase(A);
    }
    if (vasileSongs.count(B) > 0)
    {
        cnt++;
        vasileSongs.erase(B);
    }

    /// Generate songs using the given formula and check if they are in the set
    for (int i = 3; i <= M; i++)
    {
        long long V = (C * B + D * A) % E; /// Generate the next song

        /// Check if the generated song is in the set
        if (vasileSongs.count(V) > 0)
        {
            cnt++;
            vasileSongs.erase(V);
        }
        /// Update A and B for the next iteration
        A = B;
        B = V;
    }

    /// Write the count to the output file
    f2 << cnt;

    f1.close();
    f2.close();

    return 0;
}
