#include <iostream>

using namespace std;

void maxHeapify(int arr[], int i, int n)
{
    int leftIndex = 2 * i + 1;
    int rightIndex = leftIndex + 1;
    int largest = i;
    // n = heapSize
    if (leftIndex < n && arr[leftIndex] > arr[i])
        largest = leftIndex;
    if (rightIndex < n && arr[rightIndex] > arr[largest])
        largest = rightIndex;
    if (largest != i)
    {
        int t = arr[largest];
        arr[largest] = arr[i];
        arr[i] = t;
        maxHeapify(arr, largest, n);
    }
}

void buildMaxHeap(int arr[], int n)
{
    // n = heapsize
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, i, n);
}

void heapSortMaxHeap(int arr[], int n)
{
    int ncopy = n;
    buildMaxHeap(arr, n);
    for (int i = n - 1; i >= 1; i--)
    {
        int t = arr[i];
        arr[i] = arr[0];
        arr[0] = t;
        ncopy--;
        maxHeapify(arr, 0, ncopy);
    }
}

int main()
{
    int arr[] = {10, 15, 30, 20, 8, 25, 40};
    int n = 7;
    heapSortMaxHeap(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    return 0;
}