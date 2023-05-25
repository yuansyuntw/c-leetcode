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
int *rightSideView(struct TreeNode *root, int *returnSize)
{
    int front = 0;
    int end = 0;
    struct TreeNode **nodes = (struct TreeNode **)calloc(100, sizeof(struct TreeNode *));

    if (root != NULL)
    {
        nodes[end++] = root;
    }

    int count = 0;
    int *result = (int *)calloc(100, sizeof(int));

    int lastEnd = end;
    while (end >= front)
    {
        struct TreeNode *node = nodes[front++];
        if (node == NULL)
        {
            break;
        }

        if (node->left != NULL)
        {
            nodes[end++] = node->left;
        }

        if (node->right != NULL)
        {
            nodes[end++] = node->right;
        }

        if (front == lastEnd)
        {
            result[count++] = node->val;

            if (lastEnd == end)
            {
                break;
            }

            lastEnd = end;
        }
    }

    free(nodes);

    *returnSize = count;
    return result;
}