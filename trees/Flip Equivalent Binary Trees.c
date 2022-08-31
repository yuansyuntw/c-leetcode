/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool flipEquiv(struct TreeNode* root1, struct TreeNode* root2){
    if ((root1 == NULL) || (root2 == NULL)) {
        if (root1 == root2) {
            return true;
        }
        
        return false;
    }
    
    bool isDifferentValue = (root1->val != root2->val);
    if (isDifferentValue) {
        return false;
    }
    
    // no-flip
    bool isSameChilds = flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right);
    if (isSameChilds) {
        return true;
    }
    
    // flip
    bool isSameFlipedChilds = flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left);
    return isSameFlipedChilds;
}