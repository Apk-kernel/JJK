#include <stdio.h>
#include <stdlib.h>

#define last 199
#define start 0
#define head 67

void sort(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void scan(int tracks[], int n){
    int moves = 0, totaldist = 0, curdist = 0;

    int lt[n], gt[n];
    int l = 0, g = 0;

    printf("\nNo. of tracks: %d", last - start + 1);
    printf("\nR/W head is initially at: %d", head);

    printf("\nRequest queue: ");

    for(int i = 0; i < n; i++){
        printf("%d ", tracks[i]);

        if(tracks[i] > head)
            gt[g++] = tracks[i];
        else
            lt[l++] = tracks[i];
    }

    printf("\nStarting direction: Right");

    sort(gt, g);
    sort(lt, l);

    int from = head;

    printf("\n\n\tS.no.\tFrom\tTo\tDistance\n");

    for(int i = 0; i < g; i++){
        moves++;

        curdist = abs(gt[i] - from);

        printf("\t%d.\t%d\t%d\t%d\n",
               moves, from, gt[i], curdist);

        from = gt[i];
        totaldist += curdist;
    }

    for(int i = l - 1; i >= 0; i--){
        moves++;

        curdist = abs(lt[i] - from);

        printf("\t%d.\t%d\t%d\t%d\n",
               moves, from, lt[i], curdist);

        from = lt[i];
        totaldist += curdist;
    }

    printf("\nOrder of execution: %d", head);

    for(int i = 0; i < g; i++)
        printf(" -> %d", gt[i]);

    for(int i = l - 1; i >= 0; i--)
        printf(" -> %d", lt[i]);

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

    scan(tracks, n);

    return 0;
}
