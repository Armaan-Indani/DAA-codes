#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int random_no(int a, int b)
{
    int x = b - a > 0 ? b - a : 1;
    return rand() % x + a;
}

int partition(int arr[], int low, int high)
{
    int piv_index = random_no(low, high + 1);
    int pivot = arr[piv_index];
    // pivot = arr[high];
    printf("low, high, pivot = (%d %d %d)\n", low, high, pivot);
    int i = (low - 1);

    for (int j = low; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            if (i == piv_index)
            {
                piv_index = j;
            }
            swap(&arr[i], &arr[j]);
        }
    }
    printf("Element %d at position: %d\n", arr[piv_index], i + 1);
    swap(&arr[i + 1], &arr[piv_index]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int arr[] = {28, 13, 42, 25, 11, 7, 19, 56, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    printf("Sorted Array\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}