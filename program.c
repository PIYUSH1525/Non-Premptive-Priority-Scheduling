#include <stdio.h>
#include <string.h>
#include<ctype.h>
struct process
{
    int process_id,arrival_time,burst_time, priority,waiting_time,turn_around_time, completion_time,response_time;
};
int main()
{
 
 int n, i, j;
    float Tot_WT = 0, Tot_turnaround_time = 0, Tot_CT;
     while(1)
    {
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        if(n==0)
        {
            printf("Wrong Input!!!\tPleaase Input Number greater than 0\n");
            continue;
        }
        else if(n>5)
        {
            printf("Limit Crossed!!! Exiting The Program\n");
            return 0;
        }
        else
        {
            break;
        }
    }
    struct process p[n];
    for (i = 0; i < n; i++)
    {
        printf("Enter priority for process %d:--> ", i + 1);
        scanf("%d", &p[i].priority);
        printf("Enter arrival time for process %d:--> ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time for process %d:--> ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].process_id = i + 1;
        p[i].waiting_time = 0;
        p[i].turn_around_time = 0;
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].arrival_time > p[j].arrival_time)
            {
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int current_time = 0,completed = 0, prev = 0,is_over[50];
    memset(is_over,0,sizeof(is_over));
    while(completed !=n)
    {
        int randtemp = -1;
        int idi=-1;
        for(i=0;i<n;i++)
        {

            if(p[i].arrival_time <= current_time && is_over[i]==0)
            {
                if(p[i].priority>randtemp)
                {
                    randtemp = p[i].priority;
                    idi=i;
                }
                if (p[i].priority == randtemp)
                {
                    if(p[i].arrival_time < p[idi].arrival_time)
                    {
                        randtemp = p[i].priority;
                        idi=i;
                    }
                }
            }
        }
        if (idi!=-1)

        {       p[idi].response_time = current_time;
                p[idi].completion_time = p[idi].response_time + p[idi].burst_time;
                p[idi].turn_around_time = p[idi].completion_time - p[idi].arrival_time;
                p[idi].waiting_time = p[idi].turn_around_time - p[idi].burst_time;
                current_time = p[idi].completion_time;
                Tot_CT += p[idi].completion_time;
                Tot_turnaround_time += p[idi].turn_around_time;
                Tot_WT += p[idi].waiting_time;
                is_over[idi]=1;
                completed++;
        }
        else
        {
            completed++;
        }
    }
    printf("\nProcess ID\tPriority\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].process_id, p[i].priority, p[i].arrival_time, p[i].burst_time,
        p[i].completion_time, p[i].waiting_time, p[i].turn_around_time);
    }

    printf("Average waiting time is:----> %f\n", (Tot_WT / n));
    printf("Average turnaround time is:----> %f\n", (Tot_turnaround_time / n));
    printf("Average Completion time is:----> %f\n", (Tot_CT / n));

    return 0;}