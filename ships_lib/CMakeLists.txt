set(SOURCES 
    Field.cpp
    Game.cpp
    Ship.cpp)

set(HEADERS
    Field.h
    Game.h
    Ship.h)

add_library(ShipsGameLib ${SOURCES} ${HEADERS})
