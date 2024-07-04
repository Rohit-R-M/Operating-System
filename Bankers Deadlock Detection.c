//Bankers Algorithm 

#include <stdio.h>

int allocation[10][10], max[10][10], available[10], need[10][10];
int np, nr;

void read_matrix(int matrix[10][10])
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display_matrix(int matrix[10][10])
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        printf("P%d ", i);
        for (j = 0; j < nr; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void calculate_need()
{
    int i, j;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}



void bankers()
{
    int i, j, k = 0, flag = 0;
    int finish[10], safe[10];
    for (i = 0; i < np; i++)
        finish[i] = 0;

    for (i = 0; i < np; i++)
    {
    	flag=0;
        if (finish[i] == 0)
        {
            for (j = 0; j < nr; j++)
            {
                if (need[i][j] > available[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                finish[i] = 1;
                safe[k] = i;
                k++;

                for (j = 0; j < nr; j++)
                    available[j] += allocation[i][j];
                i = -1; 
            }
        }
    }

    flag = 0;
    for (i = 0; i < np; i++)
    {
        if (finish[i] == 0)
        {
            printf("The system is in deadlock state\n");
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\nThe system is in safe state\n");
        printf("Safe sequence is: ");
        for (i = 0; i < np; i++)
        {
            printf("P%d ", safe[i]);
        }
        printf("\n");
    }
}

int main()
{
	int j;
	printf("Enter the number of processor:\n");
	scanf("%d",&np);
	printf("Enter the number of resources:\n");
	scanf("%d",&nr);
	printf("Enter the Max allocation:\n");
	read_matrix(max);
	printf("Enter the Allocation:\n");
	read_matrix(allocation);
	printf("Enter the %d Available:\n",nr);
	for(j=0;j<nr;j++)
		scanf("%d",&available[j]);
	
	printf("\nNeed:\n");
	calculate_need();
	display_matrix(need);
	bankers();
	printf("\n\n");
	return 0;
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
