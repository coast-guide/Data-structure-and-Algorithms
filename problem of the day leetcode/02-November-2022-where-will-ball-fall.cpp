//  https://leetcode.com/problems/where-will-the-ball-fall/submissions/

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

public:
    vector<int> findBall(vector<vector<int>> &grid)
    {

        if (grid.empty())
            return {};

        vector<int> ans;

        dfsSolution(grid, ans);

        return ans;
    }
};
int main(int argc, char const *argv[])
{
    Solution s;
    vector<vector<int>> grid{{1, 1, 1, -1, -1}, {1, 1, 1, -1, -1}, {-1, -1, -1, 1, 1}, {1, 1, 1, 1, -1}, {-1, -1, -1, -1, -1}};
    vector<int> ans = s.findBall(grid);
    for (int i : ans)
        cout << i << " ";
    return 0;
}
