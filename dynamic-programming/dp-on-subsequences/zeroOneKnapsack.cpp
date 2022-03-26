/*
problem link: https://www.codingninjas.com/codestudio/problems/0-1-knapsack_920542
 */
#include <bits/stdc++.h>
using namespace std;
int getWeight(int ind, int w, vector<int> &weight, vector<int> &value, vector<vector<int>> &dp)
{

    if (ind == weight.size() - 1)
    {
        if (weight[ind] <= w)
            return value[ind];
        else
            return 0;
    }

    if (dp[ind][w] != -1)
        return dp[ind][w];

    int notTake = getWeight(ind + 1, w, weight, value, dp);
    int take = (w >= weight[ind]) ? value[ind] + getWeight(ind + 1, w - weight[ind], weight, value, dp) : 0;
    return dp[ind][w] = max(take, notTake);
}

int tabulation(int ind, int maxWeight, vector<int> &weight, vector<int> &value)
{
    const int n = weight.size();
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int w = 0; w <= maxWeight; w++)
        {
            if (ind == n - 1)
            {
                if (weight[ind] <= w)
                    dp[ind][w] = value[ind];
                else
                    dp[ind][w] = 0;
            }
            else
            {
                int notTake = dp[ind + 1][w];
                int take = (w >= weight[ind]) ? value[ind] + dp[ind + 1][w - weight[ind]] : 0;
                dp[ind][w] = max(take, notTake);
            }
        }
    }
    return dp[0][maxWeight];
}

int spaceOptimized(int ind, int maxWeight, vector<int> &weight, vector<int> &value)
{
    const int n = weight.size();
    vector<int> prev(maxWeight + 1);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        //         vector<int> curr(maxWeight+1);
        for (int w = maxWeight; w >= 0; w--)
        {
            if (ind == n - 1)
            {
                if (weight[ind] <= w)
                    prev[w] = value[ind];
                else
                    prev[w] = 0;
            }
            else
            {
                int notTake = prev[w];
                int take = (w >= weight[ind]) ? value[ind] + prev[w - weight[ind]] : 0;
                prev[w] = max(take, notTake);
            }
        }
        //          prev = curr;
    }
    return prev[maxWeight];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
{

    //     vector<vector<int>> dp(n,vector<int>(maxWeight+1,-1));
    //     return getWeight(0,maxWeight, weight, value,dp) ;

    return spaceOptimized(0, maxWeight, weight, value);
}