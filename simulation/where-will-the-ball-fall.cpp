// https://leetcode.com/problems/where-will-the-ball-fall/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findBall(vector<vector<int>> &grid)
    {

        const int rows = grid.size(), cols = grid[0].size();

        vector<int> pos(cols);

        for (int c = 0; c < cols; ++c)
        {

            int curr_pos = c, next_pos = -1;

            for (int r = 0; r < rows; ++r)
            {

                next_pos = curr_pos + grid[r][curr_pos];

                if (next_pos < 0 || next_pos >= cols || grid[r][curr_pos] != grid[r][next_pos])
                {
                    curr_pos = -1;
                    break;
                }

                curr_pos = next_pos;
            }

            pos[c] = curr_pos;
        }

        return pos;
    }
};