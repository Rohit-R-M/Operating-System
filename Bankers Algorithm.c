//Bankers Algorithm 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max_p 100
#define max_r 100

int need[max_p][max_r], allot[max_p][max_r], max[max_p][max_r], available[max_r];
bool isFinished[max_p];
int sequence[max_p];

// Calculate the need matrix
void calculateNeed(int n, int m) 
{
    int i, j;
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
	{
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

//display the need matrix
void displayNeed(int n, int m) 
{
    int i, j;
    printf("Need Matrix:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++)
	{
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

//read the allocation matrix
void readAllot(int n, int m) 
{
    int i, j;
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
	{
            scanf("%d", &allot[i][j]);
        }
    }
}

//read the maximum matrix
void readMax(int n, int m) 
{
    int i, j;
    printf("Enter the matrix for maximum demand of each process:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
	{
            scanf("%d", &max[i][j]);
        }
    }
}

//display the allocation matrix
void displayAllot(int n, int m) 
{
    int i, j;
    printf("Allocation Matrix:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
	{
            printf("%d ", allot[i][j]);
        }
        printf("\n");
    }
}

// display the maximum matrix
void displayMax(int n, int m) 
{
    int i, j;
    printf("Maximum Demand Matrix:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
	{
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }
}

//check if the system is in a safe state
void isSafe(int n, int m) 
{
    int i, j, work[max_r], count = 0;
    for (i = 0; i < m; i++) 
    {
        work[i] = available[i];
    }
    for (i = 0; i < n; i++) 
    {
        isFinished[i] = false;
    }
    while (count < n) 
    {
        bool canAllot = false;
        for (i = 0; i < n; i++) 
	{
            if (isFinished[i] == false) 
	    {
                for (j = 0; j < m; j++) 
		{
                    if (work[j] < need[i][j]) 
		    {
                        break;
                    }
                }
                if (j == m) 
		{
                    for (j = 0; j < m; j++) 
		    {
                        work[j] += allot[i][j];
                    }
                    sequence[count++] = i;
                    isFinished[i] = true;
                    canAllot = true;
                }
            }
        }
        if (canAllot == false) 
	{
            printf("System Is not safe\n");
            return;
        }
    }
    printf("System is in safe state\n");
    printf("Safe sequence: ");
    for (i = 0; i < n; i++) 
    {
        printf("P%d ", sequence[i]);
    }
    printf("\n");
}

int main() 
{
    int n, m, i, j;
    printf("Enter the number of processes and resources: ");
    scanf("%d%d", &n, &m);
    printf("Enter the available resources:\n");
    for (i = 0; i < m; i++) 
    {
        scanf("%d", &available[i]);
    }
    readAllot(n, m);
    readMax(n, m);
    calculateNeed(n, m);
    displayNeed(n, m);
    isSafe(n, m);
}

/*

Max Allocation
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Allocation
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Available Resources
3 3 2

output Need:
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1

Safe-Sequence
P1 -> P3 -> P4 -> P0 -> P2
*/ 
