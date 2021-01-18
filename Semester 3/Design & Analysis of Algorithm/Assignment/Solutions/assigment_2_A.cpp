#include <bits/stdc++.h>

using namespace std;

string print( string X, string Y)
{
    int m = X.length();
    int n = Y.length();

    int key[m+1][n+1];

    for(int i = 0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
        {
            if(i==0)
                key[i][j] = j;
            else if(j==0)
                key[i][j] = i;
            else if(X[i-1] == Y[j-1])
                key[i][j] = 1 + key[i-1][j-1];
            else
                key[i][j] = 1 + min(key[i-1][j], key[i][j-1]);
        }
    }

    int index = key[m][n];

    string sequence;

    int i = m , j = n ;
    while ( i > 0 && j > 0)
    {

        if ( X[i-1] == Y[j-1] )
        {
            sequence.push_back(X[i-1]);

            i--, j--, index--;
        }

        else if (key[i-1][j] > key[i][j-1])
        {
            sequence.push_back(Y[j-1]);

            j--; index--;
        }

        else
        {
            sequence.push_back(X[i-1]);

            i--; index--;
        }
    }

    while ( i>0)
    {
        sequence.push_back(X[i-1]);
        i--, index--;
    }

    while(j>0)
    {
        sequence.push_back(Y[j-1]);
        j--; index--;
    }

    reverse(sequence.begin(), sequence.end());
    return sequence;

}


int main()
{
    string X = "MATE";
    string Y = "ACHES";
   // cout << "Please input the first string.";
   // cin >> X;
   // cout << "Please input the second string";
   // cin >> Y;
    cout << print(X,Y);

    return 0;
}


