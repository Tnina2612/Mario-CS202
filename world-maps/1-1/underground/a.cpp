#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

const char* c = "./blocks.txt";
int height, width;
vector<vector<string>> s;

int main(void) {
    ifstream inp(c);
    inp >> height >> width;
    s.resize(height);
    for(int i = 0; i < height; i++) {
        s[i].resize(width);
        for(int j = 0; j < width; j++) {
            inp >> s[i][j];
        }
    }
    inp.close();

    ofstream out(c);
    out << left << setw(16) << height << left << setw(16) << width << '\n';
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            out << left << setw(16) << s[i][j];
        }
        out << '\n';
    }
    out.close();
}