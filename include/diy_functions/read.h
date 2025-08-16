#include<iostream>
#include<fstream>
#include<string>

template<typename T>
void readFromFile(std::ifstream& inp, std::string& filename, T& x) {
    inp >> x;
    if(inp.fail()) {
        throw std::runtime_error("Failed to read value from file: " + filename);
    }
}

template<typename T, typename... Args>
void readFromFile(std::ifstream& inp, std::string& filename, T& x, Args&... a) {
    inp >> x;
    if(inp.fail()) {
        throw std::runtime_error("Failed to read value from file: " + filename);
    }
    readFromFile(inp, filename, a...);
}