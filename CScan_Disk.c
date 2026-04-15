void cscan(int req[], int n, int head, int disk_size) 
{
    int total = 0, i, j;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for(i = 0; i < n; i++) 
    {
        if(req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    for(i = 0; i < r - 1; i++) 
    {
        for(j = 0; j < r - i - 1; j++) 
        {
            if(right[j] > right[j + 1]) 
            {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    for(i = 0; i < l - 1; i++) 
    {
        for(j = 0; j < l - i - 1; j++) 
        {
            if(left[j] > left[j + 1]) 
            {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }

    printf("\nC-SCAN Seek Sequence: %d ", head);

    for(i = 0; i < r; i++) 
    {
        total += abs(right[i] - head);
        head = right[i];
        printf("-> %d ", head);
    }

    total += abs((disk_size - 1) - head);
    head = disk_size - 1;
    printf("-> %d ", head);

    total += abs(head - 0);
    head = 0;
    printf("-> %d ", head);

    for(i = 0; i < l; i++) 
    {
        total += abs(left[i] - head);
        head = left[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}