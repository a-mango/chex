//
// Created by acm on 5/6/23.
//

#include "util.h"

#include <stdio.h>
#include <wchar.h>


static const wchar_t* CX_LOG_HEADERS[] = {
    L"[INFO]   ",
    L"[WARN]   ",
    L"[ERROR]  ",
};

void cx_log(char const *msg, cx_log_type_t type) {
    wprintf(L"%ls%s\n", CX_LOG_HEADERS[type], msg);
}

size_t cx_num_bits_set(uint64_t n) {
    size_t count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

size_t cx_lsb(uint64_t n) {
    size_t pos = 0;
    while (!(n & 1)) {
        ++pos;
        n >>= 1;
    }
    return pos;
}

size_t cx_msb(uint64_t n) {
    size_t pos = 0;
    while (n) {
        ++pos;
        n >>= 1;
    }
    return pos;
}
