/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int gLookedCount;

int dfsInorder(struct TreeNode* root, int k) {
    if (root->left != NULL) {
        int value = dfsInorder(root->left, k);
        if (gLookedCount == k) return value;
    }
    
    gLookedCount++;
    if (gLookedCount == k) return root->val;
    
    if (root->right != NULL) {
        int value = dfsInorder(root->right, k);
        if (gLookedCount == k) return value;
    }
    
    return -1;
}

int kthSmallest(struct TreeNode* root, int k){
    // This global variable should be initialized before each test case
    gLookedCount = 0;
    return dfsInorder(root, k);
}