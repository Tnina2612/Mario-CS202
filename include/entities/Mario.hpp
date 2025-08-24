#pragma once
#include"Character.hpp"

class Mario : public Character {
public:
    Mario();
    ~Mario() override;
    Mario(const Mario& o);
    CharacterType getType()const override;

    shared_ptr<Character> clone() const override;
};