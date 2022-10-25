// https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Function to find maximum of each subarray of size k.
    vector<int> max_of_subarrays(int *arr, int n, int k)
    {
        deque<int> dq;

        vector<int> ans;

        for (int i = 0; i < k; ++i)
        {

            while (!dq.empty() && arr[dq.back()] < arr[i])
                dq.pop_back();

            dq.push_back(i);
        }

        ans.push_back(arr[dq.front()]);

        for (int i = k; i < n; ++i)
        {
            while (!dq.empty() && arr[dq.back()] < arr[i])
                dq.pop_back();

            dq.push_back(i);

            if (!dq.empty() && dq.front() == (i - k))
                dq.pop_front();

            ans.push_back(arr[dq.front()]);
        }

        return ans;
    }
};