#include "logger.h"

char* log_file;

static char* _getTime(const char* format)
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char* buffer = (char*)malloc(32);
    if (!buffer) return NULL;
    strftime(buffer, 32, format, t);
    return buffer;
}

static void _ntlog(const char* text, const char* level, const char* color, va_list args)
{
    char formatted_text[256];
    char string_to_save[512];
    char string_to_print[512];
    char* time_buffer = _getTime("%H:%M:%S");

    vsnprintf(formatted_text, sizeof(formatted_text), text, args);
    snprintf(string_to_save, sizeof(string_to_save), "%s | [ %-5s ] | %s\n", time_buffer, level, formatted_text);
    free(time_buffer);

    snprintf(string_to_print, sizeof(string_to_print), "%s%s\033[0m", color, string_to_save);

    
    if (log_file) 
    {
        FILE* fp = fopen(log_file, "a");
        if (fp) 
        {
            fputs(string_to_save, fp);
            fclose(fp);
        }
    }

    printf("%s", string_to_print);
    
}

int gen_log_file()
{
    char base_name[256];
    char final_name[512];
    char* time_buffer = _getTime("%d_%m_%Y");
    int is_folder_created;


    if (!time_buffer) { return -1; }

    is_folder_created = mkdir(LOG_FOLDER);

    snprintf(base_name, sizeof(base_name), "%s-yaml_launch.log", time_buffer);
    free(time_buffer);

    int suffix = 0;
    snprintf(final_name, sizeof(final_name), "%s/%s", LOG_FOLDER, base_name);

    while (_access(final_name, 0) == 0) {
        suffix++;
        snprintf(final_name, sizeof(final_name), "%s/%.*s(%d).log",
            LOG_FOLDER, (int)(strlen(base_name) - 4), base_name, suffix);
    }

    FILE* log_file_ptr = fopen(final_name, "w");

    if (log_file_ptr)
    {

        char auto_gen_string[] = 
        "/*\n"
        "/\n"
        "/\tThis file was generated automatically using yaml launcher :)\n"
        "/\n"
        "*/\n\n";

        fputs(auto_gen_string, log_file_ptr);
        fclose(log_file_ptr);

        log_file = _strdup(final_name);
        return 0;
    }
    else { return -1; }
}



void log_trace(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    _ntlog(text, "trace", "\033[38;2;153;255;153m", args);
    va_end(args);
}

void log_info(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    _ntlog(text, "info", "\033[38;2;102;204;255m", args);
    va_end(args);
}

void log_warn(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    _ntlog(text, "warn", "\033[38;2;255;255;153m", args);
    va_end(args);
}

void log_error(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    _ntlog(text, "error", "\033[38;2;255;153;153m", args);
    va_end(args);
}

void log_fatal(const char* text, ...)
{
    va_list args;
    va_start(args, text);
    _ntlog(text, "fatal", "\033[7m\033[38;2;255;80;80m", args);
    va_end(args);
}