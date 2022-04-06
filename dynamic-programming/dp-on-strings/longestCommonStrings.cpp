/*
problem link: https://www.codingninjas.com/codestudio/problems/longest-common-substring_1235207
*/

#include <bits/stdc++.h>
using namespace std;

int longestCommonSubstring(int i, int j, int currLen, string &str1, string &str2)
{

    if (i == str1.size() || j == str2.size())
        return currLen;

    if (str1[i] == str2[j])
        currLen = longestCommonSubstring(i + 1, j + 1, currLen + 1, str1, str2);

    int len1 = longestCommonSubstring(i, j + 1, 0, str1, str2);
    int len2 = longestCommonSubstring(i + 1, j, 0, str1, str2);

    return max(currLen, max(len1, len2));
}

int tabulation(string &str1, string &str2)
{
    vector<vector<int>> dp(str1.size() + 1, vector<int>(str2.size() + 1));

    int maxLen = 0;
    for (int i = 1; i <= str1.size(); i++)
    {
        for (int j = 1; j <= str2.size(); j++)
        {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = 0;

            maxLen = max(maxLen, dp[i][j]);
        }
    }

    return maxLen;
}
int spaceOptimized(string &str1, string &str2)
{
    vector<int> prev(str2.size() + 1), curr(str2.size() + 1);

    int maxLen = 0;
    for (int i = 1; i <= str1.size(); i++)
    {
        for (int j = 1; j <= str2.size(); j++)
        {
            if (str1[i - 1] == str2[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = 0;

            maxLen = max(maxLen, curr[j]);
        }
        prev = curr;
    }

    return maxLen;
}

int lcs(string &str1, string &str2)
{
    // return longestCommonSubstring(0,0,0,str1,str2);
    // return tabulation(str1, str2);
    return spaceOptimized(str1, str2);
}