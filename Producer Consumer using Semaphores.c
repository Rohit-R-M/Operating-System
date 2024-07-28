#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define BUFFER_SIZE 5

typedef struct {
    sem_t empty;
    sem_t full;
    sem_t mutex;
    int buffer[BUFFER_SIZE];
    int in, out;
} psshm;

int main() 
{
    int shmid, pid;
    psshm *ptr;
    shmid = shmget(IPC_PRIVATE, sizeof(psshm), IPC_CREAT | 0666);

    ptr = (psshm*) shmat(shmid, 0, 0);
  
    sem_init(&ptr->empty, 1, BUFFER_SIZE);
    sem_init(&ptr->full, 1, 0);
    sem_init(&ptr->mutex, 1, 1);
    
    ptr->in = 0;
    ptr->out = 0;
    pid = fork();

    if (pid > 0) 
    {
        while (1) 
        {
            int item = rand() % 20;

            sem_wait(&ptr->empty);  
            sem_wait(&ptr->mutex);  
            ptr->buffer[ptr->in] = item;
            printf("Produced: %d\n", item);
            ptr->in = (ptr->in + 1) % BUFFER_SIZE;
            sem_post(&ptr->mutex);  
            sem_post(&ptr->full);   

            sleep(rand()%3);
        }
    } 
    else if (pid == 0) 
    {
        
        while (1) 
        {
            sem_wait(&ptr->full);  
            sem_wait(&ptr->mutex);  
            int item = ptr->buffer[ptr->out];
            printf("Consumed: %d\n", item);
            ptr->out = (ptr->out + 1) % BUFFER_SIZE;
            sem_post(&ptr->mutex); 
            sem_post(&ptr->empty); 
            
            sleep(rand()%3);
        }
    } 
    return 0;
}
