#include<stdio.h>
#define max 30

typedef struct FCFS
{
	int pid, at, bt, tat, wt, ct, st;
} ps;

int main()
{
	ps p[max];
	int i, j, n, sum_tat = 0, sum_wt = 0;
	float awt, atat;
	
	printf("Enter the number of processors:\n");
	scanf("%d", &n);
	
	printf("Enter the Processor ID:\n");
	for (i = 0; i < n; i++)
		scanf("%d", &p[i].pid);
		
	printf("Enter the Arrival time:\n");
	for (i = 0; i < n; i++)
		scanf("%d", &p[i].at);
		
	printf("Enter the Burst time:\n");
	for (i = 0; i < n; i++)
		scanf("%d", &p[i].bt);
		
	// Sort processes by arrival time
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (p[j].at > p[j + 1].at)
			{
				// Swapping processor IDs
				int temp = p[j + 1].pid;
				p[j + 1].pid = p[j].pid;
				p[j].pid = temp;
				
				// Swapping arrival times
				temp = p[j + 1].at;
				p[j + 1].at = p[j].at;
				p[j].at = temp;
				
				// Swapping burst times
				temp = p[j + 1].bt;
				p[j + 1].bt = p[j].bt;
				p[j].bt = temp;
			}
		}
	}
	
	// Calculate start time & completion time
	p[0].st=p[0].at;
	p[0].ct = p[0].st + p[0].bt;
	for (i = 1; i < n; i++)
	{
		if(p[i].at>p[i-1].ct)
		p[i].st=p[i].at;
		else
		p[i].st=p[i-1].ct;
		
	p[i].ct=p[i].st+p[i].bt;
	}
	
	printf("Pid\tAT\tBT\tST\tCT\tTAT\tWT\n");
	for (i = 0; i < n; i++)
	{
		p[i].tat = p[i].ct - p[i].at; // Turnaround time
		p[i].wt = p[i].tat - p[i].bt; // Waiting time
		sum_tat += p[i].tat;
		sum_wt += p[i].wt;
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,p[i].st, p[i].ct, p[i].tat, p[i].wt);
	}
	
	awt = (float)sum_wt / n;
	atat = (float)sum_tat / n;
	
	printf("Average Waiting Time: %.2f\n", awt);
	printf("Average Turnaround Time: %.2f\n", atat);
	
	return 0;
}
