// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
class Solution
{

    bool canPartition(int start, int current_sum, int k, vector<int> &used, const int target, const vector<int> &nums)
    {
        // We already found k - 1 subsets with sum = target so the remaining subset will be definitely equal to the sum = target as the total sum is (k * target)
        if (k == 1)
            return true;

        if (start == nums.size())
            return false;

        // Found one subset with sum = target
        if (current_sum == target)
        {
            // Now try to find remaining subsets
            return canPartition(0, 0, k - 1, used, target, nums);
        }

        for (int index = start; index < nums.size(); ++index)
        {
            if (used[index] || nums[index] + current_sum > target)
                continue;

            used[index] = true;

            if (canPartition(index + 1, current_sum + nums[index], k, used, target, nums))
                return true;

            used[index] = false;
        }

        return false;
    }

public:
    bool canPartitionKSubsets(vector<int> &nums, int k)
    {

        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (nums.size() < k || sum % k != 0)
            return false;

        sort(nums.begin(), nums.end(), greater<int>());

        int target = sum / k;

        vector<int> used(nums.size());

        return canPartition(0, 0, k, used, target, nums);
    }
};