project(ShipsTests)

set(SOURCES
    field_test.cpp
    ships_test.cpp
    game_test.cpp
    main.cpp)

add_executable(ShipsTests ${SOURCES})

add_test(
    NAME ShipsTests
    COMMAND ShipsTests
    )
target_include_directories(ShipsTests PUBLIC ../ships_lib) 
target_link_libraries(ShipsTests PUBLIC ShipsGameLib gtest_main)
