/**
@file main.cpp
*/

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/// Function to check if two characters from a sequence
/// string form a base pair.
/// @param s pointer to a string
/// @param i index of character
/// @param j index of character
bool checkPair(string &s, int i, int j){
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
 
/// Function which finds the base pairs for a
/// given RNA sequence
/// @param s Sequence string.
/// @param OPT 2D DP matrix.
/// @param basePairs Vector which stores the pair of bases.

void findPairs(string &s, vector<vector<int>>&OPT, int x, int y, int n, vector<pair<int,int>> &basePairs){
	if(x > n || y < 1){
		return;
	}
	if(OPT[x][y] == OPT[x][y-1]){
		findPairs(s,OPT,x,y-1,n, basePairs);
	}
	else{
		for(int t = x; t<y-4;t++){
            if(1+ OPT[x][t-1] +OPT[t+1][y-1] == OPT[x][y]){
                if(checkPair(s,t,y)){
                    basePairs.push_back({t,y});
                    findPairs(s,OPT,x,t-1,n,basePairs);
                    findPairs(s,OPT,t+1,y-1,n,basePairs);
                    break;
                }
            }
		}
	}


}

/// Takes the input sequence, performs DP to get the total number of base pairs.
/// Calls findPairs to retrieve the pairs.
 
int main(int argc, char* argv[]){

    string s;
    ifstream f;
    f.open(argv[1]);
    if (!f){
        cerr << "File Not Found:" << argv[0] << endl;
        return 0;
    }
    vector<pair<int,int>>basePairs;

    f >> s;
    cout<<"\nInput RNA Sequence: "<<s<<endl;
    s.insert(0,1,'$');
	int n = s.size();
    vector<vector<int>> OPT(n + 1, vector<int>(n + 1, 0));

 
    for (int k = 5; k < n; k++) {
        for (int i = 1; i <= n - k; i++){
            int j = i + k;
            int pairs = INT_MIN;
            for (int t = i; t <= j - 5; t++){
                if(checkPair(s,j, t)) {
                    pairs = max(1 + OPT[i][t - 1] + OPT[t + 1][j - 1], pairs);
                }
            }
            OPT[i][j] = max(OPT[i][j - 1], pairs);
        }
    }
 
    cout << "Number of Base Pairs: "<< OPT[1][n] << endl;
    cout<< "The Base Pairs are "<<endl;
    findPairs(s, OPT, 1, n, n, basePairs);
	for(auto i:basePairs){
		cout<<s[i.first]<<"("<<i.first<<")"<<" <---> "<<s[i.second]<<"("<<i.second<<")"<<endl;

	}
    return 0;
}