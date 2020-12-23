#include <fstream>

#include "map.h"
#include "player.h"
#include "retcodes.h"

#include "stages.h"

int game(std::string f_name, bool stage) {
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

    Player player(field, stage);

    int rc = player.action();
    while (rc != PLAYER_DIE && rc != EXIT) {
        rc = player.action();
    }

    return EXIT_SUCCESS;
}
