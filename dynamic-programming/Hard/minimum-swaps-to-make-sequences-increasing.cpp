// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/

#include <bits/stdc++.h>
using namespace std;

class Solution
{

    int countSwap(int index, bool swapped, vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &dp)
    {

        if (index == nums1.size())
            return 0;

        if (dp[index][swapped] != -1)
            return dp[index][swapped];

        int prev1 = nums1[index - 1];
        int prev2 = nums2[index - 1];

        if (swapped)
            swap(prev1, prev2);

        int ans = INT_MAX;

        // No swap
        if (nums1[index] > prev1 && nums2[index] > prev2)
            ans = countSwap(index + 1, false, nums1, nums2, dp);

        // Swap
        if (nums1[index] > prev2 && nums2[index] > prev1)
            ans = min(ans, 1 + countSwap(index + 1, true, nums1, nums2, dp));

        return dp[index][swapped] = ans;
    }

    int tabulation(vector<int> &nums1, vector<int> &nums2)
    {

        vector<vector<int>> dp(nums1.size() + 1, vector<int>(2));

        for (int index = nums1.size() - 1; index >= 1; --index)
        {

            for (int swapped = 1; swapped >= 0; --swapped)
            {

                int prev1 = nums1[index - 1];
                int prev2 = nums2[index - 1];

                if (swapped)
                    swap(prev1, prev2);

                int ans = INT_MAX;

                // No swap
                if (nums1[index] > prev1 && nums2[index] > prev2)
                    ans = dp[index + 1][false];

                // Swap
                if (nums1[index] > prev2 && nums2[index] > prev1)
                    ans = min(ans, 1 + dp[index + 1][true]);

                dp[index][swapped] = ans;
            }
        }

        return dp[1][false];
    }

    int spaceOptimized(vector<int> &nums1, vector<int> &nums2)
    {

        int no_swap = 0, do_swap = 0, curr_no_swap = 0, curr_do_swap = 0;

        for (int index = nums1.size() - 1; index >= 1; --index)
        {

            for (int swapped = 1; swapped >= 0; --swapped)
            {

                int prev1 = nums1[index - 1];
                int prev2 = nums2[index - 1];

                if (swapped)
                    swap(prev1, prev2);

                int ans = INT_MAX;

                // No swap
                if (nums1[index] > prev1 && nums2[index] > prev2)
                    ans = no_swap;

                // Swap
                if (nums1[index] > prev2 && nums2[index] > prev1)
                    ans = min(ans, 1 + do_swap);

                // dp[index][swapped] = ans;
                if (swapped)
                    curr_do_swap = ans;
                else
                    curr_no_swap = ans;
            }

            no_swap = curr_no_swap;
            do_swap = curr_do_swap;
        }

        return min(no_swap, do_swap);
    }

public:
    int minSwap(vector<int> &nums1, vector<int> &nums2)
    {

        nums1.insert(nums1.begin(), -1);
        nums2.insert(nums2.begin(), -1);

        // vector<vector<int>> dp(nums1.size(), vector<int>(2, -1));
        // return countSwap(1, false, nums1, nums2, dp);
        // return tabulation( nums1, nums2);
        return spaceOptimized(nums1, nums2);
    }
};