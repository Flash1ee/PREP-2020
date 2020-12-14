#include "enemy.h"

Enemy::Enemy(size_t type) {
    switch (type) {
        case WOLF:
            this->hp = WOLF_HP;
            this->dmg = WOLF_DMG + BASE_DMG;
            break;
        case RAT:
            this->hp = RAT_HP;
            this->dmg = RAT_DMG + BASE_DMG;
            break;
        case DOG:
            this->hp = DOG_HP;
            this->dmg = DOG_DMG + BASE_DMG;
            break;
    }
}
void Enemy::damage(size_t power) {
    if (this->hp < power) {
        this->hp = 0;
        return;
    }
    this->hp -= power;
}
size_t Enemy::get_hp() {
    return this->hp;
}
size_t Enemy::get_dmg() {
    return this->dmg;
}
