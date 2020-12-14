#include "player.h"

#include <iostream>

#include "retcodes.h"

int Player::set_move(std::string str, actions data) {
    if (!data.left.empty() && !str.compare(data.left)) {
        move_left();
        return true;
    }
    if (!data.right.empty() && !str.compare(data.right)) {
        move_right();
        return true;
    }
    if (!data.down.empty() && !str.compare(data.down)) {
        move_down();
        return true;
    }
    if (!data.up.empty() && !str.compare(data.up)) {
        move_up();
        return true;
    }
    return false;
}
void print_mob(size_t type) {
    if (type == WOLF) {
        std::cout << "\nwolf found, 6 hp\n";
    } else if (type == DOG) {
        std::cout << "\ndog found, 3 hp\n";
    } else if (type == RAT) {
        std::cout << "\nrat found, 2 hp\n";
    }
}
std::stringstream Player ::form_msg(actions &acts, bool &battle) {
    std::stringstream msg;
    size_t cols = this->get_cols();
    size_t rows = this->get_rows();

    size_t enemy_type = Map::get_pos(this->pos_x, this->pos_y);
    battle = false;
    if (enemy_type != EMPTY && enemy_type != PLAYER) {
        battle = true;
    }
    msg << "Supported actions:\n";
    bool val = false;
    if (battle) {
        msg << " * kick enemy\n";
    } else {
        if (this->pos_x) {
            acts.left = "move left";
            msg << " * move left\n";
            val = true;
        }
        if (this->pos_x != cols - 1) {
            acts.right = "move right";
            msg << " * move right\n";
            val = true;
        }
        if (this->pos_y) {
            acts.down = "move down";
            msg << " * move down\n";
            val = true;
        }
        if (this->pos_y != rows - 1) {
            acts.up = "move up";
            msg << " * move up\n";
            val = true;
        }
        if (!val) {
            msg << std::endl;
        }
    }
    msg << "" << this->pos_x << " x " << this->pos_y << ", hp: " << this->hp << " > ";
    return msg;
}
int Player::action() {
    std::string user_act;
    actions possible_acts;
    bool battle = false;

    std::stringstream message;
    message = form_msg(possible_acts, battle);

    std ::cout << message.str();
    if (!getline(std::cin, user_act)) {
        return EXIT;
    }
    if (battle) {
        if (!user_act.compare("kick enemy")) {
            size_t type_enemy = Map::get_pos(this->pos_x, this->pos_y);
            Enemy opponent(type_enemy);
            while (true) {
                opponent.damage(this->get_dmg());
                if (opponent.get_hp()) {
                    this->damage(opponent.get_dmg());
                }
                if (!this->get_hp() || !opponent.get_hp()) {
                    break;
                }
                std ::cout << "\nenemy kicked. Enemy hp: " << opponent.get_hp() << std::endl;
                message = form_msg(possible_acts, battle);
                std ::cout << message.str();
                message.clear();
                if (!getline(std::cin, user_act)) {
                    return EXIT;
                }
                if (user_act.compare("kick enemy")) {
                    return -1;
                }
            }
            if (!this->get_hp()) {
                std::cout << "\nplayer died\n";
                return PLAYER_DIE;
            }
            set_pos(this->pos_x, this->pos_y, EMPTY);
            std ::cout << "\nenemy killed" << std::endl;
            return MOVE_SUCCESS;

        } else {
            return EXIT;
        }
    }
    int rc = set_move(user_act, possible_acts);
    if (rc == false) {
        return EXIT;
    }
    size_t type = get_pos(pos_x, pos_y);
    if (type == EMPTY || type == PLAYER) {
        std ::cout << "\nmoved\n";
    } else {
        print_mob(type);
    }
    message.clear();
    return MOVE_SUCCESS;
}
void Player::move_down() {
    this->pos_y--;
}
void Player::move_up() {
    this->pos_y++;
}
void Player::move_right() {
    this->pos_x++;
}
void Player::move_left() {
    this->pos_x--;
}
void Player::damage(size_t power) {
    if (this->hp < power) {
        this->hp = 0;
        return;
    }
    this->hp -= power;
}
size_t Player::get_hp() {
    return this->hp;
}
size_t Player::get_dmg() {
    return this->dmg;
}
void Player::print_pos() {
    std::cout << "x: " << Map::get_rows() - pos_x << " y: " << pos_y << std::endl;
}
