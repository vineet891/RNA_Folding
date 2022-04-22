#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
void print_matrix(vector<vector<int>> &OPT, int k, int i, int j)
{   
    cout << "*********************" << endl;
    cout << "Matrix when k = " << k << " and i = " << i << " and j = " << j << endl;
    int n = OPT.size() - 1;
    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << OPT[i][j] << " ";
        }
        cout << endl;
    }
 
    cout << "*********************" << endl;
}
 
bool correct_pair(string &s, int i, int j)
{
    if (s[i] == 'A' && s[j] == 'U')
        return true;
    if (s[i] == 'U' && s[j] == 'A')
        return true;
    if (s[i] == 'C' && s[j] == 'G')
        return true;
    if (s[i] == 'G' && s[j] == 'C')
        return true;
    return false;
} 
 
 
int main(int argc, char* argv[])
{

    string s;
    ifstream f;
    f.open(argv[1]);
    if (!f)
    {
        cerr << "File Not Found:" << argv[0] << endl;
        return 0;
    }

    f >> s;
    //               123456789
    // cout<<"Enter RNA Sequence: "<<endl;
    // string s;
    // cin>>s;
    // // string s = "ACAUGAUGGCCAUGU";
    cout<<"Input RNA Sequence: "<<s<<endl;
    int n = s.length();
    vector<vector<int>> OPT(n + 1, vector<int>(n + 1, 0));
 
    // print_matrix(OPT);
 
    for (int k = 5; k < n; k++)
    {
 
        for (int i = 1; i <= n - k; i++)
        {
            int j = i + k;
 
            int pairs = 0;
            for (int t = 1; t <= j - 5; t++)
            {
                if(correct_pair(s,j-1, t-1))
                {
                    pairs = max(1 + OPT[i][t - 1] + OPT[t + 1][j - 1], pairs);
                    // std::cout << "othershit = " << othershit << " at t = " << t << std::endl;
                }
                
            }
            OPT[i][j] = max(OPT[i][j - 1], pairs);
            // print_matrix(OPT, k, i, j);
        }
    }
 
    cout << "Number of Base Pairs: "<< OPT[1][n] << endl;
    return 0;
}