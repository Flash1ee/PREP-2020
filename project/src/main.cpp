#include <cstring>
#include <iostream>

#include "map.h"
#include "player.h"
#include "retcodes.h"

#define map "--map"

int main(int argc, const char** argv) {
    try {
        if (argc != 3 || strcmp(map, argv[1])) {
            throw ARG_ERR;
        }
    } catch (Errors) {
        return ARG_ERR;
    }

    std::ifstream f(argv[2]);
    try {
        if (!f.is_open()) {
            throw IO_FILE_ERR;
        }
    } catch (int) {
        f.close();
        return IO_FILE_ERR;
    }
    Map field(f);
    Player player(field);
    int rc = player.action();
    while (rc != PLAYER_DIE && rc != EXIT) {
        try {
            rc = player.action();
        } catch (const char*) {
            std::cout << "ERROR" << std::endl;
            break;
        }
    }
    f.close();
    return 0;
}
