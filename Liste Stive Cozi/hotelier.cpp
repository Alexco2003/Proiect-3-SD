#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int v[10]= {}; /// Initialize all rooms as empty
    for (int i=0; i<n; i++)
    {
        if (s[i]=='L') /// If a customer arrives from the left entrance
        {
            /// Find the first empty room from the left and assign it to the customer
            for (int j=0; j<10; j++)
                if (v[j]==0)
                {
                    v[j]=1;
                    break;
                }
            continue;
        }
        if (s[i]=='R') /// If a customer arrives from the right entrance
        {
            /// Find the first empty room from the right and assign it to the customer
            for (int j=9; j>=0; j--)
                if (v[j]==0)
                {
                    v[j]=1;
                    break;
                }
            continue;
        }

        v[s[i]-'0']=0; /// The customer in room x (0, 1, ..., 9 respectively) leaves, so mark the room as empty

    }

    for (int i=0; i<10; i++) /// Print the status of all the rooms
        cout<<v[i];

    return 0;
}
