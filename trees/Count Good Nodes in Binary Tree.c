int result;

void dfs(struct TreeNode *node, int max)
{
    if (node == NULL)
    {
        return;
    }
    if (node->val >= max)
    {
        result++;
        max = node->val;
    }
    dfs(node->left, max);
    dfs(node->right, max);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int goodNodes(struct TreeNode *root)
{
    result = 0;
    dfs(root, root->val);
    return result;
}
