#include "Ship.h"

Ship::Ship()
{

}

Ship::Ship(const int &deck_num)
{
    this->deck_num = deck_num;
    health = deck_num;
}

char Ship::get_value(const int &x, const int &y)
{
    std::pair<int, int> p(x,y);
    return coordinates_with_values.find(p)->second;
}

void Ship::set_value(const int &x, const int &y, const char &value)
{
    std::pair<int, int> p(x,y);
    coordinates_with_values.find(p)->second = value;
}

int Ship::get_health()
{
    return health;
}

int Ship::get_deck_number()
{
    return deck_num;
}

int Ship::get_hited_deck_number()
{
    return hited_deck_num;
}

void Ship::hit(const int &x, const int &y)
{
    for(auto &el : coordinates_with_values)
    {
        if(el.first.first == x && el.first.second == y)
        {
            el.second = destroyed_sign;
            --health;
            ++hited_deck_num;
            if(health == 0)
                is_destroyed = true;
        }
    }
}

void Ship::add_ship_coordinate(const int &x, const int &y)
{
    std::pair<int,int> p(x,y);
    coordinates_with_values.insert({p, ship_sign});
}

bool Ship::has_coordinate(const int &x, const int &y)
{
    for(auto &el : coordinates_with_values)
    {
        if(el.first.first == x && el.first.second == y)
        {
            return true;
        }
    }
    return false;
}

bool Ship::get_is_destroyed()
{
    return is_destroyed;
}

std::vector<std::pair<int, int> > Ship::get_coordinates()
{
    std::vector<std::pair<int, int>> coordinates;
    for(auto &a : coordinates_with_values)
    {
        coordinates.push_back(a.first);
    }
    return coordinates;
}

