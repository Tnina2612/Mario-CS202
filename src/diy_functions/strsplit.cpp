#include<diy_functions/strsplit.h>
#include<iostream>

std::vector<std::string> strsplit(const std::string& s, char delim) {
    if(delim == ' ') {
        throw std::runtime_error("strsplit: no delimeter");
    }
    std::vector<std::string> ret;
    size_t startID = 0;
    size_t endID;
    while ((endID = s.find(delim, startID)) != std::string::npos) {
        ret.push_back(s.substr(startID, endID - startID));
        startID = endID + 1;
    }
    ret.push_back(s.substr(startID)); // Add the last token
    return ret;
}