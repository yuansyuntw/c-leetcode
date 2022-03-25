/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int g_maxPathSum;

int pathSum(struct TreeNode* root) {
    int maxSum = root->val;

    int leftSum = 0;
    if (root->left != NULL) {
        leftSum = pathSum(root->left);
        if ((leftSum + root->val) >= maxSum) {
            maxSum = leftSum + root->val;
        }
    }
    
    int rightSum = 0;
    if (root->right != NULL) {
        rightSum = pathSum(root->right);
    
        if ((rightSum + root->val) >= maxSum) {
            maxSum = rightSum + root->val;
        }
    }
    
    // local branch
    if ((root->left != NULL) && (root->right != NULL)) {
        int total = leftSum + rightSum + root->val;
        if (total > g_maxPathSum) {
            g_maxPathSum = total;
        }
    }
    
    if (maxSum > g_maxPathSum) {
        g_maxPathSum = maxSum;
    }
    
    return maxSum;
}

int maxPathSum(struct TreeNode* root){
    g_maxPathSum = root->val;
    int rootPathSum = pathSum(root);
    return g_maxPathSum;
}