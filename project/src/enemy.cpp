#include "enemy.h"

Enemy::Enemy(size_t type) {
    switch (type) {
        case WOLF:
            set_hp(WOLF_HP);
            set_dmg(WOLF_DMG + BASE_DMG);
            break;
        case RAT:
            set_hp(RAT_HP);
            set_dmg(RAT_DMG + BASE_DMG);
            break;
        case DOG:
            set_hp(DOG_HP);
            set_dmg(DOG_DMG + BASE_DMG);
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
void Enemy::set_dmg(size_t dmg) {
    this->dmg = dmg;
}
void Enemy::set_hp(size_t hp) {
    this->hp = hp;
}

