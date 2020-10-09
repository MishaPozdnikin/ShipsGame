#include <iostream>
#include <string>
#include "Field.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "Ship.h"

int enemy_x, enemy_y, my_x, my_y;
bool end = false;


void enemy_shoot(Field* my_field)
{
    while (1)
    {
        my_x = rand() % my_field->get_height();
        my_y = rand() % my_field->get_width();
        while (my_field->is_tried(my_x, my_y))
        {
            my_x = rand() % my_field->get_height();
            my_y = rand() % my_field->get_width();
        }
        while (my_field->is_destroyed_sign(my_x, my_y))
        {
            my_x = rand() % my_field->get_height();
            my_y = rand() % my_field->get_width();
        }
        std::cout << "\nEnemy tries: x = " << my_x << " y = " << my_y << ".\n\n";
        if (my_field->is_ship(my_x, my_y))
        {
            my_field->destroy_ship(my_x, my_y);
            std::cout << "Your ship has been destroyed at x " << my_x << " y " << my_y << ".\n";
            if (!my_field->get_ships_num())
            {
                std::cout << "You lose!\n";
                end = true;
                return;
            }
            std::cout << my_field->get_ships_num() << " ships left. " << "Your field:\n";
            my_field->show_field();
        }
        else
        {
            my_field->try_point(my_x, my_y);
            break;
        }
    }
}

void player_shoot(Field* enemy_field, Field* my_field)
{
    while (1)
    {
        std::cout << "Enter point x: ";
        std::cin >> enemy_x;
        if (enemy_x == 99)
        {
            std::cout << "\nEnemy field:\n";
            enemy_field->show_field();
            continue;
        }
        else if(enemy_x == 0)
        {
            std::cout << "\nEnemy field:\n";
            enemy_field->show_war_fog();
            continue;
        }
        std::cout << "Enter point y: ";
        std::cin >> enemy_y;
        if (enemy_y == 99)
        {
            std::cout << "\nYour field:\n";
            my_field->show_field();
            continue;
        }
        else if(enemy_y == 0)
        {
            std::cout << "\nEnemy field:\n";
            enemy_field->show_war_fog();
            continue;
        }
        if (enemy_x < enemy_field->get_width() + 1 && enemy_y < enemy_field->get_height() + 1)
        {
            if (enemy_field->is_destroyed_sign(enemy_x, enemy_y))
            {
                std::cout << "Try another values for x and y.\n";
                continue;
            }
            if (enemy_field->is_tried(enemy_x, enemy_y))
            {
                std::cout << "Try another values for x and y.\n";
                continue;
            }
            if (enemy_field->is_ship(enemy_x, enemy_y))
            {
                enemy_field->destroy_enemys_ship(enemy_x, enemy_y);
                if (!enemy_field->get_ships_num())
                {
                    std::cout << "You win!\n";
                    end = true;
                    return;
                }
                std::cout << enemy_field->get_ships_num() << " enemy`s ships left.\n";
                continue;
            }
            else
            {
                enemy_field->try_point(enemy_x, enemy_y);
                break;
            }
        }
        else
        {
            std::cout << "Try another values for x and y.\n";
            continue;
        }
    }
}

void logic(Field* enemy_field, Field* my_field)
{
    while (!end)
    {
        player_shoot(enemy_field, my_field);
        if (end)return;
        enemy_shoot(my_field);
        if (end)return;
    }
}

void greeting()
{
    std::cout << "*************************Durka inc. presents*************************\n";
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\n\n\n*****************************DurkaShips!!!*************************\n";
    //std::this_thread::sleep_for(std::chrono::seconds(1));
}


Field* init_field(const int height, const int width)
{
    Field *f = new Field(height, width);
    f->spawn_ships(4, 1);
    f->spawn_ships(3, 2);
    f->spawn_ships(2, 3);
    f->spawn_ships(1, 4);
    return f;
}

int main(int argc, char* argv[])
{
//    greeting();
    int height,
        width;
    std::cout << "Enter height of field: ";
    std::cin >> height;
    std::cout << "Enter width of field: ";
    std::cin >> width;
    srand(time(NULL));
    Field* my_field = init_field(height, width);
    Field* enemy_field = init_field(height, width);
    std::cout << "Your field:\n";
    my_field->show_field();

    std::cout << "\n----------------------------------------------------------\n";
    std::cout << "In order to see enemy's field enter '0'\n\n";
    logic(enemy_field, my_field);

//    Ship s(2);
//    s.add_ship_coordinate(0,0);
//    s.add_ship_coordinate(1,0);
//    //std::cout<<s.get_value(0,0) << "\n";
//    //std::cout<<s.get_value(1,0) << "\n";
//    //s.hit(0,0);
//    auto it = s.get_coordinates();

//    std::cout<<it[0].first << " " << it[0].second;
   
//    s.hit(1,0);
//    std::cout<<s.get_value(1,0) << "\n";
//    std::cout<<s.get_health()<<"\n";
//    std::cout<<s.get_deck_number()<<"\n";
//    std::cout<<s.get_hited_deck_number()<<"\n";
//    std::cout<<s.get_is_destroyed()<<"\n";

    return 0;
}
