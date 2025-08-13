#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <io.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define LOG_FOLDER "mcgw_logs"

int gen_log_file();
void log_trace(const char* text, ...);
void log_info(const char* text, ...);
void log_warn(const char* text, ...);
void log_error(const char* text, ...);
void log_fatal(const char* text, ...);

#ifdef __cplusplus
}
#endif

#endif /* LOG_H */
