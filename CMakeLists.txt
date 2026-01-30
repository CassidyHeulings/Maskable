cmake_minimum_required(VERSION 4.0)
project(Maskable)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR /opt/homebrew/opt/sfml@2/lib/cmake/SFML)
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

add_executable(Maskable "Source Files/main.cpp"
        "Source Files/Player.cpp"
        "Header Files/Player.hpp"
        "Source Files/World.cpp"
        "Header Files/World.hpp"
        "Source Files/TextureHolder.cpp"
        "Header Files/TextureHolder.hpp")

target_link_libraries(Maskable sfml-graphics sfml-window sfml-system sfml-audio)