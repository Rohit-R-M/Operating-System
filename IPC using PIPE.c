#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int fd[2],i,j,n;
	pid_t pid;

	if(pipe(fd)==-1)
	{
		perror("pipe error");
		return 0;
	}

	pid=fork();

	if(pid<0)
	{
		printf("Child creation failed");
		return 0;
	}

	else if(pid>0)
	{
		close(fd[0]);

		printf("P: Enter the total numbers:\n");
		scanf("%d",&n);

		int numbers[n];

		printf("P: Enter the numbers:\n");
		for(i=0;i<n;i++)
		{
			scanf("%d",&numbers[i]);
		}
		
		write(fd[1],&n,sizeof(int));
		write(fd[1],numbers,n*sizeof(int));
		close(fd[1]);
		
		//wait(NULL);
	}

	else if(pid==0)
	{
		close(fd[1]);

		read(fd[0],&n,sizeof(int));

		int r_numbers[n];

		read(fd[0],r_numbers,n*sizeof(int));
		close(fd[0]);

		printf("c: Numbers Read from the pipe:\n");
		for(i=0;i<n;i++)
		{
			printf("%d\t",r_numbers[i]);
		}

		for(i=0;i<n-1;i++)
		{
			for(j=0;j<n-i-1;j++)
			{
				if(r_numbers[j]>r_numbers[j+1])
				{
					int temp=r_numbers[j];
					r_numbers[j]=r_numbers[j+1];
					r_numbers[j+1]=temp;
				}
			}
		}

		printf("\nC: Sorted numbers are:\n");
		for(i=0;i<n;i++)
			printf("%d\t",r_numbers[i]);

		exit(EXIT_FAILURE);
	}
	return 0;
}
