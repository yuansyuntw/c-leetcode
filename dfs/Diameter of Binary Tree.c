int maxLength;

int max(int left, int right)
{
    if (left > right)
    {
        return left;
    }
    else
    {
        return right;
    }
}

int dfs(struct TreeNode *node)
{
    int leftLength = 0;
    if (node->left != NULL)
    {
        leftLength = dfs(node->left);
    }
    int rightLength = 0;
    if (node->right != NULL)
    {
        rightLength = dfs(node->right);
    }

    maxLength = max(maxLength, leftLength + rightLength);

    return max(leftLength, rightLength) + 1;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int diameterOfBinaryTree(struct TreeNode *root)
{
    maxLength = 0;
    dfs(root);
    return maxLength;
}
