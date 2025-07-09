#include "ui/EventManager.hpp"
#include "ui/IObserver.hpp"
#include "algorithm"

void EventManager::addObserver(IObserver* observer) {
    observerList.push_back(observer);
}

void EventManager::removeObserver(IObserver* observer) {
    auto it = std::find(observerList.begin(), observerList.end(), observer);
    if (it != observerList.end()) {
        observerList.erase(it);
    }
}

void EventManager::notify(EventType type) {
    for (auto observer : observerList) {
        observer->onNotify(type);
    }
}