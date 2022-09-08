#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/the-skyline-problem/

class Solution
{
public:
    vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
    {

        vector<pair<int, int>> pairs;

        for (vector<int> &b : buildings)
        {
            pairs.push_back({b[0], -b[2]});
            pairs.push_back({b[1], b[2]});
        }

        sort(pairs.begin(), pairs.end());

        int curr_height = 0;

        multiset<int> heights = {0};

        vector<vector<int>> ans;

        for (pair<int, int> &p : pairs)
        {

            int x = p.first, height = p.second;

            if (height < 0)
                heights.insert(-height);
            else
                heights.erase(heights.find(height));

            int max_height = *heights.rbegin();

            if (curr_height != max_height)
            {
                ans.push_back({x, max_height});
                curr_height = max_height;
            }
        }

        return ans;
    }
};
