/*
    problem link: https://leetcode.com/problems/largest-divisible-subset/
*/

#include <bits/stdc++.h>
using namespace std;

/*
    *Idea:
        1> sort the array.
        2> apply LIS.
*/

class Solution
{
public:
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {

        sort(nums.begin(), nums.end());

        vector<int> lis(nums.size(), 1), prev(nums.size(), -1);

        int maxInd = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] % nums[j] == 0 && lis[j] + 1 > lis[i])
                {
                    lis[i] = lis[j] + 1;
                    prev[i] = j;
                }
            }
            if (lis[maxInd] < lis[i])
                maxInd = i;
        }

        vector<int> ans;
        int j = maxInd;
        while (j >= 0)
        {

            ans.push_back(nums[j]);
            j = prev[j];
        }

        return ans;
    }
};