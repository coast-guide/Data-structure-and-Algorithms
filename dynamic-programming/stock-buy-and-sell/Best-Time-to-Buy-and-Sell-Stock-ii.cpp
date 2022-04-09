/*
    problem link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int profit(int i, bool hasStock, vector<int> &values, int n, vector<vector<int>> &dp)
    {

        if (i == n)
            return 0;

        if (dp[i][hasStock] != -1)
            return dp[i][hasStock];

        int skip = profit(i + 1, hasStock, values, n, dp);

        if (hasStock)
        {
            int sell = values[i] + profit(i + 1, false, values, n, dp);
            return dp[i][hasStock] = max(sell, skip);
        }

        int buy = -values[i] + profit(i + 1, true, values, n, dp);

        return dp[i][hasStock] = max(buy, skip);
    }

    int tabulation(vector<int> &values, int n)
    {

        vector<vector<int>> dp(n + 1, vector<int>(2));

        for (int i = n - 1; i >= 0; i--)
        {
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {
                int skip = dp[i + 1][hasStock];

                if (hasStock)
                {
                    int sell = values[i] + dp[i + 1][false];
                    dp[i][hasStock] = max(sell, skip);
                }
                else
                {
                    int buy = -values[i] + dp[i + 1][true];
                    dp[i][hasStock] = max(buy, skip);
                }
            }
        }

        return dp[0][0];
    }

    int spaceOptimized(vector<int> &values, int n)
    {

        vector<int> curr(2), prev(2);
        for (int i = n - 1; i >= 0; i--)
        {
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {
                int skip = prev[hasStock];

                if (hasStock)
                {
                    int sell = values[i] + prev[false];
                    curr[hasStock] = max(sell, skip);
                }
                else
                {
                    int buy = -values[i] + prev[true];
                    curr[hasStock] = max(buy, skip);
                }
            }
            swap(curr, prev);
        }

        return prev[0];
    }

    int spaceOptimizedVariables(vector<int> &values, int n)
    {

        int not_has_stock_ahead = 0, has_stock_ahead = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            int not_has_stock_curr = 0, has_stock_curr = 0;
            for (int hasStock = 1; hasStock >= 0; hasStock--)
            {

                if (hasStock)
                {
                    int sell = values[i] + not_has_stock_ahead;
                    int skip = has_stock_ahead;
                    has_stock_curr = max(sell, skip);
                }
                else
                {
                    int buy = -values[i] + has_stock_ahead;
                    int skip = not_has_stock_ahead;
                    not_has_stock_curr = max(buy, skip);
                }
            }
            not_has_stock_ahead = not_has_stock_curr;
            has_stock_ahead = has_stock_curr;
        }

        return not_has_stock_ahead;
    }

public:
    int maxProfit(vector<int> &prices)
    {
        // 	vector<vector<int>> dp(prices.size(), vector<int>(2,-1));
        // 	return profit(0,false,prices,n,dp);

        return spaceOptimizedVariables(prices, prices.size());
    }
};