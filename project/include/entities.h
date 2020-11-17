#ifndef PROJECT_INCLUDE_ENTITIES_H_
#define PROJECT_INCLUDE_ENTITIES_H_

#include <fstream>
#include <iostream>
#include <sstream>
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

#endif  // PROJECT_INCLUDE_ENTITIES_H_
