bool result = true;

int abs(int value)
{
    if (value < 0)
    {
        return -1 * value;
    }

    return value;
}

int max(int lhs, int rhs)
{
    if (lhs > rhs)
    {
        return lhs;
    }
    return rhs;
}

int dfs(struct TreeNode *root)
{
    if (!result)
    {
        return 0;
    }

    if (root == NULL)
    {
        return 0;
    }

    int leftDepth = 0;
    if (root->left != NULL)
    {
        leftDepth = dfs(root->left); // 3
    }

    int rightDepth = 0;
    if (root->right != NULL)
    {
        rightDepth = dfs(root->right); // 1
    }

    if (abs(leftDepth - rightDepth) > 1)
    {
        result = false;
        return 0;
    }

    return max(leftDepth, rightDepth) + 1; // 3
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isBalanced(struct TreeNode *root)
{
    result = true;
    dfs(root);
    return result;
}
