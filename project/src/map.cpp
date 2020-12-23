#include <fstream>
#include <map>
#include "map.h"

std::map<std::string, int> clothes = {
    {"armor", ARMOR},
    {"helmet", HELMET},
    {"shield", SHIELD},
    {"pants", PANTS},
    {"T-Shirt", T_SHIRT},
};

Map ::Map(std ::istream& f) {
    f >> this->cols >> this->rows;
    if (!this->rows || !this->cols) {
        throw "Empty play field";
    }
    field.resize(this->rows);
    for (size_t i = 0; i < rows; i++) {
        field[i].resize(cols);
    }
    std::string line;
    size_t r_tmp, c_tmp;
    while (f >> c_tmp >> r_tmp >> line) {
        if (!line.compare("wolf")) {
            field[rows - r_tmp - 1][c_tmp] = WOLF;
        } else if (!line.compare("rat")) {
            field[rows - r_tmp - 1][c_tmp] = RAT;
        } else if (!line.compare("dog")) {
            field[rows - r_tmp - 1][c_tmp] = DOG;
        } else {
            field[rows - r_tmp - 1][c_tmp] = get_clothes(line);
        }
    }
    if (!f.eof()) {
        throw "read error, not found eof";
    }
    field[rows - 1][0] = PLAYER;
}

size_t Map::get_pos(size_t x, size_t y) {
    return this->field[this->rows - y - 1][x];
}

size_t Map ::get_rows() {
    return this->rows;
}
size_t Map ::get_cols() {
    return this->cols;
}

int get_clothes(std::string str) {
    if (clothes.find(str) == clothes.end()) {
        return -1;
    }
    
    return clothes[str];
}

void Map::set_pos(size_t x, size_t y, int type) {
    this->field[this->rows - y - 1][x] = type;
}
