#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#ifndef FILE_HANDLER
#define FILE_HANDLER



#define handle_error(msg) do {exit(EXIT_FAILURE);} while (0)

typedef struct file
{
    FILE *fp;
    off_t size;
} file;


void openFiles(int argc, char **argv);
    



#endif