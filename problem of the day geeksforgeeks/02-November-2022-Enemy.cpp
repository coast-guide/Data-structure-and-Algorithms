// https://practice.geeksforgeeks.org/problems/enemy/1
#include <bits/stdc++.h>
using namespace std;
class Solution
{
    int dfs(int x, int y, vector<vector<int>> &matrix)
    {
        if (x < 0 || y < 0 || x >= matrix.size() || y >= matrix[0].size() || matrix[x][y] == 1)
            return 0;

        int cnt = 1;

        matrix[x][y] = 1;

        int dx[4]{0, 0, -1, 1}, dy[4]{-1, 1, 0, 0};

        for (int i = 0; i < 4; ++i)
            cnt += dfs(x + dx[i], y + dy[i], matrix);

        return cnt;
    }

    int dfsSol(int r, int c, int k, vector<vector<int>> &enemy)
    {
        vector<int> rows, cols;
        for (vector<int> &p : enemy)
        {
            rows.push_back(p[0] - 1);
            cols.push_back(p[1] - 1);
        }

        vector<vector<int>> matrix(r, vector<int>(c));

        for (int row : rows)
            for (int j = 0; j < c; ++j)
                matrix[row][j] = 1;

        for (int col : cols)
            for (int i = 0; i < r; ++i)
                matrix[i][col] = 1;

        int maxArea = 0;

        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                if (matrix[i][j] == 0)
                    maxArea = max(maxArea, dfs(i, j, matrix));
            }
        }

        return maxArea;
    }

    int greedySolution(int r, int c, int k, vector<vector<int>> &enemy)
    {
        if (enemy.empty())
            return r * c;

        vector<int> rows, cols;

        for (vector<int> &e : enemy)
        {
            rows.push_back(e[0]);
            cols.push_back(e[1]);
        }

        sort(rows.begin(), rows.end());
        sort(cols.begin(), cols.end());

        rows.push_back(r + 1);
        cols.push_back(c + 1);

        int max_row = rows[0] - 1;

        for (int i = 1; i < rows.size(); ++i)
        {
            max_row = max(max_row, rows[i] - rows[i - 1] - 1);
        }

        int max_col = cols[0] - 1;

        for (int i = 1; i < cols.size(); ++i)
        {
            max_col = max(max_col, cols[i] - cols[i - 1] - 1);
        }

        return max_row * max_col;
    }

public:
    int largestArea(int r, int c, int k, vector<vector<int>> &enemy)
    {
        return greedySolution(r, c, k, enemy);
    }
};