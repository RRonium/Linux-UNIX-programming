#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void fcfs(int req[], int n, int head) {
    int total = 0, i;
    printf("\nFCFS Seek Sequence: %d ", head);
    for(i = 0; i < n; i++) {
        total += abs(req[i] - head);
        head = req[i];
        printf("-> %d ", head);
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

    fcfs(req, n, head);

    return 0;
}