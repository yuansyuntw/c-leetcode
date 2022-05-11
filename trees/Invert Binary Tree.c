/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void switchChild(struct TreeNode* root) {
    if (root == NULL) return;
    
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    switchChild(root->left);
    switchChild(root->right);
}

struct TreeNode* invertTree(struct TreeNode* root){
    switchChild(root);
    return root;
}