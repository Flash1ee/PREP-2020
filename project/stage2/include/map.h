#ifndef PROJECT_STAGE2_INCLUDE_MAP_H_
#define PROJECT_STAGE2_INCLUDE_MAP_H_

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
};
enum Clothes {
    T_SHIRT = 5,
    ARMOR,
    HELMET,
    PANTS,
    SHIELD,
};
int get_clothes(std::string str);
class Map {
 private:
    size_t rows;
    size_t cols;
    std::vector<std::vector<size_t> > field;

 public:
    Map();
    Map(Map&);
    explicit Map(std ::istream &f);
    size_t get_rows();
    size_t get_cols();
    size_t get_pos(size_t x, size_t y);
    void set_pos(size_t x, size_t y, int type);
};


#endif  // PROJECT_STAGE2_INCLUDE_MAP_H_
