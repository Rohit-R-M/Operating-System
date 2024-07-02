//Bankers Algorithm 
#include<stdio.h> 
int main() 
{  
    int n, m, i, j, k; 
    int alloc[20][20], max[20][20], avail[20]; 
    
    printf("Enter the size n and m:\n"); 
    scanf("%d%d", &n, &m); 
    
    printf("Enter the matrix of Maximum Allocation:\n"); 
    for (i = 0; i < n; i++) 
    { 
        for (j = 0; j < m; j++) 
        { 
            scanf("%d", &max[i][j]); 
        } 
    } 
    
    printf("Enter the matrix of Allocation:\n"); 
    for (i = 0; i < n; i++) 
    { 
        for (j = 0; j < m; j++) 
        { 
            scanf("%d", &alloc[i][j]); 
        } 
    } 
    
    printf("Enter the %d Available resources:\n",m); 
    for (i = 0; i < m; i++) 
    { 
        scanf("%d", &avail[i]); 
    } 
    
    int f[n], ans[n], ind = 0; 
    
    for (i = 0; i < n; i++) 
    { 
        ans[i] = 0; 
    } 
    
    for (k = 0; k < n; k++) 
    { 
        f[k] = 0; 
    } 
    
    int need[n][m]; 
    for (i = 0; i < n; i++) 
    { 
        for (j = 0; j < m; j++) 
        { 
            need[i][j] = max[i][j] - alloc[i][j]; 
        } 
    } 
    printf("Need matrix:\n");
   	for(i=0;i<n;i++)
   	{
    	for(j=0;j<m;j++)
   	    {
   			printf("%d ",need[i][j]);
 		}
		printf("\n");
	}
    int y = 0; 
    for (k = 0; k < 5; k++) 
    { 
        for (i = 0; i < n; i++) 
        { 
            if (f[i] == 0) 
            { 
                int flag = 0; 
                for (j = 0; j < m; j++) 
                { 
                    if (need[i][j] > avail[j]) 
                    { 
                        flag = 1; 
                        break; 
                    } 
                } 
                if (flag == 0) 
                { 
                    ans[ind++] = i; 
                    for (y = 0; y < m; y++) 
                    { 
                        avail[y] += alloc[i][j]; 
                    } 
                    f[i] = 1; 
                } 
            } 
        } 
    } 
    printf("Following is the safe sequence:\n"); 
    for (i = 0; i < n - 1; i++) 
    { 
        printf("P%d -> ", ans[i]); 
    } 
    printf("P%d\n", ans[n - 1]); 
    
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
