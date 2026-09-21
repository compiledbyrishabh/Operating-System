#include <stdio.h>

// Structure for a process
typedef struct
{
    int id, arr, burst, rem, comp, tat, wait, in_q;
} Process;

int main()
{
    int n, tq, curr = 0, completed = 0;
    float tot_wait = 0, tot_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        p[i].in_q = 0; // Tracks if process is in the queue

        printf("\nEnter arrival time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].arr);

        printf("Enter burst time for Process P%d: ", p[i].id);
        scanf("%d", &p[i].burst);

        p[i].rem = p[i].burst; // Remaining burst time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // Sort by arrival time initially
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arr > p[j + 1].arr)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // RR Logic using a simple array as a queue
    int q[1000], f = 0, r = 0;
    q[r++] = 0; // Push first process to queue
    p[0].in_q = 1;
    curr = p[0].arr;

    while (completed < n)
    {
        if (f == r)
        { // Queue is empty, CPU is idle
            curr++;
            for (int i = 0; i < n; i++)
            {
                if (p[i].arr <= curr && !p[i].in_q && p[i].rem > 0)
                {
                    q[r++] = i;
                    p[i].in_q = 1;
                }
            }
            continue;
        }

        int idx = q[f++]; // Pop process from queue
        int spent = (p[idx].rem > tq) ? tq : p[idx].rem;

        p[idx].rem -= spent;
        curr += spent;

        // Check for new arrivals while this process was executing
        for (int i = 0; i < n; i++)
        {
            if (p[i].arr <= curr && !p[i].in_q && p[i].rem > 0)
            {
                q[r++] = i;
                p[i].in_q = 1;
            }
        }

        // If current process isn't done, put it at the back of the queue
        if (p[idx].rem > 0)
        {
            q[r++] = idx;
        }
        else
        {
            // Process completed
            p[idx].comp = curr;
            p[idx].tat = p[idx].comp - p[idx].arr;
            p[idx].wait = p[idx].tat - p[idx].burst;
            tot_tat += p[idx].tat;
            tot_wait += p[idx].wait;
            completed++;
        }
    }

    // Sort by ID to display processes in P1, P2, P3... order again
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].id > p[j + 1].id)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Display Results with exact formatting
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