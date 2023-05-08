#ifndef CHEX_LOG_H
#define CHEX_LOG_H

#include "print.h"


#define CX_LOG_STREAM CX_DEFAULT_STREAM

extern cx_cstr CX_LOG_HEADERS[];

typedef enum LogType {
    CX_LOG_INFO,
    CX_LOG_WARN,
    CX_LOG_ERROR,
    CX_LOG_DEBUG,
    CX_LOG_FATAL,
} cx_log_t;

void cx_log(cx_cstr msg, cx_log_t type);
void cx_log_va(cx_cstr fmt, cx_log_t type, ...);

#endif  // CHEX_LOG_H
