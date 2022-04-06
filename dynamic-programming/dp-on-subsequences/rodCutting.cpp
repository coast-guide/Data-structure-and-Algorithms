#include <bits/stdc++.h>
using namespace std;

/*
Problem link: https://www.codingninjas.com/codestudio/problems/rod-cutting-problem_800284
 */

int memoize(int ind, int length, vector<int> &price, vector<vector<int>> &dp)
{

    if (ind == price.size() - 1)
        return dp[ind][length] = (length / (ind + 1)) * price[ind];

    if (length == 0)
        return dp[ind][length] = 0;

    if (dp[ind][length] != -1)
        return dp[ind][length];

    return dp[ind][length] = max(memoize(ind + 1, length, price, dp), (length - ind - 1 >= 0 ? price[ind] + memoize(ind, length - ind - 1, price, dp) : 0));
}
int tabulation(int len, vector<int> &price)
{
    const int n = price.size();
    vector<vector<int>> dp(n, vector<int>(len + 1));

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int length = 0; length <= len; length++)
        {
            if (ind == n - 1)
                dp[ind][length] = (length / (ind + 1)) * price[ind];

            else if (length == 0)
                dp[ind][length] = 0;
            else
                dp[ind][length] = max(dp[ind + 1][length], (length - ind - 1 >= 0 ? price[ind] + dp[ind][length - ind - 1] : 0));
        }
    }

    return dp[0][len];
}
int spaceOptimizedTwoArray(int len, vector<int> &price)
{
    const int n = price.size();
    vector<int> curr(len + 1), prev(len + 1);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int length = 0; length <= len; length++)
        {
            if (ind == n - 1)
                curr[length] = (length / (ind + 1)) * price[ind];

            else if (length == 0)
                curr[length] = 0;
            else
                curr[length] = max(prev[length], (length - ind - 1 >= 0 ? price[ind] + curr[length - ind - 1] : 0));
        }
        prev = curr;
    }

    return prev[len];
}
int spaceOptimizedSingleArray(int len, vector<int> &price)
{
    const int n = price.size();
    vector<int> prev(len + 1);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int length = 0; length <= len; length++)
        {
            if (ind == n - 1)
                prev[length] = (length / (ind + 1)) * price[ind];

            else if (length == 0)
                prev[length] = 0;
            else
                prev[length] = max(prev[length], (length - ind - 1 >= 0 ? price[ind] + prev[length - ind - 1] : 0));
        }
    }

    return prev[len];
}

int cutRod(vector<int> &price, int length)
{
    // vector<vector<int>> dp(price.size(), vector<int>(length + 1, -1));
    // return memoize(0, length, price, dp);
    // return tabulation(length, price);
    // return spaceOptimizedTwoArray(length, price);
    return spaceOptimizedSingleArray(length, price);
}
