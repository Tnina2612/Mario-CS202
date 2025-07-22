#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Singleton.h"
using namespace std;


class InputManager {
    template<class T>
    friend class Singleton;
    //class Listener;

public:
    class Listener {
    public:
        virtual void onkey(KeyboardKey key, bool active) = 0;
        virtual ~Listener() {};    
    };
    void addKey(KeyboardKey key);
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    void update();
    
    ~InputManager() = default;
private:
    unordered_map<KeyboardKey, bool> keyStates;
    vector<Listener*> listeners;

    InputManager() = default;
    InputManager(const InputManager& other) = delete;
    InputManager& operator = (const InputManager& other) = delete;
};