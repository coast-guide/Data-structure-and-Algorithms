// https://practice.geeksforgeeks.org/problems/grouping-of-numbers0015/1
#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int get_maximum_group_size(int numbers[], int numbers_size, int k)
    {

        vector<int> remainder_frequency(k);

        for (int i = 0; i < numbers_size; ++i)
        {

            int remainder = numbers[i] % k;

            ++remainder_frequency[remainder];
        }

        int i = 1, j = k - 1, maximum_group_size = 0;

        while (i < j)
        {

            maximum_group_size += max(remainder_frequency[i], remainder_frequency[j]);

            ++i;
            --j;
        }

        if (i == j && remainder_frequency[j] > 0)
            ++maximum_group_size;

        if (remainder_frequency[0] > 0)
            ++maximum_group_size;

        return maximum_group_size;
    }

public:
    int maxGroupSize(int arr[], int N, int k)
    {

        return get_maximum_group_size(arr, N, k);
    }
};
