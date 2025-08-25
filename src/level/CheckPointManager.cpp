#include<level/Level.hpp>
#include<diy_functions/read.h>

CheckPointManager::CheckPointManager(std::string filename, SubLevel* subLevel) :
    subLevel(subLevel) {
    ifstream inp(filename);

    int numPoints;
    readFromFile(inp, filename, numPoints);

    pivots.resize(numPoints);
    for(int i = 0; i < numPoints; i++) {
        readFromFile(inp, filename, pivots[i].x, pivots[i].y);
    }

    sort(pivots.begin(), pivots.end(), [](Vector2& a, Vector2& b){
        return a.x < b.x;
    });
    inp.close();
}

void CheckPointManager::update(void) {
    // Find rightmost pivot
    int L = rightmostPivot + 1, R = (int)pivots.size() - 1;
    while(L <= R) {
        int M = L + R >> 1;
        if(pivots[M].x <= subLevel->player->getPos().x) {
            rightmostPivot = M;
            L = M + 1;
        } else {
            R = M - 1;
        }
    }
}