/*
    problem link : https://www.codingninjas.com/codestudio/problems/can-you-make_4244510
    * idea: keep longest common subsequece and count operations for rest of the characters
*/

#include <bits/stdc++.h>
using namespace std;

int lcs(string &s, string &t)
{

    vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1));

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

    return dp[0][0];
}

int lcs_spaceOptimized(string &s, string &t)
{

    vector<int> prev(t.size() + 1), curr(t.size() + 1);

    for (int i = s.size() - 1; i >= 0; i--)
    {
        for (int j = t.size() - 1; j >= 0; j--)
        {
            if (s[i] == t[j])
                curr[j] = 1 + prev[j + 1];
            else
                curr[j] = max(prev[j], curr[j + 1]);
        }
        swap(prev, curr);
    }

    return prev[0];
}

int canYouMake(string &str, string &ptr)
{
    return str.size() + ptr.size() - 2 * lcs_spaceOptimized(str, ptr);
}