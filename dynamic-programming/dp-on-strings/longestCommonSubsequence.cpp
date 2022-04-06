/*
    problem-link: https://www.codingninjas.com/codestudio/problems/longest-common-subsequence_624879
 */

#include <bits/stdc++.h>
using namespace std;

int memoized(int s_ind, int t_ind, string &s, string &t, vector<vector<int>> &dp)
{
    if (s_ind == s.size() || t_ind == t.size())
        return 0;

    if (dp[s_ind][t_ind] != -1)
        return dp[s_ind][t_ind];

    if (s[s_ind] == t[t_ind])
        return dp[s_ind][t_ind] = 1 + memoized(s_ind + 1, t_ind + 1, s, t, dp);

    return dp[s_ind][t_ind] = max(memoized(s_ind, t_ind + 1, s, t, dp), memoized(s_ind + 1, t_ind, s, t, dp));
}

int tabulation(string &s, string &t)
{
    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));

    for (int s_ind = s.size(); s_ind >= 0; s_ind--)
    {
        for (int t_ind = t.size(); t_ind >= 0; t_ind--)
        {
            if (s_ind == s.size() || t_ind == t.size())
                dp[s_ind][t_ind] = 0;

            else if (s[s_ind] == t[t_ind])
                dp[s_ind][t_ind] = 1 + dp[s_ind + 1][t_ind + 1];

            else
                dp[s_ind][t_ind] = max(dp[s_ind][t_ind + 1], dp[s_ind + 1][t_ind]);
        }
    }

    return dp[0][0];
}
int spaceOptimized(string &s, string &t)
{
    vector<int> prev(t.size() + 1), curr(t.size() + 1);

    for (int s_ind = s.size(); s_ind >= 0; s_ind--)
    {
        for (int t_ind = t.size(); t_ind >= 0; t_ind--)
        {
            if (s_ind == s.size() || t_ind == t.size())
                curr[t_ind] = 0;

            else if (s[s_ind] == t[t_ind])
                curr[t_ind] = 1 + prev[t_ind + 1];

            else
                curr[t_ind] = max(curr[t_ind + 1], prev[t_ind]);
        }
        prev = curr;
    }

    return prev[0];
}

int lcs(string s, string t)
{
    // vector<vector<int>> dp(s.size(), vector<int>(t.size(), -1));
    // return memoized(0, 0, s, t, dp);

    return spaceOptimized(s, t);
}