/*
problem link: https://leetcode.com/problems/target-sum/
 */
#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int cntWays(vector<int> &nums, int target, int ind, vector<vector<int>> &dp)
    {

        if (ind == nums.size() - 1)
        {

            if (nums[ind] == 0 && target == 0)
                return 2;

            if (target == 0 || nums[ind] == target)
                return 1;

            return 0;
        }

        if (dp[ind][target] != -1)
            return dp[ind][target];

        return dp[ind][target] = ((target >= nums[ind]) ? cntWays(nums, target - nums[ind], ind + 1, dp) : 0) + cntWays(nums, target, ind + 1, dp);
    }

    int tabulation(vector<int> &nums, int targetSum, vector<vector<int>> &dp)
    {

        for (int ind = nums.size() - 1; ind >= 0; ind--)
        {
            for (int target = 0; target <= targetSum; target++)
            {

                if (ind == nums.size() - 1)
                {

                    if (nums[ind] == 0 && target == 0)
                        dp[ind][target] = 2;

                    else if (target == 0 || nums[ind] == target)
                        dp[ind][target] = 1;
                }
                else
                {
                    dp[ind][target] = ((target >= nums[ind]) ? dp[target - nums[ind]][ind + 1] : 0) + dp[target][ind + 1];
                }
            }
        }

        return dp[0][targetSum];
    }

    int spaceOptimized(vector<int> &nums, int targetSum, vector<vector<int>> &dp)
    {

        vector<int> prevRow(targetSum + 1), currRow(targetSum + 1);
        for (int ind = nums.size() - 1; ind >= 0; ind--)
        {
            for (int target = 0; target <= targetSum; target++)
            {

                if (ind == nums.size() - 1)
                {

                    if (nums[ind] == 0 && target == 0)
                        currRow[target] = 2;

                    else if (target == 0 || nums[ind] == target)
                        currRow[target] = 1;
                }
                else
                {
                    currRow[target] = ((target >= nums[ind]) ? prevRow[target - nums[ind]] : 0) + prevRow[target];
                }
            }

            prevRow = currRow;
        }

        return prevRow[targetSum];
    }

public:
    int findTargetSumWays(vector<int> &nums, int target)
    {

        int sum = 0;

        for (int num : nums)
            sum += num;

        if (sum - target < 0 || (sum - target) % 2)
            return 0;

        // vector<vector<int>> dp( nums.size(), vector<int>( (sum-target)/2 + 1,-1)) ;
        // return cntWays(nums,(sum-target)/2,0,dp);

        // vector<vector<int>> dp( nums.size(), vector<int>( (sum-target)/2 + 1));
        // return tabulation(nums, (sum - target)/2,dp);

        vector<vector<int>> dp(nums.size(), vector<int>((sum - target) / 2 + 1));
        return spaceOptimized(nums, (sum - target) / 2, dp);
    }
};
