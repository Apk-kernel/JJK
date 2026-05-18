#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define last 199
#define start 0
#define head 67

void sstf(int tracks[], int n){
    int moves = 0, totaldist = 0, curdist = 0;

    printf("\nNo. of tracks: %d", last - start + 1);
    printf("\nR/W head is initially at: %d", head);

    printf("\nRequest queue: ");

    for(int i = 0; i < n; i++)
        printf("%d ", tracks[i]);

    int order[n];
    int visited[n];

    for(int i = 0; i < n; i++)
        visited[i] = 0;

    int from = head;

    printf("\n\n\tS.no.\tFrom\tTo\tDistance\n");

    for(int i = 0; i < n; i++){
        int closest = -1;
        int mindist = INT_MAX;

        for(int j = 0; j < n; j++){
            if(!visited[j]){
                if(abs(tracks[j] - from) < mindist){
                    mindist = abs(tracks[j] - from);
                    closest = j;
                }
            }
        }

        moves++;
        curdist = mindist;

        visited[closest] = 1;
        order[i] = tracks[closest];

        printf("\t%d.\t%d\t%d\t%d\n",
               moves, from, tracks[closest], curdist);

        totaldist += curdist;
        from = tracks[closest];
    }

    printf("\nOrder of execution: %d", head);

    for(int i = 0; i < n; i++)
        printf(" -> %d", order[i]);

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

    sstf(tracks, n);

    return 0;
}
