#include <map>
#include <sstream>
#include <string>

#include "retcodes.h"
#include "player.h"
#include "map.h"

#define CLOTHES 5

std::map<Clothes, std::vector<size_t>> arm_weight = {
    {T_SHIRT, {1, 1}},
    {ARMOR, {3, 3}},
    {HELMET, {3, 2}},
    {SHIELD, {5, 7}},
    {PANTS, {1, 1}},
};

std::map<std::string, int> picks = {
    {"pick T-Shirt", T_SHIRT},
    {"pick armor", ARMOR},
    {"pick helmet", HELMET},
    {"pick pants", PANTS},
    {"pick shield", SHIELD},
};

std::map<std::string, int> throws = {
    {"throw T-Shirt", T_SHIRT},
    {"throw armor", ARMOR},
    {"throw helmet", HELMET},
    {"throw pants", PANTS},
    {"throw shield", SHIELD},
};

std::string Player ::gear_message(size_t map_type) {
    std::string out;
    std::string picked;

    if (!clothes[map_type - CLOTHES]) {
        out += " * pick ";

        switch (map_type) {
            case T_SHIRT:
                out += "T-Shirt\n";
                break;
            case ARMOR:
                out += "armor\n";
                break;
            case HELMET:
                out += "helmet\n";
                break;
            case PANTS:
                out += "pants\n";
                break;
            case SHIELD:
                out += "shield\n";
                break;
        }
    }
    for (size_t i = T_SHIRT; i <= SHIELD; i++) {
        if (clothes[i - CLOTHES] && !change_pos) {
            switch (i) {
                case T_SHIRT:
                    out += " * throw T-Shirt\n";
                    break;
                case ARMOR:
                    out += " * throw armor\n";
                    break;
                case HELMET:
                    out += " * throw helmet\n";
                    break;
                case PANTS:
                    out += " * throw pants\n";
                    break;
                case SHIELD:
                    out += " * throw shield\n";
                    break;
            }
        }
    }
    return out;
}

std::string is_clothes(size_t &val) {
    std::string out;

    if (val == T_SHIRT) {
        out += "\nT-Shirt found\n";

    } else if (val == ARMOR) {
        out += "\narmor found\n";

    } else if (val == HELMET) {
        out += "\nhelmet found\n";

    } else if (val == PANTS) {
        out += "\npants found\n";

    } else if (val == SHIELD) {
        out += "\nshield found\n";
    }

    return out;
}

bool is_enemy(size_t &character) {
    if (character == EMPTY || character == PLAYER) {
        return false;
    }
    for (size_t i = ARMOR; i <= T_SHIRT; i++) {
        if (i == character) {
            return false;
        }
    }
    for (size_t i = WOLF; i <= RAT; i++) {
        if (i == character) {
            return true;
        }
    }

    return false;
}
int Player::set_move(std::string str, actions data) {
    if (!data.left.empty() && !str.compare(data.left)) {
        move_left();
        return MOVE;
    }
    if (!data.right.empty() && !str.compare(data.right)) {
        move_right();
        return MOVE;
    }
    if (!data.down.empty() && !str.compare(data.down)) {
        move_down();
        return MOVE;
    }
    if (!data.up.empty() && !str.compare(data.up)) {
        move_up();
        return MOVE;
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

bool check_clothes(size_t pos) {
    if (pos >= T_SHIRT && pos < SHIELD) {
        return true;
    }

    return false;
}

std::stringstream Player ::form_msg(actions &acts, bool &battle) {
    std::stringstream msg;
    size_t cols = this->get_cols();
    size_t rows = this->get_rows();

    size_t map_type = Map::get_pos(this->pos_x, this->pos_y);
    battle = is_enemy(map_type);
    bool gear = false;

    if (m_stage) {
        gear = !is_clothes(map_type).empty();
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
        if (gear) {
            msg << gear_message(map_type);
            change_pos = EMPTY;
        }
        if (!val) {
            msg << std::endl;
        }
    }
    msg << "" << this->pos_x << " x " << this->pos_y << ", hp: " << this->hp;

    if (m_stage) {
        msg << ", armor: " << this->arm;
    }

    msg << " > ";

    return msg;
}

int Player::set_arm(std::string str) {
    int pos_type = get_pos(this->pos_x, this->pos_y);

    auto tmp = picks.find(str);

    if (tmp != picks.end()) {
        if (tmp->second == pos_type) {
            clothes[tmp->second - 5] = true;

            add_arm(static_cast<Clothes>(pos_type));
            change_pos = pos_type;
        }
    } else {
        tmp = throws.find(str);

        if (tmp != throws.end()) {
            clothes[tmp->second - 5] = false;

            dec_arm(static_cast<Clothes>(tmp->second));
        } else {
            return ARG_ERR;
        }
    }

    return EXIT_SUCCESS;
}

void Player::dec_arm(Clothes thing) {
    arm_wgt -= arm_weight[thing][1];
    arm -= arm_weight[thing][0];

    clothes[thing - 5] = false;
}

void Player::add_arm(Clothes thing) {
    arm_wgt += arm_weight[thing][1];
    arm += arm_weight[thing][0];

    clothes[thing - 5] = true;
}

bool print_clothes(std ::string user_act) {
    if (user_act.find("pick") != std::string::npos) {
        std ::cout << "\nclothes worn\n";

        return true;
    }
    if (user_act.find("throw") != std::string::npos) {
        std::string clothes;

        clothes.assign(user_act, user_act.find(' ') + 1);
        std::cout << "\nthe " << clothes << " is thrown out\n";

        return true;
    }

    return false;
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
    size_t x_bef = pos_x;
    size_t y_bef = pos_y;
    int rc = set_move(user_act, possible_acts);

    if (rc && m_stage) {
        set_pos(x_bef, y_bef, EMPTY);
    } else if (m_stage) {
        rc = set_arm(user_act);
        if (rc) {
            return EXIT;
        }
    }

    size_t type = get_pos(pos_x, pos_y);

    if (is_enemy(type)) {
        print_mob(type);

        return MOVE_SUCCESS;
    }

    if (rc == MOVE) {
        if (!is_clothes(type).empty()) {
            std::cout << is_clothes(type);
        } else {
            std ::cout << "\nmoved\n";
        }

        return MOVE_SUCCESS;
    }

    if (m_stage) {
        print_clothes(user_act);
    }

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
    if (this->arm >= power) {
        this->hp--;
    } else {
        if (this->hp < power - this->arm) {
            this->hp = 0;
            return;
        }

        this->hp = this->hp + this->arm - power;
    }
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
