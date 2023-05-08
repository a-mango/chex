#ifndef CHEX_LOG_H
#define CHEX_LOG_H

#include "print.h"

static const wchar_t *CX_LOG_HEADERS[] = {
    L"[" ANSI_COLOR_CYAN "INFO" ANSI_COLOR_RESET "]   ",
    L"[" ANSI_COLOR_MAGENTA "WARN" ANSI_COLOR_RESET "]   ",
    L"[" ANSI_COLOR_RED "ERROR" ANSI_COLOR_RESET "]  ",
    L"[" ANSI_COLOR_YELLOW "DEBUG" ANSI_COLOR_RESET "]  ",
};

typedef enum LogType {
    CX_LOG_INFO,
    CX_LOG_WARN,
    CX_LOG_ERROR,
    CX_LOG_DEBUG,
    CX_LOG_FATAL,
} cx_log_type_t;

void cx_log(char const *msg, cx_log_type_t type);
void cx_log_va(wchar_t const *msg, cx_log_type_t type, ...);

#endif  // CHEX_LOG_H
