#include <stdio.h>

// Structure for a process
typedef struct
{
    int id;
    int arr;   // Arrival time
    int burst; // Burst time
    int comp;  // Completion time
    int tat;   // Turnaround time
    int wait;  // Waiting time
} Process;

// Calculate FCFS scheduling
void calc_fcfs(Process p[], int n)
{
    int curr_time = 0;

    for (int i = 0; i < n; ++i)
    {
        if (curr_time < p[i].arr)
        {
            curr_time = p[i].arr;
        }

        p[i].comp = curr_time + p[i].burst;
        p[i].tat = p[i].comp - p[i].arr;
        p[i].wait = p[i].tat - p[i].burst;

        curr_time = p[i].comp;
    }
}

// Display the results
void print_results(Process p[], int n)
{
    printf("\nID\tArrival\tBurst\tComp\tTAT\tWait\n");
    printf("---------------------------------------------\n");

    double total_wait = 0, total_tat = 0;

    for (int i = 0; i < n; ++i)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arr, p[i].burst, p[i].comp, p[i].tat, p[i].wait);

        total_wait += p[i].wait;
        total_tat += p[i].tat;
    }

    printf("\nAvg Wait Time: %.2f\n", total_wait / n);
    printf("Avg Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("\nEnter Arrival Time for P%d: ", p[i].id);
        scanf("%d", &p[i].arr);

        printf("Enter Burst Time for P%d: ", p[i].id);
        scanf("%d", &p[i].burst);
    }

    // Sort processes by arrival time
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

    calc_fcfs(p, n);
    print_results(p, n);

    return 0;
}