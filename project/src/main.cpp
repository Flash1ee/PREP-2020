#include <cstring>
#include <iostream>
#include <fstream>

#include "map.h"
#include "player.h"
#include "retcodes.h"

#define map "--map"

int main(int argc, const char** argv) {
    if (!argc) {
        throw ARG_ERR;
    }
    const char *f_name;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], map)) {
            f_name = argv[i + 1];
            break;
        }
    }
    if (!f_name) {
        throw ARG_ERR;
    }
    std::ifstream f(f_name);
    try {
        if (!f.is_open()) {
            throw IO_FILE_ERR;
        }
    } catch (int) {
        f.close();
        return IO_FILE_ERR;
    }
    Map field(f);
    f.close();

    Player player(field);
    int rc = player.action();
    while (rc != PLAYER_DIE && rc != EXIT) {
        rc = player.action();
    }
    return EXIT_SUCCESS;
}
