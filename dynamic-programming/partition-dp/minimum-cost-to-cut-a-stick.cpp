/*

    problem link : https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int cost(int l, int r, vector<int> &cuts, vector<vector<int>> &dp)
    {

        if (l > r)
            return 0;

        if (dp[l][r] != -1)
            return dp[l][r];

        int minCost = INT_MAX;

        for (int i = l; i <= r; i++)
        {
            minCost = min(minCost, cuts[r + 1] - cuts[l - 1] + cost(l, i - 1, cuts, dp) + cost(i + 1, r, cuts, dp));
        }

        return dp[l][r] = minCost;
    }

    int tabulation(int c, vector<int> &cuts)
    {

        vector<vector<int>> dp(cuts.size() + 1, vector<int>(cuts.size() + 1));

        for (int l = c; l >= 1; l--)
        {

            for (int r = 1; r <= c; r++)
            {

                if (l > r)
                    continue;

                int minCost = INT_MAX;

                for (int i = l; i <= r; i++)
                    minCost = min(minCost, cuts[r + 1] - cuts[l - 1] + dp[l][i - 1] + dp[i + 1][r]);

                dp[l][r] = minCost;
            }
        }

        return dp[1][c];
    }

public:
    int minCost(int n, vector<int> &cuts)
    {

        int c = cuts.size();
        sort(cuts.begin(), cuts.end());
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);
        // vector<vector<int>> dp(cuts.size() + 1, vector<int>(cuts.size()+1,-1));
        // return cost(1,c,cuts,dp);

        return tabulation(c, cuts);
    }
};