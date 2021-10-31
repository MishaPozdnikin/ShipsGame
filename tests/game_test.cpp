#include "Game.h"

#include <gtest/gtest.h>

#include "Field.h"

TEST(GameTests, ConstructorDefaultTest) {
  Game game;
  EXPECT_EQ(game.getGameMode(), GAME_MODE::PvP);
  EXPECT_EQ(game.getCurrentPlayer(), CURRENT_PLAYER::FIRST_PLAYER);
}

TEST(GameTests, ConstructorWithParamsTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  EXPECT_EQ(game.getGameMode(), GAME_MODE::CvC);
  EXPECT_EQ(game.getCurrentPlayer(), CURRENT_PLAYER::FIRST_COMPUTER);
}

TEST(GameTests, GetGameModeTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  EXPECT_EQ(game.getGameMode(), GAME_MODE::CvC);
}

TEST(GameTests, GetCurrentPlayerTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  EXPECT_EQ(game.getCurrentPlayer(), CURRENT_PLAYER::FIRST_COMPUTER);
}

TEST(GameTests, SetCurrentPlayerTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  game.setCurrentPlayer(CURRENT_PLAYER::FIRST_PLAYER);
  EXPECT_EQ(game.getCurrentPlayer(), CURRENT_PLAYER::FIRST_PLAYER);
}

TEST(GameTests, EnemyShootTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  Field f;
  ASSERT_NO_THROW(game.enemy_shoot(&f));
}

TEST(GameTests, IsEndTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  EXPECT_FALSE(game.isEnd());
}

TEST(GameTests, InitFieldTest) {
  Game game(GAME_MODE::CvC, CURRENT_PLAYER::FIRST_COMPUTER);
  Field *f;
  f = game.init_field();
  EXPECT_EQ(f->get_ships_num(), 10);
}
