/*
problem link: https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954?leftPanelTab=0
*/
#include <bits/stdc++.h>
using namespace std;

bool findSubset(int i, int sum, vector<int> &arr)
{

    if (i == arr.size() - 1)
        return sum == arr[i];

    if (sum == arr[i])
        return true;

    return findSubset(i + 1, sum, arr) || (sum >= arr[i] ? findSubset(i + 1, sum - arr[i], arr) : false);
}

bool tabulation(int n, int k, vector<int> &arr)
{
    vector<vector<int>> dp(n, vector<int>(k + 1));

    for (int sum = 0; sum <= k; sum++)
        if (sum == arr[n - 1])
            dp[n - 1][sum] = true;

    for (int i = n - 2; i >= 0; i--)
    {
        for (int sum = 0; sum <= k; sum++)
        {
            if (sum == arr[i])
                dp[i][sum] = true;
            else
                dp[i][sum] = dp[i + 1][sum] || (sum >= arr[i] ? dp[i + 1][sum - arr[i]] : false);
        }
    }
    return dp[0][k];
}

bool spaceOptimized(int n, int k, vector<int> &arr)
{

    vector<int> prev(k + 1);

    for (int sum = 0; sum <= k; sum++)
        if (sum == arr[n - 1])
            prev[sum] = true;

    for (int i = n - 2; i >= 0; i--)
    {
        vector<int> curr(k + 1);
        for (int sum = 0; sum <= k; sum++)
        {
            if (sum == arr[i])
                curr[sum] = true;
            else
                curr[sum] = prev[sum] || (sum >= arr[i] ? prev[sum - arr[i]] : false);
        }
        prev = curr;
    }
    return prev[k];
}

bool subsetSumToK(int n, int k, vector<int> &arr)
{

    return spaceOptimized(n, k, arr);
}