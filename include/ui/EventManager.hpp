#pragma once
#include "core/Variables.hpp"
#include "ui/ISubject.hpp"
#include <vector>

class IObserver;

// Concrete Subject in Observer Pattern
class EventManager : public ISubject {
private:
    std::vector<IObserver*> observerList;

public:
    ~EventManager() = default;
    void addObserver(IObserver* observer) override;
    void removeObserver(IObserver* observer) override;
    void notify(EventType type) override;
};