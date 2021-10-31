#ifndef FIELD_H
#define FIELD_H
#include <ctime>
#include <iostream>
#include <vector>

#include "Ship.h"

class Field {
 private:
  int height, width, curr_ships_num = 0;
  char **arr;
  std::vector<Ship *> ships;
  char ship_sign = 's', field_sign = '-', destroyed_sign = 'x',
       tried_sign = '.', border_sign = '*';

 public:
  Field();

  void show_field();

  void create_field(const int &height, const int &width);

  void initialize(const char &c);

  void spawn_ships(const int &ship_type, const int &ships_number);

  bool is_ship(const int &x, const int &y);

  void destroy_ship(const int &x, const int &y);

  void destroy_enemys_ship(const int &x, const int &y);

  void draw_ship_perimetr_with_tried_sign(Ship *sh);

  int get_ships_num();

  bool is_destroyed_sign(const int &x, const int &y);

  bool is_destroyed(const int &x, const int &y);

  bool is_tried(const int &x, const int &y);

  void try_point(const int &x, const int &y);

  int get_width() { return this->width; }

  int get_height() { return this->height; }

  int get_deck_number(const int &x, const int &y);

  void show_war_fog();

  Ship &get_ship(const int &x, const int &y);

  ~Field() {
    for (int i = 0; i < width; i++) {
      delete arr[i];
    }
    delete[] arr;
  }
};

#endif  // FIELD_H
