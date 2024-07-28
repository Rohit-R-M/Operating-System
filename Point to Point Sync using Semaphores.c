#include<stdio.h>
#include<semaphore.h>
#include<sys/types.h>
#include<fcntl.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>
#include<sys/shm.h>
#include<stdlib.h>
#define KEY 1011

int main()
{
	sem_t* mutex;
	key_t key=KEY;
	int shmid,pid;
	shmid=shmget(key,sizeof(sem_t),IPC_CREAT|0666);
	mutex=(sem_t*)shmat(shmid,NULL,0);
	sem_init(mutex,1,0);
	pid=fork();
	if(pid>0)
	{
		sleep(5);
		printf("P:Hi!!!\n");
		sem_post(mutex);
		printf("P: I am going to terminate\n");
		exit(1);
	}
	else if(pid==0)
	{
		printf("C: I am going to wait\n");
		sem_wait(mutex);
		printf("C: Good Morning\n");
		printf("C: i am going to terminate\n");
		exit(1);
	}
}
