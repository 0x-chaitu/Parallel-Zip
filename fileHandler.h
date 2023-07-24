#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#ifndef FILE_HANDLER
#define FILE_HANDLER



#define handle_error(msg) do {exit(EXIT_FAILURE);} while (0)
extern long chunks;
extern long pageSize;

typedef struct file
{
    int fp;
    off_t size;
} file;


file *openFiles(int argc, char **argv);
long getChunks();
long getPageSize();
    



#endif