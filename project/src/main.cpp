#include <cstring>
#include <iostream>
#include <fstream>

#include "stages.h"
#include "retcodes.h"

#define map "--map"
#define stage_1 "stage1"
#define stage_2 "stage2"


int main(int argc, const char** argv) {
    if (!argc) {
        throw ARG_ERR;
    }

    std::string f_name;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], map)) {
            f_name = argv[i + 1];
            break;
        }
    }

    if (f_name.empty()) {
        throw ARG_ERR;
    }

    bool stage = false;  //  false - stage 1 true - stage2

    if (f_name.find(stage_1) != std::string::npos) {
        return game(f_name, stage);
    }
    if (f_name.find(stage_2) != std::string::npos) {
        stage = true;
        return game(f_name, stage);
    }

    return EXIT_FAILURE;
}
