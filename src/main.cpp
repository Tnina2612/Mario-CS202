#include <iostream>
#include "raylib.h"
#include "core/Program.hpp"
#include "core/Variables.hpp"

int main() {
    try {
        Program::getInstance().run();
    } catch(const std::invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
    } catch(const std::out_of_range& e) {
        cout << "Out of range: " << e.what() << endl;
    } catch(const std::runtime_error& e) {
        cout << "Runtime error: " << e.what() << endl;
    } catch(const char* c) {
        cout << c << endl;
    } catch(const string& s) {
        cout << s << endl;
    } catch(...) {
        cout << "Catched an error." << endl;
    }
    return 0;
}