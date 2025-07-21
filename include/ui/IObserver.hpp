#pragma once
#include "core/Variables.hpp"

// Observer Interface in Observer Pattern
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(EventType type) = 0;
};