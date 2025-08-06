#pragma once
#include"raylib.h"
#include<string>
#include<unordered_map>
#include<vector>

using namespace std;

namespace CharacterSprite {
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
            Duck,
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
            Right::Idle,
            Left::Throw, 
            Right::Throw
        };
        namespace Fireball {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Normal", {Rectangle{25.f, 150.f, 10.f, 10.f}, 
                        Rectangle{40.f, 150.f, 10.f, 10.f}, 
                        Rectangle{25.f, 165.f, 10.f, 10.f}, 
                        Rectangle{40.f, 165.f, 10.f, 10.f}}}
        };
    };
    };
};


namespace EnemySprite {
    namespace Koopa {
        namespace Map1 {
            namespace Left {
                const Rectangle WWalk1 = {90, 0, 16, 24};
                const Rectangle WWalk2 = {120, 0, 16, 23};
                const Rectangle Walk1 = {150, 0, 16, 24};
                const Rectangle Walk2 = {180, 0, 16, 23};
            };

            namespace Right {
                const Rectangle WWalk1 = {300, 0, 16, 24};
                const Rectangle WWalk2 = {270, 0, 16, 23};
                const Rectangle Walk1 = {240, 0, 16, 24};
                const Rectangle Walk2 = {210, 0, 16, 23};
            };

            namespace Shell {
                const Rectangle Move = {330, 4, 16, 15};
                const Rectangle Idle = {360, 5, 16, 14};
            };
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"LWWalk", {Left::WWalk1, Left::WWalk2}},
                {"RWWalk", {Right::WWalk1, Right::WWalk2}},
                {"RWalk", {Right::Walk1, Right::Walk2}},
                {"LWalk", {Left::Walk1, Left::Walk2}},
                {"Shell1", {Shell::Move}},
                {"Shell2", {Shell::Idle}}
            };

        };
        namespace Map2 {
            namespace Left {
                const Rectangle WWalk1 = {90, 60, 16, 24};
                const Rectangle WWalk2 = {120, 60, 16, 23};
                const Rectangle Walk1 = {150, 60, 16, 24};
                const Rectangle Walk2 = {180, 60, 16, 23};
            };

            namespace Right {
                const Rectangle WWalk1 = {300, 60, 16, 24};
                const Rectangle WWalk2 = {270, 60, 16, 23};
                const Rectangle Walk1 = {240, 60, 16, 24};
                const Rectangle Walk2 = {210, 60, 16, 23};
            };

            namespace Shell {
                const Rectangle Move = {330, 64, 16, 15};
                const Rectangle Idle = {360, 65, 16, 14};
            };
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"LWWalk", {Left::WWalk1, Left::WWalk2}},
                {"RWWalk", {Right::WWalk1, Right::WWalk2}},
                {"RWalk", {Right::Walk1, Right::Walk2}},
                {"LWalk", {Left::Walk1, Left::Walk2}},
                {"Shell1", {Shell::Move}},
                {"Shell2", {Shell::Idle}}
            };
        };
        namespace Map3 {
            namespace Left {
                const Rectangle WWalk1 = {90, 30, 16, 24};
                const Rectangle WWalk2 = {120, 30, 16, 23};
                const Rectangle Walk1 = {150, 30, 16, 24};
                const Rectangle Walk2 = {180, 30, 16, 23};
            };

            namespace Right {
                const Rectangle WWalk1 = {300, 30, 16, 24};
                const Rectangle WWalk2 = {270, 30, 16, 23};
                const Rectangle Walk1 = {240, 30, 16, 24};
                const Rectangle Walk2 = {210, 30, 16, 23};
            };

            namespace Shell {
                const Rectangle Move = {330, 34, 16, 15};
                const Rectangle Idle = {360, 35, 16, 14};
            };
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"LWWalk", {Left::WWalk1, Left::WWalk2}},
                {"RWWalk", {Right::WWalk1, Right::WWalk2}},
                {"RWalk", {Right::Walk1, Right::Walk2}},
                {"LWalk", {Left::Walk1, Left::Walk2}},
                {"Shell1", {Shell::Move}},
                {"Shell2", {Shell::Idle}}
            };
        };
    }

    namespace Goomba {
        namespace Map1 {
            const Rectangle Leftfoot = {0, 4, 16, 16};
            const Rectangle Rightfoot = {30, 4, 16, 16};
            const Rectangle Dead = {60, 8, 16, 8};
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"Walk", {Leftfoot, Rightfoot}},
                {"Dead", {Dead}}
            };
        };
        namespace Map2 {
            const Rectangle Leftfoot = {0, 34, 16, 16};
            const Rectangle Rightfoot = {30, 34, 16, 16};
            const Rectangle Dead = {60, 38, 16, 8};
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"Walk", {Leftfoot, Rightfoot}},
                {"Dead", {Dead}}
            };
        };
        namespace Map3 {
            const Rectangle Leftfoot = {0, 64, 16, 16};
            const Rectangle Rightfoot = {30, 64, 16, 16};
            const Rectangle Dead = {60, 68, 16, 8};
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"Walk", {Leftfoot, Rightfoot}},
                {"Dead", {Dead}}
            };
        };
    };
    
    namespace PiranhaPlant {
        namespace Map2 {
            const Rectangle Close = {390, 60, 16, 24};
            const Rectangle Open = {420, 60, 16, 23};
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"Walk", {Close, Open}}
            };
        };
        namespace Map3 {
            const Rectangle Close = {390, 30, 16, 24};
            const Rectangle Open = {420, 30, 16, 23};            
            const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
                {"Walk", {Close, Open}}
            };
        };

    };

    namespace Podoboo {
        const Rectangle Down = {0.f, 150.f, 16.f, 16.f};
        const Rectangle Up = {60.f, 150.f, 16.f, 16.f};
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Up", {Up}},
            {"Down", {Down}}
        };
    };
    namespace Firebar {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Normal", {Rectangle{25.f, 150.f, 10.f, 10.f}, 
                        Rectangle{40.f, 150.f, 10.f, 10.f}, 
                        Rectangle{25.f, 165.f, 10.f, 10.f}, 
                        Rectangle{40.f, 165.f, 10.f, 10.f}}}
        };
    };
    namespace Bowser {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"LBreath", {Rectangle{0.f, 210.f, 35.f, 35.f}, 
                        Rectangle{40.f, 210.f, 35.f, 35.f}}},
            {"LIdle", {Rectangle{80.f, 210.f, 35.f, 35.f}, 
                        Rectangle{120.f, 210.f, 35.f, 35.f}}},
            {"RIdle", {Rectangle{160.f, 210.f, 35.f, 35.f}, 
                        Rectangle{200.f, 210.f, 35.f, 35.f}}},
            {"RBreath", {Rectangle{240.f, 210.f, 35.f, 35.f}, 
                        Rectangle{280.f, 210.f, 35.f, 35.f}}}
        };
    }
    namespace Fireball {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Left", {Rectangle{100.f, 250.f, 25.f, 10.f}, 
                        Rectangle{130.f, 250.f, 25.f, 10.f}}},
            {"Right", {Rectangle{160.f, 250.f, 25.f, 10.f}, 
                        Rectangle{190.f, 250.f, 25.f, 10.f}}}
        };
    }
};

namespace ItemSprite
{
    //Line 1
    const Rectangle BLOCK_QUESTION =          {4, 4, 16, 16};
    const Rectangle BLOCK_QUESTION_FLASHING = {34, 4, 16, 16};
    const Rectangle BLOCK_QUESTION_USED =     {64, 4, 16, 16};
    const vector <Rectangle> QUESTIONBLOCK = {
        {4, 4, 16, 16},
        {34, 4, 16, 16},
        {64, 4, 16, 16}
    };
    const Rectangle SPRINGBOARD_EXTENDED =    {94, 0, 16, 24};
    const Rectangle SPRINGBOARD =             {124, 4, 16, 16};
    const Rectangle SPRINGBOARD_COMPRESSED =  {154, 8, 16, 8};
    const vector <Rectangle> SPRINGBOARD = {
        {94, 0, 16, 24},
        {124, 4, 16, 16},
        {154, 8, 16, 8}
    };
    const Rectangle BEANSTALK_FRAME_1 =       {188, 7, 8, 9};
    const Rectangle BEANSTALK_FRAME_2 =       {215, 4, 14, 16};
    const vector <Rectangle> BEANSTALK = {
        {188, 7, 8, 9},
        {215, 4, 14, 16}
    };  
    const Rectangle CHAR_TOAD =               {244, 0, 16, 24};

    //Line 2
    const Rectangle PLATFORM_MOVING_3 = {0, 38, 24, 8};
    const Rectangle PLATFORM_MOVING_4 = {26, 38, 32, 8};
    const Rectangle PLATFORM_MOVING_6 = {63, 38, 48, 8};
    const Rectangle COINS =             {123, 38, 48, 8};
    const Rectangle MUSHROOM_SUPER =    {184, 34, 16, 16};
    const Rectangle MUSHROOM_ONE_UP =   {214, 34, 16, 16};

    //Line 3
    const Rectangle FIRE_FLOWER_ANIMATION_1_FRAME_1 = {4, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_1_FRAME_2 = {34, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_1_FRAME_3 = {64, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_1_FRAME_4 = {94, 64, 16, 16};
    const vector <Rectangle> FIRE_FLOWER_1 = {
        {4, 64, 16, 16},
        {34, 64, 16, 16},
        {64, 64, 16, 16},
        {94, 64, 16, 16}
    };
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_1 = {124, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_2 = {154, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_3 = {184, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_4 = {214, 64, 16, 16};
    const vector <Rectangle> FIRE_FLOWER_2 = {
        {124, 64, 16, 16},
        {154, 64, 16, 16},
        {184, 64, 16, 16},
        {214, 64, 16, 16}
    };

    //Line 4
    const Rectangle SUPER_STAR_FRAME_1 = {5, 94, 14, 16};
    const Rectangle SUPER_STAR_FRAME_2 = {35, 94, 14, 16};
    const Rectangle SUPER_STAR_FRAME_3 = {65, 94, 14, 16};
    const Rectangle SUPER_STAR_FRAME_4 = {95, 94, 14, 16};
    const vector <Rectangle> SUPER_STAR = {
        {5, 94, 14, 16},
        {35, 94, 14, 16},
        {65, 94, 14, 16},
        {95, 94, 14, 16}
    };
    const Rectangle COIN_SPIN_FRAME_1 =  {128, 95, 8, 14};
    const Rectangle COIN_SPIN_FRAME_2 =  {160, 95, 4, 14};
    const Rectangle COIN_SPIN_FRAME_3 =  {191, 95, 1, 14};
    const Rectangle COIN_SPIN_FRAME_4 =  {220, 95, 4, 14};
    const vector <Rectangle> COIN_SPIN = {
        {128, 95, 8, 14},
        {160, 95, 4, 14},
        {191, 95, 1, 14},
        {220, 95, 4, 14}
    };
    const Rectangle PRINCESS_PEACH =     {245, 90, 14,24};
    
} 
