cmake_minimum_required(VERSION 3.0)

project(warships VERSION 0.0.1 LANGUAGES CXX)

set(
    CORE
        warships/warships.cpp
)

add_executable(Warships ${CORE})

target_include_directories(Warships
    PRIVATE
    warships/
)

set_target_properties(
    Warships PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)