#include <stdio.h>
#include <stdlib.h>

#define R 3

struct process{
    int alloc[R];
    int max[R];
    int need[R];
    int finished;
};

int n;
int total[R], taken[R];
int work[R], available[R];

void bankers(){
    int deadlock = 0;

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    struct process *p = (struct process*)malloc(n * sizeof(struct process));

    printf("\nEnter details for each process:\n");

    for(int i = 0; i < n; i++){
        printf("\n===== Process %d =====\n", i + 1);

        for(int j = 0; j < R; j++){
            char type = 'A' + j;

            printf("Resources Allocated [%c]: ", type);
            scanf("%d", &p[i].alloc[j]);

            if(taken[j] + p[i].alloc[j] > total[j]){
                printf("\nERROR: Instances allocated of type %c exceed the total number of instances.\n", type);
                free(p);
                return;
            }
        }

        for(int j = 0; j < R; j++)
            taken[j] += p[i].alloc[j];

        for(int j = 0; j < R; j++){
            char type = 'A' + j;

            printf("Max Requirement [%c]: ", type);
            scanf("%d", &p[i].max[j]);

            if(p[i].alloc[j] > p[i].max[j]){
                printf("\nERROR: Instances allocated of type %c exceed the max requirement.\n", type);
                free(p);
                return;
            }
        }

        for(int j = 0; j < R; j++)
            p[i].need[j] = p[i].max[j] - p[i].alloc[j];

        p[i].finished = 0;
    }

    for(int i = 0; i < R; i++){
        available[i] = total[i] - taken[i];
        work[i] = available[i];
    }

    printf("\nProcess\t\tAllocated\t\tMax\t\t\tNeed\t\tFinish\n");
    printf("\t\tA\tB\tC\tA\tB\tC\tA\tB\tC\n");

    for(int i = 0; i < n; i++){
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i,
               p[i].alloc[0], p[i].alloc[1], p[i].alloc[2],
               p[i].max[0], p[i].max[1], p[i].max[2],
               p[i].need[0], p[i].need[1], p[i].need[2],
               p[i].finished);
    }

    printf("\nAvailable : %d %d %d\n",
           available[0], available[1], available[2]);

    int c = 0;
    int *order = (int*)malloc(n * sizeof(int));

    while(c != n){
        int prev = c;

        for(int i = 0; i < n; i++){
            int ok = 1;

            for(int j = 0; j < R; j++){
                if(p[i].need[j] > work[j]){
                    ok = 0;
                    break;
                }
            }

            if(p[i].finished)
                ok = 0;

            if(ok){
                p[i].finished = 1;

                printf("\nExecuting P%d:\n", i + 1);

                order[c] = i;
                c++;

                for(int j = 0; j < R; j++){
                    work[j] += p[i].alloc[j];
                    p[i].alloc[j] = 0;
                }

                printf("\nWork : %d %d %d\n",
                       work[0], work[1], work[2]);

                printf("\nProcess\t\tAllocated\t\tMax\t\t\tNeed\t\tFinish\n");
                printf("\t\tA\tB\tC\tA\tB\tC\tA\tB\tC\n");

                for(int k = 0; k < n; k++){
                    printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                           k,
                           p[k].alloc[0], p[k].alloc[1], p[k].alloc[2],
                           p[k].max[0], p[k].max[1], p[k].max[2],
                           p[k].need[0], p[k].need[1], p[k].need[2],
                           p[k].finished);
                }

                printf("\n============================================================================================================\n\n");
            }
        }

        if(prev == c){
            deadlock = 1;
            printf("\nSYSTEM IS IN DEADLOCK STATE. TERMINATING THE PROGRAM\n");
            break;
        }
    }

    printf("\n");

    if(deadlock == 0){
        printf("Safe order for execution: ");

        for(int i = 0; i < n; i++)
            printf("P%d\t", order[i]);
    }

    free(order);
    free(p);
}

int main(){
    printf("\nEnter total instance of each resource in system:\n");

    for(int i = 0; i < R; i++){
        char type = 'A' + i;

        printf("%c: ", type);
        scanf("%d", &total[i]);

        taken[i] = 0;
    }

    bankers();

    return 0;
}
