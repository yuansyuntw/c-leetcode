void releaseDP(struct TreeNode *dpNode)
{
    if (dpNode->left != NULL)
    {
        releaseDP(dpNode->left);
    }
    if (dpNode->right != NULL)
    {
        releaseDP(dpNode->right);
    }
    free(dpNode);
}

int max(int value1, int value2)
{
    if (value1 > value2)
    {
        return value1;
    }
    else
    {
        return value2;
    }
}

int sumOfChildNode(struct TreeNode *dpNode)
{
    int sum = 0;
    if (dpNode->left != NULL)
    {
        sum += dpNode->left->val;
    }

    if (dpNode->right != NULL)
    {
        sum += dpNode->right->val;
    }

    return sum;
}

void helper(struct TreeNode *node, struct TreeNode *dpNode)
{
    if (node->left != NULL)
    {
        dpNode->left = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
        helper(node->left, dpNode->left);
    }

    if (node->right != NULL)
    {
        dpNode->right = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
        helper(node->right, dpNode->right);
    }

    int sumOfLayer13 = 0;
    sumOfLayer13 += node->val;
    if (node->left != NULL)
    {
        sumOfLayer13 += sumOfChildNode(dpNode->left);
    }
    if (node->right != NULL)
    {
        sumOfLayer13 += sumOfChildNode(dpNode->right);
    }

    int sumOfLayer2 = sumOfChildNode(dpNode);

    dpNode->val = max(sumOfLayer13, sumOfLayer2);
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int rob(struct TreeNode *root)
{
    struct TreeNode *dp = (struct TreeNode *)calloc(1, sizeof(struct TreeNode));
    helper(root, dp);
    int result = dp->val;
    releaseDP(dp);
    return result;
}
