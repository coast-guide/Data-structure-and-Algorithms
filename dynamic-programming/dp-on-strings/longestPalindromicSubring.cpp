/*
problem link: https://leetcode.com/problems/longest-palindromic-substring/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
    string longestPalindrome_dp(string &s)
    {
        const int n = s.size();
        bool dp[n][n];
        memset(dp, false, sizeof dp);

        int max_start = 0, max_len = 1;

        for (int len = 1; len <= n; ++len)
        {

            for (int start = 0, end = start + len - 1; end < n; ++start, ++end)
            {

                bool isPalindrome = (len == 1) || (len == 2 && s[start] == s[end]) || (s[start] == s[end] && dp[start + 1][end - 1] == true);

                if (isPalindrome)
                {
                    if (end - start + 1 > max_len)
                    {
                        max_start = start;
                        max_len = end - start + 1;
                    }
                    dp[start][end] = true;
                }
            }
        }

        return s.substr(max_start, max_len);
    }

    void check_for_palindrome(int left, int right, const string &s, int &start, int &longest)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {

            if (right - left + 1 > longest)
            {

                longest = right - left + 1;
                start = left;
            }

            --left;
            ++right;
        }
    }

    string find_longest_palindrome(const string &s)
    {
        int longest = 1, start = 0;

        for (int i = 0; i < s.size(); ++i)
        {
            // odd length palindromes
            check_for_palindrome(i, i, s, start, longest);

            // even length palindromes
            check_for_palindrome(i, i + 1, s, start, longest);
        }

        return s.substr(start, longest);
    }

public:
    string longestPalindrome(string s)
    {
        return longestPalindrome_dp(s);
    }
};