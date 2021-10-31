#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

#include <cstdlib>
#include <ctime>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

#include "Field.h"
#include "Game.h"

bool consoleHandler(int signal) {
  if (signal == CTRL_C_EVENT) {
    exit(0);
  }
  return true;
}

int main() {
  Game game = Game();
  char choise = 'y';
  srand(time(NULL));
  SetConsoleCtrlHandler((PHANDLER_ROUTINE)consoleHandler, TRUE);

  while (choise == 'y') {
    system("cls");
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
        system("cls");
        std::cout << "Player 2 move in 3 seconds..." << std::flush;
        Sleep(3000);
        system("cls");
        game.setCurrentPlayer(CURRENT_PLAYER::SECOND_PLAYER);
        game.player_shoot(f2, f1);
        if (game.isEnd()) {
          break;
        }
        system("cls");
        std::cout << "Player 1 move in 3 seconds..." << std::flush;
        Sleep(3000);
      }
      system("cls");
      std::cout << "Continue playing? (enter 'y' to continue):\n- ";
      std::cin >> choise;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (choise == 'y') {
        continue;
      } else {
        system("cls");
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
        system("cls");
      }
      system("cls");
      std::cout << "Continue playing? (enter 'y' to continue):\n- ";
      std::cin >> choise;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (choise == 'y') {
        continue;
      } else {
        system("cls");
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
        system("cls");
        game.setCurrentPlayer(CURRENT_PLAYER::SECOND_COMPUTER);
        game.player_shoot(f2, f1);
        if (game.isEnd()) {
          break;
        }
        system("cls");
      }
      std::cout << "Continue playing? (enter 'y' to continue):\n- ";
      std::cin >> choise;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (choise == 'y') {
        continue;
      } else {
        system("cls");
        return 0;
      }
    } else if (game.getGameMode() == EXIT) {
      system("cls");
      return 0;
    }
  }

  return 0;
}
