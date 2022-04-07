/*
    problem link: https://leetcode.com/problems/distinct-subsequences/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int memoize(int i, int j, string &text, string &key, vector<vector<int>> &dp)
    {

        if (j == key.size())
        {
            return 1;
        }

        if (i == text.size())
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (text[i] == key[j])
            return dp[i][j] = (memoize(i + 1, j + 1, text, key, dp) + memoize(i + 1, j, text, key, dp));

        return dp[i][j] = memoize(i + 1, j, text, key, dp);
    }

    int tabulation(string &text, string &key)
    {
        vector<vector<int>> dp(text.size() + 1, vector<int>(key.size() + 1));

        for (int i = text.size(); i >= 0; i--)
        {
            for (int j = key.size(); j >= 0; j--)
            {
                if (j == key.size())
                    dp[i][j] = 1;
                else if (i == text.size())
                    dp[i][j] = 0;
                else if (text[i] == key[j])
                    dp[i][j] = (dp[i + 1][j + 1] + dp[i + 1][j]);
                else
                    dp[i][j] = dp[i + 1][j];
            }
        }

        return dp[0][0];
    }

    int spaceOptimized(string &text, string &key)
    {

        vector<int> prev(key.size() + 1), curr(key.size() + 1);
        for (int i = text.size(); i >= 0; i--)
        {
            for (int j = key.size(); j >= 0; j--)
            {
                if (j == key.size())
                    curr[j] = 1;
                else if (i == text.size())
                    curr[j] = 0;
                else if (text[i] == key[j])
                    curr[j] = (prev[j + 1] + prev[j]);
                else
                    curr[j] = prev[j];
            }

            prev = curr;
        }

        return prev[0];
    }

    int singleArraySpaceOptimized(string &text, string &key)
    {

        vector<double> prev(key.size() + 1);
        for (int i = text.size(); i >= 0; i--)
        {
            for (int j = 0; j <= key.size(); j++)
            {
                if (j == key.size())
                    prev[j] = 1;
                else if (i == text.size())
                    prev[j] = 0;
                else if (text[i] == key[j])
                    prev[j] = (prev[j + 1] + prev[j]);
            }
        }

        return (int)prev[0];
    }

public:
    int numDistinct(string s, string t)
    {

        return singleArraySpaceOptimized(s, t);
    }
};