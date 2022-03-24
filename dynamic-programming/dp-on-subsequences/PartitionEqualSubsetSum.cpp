/*
problem link: https://www.codingninjas.com/codestudio/problems/partition-equal-subset-sum_892980
*/
#include <bits/stdc++.h>
using namespace std;

bool memoize(int ind, int target, vector<int> &arr, vector<vector<int>> &dp)
{

    if (dp[ind][target] != -1)
        return dp[ind][target];
    if (ind == arr.size() - 1)
        return dp[ind][target] = (arr[ind] == target);

    if (arr[ind] == target)
        return dp[ind][target] = true;

    return dp[ind][target] = memoize(ind + 1, target, arr, dp) || (target >= arr[ind] ? memoize(ind + 1, target - arr[ind], arr, dp) : false);
}

bool tabulation(vector<int> &arr, int n, int targetSum)
{
    vector<vector<int>> dp(n, vector<int>(targetSum + 1));

    for (int target = 0; target <= targetSum; target++)
        dp[n - 1][target] = (arr[n - 1] == target);

    for (int i = n - 2; i >= 0; i--)
    {
        for (int target = 0; target <= targetSum; target++)
        {
            if (arr[i] == target)
                dp[i][target] = true;
            else
                dp[i][target] = dp[i + 1][target] || (target >= arr[i] ? dp[i + 1][target - arr[i]] : false);
        }
    }
    return dp[0][targetSum];
}

bool spaceOptimized(vector<int> &arr, int n, int targetSum)
{
    vector<int> prev(targetSum + 1);

    for (int target = 0; target <= targetSum; target++)
        prev[target] = (arr[n - 1] == target);

    for (int i = n - 2; i >= 0; i--)
    {
        vector<int> curr(targetSum + 1);
        for (int target = 0; target <= targetSum; target++)
        {
            if (arr[i] == target)
                curr[target] = true;
            else
                curr[target] = prev[target] || (target >= arr[i] ? prev[target - arr[i]] : false);
        }
        prev = curr;
    }
    return prev[targetSum];
}

bool canPartition(vector<int> &arr, int n)
{

    int sum = 0;
    for (int ele : arr)
        sum += ele;
    if (sum % 2)
        return false;

    return spaceOptimized(arr, n, sum / 2);
    //     vector<vector<int>> dp(n,vector<int>(sum/2+1, -1));
    //     return memoize(0,sum/2,arr, dp);
}
