/*
    Problem link: https://leetcode.com/problems/shortest-common-supersequence/

    Idea: think on "print longest common subsequence" problem
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    void lcsTable(string &s, string &t, vector<vector<int>> &dp)
    {

        for (int i = s.size() - 1; i >= 0; i--)
        {
            for (int j = t.size() - 1; j >= 0; j--)
            {
                if (s[i] == t[j])
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }

public:
    string shortestCommonSupersequence(string s, string t)
    {

        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));
        lcsTable(s, t, dp);

        string scs;

        int i = 0, j = 0;

        while (i < s.size() && j < t.size())
        {

            if (s[i] == t[j])
            {
                scs.push_back(s[i]);
                i++;
                j++;
            }
            else if (dp[i + 1][j] > dp[i][j + 1])
            {
                scs.push_back(s[i]);
                i++;
            }
            else
            {
                scs.push_back(t[j]);
                j++;
            }
        }

        while (i < s.size())
            scs.push_back(s[i++]);
        while (j < t.size())
            scs.push_back(t[j++]);

        return scs;
    }
};
