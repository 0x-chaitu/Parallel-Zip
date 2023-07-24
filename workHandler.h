#include "fileHandler.h"
#include <pthread.h>

#ifndef WORK_HANDLER
#define WORK_HANDLER



#define handle_error(msg) do {exit(EXIT_FAILURE);} while (0)

void spawnWorkers(file *files, int argc);

typedef struct work{
    int size;
    char *addr;
} work;




#endif