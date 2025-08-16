#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

int width, height;
vector<vector<string>> d;

const char* filename = "background.txt";

int main() {
    std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Failed to open " + string(filename) + " for reading\n";
            return 1;
        }
        infile >> height >> width;
        d.resize(height);
        for(int i = 0; i < height; i++) {
            d[i].resize(width);
            for(int j = 0; j < width; j++) {
                infile >> d[i][j];
            }
        }
    infile.close();

    ofstream out(filename);
        if (!out) {
            std::cerr << "Failed to open " + string(filename) + " for writing\n";
            return 1;
        }
        out << left << setw(20) << height << setw(20) << width << '\n';
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                out << left << setw(20) << d[i][j];
            }
            out << '\n';
        }

        int remainingDigit = width;
        int divisor = 1;
        while(remainingDigit > 0) {
            for(int i = 0; i < width; i++) {
                int digit = i / divisor;
                digit %= 10;
                out << left << setw(20) << digit;
            }
            out << '\n';
            remainingDigit /= 10;
            divisor *= 10;
        }
    out.close();
}