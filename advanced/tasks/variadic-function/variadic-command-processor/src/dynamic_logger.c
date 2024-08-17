#include "dynamic_logger.h"
#include "project_config.h"

static pthread_mutex_t log_mutex;
static FILE *log_file;

void init_logger() {
#if ENABLE_THREAD_SAFE_LOGGING
    pthread_mutex_init(&log_mutex, NULL);
#endif
    log_file = fopen(LOG_FILE_NAME, "w");
}

void log_message(const char *format, ...) {
    va_list args;
    va_start(args, format);

#if ENABLE_THREAD_SAFE_LOGGING
    pthread_mutex_lock(&log_mutex);
#endif
    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");
    fflush(log_file);

#if ENABLE_THREAD_SAFE_LOGGING
    pthread_mutex_unlock(&log_mutex);
#endif

    va_end(args);
}

void cleanup_logger() {
    if (log_file) {
        fclose(log_file);
    }
#if ENABLE_THREAD_SAFE_LOGGING
    pthread_mutex_destroy(&log_mutex);
#endif
}
