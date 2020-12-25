#include <cstring>
#include <iostream>
#include <fstream>

#include "stages.h"
#include "retcodes.h"

#define map "--map"
#define stage_2 "--view-armor"


int main(int argc, const char** argv) {
    if (!argc) {
        throw ARG_ERR;
    }
    bool stage = false;  //  false - stage 1 true - stage2

    std::string f_name;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], map)) {
            f_name = argv[i + 1];
        }
        if (!strcmp(argv[i], stage_2)) {
            stage = true;
        }
    }

    if (f_name.empty()) {
        throw ARG_ERR;
    }

    return game(f_name, stage);
}
