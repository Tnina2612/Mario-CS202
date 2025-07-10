#pragma once
#include "Variables.h"

// Observer Interface in Observer Pattern
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(EventType type) = 0;
};