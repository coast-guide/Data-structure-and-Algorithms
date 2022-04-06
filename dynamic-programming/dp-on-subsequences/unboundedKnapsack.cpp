/*
    problem link : https://www.codingninjas.com/codestudio/problems/unbounded-knapsack_1215029
 */

#include <bits/stdc++.h>
using namespace std;

int memoize(int i, int w, vector<int> &profit, vector<int> &weight, vector<vector<int>> &dp)
{

    if (i == profit.size() - 1)
        return dp[i][w] = (w / weight[i]) * profit[i];

    if (w == 0)
        return dp[i][w] = 0;

    if (dp[i][w] != -1)
        return dp[i][w];

    return dp[i][w] = max(memoize(i + 1, w, profit, weight, dp), (w >= weight[i] ? profit[i] + memoize(i, w - weight[i], profit, weight, dp) : 0));
}

int tabulation(int n, int wt, vector<int> &profit, vector<int> &weight)
{
    vector<vector<int>> dp(n, vector<int>(wt + 1));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int w = 0; w <= wt; w++)
        {

            if (i == n - 1)
                dp[i][w] = (w / weight[i]) * profit[i];
            else if (w == 0)
                dp[i][w] = 0;
            else
                dp[i][w] = max(dp[i + 1][w], (w >= weight[i] ? profit[i] + dp[i][w - weight[i]] : 0));
        }
    }

    return dp[0][wt];
}
int spaceOptimized(int n, int wt, vector<int> &profit, vector<int> &weight)
{
    vector<int> prev(wt + 1), curr(wt + 1);

    for (int i = n - 1; i >= 0; i--)
    {
        for (int w = 0; w <= wt; w++)
        {

            if (i == n - 1)
                curr[w] = (w / weight[i]) * profit[i];
            else if (w == 0)
                curr[w] = 0;
            else
                curr[w] = max(prev[w], (w >= weight[i] ? profit[i] + curr[w - weight[i]] : 0));
        }
        prev = curr;
    }

    return prev[wt];
}
int singleArraySpaceOptimized(int n, int wt, vector<int> &profit, vector<int> &weight)
{
    vector<int> prev(wt + 1);

    for (int i = n - 1; i >= 0; i--)
    {
        for (int w = 0; w <= wt; w++)
        {

            if (i == n - 1)
                prev[w] = (w / weight[i]) * profit[i];
            else if (w == 0)
                prev[w] = 0;
            else
                prev[w] = max(prev[w], (w >= weight[i] ? profit[i] + prev[w - weight[i]] : 0));
        }
    }

    return prev[wt];
}

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
{
    // vector<vector<int>> dp(n, vector<int>(w+1,-1));
    // return memoize(0,w,profit,weight,dp);

    // return tabulation(n, w, profit, weight);
    // return spaceOptimized(n, w, profit, weight);
    return singleArraySpaceOptimized(n, w, profit, weight);
}
