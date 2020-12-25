#include <fstream>

#include "map.h"
#include "player.h"
#include "retcodes.h"

#include "stages.h"

int game(std::string f_name, bool stage) {
    std::ifstream f(f_name);

    if (!f.is_open()) {
        f.close();
        throw IO_FILE_ERR;
    }

    Map field(f);
    f.close();

    Player player(stage);

    int rc = player.action(&field);
    while (rc != PLAYER_DIE && rc != EXIT) {
        rc = player.action(&field);
    }

    return EXIT_SUCCESS;
}
