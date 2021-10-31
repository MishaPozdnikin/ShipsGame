cmake_minimum_required(VERSION 3.22)
project(ShipsGame)

set(CXXMAKE_C_STANDARD 11)
set(POSITION_INDEPENDENT_CODE ON)

enable_testing()

include_directories(ships_lib)
add_subdirectory(ships_lib)
add_subdirectory(tests)
add_subdirectory(googletest)

add_executable(ShipsGame main.cpp)

target_link_libraries(ShipsGame ShipsGameLib)
