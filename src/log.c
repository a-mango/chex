#include "log.h"

#include <assert.h>
#include <stdarg.h>
#include <wchar.h>


cx_cstr CX_LOG_HEADERS[] = {
    L"[" ANSI_COLOR_CYAN "INFO" ANSI_COLOR_RESET "]   ",
    L"[" ANSI_COLOR_MAGENTA "WARN" ANSI_COLOR_RESET "]   ",
    L"[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET "]  ",
    L"[" ANSI_COLOR_YELLOW "DEBUG" ANSI_COLOR_RESET "]  ",
    L"[" ANSI_COLOR_RED "FATAL" ANSI_COLOR_RESET "]  ",
};

void cx_log(cx_cstr msg, cx_log_t type) {
    cx_log_va(L"%"CX_PRIWSTR, type, msg);
}

void cx_log_va(cx_cstr fmt, cx_log_t type, ...) {
    assert(type < CX_LOG_FATAL);
    assert(fmt != NULL);

    va_list args;
    va_start(args, type);
    cx_print(CX_LOG_STREAM, L"%"CX_PRIWSTR, CX_LOG_HEADERS[type]);
    cx_print_va(CX_LOG_STREAM, fmt, args);
    cx_print(CX_LOG_STREAM, L"\n");
    va_end(args);
}
