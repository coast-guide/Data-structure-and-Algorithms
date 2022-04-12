/*
    problem link: https://leetcode.com/problems/longest-string-chain/
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    static bool comp(string &word1, string &word2)
    {

        return word1.size() < word2.size();
    }

    bool canBuildChain(string &word1, string &word2)
    {

        int i = 0, j = 0;

        while (i < word1.size())
        {
            if (j < word2.size() && word1[i] == word2[j])
            {
                i++;
                j++;
            }
            else
                i++;
        }

        return i == word1.size() && j == word2.size();
    }

public:
    int longestStrChain(vector<string> &words)
    {

        // sort the strings according to length
        sort(words.begin(), words.end(), comp);

        vector<int> lis(words.size(), 1);

        int longest = 1;
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (words[i].size() - words[j].size() == 1 && canBuildChain(words[i], words[j]))
                    lis[i] = max(lis[i], 1 + lis[j]);
            }
            longest = max(longest, lis[i]);
        }

        return longest;
    }
};