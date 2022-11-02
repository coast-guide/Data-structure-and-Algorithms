//  https://leetcode.com/problems/where-will-the-ball-fall/
#include <bits/stdc++.h>
using namespace std;

class Solution
{

    bool isValid(int x, int y, vector<vector<int>> &grid)
    {
        return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size();
    }

    int dfs(int x, int y, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {

        if (x == grid.size())
            return y;

        if (!isValid(x, y, grid))
            return -1;

        if (dp[x][y] != -1)
            return dp[x][y];

        if (grid[x][y] == 1 && isValid(x, y + 1, grid) && grid[x][y + 1] == 1)
            return dp[x][y] = dfs(x + 1, y + 1, grid, dp);

        if (grid[x][y] == -1 && isValid(x, y - 1, grid) && grid[x][y - 1] == -1)
            return dp[x][y] = dfs(x + 1, y - 1, grid, dp);

        return -1;
    }

    void dfsSolution(vector<vector<int>> &grid, vector<int> &ans)
    {
        vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), -1));
        for (int c = 0; c < grid[0].size(); ++c)
            ans.push_back(dfs(0, c, grid, dp));
    }

    void optimizedSolution(vector<vector<int>> &grid, vector<int> &ans)
    {
        for (int c = 0; c < grid[0].size(); ++c)
        {
            int curr_row = 0, curr_col = c;

            while (curr_row < grid.size())
            {
                if (grid[curr_row][curr_col] == 1 && curr_col + 1 < grid[0].size() && grid[curr_row][curr_col + 1] == 1)
                {
                    ++curr_row;
                    ++curr_col;
                }
                else if (grid[curr_row][curr_col] == -1 && curr_col - 1 >= 0 && grid[curr_row][curr_col - 1] == -1)
                {
                    ++curr_row;
                    --curr_col;
                }
                else
                    break;
            }

            ans.push_back(curr_row == grid.size() ? curr_col : -1);
        }
    }

public:
    vector<int> findBall(vector<vector<int>> &grid)
    {

        if (grid.empty())
            return {};

        vector<int> ans;

        // dfsSolution(grid, ans);

        optimizedSolution(grid, ans);

        return ans;
    }
};
