cmake_minimum_required(VERSION 3.15)

project(warships VERSION 0.0.1 LANGUAGES CXX)

set(CORE
    warships/warships.cpp
    warships/src/battlefield.cpp
    warships/src/cell.cpp
    warships/src/console-user-interface.cpp
    warships/src/controller.cpp
    warships/src/game.cpp
    warships/src/i-user-interface.cpp
    warships/src/notepad-database.cpp
    warships/src/ship.cpp
)

add_executable(Warships ${CORE})

target_include_directories(Warships
    PRIVATE
    warships
    warships/src
)

set_target_properties(
    Warships PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(Warships PRIVATE /W4 /permissive-)
else()
    target_compile_options(Warships PRIVATE -Wall -Wextra -Wpedantic)
endif()
