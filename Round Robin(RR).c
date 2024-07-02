#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

struct P
{
	int AT,BT,ST[20],WT,FT,TAT,pos;
};

int quant;

int main()
{
    int n, i, j;
    printf("Enter the no. of processes: ");
    scanf("%d",&n);
    struct P p[n];

    printf("Enter the quantum: ");
    scanf("%d",&quant);

    printf("Enter the process numbers: \n");
    for(i=0;i<n;i++) 
		scanf("%d",&(p[i].pos));

    printf("Enter the Arrival time of processes: \n");
    for(i=0;i<n;i++) 
		scanf("%d",&(p[i].AT));

    printf("Enter the Burst time of processes: \n");
    for(i=0;i<n;i++) 
		scanf("%d",&(p[i].BT));

    int c=n, s[n][20];
    float time=0, mini=INT_MAX, b[n], a[n];
    int index=-1;
    for(i=0;i<n;i++)
	{
        b[i]=p[i].BT; 
		a[i]=p[i].AT;
        for(j=0;j<20;j++) 
			s[i][j]=-1;
    }

    int tot_wt=0, tot_tat=0;
    bool flag=false;

    while(c!=0)
	{
        mini=INT_MAX; flag=false;
        for(i=0;i<n;i++)
		{
            float p=time+0.1;
            if(a[i]<=p && mini>a[i] && b[i]>0)
			{
                index=i; 
				mini=a[i];
				flag=true;
            }
        }
        if(!flag)
		{ 
			time++;
			continue; 
		}
        j=0;
        while(s[index][j]!=-1) 
			j++;
        if(s[index][j]==-1)
		{ 
			s[index][j]=time; 
			p[index].ST[j]=time; 
		}
        if(b[index]<=quant)
		{ 
			time+=b[index]; 
			b[index]=0;
		}
        else
		{
			time+=quant; 
			b[index]-=quant; 
		}
        if(b[index]>0)
			a[index]=time+0.1;
        if(b[index]==0)
		{
            c--; 
			p[index].FT=time;
            p[index].WT=p[index].FT-p[index].AT-p[index].BT;
            tot_wt+=p[index].WT;
            p[index].TAT=p[index].BT+p[index].WT;
            tot_tat+=p[index].TAT;
        }
    }

    printf("P_id\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
	{
        printf("%d\t%d\t%d\t", p[i].pos, p[i].AT, p[i].BT);
        printf("%d\t%d\t%d\n", p[i].FT, p[i].TAT, p[i].WT);
    }

    double avg_wt=tot_wt/(float)n, avg_tat=tot_tat/(float)n;
    printf("The average TurnAround time is: %lf\n", avg_tat);
    printf("The average wait time is: %lf\n", avg_wt);
    return 0;
}
