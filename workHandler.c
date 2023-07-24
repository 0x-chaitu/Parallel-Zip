#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <assert.h>
#include <sys/mman.h>
#include "workHandler.h"
#include "fileHandler.h"


long currWork = 0;
sem_t mutex, empty, full;


void Seminit(sem_t *arg, int pshared,int value){
    assert(sem_init(arg ,pshared, value) == 0);
}

void *worker(void *arg){
    work *works = (work *)arg;
    long chunks;

    chunks = getChunks();

    while (1) {
        
        assert(sem_wait(&full) == 0);
        assert(sem_wait( &mutex) == 0);
        work *curW = &works[currWork];
        currWork = (currWork + 1) % chunks; 
        for (long i = 0; i < curW->size; i++){
            char currChar = curW->addr[i];
            printf("%c", currChar );

        }
        assert(sem_post( &mutex) == 0);
        assert(sem_post(&empty) == 0);
    }
}

void spawnWorkers(file *files, int argc){
    long np;
    pthread_t *threads;
    work *works;
    int fillWP;
    long pageSize;
    long chunks;


    chunks = getChunks();
    fillWP = 0;
    pageSize = getPageSize();
    np = sysconf(_SC_NPROCESSORS_ONLN);
    if ((threads = malloc(sizeof(pthread_t) * np)) == NULL){
        perror("Error: ");
    }
    if ((works = malloc(sizeof(work) * chunks)) == NULL){
        perror("Error: ");
    }

    Seminit(&mutex, 0, 1);
    Seminit(&empty, 0, 1);
    Seminit(&full, 0, 0);

    for (int i = 0; i < np; i++){
        pthread_create(&threads[i],NULL,worker,works);
    }


    //create jobs
    for (int i = 1; i < argc; i++ ){
        long long offset = 0;
        while (offset < files[i].size)
        {
            assert(sem_wait(&empty) == 0);
            assert(sem_wait( &mutex) == 0);
            
            works[fillWP].size = offset;
            if (offset + pageSize > files[i].size){
                works[fillWP].size = files[i].size - offset;
            }
            char *addr = mmap(NULL, (size_t)works[fillWP].size, PROT_READ, MAP_PRIVATE, 
                            files[i].fp, offset);

            if (addr == MAP_FAILED){
                handle_error("Err: mmap: ");
            }
            printf("here ne ok lop w");

            works[fillWP].addr = addr;
            offset += pageSize;
            fillWP = (fillWP + 1) % chunks;
            printf("here ne ok lop w");
            assert(sem_post(&mutex) == 0);
            assert(sem_post(&full) == 0);

        }
        close(files[i].fp);
    
    }

    assert(sem_wait(&empty) == 0);
    assert(sem_wait( &mutex) == 0);

    for (long i = 0; i < np; i++){
        pthread_cancel(threads[i]);
        pthread_join(threads[i], NULL);
    }
    



}