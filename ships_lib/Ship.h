#ifndef SHIP_H
#define SHIP_H
#include <map>
#include <vector>

class Ship {
 private:
  int deck_num = 1, hited_deck_num = 0, health = 1;

  char ship_sign = 's', destroyed_sign = 'x';

  bool is_destroyed = false;

  std::map<std::pair<int, int>, char> coordinates_with_values;

 public:
  Ship();

  Ship(const int &deck_num);

  int get_health();

  int get_deck_number();

  void hit(const int &x, const int &y);

  void add_ship_coordinate(const int &x, const int &y);

  bool has_coordinate(const int &x, const int &y);

  bool get_is_destroyed();

  std::vector<std::pair<int, int> > get_coordinates();
};

#endif  // SHIP_H
