#include <string>
#include <iostream>
#include <vector>
using namespace std;

class RNA {
    string seq;
    vector<vector<char>> rna_pairs;

    public:
    void extract_sequences();

};