#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct SwapData {
    int *a;
    int *b;
};

void* swap_numbers(void* arg) {
    struct SwapData *data = (struct SwapData*)arg;
    int temp;

    temp = *(data->a);
    *(data->a) = *(data->b);
    *(data->b) = temp;

    return NULL;
}

int main() {
    pthread_t tid;
    int x, y;

    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);

    printf("Before Swap: x = %d, y = %d\n", x, y);

    struct SwapData data;
    data.a = &x;
    data.b = &y;

    pthread_create(&tid, NULL, swap_numbers, &data);
    pthread_join(tid, NULL);

    printf("After Swap: x = %d, y = %d\n", x, y);

    return 0;
}