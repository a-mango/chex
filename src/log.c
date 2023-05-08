#include "log.h"

#include <stdarg.h>
#include <wchar.h>

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