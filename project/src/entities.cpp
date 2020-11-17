#include "map.h"

Map ::Map() : rows(0), cols(0) {
}
Map ::Map(Map& map)
    : rows(map.rows), cols(map.cols), field(map.field) {
}
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
            throw "valide enemy not found.";
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

void Map ::print() {
    std::cout << "rows = " << this->rows << std::endl;
    std::cout << "cols = " << this->cols << std::endl;

    for (size_t i = 0; i < this->rows; i++) {
        for (size_t j = 0; j < this->cols; j++) {
            std::cout << this->field[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
size_t Map ::get_rows() {
    return this->rows;
}
size_t Map ::get_cols() {
    return this->cols;
}
void Map::set_pos(size_t x, size_t y, int type) {
    this->field[this->rows - y - 1][x] = type;
}
