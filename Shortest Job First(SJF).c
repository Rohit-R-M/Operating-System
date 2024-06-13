#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    int pid, at, bt, tat, wt, st, ct;
} process;

int main()
{
    process p[20], t;
    int n, i, j, c_time;
    float stat = 0, stwt = 0, atat = 0, awt = 0;

    printf("Enter the number of processes:\n");
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

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
            }
        }
    }

    c_time = p[0].at;

    for (i = 0; i < n; i++)
    {
        int min_bt = p[i].bt;
        int min_index = i;

        for (j = i; j < n; j++)
        {
            if (p[j].at <= c_time && p[j].bt < min_bt)
            {
                min_bt = p[j].bt;
                min_index = j;
            }
        }

        t = p[i];
        p[i] = p[min_index];
        p[min_index] = t;

        if (p[i].at >= c_time)
            p[i].st = p[i].at;
        else
            p[i].st = c_time;

        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        c_time = p[i].ct;

        stat += p[i].tat;
        stwt += p[i].wt;
    }

    atat = stat / n;
    awt = stwt / n;

    printf("Pid\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
   	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,p[i].st, p[i].ct, p[i].tat, p[i].wt);
   	return 0;
}

