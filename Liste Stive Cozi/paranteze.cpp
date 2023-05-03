#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

int main()
{
    ifstream f1("paranteze.in");
    ofstream f2("paranteze.out");
    int n;
    f1 >> n;
    f1.ignore();

    int v[n+1]= {0}; /// initialize an array to store whether each character is part of a correct subsequence
    stack <int> s; /// initialize a stack to store indexes of opening brackets
    char cuv[n+1];
    f1.getline(cuv, n+1);

    /// iterate over the sequence and process each character
    for (int i=0; i<n; i++)
    {
        char temp='W'; /// initialize a temporary variable to store the matching bracket type

        /// check which type of bracket the current character is and set the matching bracket type
        if(cuv[i] == '}')
            temp = '{';
        if(cuv[i] == ']')
            temp = '[';
        if(cuv[i] == ')')
            temp = '(';

        if(temp=='W') /// if the current character is an opening bracket, push its index onto the stack
        {
            s.push(i);
        }
        else /// if the current character is a closing bracket, try to match it with the last opening bracket on the stack
        {
            if(s.empty()==false && cuv[s.top()]==temp) /// if the brackets match, mark both as part of a correct subsequence
            {
                v[i]=1;
                v[s.top()]=1;
                s.pop(); /// pop the last opening bracket from the stack
            }
            else /// if the brackets don't match, push the current closing bracket index onto the stack
            {
                s.push(i);
            }
        }

    }

    /// find the length of the longest correct subsequence
    int mx1=0,mx2=0;
    for (int i=0; i<n; i++)
        if(v[i]==1) /// if the current character is part of a correct subsequence, increment the counter
        {
            mx1++;
            if(mx2<mx1) /// if the current counter is greater than the previous maximum, update the maximum
                mx2=mx1;
        }
        else /// if the current character is not part of a correct subsequence, reset the counter
        {
            mx1=0;
        }

    f2<<mx2;
}
