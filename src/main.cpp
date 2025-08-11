#include <iostream>
#include "raylib.h"
#include "core/Program.hpp"
#include "core/Variables.hpp"

int main() {
    try {
        Program::getInstance().run();
    } catch(...) {
        cout << "Catched an error." << endl;
    }
    return 0;
}