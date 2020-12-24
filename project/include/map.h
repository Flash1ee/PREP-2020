#pragma once

#include <vector>
#include <string>
struct actions {
    std::string left;
    std::string right;
    std::string down;
    std::string up;
};

enum Entities {
    EMPTY,
    PLAYER,
    WOLF,
    DOG,
    RAT,
    PLAYER_DIE,
    COUNT,
};
enum Clothes {
    T_SHIRT = COUNT,
    ARMOR,
    HELMET,
    PANTS,
    SHIELD,
};
class Map {
 private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<size_t> > field;

 public:
    Map() : rows(0), cols(0) {}
    Map(Map& map)
    : rows(map.rows), cols(map.cols), field(map.field) {}
    explicit Map(std ::istream &f);

    size_t get_rows();
    size_t get_cols();
    size_t get_pos(size_t x, size_t y);

    void set_pos(size_t x, size_t y, int type);
};

int get_clothes(std::string str);
