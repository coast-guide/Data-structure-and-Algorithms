// Randomized quicksort

#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

/* Function to print an array */
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    printf("\n");
}

// } Driver Code Ends
class Solution
{
public:
    // Function to sort an array using quick sort algorithm.
    void quickSort(int arr[], int low, int high)
    {
        if (low >= high)
            return;

        int pivot_index = partition_r(arr, low, high);
        quickSort(arr, low, pivot_index - 1);
        quickSort(arr, pivot_index + 1, high);
    }

    int partition_r(int arr[], int low, int high)
    {

        srand(time(nullptr));
        int random_index = low + rand() % (high - low);
        swap(arr[random_index], arr[high]);

        return partition(arr, low, high);
    }

public:
    int partition(int arr[], int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; ++j)
        {

            if (arr[j] < pivot)
            {
                ++i;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        return i + 1;
    }
};

// { Driver Code Starts.
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;

        int arr[n];
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        Solution ob;
        ob.quickSort(arr, 0, n - 1);
        printArray(arr, n);
    }
    return 0;
} // } Driver Code Ends
