#include <iostream>

using namespace std;

int partition(int arr[], int low, int high)
{
    // last element as pivot
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            // swap
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    // place pivot at correct position (swap)
    arr[high] = arr[i + 1];
    arr[i + 1] = pivot;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int i = partition(arr, low, high);
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}

int main()
{
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int n = 7;
    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}
