#ifndef PROJECT_INCLUDE_PLAYER_H_
#define PROJECT_INCLUDE_PLAYER_H_

#include <string>

#define MOVE_SUCCESS 1
#define PLAYER_HP 100
#define BASE_DMG 1

#include "enemy.h"
#include "map.h"

class Player : public Map {
 private:
    size_t pos_x;
    size_t pos_y;

    size_t hp;
    size_t dmg;
    std::stringstream form_msg(actions &acts, bool &battle);

 public:
    Player() : pos_x(0), pos_y(0), hp(PLAYER_HP), dmg(BASE_DMG) {
    }
    explicit Player(Map &map) : Map(map),
    pos_x(0), pos_y(0), hp(PLAYER_HP), dmg(BASE_DMG) {
    }
    size_t get_hp();
    size_t get_dmg();
    void print_pos();
    void damage(size_t power);
    int set_move(std::string str, actions data);
    int action();
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};

#endif  // PROJECT_INCLUDE_PLAYER_H_
