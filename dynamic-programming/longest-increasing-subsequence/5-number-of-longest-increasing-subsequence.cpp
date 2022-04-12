#include <bits/stdc++.h>
using namespace std;

/*
    problem link : https://leetcode.com/problems/number-of-longest-increasing-subsequence/
 */

class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {

        vector<int> lis(nums.size(), 1), count(nums.size(), 1);

        int longest = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {

                if (nums[i] > nums[j])
                {
                    if (1 + lis[j] > lis[i])
                    {
                        lis[i] = 1 + lis[j];
                        count[i] = count[j];
                    }
                    else if (1 + lis[j] == lis[i])
                        count[i] += count[j];
                }
            }
            longest = max(longest, lis[i]);
        }

        int cnt = 0;
        for (int i = 0; i < nums.size(); i++)
            if (lis[i] == longest)
                cnt += count[i];

        return cnt;
    }
};