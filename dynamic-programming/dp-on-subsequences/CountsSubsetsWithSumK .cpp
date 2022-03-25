/*
    problem link: https://www.codingninjas.com/codestudio/problems/number-of-subsets_3952532

    Handle case : {0,0,1}
    ans = 4

int cntWays(int ind, int target, vector<int> &num, vector<vector<int>> &dp)
{
    if (ind == num.size() - 1) {
        if(num[ind] == 0 && target == 0)
            return 2;
        if(target == 0 || target == num[0])
            return 1;

        return 0;
    }


    if (dp[ind][target] != -1)
        return dp[ind][target];



    return dp[ind][target] = cntWays(ind + 1, target, num, dp) + (target >= num[ind] ? cntWays(ind + 1, target - num[ind], num, dp) : 0);
}

 */
#include <bits/stdc++.h>
using namespace std;

int cntWays(int ind, int target, vector<int> &num, vector<vector<int>> &dp)
{

    if (dp[ind][target] != -1)
        return dp[ind][target];

    if (target == 0)
        return dp[ind][target] = 1;

    if (ind == num.size() - 1)
        return dp[ind][target] = num[ind] == target;

    return dp[ind][target] = cntWays(ind + 1, target, num, dp) + (target >= num[ind] ? cntWays(ind + 1, target - num[ind], num, dp) : 0);
}

int memoize(vector<int> &num, int target)
{
    vector<vector<int>> dp(num.size(), vector<int>(target + 1, -1));

    return cntWays(0, target, num, dp);
}

int tabulation(vector<int> &num, int targetSum)
{
    vector<vector<int>> dp(num.size(), vector<int>(targetSum + 1));

    for (int ind = num.size() - 1; ind >= 0; ind--)
    {
        for (int target = 0; target <= targetSum; target++)
        {

            if (target == 0)
                dp[ind][target] = 1;
            else if (ind == num.size() - 1)
                dp[ind][target] = num[ind] == target;
            else
                dp[ind][target] = dp[ind + 1][target] + (target >= num[ind] ? dp[ind + 1][target - num[ind]] : 0);
        }
    }
    return dp[0][targetSum];
}

int spaceOptimized(vector<int> &num, int targetSum)
{
    vector<int> prev(targetSum + 1);

    for (int ind = num.size() - 1; ind >= 0; ind--)
    {
        vector<int> curr(targetSum + 1);
        for (int target = 0; target <= targetSum; target++)
        {

            if (target == 0)
                curr[target] = 1;
            else if (ind == num.size() - 1)
                curr[target] = num[ind] == target;
            else
                curr[target] = prev[target] + (target >= num[ind] ? prev[target - num[ind]] : 0);
        }
        prev = curr;
    }
    return prev[targetSum];
}

int findWays(vector<int> &num, int tar)
{

    // return memoize(num, tar);
    // return tabulation(num, tar);
    return spaceOptimized(num, tar);
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, tar;
        cin >> n >> tar;

        vector<int> num(n);
        for (int i = 0; i < n; i++)
            cin >> num[i];

        cout << findWays(num, tar) << endl;
    }

    return 0;
}