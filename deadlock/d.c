#include <stdio.h>
#include <stdlib.h>

#define R 3

struct process{
    int alloc[R];
    int req[R];
    int finished;
};

int n;
int total[R], taken[R], available[R], work[R];

void dd(){
    int deadlock = 0;

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    struct process *p = (struct process*)malloc(n * sizeof(struct process));

    printf("\nEnter details for each process:\n");

    for(int i = 0; i < n; i++){
        printf("\n========== PROCESS %d ==========\n", i + 1);

        for(int j = 0; j < R; j++){
            char type = 'A' + j;

            printf("Resources allocated [%c]: ", type);
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

            printf("Resources requested [%c]: ", type);
            scanf("%d", &p[i].req[j]);

            if(p[i].req[j] > total[j]){
                printf("\nERROR: Instances requested of type %c exceed the total number of instances.\n", type);
                free(p);
                return;
            }
        }

        p[i].finished = 0;
    }

    for(int j = 0; j < R; j++){
        available[j] = total[j] - taken[j];
        work[j] = available[j];
    }

    printf("\nProcess\t\tAllocated\t\tRequested\t\tFinish\n");
    printf("\t\tA\tB\tC\tA\tB\tC\n");

    for(int i = 0; i < n; i++){
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i,
               p[i].alloc[0], p[i].alloc[1], p[i].alloc[2],
               p[i].req[0], p[i].req[1], p[i].req[2],
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
                if(p[i].req[j] > work[j])
                    ok = 0;
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

                printf("\nProcess\t\tAllocated\t\tRequested\t\tFinish\n");
                printf("\t\tA\tB\tC\tA\tB\tC\n");

                for(int k = 0; k < n; k++){
                    printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                           k,
                           p[k].alloc[0], p[k].alloc[1], p[k].alloc[2],
                           p[k].req[0], p[k].req[1], p[k].req[2],
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
        printf("Order in which processes were executed without deadlock: ");

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

    dd();

    return 0;
}
