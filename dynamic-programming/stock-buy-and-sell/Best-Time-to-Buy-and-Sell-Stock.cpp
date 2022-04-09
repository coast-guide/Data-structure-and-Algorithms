/*
    problem link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        // Sell at i'th day and buy at min price [0...i-1] day

        int minDay = prices[0], profit = 0;

        for (int i = 1; i < prices.size(); i++)
        {
            profit = max(profit, prices[i] - minDay);
            minDay = min(minDay, prices[i]);
        }

        return profit;
    }
};