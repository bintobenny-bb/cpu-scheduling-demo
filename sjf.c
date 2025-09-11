#include <stdio.h>

typedef struct {
    int pid;       // Process ID
    int bt;        // Burst Time
    int at;        // Arrival Time
    int wt;        // Waiting Time
    int tat;       // Turnaround Time
    int ct;        // Completion Time
    int done;      // Flag to check if process is completed
} Process;

int main() {
    int n, completed = 0, t = 0, i, minIndex;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        minIndex = -1;
        int minBT = 1e9;

        // Find process with shortest burst time among arrived processes
        for (i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= t && p[i].bt < minBT) {
                minBT = p[i].bt;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            // No process has arrived yet
            t++;
        } else {
            // Execute selected process
            t += p[minIndex].bt;
            p[minIndex].ct = t;
            p[minIndex].tat = p[minIndex].ct - p[minIndex].at;
            p[minIndex].wt = p[minIndex].tat - p[minIndex].bt;

            p[minIndex].done = 1;
            completed++;

            printf("| P%d ", p[minIndex].pid);
        }
    }
    printf("|\n");

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
