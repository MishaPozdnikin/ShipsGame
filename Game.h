#include "Ship.h"
#include "Field.h"

enum GAME_MODE {
    PvP,
    PvC,
    CvC,
    EXIT
};

enum CURRENT_PLAYER {
    FIRST_PLAYER,
    SECOND_PLAYER,
    FIRST_COMPUTER,
    SECOND_COMPUTER
};

class Game {
private:
    int enemy_x, enemy_y, my_x, my_y;
    bool end = false;
    GAME_MODE game_mode = PvP;
    CURRENT_PLAYER current_player = FIRST_PLAYER;
public:
    Game();
    Game(GAME_MODE game_mode, CURRENT_PLAYER current_player);

    void setGameMode();
    GAME_MODE getGameMode();

    void setCurrentPlayer(CURRENT_PLAYER current_player);
    CURRENT_PLAYER getCurrentPlayer();
    
    bool isEnd();

    void enemy_shoot(Field* my_field);
    void player_shoot(Field* enemy_field, Field* my_field);
    
    Field* init_field();

};