#include "Game.h"

#include <iostream>
#include <limits>
#include <ios>
#include <Windows.h>

#include "Ship.h"
#include "Field.h"


Game::Game() {
    this->game_mode = PvP;
    this->current_player = FIRST_PLAYER;
}

Game::Game(GAME_MODE game_mode, CURRENT_PLAYER current_player) {
    this->game_mode = game_mode;
    this->current_player = current_player;
}

void Game::setGameMode() {
    char mode;
    std::cout << "\t\t\tSHIPS GAME\n\n\n";
    std::cout << "\t\t\tChoose your game mode:\n";
    std::cout << "\t\t\t1 - Player vs Player\n";
    std::cout << "\t\t\t2 - Player vs Computer\n";
    std::cout << "\t\t\t3 - Computer vs Computer\n";
    std::cout << "\t\t\t4 - Exit\n";
    std::cout << "\t\t\t- ";
    std::cin >> mode;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (mode != '1' && mode != '2' && mode != '3' && mode != '4') {
        system("clear");
        setGameMode();
    } else {
        this->game_mode = static_cast<GAME_MODE>(mode - '1');
    }
}

GAME_MODE Game::getGameMode() {
    return this->game_mode;
}

void Game::setCurrentPlayer(CURRENT_PLAYER current_player) {
    this->current_player = current_player;
}

CURRENT_PLAYER Game::getCurrentPlayer() {
    return this->current_player;
}

void Game::enemy_shoot(Field* my_field) {
    while (1) {
        my_x = rand() % my_field->get_height() + 1;
        my_y = rand() % my_field->get_width() + 1;
        if (my_x < my_field->get_width() + 1 && my_x < my_field->get_height() + 1 && my_x > 0 && my_y > 0) {
            while (my_field->is_tried(my_x, my_y)) {
                my_x = rand() % my_field->get_height();
                my_y = rand() % my_field->get_width();
            }
            while (my_field->is_destroyed_sign(my_x, my_y)) {
                my_x = rand() % my_field->get_height();
                my_y = rand() % my_field->get_width();
            }
            std::cout << "\nEnemy tries: x = " << my_x << " y = " << my_y << ".\n\n";
            if (my_field->is_ship(my_x, my_y)) {
                my_field->destroy_ship(my_x, my_y);
                std::cout << "Your ship has been destroyed at x " << my_x << " y " << my_y << ".\n";
                if (!my_field->get_ships_num()) {
                    std::cout << "You lose!\n";
                    end = true;
                    return;
                }
                std::cout << my_field->get_ships_num() << " ships left. " << "Your field:\n";
                my_field->show_field();
            }
            else {
                my_field->try_point(my_x, my_y);
                break;
            }
        } else {
            continue;
        }
    }
}

void Game::player_shoot(Field* enemy_field, Field* my_field) {
    while (1) {
        system("clear");
        if (game_mode == GAME_MODE::CvC) {
            std::cout << "Computer " << getCurrentPlayer() - 1 << ". Your field:" << std::endl << std::endl;
        }
        else {
            std::cout << "Player " << getCurrentPlayer() + 1 << ". Your field:" << std::endl << std::endl;
        }
        my_field->show_field();
        std::cout << "\nEnemy's field:\n\n";
        enemy_field->show_war_fog();
        std::cout << enemy_field->get_ships_num() << " enemy's ships left.\n";
        std::cout << std::endl;
        if (game_mode != GAME_MODE::CvC) {
            std::cout << "Enter point x: ";
            std::cin >> enemy_x;
        } else {
            while (1) {
                enemy_x = rand() % my_field->get_height() + 1;
                Sleep(50);
                enemy_y = rand() % my_field->get_width() + 1;
                if (enemy_x < enemy_field->get_width() + 1 && enemy_y < enemy_field->get_height() + 1 && enemy_x > 0 && enemy_y > 0 && 
                    !enemy_field->is_destroyed_sign(enemy_x, enemy_y) && !enemy_field->is_tried(enemy_x, enemy_y)) {
                    Sleep(1000);
                    std::cout << "x: " << enemy_x << std::endl;
                    Sleep(1000);
                    std::cout << "y: " << enemy_y << std::endl;
                    Sleep(3000);
                    break;
                } else {
                    continue;
                }
            }
        }
        if (enemy_x == 99) {
            std::cout << "\nEnemy's field:\n";
            enemy_field->show_field();
            std::cout << "\nPress 'Enter' to continue\n";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("clear");
            continue;
        }
        if (game_mode != GAME_MODE::CvC) {
            std::cout << "Enter point y: ";
            std::cin >> enemy_y;
        }
        if (enemy_x < enemy_field->get_width() + 1 && enemy_y < enemy_field->get_height() + 1 && enemy_x > 0 && enemy_y > 0 && 
                    !enemy_field->is_destroyed_sign(enemy_x, enemy_y) && !enemy_field->is_tried(enemy_x, enemy_y)) {
            if (enemy_field->is_ship(enemy_x, enemy_y)) {
                enemy_field->destroy_enemys_ship(enemy_x, enemy_y);
                if (!enemy_field->get_ships_num()) {
                    std::cout << "You win!\n";
                    std::cout << "\nPress 'Enter' to continue\n";
                    std::cin.get();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    system("clear");
                    end = true;
                    return;
                }
                continue;
            } else {
                enemy_field->try_point(enemy_x, enemy_y);
                break;
            }
        } else {
            std::cout << "Try another values for x and y.\n";
            std::cout << "\nPress 'Enter' to continue\n";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("clear");
            continue;
        }
    }
}

bool Game::isEnd() {
    return end;
}

Field* Game::init_field() {
    Field *f = new Field(10, 10);
    f->spawn_ships(4, 1);
    f->spawn_ships(3, 2);
    f->spawn_ships(2, 3);
    f->spawn_ships(1, 4);
    return f;
}
