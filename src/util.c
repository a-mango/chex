//
// Created by acm on 5/6/23.
//

#include "util.h"

#include <stdio.h>

static const wchar_t *CX_LOG_HEADERS[] = {
    L"[INFO]   ",
    L"[WARN]   ",
    L"[ERROR]  ",
    L"[DEBUG]  ",
};

void cx_log(char const *msg, cx_log_type_t type) {
    wprintf(L"%ls%s\n", CX_LOG_HEADERS[type], msg);
}

void cx_log_va(wchar_t const *msg, cx_log_type_t type, ...) {
    va_list args;
    va_start(args, type);
    wprintf(L"%ls", CX_LOG_HEADERS[type]);
    vwprintf(msg, args);
    wprintf(L"\n");
    va_end(args);
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
    size_t pos = 63;
    while (!(n & (CX_BIT << pos))) {
        --pos;
    }
    return pos;
}

size_t cx_pop_lsb(uint64_t *n) {
    size_t pos = cx_lsb(*n);
    *n &= *n - 1;
    return pos;
}

size_t cx_pop_msb(uint64_t *n) {
    size_t pos = cx_msb(*n);
    *n &= *n - 1;
    return pos;
}
