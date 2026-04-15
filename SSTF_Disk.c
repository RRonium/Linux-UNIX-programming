#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sstf(int req[], int n, int head) {
    int total = 0, completed[MAX] = {0};
    int i, count = 0;
    printf("\nSSTF Seek Sequence: %d ", head);
    while(count < n) {
        int min = 9999, index = -1;
        for(i = 0; i < n; i++) {
            if(!completed[i]) {
                int dist = abs(req[i] - head);
                if(dist < min) {
                    min = dist;
                    index = i;
                }
            }
        }
        total += abs(req[index] - head);
        head = req[index];
        completed[index] = 1;
        printf("-> %d ", head);
        count++;
    }
    printf("\nTotal Head Movement = %d\n", total);
}

int main() {
    int req[MAX], n, head, i;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    sstf(req, n, head);

    return 0;
}