#pragma once
#include"Character.hpp"

class Luigi : public Character {
public:
    Luigi();
    Luigi(const Luigi& o);
    ~Luigi() override;
    CharacterType getType()const override;

    shared_ptr<Character> clone() const override;
};