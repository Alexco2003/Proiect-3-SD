#include <fstream>
#include <unordered_map>
using namespace std;

int main()
{
    ifstream f1("loto.in");
    ofstream f2("loto.out");

    int N, v[101];
    long long S;
    unordered_map<long long, pair<int, pair<int, int>>> dict;

    f1 >> N >> S;
    for (int i = 0; i < N; i++)
    {
        f1 >> v[i];
    }

    /// Generate all possible sums of triplets and store them in the unordered_map
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                long long sum = v[i] + v[j] + v[k];
                dict[sum] = make_pair(i, make_pair(j, k));
            }
        }
    }

    /// Search for a triplet whose sum, when subtracted from the target sum, matches a sum in the unordered_map
    bool found = false;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                long long sum = v[i] + v[j] + v[k];
                if (dict.find(S - sum) != dict.end())
                {
                    /// If a match is found, retrieve the triplet from the unordered_map and output the result
                    auto p = dict[S - sum];
                    f2 << v[i] << " " << v[j] << " " << v[k] << " "<< v[p.first] << " " << v[p.second.first] << " "<< v[p.second.second];
                    found = true;
                    break;
                }
            }
            if (found)
            {
                break;
            }
        }
        if (found)
        {
            break;
        }
    }

    /// If no matching triplet is found, output -1
    if (!found)
    {
        f2 << "-1";
    }

    f1.close();
    f2.close();
    return 0;
}
