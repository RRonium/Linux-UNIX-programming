#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct ArrayData 
{
    int *arr;
    int size;
};
void* sort_array(void* arg) 
{
    struct ArrayData *data = (struct ArrayData*)arg;
    int n = data->size;
    int *a = data->arr;
    int temp;

    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (a[j] > a[j+1]) 
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    return NULL;
}
int main() 
{
    pthread_t tid;
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    struct ArrayData data;
    data.arr = arr;
    data.size = n;

    pthread_create(&tid, NULL, sort_array, &data);
    pthread_join(tid, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}