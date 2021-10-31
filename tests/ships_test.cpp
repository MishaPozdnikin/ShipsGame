#include <gtest/gtest.h>

#include <iostream>

#include "Ship.h"

TEST(ShipTests, ConstructorDefaultTest) { ASSERT_NO_THROW(Ship s); }

TEST(ShipTests, ConstructorWithParamsTest) {
  Ship s(4);
  EXPECT_EQ(s.get_deck_number(), 4);
  EXPECT_EQ(s.get_health(), 4);
}

TEST(ShipTests, HitTest) {
  Ship s(1);
  s.add_ship_coordinate(0, 1);
  s.hit(0, 1);
  EXPECT_TRUE(s.get_is_destroyed());
}

TEST(ShipTests, HasCoordinateTest) {
  Ship s(1);
  s.add_ship_coordinate(0, 1);
  EXPECT_TRUE(s.has_coordinate(0, 1));
}

TEST(ShipTests, AddShipCoordinate) {
  Ship s(1);
  s.add_ship_coordinate(0, 1);
  EXPECT_TRUE(s.has_coordinate(0, 1));
}
