/*
    problem link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int memoize(int i, bool hasStock, int fee, vector<int> &prices, vector<vector<int>> &dp)
    {

        if (i == prices.size())
            return 0;

        if (dp[i][hasStock] != -1)
            return dp[i][hasStock];
        if (hasStock)
        {
            int sell = prices[i] - fee + memoize(i + 1, false, fee, prices, dp);
            int skip = memoize(i + 1, true, fee, prices, dp);
            return dp[i][hasStock] = max(sell, skip);
        }

        int buy = -prices[i] + memoize(i + 1, true, fee, prices, dp);
        int skip = memoize(i + 1, false, fee, prices, dp);
        return dp[i][hasStock] = max(buy, skip);
    }

    int tabulation(int fee, vector<int> &prices)
    {

        vector<vector<int>> dp(prices.size() + 1, vector<int>(2));

        for (int i = prices.size() - 1; i >= 0; i--)
        {
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {
                if (hasStock)
                {
                    int sell = prices[i] - fee + dp[i + 1][0];
                    int skip = dp[i + 1][1];
                    dp[i][hasStock] = max(sell, skip);
                }
                else
                {
                    int buy = -prices[i] + dp[i + 1][1];
                    int skip = dp[i + 1][0];
                    dp[i][hasStock] = max(buy, skip);
                }
            }
        }

        return dp[0][0];
    }

    int spaceOptimized(int fee, vector<int> &prices)
    {

        vector<int> curr(2), prev(2);

        for (int i = prices.size() - 1; i >= 0; i--)
        {
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {
                if (hasStock)
                {
                    int sell = prices[i] - fee + prev[0];
                    int skip = prev[1];
                    curr[hasStock] = max(sell, skip);
                }
                else
                {
                    int buy = -prices[i] + prev[1];
                    int skip = prev[0];
                    curr[hasStock] = max(buy, skip);
                }
            }
            swap(curr, prev);
        }

        return prev[0];
    }

public:
    int maxProfit(vector<int> &prices, int fee)
    {
        // 	vector<vector<int>> dp(prices.size(),vector<int>(2,-1));
        // return memoize(0,false,fee,prices,dp);

        return spaceOptimized(fee, prices);
    }
};