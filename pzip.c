#include <stdio.h>
#include "fileHandler.h"
#include "workHandler.h"

int main(int argc, char **argv){

    file *files;
    files = openFiles(argc, argv);
    if (files != NULL ) {
        spawnWorkers(files, argc);
    }

    return 0;
}