/*
    problem link: https://leetcode.com/problems/longest-increasing-subsequence/
 */

#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int memoize(int i, int prev, vector<int> &arr, int n, vector<vector<int>> &dp)
    {
        if (i == n)
            return 0;

        if (dp[i][prev + 1] != -1)
            return dp[i][prev + 1];

        int lis = memoize(i + 1, prev, arr, n, dp); // skip

        if (prev == -1 || arr[i] > arr[prev])
            lis = max(lis, 1 + memoize(i + 1, i, arr, n, dp)); // take

        return dp[i][prev + 1] = lis;
    }

    int tabulation(vector<int> &arr, int n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        for (int i = n - 1; i >= 0; i--)
        {
            for (int prev = i - 1; prev >= -1; prev--)
            {
                int lis = dp[i + 1][prev + 1]; // skip

                if (prev == -1 || arr[i] > arr[prev])
                    lis = max(lis, 1 + dp[i + 1][i + 1]); // take

                dp[i][prev + 1] = lis;
            }
        }
        return dp[0][0];
    }

    int doubleArraySpaceOptimized(vector<int> &arr, int n)
    {
        vector<int> prev_row(n + 1), curr_row(n + 1);

        for (int i = n - 1; i >= 0; i--)
        {
            for (int prev = i - 1; prev >= -1; prev--)
            {
                int lis = prev_row[prev + 1]; // skip

                if (prev == -1 || arr[i] > arr[prev])
                    lis = max(lis, 1 + prev_row[i + 1]); // take

                curr_row[prev + 1] = lis;
            }
            prev_row = curr_row;
        }
        return prev_row[0];
    }

    int singleArraySpaceOptimized(vector<int> &arr, int n)
    {
        vector<int> lcs(n, 1);

        int longest = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[i] > arr[j])
                    lcs[i] = max(lcs[i], 1 + lcs[j]);
            }
            longest = max(longest, lcs[i]);
        }

        return longest;
    }
    void printLCS(vector<int> &arr, int n)
    {
        vector<int> lcs(n, 1), prev(n, -1), ans;

        int lcs_ind = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {

                if (arr[j] < arr[i] && 1 + lcs[j] > lcs[i])
                {
                    lcs[i] = 1 + lcs[j];
                    prev[i] = j;
                }
            }

            if (lcs[lcs_ind] < lcs[i])
                lcs_ind = i;
        }

        int i = lcs_ind;
        while (i >= 0)
        {
            ans.push_back(arr[i]);
            i = prev[i];
        }

        reverse(ans.begin(), ans.end());
        for (int ele : ans)
            cout << ele << " ";
        cout << endl;
    }

    int optimalSolution(vector<int> &arr, int n)
    {
        vector<int> prev{arr[0]};

        for (int i = 1; i < n; i++)
        {

            if (arr[i] > prev.back())
                prev.push_back(arr[i]);
            else
            {
                int ind = lower_bound(prev.begin(), prev.end(), arr[i]) - prev.begin();
                prev[ind] = arr[i];
            }
        }
        return prev.size();
    }

    int lengthOfLIS(vector<int> &nums)
    {
        const int n = nums.size();
        // vector<vector<int>> dp(n,vector<int>(n+1,-1));
        // return memoize(0,-1,nums,n,dp);

        // return doubleArraySpaceOptimized(nums, n);
        // return singleArraySpaceOptimized(nums, n);
        // printLCS(nums, n);
        return optimalSolution(nums, n);
    }
};
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Solution s;
    s.printLCS(arr, n);
    cout << "length : " << s.lengthOfLIS(arr) << endl;

    return 0;
}
