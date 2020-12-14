#ifndef PROJECT_STAGE1_INCLUDE_MAP_H_
#define PROJECT_STAGE1_INCLUDE_MAP_H_

#include <vector>
#include "entities.h"


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
    void print();
    void motion();
    size_t get_pos(size_t x, size_t y);
    void set_pos(size_t x, size_t y, int type);
};


#endif  // PROJECT_STAGE1_INCLUDE_MAP_H_
