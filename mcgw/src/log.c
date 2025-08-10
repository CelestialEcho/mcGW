#include "log.h"

FILE* log_file_ptr;
char* log_file;
BOOL write_file = FALSE;

char* get_time(const char* format)
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char* buffer = (char*)malloc(32);
    if (!buffer) return NULL;
    strftime(buffer, 32, format, t);
    return buffer;
}

int gen_log_file()
{
    char final_name[256];
    char* time_buffer = get_time("%d_%m_%Y-%H:%M:%S");
    if (!time_buffer) { return -1; }

    snprintf(final_name, sizeof(final_name), "%s-mcgw-launch.log", time_buffer);
    free(time_buffer);

    log_file_ptr = fopen(final_name, "w");

    if (log_file_ptr)
    {

        char auto_gen_string[] = 
        "/*\n"
        "/\n"
        "/\tThis file was generated automatically using mcgw launcher :)\n"
        "/\n"
        "*/";

        fputs(auto_gen_string, log_file_ptr);
        fclose(log_file_ptr);

        log_file = strdup(final_name);
        return 0;
    }
    else { return -1; }
}


void log_trace(const char* text, ...)
{
    log_file_ptr = fopen(log_file, "w");
    if (log_file_ptr)
    {
        printf("Log file opened");
    }
}

void log_info(const char* text, ...)
{
    
}

void log_warn(const char* text, ...)
{
    
}

void log_success(const char* text, ...)
{

}

void log_error(const char* text, ...)
{
    
}

void log_fatal(const char* text, ...)
{
    
}

void zip_log()
{

}