#pragma once
#include"Character.hpp"

class Mario : public Character {
public:
    Mario();
    ~Mario() override;
    CharacterType getType()const override;
};