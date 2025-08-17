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
            const Rectangle Climb1 = {331, 30, 13, 15};
            const Rectangle Climb2 = {361, 30, 14, 16};
        };
        namespace Right {
            const Rectangle Jump = {359, 0, 17, 16};
            const Rectangle Brake = {60, 0, 14, 16};
            const Rectangle Run1 = {300, 0, 16, 16};
            const Rectangle Run2 = {272, 0, 12, 16};
            const Rectangle Run3 = {241, 0, 14, 15};
            const Rectangle Idle = {211, 0, 13, 16};
            const Rectangle Climb1 = {61, 30, 13, 15};
            const Rectangle Climb2 = {30, 30, 14, 16};
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
            Right::Idle,
            Left::Climb1,
            Left::Climb2,
            Right::Climb1,
            Right::Climb2
        };
        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"LIdle", {Left::Idle}},
            {"LJump", {Left::Jump}},
            {"LBrake", {Left::Brake}},
            {"LRun", {Left::Run1, Left::Run2, Left::Run3}},
            {"RIdle", {Right::Idle}},
            {"RJump", {Right::Jump}},
            {"RBrake", {Right::Brake}},
            {"RRun", {Right::Run1, Right::Run2, Right::Run3}},
            {"LClimb", {Left::Climb1, Left::Climb2}},
            {"RClimb", {Right::Climb1, Right::Climb2}},
            {"Duck", {Duck}},
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
            const Rectangle Climb1 = {0, 158, 15, 30};
            const Rectangle Climb2 = {28, 159, 14, 27};
        };
        namespace Right {
            const Rectangle Duck = {389, 57, 16, 22 };
            const Rectangle Jump = {359, 52, 16, 32};
            const Rectangle Brake = {329, 52, 16, 32};
            const Rectangle Run1 = {299, 53, 16, 30};
            const Rectangle Run2 = {270, 52, 14, 31};
            const Rectangle Run3 = {239, 52, 16, 32};
            const Rectangle Idle = {209, 52, 16, 32};
            const Rectangle Climb1 = {390, 158, 15, 30};
            const Rectangle Climb2 = {363, 159, 14, 27};
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
            Left::Climb1,
            Left::Climb2,
            Right::Climb1,
            Right::Climb2
        };
        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"LIdle", {Left::Idle}},
            {"LJump", {Left::Jump}},
            {"LBrake", {Left::Brake}},
            {"LRun", {Left::Run1, Left::Run2, Left::Run3}},
            {"RIdle", {Right::Idle}},
            {"RJump", {Right::Jump}},
            {"RBrake", {Right::Brake}},
            {"RRun", {Right::Run1, Right::Run2, Right::Run3}},
            {"LClimb", {Left::Climb1, Left::Climb2}},
            {"RClimb", {Right::Climb1, Right::Climb2}},
            {"Duck", {Left::Duck, Right::Duck}},
            {"LDuck", {Left::Duck}},
            {"RDuck", {Right::Duck}}
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
            const Rectangle Climb1 = {0, 88, 15, 30};
            const Rectangle Climb2 = {28, 89, 14, 27};
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
            const Rectangle Climb1 = {390, 88, 15, 30};
            const Rectangle Climb2 = {363, 89, 14, 27};
        };
        const vector<Rectangle> frames = {
            Left::Duck, //0
            Left::Jump, //1
            Left::Brake, //2
            Left::Run1, //3
            Left::Run2, //4
            Left::Run3, //5
            Left::Idle, //6
            Right::Duck, //7
            Right::Jump, //8
            Right::Brake, //9
            Right::Run1, //10
            Right::Run2, //11
            Right::Run3, //12
            Right::Idle,//13
            Left::Climb1, //14
            Left::Climb2,// 15
            Right::Climb1, //16
            Right::Climb2, //17
            Left::Throw, //18
            Right::Throw //19
        };
        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"LIdle", {Left::Idle}},
            {"LJump", {Left::Jump}},
            {"LBrake", {Left::Brake}},
            {"LRun", {Left::Run1, Left::Run2, Left::Run3}},
            {"RIdle", {Right::Idle}},
            {"RJump", {Right::Jump}},
            {"RBrake", {Right::Brake}},
            {"RRun", {Right::Run1, Right::Run2, Right::Run3}},
            {"LClimb", {Left::Climb1, Left::Climb2}},
            {"RClimb", {Right::Climb1, Right::Climb2}},
            {"LDuck", {Left::Duck}},
            {"RDuck", {Right::Duck}},
            {"LThrow", {Left::Throw}},
            {"RThrow", {Right::Throw}}
        };
        namespace FireballSprite {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Normal", {Rectangle{25.f, 150.f, 10.f, 10.f}, 
                        Rectangle{40.f, 150.f, 10.f, 10.f}, 
                        Rectangle{25.f, 165.f, 10.f, 10.f}, 
                        Rectangle{40.f, 165.f, 10.f, 10.f}}}
        };
    };
    };
};

namespace MarioInvincible {
    namespace Small {
        namespace Stance
        {
            const Rectangle s1 = {7, 292, 12, 15};
            const Rectangle s2 = {28, 292, 12, 15};
            const Rectangle s3 = {49, 292, 12, 15};
            const Rectangle s4 = {70, 292, 12, 15};
            const std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
            const Rectangle rs4 = {154, 292, 12, 15};
            const Rectangle rs3 = {133, 292, 12, 15};
            const Rectangle rs2 = {112, 292, 12, 15};
            const Rectangle rs1 = {91, 292, 12, 15};
            const std::vector<Rectangle> reverse_stance_ = {rs1, rs2, rs3, rs4};
        };
        namespace Jump
        {
            const Rectangle j1 = {175, 291, 16, 16};
            const Rectangle j2 = {196, 291, 16, 16};
            const Rectangle j3 = {217, 291, 16, 16};
            const Rectangle j4 = {238, 291, 16, 16};
            const std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
            const Rectangle rj4 = {322, 291, 16, 16};
            const Rectangle rj3 = {301, 291, 16, 16};
            const Rectangle rj2 = {280, 291, 16, 16};
            const Rectangle rj1 = {259, 291, 16, 16};
            const std::vector<Rectangle> reverse_jump_ = {rj1, rj2, rj3, rj4};
        };
        namespace Walk
        {
            const Rectangle w1 = {7, 334, 12, 15};
            const Rectangle w2 = {28, 334, 12, 15};
            const Rectangle w3 = {47, 333, 15, 16};
            const Rectangle w4 = {70, 334, 12, 15};
            const Rectangle w5 = {91, 334, 12, 15};
            const Rectangle w6 = {110, 333, 15, 16};
            const Rectangle w7 = {133, 334, 12, 15};
            const Rectangle w8 = {154, 334, 12, 15};
            const Rectangle w9 = {173, 333, 15, 16};
            const Rectangle w10 = {196, 334, 12, 15};
            const Rectangle w11 = {217, 334, 12, 15};
            const Rectangle w12 = {236, 333, 15, 16};
            const Rectangle w13 = {259, 334, 12, 15};
            const Rectangle w14 = {280, 334, 12, 15};
            const Rectangle w15 = {299, 332, 15, 16};
            const std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15};
            const Rectangle rw1 = {7, 366, 12, 15};
            const Rectangle rw2 = {28, 366, 12, 15};
            const Rectangle rw3 = {48, 365, 15, 16};
            const Rectangle rw4 = {70, 366, 12, 15};
            const Rectangle rw5 = {91, 366, 12, 15};
            const Rectangle rw6 = {111, 365, 15, 16};
            const Rectangle rw7 = {133, 366, 12, 15};
            const Rectangle rw8 = {154, 366, 12, 15};
            const Rectangle rw9 = {174, 365, 15, 16};
            const Rectangle rw10 = {196, 366, 12, 15};
            const Rectangle rw11 = {217, 366, 12, 15};
            const Rectangle rw12 = {237, 366, 15, 16};
            const Rectangle rw13 = {259, 366, 12, 15};
            const Rectangle rw14 = {280, 366, 12, 15};
            const Rectangle rw15 = {300, 364, 15, 16};
            const std::vector<Rectangle> reverse_walk_= {rw1, rw2, rw3, rw4, rw5, rw6, rw7, rw8, rw9, rw10, rw11, rw12, rw13, rw15};
        };
        namespace Climb
        {
            const Rectangle c1 = {7, 490, 13, 16};
            const Rectangle c2 = {28, 490, 13, 15};
            const Rectangle c3 = {49, 490, 13, 16};
            const Rectangle c4 = {70, 490, 13, 15};
            const Rectangle c5 = {91, 490, 13, 16};
            const Rectangle c6 = {112, 490, 13, 15};
            const Rectangle c7 = {133, 490, 13, 16};
            const Rectangle c8 = {154, 490, 13, 15};
            const std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
            const Rectangle rc1 = {174, 490, 13, 16};
            const Rectangle rc2 = {195, 490, 13, 15};
            const Rectangle rc3 = {216, 490, 13, 16};
            const Rectangle rc4 = {237, 490, 13, 15};
            const Rectangle rc5 = {258, 490, 13, 16};
            const Rectangle rc6 = {279, 490, 13, 15};
            const Rectangle rc7 = {300, 490, 13, 16};
            const Rectangle rc8 = {321, 490, 13, 15};
            const std::vector<Rectangle> reverse_climb_ = {rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8};
        };
        namespace Slide
        {
            const Rectangle s1 = {364, 448, 14, 16};
            const Rectangle s2 = {386, 448, 14, 16};
            const Rectangle s3 = {407, 448, 14, 16};
            const Rectangle s4 = {428, 448, 14, 16};
            const std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
            const Rectangle rs1 = {449, 448, 14, 16};
            const Rectangle rs2 = {470, 448, 14, 16};
            const Rectangle rs3 = {491, 448, 14, 16};
            const Rectangle rs4 = {512, 448, 14, 16};
            const std::vector<Rectangle> reverse_slide_ = {rs1, rs2, rs3, rs4};
        };

        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"Duck", Stance::stance_},
            {"RIdle", Stance::stance_},
            {"RJump", Jump::jump_},
            {"RRun", Walk::walk_},
            {"RClimb", Climb::climb_},
            {"RBrake", Slide::slide_},
            {"LIdle", Stance::reverse_stance_},
            {"LJump", Jump::reverse_jump_},
            {"LRun", Walk::reverse_walk_},
            {"LClimb", Climb::reverse_climb_},
            {"LBrake", Slide::reverse_slide_},
        };
    };

    namespace Super {
        namespace Stance
        {
            const Rectangle s1 = {558, 332, 14, 30};
            const Rectangle s2 = {579, 332, 14, 30};
            const Rectangle s3 = {600, 332, 14, 30};
            const Rectangle s4 = {621, 332, 14, 30};
            const std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
            const Rectangle rs1 = {642, 332, 14, 30};
            const Rectangle rs2 = {663, 332, 14, 30};
            const Rectangle rs3 = {684, 332, 14, 30};
            const Rectangle rs4 = {705, 332, 14, 30};
            const std::vector<Rectangle> reverse_stance_ = {rs1, rs2, rs3, rs4};
        };
        namespace Jump
        {
            const Rectangle j1 = {727, 331, 16, 30};
            const Rectangle j2 = {748, 331, 16, 30};
            const Rectangle j3 = {769, 331, 16, 30};
            const Rectangle j4 = {790, 331, 16, 30};
            const std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
            const Rectangle rj1 = {811, 331, 16, 30};
            const Rectangle rj2 = {832, 331, 16, 30};
            const Rectangle rj3 = {853, 331, 16, 30};
            const Rectangle rj4 = {874, 331, 16, 30};
            const std::vector<Rectangle> reverse_jump_ = {rj1, rj2, rj3, rj4};
        };
        namespace Crouch
        {
            const Rectangle c1 = {727, 388, 16, 22};
            const Rectangle c2 = {748, 388, 16, 22};
            const Rectangle c3 = {769, 388, 16, 22};
            const Rectangle c4 = {790, 388, 16, 22};
            const std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
            const Rectangle rc1 = {811, 388, 16, 22};
            const Rectangle rc2 = {832, 388, 16, 22};
            const Rectangle rc3 = {853, 388, 16, 22};
            const Rectangle rc4 = {874, 388, 16, 22};
            const std::vector<Rectangle> reverse_crouch_ = {rc1, rc2, rc3, rc4};
        };
        namespace Slide
        {
            const Rectangle s1 = {557, 479, 16, 31};
            const Rectangle s2 = {578, 479, 16, 31};
            const Rectangle s3 = {599, 479, 16, 31};
            const Rectangle s4 = {620, 479, 16, 31};
            const std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
            const Rectangle rs1 = {641, 479, 16, 31};
            const Rectangle rs2 = {662, 479, 16, 31};
            const Rectangle rs3 = {683, 479, 16, 31};
            const Rectangle rs4 = {704, 479, 16, 31};
            const std::vector<Rectangle> reverse_slide_ = {rs1, rs2, rs3, rs4};
        };
        namespace Climb
        {
            const Rectangle c1 = {727, 421, 16, 30};
            const Rectangle c2 = {748, 421, 16, 28};
            const Rectangle c3 = {769, 421, 16, 30};
            const Rectangle c4 = {790, 421, 16, 28};
            const Rectangle c5 = {811, 421, 16, 30};
            const Rectangle c6 = {832, 421, 16, 28};
            const Rectangle c7 = {853, 421, 16, 30};
            const Rectangle c8 = {874, 421, 16, 28};
            const std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
            const Rectangle rc1 = {896, 421, 16, 30};
            const Rectangle rc2 = {917, 421, 16, 28};
            const Rectangle rc3 = {938, 421, 16, 30};
            const Rectangle rc4 = {959, 421, 16, 28};
            const Rectangle rc5 = {980, 421, 16, 30};
            const Rectangle rc6 = {1001, 421, 16, 28};
            const Rectangle rc7 = {1022, 421, 16, 30};
            const Rectangle rc8 = {1043, 421, 16, 28};
            const std::vector<Rectangle> reverse_climb_ = {rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8};
        };
        namespace Shoot_Fire
        {
            const Rectangle s1 = {727, 464, 15, 30};
            const Rectangle s2 = {748, 464, 15, 30};
            const Rectangle s3 = {769, 464, 15, 30};
            const Rectangle s4 = {790, 464, 15, 30};
            const std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
            const Rectangle rs1 = {812, 464, 15, 30};
            const Rectangle rs2 = {833, 464, 15, 30};
            const Rectangle rs3 = {854, 464, 15, 30};
            const Rectangle rs4 = {875, 464, 15, 30};
            const std::vector<Rectangle> reverse_shoot_fire = {rs1, rs2, rs3, rs4};
        };
        namespace Walk
        {
            const Rectangle w1 = {557, 374, 15, 30};
            const Rectangle w2 = {578, 438, 16, 30};
            const Rectangle w3 = {578, 406, 16, 29};
            const Rectangle w4 = {600, 374, 14, 30};
            const Rectangle w5 = {599, 438, 16, 30};
            const Rectangle w6 = {620, 406, 16, 29};
            const Rectangle w7 = {621, 374, 14, 30};
            const Rectangle w8 = {557, 438, 16, 30};
            const Rectangle w9 = {557, 406, 16, 29};
            const Rectangle w10 = {579, 374, 14, 30};
            const Rectangle w11 = {578, 438, 16, 30};
            const Rectangle w12 = {599, 406, 16, 29};
            const Rectangle w13 = {600, 374, 14, 30};
            const Rectangle w14 = {620, 438, 16, 30};
            const Rectangle w15 = {620, 406, 16, 29};
            const std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12, w13, w14, w15};
            const Rectangle rw1 = {642, 374, 15, 30};
            const Rectangle rw2 = {641, 438, 16, 30};
            const Rectangle rw3 = {641, 406, 16, 29};
            const Rectangle rw4 = {663, 374, 14, 30};
            const Rectangle rw5 = {662, 438, 16, 30};
            const Rectangle rw6 = {662, 406, 16, 29};
            const Rectangle rw7 = {684, 374, 14, 30};
            const Rectangle rw8 = {683, 438, 16, 30};
            const Rectangle rw9 = {683, 406, 16, 29};
            const Rectangle rw10 = {705, 374, 14, 30};
            const Rectangle rw11 = {704, 438, 16, 30};
            const Rectangle rw12 = {704, 406, 16, 29};
            const Rectangle rw13 = {726, 374, 14, 30};
            const Rectangle rw14 = {725, 438, 16, 30};
            const Rectangle rw15 = {725, 406, 16, 29};
            const std::vector<Rectangle> reverse_walk_ = {rw1, rw2, rw3, rw4, rw5, rw6, rw7, rw8, rw9, rw10, rw11, rw12, rw13, rw14, rw15};
        };
        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"RIdle", Stance::stance_},
            {"RJump", Jump::jump_},
            {"RRun", Walk::walk_},
            {"RClimb", Climb::climb_},
            {"RThrow", Shoot_Fire::shoot_fire},
            {"RBrake", Slide::slide_},
            {"RDuck", Crouch::crouch_},
            {"LIdle", Stance::reverse_stance_},
            {"LJump", Jump::reverse_jump_},
            {"LRun", Walk::reverse_walk_},
            {"LClimb", Climb::reverse_climb_},
            {"LThrow", Shoot_Fire::reverse_shoot_fire},
            {"LBrake", Slide::reverse_slide_},
            {"LDuck", Crouch::reverse_crouch_}
        };
    };
};

namespace LuigiInvicinble {
    namespace Small {
        namespace Stance
        {
            const Rectangle s1 = {8, 298, 11, 15};
            const Rectangle s2 = {29, 298, 11, 15};
            const Rectangle s3 = {50, 298, 11, 15};
            const Rectangle s4 = {71, 298, 11, 15};
            const std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
            const Rectangle rs4 = {154, 298, 11, 15};
            const Rectangle rs3 = {133, 298, 11, 15};
            const Rectangle rs2 = {112, 298, 11, 15};
            const Rectangle rs1 = {91, 298, 11, 15};
            const std::vector<Rectangle> reverse_stance_ = {rs1, rs2, rs3, rs4};
        };
        namespace Jump
        {
            const Rectangle j1 = {175, 297, 16, 16};
            const Rectangle j2 = {196, 297, 16, 16};
            const Rectangle j3 = {217, 297, 16, 16};
            const Rectangle j4 = {238, 297, 16, 16};
            const std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
            const Rectangle rj1 = {259, 297, 16, 16};
            const Rectangle rj2 = {280, 297, 16, 16};
            const Rectangle rj3 = {301, 297, 16, 16};
            const Rectangle rj4 = {322, 297, 16, 16};
            const std::vector<Rectangle> reverse_jump_ = {rj1, rj2, rj3, rj4};
        };
        namespace Walk
        {
            const Rectangle w1 = {7, 341, 11, 15};
            const Rectangle w2 = {28, 341, 12, 15};
            const Rectangle w3 = {48, 340, 14, 16};
            const Rectangle w4 = {71, 341, 11, 15};
            const Rectangle w5 = {91, 341, 12, 15};
            const Rectangle w6 = {111, 340, 14, 16};
            const Rectangle w7 = {134, 341, 11, 15};
            const Rectangle w8 = {154, 341, 12, 15};
            const Rectangle w9 = {174, 340, 14, 16};
            const Rectangle w10 = {197, 341, 11, 15};
            const Rectangle w11 = {217, 341, 11, 15};
            const Rectangle w12 = {237, 340, 14, 16};
            const Rectangle w13 = {260, 341, 11, 15};
            const Rectangle w14 = {280, 341, 12, 15};
            const Rectangle w15 = {300, 340, 14, 16};
            const std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14};
            const Rectangle rw1 = {7, 374, 11, 15};
            const Rectangle rw2 = {28, 374, 12, 15};
            const Rectangle rw3 = {48, 373, 14, 16};
            const Rectangle rw4 = {71, 374, 11, 15};
            const Rectangle rw5 = {91, 374, 12, 15};
            const Rectangle rw6 = {111, 373, 14, 16};
            const Rectangle rw7 = {134, 374, 11, 15};
            const Rectangle rw8 = {154, 374, 12, 15};
            const Rectangle rw9 = {174, 373, 14, 16};
            const Rectangle rw10 = {197, 374, 11, 15};
            const Rectangle rw11 = {217, 374, 11, 15};
            const Rectangle rw12 = {237, 374, 14, 16};
            const Rectangle rw13 = {260, 374, 11, 15};
            const Rectangle rw14 = {280, 374, 12, 15};
            const Rectangle rw15 = {300, 373, 14, 16};
            const std::vector<Rectangle> reverse_walk_ = {rw1, rw2, rw3, rw4, rw5, rw6, rw7, rw8, rw9, rw10, rw11, rw12, rw13, rw14, rw15};
        };
        namespace Climb
        {
            const Rectangle c1 = {7, 501, 12, 16};
            const Rectangle c2 = {28, 501, 12, 15};
            const Rectangle c3 = {49, 501, 12, 16};
            const Rectangle c4 = {70, 501, 12, 15};
            const Rectangle c5 = {91, 501, 12, 16};
            const Rectangle c6 = {112, 501, 12, 15};
            const Rectangle c7 = {133, 501, 12, 16};
            const Rectangle c8 = {154, 501, 12, 15};
            const std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
            const Rectangle rc1 = {175, 501, 12, 16};
            const Rectangle rc2 = {196, 501, 12, 15};
            const Rectangle rc3 = {217, 501, 12, 16};
            const Rectangle rc4 = {238, 501, 12, 15};
            const Rectangle rc5 = {259, 501, 12, 16};
            const Rectangle rc6 = {280, 501, 12, 15};
            const Rectangle rc7 = {301, 501, 12, 16};
            const Rectangle rc8 = {322, 501, 12, 15};
            const std::vector<Rectangle> reverse_climb_ = {rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8};
        };
        namespace Slide
        {
            const Rectangle s1 = {323, 458, 13, 16};
            const Rectangle s2 = {344, 458, 13, 16};
            const Rectangle s3 = {365, 458, 13, 16};
            const Rectangle s4 = {386, 458, 13, 16};
            const std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
            const Rectangle rs1 = {408, 458, 13, 16};
            const Rectangle rs2 = {429, 458, 13, 16};
            const Rectangle rs3 = {450, 458, 13, 16};
            const Rectangle rs4 = {471, 458, 13, 16};
            const std::vector<Rectangle> reverse_slide_ = {rs1, rs2, rs3, rs4};
        };
        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"Duck", Stance::stance_},
            {"RIdle", Stance::stance_},
            {"RJump", Jump::jump_},
            {"RRun", Walk::walk_},
            {"RClimb", Climb::climb_},
            {"RBrake", Slide::slide_},
            {"LIdle", Stance::reverse_stance_},
            {"LJump", Jump::reverse_jump_},
            {"LRun", Walk::reverse_walk_},
            {"LClimb", Climb::reverse_climb_},
            {"LBrake", Slide::reverse_slide_}
        };
    };

    namespace Super {
        namespace Stance
        {
            const Rectangle s1 = {539, 338, 14, 31};
            const Rectangle s2 = {560, 338, 14, 31};
            const Rectangle s3 = {581, 338, 14, 31};
            const Rectangle s4 = {602, 338, 14, 31};
            const std::vector<Rectangle> stance_ = {s1, s2, s3, s4};
            const Rectangle rs1 = {623, 338, 14, 31};
            const Rectangle rs2 = {644, 338, 14, 31};
            const Rectangle rs3 = {665, 338, 14, 31};
            const Rectangle rs4 = {686, 338, 14, 31};
            const std::vector<Rectangle> reverse_stance_ = {rs1, rs2, rs3, rs4};
        };
        namespace Jump
        {
            const Rectangle j1 = {708, 338, 16, 30};
            const Rectangle j2 = {729, 338, 16, 30};
            const Rectangle j3 = {750, 338, 16, 30};
            const Rectangle j4 = {771, 338, 16, 30};
            const std::vector<Rectangle> jump_ = {j1, j2, j3, j4};
            const Rectangle rj1 = {792, 338, 16, 30};
            const Rectangle rj2 = {813, 338, 16, 30};
            const Rectangle rj3 = {834, 338, 16, 30};
            const Rectangle rj4 = {855, 338, 16, 30};
            const std::vector<Rectangle> reverse_jump_ = {rj1, rj2, rj3, rj4};
        };
        namespace Crouch
        {
            const Rectangle c1 = {708, 395, 15, 23};
            const Rectangle c2 = {729, 395, 15, 23};
            const Rectangle c3 = {750, 395, 15, 23};
            const Rectangle c4 = {771, 395, 15, 23};
            const std::vector<Rectangle> crouch_ = {c1, c2, c3, c4};
            const Rectangle rc1 = {793, 395, 15, 23};
            const Rectangle rc2 = {814, 395, 15, 23};
            const Rectangle rc3 = {835, 395, 15, 23};
            const Rectangle rc4 = {856, 395, 15, 23};
            const std::vector<Rectangle> reverse_crouch_ = {rc1, rc2, rc3, rc4};
        };
        namespace Slide
        {
            const Rectangle s1 = {538, 489, 16, 32};
            const Rectangle s2 = {559, 489, 16, 32};
            const Rectangle s3 = {580, 489, 16, 32};
            const Rectangle s4 = {601, 489, 16, 32};
            const std::vector<Rectangle> slide_ = {s1, s2, s3, s4};
            const Rectangle rs1 = {622, 489, 16, 32};
            const Rectangle rs2 = {643, 489, 16, 32};
            const Rectangle rs3 = {664, 489, 16, 32};
            const Rectangle rs4 = {685, 489, 16, 32};
            const std::vector<Rectangle> reverse_slide_ = {rs1, rs2, rs3, rs4};
        };
        namespace Climb
        {
            const Rectangle c1 = {709, 430, 14, 29};
            const Rectangle c2 = {730, 430, 14, 27};
            const Rectangle c3 = {751, 430, 14, 29};
            const Rectangle c4 = {772, 430, 14, 27};
            const Rectangle c5 = {793, 430, 14, 29};
            const Rectangle c6 = {814, 430, 14, 27};
            const Rectangle c7 = {835, 430, 14, 29};
            const Rectangle c8 = {856, 430, 14, 27};
            const std::vector<Rectangle> climb_ = {c1, c2, c3, c4, c5, c6, c7, c8};
            const Rectangle rc1 = {877, 430, 14, 29};
            const Rectangle rc2 = {898, 430, 14, 27};
            const Rectangle rc3 = {919, 430, 14, 29};
            const Rectangle rc4 = {940, 430, 14, 27};
            const Rectangle rc5 = {961, 430, 14, 29};
            const Rectangle rc6 = {982, 430, 14, 27};
            const Rectangle rc7 = {1003, 430, 14, 29};
            const Rectangle rc8 = {1024, 430, 14, 27};
            const std::vector<Rectangle> reverse_climb_ = {rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8};
        };
        namespace Shoot_Fire
        {
            const Rectangle s1 = {708, 473, 15, 31};
            const Rectangle s2 = {729, 473, 15, 31};
            const Rectangle s3 = {750, 473, 15, 31};
            const Rectangle s4 = {771, 473, 15, 31};
            const std::vector<Rectangle> shoot_fire = {s1, s2, s3, s4};
            const Rectangle rs1 = {793, 473, 15, 31};
            const Rectangle rs2 = {814, 473, 15, 31};
            const Rectangle rs3 = {835, 473, 15, 31};
            const Rectangle rs4 = {856, 473, 15, 31};
            const std::vector<Rectangle> reverse_shoot_fire = {rs1, rs2, rs3, rs4};
        };
        namespace Walk
        {
            const Rectangle w1 = {539, 381, 14, 31};
            const Rectangle w2 = {538, 447, 16, 31};
            const Rectangle w3 = {559, 414, 16, 30};
            const Rectangle w4 = {581, 381, 14, 31};
            const Rectangle w5 = {559, 447, 16, 31};
            const Rectangle w6 = {601, 414, 16, 30};
            const Rectangle w7 = {621, 374, 14, 30};
            const Rectangle w8 = {538, 447, 16, 31};
            const Rectangle w9 = {538, 414, 16, 30};
            const Rectangle w10 = {560, 381, 14, 31};
            const Rectangle w11 = {538, 447, 16, 31};
            const Rectangle w12 = {580, 414, 16, 30};
            const Rectangle w13 = {581, 381, 14, 31};
            const Rectangle w14 = {601, 447, 16, 31};
            const Rectangle w15 = {601, 414, 16, 30};
            const std::vector<Rectangle> walk_ = {w1, w2, w3, w4, w5, w6, w7, w7, w9, w10, w11, w12, w13, w14, w15};
            const Rectangle rw1 = {623, 381, 14, 31};
            const Rectangle rw2 = {622, 447, 16, 31};
            const Rectangle rw3 = {622, 414, 16, 30};
            const Rectangle rw4 = {644, 381, 14, 31};
            const Rectangle rw5 = {643, 447, 16, 31};
            const Rectangle rw6 = {643, 414, 16, 30};
            const Rectangle rw7 = {665, 381, 14, 31};
            const Rectangle rw8 = {664, 447, 16, 31};
            const Rectangle rw9 = {664, 414, 16, 30};
            const Rectangle rw10 = {686, 381, 14, 31};
            const Rectangle rw11 = {685, 447, 16, 31};
            const Rectangle rw12 = {685, 414, 16, 30};
            const Rectangle rw13 = {707, 381, 14, 31};
            const Rectangle rw14 = {706, 447, 16, 31};
            const Rectangle rw15 = {706, 414, 16, 30};
            const std::vector<Rectangle> reverse_walk_ = {rw1, rw2, rw3, rw4, rw5, rw6, rw7, rw8, rw9, rw10, rw11, rw12, rw13, rw14, rw15};
        };
        const unordered_map<string, vector<Rectangle>> allFrames = {
            {"RIdle", Stance::stance_},
            {"RJump", Jump::jump_},
            {"RDuck", Crouch::crouch_},
            {"RRun", Walk::walk_},
            {"RClimb", Climb::climb_},
            {"RBrake", Slide::slide_},
            {"RThrow", Shoot_Fire::shoot_fire},
            {"LIdle", Stance::reverse_stance_},
            {"LJump", Jump::reverse_jump_},
            {"LDuck", Crouch::reverse_crouch_},
            {"LRun", Walk::reverse_walk_},
            {"LClimb", Climb::reverse_climb_},
            {"LBrake", Slide::reverse_slide_},
            {"LThrow", Shoot_Fire::reverse_shoot_fire}
        };
    };
};


namespace EnemySprite {
    namespace KoopaSprite {
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

    namespace GoombaSprite {
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
    
    namespace PiranhaPlantSprite {
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

    namespace PodobooSprite {
        const Rectangle Down = {0.f, 150.f, 16.f, 16.f};
        const Rectangle Up = {60.f, 150.f, 16.f, 16.f};
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Up", {Up}},
            {"Down", {Down}}
        };
    };
    namespace FirebarSprite {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Normal", {Rectangle{25.f, 150.f, 10.f, 10.f}, 
                        Rectangle{40.f, 150.f, 10.f, 10.f}, 
                        Rectangle{25.f, 165.f, 10.f, 10.f}, 
                        Rectangle{40.f, 165.f, 10.f, 10.f}}}
        };
    };
    namespace BowserSprite {
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
    namespace FireballSprite {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Left", {Rectangle{100.f, 250.f, 25.f, 10.f}, 
                        Rectangle{130.f, 250.f, 25.f, 10.f}}},
            {"Right", {Rectangle{160.f, 250.f, 25.f, 10.f}, 
                        Rectangle{190.f, 250.f, 25.f, 10.f}}}
        };
        const Rectangle Frame1 = {364, 188, 8, 8};
        const Rectangle Frame2 = {392, 184, 12, 14};
        const Rectangle Frame3 = {420, 184, 16, 16};
        const std::vector<Rectangle> CharacterFireballFrames = {Frame1, Frame2, Frame3};
    }
    namespace LakituSprite {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Left", {Rectangle{0.f, 90.f, 16.f, 25.f} }},
            {"Right", {Rectangle{60.f, 90.f, 16.f, 25.f}}}, 
            {"Skill", {Rectangle{30.f, 90.f, 16.f, 25.f}} }
        };
    }

    namespace SpinySprite {
        const std::unordered_map<std::string, std::vector<Rectangle>> Frames = {
            {"Left", {Rectangle{90.f, 153.f, 16.f, 16.f},
                        Rectangle{120.f, 153.f, 16.f, 16.f}}},
            {"Right", {Rectangle{150.f, 153.f, 16.f, 16.f},
                        Rectangle{180.f, 153.f, 16.f, 16.f}}},
            {"Egg", {Rectangle{210.f, 153.f, 16.f, 16.f},
                        Rectangle{240.f, 153.f, 16.f, 16.f}} }
        };
    };
};

namespace ItemSprite
{
    //Line 1
    const Rectangle BLOCK_QUESTION =          {4, 4, 16, 16};
    const Rectangle BLOCK_QUESTION_FLASHING = {34, 4, 16, 16};
    const Rectangle BLOCK_QUESTION_USED =     {64, 4, 16, 16};
    const std::vector <Rectangle> QUESTIONBLOCK = {
        {4, 4, 16, 16},
        {34, 4, 16, 16},
        {64, 4, 16, 16}
    };
    const Rectangle SPRINGBOARD_EXTENDED =    {94, 0, 16, 24};
    const Rectangle SPRINGBOARD_ =             {124, 4, 16, 16};
    const Rectangle SPRINGBOARD_COMPRESSED =  {154, 8, 16, 8};
    const std::vector <Rectangle> SPRINGBOARD = {
        {94, 0, 16, 24},
        {124, 4, 16, 16},
        {154, 8, 16, 8}
    };
    const Rectangle BEANSTALK_FRAME_1 =       {188, 7, 8, 9};
    const Rectangle BEANSTALK_FRAME_2 =       {215, 4, 14, 16};
    const std::vector <Rectangle> BEANSTALK = {
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
    const std::vector <Rectangle> FIREFLOWER1 = {
        {4, 64, 16, 16},
        {34, 64, 16, 16},
        {64, 64, 16, 16},
        {94, 64, 16, 16}
    };
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_1 = {124, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_2 = {154, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_3 = {184, 64, 16, 16};
    const Rectangle FIRE_FLOWER_ANIMATION_2_FRAME_4 = {214, 64, 16, 16};
    const std::vector <Rectangle> FIREFLOWER2 = {
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
    const std::vector <Rectangle> STAR = {
        {5, 94, 14, 16},
        {35, 94, 14, 16},
        {65, 94, 14, 16},
        {95, 94, 14, 16}
    };
    const Rectangle COIN_SPIN_FRAME_1 =  {128, 95, 8, 14};
    const Rectangle COIN_SPIN_FRAME_2 =  {160, 95, 4, 14};
    const Rectangle COIN_SPIN_FRAME_3 =  {191, 95, 1, 14};
    const Rectangle COIN_SPIN_FRAME_4 =  {220, 95, 4, 14};
    const std::vector <Rectangle> COINSPIN = {
        {128, 95, 8, 14},
        {160, 95, 4, 14},
        {191, 95, 1, 14},
        {220, 95, 4, 14}
    };
    const Rectangle PRINCESS_PEACH =     {245, 90, 14,24};
    
} 
