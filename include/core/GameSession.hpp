#pragma once
#include <utility>

struct GameSession {
    int SCORE = 0;
    int COINS = 0;
    std::pair<int,int> WORLD = {1, 1};
    int TIMELEFT = 400;
    int LIVES = 3;
};