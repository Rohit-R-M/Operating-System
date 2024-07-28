#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>
#include<sys/types.h>
#include<fcntl.h>
#include<math.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
void sigfn1(int signo)
{
	printf("parent work is over,child-you can proceed\n");
}
void sigfn2(int signo)
{
	printf("child works is over,parent-you can proceed\n");
}
int main()
{
	signal(SIGUSR1,sigfn1);
	signal(SIGUSR2,sigfn2);
	int temp;
	key_t key=ftok("worstfit.c",165);
	int shmid=shmget(key,10*sizeof(int),IPC_CREAT|0666);
	if(shmid>0)
    {
		printf("it is okshm id=%d\n",shmid);	
	}
	int *ptr=(int*)(shmat(shmid,0,0));
	int pid=fork();
	if(pid==0)
	{
		printf("child:child is  going to wait for data\n");
		pause();
		printf("child:got signal from parent\n");
		for(int i=0; i<10;i++)
		    printf("child:%d\n",*(ptr+i));
		printf("child:i am going to stop\n");
		for(int i=0; i<10;i++)
		    for(int j=i+1; j<10;++j)
		        if(*(ptr+i)>*(ptr+j))
		        {
					temp=*(ptr+i);
					*(ptr+i)=*(ptr+j);
					*(ptr+j)=temp;
				}
	   printf("child:stored data\n");
	   for(int i=0;i<10;i++)
	       printf("child:%d\n",*(ptr+i));
	   printf("child:I am signalling parent\n");
	   kill(getppid(),SIGUSR2);
	   printf("child i am going to terminate\n");
	}
	else
	{
		printf("parent is waiting data\n");
		printf("parent:enter 10 data\n");
		for(int i=0; i<10;i++)
		   scanf("%d",ptr+i);
		printf("parent:data written in memory\n");
		for(int i=0;i<10;i++)
		  printf("parent:%d\n",*(ptr+i));
		printf("p:parent is going to signal child\n");
		kill(pid,SIGUSR1);
		printf("p:parent is going to WAIT FOR child\n");
		pause();
		printf("p:parent got signal\n");
		printf("p:sorted data\n");
		for(int i=0;i<10;i++)
		     printf("parent:%d\n",*(ptr+i));
		shmdt(ptr);
	}
}
