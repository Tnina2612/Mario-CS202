:: Rebuild when CMakeLists.txt is modified
:: cmake -B build -G "MinGW Makefiles"

:: Rebuild when other files are updated
cmake --build build
.\build\Mario.exe