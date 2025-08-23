#pragma once
#include"Character.hpp"

class Luigi : public Character {
public:
    Luigi();
    ~Luigi() override;
    CharacterType getType()const override;
};