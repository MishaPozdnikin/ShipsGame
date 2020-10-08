cmake_minimum_required(VERSION 3.0)

project(ShipsGame LANGUAGES CXX)

set(CMAKE_CXX_STANDATD 17)

set(CMAKE_CXX_STANDATD_REQUIRED ON)

add_executable(ShipsGame main.cpp field.cpp Ship.cpp)