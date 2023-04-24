/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
    int *result = (int *)calloc(100, sizeof(int));
    int resultCount = 0;

    struct TreeNode **stack = (struct TreeNode **)calloc(100, sizeof(struct TreeNode *));
    int stackCount = 0;

    if (root == NULL)
    {
        *returnSize = 0;
        return result;
    }

    struct TreeNode *node = root;
    while (node != NULL)
    {
        if (node->left != NULL)
        {
            stack[stackCount++] = node;
            node = node->left;
            continue;
        }

        result[resultCount++] = node->val;
        if (node->right != NULL)
        {
            node = node->right;
            continue;
        }
        else
        {
            node = NULL;
        }

        while (stackCount > 0)
        {
            struct TreeNode *parent = stack[--stackCount];
            result[resultCount++] = parent->val;
            if (parent->right != NULL)
            {
                node = parent->right;
                break;
            }
        }
    }

    free(stack);

    *returnSize = resultCount;
    return result;
}
