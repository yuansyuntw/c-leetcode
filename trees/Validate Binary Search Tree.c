/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* lastNode;

bool isValidBSTForBranch(struct TreeNode* root){
    if (root == NULL) {
        return true;
    }
    
    if ((root->left != NULL) && !isValidBSTForBranch(root->left)) {
        return false;
    }
    
    if (lastNode != NULL) {
        if (lastNode->val >= root->val) {
            return false;
        }
    }
    
    lastNode = root;
    
    if (root->right != NULL) {
        return isValidBSTForBranch(root->right);
    }
    
    return true;
}

bool isValidBST(struct TreeNode* root) {
    lastNode = NULL;
    return isValidBSTForBranch(root);
}