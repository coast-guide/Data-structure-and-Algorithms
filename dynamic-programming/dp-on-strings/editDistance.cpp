#include <bits/stdc++.h>
using namespace std;

/*
    problem link : https://leetcode.com/problems/edit-distance/
*/

class Solution
{

    int memoize(int i, int j, string &s, string &t, vector<vector<int>> &dp)
    {
        if (j == t.size())
            return s.size() - i;

        if (i == s.size())
            return t.size() - j;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j])
            return dp[i][j] = memoize(i + 1, j + 1, s, t, dp);

        int insertOp = 1 + memoize(i, j + 1, s, t, dp);
        int deleteOp = 1 + memoize(i + 1, j, s, t, dp);
        int replaceOp = 1 + memoize(i + 1, j + 1, s, t, dp);

        return dp[i][j] = min(insertOp, min(deleteOp, replaceOp));
    }

    int tabulation(string &s, string &t)
    {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));

        for (int i = s.size(); i >= 0; i--)
        {
            for (int j = t.size(); j >= 0; j--)
            {
                if (j == t.size())
                    dp[i][j] = s.size() - i;
                else if (i == s.size())
                    dp[i][j] = t.size() - j;
                else if (s[i] == t[j])
                    dp[i][j] = dp[i + 1][j + 1];
                else
                    dp[i][j] = min(1 + dp[i][j + 1], min(1 + dp[i + 1][j], 1 + dp[i + 1][j + 1]));
            }
        }
        return dp[0][0];
    }

    int spaceOptimized(string &s, string &t)
    {
        vector<int> prev(t.size() + 1), curr(t.size() + 1);
        for (int i = s.size(); i >= 0; i--)
        {
            for (int j = t.size(); j >= 0; j--)
            {
                if (j == t.size())
                    curr[j] = s.size() - i;
                else if (i == s.size())
                    curr[j] = t.size() - j;
                else if (s[i] == t[j])
                    curr[j] = prev[j + 1];
                else
                    curr[j] = min(1 + curr[j + 1], min(1 + prev[j], 1 + prev[j + 1]));
            }
            prev = curr;
        }
        return prev[0];
    }

public:
    int minDistance(string word1, string word2)
    {
        //     	vector<vector<int>> dp(word1.size(), vector<int>(word2.size(), -1));
        // return memoize(0,0,word1,word2,dp);

        //     return tabulation(word1,word2);
        return spaceOptimized(word1, word2);
    }
};