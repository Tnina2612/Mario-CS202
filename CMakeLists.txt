cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MarioGame)

set(RAYLIB_PATH "D:/raylib")

include_directories(${RAYLIB_PATH}/include)
link_directories(${RAYLIB_PATH}/lib)

include_directories(include)

file(GLOB_RECURSE SOURCES 
    # "src/DataStructures/*.cpp"
    "src/Pages/*.cpp"
    # "src/Items/*.cpp"
    "src/*.cpp"
    "main.cpp"
)  # Đệ quy tìm trong các thư mục con

add_executable(MarioGame ${SOURCES})

target_link_libraries(MarioGame raylib -lopengl32 -lgdi32 -lwinmm)