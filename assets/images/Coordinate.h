#pragma once
#include"raylib.h"
#include<vector>

using namespace std;

namespace Character {
    namespace Small {
        const Rectangle Duck = {0, 16, 15, 14};
        namespace Left {
            const Rectangle Jump = {29, 0, 17, 16};
            const Rectangle Brake = {331, 0, 14, 16};
            const Rectangle Run1 = {89, 0, 16, 16};
            const Rectangle Run2 = {121, 0, 12, 16};
            const Rectangle Run3 = {150, 0, 14, 15};
            const Rectangle Idle = {181, 0, 13, 16};
        };
        namespace Right {
            const Rectangle Jump = {359, 0, 17, 16};
            const Rectangle Brake = {60, 0, 14, 16};
            const Rectangle Run1 = {300, 0, 16, 16};
            const Rectangle Run2 = {272, 0, 12, 16};
            const Rectangle Run3 = {241, 0, 14, 15};
            const Rectangle Idle = {211, 0, 13, 16};
        };
        const vector<Rectangle> frames = {
            Duck, 
            Left::Jump, 
            Left::Brake, 
            Left::Run1, 
            Left::Run2, 
            Left::Run3, 
            Left::Idle,
            Right::Jump, 
            Right::Brake, 
            Right::Run1, 
            Right::Run2, 
            Right::Run3, 
            Right::Idle
        };
    };
    namespace Super {
        namespace Left {
            const Rectangle Duck = {0, 57, 16, 22};
            const Rectangle Jump = {30, 52, 16, 32};
            const Rectangle Brake = {60, 52, 16, 32};
            const Rectangle Run1 = {90, 53, 16, 30};
            const Rectangle Run2 = {121, 52, 14, 31};
            const Rectangle Run3 = {150, 52, 16, 32};
            const Rectangle Idle = {180, 52, 16, 32};
        };
        namespace Right {
            const Rectangle Duck = {389, 57, 16, 22 };
            const Rectangle Jump = {359, 52, 16, 32};
            const Rectangle Brake = {329, 52, 16, 32};
            const Rectangle Run1 = {299, 53, 16, 30};
            const Rectangle Run2 = {270, 52, 14, 31};
            const Rectangle Run3 = {239, 52, 16, 32};
            const Rectangle Idle = {209, 52, 16, 32};
        };
        const vector<Rectangle> frames = {
            Left::Duck, 
            Left::Jump, 
            Left::Brake, 
            Left::Run1, 
            Left::Run2, 
            Left::Run3, 
            Left::Idle,
            Right::Duck, 
            Right::Jump, 
            Right::Brake, 
            Right::Run1, 
            Right::Run2, 
            Right::Run3, 
            Right::Idle
        };
    };
    namespace Fire {
        namespace Left {
            const Rectangle Duck = {0, 127, 16, 22};
            const Rectangle Jump = {27, 122, 16, 32};
            const Rectangle Brake = {52, 122, 16, 32};
            const Rectangle Throw = {77, 123, 16, 30};
            const Rectangle Run1 = {102, 123, 16, 30}; 
            const Rectangle Run2 = {128, 122, 14, 31};
            const Rectangle Run3 = {152, 122, 16, 32};
            const Rectangle Idle = {180, 122, 16, 32};
        };
        namespace Right {
            const Rectangle Duck = {389, 127, 16, 22};
            const Rectangle Jump = {362, 122, 16, 32};
            const Rectangle Brake = {337, 122, 16, 32};
            const Rectangle Throw = {312, 123, 16, 30};
            const Rectangle Run1 = {287, 123, 16, 30}; 
            const Rectangle Run2 = {263, 122, 14, 31};
            const Rectangle Run3 = {237, 122, 16, 32};
            const Rectangle Idle = {209, 122, 16, 32};
        };
        const vector<Rectangle> frames = {
            Left::Duck, 
            Left::Jump, 
            Left::Brake, 
            Left::Throw, 
            Left::Run1, 
            Left::Run2, 
            Left::Run3, 
            Left::Idle,
            Right::Duck, 
            Right::Jump, 
            Right::Brake, 
            Right::Throw, 
            Right::Run1, 
            Right::Run2, 
            Right::Run3, 
            Right::Idle
        };
    };
};