#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



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
 
void findPairs(string &s, vector<vector<int>>&OPT, int x, int y, int n, vector<pair<int,int>> &base_pairs){
	if(x > n || y < 1){
		return;
	}
	if(OPT[x][y] == OPT[x][y-1]){
		findPairs(s,OPT,x,y-1,n, base_pairs);
	}
	else{
		for(int t = x; t<y-4;t++){
            if(1+ OPT[x][t-1] +OPT[t+1][y-1] == OPT[x][y]){
                if(checkPair(s,t,y)){
                    base_pairs.push_back({t,y});
                    findPairs(s,OPT,x,t-1,n,base_pairs);
                    findPairs(s,OPT,t+1,y-1,n,base_pairs);
                    break;
                }
            }
		}
	}


}
 
int main(int argc, char* argv[]){

    string s;
    ifstream f;
    f.open(argv[1]);
    if (!f){
        cerr << "File Not Found:" << argv[0] << endl;
        return 0;
    }
    vector<pair<int,int>>base_pairs;

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
    findPairs(s, OPT, 1, n, n, base_pairs);
	for(auto i:base_pairs){
		cout<<s[i.first]<<"("<<i.first<<")"<<" <---> "<<s[i.second]<<"("<<i.second<<")"<<endl;

	}
    return 0;
}