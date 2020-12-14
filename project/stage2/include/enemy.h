#ifndef PROJECT_STAGE2_INCLUDE_ENEMY_H_
#define PROJECT_STAGE2_INCLUDE_ENEMY_H_

#define WOLF_HP 6
#define DOG_HP 3
#define RAT_HP 2

#define WOLF_DMG 10
#define DOG_DMG 5
#define RAT_DMG 3
#define BASE_DMG 1

#include <iostream>

#include "player.h"

class Enemy {
 private:
    size_t hp;
    size_t dmg;

 public:
    Enemy() : hp(0), dmg(0) {
    }
    void damage(size_t power);
    explicit Enemy(size_t type);
    size_t get_hp();
    size_t get_dmg();
};

#endif  // PROJECT_STAGE2_INCLUDE_ENEMY_H_
