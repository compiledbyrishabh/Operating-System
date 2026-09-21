#include <stdio.h>

// Structure for a process
typedef struct
{
    int id, arr, burst, comp, tat, wait, done;
} Process;

int main()
{
    int n, curr = 0, completed = 0;
    float tot_wait = 0, tot_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        p[i].done = 0;

        printf("\nEnter arrival time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].arr);

        printf("Enter burst time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].burst);
    }

    // SJF Logic
    while (completed < n)
    {
        int idx = -1, min_b = 999999;

        // Find arrived process with shortest burst time
        for (int i = 0; i < n; i++)
        {
            if (p[i].arr <= curr && !p[i].done && p[i].burst < min_b)
            {
                min_b = p[i].burst;
                idx = i;
            }
        }

        if (idx != -1)
        {
            curr += p[idx].burst; // Execute process
            p[idx].comp = curr;
            p[idx].tat = p[idx].comp - p[idx].arr;
            p[idx].wait = p[idx].tat - p[idx].burst;
            p[idx].done = 1;

            tot_tat += p[idx].tat;
            tot_wait += p[idx].wait;
            completed++;
        }
        else
        {
            curr++; // CPU is idle, jump time forward
        }
    }

    // Display Results with FCFS formatting
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    printf("--------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].id, p[i].arr, p[i].burst, p[i].comp, p[i].tat, p[i].wait);
    }

    printf("\nAverage Waiting Time: %.2f\n", tot_wait / n);
    printf("Average Turnaround Time: %.2f\n", tot_tat / n);

    return 0;
}