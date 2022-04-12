/*
    problem link: https://www.codingninjas.com/codestudio/problems/longest-bitonic-sequence_1062688
 */

#include <bits/stdc++.h>
using namespace std;

/*
    1> Find LIS from both and back.
    2> LIS[i] = LIS_back[i] + LIS_front[i] - 1
    3> Find the maximum.
 */

int longestBitonicSequence(vector<int> &arr, int n)
{

    vector<int> frontLIS(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (arr[i] > arr[j])
                frontLIS[i] = max(frontLIS[i], 1 + frontLIS[j]);

    vector<int> backLIS(n, 1);
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j > i; j--)
            if (arr[i] > arr[j])
                backLIS[i] = max(backLIS[i], 1 + backLIS[j]);

    int longest = 1;

    for (int i = 0; i < n; i++)
        longest = max(longest, frontLIS[i] + backLIS[i] - 1);

    return longest;
}
