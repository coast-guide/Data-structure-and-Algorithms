/*
problem link: https://www.codingninjas.com/codestudio/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494
*/
#include <bits/stdc++.h>
using namespace std;

void printV(vector<vector<int>> &vec)
{

    for (auto &v : vec)
    {
        for (int ele : v)
            cout << ele << "  ";

        cout << "\n";
    }
}

int subsetSum(int ind, int target, vector<int> &arr, vector<vector<int>> &dp)
{

    if (dp[ind][target] != -1)
        return dp[ind][target];

    if (ind == arr.size() - 1)
        return dp[ind][target] = (arr[ind] == target);

    if (arr[ind] == target)
        return dp[ind][target] = true;

    return dp[ind][target] = (target >= arr[ind] ? subsetSum(ind + 1, target - arr[ind], arr, dp) : false) || subsetSum(ind + 1, target, arr, dp);
}

void memoize(vector<int> &arr, int n, vector<vector<int>> &dp, int sum)
{

    for (int target = 0; target <= sum; target++)
        dp[n - 1][target] = (arr[n - 1] == target);

    for (int ind = n - 2; ind >= 0; ind--)
    {
        for (int target = 0; target <= sum; target++)
        {
            if (arr[ind] == target)
                dp[ind][target] = true;
            else
                dp[ind][target] = (target >= arr[ind] ? dp[ind + 1][target - arr[ind]] : false) || dp[ind + 1][target];
        }
    }
}

int minSubsetSumDifference(vector<int> &arr, int n)
{
    int sum = 0;
    for (int ele : arr)
        sum += ele;

    vector<vector<int>> dp(n, vector<int>(sum + 1));
    // subsetSum(0, sum, arr, dp);
    memoize(arr, n, dp, sum);

    // printV(dp);

    int minDiff = INT_MAX;
    for (int s1 = 0; s1 <= sum; s1++)
        if (dp[0][s1] == true)
        {
            minDiff = min(minDiff, abs(2 * s1 - sum));
        }

    return minDiff;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        cout << minSubsetSumDifference(arr, n) << endl;
    }
    return 0;
}
