// https://leetcode.com/problems/trapping-rain-water/

#include <bits/stdc++.h>
using namespace std;

// First Approach :  Time ⇒ O(N) , Space ⇒ O(N)
class Solution
{
public:
    int trap(vector<int> &height)
    {

        vector<int> leftMax(height.size()), rightMax(height.size());

        leftMax[0] = height[0];

        rightMax[height.size() - 1] = height[height.size() - 1];

        for (int i = 1; i < height.size(); ++i)
            leftMax[i] = max(height[i], leftMax[i - 1]);

        for (int i = height.size() - 2; i >= 0; --i)
            rightMax[i] = max(height[i], rightMax[i + 1]);

        int water = 0;

        for (int i = 0; i < height.size(); ++i)
        {
            int minHeight = min(leftMax[i], rightMax[i]);
            water += minHeight <= height[i] ? 0 : minHeight - height[i];
        }
        return water;
    }
};

// Optimal Approach :  Time ⇒ O(N) , Space ⇒ O(1)
class Solution
{
public:
    int trap(vector<int> &height)
    {

        int left = 0, right = height.size() - 1;

        int leftMax = height[left], rightMax = height[right];

        int water = 0;

        while (left < right)
        {

            if (leftMax <= rightMax)
            {

                ++left;

                water += leftMax > height[left] ? leftMax - height[left] : 0;

                leftMax = max(leftMax, height[left]);
            }
            else
            {

                --right;

                water += rightMax > height[right] ? rightMax - height[right] : 0;

                rightMax = max(rightMax, height[right]);
            }
        }

        return water;
    }
};
