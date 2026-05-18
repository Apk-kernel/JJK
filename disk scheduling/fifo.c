#include <stdio.h>
#include <stdlib.h>

#define last 199
#define start 0
#define head 67

void fifo(int tracks[], int n){
    int moves = 0, totaldist = 0, curdist = 0;

    printf("\nNo. of tracks: %d", last - start + 1);
    printf("\nR/W head is initially at: %d", head);

    printf("\nRequest queue: ");

    for(int i = 0; i < n; i++)
        printf("%d ", tracks[i]);

    printf("\nStarting direction: ");

    if(tracks[0] > head)
        printf("Right");
    else
        printf("Left");

    printf("\n\n\tS.no.\tFrom\tTo\tDistance\n");

    int from = head;

    for(int i = 0; i < n; i++){
        moves++;

        curdist = abs(tracks[i] - from);

        printf("\t%d.\t%d\t%d\t%d\n",
               moves, from, tracks[i], curdist);

        from = tracks[i];
        totaldist += curdist;
    }

    printf("\nOrder of execution: %d", head);

    for(int i = 0; i < n; i++)
        printf(" -> %d", tracks[i]);

    printf("\nTotal track distance: %d", totaldist);

    printf("\nAverage seek length: %.2f\n",
           (float)totaldist / moves);
}

int main(){
    int n;

    printf("\nEnter number of track requests: ");
    scanf("%d", &n);

    int tracks[n];

    printf("\nEnter track indices:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &tracks[i]);

    fifo(tracks, n);

    return 0;
}
