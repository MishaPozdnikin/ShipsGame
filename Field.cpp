#include "Field.h"

#include <Windows.h>

#include "Ship.h"

Field::Field() : height(10),
    width(10)
{
    create_field(height, width);
    initialize(field_sign);
}

Field::Field(const int& height, const int& width)
    : height(height),
    width(width)
{
    create_field(height, width);
    initialize(field_sign);
}

void Field::show_field()
{
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
}

void Field::create_field(const int& height, const int& width)
{
    arr = new char* [height + 2];
    for (int i = 0; i < height + 2; i++)
    {
        arr[i] = new char[width + 2];
    }

}

void Field::initialize(const char& c)
{
    for (int i = 0; i <= height + 1; i++)
    {
        for (int j = 0; j <= width + 1; j++)
        {
            if(i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                arr[i][j] = border_sign;
            }
            if (arr[i][j] != border_sign)
                this->arr[i][j] = c;
        }
    }
}

void Field::spawn_ships(const int& ship_deck_number, const int& ships_number)
{
    if (ships_number * ship_deck_number > height * width)
    {
        std::cout << "too much ships for this field. max ships number is " << height * width << "\n";
        return;
    }

    int counter = 0,
        x = 0,
        y = 0,
        direction = 0,
        temp_x = x,
        temp_y = y,
        check = 0;
    bool is_posible = true;


    while (counter < ships_number)
    {
        x = 1 + (rand() % width);
        y = 1 + (rand() % height);
        temp_x = x;
        temp_y = y;
        direction = rand() % 4;
        //x++    -> 0
        //y++    ↓  1
        //x--    <- 2
        //y--    ↑  3
        is_posible = true;

        check++;
        if (check > 10000)
        {
            std::cout << "check > 1000\n";
            break;
        }

        for (int i = 0; i < ship_deck_number; i++)
        {
            if (x > width + 1 || y > height + 1 || x < 1 || y < 1)
            {
                is_posible = false;
                break;
            }
            if (arr[y][x] == border_sign ||
                direction == 0 && arr[y][x + 1] == border_sign ||                         //x++    -> 0
                direction == 2 && arr[y][x - 1] == border_sign ||                         //y++    ↓  1
                direction == 1 && arr[y + 1][x] == border_sign ||                         //x--    <- 2
                direction == 3 && arr[y - 1][x] == border_sign
                )
            {
                is_posible = false;
                break;
            }
            if (arr[y][x] == ship_sign ||
                arr[y][x + 1] == ship_sign ||
                arr[y][x - 1] == ship_sign ||
                arr[y + 1][x] == ship_sign ||
                arr[y - 1][x] == ship_sign ||
                arr[y + 1][x - 1] == ship_sign ||
                arr[y + 1][x + 1] == ship_sign ||
                arr[y - 1][x - 1] == ship_sign ||
                arr[y - 1][x + 1] == ship_sign
                )
            {
                is_posible = false;
                break;
            }
            else
            {
                switch (direction)
                {
                case 0:
                {
                    x++;
                    break;
                }
                case 1:
                {
                    y++;
                    break;
                }
                case 2:
                {
                    x--;
                    break;
                }
                case 3:
                {
                    y--;
                    break;
                }
                default:
                {
                    std::cout << "spawn ships error.\n";
                    break;
                }
                }
            }
        }
        if (is_posible == true)
        {
            Ship *ship = new Ship(ship_deck_number);
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < ship_deck_number; i++)
            {
                arr[y][x] = ship_sign;
                ship->add_ship_coordinate(x,y);
                switch (direction)
                {
                    case 0:
                    {
                        x++;
                        break;
                    }
                    case 1:
                    {
                        y++;
                        break;
                    }
                    case 2:
                    {
                        x--;
                        break;
                    }
                    case 3:
                    {
                        y--;
                        break;
                    }
                    default:
                    {
                        std::cout << "spawn ships error.\n";
                        break;
                    }
                }
            }
            counter++;
            curr_ships_num++;
            ships.push_back(ship);
        }
    }
}

bool Field::is_ship(const int& x, const int& y)
{
    if (arr[y][x] == ship_sign || arr[y][x] == destroyed_sign)
        return true;
    return false;
}

void Field::destroy_enemys_ship(const int& x, const int& y)
{
    arr[y][x] = destroyed_sign;
    get_ship(x,y).hit(x, y);
    if (get_ship(x,y).get_health() > 0)
    {
        std::cout << "Hit!\n";
        Sleep(1000);
    }
    else if (get_ship(x,y).get_health() == 0)
    {
        curr_ships_num--;
        draw_ship_perimetr_with_tried_sign(&get_ship(x,y));
        std::cout << "Destroyed!\n";
        Sleep(1000);
    }
}

void Field::draw_ship_perimetr_with_tried_sign(Ship *sh)
{
    std::vector<std::pair<int,int>> ship_coordinates = sh->get_coordinates();
    int x,
        y;
    for(int i = 0; i < sh->get_deck_number(); i++)
    {
        x = ship_coordinates[i].first;
        y = ship_coordinates[i].second;
        if(arr[y+1][x] != border_sign && 
           arr[y+1][x] != ship_sign   && 
           arr[y+1][x] != destroyed_sign   && 
           arr[y+1][x] != tried_sign)
        {
            arr[y+1][x] = tried_sign;
        }
        if(arr[y-1][x] != border_sign && 
           arr[y-1][x] != ship_sign   &&
           arr[y-1][x] != destroyed_sign   && 
           arr[y-1][x] != tried_sign)
        {
            arr[y-1][x] = tried_sign;
        }
        if(arr[y][x+1] != border_sign && 
           arr[y][x+1] != ship_sign   && 
           arr[y][x+1] != destroyed_sign   && 
           arr[y][x+1] != tried_sign)
        {
            arr[y][x+1] = tried_sign;
        }
        if(arr[y][x-1] != border_sign && 
           arr[y][x-1] != ship_sign   && 
           arr[y][x-1] != destroyed_sign   &&
           arr[y][x-1] != tried_sign)
        {
            arr[y][x-1] = tried_sign;
        }
        if(arr[y+1][x+1] != border_sign && 
           arr[y+1][x+1] != ship_sign   && 
           arr[y+1][x+1] != destroyed_sign   && 
           arr[y+1][x+1] != tried_sign)
        {
            arr[y+1][x+1] = tried_sign;
        }
        if(arr[y+1][x-1] != border_sign && 
           arr[y+1][x-1] != ship_sign   &&  
           arr[y+1][x-1] != destroyed_sign   &&        
           arr[y+1][x-1] != tried_sign)             
        {                                           
            arr[y+1][x-1] = tried_sign;
        }
        if(arr[y-1][x-1] != border_sign && 
           arr[y-1][x-1] != ship_sign   &&
           arr[y-1][x-1] != destroyed_sign   && 
           arr[y-1][x-1] != tried_sign)
        {
            arr[y-1][x-1] = tried_sign;
        }
        if(arr[y-1][x+1] != border_sign && 
           arr[y-1][x+1] != ship_sign   && 
           arr[y-1][x+1] != destroyed_sign   &&
           arr[y-1][x+1] != tried_sign)
        {
            arr[y-1][x+1] = tried_sign;
        }
    }
}

void Field::destroy_ship(const int& x, const int& y)
{
    arr[y][x] = destroyed_sign;
    get_ship(x,y).hit(x, y);
    if (get_ship(x,y).get_health() == 0)
    {
        curr_ships_num--;
        draw_ship_perimetr_with_tried_sign(&get_ship(x,y));
    }
}

int Field::get_ships_num()
{
    return curr_ships_num;
}

bool Field::is_destroyed_sign(const int& x, const int& y)
{
    if (arr[y][x] == destroyed_sign)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Field::is_destroyed(const int &x, const int &y)
{
    if(get_ship(x,y).get_is_destroyed())
        return true;
    return false;
}

bool Field::is_tried(const int& x, const int& y)
{
    if (arr[y][x] == tried_sign)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Field::try_point(const int& x, const int& y)
{
    arr[y][x] = tried_sign;
}

int Field::get_deck_number(const int& x, const int& y)
{
    return get_ship(x,y).get_deck_number();
}

void Field::show_war_fog()
{
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if(arr[i][j] == ship_sign)
                std::cout << field_sign;
            else
                std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
}

Ship& Field::get_ship(const int &x, const int &y)
{
    Ship *temp;
    for(auto &el : ships)
    {
        if(el->has_coordinate(x, y))
        {
            temp = el;
            break;
        }
    } 
    return *temp;
}

