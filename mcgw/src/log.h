#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#define BOOL char
#define FALSE 0
#define TRUE 1

int gen_log_file();
void log_trace(const char* text, ...);
void log_info(const char* text, ...);
void log_warn(const char* text, ...);
void log_success(const char* text, ...);
void log_error(const char* text, ...);
void log_fatal(const char* text, ...);
void zip_log();

#endif /* LOG_H */
