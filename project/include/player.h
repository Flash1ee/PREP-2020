#pragma once

#include <vector>
#include <memory>
#include <string>


#include "enemy.h"
#include "map.h"

#define MOVE_SUCCESS 1
#define PLAYER_HP 100
#define BASE_DMG 1
#define MAX_ARM 20

#define MOVE 11

struct suit {
    bool armor;
    bool helmet;
    bool shield;
    bool pants;
    bool t_shirt;
};

class Player;

bool is_enemy(Entities character);
void print_found(size_t clothes);
void print_mob(size_t type);
bool print_clothes(std ::string user_act);
std::string is_clothes(size_t &val);
int is_battle(Player *player, Map *map, std::string user_act, actions acts);
std::stringstream form_msg(Player *p, actions &acts, bool &battle, Map *map);

class Player {
 private:
    size_t pos_x;
    size_t pos_y;

    size_t hp;
    size_t dmg;
    size_t arm;
    size_t arm_wgt;

    bool change_pos;
    bool m_stage;

    std::vector <bool> clothes;

 public:
    explicit Player(bool stage)
    : pos_x(0), pos_y(0), hp(PLAYER_HP), dmg(BASE_DMG),
      arm(0), arm_wgt(0), change_pos(0), m_stage(stage), clothes(5) { }
    int action(Map *map);

    size_t get_hp();
    size_t get_dmg();
    size_t get_pos_x();
    size_t get_pos_y();
    bool get_stage();
    size_t get_arm();

    int set_guard(Clothes &armor);
    int set_move(std::string str, actions data, Map *map);
    int set_arm(std::string str, Map *map);
    void set_pos(bool pos);

    void add_arm(Clothes thing);
    void dec_arm(Clothes thing);

    void damage(size_t power);
    void move_left();
    void move_right(Map *map);
    void move_up(Map *map);
    void move_down();

    bool check_clothes(size_t pos);
    std::string gear_message(size_t map_type);

    void print_pos(Map *map);
};

