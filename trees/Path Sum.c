/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool checkPathSum(struct TreeNode* node, int parentSum, int targetSum) {
    bool isSameSum = false;
    if ((node->left == NULL) && (node->right == NULL)) {
        if ((parentSum + node->val) == targetSum) {
            isSameSum = true;
        } 
    } else {
        if (node->left != NULL) {
            isSameSum = checkPathSum(node->left, parentSum + node->val, targetSum);
        }
        
        if (isSameSum) {
            return true;
        }

        if (node->right != NULL) {
            isSameSum = checkPathSum(node->right, parentSum + node->val, targetSum);
        }

        if (isSameSum) {
            return true;
        }
    }

    return isSameSum;
}

bool hasPathSum(struct TreeNode* root, int targetSum){
    if (root == NULL) {
        return false;
    }
    
    return checkPathSum(root, 0, targetSum);
}