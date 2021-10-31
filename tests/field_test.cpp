#include "Field.h"

#include <gtest/gtest.h>

#include "Ship.h"

TEST(FieldTests, ConstructorDefaultTest) {
  Field f;
  EXPECT_EQ(f.get_width(), 10);
  EXPECT_EQ(f.get_height(), 10);
}

TEST(FieldTests, ShowFiledTest) {
  Field f;
  ASSERT_NO_THROW(f.show_field());
}

TEST(FieldTests, CreateFieldTest) {
  Field f;
  ASSERT_NO_THROW(f.create_field(10, 10));
  ASSERT_NO_THROW(f.create_field(10, 20));
}

TEST(FieldTests, InitializeTest) {
  Field f;
  ASSERT_NO_THROW(f.create_field(10, 10));
  ASSERT_NO_THROW(f.initialize('-'));
}

TEST(FieldTests, SpawnShipsTest) {
  Field f;
  ASSERT_NO_THROW(f.create_field(10, 10));
  ASSERT_NO_THROW(f.spawn_ships(4, 1));
  ASSERT_NO_THROW(f.spawn_ships(3, 2));
  ASSERT_NO_THROW(f.spawn_ships(2, 3));
  ASSERT_NO_THROW(f.spawn_ships(1, 4));
  EXPECT_EQ(f.get_ships_num(), 10);
}

TEST(FieldTests, IsShipTest) {
  Field f;
  size_t ships_counter = 0;

  f.spawn_ships(4, 1);
  f.spawn_ships(3, 2);
  f.spawn_ships(2, 3);
  f.spawn_ships(1, 4);
  for (size_t i = 1; i < 11; ++i) {
    for (size_t j = 1; j < 11; j++) {
      if (f.is_ship(i, j)) {
        ++ships_counter;
      }
    }
  }
  EXPECT_EQ(ships_counter, 20);
}

TEST(FieldTests, DestroyShipTest) {
  Field f;
  size_t ships_counter, x, y = 0;
  bool exit_loops = false;

  f.spawn_ships(4, 1);
  f.spawn_ships(3, 2);
  f.spawn_ships(2, 3);
  f.spawn_ships(1, 4);
  for (size_t i = 1; i < 11; ++i) {
    for (size_t j = 1; j < 11; j++) {
      if (f.is_ship(i, j)) {
        f.destroy_ship(i, j);
        x = j;
        y = i;
        exit_loops = true;
        break;
      }
    }
    if (exit_loops) {
      break;
    }
  }
  EXPECT_TRUE(f.is_destroyed_sign(y, x));
}

TEST(FieldTests, DestroyEnemysShipTest) {
  Field f;
  size_t ships_counter, x, y = 0;
  bool exit_loops = false;

  f.spawn_ships(4, 1);
  f.spawn_ships(3, 2);
  f.spawn_ships(2, 3);
  f.spawn_ships(1, 4);
  for (size_t i = 1; i < 11; ++i) {
    for (size_t j = 1; j < 11; j++) {
      if (f.is_ship(i, j)) {
        f.destroy_enemys_ship(i, j);
        x = j;
        y = i;
        exit_loops = true;
        break;
      }
    }
    if (exit_loops) {
      break;
    }
  }
  EXPECT_TRUE(f.is_destroyed_sign(y, x));
}

TEST(FieldTests, DrawShipPerimetrWithTriedSignTest) {
  Field f;
  Ship s;
  size_t ships_counter = 0;
  bool exit_loops = false;

  f.spawn_ships(4, 1);
  f.spawn_ships(3, 2);
  f.spawn_ships(2, 3);
  f.spawn_ships(1, 4);
  for (size_t i = 1; i < 11; ++i) {
    for (size_t j = 1; j < 11; j++) {
      if (f.is_ship(i, j)) {
        s = f.get_ship(i, j);
        exit_loops = true;
        break;
      }
    }
    if (exit_loops) {
      break;
    }
  }

  ASSERT_NO_THROW(f.draw_ship_perimetr_with_tried_sign(&s));
}

TEST(FieldTests, GetShipsNumTest) {
  Field f;
  f.spawn_ships(4, 1);
  f.spawn_ships(3, 2);
  f.spawn_ships(2, 3);
  f.spawn_ships(1, 4);

  EXPECT_EQ(f.get_ships_num(), 10);
}

TEST(FieldTests, IsTriedTest) {
  Field f;
  f.try_point(1, 1);
  EXPECT_TRUE(f.is_tried(1, 1));
}

TEST(FieldTests, GetDeckNumberTest) {
  Field f;
  bool exit_loops = false;
  int x, y = 0;
  f.spawn_ships(4, 1);

  for (size_t i = 1; i < 11; ++i) {
    for (size_t j = 1; j < 11; j++) {
      if (f.is_ship(i, j)) {
        x = j;
        y = i;
        break;
      }
    }
    if (exit_loops) {
      break;
    }
  }
  EXPECT_EQ(f.get_deck_number(y, x), 4);
}

TEST(FieldTests, GetWidthTest) {
  Field f;
  EXPECT_EQ(f.get_width(), 10);
}

TEST(FieldTests, GetHeightTest) {
  Field f;
  EXPECT_EQ(f.get_height(), 10);
}

TEST(FieldTests, ShowWarFogTest) {
  Field f;
  ASSERT_NO_THROW(f.show_war_fog());
}
