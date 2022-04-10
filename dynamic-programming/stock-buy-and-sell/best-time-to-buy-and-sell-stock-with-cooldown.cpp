#include <bits/stdc++.h>
using namespace std;
class Solution
{

    int memoize(int i, bool hasStock, vector<int> &prices, vector<vector<int>> &dp)
    {

        if (i >= prices.size())
            return 0;

        if (dp[i][hasStock] != -1)
            return dp[i][hasStock];

        if (hasStock)
        {
            int sell = prices[i] + memoize(i + 2, false, prices, dp);
            int skip = memoize(i + 1, true, prices, dp);
            return dp[i][hasStock] = max(sell, skip);
        }

        int buy = -prices[i] + memoize(i + 1, true, prices, dp);
        int skip = memoize(i + 1, false, prices, dp);
        return dp[i][hasStock] = max(buy, skip);
    }

    int tabulation(vector<int> &prices)
    {

        vector<vector<int>> dp(prices.size(), vector<int>(2));

        for (int i = prices.size() - 1; i >= 0; i--)
        {
            for (int hasStock = 0; hasStock <= 1; hasStock++)
            {
                if (hasStock)
                {
                    int sell = prices[i] + (i + 2 < prices.size() ? dp[i + 2][0] : 0);
                    int skip = (i + 1 < prices.size() ? dp[i + 1][1] : 0);
                    dp[i][hasStock] = max(sell, skip);
                }
                else
                {
                    int buy = -prices[i] + (i + 1 < prices.size() ? dp[i + 1][1] : 0);
                    int skip = (i + 1 < prices.size() ? dp[i + 1][0] : 0);
                    dp[i][hasStock] = max(buy, skip);
                }
            }
        }
        return dp[0][0];
    }

    int spaceOptimized(vector<int> &prices)
    {

        vector<int> prevOfPrev(2), prev(2), curr(2);

        for (int i = prices.size() - 1; i >= 0; i--)
        {
            for (int hasStock = 0; hasStock <= 1; hasStock++)
            {
                if (hasStock)
                {
                    int sell = prices[i] + (i + 2 < prices.size() ? prevOfPrev[0] : 0);
                    int skip = (i + 1 < prices.size() ? prev[1] : 0);
                    curr[hasStock] = max(sell, skip);
                }
                else
                {
                    int buy = -prices[i] + (i + 1 < prices.size() ? prev[1] : 0);
                    int skip = (i + 1 < prices.size() ? prev[0] : 0);
                    curr[hasStock] = max(buy, skip);
                }
            }
            prevOfPrev = prev;
            prev = curr;
        }
        return prev[0];
    }

public:
    int maxProfit(vector<int> &prices)
    {
        // 	vector<vector<int>> dp(prices.size(),vector<int>(2,-1));
        // 	return memoize(0,false,prices,dp);

        return spaceOptimized(prices);
    }
};