#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <limits>
#include <ios>
#include <ctime>

#include "Game.h"
#include "Field.h"

int main(int argc, char* argv[]) {
    Game game;
    char choise = 'y';
    srand(time(NULL));
    
    while(choise == 'y') {
        system("clear");
        game.setGameMode();
        if (game.getGameMode() == PvP) {
            Field *f1 = game.init_field();
            Sleep(50);
            Field *f2 = game.init_field();
            while (1) {
                game.setCurrentPlayer(CURRENT_PLAYER::FIRST_PLAYER);
                game.player_shoot(f1, f2);
                if (game.isEnd()) {
                    break;
                }
                system("clear");
                std::cout << "Player 2 move in 3 seconds..." << std::flush;
                Sleep(3000);
                system("clear");
                game.setCurrentPlayer(CURRENT_PLAYER::SECOND_PLAYER);
                game.player_shoot(f2, f1);
                if (game.isEnd()) {
                    break;
                }
                system("clear");
                std::cout << "Player 1 move in 3 seconds..." << std::flush;
                Sleep(3000);
            }
            system("clear");
            std::cout << "Continue playing? (enter 'y' to continue):\n- ";
            std::cin >> choise;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choise == 'y') {
                continue;
            } else {
                system("clear");
                return 0;
            }
        } else if (game.getGameMode() == PvC) {
            Field *f1 = game.init_field();
            Sleep(200);
            Field *f2 = game.init_field();
            while (1) {
                game.setCurrentPlayer(CURRENT_PLAYER::FIRST_PLAYER);
                game.player_shoot(f1, f2);
                if (game.isEnd()) {
                    break;
                }
                game.setCurrentPlayer(CURRENT_PLAYER::FIRST_COMPUTER);
                game.enemy_shoot(f2);
                if (game.isEnd()) {
                    break;
                }
                std::cout << "\nPress 'Enter' to continue\n";
                std::cin.get();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                system("clear");
            }
            system("clear");
            std::cout << "Continue playing? (enter 'y' to continue):\n- ";
            std::cin >> choise;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choise == 'y') {
                continue;
            } else {
                system("clear");
                return 0;
            }
        } else if (game.getGameMode() == CvC) {
            Field *f1 = game.init_field();
            Sleep(200);
            Field *f2 = game.init_field();
            while (1) {
                game.setCurrentPlayer(CURRENT_PLAYER::FIRST_COMPUTER);
                game.player_shoot(f1, f2);
                if (game.isEnd()) {
                    break;
                }
                system("clear");
                std::cout << "Computer 2 move in 3 seconds..." << std::flush;
                Sleep(3000);
                system("clear");
                game.setCurrentPlayer(CURRENT_PLAYER::SECOND_COMPUTER);
                game.player_shoot(f2, f1);
                if (game.isEnd()) {
                    break;
                }
                system("clear");
                std::cout << "Computer 1 move in 3 seconds..." << std::flush;
                Sleep(3000);
            }
            std::cout << "Continue playing? (enter 'y' to continue):\n- ";
            std::cin >> choise;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choise == 'y') {
                continue;
            } else {
                system("clear");
                return 0;
            }
        } else if (game.getGameMode() == EXIT) {
            system("clear");
            return 0;
        }
    }
    
    return 0;
}
