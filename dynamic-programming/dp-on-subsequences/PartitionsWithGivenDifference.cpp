/*
problem link : https://www.codingninjas.com/codestudio/problems/partitions-with-given-difference_3751628
 */
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int targetSum(int ind, int target, vector<int> &arr, vector<vector<int>> &dp)
{

    if (ind == arr.size() - 1)
    {
        if (arr[ind] == 0 && target == 0)
            return 2;
        if (target == 0 || arr[ind] == target)
            return 1;
        return 0;
    }

    if (dp[ind][target] != -1)
        return dp[ind][target];

    return dp[ind][target] = (targetSum(ind + 1, target, arr, dp) + ((target >= arr[ind]) ? targetSum(ind + 1, target - arr[ind], arr, dp) : 0)) % mod;
}

int countPartitions(int n, int d, vector<int> &arr)
{

    int s = 0;
    for (int ele : arr)
        s += ele;
    // s1 - s2 = d => s - 2s2 = d => s2 = (s-d)/2
    if (s - d < 0 || (s - d) % 2 == 1)
        return 0;
    int target = (s - d) / 2;

    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    return targetSum(0, target, arr, dp);
}
