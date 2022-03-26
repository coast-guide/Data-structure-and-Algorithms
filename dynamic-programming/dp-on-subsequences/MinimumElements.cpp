#include <bits/stdc++.h>
using namespace std;
int memoize(int ind, int sum, vector<int> &num, vector<vector<int>> &dp)
{
    if (dp[ind][sum] != -1)
        return dp[ind][sum];

    if (ind == num.size() - 1)
    {
        if (sum % num[ind] == 0)
            return dp[ind][sum] = sum / num[ind];
        return dp[ind][sum] = INT_MAX;
    }

    int notTake = memoize(ind + 1, sum, num, dp);
    int take = (sum >= num[ind]) ? memoize(ind, sum - num[ind], num, dp) : INT_MAX;
    take = (take == INT_MAX) ? take : 1 + take;
    return dp[ind][sum] = min(take, notTake);
}

int tabulation(int ind, int target, vector<int> &num)
{

    vector<vector<int>> dp(num.size(), vector<int>(target + 1));
    for (int sum = 0; sum <= target; sum++)
    {
        if (sum % num[num.size() - 1] == 0)
            dp[num.size() - 1][sum] = sum / num[num.size() - 1];
        else
            dp[num.size() - 1][sum] = INT_MAX;
    }

    for (int ind = num.size() - 2; ind >= 0; ind--)
    {
        for (int sum = 0; sum <= target; sum++)
        {

            int notTake = dp[ind + 1][sum];
            int take = (sum >= num[ind]) ? dp[ind][sum - num[ind]] : INT_MAX;
            take = (take == INT_MAX) ? take : 1 + take;
            dp[ind][sum] = min(take, notTake);
        }
    }
    return dp[0][target] == INT_MAX ? -1 : dp[0][target];
}

int spaceOptimized(int ind, int target, vector<int> &num)
{

    vector<int> prev(target + 1), curr(target + 1);
    for (int sum = 0; sum <= target; sum++)
    {
        if (sum % num[num.size() - 1] == 0)
            prev[sum] = sum / num[num.size() - 1];
        else
            prev[sum] = INT_MAX;
    }

    for (int ind = num.size() - 2; ind >= 0; ind--)
    {
        for (int sum = 0; sum <= target; sum++)
        {

            int notTake = prev[sum];
            int take = (sum >= num[ind]) ? curr[sum - num[ind]] : INT_MAX;
            take = (take == INT_MAX) ? take : 1 + take;
            curr[sum] = min(take, notTake);
        }
        prev = curr;
    }
    return prev[target] == INT_MAX ? -1 : prev[target];
}

int minimumElements(vector<int> &num, int x)
{
    //     vector<vector<int>> dp(num.size(), vector<int>(x+1,-1));
    //     int ans = memoize(0,x,num,dp);
    //     return  (ans == INT_MAX) ? -1: ans ;
    return spaceOptimized(0, x, num);
}