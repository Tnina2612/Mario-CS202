#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

string filename;

int main(void) {
    cin >> filename;

    int r, c;
    vector<vector<string>> table;

    ifstream inp(filename);
    if(inp.is_open() == false) throw runtime_error("Cannot find file: " + filename);
    inp >> r >> c;
    table.resize(r);
    for(int i = 0; i < r; i++) {
        table[i].resize(c);
        for(int j = 0; j < c; j++) {
            inp >> table[i][j];
        }
    }
    inp.close();

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(table[i][j] == "G1") table[i][j] = "ground1";
            if(table[i][j] == "G2") table[i][j] = "brick1";
            if(table[i][j] == "G3" || table[i][j] == "G13") table[i][j] = "brick2";
            if(table[i][j] == "G9") table[i][j] = "ground2";
            if(table[i][j] == "C1") table[i][j] = "coin1";
            if(table[i][j] == "C2") table[i][j] = "coin2";
            if(table[i][j] == "C3") table[i][j] = "coin3";
        }
    }

    ofstream out(filename);
    out << r << ' ' << c << '\n';
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            out << table[i][j] << "\t\t";
        }
        out << '\n';
    }
    out.close();

    return 0;
}