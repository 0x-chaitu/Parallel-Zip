#include "fileHandler.h"

void openFiles(int argc, char ** argv)
{
    file *files;
    files = malloc(sizeof(file) * (argc-1));
    if (files == NULL) {
        handle_error("Err: ");
    }
    for (int i = 1; i < argc; i++) {
        int fd ;
        if ((fd = open(argv[i], O_RDONLY)) == -1){
            handle_error("Err: ");
        };
        
        struct stat sd;
        if (fstat(fd, &sd) == -1){
            handle_error("Err: ");
        };
        files[i-1].fp = fd;
        files[i-1].size = sd.st_size; 
        close(fd);

    }

}