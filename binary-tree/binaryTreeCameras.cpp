/*
    problem link: https://leetcode.com/problems/binary-tree-cameras/
 */

#include <bits/stdc++.h>
using namespace std;
//   Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{

    int place_cameras(TreeNode *root, int &camera_count)
    {

        // leaf node so need camera
        if (!root->left && !root->right)
            return 0;

        int left_state = !root->left ? 2 : place_cameras(root->left, camera_count);
        int right_state = !root->right ? 2 : place_cameras(root->right, camera_count);

        if (left_state == 0 || right_state == 0)
        {
            ++camera_count;
            return 1;
        }

        return (left_state == 1 || right_state == 1) ? 2 : 0;
    }

public:
    int minCameraCover(TreeNode *root)
    {

        /*
            *start with leaf nodes by placing a camera to its parent
            *postorder traversal
            *STATES => 0 --> need a camera
                        1 --> has a camera
                        2 --> covered by another node
        */

        int camera_count = 0;

        int state = place_cameras(root, camera_count);

        return state == 0 ? ++camera_count : camera_count;
    }
};