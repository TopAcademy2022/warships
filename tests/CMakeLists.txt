cmake_minimum_required(VERSION 3.15)

project(warships_tests)

enable_testing()

find_package(GTest REQUIRED)

add_executable(warships_tests
    test_database.cpp
)

target_link_libraries(warships_tests
    Warships
    GTest::GTest
    GTest::Main
)

target_include_directories(warships_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}
)

set_target_properties(warships_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

add_test(NAME DatabaseTest COMMAND warships_tests)