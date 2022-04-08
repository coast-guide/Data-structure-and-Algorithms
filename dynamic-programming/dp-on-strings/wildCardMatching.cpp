/*
    problem link : https://leetcode.com/problems/wildcard-matching/
 */

#include <bits/stdc++.h>
using namespace std;
class Solution
{

    bool memoize(int s_ind, int p_ind, string &s, string &p, vector<vector<int>> &dp)
    {

        if (p_ind == p.size() && s_ind == s.size())
            return true;

        if (p_ind == p.size() && s_ind < s.size())
            return false;

        if (dp[p_ind][s_ind] != -1)
            return dp[p_ind][s_ind];

        if (s_ind == s.size() && p_ind < p.size())
        {

            bool flag = true;
            for (int i = p_ind; i < p.size(); i++)
                if (p[i] != '*')
                {
                    flag = false;
                    break;
                }

            return dp[p_ind][s_ind] = flag;
        }

        if (p[p_ind] == s[s_ind] || p[p_ind] == '?')
            return dp[p_ind][s_ind] = memoize(s_ind + 1, p_ind + 1, s, p, dp);

        if (p[p_ind] == '*')
            return dp[p_ind][s_ind] = memoize(s_ind, p_ind + 1, s, p, dp) || memoize(s_ind + 1, p_ind, s, p, dp);

        return dp[p_ind][s_ind] = false;
    }

    bool tabulation(string &s, string &p)
    {

        vector<vector<int>> dp(p.size() + 1, vector<int>(s.size() + 1));

        for (int p_ind = p.size(); p_ind >= 0; p_ind--)
        {
            for (int s_ind = s.size(); s_ind >= 0; s_ind--)
            {

                if (p_ind == p.size() && s_ind == s.size())
                    dp[p_ind][s_ind] = true;

                else if (p_ind == p.size() && s_ind < s.size())
                    dp[p_ind][s_ind] = false;

                else if (s_ind == s.size() && p_ind < p.size())
                {

                    bool flag = true;
                    for (int i = p_ind; i < p.size(); i++)
                        if (p[i] != '*')
                        {
                            flag = false;
                            break;
                        }

                    dp[p_ind][s_ind] = flag;
                }

                else if (p[p_ind] == s[s_ind] || p[p_ind] == '?')
                    dp[p_ind][s_ind] = dp[p_ind + 1][s_ind + 1];

                else if (p[p_ind] == '*')
                    dp[p_ind][s_ind] = dp[p_ind + 1][s_ind] || dp[p_ind][s_ind + 1];
                else
                    dp[p_ind][s_ind] = false;
            }
        }

        return dp[0][0];
    }

    bool spaceOptimized(string &s, string &p)
    {

        vector<int> prev(s.size() + 1), curr(s.size() + 1);

        for (int p_ind = p.size(); p_ind >= 0; p_ind--)
        {
            for (int s_ind = s.size(); s_ind >= 0; s_ind--)
            {

                if (p_ind == p.size() && s_ind == s.size())
                    curr[s_ind] = true;

                else if (p_ind == p.size() && s_ind < s.size())
                    curr[s_ind] = false;

                else if (s_ind == s.size() && p_ind < p.size())
                {

                    bool flag = true;
                    for (int i = p_ind; i < p.size(); i++)
                        if (p[i] != '*')
                        {
                            flag = false;
                            break;
                        }

                    curr[s_ind] = flag;
                }

                else if (p[p_ind] == s[s_ind] || p[p_ind] == '?')
                    curr[s_ind] = prev[s_ind + 1];

                else if (p[p_ind] == '*')
                    curr[s_ind] = prev[s_ind] || curr[s_ind + 1];
                else
                    curr[s_ind] = false;
            }
            prev = curr;
        }

        return prev[0];
    }

public:
    bool isMatch(string s, string p)
    {

        //        vector<vector<int>> dp(p.size(), vector<int>(s.size() + 1, -1));
        //        return memoize(0,0,s,p,dp);

        return spaceOptimized(s, p);
    }
};