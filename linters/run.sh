#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=cpp --headers=h,hpp --filter=-runtime/references,-legal/copyright,-build/include_subdir,-whitespace/line_length project/stage1/include/* project/stage1/src/* project/stage2/include/* project/stage2/src/*

print_header "SUCCESS"
