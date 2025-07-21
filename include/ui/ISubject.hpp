#pragma once
#include "core/Variables.hpp"

class IObserver;

// Subject Interface in Observer Pattern
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notify(EventType type) = 0;
};