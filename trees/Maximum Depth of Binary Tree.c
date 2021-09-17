/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


int maxDepth(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    
    int depth = 1;
    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);
    
    if (leftDepth > rightDepth) {
        depth += leftDepth;
    } else {
        depth += rightDepth;
    }
    
    return depth;
}