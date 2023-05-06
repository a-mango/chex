//
// Created by acm on 5/6/23.
//

#include "util.h"
#include <stdio.h>
#include <wchar.h>

void cx_log(char const *msg, cx_log_type_t type) {
    wprintf(L"%s\n", msg);
}

void cx_print_bin(cx_piece_t n) {
    for (int i = 0; i < 64; i++) {
        wprintf(L"%lu", (n >> (63 - i)) & 1);
    }
    wprintf(L"\n");
}
