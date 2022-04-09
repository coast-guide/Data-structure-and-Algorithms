
/*
    problem link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int memoize(int i, bool hasStock, int transactionCount, vector<int> &prices, vector<vector<vector<int>>> &dp)
    {
        if (i == prices.size() || transactionCount == 0)
            return 0;

        if (dp[i][hasStock][transactionCount] != -1)
            return dp[i][hasStock][transactionCount];

        int skip = memoize(i + 1, hasStock, transactionCount, prices, dp);

        if (hasStock)
        {
            int sell = prices[i] + memoize(i + 1, false, transactionCount - 1, prices, dp);
            return dp[i][hasStock][transactionCount] = max(skip, sell);
        }

        int buy = -prices[i] + memoize(i + 1, true, transactionCount, prices, dp);
        return dp[i][hasStock][transactionCount] = max(buy, skip);
    }

    int tabulation(int k, vector<int> &prices)
    {
        const int n = prices.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1)));

        for (int i = n - 1; i >= 0; i--)
        {
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {
                for (int transactionCount = 1; transactionCount <= k; transactionCount++)
                {

                    if (hasStock)
                    {
                        int sell = prices[i] + dp[i + 1][false][transactionCount - 1];
                        int skip = dp[i + 1][hasStock][transactionCount];
                        dp[i][hasStock][transactionCount] = max(skip, sell);
                    }
                    else
                    {
                        int buy = -prices[i] + dp[i + 1][true][transactionCount];
                        int skip = dp[i + 1][hasStock][transactionCount];
                        dp[i][hasStock][transactionCount] = max(buy, skip);
                    }
                }
            }
        }

        return dp[0][0][k];
    }

    int spaceOptimized(int k, vector<int> &prices)
    {
        const int n = prices.size();
        vector<vector<int>> curr(2, vector<int>(k + 1)), prev(2, vector<int>(k + 1));

        for (int i = n - 1; i >= 0; i--)
        {
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {
                for (int transactionCount = 1; transactionCount <= k; transactionCount++)
                {

                    if (hasStock)
                    {
                        int sell = prices[i] + prev[false][transactionCount - 1];
                        int skip = prev[hasStock][transactionCount];
                        curr[hasStock][transactionCount] = max(skip, sell);
                    }
                    else
                    {
                        int buy = -prices[i] + prev[true][transactionCount];
                        int skip = prev[hasStock][transactionCount];
                        curr[hasStock][transactionCount] = max(buy, skip);
                    }
                }
            }
            swap(curr, prev);
        }

        return prev[0][k];
    }

public:
    int maxProfit(int k, vector<int> &prices)
    {

        // vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(2,vector<int>(k+1,-1)));
        // return memoize(0,false,k,prices,dp);

        return spaceOptimized(k, prices);
    }
};